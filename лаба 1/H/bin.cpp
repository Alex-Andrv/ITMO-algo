 #include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n, w, h;
    cin >> w >> h >> n;
    long long l = 0, r = max(w, h) * n;
    while (r - l > 1)
    {
        long long mid = (l + r) / 2;
        if ((mid / w) * (mid / h) < n)
            l = mid;
        else
            r = mid;
    }
    cout << r;
}
