#include "huffmanNode.hpp"

#include <list>

class huffmanTree {
private:
    huffmanNode * root;
public:
    huffmanTree();
    huffmanTree(huffmanNode * node);

    huffmanNode * getRoot();
    void setRoot(huffmanNode * node);

    void insert(huffmanNode * node);

    std::list<huffmanNode> preOrder();
    std::list<huffmanNode> inOrder();
    std::list<huffmanNode> postOrder();

    void preOrder(huffmanNode * node, std::list<huffmanNode> * list);
    void inOrder(huffmanNode * node, std::list<huffmanNode> * list);
    void postOrder(huffmanNode * node, std::list<huffmanNode> * list);

    int height();
    int height(huffmanNode * node, int temp_height);
};
