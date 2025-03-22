EXE = intro
OBJS = main.o png.o rgbapixel.o intro.o

COMPILER = g++ 
COMPILER_OPTS = -std=c++17 -c -g -O0 -Wall -Wextra -pedantic-errors -Werror
LINKER = g++
LINKER_OPTS = -lpng

all : $(EXE)

$(EXE) : $(OBJS)
	$(LINKER) $(OBJS) $(LINKER_OPTS) -o $(EXE)

main.o : main.cpp ./RGBA/png.h ./RGBA/rgbapixel.h intro.h
	$(COMPILER) $(COMPILER_OPTS) main.cpp

png.o : ./RGBA/png.cpp ./RGBA/png.h ./RGBA/rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) ./RGBA/png.cpp

rgbapixel.o : ./RGBA/rgbapixel.cpp ./RGBA/rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) ./RGBA/rgbapixel.cpp

intro.o : intro.cpp intro.h RGBA/png.h RGBA/rgbapixel.h
	$(COMPILER) $(COMPILER_OPTS) intro.cpp

clean :
	-rm -f *.o $(EXE)