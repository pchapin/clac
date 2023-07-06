#
# Makefile for the Clac entity library.
#

CXX=g++
CXXFLAGS=-c -g -std=c++20 -Wall
LINK=ar
LINKFLAGS=-r -c
SOURCES=BinaryEntity.cpp    \
	ComplexEntity.cpp   \
	convert.cpp         \
	DirectoryEntity.cpp \
	DisplayState.cpp    \
	Entity.cpp          \
	FloatEntity.cpp     \
	IntegerEntity.cpp   \
	LabeledEntity.cpp   \
	ListEntity.cpp      \
	MatrixEntity.cpp    \
	ProgramEntity.cpp   \
	RationalEntity.cpp  \
	StringEntity.cpp    \
	support.cpp         \
	VectorEntity.cpp    \
	VeryLong.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=libClacEntity.a

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(LIBRARY):	$(OBJECTS)
	$(LINK) $(LINKFLAGS) $@ $(OBJECTS)

# File Dependencies
###################

# Module dependencies -- Produced with 'depend' on Sat Apr  1 10:14:31 2023


BinaryEntity.o:	BinaryEntity.cpp Entities.hpp BinaryEntity.hpp Entity.hpp ComplexEntity.hpp DirectoryEntity.hpp \
	FloatEntity.hpp IntegerEntity.hpp VeryLong.hpp LabeledEntity.hpp ListEntity.hpp MatrixEntity.hpp \
	ProgramEntity.hpp RationalEntity.hpp Rational.hpp StringEntity.hpp VectorEntity.hpp DisplayState.hpp \
	support.hpp 

ComplexEntity.o:	ComplexEntity.cpp Entities.hpp BinaryEntity.hpp Entity.hpp ComplexEntity.hpp DirectoryEntity.hpp \
	FloatEntity.hpp IntegerEntity.hpp VeryLong.hpp LabeledEntity.hpp ListEntity.hpp MatrixEntity.hpp \
	ProgramEntity.hpp RationalEntity.hpp Rational.hpp StringEntity.hpp VectorEntity.hpp DisplayState.hpp \
	support.hpp 

convert.o:	convert.cpp convert.hpp Entity.hpp Entities.hpp BinaryEntity.hpp ComplexEntity.hpp \
	DirectoryEntity.hpp FloatEntity.hpp IntegerEntity.hpp VeryLong.hpp LabeledEntity.hpp ListEntity.hpp \
	MatrixEntity.hpp ProgramEntity.hpp RationalEntity.hpp Rational.hpp StringEntity.hpp VectorEntity.hpp \
	

DirectoryEntity.o:	DirectoryEntity.cpp Entities.hpp BinaryEntity.hpp Entity.hpp ComplexEntity.hpp DirectoryEntity.hpp \
	FloatEntity.hpp IntegerEntity.hpp VeryLong.hpp LabeledEntity.hpp ListEntity.hpp MatrixEntity.hpp \
	ProgramEntity.hpp RationalEntity.hpp Rational.hpp StringEntity.hpp VectorEntity.hpp 

DisplayState.o:	DisplayState.cpp DisplayState.hpp 

Entity.o:	Entity.cpp Entity.hpp 

FloatEntity.o:	FloatEntity.cpp Entities.hpp BinaryEntity.hpp Entity.hpp ComplexEntity.hpp DirectoryEntity.hpp \
	FloatEntity.hpp IntegerEntity.hpp VeryLong.hpp LabeledEntity.hpp ListEntity.hpp MatrixEntity.hpp \
	ProgramEntity.hpp RationalEntity.hpp Rational.hpp StringEntity.hpp VectorEntity.hpp DisplayState.hpp \
	support.hpp 

IntegerEntity.o:	IntegerEntity.cpp Entities.hpp BinaryEntity.hpp Entity.hpp ComplexEntity.hpp DirectoryEntity.hpp \
	FloatEntity.hpp IntegerEntity.hpp VeryLong.hpp LabeledEntity.hpp ListEntity.hpp MatrixEntity.hpp \
	ProgramEntity.hpp RationalEntity.hpp Rational.hpp StringEntity.hpp VectorEntity.hpp 

LabeledEntity.o:	LabeledEntity.cpp Entities.hpp BinaryEntity.hpp Entity.hpp ComplexEntity.hpp DirectoryEntity.hpp \
	FloatEntity.hpp IntegerEntity.hpp VeryLong.hpp LabeledEntity.hpp ListEntity.hpp MatrixEntity.hpp \
	ProgramEntity.hpp RationalEntity.hpp Rational.hpp StringEntity.hpp VectorEntity.hpp 

ListEntity.o:	ListEntity.cpp Entities.hpp BinaryEntity.hpp Entity.hpp ComplexEntity.hpp DirectoryEntity.hpp \
	FloatEntity.hpp IntegerEntity.hpp VeryLong.hpp LabeledEntity.hpp ListEntity.hpp MatrixEntity.hpp \
	ProgramEntity.hpp RationalEntity.hpp Rational.hpp StringEntity.hpp VectorEntity.hpp 

MatrixEntity.o:	MatrixEntity.cpp Entities.hpp BinaryEntity.hpp Entity.hpp ComplexEntity.hpp DirectoryEntity.hpp \
	FloatEntity.hpp IntegerEntity.hpp VeryLong.hpp LabeledEntity.hpp ListEntity.hpp MatrixEntity.hpp \
	ProgramEntity.hpp RationalEntity.hpp Rational.hpp StringEntity.hpp VectorEntity.hpp 

ProgramEntity.o:	ProgramEntity.cpp Entities.hpp BinaryEntity.hpp Entity.hpp ComplexEntity.hpp DirectoryEntity.hpp \
	FloatEntity.hpp IntegerEntity.hpp VeryLong.hpp LabeledEntity.hpp ListEntity.hpp MatrixEntity.hpp \
	ProgramEntity.hpp RationalEntity.hpp Rational.hpp StringEntity.hpp VectorEntity.hpp 

RationalEntity.o:	RationalEntity.cpp Entities.hpp BinaryEntity.hpp Entity.hpp ComplexEntity.hpp DirectoryEntity.hpp \
	FloatEntity.hpp IntegerEntity.hpp VeryLong.hpp LabeledEntity.hpp ListEntity.hpp MatrixEntity.hpp \
	ProgramEntity.hpp RationalEntity.hpp Rational.hpp StringEntity.hpp VectorEntity.hpp 

StringEntity.o:	StringEntity.cpp Entities.hpp BinaryEntity.hpp Entity.hpp ComplexEntity.hpp DirectoryEntity.hpp \
	FloatEntity.hpp IntegerEntity.hpp VeryLong.hpp LabeledEntity.hpp ListEntity.hpp MatrixEntity.hpp \
	ProgramEntity.hpp RationalEntity.hpp Rational.hpp StringEntity.hpp VectorEntity.hpp 

support.o:	support.cpp DisplayState.hpp support.hpp Entity.hpp 

VectorEntity.o:	VectorEntity.cpp Entities.hpp BinaryEntity.hpp Entity.hpp ComplexEntity.hpp DirectoryEntity.hpp \
	FloatEntity.hpp IntegerEntity.hpp VeryLong.hpp LabeledEntity.hpp ListEntity.hpp MatrixEntity.hpp \
	ProgramEntity.hpp RationalEntity.hpp Rational.hpp StringEntity.hpp VectorEntity.hpp 

VeryLong.o:	VeryLong.cpp VeryLong.hpp 


##################
clean:
	rm -f *.bc *.o $(LIBRARY) *.s *.ll *~
