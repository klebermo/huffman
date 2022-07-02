#include "huffmanTree.hpp"

huffmanTree::huffmanTree() {
    this->root = nullptr;
}

huffmanTree::huffmanTree(huffmanNode * node) {
    this->root = node;
}

huffmanNode * huffmanTree::getRoot() {
    return root;
}

void huffmanTree::setRoot(huffmanNode * node) {
    root = node;
}

void huffmanTree::insert(huffmanNode * node) {
    if(root == nullptr) {
        root = new huffmanNode(*node);
        return;
    }

    huffmanNode * aux = root;
    huffmanNode * auxParent = nullptr;
    while(aux != nullptr) {
        auxParent = aux;
        if(node < aux)
        aux = aux->getLeft();
        else
        aux = aux->getRight();
    }

    aux = new huffmanNode(*node);
    if(aux < auxParent)
        auxParent->setLeft(aux);
    else
        auxParent->setRight(aux);
}

std::list<huffmanNode> huffmanTree::preOrder() {
    std::list<huffmanNode> list;
    if(root != nullptr) {
        list.insert(list.end(), *root);
        preOrder(root->getLeft(), &list);
        preOrder(root->getRight(), &list);
    }
    return list;
}

void huffmanTree::preOrder(huffmanNode * node, std::list<huffmanNode> * list) {
    if(node != nullptr) {
        list->insert(list->end(), *node);
        preOrder(node->getLeft(), list);
        preOrder(node->getRight(), list);
    }
}

std::list<huffmanNode> huffmanTree::inOrder() {
    std::list<huffmanNode> list;
    if(root != nullptr) {
        inOrder(root->getLeft(), &list);
        list.insert(list.end(), *root);
        inOrder(root->getRight(), &list);
    }
    return list;
}

void huffmanTree::inOrder(huffmanNode * node, std::list<huffmanNode> * list) {
    if(node != nullptr) {
        inOrder(node->getLeft(), list);
        list->insert(list->end(), *node);
        inOrder(node->getRight(), list);
    }
}

std::list<huffmanNode> huffmanTree::postOrder() {
    std::list<huffmanNode> list;
    if(root != nullptr) {
        postOrder(root->getLeft(), &list);
        postOrder(root->getRight(), &list);
        list.insert(list.end(), *root);
    }
    return list;
}

void huffmanTree::postOrder(huffmanNode * node, std::list<huffmanNode> * list) {
    if(node != nullptr) {
        postOrder(node->getLeft(), list);
        postOrder(node->getRight(), list);
        list->insert(list->end(), *node);
    }
}

int huffmanTree::height() {
    if(root == nullptr)
        return 0;

    int left_height = height(root->getLeft(), 1);
    int right_height = height(root->getRight(), 1);

    if(left_height > right_height)
        return left_height;
    else
        return right_height;
}

int huffmanTree::height(huffmanNode * node, int temp_height) {
    if(node == nullptr)
        return temp_height;

    int left_height = height(node->getLeft(), temp_height+1);
    int right_height = height(node->getRight(), temp_height+1);

    if(left_height > right_height)
        return left_height;
    else
        return right_height;
}
