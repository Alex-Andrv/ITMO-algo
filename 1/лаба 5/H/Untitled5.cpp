#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

struct node
{

    int x;
    int y;
    int k;
    bool rev;

    node * left;
    node * right;

    node(int val)
    {
        rev = false;
        x = val;
        y = rand();
        k = 1;
        left = right = nullptr;
    }
};

void push(node * root)
{
    if (root != nullptr && root -> rev) {
        root -> rev = false;
        swap(root -> left, root -> right);
        if (root -> left) root -> left -> rev ^= true;
        if (root -> right) root -> right -> rev ^= true;
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


node * sw(node * root, int l, int r)
{
    auto res = split(root, l);
    auto res2 = split(res.second, r - l + 1);
    res2.first -> rev = !res2.first -> rev;
    root = merge(res.first, merge(res2.first, res2.second));
    return root;
}

int main()
{
    node * root = nullptr;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        root = merge(root, new node(i + 1));
    }
    for (int i = 0; i < m; i++)
    {
        int l, r;
        cin >> l >> r;
        root = sw(root, l, r + 1);
    }
    println(root);
}

