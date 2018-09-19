game: main.o functions.o
	g++ main.o functions.o -o game

main.o: main.cpp graph.h
	g++ -c main.cpp

functions.o: functions.cpp graph.h
	g++ -c functions.cpp

clean:
	rm *.o game
