#include <bits/stdc++.h>

using namespace std;

long long merges(vector<long long> &a, long long l, long long m, long long r)
{
    vector<long long> result(r - l);
    long long i = l, j = m;
    long long ans = 0;
    while (i != m && j != r)
    {
        if (a[i] <= a[j])
        {
            result[i + j - m - l] = a[i];
            i++;
        }
        else
        {
            result[i + j - m - l] = a[j];
            j++;
            ans += (m - i);
        }
    }
    while (i != m)
    {
        result[i + j - m - l] = a[i];
        i++;
    }
    while (j != r)
    {
        result[i + j - m - l] = a[j];
        j++;
    }
    for (i = l; i < r; i++)
        a[i] = result[i - l];
    return ans;
}

int main()
{
    long long n;
    cin >> n;
    vector<long long> a(n);
    for (long long i = 0; i < n; i++)
        cin >> a[i];
    long long ans = 0;
    for (long long i = 1; i < n ; i *= 2)
    {
        for (long long j = 0; j <= n - i; j = j + 2 * i)
        {
            ans += merges(a, j, j + i, min(j + 2 * i, n));
        }
    }
    cout << ans << endl;
    return 0;
}
