#include<iostream>
using namespace std;
#define MAX 100

int adj[MAX][MAX];
int visited[MAX];
char landmark[MAX][50];
int n;

int stack[MAX];
int top =-1;

int queue[MAX];
   int front =-1;
   int rear =-1;


void push(int val)
{
    stack[++top] = val;
}

int pop()
{
    return stack[top--];
}

void enqueue(int val)
{
    if(front==-1)
    {
        front =0;
    }
    queue[++rear]= val;
}

int dequeue()
{
    return queue[front++];
}

void DFS(int start)
{
    for(int i=0;i<n; i++)
    {
        visited[i]=0;
    }
    push(start);
    visited[start]=1;
    
    cout<<"\nDFS Traversal is ";
    while(top!=-1)
    {
        int current = pop();
        cout<<landmark[current] <<" ";
        for(int i=0; i<n;i++)
        {
            if(adj[current][i]==1 && visited[i]==0)
            {
                push(i);
                visited[i]=1;
            }
        }
    }
}

void BFS(int start )
{
    for(int i=0;i<n;i++)
    {
        visited[i]=0;
    }
    front = rear = -1;
    enqueue(start);
    visited[start] =1;

    cout<<"\nBFS Traversal is ";
    while(front<=rear )
    {
        int current = dequeue();
        cout<<landmark[current] <<" ";

        for(int i=0;i<n;i++)
        {
            if(adj[current][i]==1 && visited[i]==0)
            {
                enqueue(i);
                visited[i]=1;
            }
        }
    }
}

int main()
{
    cout<<"\nEnter the no of Landmarks ";
    cin>>n;

    cout<<"\nEnter the name of landmarks ";
    for(int i=0;i<n;i++)
    {
        cin>>landmark[i];
    }

    cout<<"\nEnter the Adjacency Matrix ";
    for(int i=0;i<n;i++)
    {
       for(int j=0;j<n;j++)
       {
        cin>>adj[i][j];
       }
    }
    int start;
    cout<<"\nEnter the starting index ";
    cin>>start;
    DFS(start);
    BFS(start);
    return 0;
}