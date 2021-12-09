#include <bits/stdc++.h>

using namespace std;

struct kBest
{
    long double v;
    long double w;
    long double in;
    kBest(long double vi = 0, long double wi = 0, long double ind = 0)
    {
        v = vi;
        w = wi;
        in = ind;
    }
};

bool cmp(const kBest &a, const kBest &b)
{
    return (a.v / a.w) < (b.v / b.w);
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<kBest> arr;
    for (int i = 0; i < n; i++)
    {
        long double v, w;
        cin >> v >> w;
        arr.push_back(kBest(v, w, i + 1));
    }
    sort(arr.rbegin(), arr.rend(), cmp);
    for (int i = 0; i < k ; i++)
        cout << arr[i].in << " ";
}
