#include <bits/stdc++.h>

using namespace std;

void qsort(int *arr, int l, int r)
{
    int q = arr[(l + r) / 2];
    int i = l, j = r;
    while (i <= j)
    {
        while (arr[i] < q)
            i++;
        while (arr[j] > q)
            j--;
        if (i <= j)
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (j - l > 0)
        qsort(arr, l, j);
    if (r - i > 0)
        qsort(arr, i, r);
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    qsort(arr, 0, n - 1);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
}
