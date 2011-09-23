CC=gcc
FLAGS= -Wall -lstdc++ -lGL -lSDLmain -lSDL -lm -O2
OUT=3body

OBJS=3body.o blackhole.o body.o config.o cosmos.o interface.o mathlib.o \
 object.o painter.o

all: $(OBJS)
	gcc $(FLAGS) -o $(OUT) *.o

3body.o: 3body.cpp 3body.h interface.h cosmos.h object.h vector.h \
 painter.h config.h body.h blackhole.h
	gcc -c $(FLAGS) $< 

blackhole.o: blackhole.cpp blackhole.h object.h vector.h cosmos.h \
 painter.h config.h
	gcc -c $(FLAGS) $< 

body.o: body.cpp body.h object.h vector.h cosmos.h painter.h config.h \
 mathlib.h
	gcc -c $(FLAGS) $< 

config.o: config.cpp config.h object.h vector.h cosmos.h painter.h body.h \
 blackhole.h
	gcc -c $(FLAGS) $< 

cosmos.o: cosmos.cpp cosmos.h object.h vector.h painter.h config.h \
 mathlib.h body.h blackhole.h
	gcc -c $(FLAGS) $< 

interface.o: interface.cpp interface.h painter.h cosmos.h object.h \
 vector.h config.h
	gcc -c $(FLAGS) $< 

mathlib.o: mathlib.cpp mathlib.h vector.h object.h cosmos.h painter.h \
 config.h
	gcc -c $(FLAGS) $< 

object.o: object.cpp object.h vector.h cosmos.h painter.h config.h	
	gcc -c $(FLAGS) $< 

painter.o: painter.cpp painter.h interface.h mathlib.h vector.h object.h \
 cosmos.h config.h body.h
	gcc -c $(FLAGS) $< 


clean:
	rm -f *.o
	rm -f $(OUT)
