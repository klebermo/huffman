#include "huffmanTree.hpp"

#include <map>
#include <string>
#include <fstream>
#include <bitset>
#include <algorithm>

void getCode(std::map<char,std::string> * table, huffmanNode * node, std::string code = "") {
  if(node->getLeft() == nullptr && node->getRight() == nullptr) {
    table->insert({node->getData(), code});
  } else {
    if(node->getLeft() != nullptr)
      getCode(table, node->getLeft(), code+"0");
    if(node->getRight() != nullptr)
      getCode(table, node->getRight(), code+"1");
  }
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

  if(input.is_open()) {
    char c;
    while(input.get(c)) {
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
    z->setData(0x0);
    z->setFrequency(left->getFrequency() + right->getFrequency());
    z->setLeft(left);
    z->setRight(right);

    priorityQueue.push_back(*z);
  }

  toEncode.setRoot(&priorityQueue.front());
  getCode(&encodeTable, toEncode.getRoot());

  if (output.is_open()) {
    std::list<huffmanNode> pre = toEncode.preOrder();
    std::vector<huffmanNode> pre_vector(pre.begin(), pre.end());

    std::vector<huffmanNode>::size_type size = 0;
    for(std::vector<huffmanNode>::size_type i=0; i<pre.size(); i++)
      if(pre_vector[i].getLeft() == nullptr && pre_vector[i].getRight() == nullptr) size++;

    output.write(reinterpret_cast<char*>(&size), sizeof(size));

    for(std::vector<huffmanNode>::size_type i=0; i<pre.size(); i++) {
      if(pre_vector[i].getLeft() == nullptr && pre_vector[i].getRight() == nullptr) {
        char c = pre_vector[i].getData();
        output.write(&c, sizeof(c));
        int f = pre_vector[i].getFrequency();
        output.write(reinterpret_cast<char*>(&f), sizeof(f));
      }
    }

    input.clear();
    input.seekg(0, std::ios::beg);

    std::string encoded_string = "";
    char c;
    while(input.get(c)) {
      std::string code = encodeTable[c];
      encoded_string = encoded_string + code;
    }

    for(long unsigned int i=0; i<encoded_string.size();) {
      std::string sub;
      if(i + 8 > encoded_string.size()) {
        long unsigned int j = 0;
        for(j=i; j<encoded_string.size(); j++) {
          sub = sub + encoded_string[j];
        }
        i = i + j;
      } else {
        sub = encoded_string.substr(i, 8);
        i = i + 8;
      }

      std::bitset<8> bits(sub);
      unsigned long x = bits.to_ulong();
      unsigned char c = static_cast<unsigned char>(x);
      output.write(reinterpret_cast<char*>(&c), sizeof(c));
    }
  }

  input.close();
  output.close();
}

void decode(std::string input_file, std::string output_file) {
  std::list<huffmanNode> priorityQueue;
  huffmanTree toDecode;
  std::map<char, std::string> decodeTable;

  std::ifstream input(input_file, std::ios_base::in | std::ios_base::binary);
  std::ofstream output(output_file, std::ios_base::out);

  std::string encoded_string;
  if (input.is_open()) {
    std::vector<huffmanNode>::size_type size;
    input.read(reinterpret_cast<char*>(&size), sizeof(size));

    for(std::vector<huffmanNode>::size_type i=0; i<size; i++) {
      char c;
      input.read(&c, sizeof(c));
      int f;
      input.read(reinterpret_cast<char*>(&f), sizeof(f));

      huffmanNode node(c, f);
      priorityQueue.push_back(node);
    }

    char c;
    while(input.read(reinterpret_cast<char*>(&c), sizeof(c))) {
      std::bitset<8> bits(c);
      encoded_string = encoded_string + bits.to_string();
    }
  }

  priorityQueue.sort();

  while(priorityQueue.size() > 1) {
    huffmanNode * left = new huffmanNode(priorityQueue.front());
    priorityQueue.pop_front();

    huffmanNode * right = new huffmanNode(priorityQueue.front());
    priorityQueue.pop_front();

    huffmanNode * z = new huffmanNode();
    z->setData(0x0);
    z->setFrequency(left->getFrequency() + right->getFrequency());
    z->setLeft(left);
    z->setRight(right);

    priorityQueue.push_back(*z);
  }

  toDecode.setRoot(&priorityQueue.front());
  getCode(&decodeTable, toDecode.getRoot());

  if(output.is_open()) {
    std::string decoded_string;

    long unsigned int max = encoded_string.size();
    for(long unsigned int i=0; i<max; i++) {
      for(auto it = decodeTable.begin(); it != decodeTable.end(); it++) {
        std::string code = it->second;
        std::string temp = encoded_string.substr(0, code.length());

        if(temp.compare(code) == 0) {
          decoded_string = decoded_string + it->first;
          encoded_string.erase(0, code.length());
        }
      }
    }

    output << decoded_string;
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
