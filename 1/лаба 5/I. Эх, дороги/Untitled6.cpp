#include <bits/stdc++.h>

using namespace std;

struct node
{

    int x;
    int y;
    int k;
    bool rev;
    bool circle;

    node * left;
    node * right;
    node * parent;

    node(int val)
    {
        circle = false;
        rev = false;
        x = val;
        y = rand();
        k = 1;
        parent = left = right = nullptr;
    }
};

void push(node * root)
{
    if (root != nullptr && root -> rev)
    {
        root -> rev = false;
        swap(root -> left, root -> right);
        if (root -> left)
            root -> left -> rev ^= true;
        if (root -> right)
            root -> right -> rev ^= true;
    }
}

void println(node * root)
{
    if (root == nullptr)
    {
        return;
    }
    push(root);
    println(root -> rev ? root -> right : root -> left);
    cout << root -> x << " ";
    println(root -> rev ? root -> left : root -> right);
}

int get_k (node * root)
{
    return (root == nullptr ? 0 : root -> k);
}

void updata(node * root)
{
    if (root == nullptr)
        return;
    root -> k = get_k(root -> left) + get_k(root -> right) + 1;
    if (root -> left)
        root -> left -> parent = root;
    if (root -> right)
        root -> right -> parent = root;
    return;
}

pair<node *, node*> split (node * root, int k)
{
    if (root == nullptr)
    {
        return {nullptr, nullptr};
    }
    push(root);
    if (get_k(root -> left) + 1 < k)
    {
        auto res = split(root -> right, k - get_k(root -> left) - 1);
        root -> right  = res.first;
        updata(root);
        if (res.second != nullptr)
            res.second -> parent = nullptr;
        return {root, res.second};
    }
    auto res = split(root -> left, k);
    root -> left  = res.second;
    updata(root);
    if (res.first != nullptr)
        res.first -> parent = nullptr;
    return {res.first, root};
}

node * merge(node * first, node * second)
{
    if (first == nullptr)
        return second;
    if (second == nullptr)
        return first;
    if (first -> y > second -> y)
    {
        push(first);
        first -> right = merge(first -> right, second);
        updata(first);
        return first;
    }
    push(second);
    second -> left = merge(first, second -> left);
    updata(second);
    return second;
}


node * sw(node * root)
{
    root -> rev = !root -> rev;
    return root;
}


node * find(node * son, int & k)
{
    k = (!son -> rev ? get_k(son -> left) : get_k(son -> right)) + 1;
    while (son -> parent != nullptr)
    {
        if (son == son -> parent -> right && !son -> parent -> rev)
            k = k + (get_k(son -> parent -> left) + 1);
        if (son -> parent -> rev)
            k = (get_k(son) - k + 1);
        if (son == son -> parent -> left && son -> parent -> rev)
            k = k + (get_k(son -> parent -> right) + 1);
        son = son -> parent;
    }
    return son;
}


void add(node * first, node * second)
{
    int k1, k2;
    k1 = k2 = 0;
    node * root_first = find(first, k1);
    node * root_second = find(second, k2);
    if (root_first == root_second)
    {
        root_first -> circle = true;
        return;
    }
    if (k2 == 1 && k1 != 1)
    {
        merge(root_first, root_second);
    }
    if (k1 == 1 && k2 != 1)
    {
        merge(root_second, root_first);
    }
    if (k1 == 1 && k2 == 1)
    {
        root_first = sw(root_first);
        merge(root_first, root_second);
    }
    if (k1 != 1 && k2 != 1)
    {
        root_first = sw(root_first);
        merge(root_second, root_first);
    }
}

void remove(node * first, node * second)
{
    int k1, k2;
    k1 = k2 = 0;
    node * root_first = find(first, k1);
    node * root_second = find(second, k2);
    if (root_first -> circle)
    {
        root_first -> circle = false;
        auto res = split(root_first, min(k1, k2) + 1);
        if (min(k1, k2) == 1 && max(k1, k2) != 2)
            merge(res.first, res.second);
        else
            merge(res.second, res.first);
    }
    else
    {
        split(root_first, min(k1, k2) + 1);
    }
}




int main()
{
    node * root = nullptr;
    int n, m, q;
    cin >> n >> m >> q;
    vector<node *> forest(n);
    for (int i = 0; i < n; i++)
    {
        forest[i] = new node(i + 1);
    }
    for (int i = 0; i < m; i++)
    {
        int f, s;
        cin >> f >> s;
        add(forest[f - 1], forest[s - 1]);
    }
    for (int i = 0; i < q; i++)
    {
        char c;
        cin >> c;
        int f, s;
        cin >> f >> s;
        if (c == '+')
        {
            add(forest[f - 1], forest[s - 1]);
        }
        if (c == '-')
        {
            if (s == f)
                continue;
            remove(forest[f - 1], forest[s - 1]);
        }
        if (c == '?')
        {
            if (f == s) {
                cout << "0" << endl;
                continue;
            }
            int k1 = 0;
            int k2 = 0;
            node * root_first = find(forest[f - 1], k1);
            node * root_second = find(forest[s - 1], k2);
            if (root_first != root_second)
            {
                cout << "-1" << endl;
            }
            else
            {
                int rast = abs(k2 - k1) - 1;
                if (root_first -> circle)
                    cout << min(rast, get_k(root_first) - rast - 2) << endl;
                else
                    cout << rast << endl;
            }
        }
    }
}

