#include "huffmanTree.hpp"

#include <map>
#include <string>
#include <fstream>
#include <bitset>
#include <algorithm>

void getCode(std::map<char,std::string> * table, huffmanNode * node, std::string code = "") {
  if(node->getLeft() == nullptr && node->getRight() == nullptr) {
    table->insert({node->getData(), code});
    return;
  }

  if(node->getLeft() != nullptr) getCode(table, node->getLeft(), code+"0");
  if(node->getRight() != nullptr) getCode(table, node->getRight(), code+"1");
}

std::string getSubstring(int length) {
  std::string result = "";
  for(int i=0; i<length; i++)
    result = result + "0";
  return result;
}

void encode(std::string input_file, std::string output_file) {
  std::list<huffmanNode> priorityQueue;
  huffmanTree toEncode;
  std::map<char, std::string> encodeTable;

  std::ifstream input(input_file, std::ios_base::in);
  std::ofstream output(output_file, std::ios_base::out | std::ios_base::binary);

  if (input.is_open()) {
    char c;
    while (input.get(c)) {
      huffmanNode node(c, 1);

      std::list<huffmanNode>::iterator pos = find(begin(priorityQueue), end(priorityQueue), node);
      if(pos != end(priorityQueue)) {
        (*pos)++;
      } else {
        priorityQueue.push_back(node);
      }
    }
  }

  priorityQueue.sort();

  while(priorityQueue.size() > 1) {
    huffmanNode * left = new huffmanNode(priorityQueue.front());
    priorityQueue.pop_front();

    huffmanNode * right = new huffmanNode(priorityQueue.front());
    priorityQueue.pop_front();

    huffmanNode * z = new huffmanNode();
    z->setFrequency(left->getFrequency() + right->getFrequency());
    z->setLeft(left);
    z->setRight(right);

    priorityQueue.push_back(*z);
  }

  if (output.is_open()) {
    //
  }

  input.close();
  output.close();
}

void decode(std::string input_file, std::string output_file) {
  std::list<huffmanNode> decodeList;
  huffmanTree toDecode;
  std::map<char, std::string> decodeTable;

  std::ifstream input(input_file, std::ios_base::in | std::ios_base::binary);
  std::ofstream output(output_file, std::ios_base::out);

  if (input.is_open()) {
    //
  }

  if(output.is_open()) {
    //
  }

  input.close();
  output.close();
}

int main(int argc, char ** argv) {
  if (argc < 4) {
    std::cout << "Usage: huffman (encode|decode) <input file> <output file>" << std::endl;
    return 0;
  }

  std::string action(argv[1]), input(argv[2]), output(argv[3]);

  if(action == "encode") encode(input, output);

  if(action == "decode") decode(input, output);

  return 0;
}
