#include <bits/stdc++.h>

using namespace std;

long double  mid;

struct kBest
{
    int v;
    int w;
    int in;
    kBest(int vi = 0, int wi = 0, int ind = 0)
    {
        v = vi;
        w = wi;
        in = ind;
    }
};

bool cmp(const kBest &a, const kBest &b)
{
    return (a.v * 1. - mid * a.w) < (b.v * 1. - mid * b.w);
}

bool isit (vector<kBest> &arr, int &k)
{
    sort(arr.rbegin(), arr.rend(), cmp);
    double sum = 0;
    for (int i = 0; i < k; i++)
        sum = sum + (arr[i].v * 1. - arr[i].w * mid);
    if (sum >= 0)
        return true;
    else
        return false;
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<kBest> arr;
    for (int i = 0; i < n; i++)
    {
        int v, w;
        cin >> v >> w;
        arr.push_back(kBest(v, w, i + 1));
    }
    long double  l = 0, r = 1e7;
    for (int i = 0; i < 100; i++)
    {
        mid = (l + r) / 2;
        if (isit(arr, k))
            l = mid;
        else
            r = mid;
    }
    mid = l;
    sort(arr.rbegin(), arr.rend(), cmp);
    for (int i = 0; i < k; i++)
        cout << arr[i].in << " ";
}
