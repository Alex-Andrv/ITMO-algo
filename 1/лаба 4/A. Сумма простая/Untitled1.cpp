#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n, x, y, a0;
    cin >> n >> x >> y >> a0;
    vector<long long> a(n + 1);
    a[0] = 0;
    a[1] = a0;
    for (long long i = 2; i < a.size(); i++)
    {
        a[i] = (x * a[i - 1] % (1 << 16) + y) % (1 << 16);
    }
    for (int i = 1; i < a.size(); i++)
    {
         a[i] = a[i - 1] + a[i];
    }
    long long m, z, t, b0;
    cin >> m >> z >> t >> b0;
    if (t == -1)
    {
        t = (1 << 30) - 1;
    }
    if (m == 0)
    {
        cout << 0;
        return 0;
    }
    vector<long long> b(2 * m);
    b[0] = b0;
    for (long long i = 1; i < b.size(); i++)
    {
        b[i] = (z * b[i - 1] % (1 << 30) + t) % (1 << 30);
    }
    for (long long i = 0; i < b.size(); i++)
    {
        b[i] = b[i] % n;
    }
    long long sum = 0;
    for (long long i = 0; i < m; i++)
    {
        long long left = min(b[2 * i], b[2 * i + 1]);
        long long right = max(b[2 * i], b[2 * i + 1]);
        sum += (a[right + 1] - a[left]);
    }
    cout << sum;
}
