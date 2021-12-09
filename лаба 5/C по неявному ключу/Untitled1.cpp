#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

struct node
{

    int x;
    int y;
    int k;
    bool here_is_zero;

    node * left;
    node * right;

    node(int val)
    {
        here_is_zero = (val == 0 ? true : false);
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

bool zero(node * root)
{
    return (root == nullptr ? false : root -> here_is_zero);
}


void updata(node * root)
{
    root -> k = get_k(root -> left) + get_k(root -> right) + 1;
    root -> here_is_zero = zero(root -> left) || zero(root -> right) || (root -> x == 0);
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

int find_zero(node * root)
{
    if (zero(root -> left))
        return find_zero(root -> left);
    if (root -> x == 0)
        return get_k(root -> left) + 1;
    return get_k(root -> left) + 1 + find_zero(root -> right);
}

node * delete_zero(node * root)
{
    int pos_zero = find_zero(root);
    auto res1 = split(root, pos_zero);
    auto res2 = split(res1.second, 2);
    delete res2.first;
    return merge(res1.first, res2.second);
}

node * add(node * root, int k, node * nd)
{
    auto res = split(root, k);
    if (res.second -> here_is_zero)
    {
        res.second = delete_zero(res.second);
        //updata(res.second);
    }
    return merge(merge(res.first, nd), res.second);
}

int main()
{
    node * root = nullptr;
    int n, m;
    cin >> n >> m;
    m = 0;
    vector<int> al;
    for (int i = 0; i < n; i++)
    {
        int l;
        cin >> l;
        al.push_back(l);
        m = max(m, l);
    }
    for (int i = 0; i < m; i++)
    {
        root = merge(root, new node(0));
    }
    for (int i = 0; i < n; i++)
    {
        root = add(root, al[i], new node(i + 1));
    }
    node * r = root;
    cout << root -> k << endl;
    println(root);
}
