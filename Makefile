#
# Makefile for the clac project.
#

CXX=g++
CXXFLAGS=-std=c++11 -c -O -I../Spica -I../Scr -IClacEntity -IClacEngine
LINK=g++
LINKFLAGS=-lncurses
SOURCES=clac.cpp              \
	record_f.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=clac
LIBSPICA=../Spica/Cpp/libSpicaCpp.a
LIBENTITY=ClacEntity/libClacEntity.a
LIBENGINE=ClacEngine/libClacEngine.a

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXECUTABLE):	$(OBJECTS)
	$(CXX) $(OBJECTS) $(LIBSPICA) $(LIBENGINE) $(LIBENTITY) $(LINKFLAGS) -o $@


# File Dependencies
###################

# Module dependencies -- Produced with 'depend' on Tue Jan 14 20:16:06 2020


clac.o:	clac.cpp ClacEntity/BinaryEntity.hpp ClacEntity/Entity.hpp ClacEntity/FloatEntity.hpp \
	ClacEntity/IntegerEntity.hpp ClacEntity/VeryLong.hpp ClacEntity/StringEntity.hpp ClacEntity/convert.hpp \
	ClacEntity/support.hpp ClacEngine/actions.hpp ClacEngine/cstack.hpp ClacEngine/get.hpp ClacEngine/WordStream.hpp \
	ClacEngine/global.hpp ClacEngine/words.hpp 

record_f.o:	record_f.cpp record_f.h 


# Additional Rules
##################
clean:
	rm -f *.bc *.bc1 *.bc2 *.o $(EXECUTABLE) *.s *.ll *~
