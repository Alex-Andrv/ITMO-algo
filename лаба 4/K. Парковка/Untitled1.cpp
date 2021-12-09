#include <bits/stdc++.h>

using namespace std;

vector<int> SegmentTree;

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

void build(int v, int vl, int vr)
{
    if (vr - vl == 1)
    {
        return;
    }
    int vm = (vl + vr) / 2;
    build(2 * v + 1, vl, vm);
    build(2 * v + 2, vm, vr);
    SegmentTree[v] = SegmentTree[2 * v + 1];
    if (SegmentTree[v] == -1)
    {
        SegmentTree[v] = SegmentTree[2 * v + 2];
    }
    return;
}

void set_el(int v, int vl, int vr, int pos, int value)
{
    if (vr - vl == 1)
    {
        SegmentTree[v] = value;
        return;
    }
    int vm = (vl + vr) / 2;
    if (pos < vm)
    {
        set_el(2 * v + 1, vl, vm, pos, value);
    }
    else
    {
        set_el(2 * v + 2, vm, vr, pos, value);
    }
    SegmentTree[v] = SegmentTree[2 * v + 1];
    if (SegmentTree[v] == -1)
    {
        SegmentTree[v] = SegmentTree[2 * v + 2];
    }
    return;
}

int left_pos(int v, int vl, int vr, int l, int r)
{
    if (l <= vl && vr <= r)
    {
        return SegmentTree[v];
    }
    if (vr <= l || r <= vl)
    {
        return -1; // че?
    }
    int vm = (vl + vr) / 2;
    int ans = left_pos(2 * v + 1, vl, vm, l, r);
    if (ans == -1)
    {
        return left_pos(2 * v + 2, vm, vr, l, r);
    }
    return ans;
}

int main()
{
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    ifstream fin ("parking.in");
    ofstream fout("parking.out");
    int n, m;
    fin >> n >> m;
    int bn = 1;
    while (bn < n)
    {
        bn *= 2;
    }
    SegmentTree.resize(2 * bn);
    for (int i = bn - 1; i < 2 * bn - 1; i++)
    {
        SegmentTree[i] = i - (bn - 1);
    }
    build(0, 0, bn);
    //out();
    for (int i = 0; i < m; i++)
    {
        string st;
        fin >> st;
        if (st == "enter")
        {
            int pos;
            fin >> pos;
            pos--;
            //cout << pos + 1 << endl;
            pos = max(left_pos(0, 0, bn, pos, n), left_pos(0, 0, bn, 0, pos));
            //cout << pos + 1 << endl;
            fout << pos + 1 << '\n';
            set_el(0, 0, bn, pos, -1);
            //out();
        }
        else
        {
            int pos;
            fin >> pos;
            pos--;
            set_el(0, 0, bn, pos, pos);
            //out();
        }
    }
    fin.close();
    fout.close();
}

