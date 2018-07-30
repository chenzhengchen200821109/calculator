main: main.o commandParser.o parser.o scanner.o tree.o store.o symbolTable.o hashTable.o functionTable.o
	g++ main.o commandParser.o parser.o scanner.o tree.o store.o symbolTable.o hashTable.o functionTable.o -o main
main.o: main.cpp
	g++ -c main.cpp
commandParser.o: commandParser.h commandParser.cpp
	g++ -c commandParser.cpp
parser.o: parser.cpp parser.h
	g++ -c parser.cpp
scanner.o: scanner.cpp scanner.h
	g++ -c scanner.cpp
tree.o: tree.cpp tree.h
	g++ -c tree.cpp 
store.o: store.cpp store.h
	g++ -c store.cpp
symbolTable.o: symbolTable.cpp symbolTable.h serialize.h
	g++ -c symbolTable.cpp 
functionTable.o: functionTable.cpp functionTable.h
	g++ -c functionTable.cpp
hashTable.o: hashTable.cpp hashTable.h list.h
	g++ -c hashTable.cpp
clean:
	rm -rf main parser.o tree.o store.o symbolTable.o hashTable.o functionTable.o calculator.o commandParser.o main.o scanner.o 
