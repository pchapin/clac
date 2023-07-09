#
# Makefile for the Clac project.
#

CXX=g++
CXXFLAGS=-c -g -std=c++20 -Wall -IClacEntity -IClacEngine -IScr -ISpicaCpp
LINK=g++
SOURCES=clac.cpp          \
	ClacCommandWindow.cpp \
	DirectoryWindow.cpp   \
	StackWindow.cpp       \
	RecordFile.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=clac
LIBENTITY=ClacEntity/libClacEntity.a
LIBENGINE=ClacEngine/libClacEngine.a
LIBSCR=Scr/libScr.a
LIBSPICACPP=SpicaCpp/libSpicaCpp.a

.PHONY:	all
all:	$(EXECUTABLE)

# Recursive Build
# See: https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
# Also, see: https://accu.org/journals/overload/14/71/miller_2004/ for a discussion about why
# recursive make is supposedly bad. Note that Miller's example is a crazy way of organizing
# a multi-module project, and so we regard Miller's article as something of a straw man. 
#################
COMPONENTS = check ClacEngine ClacEntity Scr SpicaCpp

.PHONY:	components $(COMPONENTS)
components:	$(COMPONENTS)

$(COMPONENTS):
	$(MAKE) -C $@


# Component Dependencies
########################

check:	ClacEngine ClacEntity SpicaCpp


# Top-Level Rules and Dependencies
###################################

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXECUTABLE):	components $(OBJECTS) $(LIBENGINE) $(LIBENTITY) $(LIBSCR) $(LIBSPICACPP)
	$(CXX) $(OBJECTS) $(LIBENGINE) $(LIBENTITY) $(LIBSCR) $(LIBSPICACPP) -lcurses $(LINKFLAGS) -o $@


# File Dependencies
###################

# Module dependencies -- Produced with 'depend' on Mon Jun 26 14:19:31 2023


clac.o:	clac.cpp Scr/debug.hpp Scr/scr.hpp Scr/TextWindow.hpp Scr/Window.hpp Scr/ImageBuffer.hpp \
	Scr/MessageWindow.hpp Scr/Shadow.hpp ClacEngine/Global.hpp SpicaCpp/VeryLong.hpp ClacEngine/ClacStack.hpp \
	ClacEntity/Entity.hpp ClacEngine/WordStream.hpp ClacCommandWindow.hpp Scr/CommandWindow.hpp \
	Scr/Manager.hpp DirectoryWindow.hpp ClacEntity/DirectoryEntity.hpp StackWindow.hpp 

ClacCommandWindow.o:	ClacCommandWindow.cpp ClacEntity/convert.hpp ClacEntity/Entity.hpp ClacEntity/support.hpp \
	ClacEngine/actions.hpp ClacEngine/ClacStack.hpp SpicaCpp/VeryLong.hpp ClacEngine/get.hpp \
	ClacEngine/WordStream.hpp ClacEngine/Global.hpp ClacCommandWindow.hpp Scr/CommandWindow.hpp \
	Scr/ImageBuffer.hpp Scr/scr.hpp Scr/Manager.hpp Scr/Window.hpp 

DirectoryWindow.o:	DirectoryWindow.cpp Scr/scr.hpp ClacEntity/LabeledEntity.hpp ClacEntity/Entity.hpp \
	DirectoryWindow.hpp Scr/ImageBuffer.hpp Scr/Manager.hpp Scr/Window.hpp ClacEntity/DirectoryEntity.hpp \
	

StackWindow.o:	StackWindow.cpp Scr/scr.hpp ClacEntity/Entity.hpp StackWindow.hpp Scr/ImageBuffer.hpp \
	Scr/Manager.hpp Scr/Window.hpp ClacEngine/ClacStack.hpp SpicaCpp/VeryLong.hpp 

RecordFile.o:	RecordFile.cpp RecordFile.hpp


# Additional Rules
##################
.PHONY:	clean
clean:
	$(MAKE) -C check clean
	$(MAKE) -C ClacEngine clean
	$(MAKE) -C ClacEntity clean
	$(MAKE) -C Scr clean
	$(MAKE) -C SpicaCpp clean
	rm -f *.bc *.bc1 *.bc2 *.o $(EXECUTABLE) *.s *.ll *~
