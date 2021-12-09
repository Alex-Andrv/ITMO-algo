#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n;
    cin >> n;
    long long x, y;
    cin >> x >> y;
    if (x > y) swap(x, y);
    long long ans = n * y;
    n--;
    long long l = -1, r = n * y;
    while (r - l > 1)
    {
        long long mid = (l + r) / 2;
        if (mid / y + mid / x < n)
            l = mid;
        else
            r = mid;
    }
    cout << r + x;
}
