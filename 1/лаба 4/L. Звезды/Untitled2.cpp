#include <bits/stdc++.h>

using namespace std;


vector<vector<vector<int>>> fenwick;

void set_el(int x1, int y1, int z1, int q, int n)
{
    for (int x = x1; x < n; x |= (x + 1))
        for (int y = y1; y < n; y |= (y + 1))
            for (int z = z1; z < n; z |= (z + 1))
            {
                //cout << x << endl;
                fenwick[x][y][z] += q;
            }
}

int coun(int x1, int y1, int z1)
{
    int res = 0;
    for (int x = x1; x >= 0; x = (x & (x + 1)) - 1)
        for (int y = y1; y >= 0; y = (y & (y + 1)) - 1)
            for (int z = z1; z >= 0; z = (z & (z + 1)) - 1)
            {
                //cout << z << endl;
                res += fenwick[x][y][z];
            }
    return res;
}

int main()
{
    int n;
    cin >> n;
    fenwick.resize(n, vector<vector<int>> (n, vector<int> (n)));
    int v;
    cin >> v;
    while (v != 3)
    {
        if (v == 1)
        {
            int x, y, z, q;
            cin >> x >> y >> z >> q;
            set_el(x, y, z, q, n);
        }
        else
        {
            int x1, y1, z1, x2, y2, z2;
            cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            cout << coun(x2, y2, z2) - coun(x2, y2, z1 - 1) - coun(x2, y1 - 1, z2) - coun(x1 - 1, y2, z2) + coun(x2, y1 - 1, z1 - 1) + coun(x1 - 1, y2, z1 - 1) + coun(x1 - 1, y1 - 1, z2) - coun(x1 - 1, y1 - 1, z1 - 1) << '\n';
        }
        cin >> v;
    }
}
