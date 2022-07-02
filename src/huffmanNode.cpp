#include "huffmanNode.hpp"

huffmanNode::huffmanNode() {
    data = 0x0;
    frequency = 0;
    left = nullptr;
    right = nullptr;
}

huffmanNode::huffmanNode(char data, int frequency) {
    this->data = data;
    this->frequency = frequency;
    left = nullptr;
    right = nullptr;
}

huffmanNode::huffmanNode(char data) {
    this->data = data;
    this->frequency = 0;
    left = nullptr;
    right = nullptr;
}

huffmanNode::huffmanNode(const huffmanNode &node) {
    data = node.data;
    frequency = node.frequency;
    left = node.left;
    right = node.right;
}

char huffmanNode::getData() {
    return data;
}

void huffmanNode::setData(char value) {
    data = value;
}

int huffmanNode::getFrequency() {
    return frequency;
}

void huffmanNode::setFrequency(int value) {
    frequency = value;
}

huffmanNode * huffmanNode::getLeft() {
    return left;
}

void huffmanNode::setLeft(huffmanNode * node) {
    this->left = node;
}

huffmanNode * huffmanNode::getRight() {
    return right;
}

void huffmanNode::setRight(huffmanNode * node) {
    this->right = node;
}
