all: huffman

huffmanNode.o: src/huffmanNode.cpp
	g++ -Wall -g -c src/huffmanNode.cpp -o build/huffmanNode.o

huffmanTree.o: src/huffmanTree.cpp
	g++ -Wall -g -c src/huffmanTree.cpp -o build/huffmanTree.o

main.o: src/main.cpp
	g++ -Wall -g -c src/main.cpp -o build/main.o

huffman: huffmanNode.o huffmanTree.o main.o
	g++ -Wall -g -o huffman build/huffmanNode.o build/huffmanTree.o build/main.o

clean:
	rm build/*.o
	rm huffman
