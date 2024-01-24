test: main vec3
	g++ main.o vec3.o -o weekend
	rm -f *.o

main:
	g++ -c main.cpp -o main.o

vec3:
	g++ -c vec3.cpp -o vec3.o