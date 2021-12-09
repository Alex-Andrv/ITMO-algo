#include <bits/stdc++.h>

using namespace std;


int LCA(int u, int v, vector<int> &level, vector<vector<int>>  &sparse, int k)
{
    if (level[u] > level[v])
        swap(u, v);
    for (int j = k - 1; j >= 0; j--)
    {
        if (level[sparse[v][j]] - level[u] >= 0)
            v = sparse[v][j];
    }
    if (u == v) {
        return u;
    }
    for (int j = k - 1; j >= 0; j--)
    {
        if (sparse[u][j] != sparse[v][j])
        {
            u = sparse[u][j];
            v = sparse[v][j];
        }
    }
    return sparse[u][0];
}

int get_log(int n)
{
    int k = 0;
    while (n != 1)
    {
        n /= 2;
        k++;
    }
    return k + 1;
}

int f(int u, vector<int> &first_life, vector<vector<int>> &sparse)
{
    if (first_life[u] == u)
        return first_life[u];
    first_life[u] = f(first_life[u], first_life, sparse);
    return first_life[u];
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int k = get_log(n);
    vector<vector<int>> sparse(n + 1, vector<int> (k));
    vector<int> level(n + 1, -1);
    level[0] = 0;
    int count = 1;
    vector<int> first_life(n + 1, -1);
    first_life[0] = 0;
    for (int i = 0; i < n; i++)
    {
        int v;
        char c;
        cin >> c;
        switch (c)
        {
            case '+':
                cin >> v;
                level[count] = level[--v] + 1;
                sparse[count][0] = v;
                first_life[count] = count;
                for (int j = 1; j < k; j++)
                {
                    sparse[count][j] = sparse[sparse[count][j - 1]][j - 1];
                }
                count++;
                break;
            case '-':
                cin >> v;
                --v;
                first_life[v] = sparse[v][0];
                break;
            case '?':
                int u;
                cin >> u >> v;
                cout << f(LCA(--u, --v, level, sparse, k), first_life, sparse) + 1 << "\n";
                break;
        }
    }

}
