#
# Makefile for the Clac unit test program.
#

CXX=g++
CXXFLAGS=-std=c++20 -c -g -I../ClacEntity -I../ClacEngine
LINK=g++
LINKFLAGS=
SOURCES=u_tests.cpp             \
    VeryLong_tests.cpp          \
	UnitTestManager.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=u_tests
LIBENTITY=../ClacEntity/libClacEntity.a
LIBENGINE=../ClacEngine/libClacEngine.a

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXECUTABLE):	$(OBJECTS)
	$(CXX) $(OBJECTS) $(LIBENGINE) $(LIBENTITY) $(LINKFLAGS) -o $@


# File Dependencies
###################

# Module dependencies -- Produced with 'depend' on Thu May 27 17:11:15 2021


u_tests.o:	u_tests.cpp u_tests.hpp UnitTestManager.hpp 

VeryLong_tests.o:	VeryLong_tests.cpp ../ClacEntity/VeryLong.hpp 

UnitTestManager.o:	UnitTestManager.cpp UnitTestManager.hpp 


# Additional Rules
##################
clean:
	rm -f *.bc *.bc1 *.bc2 *.o $(EXECUTABLE) *.s *.ll *~
