#
# Makefile for the Clac project.
#

CXX=g++
CXXFLAGS=-c -g -std=c++20 -Wall -IClacEntity -IClacEngine
LINK=g++
SOURCES=clac.cpp              \
	RecordFile.cpp
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
COMPONENTS = ClacEntity ClacEngine check

.PHONY:	components $(COMPONENTS)
components:	$(COMPONENTS)

$(COMPONENTS):
	$(MAKE) -C $@

# In general, the engine depends on the entity library so build them in the right order.
ClacEngine:	ClacEntity

# Top-Level Rules and Dependencies
###################################

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXECUTABLE):	components $(OBJECTS) $(LIBENGINE) $(LIBENTITY)
	$(CXX) $(OBJECTS) $(LIBENGINE) $(LIBENTITY) $(LINKFLAGS) -o $@


# File Dependencies
###################

# Module dependencies -- Produced with 'depend' on Sat Apr  1 10:21:07 2023


clac.o:	clac.cpp ClacEntity/BinaryEntity.hpp ClacEntity/Entity.hpp ClacEntity/FloatEntity.hpp \
	ClacEntity/IntegerEntity.hpp ClacEntity/VeryLong.hpp ClacEntity/StringEntity.hpp ClacEntity/convert.hpp \
	ClacEntity/support.hpp ClacEngine/actions.hpp ClacEngine/ClacStack.hpp ClacEngine/get.hpp \
	ClacEngine/WordStream.hpp ClacEngine/Global.hpp ClacEngine/words.hpp 

RecordFile.o:	RecordFile.cpp RecordFile.hpp 


# Additional Rules
##################
.PHONY:	clean
clean:
	$(MAKE) -C check clean
	$(MAKE) -C ClacEngine clean
	$(MAKE) -C ClacEntity clean
	rm -f *.bc *.bc1 *.bc2 *.o $(EXECUTABLE) *.s *.ll *~
