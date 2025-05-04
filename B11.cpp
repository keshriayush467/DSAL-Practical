#include<iostream>
#include<string>
using namespace std;

struct Node
{
    string keyword;
    string meaning;
    Node* left;
    Node *right;

    Node(string key, string val)
    {
        keyword = key;
        meaning = val;
        left = right =NULL;
    }
};

class Dictionary
{
    Node *root;
    public:

    Dictionary()
    {
        root= NULL;
    }

    Node *insert(Node*root, string key, string meaning)
    {
        if(root==NULL)
        {
          return new Node(key, meaning);
        }

        if(key< root->keyword)
        {
            root->left = insert(root->left, key, meaning);
        }
        else if(key>root->keyword)
        {
            root->left = insert(root->left, key, meaning);
        }
        else
        {
            cout<<"\nKeyword Already Exist ";

        }
        return root;
    }

    void insertfunc(string key ,string meaning)
    {
        root = insert(root,key ,meaning);
    }

    void displayAscending(Node *root)
    {
        if(root!=NULL)
        {
            displayAscending(root->left);
            cout<<"\n" << root->keyword <<" : " <<root->meaning ;
            displayAscending(root->right);
        }
    }

    void displayDecending(Node*root)
    {
        if(root!=NULL)
        {
            displayDecending(root->right);
            cout<<"\n" <<root->keyword <<" : " <<root->meaning ;
            displayDecending(root->left);
        }
    }

    Node* findMin(Node*root)
    {
        while(root->left!=NULL)
        {
            root = root->left;
        }
        return root;
    }

    Node* deleteNode(Node*root , string key)
    {
        if(!root)
        {
            return NULL ;
        }
        if(key<root->keyword)
        {
            root ->left = deleteNode(root->left , key );
        }
        else if(key > root->keyword)
        {
            root->right = deleteNode(root->right  ,key);

        }
        else
        {
            if(root->left==NULL || root->right==NULL)
            {
                delete root;
                return NULL;
            }
            else if(root->left!=NULL)
            {
                Node*temp = root->right;
                delete root;
                return temp;
            }
            else if(root->left)
            {
                Node *temp = root->left;
                delete root;
                return temp;
            }
            else
            {
                Node*temp = root->right;
                root->keyword = temp->keyword;
                root->right = deleteNode(root->right ,temp->keyword);
            }
        }
        return root;
    }

    Node *update(Node*root , string key, string new_meaning)
    {
        if(root==NULL)
        {
            return NULL;
        }
        if(key == root->keyword)
        {
            root->keyword = new_meaning;
        }
        else if(key< root->keyword)
        {
           return update(root->left, key, new_meaning);
        }
        else
        {
            return update(root->right,key,new_meaning);
        }
      
    }

    void updatefun(string key ,string new_meaning)
    {
        if(update(root, key ,new_meaning))
        {
            cout<<"\nMeaning Updated Succesfully ";
        }
    }

    void deletefunc(string key)
    {
        root = deleteNode(root, key);
    }

    void showAccending()
    {
        cout<<"\nAscending Order ";
         displayAscending(root);
    }

    void showDecending()
    {
        cout<<"\nDecending Order ";
        displayDecending(root);
    }

    int maxComparison(Node*root)
    {
        int left = maxComparison(root->left);
        int right = maxComparison(root->right);
        return 1 + max(left,right);
    }

    int getMax()
    {
        return maxComparison(root);
    }


};

int main()
{
    Dictionary D;
    string key ,meaning; 
    int ch;
    do
    {
       cout<<"\n1.Add Keyword and Meaning ";
       cout<<"\n2.Delete Keyword ";
       cout<<"\n3.Update Meaning ";
       cout<<"\n4. Display Ascending ";
       cout<<"\n5. Display Decending ";
       cout<<"\n6. Max Height ";
       cout<<"\n7. Exit ";
       cout<<"\nEnter your choice ";
       cin>>ch;


       switch(ch)
       {
        case 1:     cout<<"\nEnter the keyword ";
                   cin>>key;
                    cout<<"\nEnter the meaning ";
                    cin>>meaning;
                    D.insertfunc(key ,meaning);
                    break;

        case 2:     cout<<"\nEnter the keyword to be deleted ";
                    cin>>key;
                    D.deletefunc(key);
                    break;

        case 3:     cout<<"\nEnter the keyword to be updated ";
                    cin>>key;
                    cout<<"\nEnter the new Meaning ";
                    cin>>meaning;
                    D.updatefun(key, meaning);
                    break;

        case 4:     D.showAccending();
                    break;

        case 5:     D.showDecending();
                    break;

        case 6:     D.getMax();
                    break;

        case 7:     cout<<"\nExiting ";
       }
    } while (ch!=7);
    return 0;
}