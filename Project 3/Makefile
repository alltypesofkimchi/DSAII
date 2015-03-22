dijkstra.exe: dijkstra.o hash.o heap.o graph.o
	g++ -o dijkstra.exe hash.o heap.o dijkstra.o graph.o

dijkstra.o: dijkstra.cpp
	g++ -c dijkstra.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp