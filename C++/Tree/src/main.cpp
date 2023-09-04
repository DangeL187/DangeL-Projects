#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <memory>
#include "split.h"

class Node {
public:
    int key;
    int value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    int height = 0;

    Node(int key_, int value_) {
        key = key_;
        value = value_;
        left = NULL;
        right = NULL;
    }
    bool isNull() {
        if (this == NULL) {
            return true;
        }
        else {
            return false;
        }
    }
};

int getHeight(std::shared_ptr<Node> node) {
    if (node->isNull()) {
        return -1;
    } else {
        return node->height;
    }
}

void updateHeight(std::shared_ptr<Node>& node) {
    auto a = getHeight(node->left);
    auto b = getHeight(node->right);
    if (a > b) {
        node->height = a + 1;
    } else {
        node->height = b + 1;
    }
}


void swap(std::shared_ptr<Node>& node_a, std::shared_ptr<Node>& node_b) {
    auto node_a_key = node_a->key;
    node_a->key = node_b->key;
    node_b->key = node_a_key;
    auto node_a_value = node_a->value;
    node_a->value = node_b->value;
    node_b->value = node_a_value;
}


void rightRotate(std::shared_ptr<Node>& node) {
    swap(node, node->left);
    auto buffer = node->right;
    node->right = node->left;
    node->left = node->right->left;
    node->right->left = node->right->right;
    node->right->right = buffer;
    updateHeight(node->right);
    updateHeight(node);
}

void leftRotate(std::shared_ptr<Node>& node) {
    swap(node, node->right);
    auto buffer = node->left;
    node->left = node->right;
    node->right = node->left->right;
    node->right->left = node->right->right;
    node->left->right = node->left->left;
    node->left->left = buffer;
    updateHeight(node->left);
    updateHeight(node);
}

int getBalance(std::shared_ptr<Node> node) {
    if (node->isNull()) {
        return 0;
    } else {
        return getHeight(node->right) - getHeight(node->left);
    }
}

void balance(std::shared_ptr<Node>& node) {
    auto get_balance = getBalance(node);
    if (get_balance == -2) {
        if (getBalance(node->left) == 1) {
            leftRotate(node->left);
        }
        rightRotate(node);
    }
    else if (get_balance == 2) {
        if (getBalance(node->right) == -1) {
            rightRotate(node->right);
        }
        leftRotate(node);
    }
}


void insert(std::shared_ptr<Node> node, int key, int value) {
    if (key < node->key) {
        if (node->left == NULL) {
            node->left = std::make_shared<Node>(key, value);
        }
        else {
            insert(node->left, key, value);
        }
    }
    else if (key >= node->key) {
        if (node->right == NULL) {
            node->right = std::make_shared<Node>(key, value);
        }
        else {
            insert(node->right, key, value);
        }
    }

    updateHeight(node);
    balance(node);
}


std::shared_ptr<Node> search(std::shared_ptr<Node> node, int key) {
    if (node->isNull()) {
        return NULL;
    }
    if (node->key == key) {
        return node;
    }
    if (key < node->key) {
        return search(node->left, key);
    }
    else {
        return search(node->right, key);
    }
}


std::shared_ptr<Node> getMin(std::shared_ptr<Node> node) {
    if (node->isNull()) {
        return NULL;
    }
    if (node->left->isNull()) {
        return node;
    }
    return getMin(node->left);
}

std::shared_ptr<Node> getMax(std::shared_ptr<Node> node) {
    if (node->isNull()) {
        return NULL;
    }
    if (node->right->isNull()) {
        return node;
    }
    return getMax(node->right);
}


void remove(std::shared_ptr<Node>& node, int key) {
    if (node->isNull()) {
        return NULL;
    }
    else if (key < node->key) {
        remove(node->left, key);
    }
    else if (key > node->key) {
        remove(node->right, key);
    }
    else {
        if (node->left->isNull() || node->right->isNull()) {
            if (node->left->isNull()) {
                node = node->right;
            }
            else {
                node = node->left;
            }
        }
        else {
            auto max_in_left = getMax(node->left);
            node->key = max_in_left->key;
            node->value = max_in_left->value;
            remove(node->right, max_in_left->key);
            remove(node->left, max_in_left->key);
        }
    }
    if (!node->isNull()) {
        updateHeight(node);
        balance(node);
    }
}


void symmetricalTree(std::shared_ptr<Node> node) {
    if (node->isNull()) {
        return;
    }
    symmetricalTree(node->left);
    std::cout << node->value << std::endl;
    symmetricalTree(node->right);
}

void reverseTree(std::shared_ptr<Node> node) {
    if (node->isNull()) {
        return;
    }
    reverseTree(node->left);
    reverseTree(node->right);
    std::cout << node->value << std::endl;
}

void straightTree(std::shared_ptr<Node> node) {
    if (node->isNull()) {
        return;
    }
    std::cout << node->value << std::endl;
    straightTree(node->left);
    straightTree(node->right);
}


void searchWrap(std::shared_ptr<Node>& node, int key) {
    auto out = search(node, key);
    if (out != NULL) {
        std::cout << out->value << std::endl;
    }
    else {
        std::cout << "No such element!\n";
    }
}


int main() {
    Node tree(7, 77);

    std::shared_ptr<Node> p_tree;
    p_tree = std::make_shared<Node>(tree);

    insert(p_tree, 5, 55);
    insert(p_tree, 8, 88);
    insert(p_tree, 4, 44);
    insert(p_tree, 6, 66);

    //remove(p_tree, 3);

    //symmetricalTree(p_tree);
    //reverseTree(p_tree);
    //straightTree(p_tree);

    //std::cout << getMin(p_tree)->value << std::endl;
    //std::cout << getMax(p_tree)->value << std::endl;

    //searchWrap(p_tree, 5);

    return 0;
}
