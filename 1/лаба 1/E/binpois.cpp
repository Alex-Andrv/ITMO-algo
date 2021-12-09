#include <bits/stdc++.h>

using namespace std;

void qsort (vector<int> &a, int l, int r)
{
    int mid = a[(l + r) / 2];
    int i = l, j = r;
    while (i <= j)
    {
       while (mid > a[i]) i++;
       while (mid < a[j]) j--;
       if (i <= j)
       {
            swap(a[i], a[j]);
            i++;
            j--;
       }
    }
    if (l < j)
        qsort(a, l, j);
    if (i < r)
        qsort(a, i, r);
}

int lower(vector<int> &a, int in)
{
    int l = 0;
    int r = a.size();
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        if (a[mid] < in)
            l = mid;
        else
            r = mid;
    }
    return l;
}

int upper(vector<int> &a, int in)
{
    int l = 0;
    int r = a.size();
    while (r - l > 1)
    {
        int mid = (l + r) / 2;
        if (a[mid] <= in)
            l = mid;
        else
            r = mid;
    }
    return l;
}

int main()
{
    int n;
    cin >> n;
    vector<int> mas(n + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> mas[i];
    }
    mas[n] = -1e9 - 1;
    qsort(mas, 0, n);
    int k;
    cin >> k;
    for (int i = 0; i < k; i++)
    {
        int l, r;
        cin >> l >> r;
        cout << upper(mas, r) - lower(mas, l)<< " ";
    }
}
