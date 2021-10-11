CPPFILES = ECTextViewImp.cpp ECEditorTest.cpp

HFILES = $(CPPFILES:.cpp=.h)

OFILES= $(CPPFILES:.cpp=.o)

CC = g++
LIBPATH =

CFLAGS = -O3 -std=c++11 -Wall -I.

all: Editor

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

Editor:$(OFILES)
	$(CC) -o Editor $(OFILES)

clean: 
	rm *.o
	rm Editor

