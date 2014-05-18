#include	<chrono>

#include	"RandomInt.hpp"
#include	"RandomReal.hpp"

std::default_random_engine	RandomInt::seed(std::chrono::system_clock::now().time_since_epoch().count());
std::default_random_engine	RandomReal::seed(std::chrono::system_clock::now().time_since_epoch().count());
