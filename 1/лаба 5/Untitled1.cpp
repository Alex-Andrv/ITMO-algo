#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

struct node
{

    long long x;
    long long y;
    long long k;

    node * left;
    node * right;

    node(long long val)
    {
        x = val;
        y = rand();
        k = 1;
        left = right = nullptr;
    }

    ~node()
    {
        delete left;
        delete right;
    }
};

bool exist(node *root, long long x)
{
    if (root == nullptr)
        return false;
    if (root -> x == x)
        return true;
    if (root -> x > x)
        return exist(root -> left, x);
    return exist(root -> right, x);
}

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

long long get_k(node * root)
{
    return (root == nullptr ? 0 : root -> k);
}

void updata(node * root)
{
    root -> k = get_k(root -> left) + get_k(root -> right) + 1;
    return;
}

pair<node *, node*> split (node * root, long long x)
{
    if (root == nullptr)
    {
        return {nullptr, nullptr};
    }
    if (root -> x < x)
    {
        auto res = split(root -> right, x);
        root -> right = res.first;
        updata(root);
        return {root, res.second};
    }
    auto res = split(root -> left, x);
    root -> left = res.second;
    updata(root);
    return {res.first, root};
}

node * merge(node * first, node * second)
{
    if (first == nullptr)
        return second;
    if (second  == nullptr)
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

node * add(node * root, node * nd)
{
    if (root == nullptr)
    {
        return nd;
    }
    if (root -> y > nd -> y)
    {
        if (root -> x < nd -> x)
        {
            root -> right = add(root -> right, nd);
            updata(root);
            return root;
        }
        root -> left = add(root -> left, nd);
        updata(root);
        return root;
    }
    auto res = split(root, nd -> x);
    nd -> left = res.first;
    nd -> right = res.second;
    updata(nd);
    return nd;
}

long long find(node * root, long long k) {
    if (get_k(root -> right) >= k)
    {
        return find(root -> right, k);
    }
    if (get_k(root -> right) + 1 == k)
    {
        return root -> x;
    }
    return find(root -> left, k - get_k(root -> right) - 1);
}

void remove(node *&root, long long x)
{
    if (root -> x < x) {
        remove(root -> right, x);
    } else if (root -> x > x) {
        remove(root -> left, x);
    } else {
        root = merge(root -> left, root -> right);
    }
}

int main()
{
    node * root = nullptr;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int zn;
        cin >> zn;
        if (zn == 1)
        {
            long long x;
            cin >> x;
            root = add(root, new node(x));
        }
        if (zn == -1)
        {
            long long x;
            cin >> x;
            remove(root, x);
        }
        if (zn == 0)
        {
            long long x;
            cin >> x;
            cout << find(root, x) << endl;
        }
    }
}

