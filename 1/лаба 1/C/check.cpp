#include <bits/stdc++.h>

using namespace std;

int slow(vector<int> &a,int n)
{
    int ans = 0;
    for (int i = 1; i < n ; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (a[i] < a[j])
                ans++;
        }
    }
    return ans;
}

int merges(vector<int> &a, int l, int m, int r)
{
    vector<int> result(r - l);
    int i = l, j = m;
    int ans = 0;
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

int fast(vector<int> a, int n)
{
    int ans = 0;
    for (int i = 1; i < n ; i *= 2)
    {
        for (int j = 0; j <= n - i; j = j + 2 * i)
        {
            ans += merges(a, j, j + i, min(j + 2 * i, n));
        }
    }
    return ans;
}
int main()
{
    while (true)
    {
        srand(time(0));
        int n = abs(rand() % 10000);
        vector<int> a(n);
        for (int i = 0; i < n; i++)
            a[i] = rand();
        vector<int> b = a;
        int ansf = fast(a, n);
        int anss = slow(b, n);
        if (ansf == anss)
            cout << "YES";
        else
        {
            cout << "PIS";
        }

    }
}
