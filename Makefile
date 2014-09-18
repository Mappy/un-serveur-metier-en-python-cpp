main: main.o geo.o
	g++ -o main geo.o main.o

haversine.o: geo.cpp
	g++ -o geo.o -c geo.cpp 

main_next.o: main.cpp
	g++ -o main.o -c main.cpp -g -Wall

main.o: main.cpp
	g++ -o main.o -c main.cpp -g -Wall

clean:
	rm -rf *.o
