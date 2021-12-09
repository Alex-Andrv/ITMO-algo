#include <bits/stdc++.h>

using namespace std;


int minn(vector<int> &log, vector<vector<int>> &SparseTable, int l, int r)
{
    return min(SparseTable[log[r - l]][l], SparseTable[log[r - l]][r - (1 << log[r - l])]);
}

int main()
{

    int n, m;
    int a0;
    cin >> n >> m >> a0;
    int bn = 1;
    vector<int> log(n + 1);
    int bz = 2;
    log[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i == bz)
        {
            bz *= 2;
            log[i] = log[i - 1] + 1;
        }
        else
        {
            log[i] = log[i - 1];
        }
    }
    /*for (int i = 0; i <= n; i++)
    {
        cout << log[i] << " " << i << endl;
    }*/
    vector<vector<int>> SparseTable(log[n] + 1, vector<int> (n));
    SparseTable[0][0] = a0;
    for (int i = 1; i < n; i++)
    {
        SparseTable[0][i] = ((23 * SparseTable[0][i - 1] + 21563) % 16714589);
    }
    //cout << log[n];
    int start = 2;
    for (int i = 1; i <= log[n]; i++)
    {
        for (int j = 0; j < n - (start - 1); j++)
        {
            SparseTable[i][j] = (min(SparseTable[i - 1][j], SparseTable[i - 1][j + start / 2]));
        }
        start = start * 2;
    }
    /*cout << "!!" << endl;
    for (int i = 0; i < SparseTable.size(); i++)
    {
        for (int j = 0; j < SparseTable[i].size(); j++)
        {
            cout << SparseTable[i][j] << " ";
        }
        cout << endl;
    }*/
    int u, v;
    cin >> u >> v;
    int r = 0;
    for (int i = 0; i < m; i++)
    {
        r = minn(log, SparseTable, min(u, v) - 1, max(u, v));
        if (i != (m - 1))
        {
            u = ((17 * u + 751 + r + 2 * (i + 1)) % n) + 1;
            v = ((13 * v + 593 + r + 5 * (i + 1)) % n) + 1;
            //cout << u  << " " << v << endl;
        }
    }
    cout << u << " " << v << " " << r;
}
