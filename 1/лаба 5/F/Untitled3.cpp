#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

struct node
{

    int x;
    int y;
    int k;

    node * left;
    node * right;

    node(int val)
    {
        x = val;
        y = rand();
        k = 1;
        left = right = nullptr;
    }
};


void println(node * root)
{
    if (root == nullptr)
    {
        return;
    }
    println(root -> left);
    cout << root -> x << " ";
    println(root -> right);
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
    return;
}

pair<node *, node*> split (node * root, int k)
{
    if (root == nullptr)
    {
        return {nullptr, nullptr};
    }
    if (get_k(root -> left) + 1 < k)
    {
        auto res = split(root -> right, k - get_k(root -> left) - 1);
        root -> right  = res.first;
        updata(root);
        return {root, res.second};
    }
    auto res = split(root -> left, k);
    root -> left  = res.second;
    updata(root);
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
        first -> right = merge(first -> right, second);
        updata(first);
        return first;
    }
    second -> left = merge(first, second -> left);
    updata(second);
    return second;
}

node * add(node * root, int k, node * nd)
{
    if (root == nullptr)
    {
        return nd;
    }
    if (root -> y < nd -> y)
    {
        if (get_k(root -> left) + 1 >= k)
        {
            root -> left = add(root -> left, k, nd);
            updata(root);
            return root;
        }
        else
        {
            root -> right = add(root -> right, k - 1 - get_k(root -> left), nd);
            updata(root);
            return root;
        }
    }
    auto res = split(root, k);
    nd -> left = res.first;
    nd -> right = res.second;
    updata(nd);
    return nd;
}

node * del(node * root, int k)
{
    if (get_k(root -> left) + 1 > k)
    {
        root -> left = del(root -> left, k);
        updata(root);
        return root;
    }
    else if (get_k(root -> left) + 1 < k)
    {
        root -> right = del(root -> right, k - get_k(root -> left) - 1);
        updata(root);
        return root;
    }
    return merge(root -> left, root -> right);
}

int main()
{
    node * root = nullptr;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        root = merge(root, new node(x));
    }
    for (int i = 0; i < m; i++)
    {
        string com;
        cin >> com;
        if (com == "add")
        {
            int k, x;
            cin >> k >> x;
            root = add(root, k + 1, new node(x));
        }
        else
        {
            int x;
            cin >> x;
            root = del(root, x);
        }
    }
    cout << get_k(root) << endl;
    println(root);
}

