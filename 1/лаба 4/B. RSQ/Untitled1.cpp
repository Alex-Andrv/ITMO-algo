#include <bits/stdc++.h>

#define LL long long

using namespace std;

vector<LL> SegmentTree;
vector<LL> arr;

void build (int v, int vl, int vr)
{
    if (vr - vl == 1)
    {
        SegmentTree[v] = arr[vl];
        return;
    }
    int vm = (vl + vr) / 2;
    build(2 * v + 1, vl, vm);
    build(2 * v + 2, vm, vr);
    SegmentTree[v] =  SegmentTree[2 * v + 1] + SegmentTree[2 * v + 2];
}

LL sum(int v, int vl, int vr, int l, int r)
{
  //  cout << v << " " << vl << " " << vr << " " << l << " " << r << endl;
    if (vr - vl == 1)
    {
        return SegmentTree[v];
    }
    if (l <= vl && vr <= r)
    {
        return SegmentTree[v];
    }
    int vm = (vr + vl) / 2;
    if (r <= vm)
    {
        return sum(2 * v + 1, vl, vm, l, r);
    }
    if (l >= vm)
    {
        return sum(2 * v + 2, vm, vr, l, r);
    }
    return sum(2 * v + 1, vl, vm, l, r) + sum(2 * v + 2, vm, vr, l, r);
}

void set_el(int v, int vl, int vr, int i, int x)
{
    if (vr - vl == 1)
    {
        SegmentTree[v] = x;
        return;
    }
    int vm = (vr + vl) / 2;
    if (i < vm)
    {
        set_el(2 * v + 1, vl, vm, i, x);
    }
    else
    {
        set_el(2 * v + 2, vm, vr, i, x);
    }
    SegmentTree[v] =  SegmentTree[2 * v + 1] + SegmentTree[2 * v + 2];
}

int main()
{
    int n;
    cin >> n;
    int bn = 1;
    while (bn < n)
    {
        bn *= 2;
    }
    arr.resize(bn);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    SegmentTree.resize(2 * bn);
    build(0, 0, bn);
    /*for (int i = 0; i < SegmentTree.size(); i++)
        cout << SegmentTree[i] << " ";
    cout << endl;*/
    string st;
    while (cin >> st)
    {
        if (st == "sum")
        {
            int l, r;
            cin >> l >> r;
            cout << sum(0, 0, bn, --l, r) << endl;
        }
        else
        {
            int i, x;
            cin >> i >> x;
            set_el(0, 0, bn, --i, x);
        }
    }
}
