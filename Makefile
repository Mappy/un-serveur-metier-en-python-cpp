main: main.o haversine.o
	g++ -o main haversine.o main.o

haversine.o: haversine.cpp
	g++ -o haversine.o -c haversine.cpp 

main_next.o: main.cpp
	g++ -o main.o -c main.cpp -g -Wall

main.o: main.cpp
	g++ -o main.o -c main.cpp -g -Wall

clean:
	rm -rf *.o
