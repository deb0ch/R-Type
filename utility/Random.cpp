#include	<chrono>

#include	"RandomInt.hpp"
#include	"RandomReal.hpp"

std::default_random_engine	RandomInt::seed(std::chrono::system_clock::now().time_since_epoch().count());
std::default_random_engine	RandomReal::seed(std::chrono::system_clock::now().time_since_epoch().count());

/**
 * To generate a random number with parameters :
 * std::cout << RandomInt()(0, 5) << std::endl;
 * With only the minimum :
 * std::cout << RandomInt()(0) << std::endl;
 * Without any parameters, it's tricky :
 * std::cout << RandomInt().operator() <int>() << std::endl;
 */
