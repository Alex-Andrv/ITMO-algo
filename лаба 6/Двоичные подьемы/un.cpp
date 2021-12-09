#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    int k = 0;
    int n1 = n;
    while (n1 != 1) {
        k++;
        n1 /= 2;
    }
    k++;
    int sparse[n][k];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++)
            sparse[i][j] = -1;
    int root;
    for (int i = 0; i < n; i++) {
        int prev;
        cin >> prev;
        if (prev == 0) {
            root = i;
        }
        else {
            sparse[i][0] = --prev;
        }
    }
    for (int j = 1; j < k; j++)
        for (int i = 0; i < n; i++) {
            if (sparse[i][j - 1] != -1)
                sparse[i][j] = sparse[sparse[i][j - 1]][j - 1];
        }
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ":";
        int j = 0;
        while (j < k && sparse[i][j] != -1) {
            cout << " " << sparse[i][j] + 1;
            j++;
        }
        cout << endl;
    }
}


