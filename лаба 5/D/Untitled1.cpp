#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

struct node
{

    long long x;
    long long y;
    long long sum;

    node * left;
    node * right;

    node(long long val)
    {
        x = val;
        y = rand();
        sum = val;
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

long long get_sum (node * root)
{
    return (root == nullptr ? 0 : root -> sum);
}

void updata(node * root)
{
    root -> sum = get_sum(root -> left) + get_sum(root -> right) + root -> x;
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
    if (first == nullptr) return second;
    if (second  == nullptr) return first;
    if (first -> y > second -> y) {
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
    if (root == nullptr) {
        return nd;
    }
    if (root -> y > nd -> y) {
        if (root -> x < nd -> x){
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

long long ans(node *&root, long long a, long long b)
{
    auto res1 = split(root, a);
    auto res2 = split(res1.second, b);
    long long ans = get_sum(res2.first);
    root = merge(res1.first, merge(res2.first, res2.second));
    return ans;
}

int main()
{
    node * root = nullptr;
    long long n;
    cin >> n;
    bool zn = false;
    long long prev = 0;
    for (long long i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        if (c == '+')
        {
            long long x;
            cin >> x;
            if (zn)
                x = (x + prev) % (1000000000);
            zn = false;
            if (!exist(root, x))
                root = add(root, new node(x));
        }
        else
        {
            long long a, b;
            cin >> a >> b;
            if (b < a)
                swap(a, b);
            zn = true;
            prev = ans(root, a, b + 1);
            cout << prev << endl;
        }
    }
}
