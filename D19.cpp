#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string keyword;
    string meaning;
    int height;
    Node* left;
    Node* right;

    Node(string k, string m) {
        keyword = k;
        meaning = m;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

class AVLTree {
private:
    Node* root;

    int height(Node* node) {
        if (node == NULL) return 0;
        return node->height;
    }

    int balanceFactor(Node* node) {
        if (node == NULL) return 0;
        return height(node->left) - height(node->right);
    }

   

    Node* rightRotate(Node* root) {
        Node* child = root->left;
        Node* childnode = child->right;

        child->right = root;
        root->left = childnode;

        root->height = max(height(root->left), height(root->right)) + 1;
        child->height = max(height(child->left), height(child->right)) + 1;

        return child;
    }

    Node* leftRotate(Node* root) {
        Node* child = root->right;
        Node* childnode = child->left;

        child->left = root;
        root->right = childnode;

        root->height = max(height(root->left), height(root->right)) + 1;
        child->height = max(height(child->left), height(child->right)) + 1;

        return child;
    }

    Node* insert(Node* node, string keyword, string meaning) {
        if (node == NULL) {
            Node* newNode = new Node(keyword, meaning);
            return newNode;
        }

        if (keyword < node->keyword) {
            node->left = insert(node->left, keyword, meaning);
        } else if (keyword > node->keyword) {
            node->right = insert(node->right, keyword, meaning);
        } else {
            cout << "Duplicate keyword not allowed.\n";
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;

        int balance = balanceFactor(node);

        if (balance > 1 && keyword < node->left->keyword) {
            return rightRotate(node);
        }

        if (balance < -1 && keyword > node->right->keyword) {
            return leftRotate(node);
        }

        if (balance > 1 && keyword > node->left->keyword) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && keyword < node->right->keyword) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minNode(Node* node) {
        Node* current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* node, string keyword) {
        if (node == NULL) return node;

        if (keyword < node->keyword) {
            node->left = deleteNode(node->left, keyword);
        } else if (keyword > node->keyword) {
            node->right = deleteNode(node->right, keyword);
        } else {
            if (node->left == NULL || node->right == NULL) {
                Node* temp = node->left != NULL ? node->left : node->right;

                if (temp == NULL) {
                    temp = node;
                    node = NULL;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = minNode(node->right);
                node->keyword = temp->keyword;
                node->meaning = temp->meaning;
                node->right = deleteNode(node->right, temp->keyword);
            }
        }

        if (node == NULL) return node;

        node->height = max(height(node->left), height(node->right)) + 1;

        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }

        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && balanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }

        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(Node* node) {
        if (node != NULL) {
            inorder(node->left);
            cout << "Keyword: " << node->keyword << ", Meaning: " << node->meaning << endl;
            inorder(node->right);
        }
    }

    void reverseInorder(Node* node) {
        if (node != NULL) {
            reverseInorder(node->right);
            cout << "Keyword: " << node->keyword << ", Meaning: " << node->meaning << endl;
            reverseInorder(node->left);
        }
    }

    bool search(Node* node, string keyword, int& comparisons) {
        if (node == NULL) return false;

        comparisons = comparisons + 1;

        if (keyword < node->keyword) {
            return search(node->left, keyword, comparisons);
        } else if (keyword > node->keyword) {
            return search(node->right, keyword, comparisons);
        } else {
            return true;
        }
    }

public:
    AVLTree() {
        root = NULL;
    }

    void add(string keyword, string meaning) {
        root = insert(root, keyword, meaning);
    }

    void remove(string keyword) {
        root = deleteNode(root, keyword);
    }

    void update(string keyword, string newMeaning) {
        root = deleteNode(root, keyword);
        root = insert(root, keyword, newMeaning);
    }

    void displayAscending() {
        inorder(root);
    }

    void displayDescending() {
        reverseInorder(root);
    }

    void find(string keyword) {
        int comparisons = 0;
        bool found = search(root, keyword, comparisons);
        if (found) {
            cout << "Keyword found. Comparisons made: " << comparisons << endl;
        } else {
            cout << "Keyword not found. Comparisons made: " << comparisons << endl;
        }
    }
};

int main() {
    AVLTree dictionary;
    int choice;
    string keyword, meaning;

    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Add new keyword\n";
        cout << "2. Delete keyword\n";
        cout << "3. Update keyword\n";
        cout << "4. Display dictionary (ascending order)\n";
        cout << "5. Display dictionary (descending order)\n";
        cout << "6. Search keyword\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> keyword;
                cin.ignore();
                cout << "Enter meaning: ";
                getline(cin, meaning);
                dictionary.add(keyword, meaning);
                break;

            case 2:
                cout << "Enter keyword to delete: ";
                cin >> keyword;
                dictionary.remove(keyword);
                break;

            case 3:
                cout << "Enter keyword to update: ";
                cin >> keyword;
                cin.ignore();
                cout << "Enter new meaning: ";
                getline(cin, meaning);
                dictionary.update(keyword, meaning);
                break;

            case 4:
                cout << "Dictionary in ascending order:\n";
                dictionary.displayAscending();
                break;

            case 5:
                cout << "Dictionary in descending order:\n";
                dictionary.displayDescending();
                break;

            case 6:
                cout << "Enter keyword to search: ";
                cin >> keyword;
                dictionary.find(keyword);
                break;

            case 7:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
