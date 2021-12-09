#include <bits/stdc++.h>

using namespace std;

void build_sparse(vector<vector<pair<int, int>>> &sparse, int n, int k)
{
    for (int j = 1; j < k; j++)
        for (int i = 0; i < n; i++) {
            sparse[i][j].first = sparse[sparse[i][j - 1].first][j - 1].first;
            sparse[i][j].second = min(sparse[i][j - 1].second, sparse[sparse[i][j - 1].first][j - 1].second);
        }
}

void build_level(vector<int> &level, vector<vector<pair<int, int>>>  &sparse, int n, int k) {
    vector<vector<int>> g(n, vector<int> ());
    for (int i = 1; i < n; i++)
    {
        g[sparse[i][0].first].push_back(i);
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
    freopen("minonpath.in", "r", stdin);
    freopen("minonpath.out", "w", stdout);
    int n;
    cin >> n;
    int k = 0;
    int n1 = n;
    while (n1 != 1) {
        k++;
        n1 /= 2;
    }
    k++;
    vector<vector<pair<int, int>>> sparse(n, vector<pair<int, int>> (k));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++)
            sparse[i][j] = {i, INT_MAX};
    for (int i = 1; i < n; i++) {
        int prev, cost;
        cin >> prev >> cost;
        sparse[i][0] = {--prev, cost};
    }
    build_sparse(sparse, n, k);
    vector<int> level(n, -1);
    build_level(level, sparse, n, k);
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        int ans = INT_MAX;
        cin >> u >> v;
        u--;
        v--;
        if (level[u] > level[v])
            swap(u, v);
        for (int j = k - 1; j >= 0; j--)
        {
            if (level[sparse[v][j].first] - level[u] >= 0)
            {
                ans = min(ans, sparse[v][j].second);
                v = sparse[v][j].first;
            }
        }
        if (u == v) {
            cout << ans << endl;
            continue;
        }
        for (int j = k - 1; j >= 0; j--)
        {
            if (sparse[u][j].first != sparse[v][j].first)
            {
                ans = min(ans, sparse[u][j].second);
                ans = min(ans, sparse[v][j].second);
                u = sparse[u][j].first;
                v = sparse[v][j].first;
            }
        }
        cout << min(ans, min(sparse[u][0].second, sparse[v][0].second))  << endl;
    }
}



