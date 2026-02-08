#
# Makefile for the Clac unit test program.
#

CXX=g++
CXXFLAGS=-std=c++20 -c -g -I../ClacEntity -I../ClacEngine -I../SpicaCpp
LINK=g++
LINKFLAGS=
SOURCES=u_tests.cpp          \
	IntegerEntity_tests.cpp  \
	FloatEntity_tests.cpp
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

# Module dependencies -- Produced with 'depend' on Fri Jul 14 10:56:17 2023


u_tests.o:	u_tests.cpp u_tests.hpp ../SpicaCpp/UnitTestManager.hpp 

IntegerEntity_tests.o:	IntegerEntity_tests.cpp ../SpicaCpp/VeryLong.hpp ../SpicaCpp/UnitTestManager.hpp ../ClacEntity/IntegerEntity.hpp \
	../ClacEntity/Entity.hpp u_tests.hpp 

FloatEntity_tests.o:	FloatEntity_tests.cpp ../SpicaCpp/UnitTestManager.hpp ../ClacEntity/FloatEntity.hpp \
	../ClacEntity/Entity.hpp u_tests.hpp 


# Additional Rules
##################
clean:
	rm -f *.bc *.bc1 *.bc2 *.o $(EXECUTABLE) *.s *.ll *~
