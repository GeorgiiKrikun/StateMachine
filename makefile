all: main
	./main


obj/state.o: src/state.cpp
	g++ -c -std=c++11 src/state.cpp -o obj/state.o

obj/StateMachine.o: src/StateMachine.cpp obj/state.o
	g++ -c -std=c++11 src/StateMachine.cpp -o obj/StateMachine.o

obj/main.o: main.cpp obj/state.o obj/StateMachine.o
	g++ -c -std=c++11 main.cpp -o obj/main.o

main: obj/main.o obj/state.o obj/StateMachine.o
	g++ -std=c++11 obj/main.o obj/state.o obj/StateMachine.o -o main

clean:
	rm obj/*
	rm main

