#include <iostream>
using namespace std;


struct Node
 {
    char data;
    Node* left;
    Node* right;
};


struct Stack 
{
    Node* arr[100];
    int top;

    Stack() 
    { top = -1; 
     }

    void push(Node* node) 
    {
        if (top < 99) 
        {
            arr[++top] = node;
        }
    }

    Node* pop() 
    {
        if (top >= 0)
            return arr[top--];
        return nullptr;
    }

    Node* peek() 
    {
        if (top >= 0)
            return arr[top];
        return nullptr;
    }

    bool isEmpty() 
    {
        return top == -1;
    }
};


bool isOperator(char ch) 
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}


Node* createNode(char data) 
{
    Node* newNode = new Node;
    newNode->data = data;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}


int precedence(char op) 
{
    if (op == '*' || op == '/')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    return 0;
}


Node* constructTree(char expr[]) 
{
    Stack operandStack, operatorStack;

    for (int i = 0; expr[i] != '\0'; i++) 
    {
        char ch = expr[i];

        if (ch == ' ')
            continue;

        if (!isOperator(ch)) 
        {
            Node* operand = createNode(ch);
            operandStack.push(operand);
        } else 
        {
            while (!operatorStack.isEmpty() &&
                   precedence(operatorStack.peek()->data) >= precedence(ch)) 
                   {
                Node* opNode = operatorStack.pop();
                Node* rightOperand = operandStack.pop();
                Node* leftOperand = operandStack.pop();
                opNode->right = rightOperand;
                opNode->left = leftOperand;
                operandStack.push(opNode);
            }
            Node* opNode = createNode(ch);
            operatorStack.push(opNode);
        }
    }


    while (!operatorStack.isEmpty()) 
    {
        Node* opNode = operatorStack.pop();
        Node* rightOperand = operandStack.pop();
        Node* leftOperand = operandStack.pop();
        opNode->right = rightOperand;
        opNode->left = leftOperand;
        operandStack.push(opNode);
    }

    return operandStack.pop();
}


void postorderTraversal(Node* root) 
{
    if (!root)
        return;

    Stack s1, s2;
    s1.push(root);

    while (!s1.isEmpty()) 
    {
        Node* node = s1.pop();
        s2.push(node);

        if (node->left)
            s1.push(node->left);
        if (node->right)
            s1.push(node->right);
    }

    while (!s2.isEmpty()) 
    {
        Node* node = s2.pop();
        cout << node->data << " ";
    }
}


void deleteTree(Node* root) 
{
    if (!root)
        return;

    Stack s;
    s.push(root);

    while (!s.isEmpty()) 
    {
        Node* node = s.pop();

        if (node->right)
            s.push(node->right);
        if (node->left)
            s.push(node->left);

        delete node;
    }
}


int main()
 {
    char expr[] = "a-b*c-d/e+f";

    Node* root = constructTree(expr);

    cout << "Postorder Traversal (Non-Recursive): ";
    postorderTraversal(root);

    deleteTree(root);

    return 0;
}
