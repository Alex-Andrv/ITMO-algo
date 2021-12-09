#include <bits/stdc++.h>

using namespace std;

int main()
{
    int arr[101];
    for (int i = 0; i < 101; i++)
        arr[i] = 0;
    int buf;
    int n = 0;
    while (cin >> buf)
    {
        arr[buf]++;
    }
    for (int i = 0; i < 101; i++)
    {
        for (int j = 0; j < arr[i]; j++)
            cout << i << " ";
    }
}
