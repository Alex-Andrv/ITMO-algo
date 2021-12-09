#include <bits/stdc++.h>

#define LL long long

using namespace std;

vector<int> SegmentTree;

ifstream fin("rmq.in");
ofstream fout("rmq.out");

void out()
{
    cout << " !!!!!! " << endl;
    int pereh = 1;
    for (int i = 0; i < SegmentTree.size() - 1; i++)
    {
        if (pereh == i + 1)
        {
            cout << endl;
            pereh *= 2;
        }
        cout << SegmentTree[i] << " ";
    }
    cout << endl;
    return;
}

void propogate(int v, int vl, int vr)
{
    if (vr - vl == 1)
    {
        return;
    }
    int vm = (vl + vr) / 2;
    SegmentTree[2 * v + 1] = max(SegmentTree[v], SegmentTree[2 * v + 1]);
    SegmentTree[2 * v + 2] = max(SegmentTree[v], SegmentTree[2 * v + 2]);
    SegmentTree[v] = min(SegmentTree[2 * v + 1], SegmentTree[2 * v + 2]);

}

void propogate_all(int v, int vl, int vr)
{
    if (vr - vl == 1)
    {
        return;
    }
    propogate(v, vl, vr);
    int vm = (vl + vr) / 2;
    propogate_all(2 * v + 1, vl, vm);
    propogate_all(2 * v + 2, vm, vr);
}


void set_el(int v, int vl, int vr, int l, int r, int x)
{
    if (l >= vr || r <= vl)
    {
        return;
    }
    //out("set", v, vl, vr);
    if (l <= vl && vr <= r)
    {
        SegmentTree[v] = max(x, SegmentTree[v]);
        return;
    }
    propogate(v, vl, vr);
    int vm = (vr + vl) / 2;
    set_el(2 * v + 1, vl, vm, l, r, x);
    set_el(2 * v + 2, vm, vr, l, r, x);
    SegmentTree[v] = min(SegmentTree[2 * v + 1], SegmentTree[2 * v + 2]);
}

int get_min(int v, int vl, int vr, int l, int r)
{
    if (l >= vr || r <= vl)
    {
        return INT_MAX;
    }
    if (l <= vl && vr <= r)
    {
        return SegmentTree[v];
    }
    int vm = (vl + vr) / 2;
    return min(get_min(2 * v + 1, vl, vm, l, r), get_min(2 * v + 2, vm, vr, l, r));
}


int main()
{
    int n, m;
    fin >> n >> m;
    int bn = 1;
    while (bn < n)
    {
        bn *= 2;
    }
    SegmentTree.resize(2 * bn, INT_MIN);
    vector<vector<int>> zapr(m, vector<int> (3));
    for (int i = 0; i < m; i++)
    {
        //out();
        int l, r, q;
        fin >> l >> r >> q;
        zapr[i][0] = l;
        zapr[i][1] = r;
        zapr[i][2] = q;
        set_el(0, 0, bn, l - 1, r, q);
    }
    //out();
    propogate_all(0, 0, bn);
    for (int i = 0; i < m; i++)
    {
        int l, r, q;
        l = zapr[i][0];
        r = zapr[i][1];
        q = zapr[i][2];
        if (get_min(0, 0, bn, l - 1, r) != q)
        {
            fout << "inconsistent";
            fin.close();
            fout.close();
            exit(0);
        }
    }
    //out();
    fout << "consistent" << '\n';
    for (int i = bn - 1; i < bn + n - 1; i++)
    {
        fout << SegmentTree[i] << " ";
    }
    fin.close();
    fout.close();
}

