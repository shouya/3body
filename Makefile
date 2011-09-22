CC=gcc
FLAGS= -Wall -lstdc++ 
OUT=3body

all: blackhole body cosmos interface mathlib object painter 3body
	gcc $(FLAGS) -o $(OUT) *.o


blackhole: blackhole.cpp blackhole.h
	gcc -c $(FLAGS) blackhole.cpp

body: body.cpp body.h
	gcc -c $(FLAGS) body.cpp

cosmos: cosmos.cpp cosmos.h
	gcc -c $(FLAGS) cosmos.cpp

interface: interface.cpp interface.h
	gcc -c $(FLAGS) interface.cpp

mathlib: mathlib.cpp mathlib.h
	gcc -c $(FLAGS) mathlib.cpp

object: object.cpp object.h
	gcc -c $(FLAGS) object.cpp

painter: painter.cpp painter.h
	gcc -c $(FLAGS) painter.cpp

3body: 3body.cpp 3body.h
	gcc -c $(FLAGS) 3body.cpp



clean:
	rm -f *.o
	rm -f $(OUT)
