#include <iostream>
#include <string>
#include <sstream>
#include "AVL.h"
using namespace std;


string VerifyNextWord(istringstream& in);

int main() {
    // Instantiating the AVL tree
    AVL tree;

    // Getting the number of commands from cin
	string numCommands;
    cin >> numCommands;
    int num = stoi(numCommands);

    // Looping through each command
    string currentLine;
    cin.ignore();
    for (int i = 0; i < num; ++i) {
        getline(cin, currentLine);

        // Making the current command a string so I can extract each word individually
        istringstream stream(currentLine);

        string word = VerifyNextWord(stream);
        if (word.length() > 0) {
            // Insert command
            if (word == "insert") {
                // Extracting the name from the command

                string name;
                stream.ignore(1, '\n');
                stream.ignore(1, '\"');
                getline(stream, name, '\"');

                if (name.length() == 0) {
                    cout << "unsuccessful" << endl;
                    continue;
                }

                // Extracting the ID from the command
                string gatorID = VerifyNextWord(stream);

                if (gatorID.length() == 0 || gatorID.length() != 8) {
                    cout << "unsuccessful" << endl;
                    continue;
                }

                tree.insert(name, gatorID);
            }

            // Remove command
            else if (word == "remove") {
                // Extracting the item to be removed
                string gatorID = VerifyNextWord(stream);

                if (gatorID.length() == 0 || gatorID.length() != 8) {
                    cout << "unsuccessful" << endl;
                    continue;
                }

                tree.remove(gatorID);
            }

            // search command
            else if (word == "search") {
                string toBeSearchedFor = VerifyNextWord(stream);

                // If argument is invalid -> continue to next command
                if (toBeSearchedFor.length() == 0) {
                    cout << "unsuccessful" << endl;
                    continue;
                }

                // searchID
                try {
                    stoi(toBeSearchedFor);
                    if (toBeSearchedFor.length() != 8) {
                        cout << "unsuccessful" << endl;
                        continue;
                    }
                    tree.searchID(toBeSearchedFor);
                }

                // searchName
                catch (invalid_argument& e) {
                    string lastName = VerifyNextWord(stream);
                    if (lastName.length() == 0) {
                        toBeSearchedFor = toBeSearchedFor.substr(1, toBeSearchedFor.length()-2);
                    }
                    else {
                        toBeSearchedFor += " " + lastName;
                        toBeSearchedFor = toBeSearchedFor.substr(1, toBeSearchedFor.length()-2);
                    }
                    tree.searchName(toBeSearchedFor);
                }
            }

            // Print inorder command
            else if (word == "printInorder") {
                tree.printInorder();
            }

            // Print preorder command
            else if (word == "printPreorder") {
                tree.printPreorder();
            }

            // Print postorder command
            else if (word == "printPostorder") {
                tree.printPostorder();
            }

            // Print level count command
            else if (word == "printLevelCount") {
                tree.printLevelCount();
            }

            // Remove inorder command
            else if (word == "removeInorder") {
                // Extracting index to be removed
                string index = VerifyNextWord(stream);

                if (index.length() == 0) {
                    cout << "unsuccessful" << endl;
                    continue;
                }

                int N = stoi(index);
                tree.removeInorder(N);
            }

            else {
                cout << "unsuccessful" << endl;
            }
        }
        else {
            cout << "unsuccessful" << endl;
        }
    }
}

string VerifyNextWord(istringstream& in) {
    string word;
    in >> word;

    for (char c : word) {
        if (!isalnum(c) && c != 34)
            return "";
    }
    return word;
}
