#
# Makefile for the Clac project.
#

CXX=g++
CXXFLAGS=-std=c++17 -c -g -IClacEntity -IClacEngine
LINK=g++
SOURCES=clac.cpp              \
	record_f.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=clac
LIBENTITY=ClacEntity/libClacEntity.a
LIBENGINE=ClacEngine/libClacEngine.a

.PHONY:	all
all:	$(EXECUTABLE)

# Recursive Build
# See: https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
# Also, see: https://accu.org/journals/overload/14/71/miller_2004/ for a discussion about why
# recursive make is supposedly bad. Note that Miller's example is a crazy way of organizing
# a multi-module project, and so we regard Miller's article as something of a straw man. 
#################
COMPONENTS = ClacEntity ClacEngine

.PHONY:	components $(COMPONENTS)
components:	$(COMPONENTS)

$(COMPONENTS):
	$(MAKE) -C $@

# Top-Level Rules and Dependencies
###################################

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXECUTABLE):	components $(OBJECTS)
	$(CXX) $(OBJECTS) $(LIBENGINE) $(LIBENTITY) $(LINKFLAGS) -o $@


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
.PHONY:	clean
clean:
	$(MAKE) -C ClacEngine clean
	$(MAKE) -C ClacEntity clean
	rm -f *.bc *.bc1 *.bc2 *.o $(EXECUTABLE) *.s *.ll *~
