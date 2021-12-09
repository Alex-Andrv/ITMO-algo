#include <bits/stdc++.h>

using namespace std;

struct node
{
    node *left;
    node *right;
    int x;
    int y;
    node (int val = 0)
    {
        x = val;
        y = rand();
        left = nullptr;
        right = nullptr;
    }

};


bool exist(node *root, int x)
{
    if (root == nullptr)
        return false;
    if (root -> x == x)
        return true;
    if (root -> x > x)
        return exist(root -> left, x);
    return exist(root -> right, x);
}

node * prev(node *root, int x)
{
    if (root == nullptr)
        return nullptr;
    if (root -> x >= x)
        return prev(root -> left, x);
    node *ans = prev(root -> right, x);
    if (ans == nullptr || ans -> x < root -> x)
        return root;
    else
        return ans;
}

node * next(node *root, int x)
{
    if (root == nullptr)
        return nullptr;
    if (root -> x <= x)
        return next(root -> right, x);
    node *ans = next(root -> left, x);
    if (ans == nullptr || ans -> x > root -> x)
        return root;
    else
        return ans;
}

pair<node *, node *> split (node * root, int x)
{
    if (root == nullptr)
    {
        return {nullptr, nullptr};
    }
    if (root -> x < x)
    {
        pair<node *, node*> ans = split(root -> right, x);
        root -> right = ans.first;
        return {root, ans.second};
    }
    pair<node *, node*> ans = split(root -> left, x);
    root -> left = ans.second;
    return {ans.first, root};
}

node * merge(node * first, node * second)
{
    if (first == nullptr)
        return second;
    if (second == nullptr)
        return first;
    if (first -> y > second -> y)
    {
        first -> right = merge(first -> right, second);
        return first;
    }
    second -> left = merge(first, second -> left);
    return second;
}

node* ins (node *root, node *nd)
{
    if (root == nullptr)
        return nd;
    if (root -> y < nd -> y)
    {
        auto res = split(root, nd -> x);
        nd -> left = res.first;
        nd -> right = res.second;
        return nd;
    }
    if (root -> x < nd -> x)
    {
        root -> right = ins(root -> right, nd);
        return root;
    }
    root -> left = ins(root -> left, nd);
    return root;
}

node* del (node *root, int x)
{
    if (root == nullptr)
        return nullptr;
    if (root -> x == x)
    {
        auto ans = merge(root -> left, root -> right);
        delete root;
        return ans;
    }
    if (root -> x < x)
    {
        root -> right = del(root -> right, x);
        return root;
    }
    root -> left = del(root -> left, x);
    return root;
}

int main()
{
    string op;
    node *root = nullptr;
    cout << std::boolalpha;
    while (cin >> op)
    {
        int x;
        cin >> x;
        if (op == "insert")
        {
            if (!exist(root, x))
                root = ins(root, new node(x));
        }
        if (op == "delete")
        {
            root = del(root, x);
        }
        if (op == "exists")
        {
            cout << exist(root, x) << endl;
        }
        if (op == "next" || op == "prev")
        {
            node *ans = nullptr;
            if (op == "next")
                ans = next(root, x);
            else
                ans = prev(root, x);
            if (ans == nullptr)
                cout << "none" << endl;
            else
                cout << ans -> x << endl;
        }
    }
}


