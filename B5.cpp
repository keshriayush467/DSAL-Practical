#include <iostream>
#include <string>
using namespace std;

class Node 
{
public:
    string name;
    Node* first;
    Node* sibling;

    Node(string s) 
    {
        name = s;
        first = NULL;
        sibling = NULL;
    }

    void create(Node* root, Node* child) {
        if (root == NULL) {
            // This branch is unused; root should never be NULL when calling create
            return;
        }
        if (root->first == NULL) 
        {
            root->first = child;
        } else 
        {
            Node* sib = root->first;
            while (sib->sibling != NULL) {
                sib = sib->sibling;
            }
            sib->sibling = child;
        }
    }

    void display(Node* root, int level = 0) {
        if (root == NULL) return;

        for (int i = 0; i < level; i++) cout << "  ";  
        cout << "- " << root->name << endl;

        display(root->first, level + 1);   // Visit child nodes
        display(root->sibling, level);     // Visit siblings
    }

    void addChapter(Node* root) {
        string chapname;
        cout << "\nEnter the chapter name: ";
        getline(cin, chapname);
        Node* chapter = new Node(chapname);
        create(root, chapter);

        int sectionChoice;
        cout << "Do you want to add sections to '" << chapname << "'? (1 = Yes, 0 = No): ";
        cin >> sectionChoice;

        while (sectionChoice == 1) {
            addSection(chapter);
            cout << "Do you want to add another section to '" << chapname << "'? (1 = Yes, 0 = No): ";
            cin >> sectionChoice;
        }
    }

    void addSection(Node* root) {
        cin.ignore();
        string secname;
        cout << "\nEnter the section name: ";
        getline(cin, secname);
        Node* section = new Node(secname);
        create(root, section);

        int subsecChoice;
        cout << "Do you want to add subsections to '" << secname << "'? (1 = Yes, 0 = No): ";
        cin >> subsecChoice;

        while (subsecChoice == 1) {
            addSubsection(section);
            cout << "Do you want to add another subsection to '" << secname << "'? (1 = Yes, 0 = No): ";
            cin >> subsecChoice;
        }
    }

    void addSubsection(Node* root) {
        cin.ignore();
        string subsecname;
        cout << "\nEnter the subsection name: ";
        getline(cin, subsecname);
        Node* subsection = new Node(subsecname);
        create(root, subsection);
    }
};

int main() {
    Node* book = new Node("Book");

    int chapChoice;
    do {
        book->addChapter(book);
        cout << "Do you want to add another chapter? (1 = Yes, 0 = No): ";
        cin >> chapChoice;
    } while (chapChoice == 1);

    cout << "\nBook Structure:\n";
    book->display(book);

    return 0;
}
