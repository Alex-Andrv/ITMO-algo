#include <bits/stdc++.h>

using namespace std;


struct node
{
    node *left;
    node *right;
    int sum;
    int max_pref;
    int sc;
    int zn;
    node(node *left1 = nullptr, node *right1 = nullptr, int sum1 = 0, int max_pref1 = 0, int sc1 = 0, int zn1 = 0)
    {
        left = left1;
        right = right1;
        sum = sum1;
        max_pref = max_pref1;
        sc = sc1;
        zn = zn1;
    }
};

void propagate(node *root, unsigned int vl, unsigned int vr)
{
    if (vr - vl == 1)
    {
        return;
    }
    if (root -> left == nullptr)
    {
        root -> left = new node(nullptr, nullptr, 0, 0, 0);
    }
    if (root -> right == nullptr)
    {
        root -> right = new node(nullptr, nullptr, 0, 0, 0);
    }
    if (root -> sc == 0)
    {
        return;
    }
    root -> left -> sc = root -> right -> sc = 1;
    root -> left -> zn = root -> right -> zn = root -> zn;
    int vm = (vl + vr) / 2;
    root -> left -> sum = (vm - vl) * root -> zn;
    root -> right -> sum = (vr - vm) * root -> zn;
    root -> left -> max_pref = max(0, root -> left -> sum);
    root -> right -> max_pref = max(0, root -> right -> sum);
    root -> zn = root -> sc = 0;
    return;
}

void set_el(node* root, unsigned int vl, unsigned int vr, int l, int r, int c)
{
    if (l >= vr || r <= vl)
    {
        return;
    }
    if (l <= vl && vr <= r)
    {
        root -> sum = (vr - vl) * c;
        root -> max_pref = max(0, root -> sum);
        root -> sc = 1;
        root -> zn = c;
        return;
    }
    propagate(root, vl, vr);
    unsigned int vm = (vl + vr) / 2;
    set_el(root -> left, vl, vm, l, r, c);
    set_el(root -> right, vm, vr, l, r, c);
    root -> sum = root -> left -> sum + root -> right -> sum;
    root -> max_pref = max(root -> left -> max_pref, root -> left -> sum + root -> right -> max_pref);
    return;
}

unsigned int get_pos(node* root, unsigned int vl, unsigned int vr, int h)
{
    if (vr - vl == 1)
    {
        if (root -> max_pref <= h)
        {
            return vl;
        }
        else
        {
            return vl - 1;
        }
    }
    if (root -> max_pref <= h)
    {
        return vr;
    }
    propagate(root, vl, vr);
    int vm = (vl + vr) / 2;
    if (root -> left -> max_pref > h)
    {
        return get_pos(root -> left, vl, vm, h);
    }
    return get_pos(root -> right, vm, vr, h - root -> left -> sum);
}

int main()
{
    unsigned int n;
    cin >> n;
    unsigned int bz = 1;
    while (bz < n)
    {
        bz *= 2;
    }
    node root = node(nullptr, nullptr, 0, 0);
    char c;
    cin >> c;
    while (c != 'E')
    {
        if (c == 'I')
        {
            unsigned int l, r;
            int q;
            cin >> l >> r >> q;
            set_el(&root, 0, bz, --l, r, q);
        }
        else
        {
            int h;
            cin >> h;
            cout << min(get_pos(&root, 0, bz, h) + 1, n) << '\n';
        }
        cin >> c;
    }
}
