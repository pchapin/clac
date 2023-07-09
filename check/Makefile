#
# Makefile for the Clac unit test program.
#

CXX=g++
CXXFLAGS=-std=c++20 -c -g -I../ClacEntity -I../ClacEngine -I../SpicaCpp
LINK=g++
LINKFLAGS=
SOURCES=u_tests.cpp    \
    VeryLong_tests.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=u_tests
LIBENTITY=../ClacEntity/libClacEntity.a
LIBENGINE=../ClacEngine/libClacEngine.a
LIBSPICACPP=../SpicaCpp/libSpicaCpp.a

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXECUTABLE):	$(OBJECTS) $(LIBENGINE) $(LIBENTITY) $(LIBSPICACPP)
	$(CXX) $(OBJECTS) $(LIBENGINE) $(LIBENTITY) $(LIBSPICACPP) $(LINKFLAGS) -o $@


# File Dependencies
###################

# Module dependencies -- Produced with 'depend' on Thu May 27 17:11:15 2021


u_tests.o:	u_tests.cpp u_tests.hpp ../SpicaCpp/UnitTestManager.hpp 

VeryLong_tests.o:	VeryLong_tests.cpp ../SpicaCpp/VeryLong.hpp 


# Additional Rules
##################
clean:
	rm -f *.bc *.bc1 *.bc2 *.o $(EXECUTABLE) *.s *.ll *~
