#include <bits/stdc++.h>

using namespace std;

struct my_pair
{
    int f;
    int s;
};
struct my_min
{
    int m;
    int p;
    my_min (int mm = 0, int pp = 0)
    {
        m = mm;
        p = pp;
    }
};

struct node
{
    my_min m;
    my_pair s;
    node (int mm, int pp)
    {
        s.f = 0;
        s.s = 0;
        m.m = mm;
        m.p = pp;
    }
};

vector<node> SegmentTree;

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
        cout << "("<< SegmentTree[i].m.m << ", " << SegmentTree[i].m.p << "), (" << SegmentTree[i].s.f << ", " << SegmentTree[i].s.s << "))" << " ";
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
}

void propagate(int v, int vl, int vr)
{
    if (vr - vl == 1)
    {
        return;
    }
    if (SegmentTree[v].s.f == 0)
    {
        return;
    }
    int vm = (vl + vr) / 2;
    if (SegmentTree[2 * v + 1].m.m < SegmentTree[v].s.s)
    {
        SegmentTree[2 * v + 1].m.m = SegmentTree[v].s.s;
        SegmentTree[2 * v + 1].s.f = 1;
        SegmentTree[2 * v + 1].s.s = SegmentTree[v].s.s;
    }
    if (SegmentTree[2 * v + 2].m.m < SegmentTree[v].s.s)
    {
        SegmentTree[2 * v + 2].m.m = SegmentTree[v].s.s;
        SegmentTree[2 * v + 2].s.f = 1;
        SegmentTree[2 * v + 2].s.s = SegmentTree[v].s.s;
    }
    SegmentTree[v].s.f = 0;
    return;
}

my_min min_el(int v, int vl, int vr, int l, int r)
{
    if (l >= vr || r <= vl)
    {
        return my_min(INT_MAX, INT_MAX);
    }
    if (l <= vl && vr <= r)
    {
        return SegmentTree[v].m;
    }
    propagate(v, vl, vr);
    int vm = (vr + vl) / 2;
    my_min f = min_el(2 * v + 1, vl, vm, l, r);
    my_min s = min_el(2 * v + 2, vm, vr, l, r);
    return f.m < s.m ? f : s;
}


void set_el(int v, int vl, int vr, int l, int r, int c)
{
    if (l >= vr || r <= vl)
    {
        return;
    }
    if (l <= vl && vr <= r)
    {
        if (c <= SegmentTree[v].m.m)
        {
            return;
        }
        SegmentTree[v].m.m = c;
        SegmentTree[v].s.f = 1;
        SegmentTree[v].s.s = c;
        return;
    }
    propagate(v, vl, vr);
    int vm = (vr + vl) / 2;
    set_el(2 * v + 1, vl, vm, l, r, c);
    set_el(2 * v + 2, vm, vr, l, r, c);
    if (SegmentTree[2 * v + 1].m.m < SegmentTree[2 * v + 2].m.m)
    {
        SegmentTree[v].m = SegmentTree[2 * v + 1].m;
    }
    else
    {
        SegmentTree[v].m = SegmentTree[2 * v + 2].m;
    }
    return;
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
    SegmentTree.resize(2 * bz, node(0, 0));
    for (int i = bz - 1; i < 2 * bz - 1; i++)
    {
        SegmentTree[i].m.p = i - bz + 1;
    }
    build(0, 0, bz);
    for (int i = 0; i < m; i++)
    {
        string st;
        cin >> st;
        //out();
        if (st == "defend")
        {
            int l, r, c;
            cin >> l >> r >> c;
            set_el(0, 0, bz, --l, r, c);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            my_min ans = min_el(0, 0, bz, --l, r);
            cout << ans.m << " " << ans.p + 1<< '\n';
        }
        //out();
    }
}
