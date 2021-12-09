#include <bits/stdc++.h>

using namespace std;

void build_sparse(vector<vector<int>> &sparse, int n, int k)
{
    for (int j = 1; j < k; j++)
        for (int i = 0; i < n; i++) {
            if (sparse[i][j - 1] != -1)
                sparse[i][j] = sparse[sparse[i][j - 1]][j - 1];
        }
}

void build_level(vector<int> &level, vector<vector<int>>  &sparse, int n, int k) {
    vector<vector<int>> g(n, vector<int> ());
    for (int i = 1; i < n; i++)
    {
        g[sparse[i][0]].push_back(i);
    }
    level[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int f = q.front();
        q.pop();
        for (auto el : g[f])
        {
            level[el] = level[f] + 1;
            q.push(el);
        }
    }
}

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
    vector<vector<int>> sparse(n, vector<int> (k));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++)
            sparse[i][j] = i;
    for (int i = 1; i < n; i++) {
        int prev;
        cin >> prev;
        sparse[i][0] = --prev;
    }
    build_sparse(sparse, n, k);
    vector<int> level(n, -1);
    build_level(level, sparse, n, k);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        if (level[u] > level[v])
            swap(u, v);
        for (int j = k - 1; j >= 0; j--)
        {
            if (level[sparse[v][j]] - level[u] >= 0)
                v = sparse[v][j];
        }
        if (u == v) {
            cout << u + 1 << endl;
            continue;
        }
        for (int j = k - 1; j >= 0; j--)
        {
            if (sparse[u][j] != sparse[v][j])
            {
                u = sparse[u][j];
                v = sparse[v][j];
            }
        }
        cout << sparse[u][0] + 1 << endl;
    }
}



