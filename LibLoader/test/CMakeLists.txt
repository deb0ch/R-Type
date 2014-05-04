CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(PLATYPUS_H_
	Platypus.hh
	IAnimal.hh)

SET(PLATYPUS_CPP_
  Platypus.cpp)

SET(ARMADILLO_H_
	Armadillo.hh
	IAnimal.hh)

SET(ARMADILLO_CPP_
	Armadillo.cpp)	
	
  
SET (LIB_TYPE SHARED)

ADD_LIBRARY(platypus ${LIB_TYPE} ${PLATYPUS_CPP_})
ADD_LIBRARY(armadillo ${LIB_TYPE} ${ARMADILLO_CPP_})
