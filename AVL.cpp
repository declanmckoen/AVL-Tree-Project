#include "AVL.h"
using namespace std;


// Tree node functions
AVL::Node::Node() {
    gatorID = "";
    name = "";
    height = 1;
    balanceFactor = 0;
    left = nullptr;
    right = nullptr;
}

AVL::Node::Node(const Node& og) {
    this->gatorID = og.gatorID;
    this->name = og.name;
    height = 1;
    balanceFactor = 0;
    this->left = og.left;
    this->right = og.right;
}

AVL::Node::Node(string name, string gatorID) {
    this->gatorID = gatorID;
    this->name = name;
    height = 1;
    balanceFactor = 0;
    left = nullptr;
    right = nullptr;
}


// General AVL tree functions
AVL::AVL() {
    root = nullptr;
    numNodes = 0;
}

AVL::~AVL() {
    destructorHelper(root);
    root = nullptr;
    numNodes = 0;
}

AVL::AVL(const AVL& og) {
    copyHelper(root, og.root);
}

AVL& AVL::operator=(const AVL& og) {
    destructorHelper(root);
    root = nullptr;
    numNodes = 0;
    copyHelper(root, og.root);
    return (*this);
}


// AVL tree insertion
void AVL::insert(string name, string gatorID) {
    bool successful = false;

    // Checking for valid name
    for (char c : name) {
        if (!isalpha(c)) {
            cout << "unsuccessful" << endl;
            return;
        }
    }

    // Checking for valid ID
    if (gatorID.length() != 8) {
        cout << "unsuccessful" << endl;
        return;
    }

    // If the tree is empty
    if (root == nullptr) {
        successful = true;
        root = new Node(name, gatorID);
    }
    else {
        insertHelper(root, name, gatorID, successful);
    }
    if (successful) {
        numNodes++;
        cout << "successful" << endl;
    }
    else
        cout << "unsuccessful" << endl;
}


// AVL tree node deletion
bool AVL::remove(string gatorID, bool print) {
    bool deleted = true;

    // Checking for valid ID
    if (gatorID.length() != 8) {
        cout << "unsuccessful" << endl;
        return !deleted;
    }
    removeHelper(root, gatorID, deleted);
    if (deleted && print) {
        numNodes--;
        cout << "successful" << endl;
    }
    else if (!deleted)
        cout << "unsuccessful" << endl;
    return deleted;
}


// AVL tree remove inorder N function
void AVL::removeInorder(int n) {
    int index = 0;

    // Checking for valid index
    if (n >= numNodes || n < 0) {
        cout << "unsuccessful" << endl;
        return;
    }
    if (numNodes == 1) {
        delete root;
        root = nullptr;
    }
    else
        removeInorderHelper(root, n, index);
    cout << "successful" << endl;
}


// AVL tree search ID function
string AVL::searchID(string gatorID) {
    bool found = false;

    // Checking for valid ID
    if (gatorID.length() != 8) {
        cout << "unsuccessful" << endl;
        return "";
    }
    string name = searchIDHelper(root, gatorID, found);
    if (found) {
        cout << name << endl;
    }
    else {
        cout << "unsuccessful" << endl;
    }
    return name;
}


// AVL tree search name function
vector<string> AVL::searchName(std::string name) {
    vector<string> IDs;

    // Checking for valid name
    for (char c : name) {
        if (!isalpha(c)) {
            cout << "unsuccessful" << endl;
            return IDs;
        }
    }

    searchNameHelper(root, name, IDs);
    if (IDs.size() > 0) {
        for (string ID : IDs)
            cout << ID << endl;
    }
    else {
        cout << "unsuccessful" << endl;
    }
    return IDs;
}


// AVL tree level count
void AVL::printLevelCount() {
    int height = calculateHeight(root);
    cout << height << endl;
}


// Print tree functions
vector<string> AVL::printInorder() {
    // Creating a vector to store names for testing purposes and to print them out
    vector<string> res;
    printInorderHelper(root, res);
    if (res.size() > 0) {
        for (int i = 0; i < res.size()-1; ++i)
            cout << res[i] << ", ";
        cout << res[res.size()-1] << endl;
    }
    return res;
}

vector<string> AVL::printPreorder() {
    // Creating a vector to store names for testing purposes and to print them out
    vector<string> res;
    printPreorderHelper(root, res);
    if (res.size() > 0) {
        for (int i = 0; i < res.size()-1; ++i)
            cout << res[i] << ", ";
        cout << res[res.size()-1] << endl;
    }
    return res;
}

vector<string> AVL::printPostorder() {
    // Creating a vector to store names for testing purposes and to print them out
    vector<string> res;
    printPostorderHelper(root, res);
    if (res.size() > 0) {
        for (int i = 0; i < res.size()-1; ++i)
            cout << res[i] << ", ";
        cout << res[res.size()-1] << endl;
    }
    return res;
}


//Rotation functions
AVL::Node* AVL::rotateLeft(AVL::Node* currentNode) {
    Node* grandchild = currentNode->right->left;
    Node* newParent = currentNode->right;
    newParent->left = currentNode;
    currentNode->right = grandchild;
    return newParent;
}

AVL::Node* AVL::rotateRight(AVL::Node* currentNode) {
    Node* grandchild = currentNode->left->right;
    Node* newParent = currentNode->left;
    newParent->right = currentNode;
    currentNode->left = grandchild;
    return newParent;
}


// Helper Functions
// Destructor uses postorder traversal
void AVL::destructorHelper(AVL::Node* &currentNode) {
    if (currentNode == nullptr)
        return;
    destructorHelper(currentNode->left);
    destructorHelper(currentNode->right);
    delete currentNode;
}

// Copy constructor and copy assignment operator both use preorder traversal
void AVL::copyHelper(AVL::Node* &currentNode, Node* ogNode) {
    if (ogNode == nullptr)
        return;
    if (currentNode == nullptr)
        currentNode = new Node(ogNode->name, ogNode->gatorID);
    currentNode->gatorID = ogNode->gatorID;
    currentNode->name = ogNode->name;
    currentNode->height = ogNode->height;
    currentNode->balanceFactor = ogNode->balanceFactor;
    if (ogNode->left != nullptr)
        currentNode->left = new Node();
    if (ogNode->right != nullptr)
        currentNode->right = new Node();
    copyHelper(currentNode->left, ogNode->left);
    copyHelper(currentNode->right, ogNode->right);
}

AVL::Node* AVL::insertHelper(AVL::Node* currentNode, std::string name, string gatorID, bool& successful) {
    if (currentNode == nullptr) {
        successful = true;
        return new Node(name, gatorID);
    }
    if (gatorID < currentNode->gatorID)
        currentNode->left = insertHelper(currentNode->left, name, gatorID, successful);
    else if (gatorID > currentNode->gatorID)
        currentNode->right = insertHelper(currentNode->right, name, gatorID, successful);
    else
        return currentNode;

    // Increment height
    currentNode->height = calculateHeight(currentNode);

    // Calculate balanceFactor
    //currentNode->balanceFactor = calculateHeight(currentNode->left) - calculateHeight(currentNode->right);
    int heightLeft, heightRight;
    if (currentNode->left != nullptr) heightLeft = currentNode->left->height;
    else heightLeft = 0;
    if (currentNode->right != nullptr) heightRight = currentNode->right->height;
    else heightRight = 0;
    currentNode->balanceFactor = heightLeft - heightRight;

    // Rotate if absolute value of balanceFactor is greater than 2 (unbalanced)
    if (abs(currentNode->balanceFactor) >= 2) {

        // If currentNode is right heavy
        if (currentNode->balanceFactor <= -2) {

            // Right Right alignment
            if (currentNode->right->balanceFactor < 0) {
                if (currentNode == root) {
                    root = rotateLeft(root);
                    currentNode = root;
                }
                else
                    currentNode = rotateLeft(currentNode);
                currentNode->height = calculateHeight(currentNode);
                currentNode->left->height = calculateHeight(currentNode->left);
                currentNode->right->height = calculateHeight(currentNode->right);
            }

                // Right Left alignment
            else {
                if (currentNode == root) {
                    root->right = rotateRight(root->right);
                    root = rotateLeft(root);
                    currentNode = root;
                }
                else {
                    currentNode->right = rotateRight(currentNode->right);
                    currentNode = rotateLeft(currentNode);
                }
                currentNode->height = calculateHeight(currentNode);
                currentNode->left->height = calculateHeight(currentNode->left);
                currentNode->right->height = calculateHeight(currentNode->right);
            }
        }

        //If currentNode is left heavy
        if (currentNode->balanceFactor >= 2) {

            // Left Left alignment
            if (currentNode->left->balanceFactor > 0) {
                if (currentNode == root) {
                    root = rotateRight(root);
                    currentNode = root;
                }
                else
                    currentNode = rotateRight(currentNode);
                currentNode->height = calculateHeight(currentNode);
                currentNode->left->height = calculateHeight(currentNode->left);
                currentNode->right->height = calculateHeight(currentNode->right);
            }

                // Left Right alignment
            else {
                if (currentNode == root) {
                    root->left = rotateLeft(root->left);
                    root = rotateRight(root);
                    currentNode = root;
                }
                else {
                    currentNode->left = rotateLeft(currentNode->left);
                    currentNode = rotateRight(currentNode);
                }
                currentNode->height = calculateHeight(currentNode);
                currentNode->left->height = calculateHeight(currentNode->left);
                currentNode->right->height = calculateHeight(currentNode->right);
            }
        }
    }

    return currentNode;
}

AVL::Node* AVL::removeHelper(AVL::Node* currentNode, string gatorID, bool& deleted) {
    // gatorID is not in the tree -> set deleted flag to false and return null
    if (currentNode == nullptr) {
        deleted = false;
        return nullptr;
    }

    // Compare currentNode->gatorID with gatorID
    if (gatorID < currentNode->gatorID)
        currentNode->left = removeHelper(currentNode->left, gatorID, deleted);
    else if (gatorID > currentNode->gatorID)
        currentNode->right = removeHelper(currentNode->right, gatorID, deleted);
    else {
        // If currentNode has no children
        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            delete currentNode;
            return nullptr;
        }

            // If currentNode has one child
        else if ((currentNode->left != nullptr && currentNode->right == nullptr) || (currentNode->left == nullptr && currentNode->right != nullptr)) {
            // If currentNode has a left child
            if (currentNode->left != nullptr) {
                if (currentNode == root) {
                    Node* temp = currentNode->left;
                    delete currentNode;
                    root = temp;
                    return temp;
                }
                else {
                    Node* temp = currentNode->left;
                    delete currentNode;
                    return temp;
                }
            }
            // If currentNode has a right child
            if (currentNode->right != nullptr) {
                if (currentNode == root) {
                    Node* temp = currentNode->right;
                    delete currentNode;
                    root = temp;
                    return temp;
                }
                else {
                    Node* temp = currentNode->right;
                    delete currentNode;
                    return temp;
                }
            }
        }

            // If currentNode has two children -> find inorder successor
        else {
            // Right subtree has no left children
            if (currentNode->right->left == nullptr) {
                Node* temp = currentNode->right;
                temp->left = currentNode->left;
                if (currentNode == root)
                    root = temp;
                delete currentNode;
                return temp;
            }

                // Right subtree has left children -> call helper recursive function to find leftmost child
            else {
                Node* inorderSuccessor = findLeftMostNode(currentNode->right);
                Node* temp = currentNode->right;
                while (temp->left != inorderSuccessor)
                    temp = temp->left;
                temp->left = inorderSuccessor->right;
                inorderSuccessor->left = currentNode->left;
                inorderSuccessor->right = currentNode->right;
                if (currentNode == root)
                    root = inorderSuccessor;
                delete currentNode;
                return inorderSuccessor;
            }
        }
    }
    return currentNode;
}

void AVL::removeInorderHelper(AVL::Node* currentNode, int n, int& index) {
    // Index is passed by reference to keep track of current position
    if (currentNode == nullptr)
        return;
    removeInorderHelper(currentNode->left, n, index);
    if (index == n) {
        remove(currentNode->gatorID, false);
        index++;
        return;
    }
    index++;
    removeInorderHelper(currentNode->right, n, index);
}

AVL::Node* AVL::findLeftMostNode(AVL::Node* &currentNode) {
    if (currentNode->left == nullptr)
        return currentNode;
    return findLeftMostNode(currentNode->left);
}

AVL::Node* AVL::findRightMostNode(AVL::Node* &currentNode) {
    if (currentNode->right == nullptr)
        return currentNode;
    return findRightMostNode(currentNode->right);
}

string AVL::searchIDHelper(AVL::Node* currentNode, std::string gatorID, bool& found) {
    // found boolean is used to signal the caller function whether the ID was found or not
    // If ID is not in the tree
    if (currentNode == nullptr)
        return "";
    // If ID was found
    if (currentNode->gatorID == gatorID) {
        found = true;
        return currentNode->name;
    }
    if (gatorID < currentNode->gatorID)
        return searchIDHelper(currentNode->left, gatorID, found);
    else
        return searchIDHelper(currentNode->right, gatorID, found);
}

void AVL::searchNameHelper(AVL::Node* currentNode, std::string name, vector<std::string>& IDs) {
    // IDs vector is passed by reference to keep track of names found in tree
    // Names are in the same order as a preorder traversal
    if (currentNode == nullptr)
        return;
    if (currentNode->name == name)
        IDs.push_back(currentNode->gatorID);
    searchNameHelper(currentNode->left, name, IDs);
    searchNameHelper(currentNode->right, name, IDs);
}

int AVL::calculateHeight(AVL::Node* currentNode) {
    if (currentNode == nullptr)
        return 0;
    return max(1 + calculateHeight(currentNode->left), 1 + calculateHeight(currentNode->right));
}

void AVL::printInorderHelper(AVL::Node* currentNode, vector<string>& vec) {
    if (currentNode == nullptr)
        return;
    printInorderHelper(currentNode->left, vec);
    vec.push_back(currentNode->name);
    printInorderHelper(currentNode->right, vec);
}

void AVL::printPreorderHelper(AVL::Node* currentNode, vector<string>& vec) {
    if (currentNode == nullptr)
        return;
    vec.push_back(currentNode->name);
    printPreorderHelper(currentNode->left, vec);
    printPreorderHelper(currentNode->right, vec);
}

void AVL::printPostorderHelper(AVL::Node* currentNode, vector<string>& vec) {
    if (currentNode == nullptr)
        return;
    printPostorderHelper(currentNode->left, vec);
    printPostorderHelper(currentNode->right, vec);
    vec.push_back(currentNode->name);
}
