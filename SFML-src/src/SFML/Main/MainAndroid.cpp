////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2014 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// Android specific: we define the ANativeActivity_onCreate
// entry point, handling all the native activity stuff, then
// we call the user defined (and poratble) main function in
// an external thread so developers can keep a portable code
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Config.hpp>

#ifdef SFML_SYSTEM_ANDROID

#include <SFML/Window/EGLCheck.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Android/Activity.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Thread.hpp>
#include <SFML/System/Lock.hpp>


extern int main(int argc, char *argv[]);

namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
ActivityStates* retrieveStates(ANativeActivity* activity)
{
    // Hide the ugly cast we find in each callback function
    return (ActivityStates*)activity->instance;
}


////////////////////////////////////////////////////////////
static void initializeMain(ActivityStates* states)
{
    // Protect from concurent access
    Lock lock(states->mutex);

    // Prepare and share the looper to be read later
    ALooper* looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    states->looper = looper;

    // Get the default configuration
    states->config = AConfiguration_new();
    AConfiguration_fromAssetManager(states->config, states->activity->assetManager);
}


////////////////////////////////////////////////////////////
static void terminateMain(ActivityStates* states)
{
    // Protect from concurent access
    Lock lock(states->mutex);

    // The main thread has finished, we must explicitly ask the activity to finish
    states->mainOver = true;
    ANativeActivity_finish(states->activity);
}


////////////////////////////////////////////////////////////
void* main(ActivityStates* states)
{
    // Initialize the thread before giving the hand
    initializeMain(states);

    {
        Lock lock(states->mutex);

        states->initialized = true;
    }

    sleep(seconds(0.5));
    ::main(0, NULL);

    // Terminate properly the main thread and wait until it's done
    terminateMain(states);

    {
        Lock lock(states->mutex);

        states->terminated = true;
    }

    return NULL;
}

} // namespace priv
} // namespace sf


////////////////////////////////////////////////////////////
static void onStart(ANativeActivity* activity)
{
}


////////////////////////////////////////////////////////////
static void onResume(ANativeActivity* activity)
{
    // Retrieve our activity states from the activity instance
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);
    sf::Lock lock(states->mutex);

    // Send an event to warn people the activity has been resumed
    sf::Event event;
    event.type = sf::Event::MouseEntered;

    states->pendingEvents.push_back(event);
}


////////////////////////////////////////////////////////////
static void onPause(ANativeActivity* activity)
{
    // Retrieve our activity states from the activity instance
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);
    sf::Lock lock(states->mutex);

    // Send an event to warn people the activity has been paused
    sf::Event event;
    event.type = sf::Event::MouseLeft;

    states->pendingEvents.push_back(event);
}


////////////////////////////////////////////////////////////
static void onStop(ANativeActivity* activity)
{
}


////////////////////////////////////////////////////////////
static void onDestroy(ANativeActivity* activity)
{
    // Retrieve our activity states from the activity instance
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);

    // Send an event to warn people the activity is being destroyed
    {
        sf::Lock lock(states->mutex);

        // If the main thread hasn't yet finished, send the event and wait for
        // it to finish.
        if (!states->mainOver)
        {
            sf::Event event;
            event.type = sf::Event::Closed;

            states->pendingEvents.push_back(event);
        }
    }

    // Wait for the main thread to be terminated
    states->mutex.lock();

    while (!states->terminated)
    {
        states->mutex.unlock();
        sf::sleep(sf::milliseconds(20));
        states->mutex.lock();
    }

    states->mutex.unlock();

    // Terminate EGL display
    eglCheck(eglTerminate(states->display));

    // Delete our allocated states
    delete states;

    // The application should now terminate
}


////////////////////////////////////////////////////////////
static void onNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);
    sf::Lock lock(states->mutex);

    // Update the activity states
    states->window = window;

    // Notify SFML mechanism
    sf::Event event;
    event.type = sf::Event::GainedFocus;
    states->pendingEvents.push_back(event);

    // Wait for the event to be taken into account by SFML
    states->updated = false;
    while(!states->updated)
    {
        states->mutex.unlock();
        sf::sleep(sf::milliseconds(10));
        states->mutex.lock();
    }
}


////////////////////////////////////////////////////////////
static void onNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);
    sf::Lock lock(states->mutex);

    // Update the activity states
    states->window = NULL;

    // Notify SFML mechanism
    sf::Event event;
    event.type = sf::Event::LostFocus;
    states->pendingEvents.push_back(event);

    // Wait for the event to be taken into account by SFML
    states->updated = false;
    while(!states->updated)
    {
        states->mutex.unlock();
        sf::sleep(sf::milliseconds(10));
        states->mutex.lock();
    }
}


////////////////////////////////////////////////////////////
static void onNativeWindowRedrawNeeded(ANativeActivity* activity, ANativeWindow* window)
{
}


////////////////////////////////////////////////////////////
static void onNativeWindowResized(ANativeActivity* activity, ANativeWindow* window)
{
}


////////////////////////////////////////////////////////////
static void onInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{
    // Retrieve our activity states from the activity instance
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);

    // Attach the input queue
    {
        sf::Lock lock(states->mutex);

        AInputQueue_attachLooper(queue, states->looper, 1, states->processEvent, NULL);
        states->inputQueue = queue;
    }
}


////////////////////////////////////////////////////////////
static void onInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{
    // Retrieve our activity states from the activity instance
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);

    // Detach the input queue
    {
        sf::Lock lock(states->mutex);

        states->inputQueue = NULL;
        AInputQueue_detachLooper(queue);
    }
}


////////////////////////////////////////////////////////////
static void onWindowFocusChanged(ANativeActivity* activity, int focused)
{
}


////////////////////////////////////////////////////////////
static void onContentRectChanged(ANativeActivity* activity, const ARect* rect)
{
    // Retrieve our activity states from the activity instance
    sf::priv::ActivityStates* states = sf::priv::retrieveStates(activity);
    sf::Lock lock(states->mutex);

    // Send an event to warn people about the window move/resize
    sf::Event event;
    event.type = sf::Event::Resized;
    event.size.width = ANativeWindow_getWidth(states->window);
    event.size.height = ANativeWindow_getHeight(states->window);

    states->pendingEvents.push_back(event);
}


////////////////////////////////////////////////////////////
static void onConfigurationChanged(ANativeActivity* activity)
{
}


////////////////////////////////////////////////////////////
static void* onSaveInstanceState(ANativeActivity* activity, size_t* outLen)
{
    *outLen = 0;

    return NULL;
}


////////////////////////////////////////////////////////////
static void onLowMemory(ANativeActivity* activity)
{
}


////////////////////////////////////////////////////////////
int dummyProcessEvent(int fd, int events, void* data)
{
    // Do nothing
    return 0;
}


////////////////////////////////////////////////////////////
void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
    // Create an activity states (will keep us in the know, about events we care)
    sf::priv::ActivityStates* states = NULL;
    states = new sf::priv::ActivityStates;

    // Initialize the states value
    states->activity   = NULL;
    states->window     = NULL;
    states->looper     = NULL;
    states->inputQueue = NULL;
    states->config     = NULL;

    for (unsigned int i = 0; i < sf::Mouse::ButtonCount; i++)
        states->isButtonPressed[i] = false;
        
    states->display = eglCheck(eglGetDisplay(EGL_DEFAULT_DISPLAY));

    // As the input queue will be created before the SFML window, we need to use
    // this dummy function that will be replaced later by the first created
    // SFML window
    states->processEvent = dummyProcessEvent;

    if (savedState != NULL) {
        states->savedState = malloc(savedStateSize);
        states->savedStateSize = savedStateSize;
        memcpy(states->savedState, savedState, savedStateSize);
    }

    states->mainOver = false;

    states->initialized = false;
    states->terminated = false;

    // Share it across the SFML modules
    sf::priv::getActivity(states);

    // These functions will update the activity states and therefore, will allow
    // SFML to be kept in the know
    activity->callbacks->onStart   = onStart;
    activity->callbacks->onResume  = onResume;
    activity->callbacks->onPause   = onPause;
    activity->callbacks->onStop    = onStop;
    activity->callbacks->onDestroy = onDestroy;

    activity->callbacks->onNativeWindowCreated = onNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = onNativeWindowDestroyed;
    activity->callbacks->onNativeWindowRedrawNeeded = onNativeWindowRedrawNeeded;
    activity->callbacks->onNativeWindowResized = onNativeWindowResized;

    activity->callbacks->onInputQueueCreated = onInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = onInputQueueDestroyed;

    activity->callbacks->onWindowFocusChanged = onWindowFocusChanged;
    activity->callbacks->onContentRectChanged = onContentRectChanged;
    activity->callbacks->onConfigurationChanged = onConfigurationChanged;

    activity->callbacks->onSaveInstanceState = onSaveInstanceState;
    activity->callbacks->onLowMemory = onLowMemory;

    // Share this activity with the callback functions
    states->activity = activity;

    // Initialize the display
    eglCheck(eglInitialize(states->display, NULL, NULL));

    // Launch the main thread
    sf::Thread* thread = new sf::Thread(sf::priv::main, states);
    thread->launch();

    // Wait for the main thread to be initialized
    states->mutex.lock();

    while (!states->initialized)
    {
        states->mutex.unlock();
        sf::sleep(sf::milliseconds(20));
        states->mutex.lock();
    }

    states->mutex.unlock();

    // Share this state with the callback functions
    activity->instance = states;
}

#endif // SFML_SYSTEM_ANDROID
