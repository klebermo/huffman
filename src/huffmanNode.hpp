#include <iostream>

class huffmanNode {
private:
    char data;
    int frequency;
    huffmanNode * left;
    huffmanNode * right;
public:
    huffmanNode();
    huffmanNode(char data, int frequency);
    huffmanNode(char data);
    huffmanNode(const huffmanNode &node);

    char getData();
    void setData(char data);

    int getFrequency();
    void setFrequency(int frequency);

    huffmanNode * getLeft();
    void setLeft(huffmanNode * node);

    huffmanNode * getRight();
    void setRight(huffmanNode * node);

    bool operator==(huffmanNode other) { return this->data == other.data; }
    bool operator==(char data) { return this->data == data; }
    bool operator!=(huffmanNode other) { return this->data != other.data; }
    bool operator!=(char data) { return this->data != data; }

    bool operator<(huffmanNode other) { return frequency < other.frequency; }
    bool operator<=(huffmanNode other) { return frequency <= other.frequency; }
    bool operator>(huffmanNode other) { return frequency > other.frequency; }
    bool operator>=(huffmanNode other) { return frequency >= other.frequency; }

    huffmanNode operator++() { this->frequency++; return *this; }
    huffmanNode operator++(int) { this->frequency++; return *this; }
    huffmanNode operator--() { this->frequency--; return *this; }
    huffmanNode operator--(int) { this->frequency--; return *this; }

    friend std::ostream &operator<<( std::ostream &output, const huffmanNode &node ) { output << (node.data=='\n'? '#' : node.data) << " ( " << node.frequency << " ) "; return output; }
    friend std::istream &operator>>( std::istream  &input, huffmanNode &node ) { input >> node.data >> node.frequency; return input; }
};
