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

node* ins1 (node *root, int x)
{
    if (root == nullptr)
    {
        root = new node(x);
        return root;
    }
    if (root -> x < x)
    {
        root -> right = ins1(root -> right, x);
    }
    if (root -> x > x)
    {
        root -> left = ins1(root -> left, x);
    }
    return root;
}

node* del1(node *root, int x)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    if (root -> x < x)
    {
        root -> right = del1(root -> right, x);
        return root;
    }
    if (root -> x > x)
    {
        root -> left = del1(root -> left, x);
        return root;
    }
    node *rl = prev(root, root -> x);
    node *rr = next(root, root -> x);
    if (rl == rr && rr == nullptr)
    {
        delete root;
        return nullptr;
    }
    if (rl != nullptr)
    {
        root -> x = rl -> x;
        root -> left = del1(root -> left, root -> x);
    }
    else
    {
        root -> x = rr -> x;
        root -> right = del1(root -> right, root -> x);
    }
    return root;
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
    if (root -> x == nd -> x)
        return root;
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

node* del(node *root, int x)
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
    node *root = nullptr;
    node *root1 = nullptr;
    cout << std::boolalpha;
    while (true)
    {
        int op = rand() % 5;
        int x = rand() % 100;
        cout << op << " " << x << endl;
        if (op == 0)
        {
            root = ins(root, new node(x));
            root1 = ins1(root1, x);
        }
        if (op == 1)
        {
            root = del(root, x);
            root1 = del1(root1, x);
        }
        if (op == 2)
        {
            if (exist(root, x) != exist(root1, x))
            {
                int c;
                cin >> c;
            }
        }
        if (op == 3 || op == 4)
        {
            node *ans = nullptr;
            node *ans1 = nullptr;
            if (op == 3)
            {
                ans = next(root, x);
                ans1 = next(root1, x);
            }
            else
            {
                ans = prev(root, x);
                ans1 = prev(root1, x);
            }
            if (ans != ans1)
            {
                int c;
                cin >> c;
            }
        }
    }
}



