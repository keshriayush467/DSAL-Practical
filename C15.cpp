#include <iostream>
using namespace std;

#define MAX 100
#define INF 99999

int cost[MAX][MAX];   
int visited[MAX];     
int n;               

void inputGraph() {
    cout << "Enter number of offices: ";
    cin >> n;

    cout << "Enter the cost matrix (use " << INF << " if no direct connection):\n";
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            cin >> cost[i][j];
        }
    }
}

void prim() 
{
    int parent[MAX];     
    int minCost[MAX];        
    int totalCost = 0;

    // Initialize arrays
    for (int i = 0; i < n; i++) 
    {
        minCost[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    minCost[0] = 0;  // Start from first office

    for (int count = 0; count < n - 1; count++) 
    {
        int min = INF, u = -1;

        // Find unvisited node with smallest key
        for (int i = 0; i < n; i++) 
        {
            if (!visited[i] && minCost[i] < min) 
            {
                min = minCost[i];
                u = i;
            }
        }

        visited[u] = 1;

        // Update neighboring nodes
        for (int v = 0; v < n; v++) 
        {
            if (cost[u][v] < minCost[v] && !visited[v]) 
            {
                minCost[v] = cost[u][v];
                parent[v] = u;
            }
        }
    }

    // Print MST edges and total cost
    cout << "\nMinimum Spanning Tree Edges:\n";
    for (int i = 1; i < n; i++) {
        if (parent[i] != -1) {
            cout << "Office " << parent[i] + 1 << " - Office " << i + 1
                 << " : Cost = " << cost[i][parent[i]] << "\n";
            totalCost += cost[i][parent[i]];
        }
    }
    cout << "Total minimum cost: " << totalCost << "\n";
}

int main() {
    int choice;

    do {
        cout << "\n*** Phone Line Connection Menu ***\n";
        cout << "1. Input cost matrix\n";
        cout << "2. Find Minimum Cost using Prim's Algorithm\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                inputGraph();
                break;
            case 2:
                if (n == 0) {
                    cout << "Please input the cost matrix first.\n";
                } else {
                    prim();
                }
                break;
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
