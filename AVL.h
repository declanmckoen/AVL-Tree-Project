#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#pragma once
using namespace std;


class AVL {
private:
    struct Node {
        string gatorID;
        string name;
        int height;
        int balanceFactor;
        Node* left;
        Node* right;
        Node();
        Node(const Node& og);
        Node(string name, string gatorID);
    };

    Node* root;
    int numNodes;

    void destructorHelper(Node* &currentNode);
    void copyHelper(Node* &currentNode, Node* ogNode);
    Node* insertHelper(Node* currentNode, string name, string gatorID, bool& successful);
    Node* removeHelper(Node* currentNode, string gatorID, bool& deleted);
    void removeInorderHelper(Node* currentNode, int n, int& index);
    Node* findLeftMostNode(AVL::Node* &currentNode);
    Node* findRightMostNode(Node* &currentNode);
    string searchIDHelper(Node* currentNode, string gatorID, bool& found);
    void searchNameHelper(Node* currentNode, string name, vector<string>& IDs);
    int calculateHeight(Node* currentNode);
    void printInorderHelper(Node* currentNode, vector<string>& vec);
    void printPreorderHelper(Node* currentNode, vector<string>& vec);
    void printPostorderHelper(Node* currentNode, vector<string>& vec);

public:
    AVL();
    ~AVL();
    AVL(const AVL& og);
    AVL& operator=(const AVL& og);

    void insert(string name, string gatorID);
    bool remove(string gatorID, bool print = true);
    void removeInorder(int n);
    string searchID(string gatorID);
    vector<string> searchName(string name);
    void printLevelCount();
    vector<string> printInorder();
    vector<string> printPreorder();
    vector<string> printPostorder();

    Node* rotateLeft(Node* currentNode);
    Node* rotateRight(Node* currentNode);
};
