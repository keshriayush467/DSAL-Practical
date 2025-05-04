#include <iostream>
using namespace std;

#define MAX 20
float cost[MAX][MAX];
int root[MAX][MAX];

// Function to build the optimal BST
void buildOptimalBST(int n, float p[]) {
    for (int i = 0; i < n; i++) {
        cost[i][i] = p[i];  // Cost of single key is its probability
        root[i][i] = i;     // Root of single key is itself
    }

    // Build trees of size 2 to n
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            cost[i][j] = 1e9;  // Initialize with a large number

            float sumP = 0;
            for (int s = i; s <= j; s++) sumP += p[s];

            for (int r = i; r <= j; r++) {
                float c = 0;
                if (r > i) c += cost[i][r - 1];
                if (r < j) c += cost[r + 1][j];
                c += sumP;

                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
        }
    }
}

// Function to print the tree in simple form
void printTree(int i, int j, int keys[], int parent, bool isLeft) {
    if (i > j) return;
    int r = root[i][j];

    if (parent == -1)
        cout << "Root: " << keys[r] << "\n";
    else if (isLeft)
        cout << "Left child of " << keys[parent] << ": " << keys[r] << "\n";
    else
        cout << "Right child of " << keys[parent] << ": " << keys[r] << "\n";

    printTree(i, r - 1, keys, r, true);
    printTree(r + 1, j, keys, r, false);
}

int main() {
    int n, keys[MAX];
    float p[MAX];

    cout << "Enter number of keys: ";
    cin >> n;

    cout << "Enter " << n << " sorted keys: ";
    for (int i = 0; i < n; i++) cin >> keys[i];

    cout << "Enter " << n << " access probabilities: ";
    for (int i = 0; i < n; i++) cin >> p[i];

    buildOptimalBST(n, p);

    cout << "\nMinimum search cost: " << cost[0][n - 1] << "\n";
    cout << "Optimal BST structure:\n";
    printTree(0, n - 1, keys, -1, false);

    return 0;
}
