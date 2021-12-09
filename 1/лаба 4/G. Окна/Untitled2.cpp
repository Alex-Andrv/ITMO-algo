#include <bits/stdc++.h>

using namespace std;

const int sm = 2 * 100000;
const int bz = 1 << 19;

struct point
{
    int x;
    int y1;
    int y2;
    int t;
    point (int xx = 0, int yy1 = 0, int yy2 = 0, int tt = 1)
    {
        x = xx;
        y1 = yy1;
        y2 = yy2;
        t = tt;
    }
};

struct my_pair
{
    int f;
    int s;
    my_pair(int ff = 0, int ss = 0)
    {
        f = ff;
        s = ss;
    }
};

struct node
{

    my_pair m;
    my_pair s;
    node ()
    {
        m.f = 0;
        m.s = 0;
        s.f = 0;
        s.s = 0;
    }

};

vector<node> SegmentTree(2 * bz);

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
        cout << "(!("<< SegmentTree[i].m.f << ", " << SegmentTree[i].m.s << "), (" << SegmentTree[i].s.f << ", " << SegmentTree[i].s.s << ")!!)" << " ";
    }
    cout << endl;
    return;
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
    SegmentTree[2 * v + 1].m.f += SegmentTree[v].s.s;
    SegmentTree[2 * v + 1].s.f = 1;
    SegmentTree[2 * v + 1].s.s += SegmentTree[v].s.s;
    SegmentTree[2 * v + 2].m.f += SegmentTree[v].s.s;
    SegmentTree[2 * v + 2].s.f = 1;
    SegmentTree[2 * v + 2].s.s += SegmentTree[v].s.s;
    SegmentTree[v].s.f = 0;
    SegmentTree[v].s.s = 0;
    return;
}

void build(int v, int vl, int vr)
{
    if (vr - vl == 1)
    {
        SegmentTree[v].m.s = vl;
        return;
    }
    int vm = (vl + vr) / 2;
    build(2 * v + 1, vl, vm);
    build(2 * v + 2, vm, vr);
    SegmentTree[v] = SegmentTree[2 * v + 1];
}

void sum(int v, int vl, int vr, int l, int r, int c)
{
    if (l >= vr || r <= vl)
    {
        return;
    }
    if (l <= vl && vr <= r)
    {
        SegmentTree[v].m.f += c;
        SegmentTree[v].s.f = 1;
        SegmentTree[v].s.s += c;
        return;
    }
    propagate(v, vl, vr);
    int vm = (vr + vl) / 2;
    sum(2 * v + 1, vl, vm, l, r, c);
    sum(2 * v + 2, vm, vr, l, r, c);
    if (SegmentTree[2 * v + 1].m.f > SegmentTree[2 * v + 2].m.f)
    {
        SegmentTree[v].m = SegmentTree[2 * v + 1].m;
    }
    else
    {
        SegmentTree[v].m = SegmentTree[2 * v + 2].m;
    }
    return;
}

my_pair max_el(int v, int vl, int vr, int l, int r)
{
    if (l >= vr || r <= vl)
    {
        return my_pair(-1, 0);
    }
    if (l <= vl && vr <= r)
    {
        return SegmentTree[v].m;
    }
    propagate(v, vl, vr);
    int vm = (vr + vl) / 2;
    my_pair f = max_el(2 * v + 1, vl, vm, l, r);
    my_pair s = max_el(2 * v + 2, vm, vr, l, r);
    return f.f > s.f ? f : s;
}

bool cmp(const point& f, const point& s)
{
    return f.x < s.x || (f.x == s.x && f.t < s.t);
}

int main()
{
    int n;
    cin >> n;
    vector<point> points(2 * n);
    for (int i = 0; i < 2 * n; i += 2)
    {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 += sm;
        y1 += sm;
        x2 += sm;
        y2 += sm;
        points[i] = point(x1, y1, y2, 0);
        points[i + 1] = point(x2, y1, y2, 1);
    }
    sort(points.begin(), points.end(), cmp);
    build(0, 0, bz);
    int max_ans = 0;
    int x = 0, y = 0;
    //out();
    for (int i = 0; i < 2 * n; i++)
    {
        if (points[i].t == 0)
        {
            sum(0, 0, bz, points[i].y1, points[i].y2 + 1, 1);
            //cout << points[i].y1  << " " <<  points[i].y2 + 1 << " " << 1 << endl;
        }
        my_pair ans = max_el(0, 0, bz, points[i].y1, points[i].y2 + 1);
        if (ans.f > max_ans)
        {
            max_ans = ans.f;
            x = points[i].x;
            y = ans.s;
        }
        if (points[i].t == 1)
        {
            sum(0, 0, bz, points[i].y1, points[i].y2 + 1, -1);
        }
        //out();
    }
    cout << max_ans << '\n' << x - sm << " " << y - sm;
}
