#include <bits/stdc++.h>

using namespace std;

long long lower(vector<long long> &a, long long in)
{
    long long l = 0;
    long long r = a.size();
    while (r - l > 1)
    {
        long long mid = (l + r) / 2;
        if (a[mid] < in)
            l = mid;
        else
            r = mid;
    }
    return a[l];
}

long long upper(vector<long long> &a, long long in)
{
    long long l = 0;
    long long r = a.size() - 1;
    while (r - l > 1)
    {
        long long mid = (l + r) / 2;
        if (a[mid] < in)
            l = mid;
        else
            r = mid;
    }
    return a[r];
}


int main()
{
    long long n, m;
    cin >> n >> m;
    vector<long long> a(n);
    for (long long i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for (long long i = 0; i < m; i++)
    {
        long long value;
        cin >> value;
        long long x1 = lower(a, value);
        long long x2 = upper(a, value);
        if (abs(value - x1) <= abs(value - x2))
            cout << x1 << endl;
        else
            cout << x2 << endl;
    }
}
