/******************************************************************************/
/*                                                                            */
/*              ex2.c in ex2_mutexes in 3_threads_sous_unix                   */
/*              For Epitech's C++ Knowledge Unit                              */
/*              Made by : Uriel Corfa <uriel@corfa.fr>                        */
/*              Modified by : David Giron <thor@epitech.net>                  */
/*                                                                            */
/******************************************************************************/



#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <pthread.h>


struct			s_counter
{
  int			ctr;
  pthread_mutex_t	mutex;
};


void	init_counter(struct s_counter* c)
{
  c->ctr = 0;
  pthread_mutex_init(&c->mutex, NULL);
}


void	clean_counter(struct s_counter* c)
{
  c->ctr = 0;
  pthread_mutex_destroy(&c->mutex);
}



/******************************************************************************/



void*	increment_with_mutexes(void* param)
{
  struct s_counter* counter = param;
  for (int i = 0; i < 100000; ++i)
    {
      pthread_mutex_lock(&counter->mutex);
      ++(counter->ctr);
      pthread_mutex_unlock(&counter->mutex);
    }
  return NULL;
}


void*	increment_without_mutexes(void* param)
{
  int* counter = param;
  for (int i = 0; i < 100000; ++i)
    ++(*counter);
  return NULL;
}


int	main(void)
{
  {
    printf("Test sans mutexes\n");

    pthread_t thr1;
    pthread_t thr2;
    int counter = 0;

    pthread_create(&thr1, NULL, &increment_without_mutexes, &counter);
    pthread_create(&thr2, NULL, &increment_without_mutexes, &counter);

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    
    printf("Fin du test : counter = %d\n", counter);
  }


  {
    printf("Test avec mutexes\n");

    pthread_t thr1;
    pthread_t thr2;
    struct s_counter counter;

    init_counter(&counter);

    pthread_create(&thr1, NULL, &increment_with_mutexes, &counter);
    pthread_create(&thr2, NULL, &increment_with_mutexes, &counter);

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);

    printf("Fin du test : counter = %d\n", counter.ctr);

    clean_counter(&counter);
  }
  
  return 0;
}



/******************************************************************************/
