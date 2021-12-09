#include <bits/stdc++.h>

#define LL long long

using namespace std;

struct nodes
{
    int a11;
    int a12;
    int a21;
    int a22;
    nodes (int a = 0, int b = 0, int c = 0, int d = 0)
    {
        a11 = a;
        a12 = b;
        a21 = c;
        a22 = d;
    }
};

vector<nodes> SegmentTree;

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
        cout << "("<< SegmentTree[i].a11 << ", " << SegmentTree[i].a12 << ", " << SegmentTree[i].a21 << ", " << SegmentTree[i].a22 << ") ";
    }
    cout << endl;
    return;
}

int r;

nodes mult(nodes a, nodes b)
{
    return nodes((a.a11 * b.a11 % r + a.a12 * b.a21 % r) % r, (a.a11 * b.a12 % r + a.a12 * b.a22 % r) % r, (a.a21 * b.a11 % r + a.a22 * b.a21 % r) % r, (a.a21 * b.a12 % r + a.a22 * b.a22 % r) % r);
}

void build(int v, int vl, int vr)
{
    if (vr - vl == 1)
    {
        return;
    }
    int vm = (vl + vr) / 2;
    build (2 * v + 1, vl, vm);
    build (2 * v + 2, vm, vr);
    SegmentTree[v] = mult(SegmentTree[2 * v + 1], SegmentTree[2 * v + 2]);
}

nodes mult(int v, int vl, int vr, int l, int r)
{
    if (l <= vl && r >= vr)
    {
        return SegmentTree[v];
    }
    int vm = (vl + vr) / 2;
    if (r <= vm)
    {
        return mult(2 * v + 1, vl, vm, l, r);
    }
    if (l >= vm)
    {
        return mult(2 * v + 2, vm, vr, l, r);
    }
    return mult(mult(2 * v + 1, vl, vm, l, r), mult(2 * v + 2, vm, vr, l, r));
}



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream fin("crypto.in");
    ofstream fout("crypto.out");
    int n, m;
    fin >> r >> n >> m;
    int bn = 1;
    while (bn < n)
    {
        bn *= 2;
    }
    SegmentTree.resize(2 * bn);
    for (int i = 0; i < n; i++)
    {
        fin >> SegmentTree[bn - 1 + i].a11 >> SegmentTree[bn - 1 + i].a12 >> SegmentTree[bn - 1 + i].a21 >> SegmentTree[bn - 1 + i].a22;
    }
    build(0, 0, bn);
    //out();
    for (int i = 0; i < m; i++)
    {
        int l, r;
        fin >> l >> r;
        nodes ans = mult(0, 0, bn, --l, r);
       // cout << "stert " << endl;
        fout << ans.a11 << " " << ans.a12 << "\n";
        fout << ans.a21 << " " << ans.a22 << "\n";
        fout << "\n";
    }
    fin.close();
    fout.close();
}


