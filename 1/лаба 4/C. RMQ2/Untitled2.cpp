#include <bits/stdc++.h>

#define LL long long

using namespace std;

struct my_pair
{
    LL v;
    int op;
    my_pair(int v1 = 0, LL op1 = 0)
    {
        v = v1;
        op = op1;
    }
};

struct nodes
{
    LL min_el;
    my_pair set_el;
    LL add;
    nodes(LL m = 0, my_pair s = my_pair(0, 0), LL a = 0)
    {
        min_el = m;
        set_el = my_pair(0, 0);
        add = a;
    }
};

vector<nodes> SegmentTree;
vector<LL> arr;

void out(string st, int v, int vl, int vr)
{
    cout << st << " " << v << " " << vl << " " << vr << endl;
    for (int i = 0; i < SegmentTree.size(); i++)
    {
        cout << "v = " << i  << " min = " << SegmentTree[i].min_el << " add = " << SegmentTree[i].add << " set = (" << SegmentTree[i].set_el.v << ", " << SegmentTree[i].set_el.op << ")" << endl;
    }
    return;
}

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
        cout << "("<< SegmentTree[i].min_el << ", " << SegmentTree[i].add << ", (" << SegmentTree[i].set_el.v << ", " << SegmentTree[i].set_el.op << "))" << " ";
    }
    cout << endl;
    return;
}

void build (int v, int vl, int vr)
{
    if (vr - vl == 1)
    {
        SegmentTree[v].min_el = arr[vl];
        return;
    }
    int vm = (vl + vr) / 2;
    build(2 * v + 1, vl, vm);
    build(2 * v + 2, vm, vr);
    SegmentTree[v].min_el =  min(SegmentTree[2 * v + 1].min_el, SegmentTree[2 * v + 2].min_el);
}

void propogate(int v, int vl, int vr)
{
    if (vr - vl == 1)
    {
        return;
    }
    if (SegmentTree[v].set_el.op == 0 && SegmentTree[v].add == 0)
    {
        return;
    }
    if (SegmentTree[v].set_el.op == 1)
    {
        SegmentTree[2 * v + 1].set_el = SegmentTree[v].set_el;
        SegmentTree[2 * v + 1].min_el = SegmentTree[v].set_el.v;
        SegmentTree[2 * v + 2].set_el = SegmentTree[v].set_el;
        SegmentTree[2 * v + 2].min_el = SegmentTree[v].set_el.v;
        SegmentTree[2 * v + 1].add = 0;
        SegmentTree[2 * v + 2].add = 0;
        SegmentTree[v].set_el = my_pair(0, 0);
    }
    SegmentTree[2 * v + 1].add += SegmentTree[v].add;
    SegmentTree[2 * v + 1].min_el += SegmentTree[v].add;
    SegmentTree[2 * v + 2].add += SegmentTree[v].add;
    SegmentTree[2 * v + 2].min_el += SegmentTree[v].add;
    SegmentTree[v].add = 0;
}

LL min_el(int v, int vl, int vr, int l, int r)
{
    // out("min", v, vl, vr);
    if (l <= vl && vr <= r)
    {
        return SegmentTree[v].min_el;
    }
    propogate(v, vl, vr);
    int vm = (vr + vl) / 2;
    if (r <= vm)
    {
        return min_el(2 * v + 1, vl, vm, l, r);
    }
    if (l >= vm)
    {
        return min_el(2 * v + 2, vm, vr, l, r);
    }
    return min(min_el(2 * v + 1, vl, vm, l, r), min_el(2 * v + 2, vm, vr, l, r));
}


void set_el(int v, int vl, int vr, int l, int r, LL x)
{
    if (l >= vr || r <= vl)
    {
        return;
    }
    //out("set", v, vl, vr);
    if (l <= vl && vr <= r)
    {
        SegmentTree[v].min_el = x;
        SegmentTree[v].set_el = my_pair(x, 1);
        SegmentTree[v].add = 0;
        return;
    }
    propogate(v, vl, vr);
    int vm = (vr + vl) / 2;
    set_el(2 * v + 1, vl, vm, l, r, x);
    set_el(2 * v + 2, vm, vr, l, r, x);
    SegmentTree[v].min_el =  min(SegmentTree[2 * v + 1].min_el, SegmentTree[2 * v + 2].min_el);
}


void add(int v, int vl, int vr, int l, int r, LL x)
{
    if (r <= vl || l >= vr)
    {
        return;
    }
    //out("add", v, vl, vr);
    if (l <= vl && vr <= r)
    {
        SegmentTree[v].min_el = SegmentTree[v].min_el + x;
        SegmentTree[v].add += x;
        return;
    }
    propogate(v, vl, vr);
    int vm = (vr + vl) / 2;
    add(2 * v + 1, vl, vm, l, r, x);
    add(2 * v + 2, vm, vr, l, r, x);
    SegmentTree[v].min_el =  min(SegmentTree[2 * v + 1].min_el, SegmentTree[2 * v + 2].min_el);
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
        if (st == "set")
        {
            int l, r;
            LL x;
            cin >> l >> r >> x;
            set_el(0, 0, bn, --l, r, x);
            //out();
        }
        if (st == "min")
        {
            int l, r;
            cin >> l >> r;
            cout << min_el(0, 0, bn, --l, r) << endl;
            //out();
        }
        if (st == "add")
        {
            int l, r;
            LL x;
            cin >> l >> r >> x;
            add(0, 0, bn, --l, r, x);
            //out();
        }
    }
}
