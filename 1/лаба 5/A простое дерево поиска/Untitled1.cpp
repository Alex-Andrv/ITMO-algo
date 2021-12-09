#include <bits/stdc++.h>

using namespace std;

struct node
{
    node *left;
    node *right;
    int x;
    //int y;
    node (int val = 0)
    {
        x = val;
        //y = rand();
        left = nullptr;
        right = nullptr;
    }

    ~node ()
    {
        if (left)
            delete left;
        if (right)
            delete right;
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

node* ins (node *root, int x)
{
    if (root == nullptr)
    {
        root = new node(x);
        return root;
    }
    if (root -> x < x)
    {
        root -> right = ins(root -> right, x);
    }
    if (root -> x > x)
    {
        root -> left = ins(root -> left, x);
    }
    return root;
}

node* del (node *root, int x)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    if (root -> x < x)
    {
        root -> right = del(root -> right, x);
        return root;
    }
    if (root -> x > x)
    {
        root -> left = del(root -> left, x);
        return root;
    }
    node *rl = prev (root, root -> x);
    node *rr = next (root, root -> x);
    if (rl == rr && rr == nullptr)
    {
        delete root;
        return nullptr;
    }
    if (rl != nullptr)
    {
        root -> x = rl -> x;
        root -> left = del (root -> left, root -> x);
    }
    else
    {
        root -> x = rr -> x;
        root -> right = del (root -> right, root -> x);
    }
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
            root = ins(root, x);
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
