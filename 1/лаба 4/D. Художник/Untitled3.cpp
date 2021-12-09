#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> SegmentTree;


void propagate(int v, int vl, int vr)
{
    if (vr - vl == 1)
    {
        return;
    }
    if (SegmentTree[v].first == 0)
    {
        return;
    }
    SegmentTree[2 * v + 1] = SegmentTree[v];
    SegmentTree[2 * v + 2] = SegmentTree[v];
    SegmentTree[v].first = 0;
    //SegmentTree[v].second = min(SegmentTree[2 * v + 1].second, SegmentTree[2 * v + 2].second);
    return;
}

void set_el(int v, int vl, int vr, int l, int r, int q)
{
    if (l >= vr || r <= vl)
    {
        return;
    }
    if (l <= vl && vr <= r)
    {
        SegmentTree[v].second = q;
        SegmentTree[v].first = 1;
        return;
    }
    propagate(v, vl, vr);
    int vm = (vl + vr) / 2;
    set_el(2 * v + 1, vl, vm, l, r, q);
    set_el(2 * v + 2, vm, vr, l, r, q);
    //SegmentTree[v].second = min(SegmentTree[2 * v + 1].second, SegmentTree[2 * v + 2].second);
    return;
}

int min_el(int v, int vl, int vr, int l, int r)
{
    if (l >= vr || r <= vl)
    {
        return INT_MAX;
    }
    if (l <= vl && vr <= r)
    {
        return SegmentTree[v].second;
    }
    propagate(v, vl, vr);
    int vm = (vl + vr) / 2;
    return min(min_el(2 * v + 1, vl, vm, l, r), min_el(2 * v + 2, vm, vr, l, r));
}

int main()
{
    int n, m;
    cin >> n >> m;
    int bz = 1;
    while (bz < n)
    {
        bz *= 2;
    }
    SegmentTree.resize(2 * bz, {0, INT_MIN});
    vector<vector<int>> zapr(m, vector<int> (3));
    for (int i = 0; i < m; i++)
    {
        int l, r, q;
        cin >> l >> r >> q;
        set_el(0, 0, bz, --l, r, q);
        zapr[i][0] = l;
        zapr[i][1] = r;
        zapr[i][2] = q;
    }
    for (int i = 0; i < m; i++)
    {
        if (min_el(0, 0, bz, zapr[i][0], zapr[i][1]) != zapr[i][2])
        {
            cout << "inconsistent";
            exit(0);
        }
    }
    cout << "consistent" << '\n';
    for (int i = bz - 1; i < bz + n - 1; i++)
    {
        cout << SegmentTree[i].second << " ";
    }
    return 0;
}
