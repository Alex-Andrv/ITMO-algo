#include <bits/stdc++.h>

using namespace std;

const long double e = 1e-9;

int main()
{
    long double c;
    cin >> c;
    long double l = 0, r = c;
    while (r - l >= e)
    {
        long double mid = l / 2 + r / 2;
        if (mid * mid + sqrt(mid) < c )
            l = mid;
        else
            r = mid;
    }
    cout << fixed << setprecision(6) << r;
}
