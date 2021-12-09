#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> mas(n);
    for (int i = 0; i < n; i++)
        cin >> mas[i];
    vector<int> ans(n, 1);
    vector<int> prev(n, 0);
    for (int i = 0; i < n; i++)
    {
        int ma = 0;
        int prev_tmp = i;
        prev[i] = i;
        for (int j = 0; j < i; j++)
        {
            if (ma < ans[j] && mas[i] > mas[j])
            {
                ma = ans[j];
                prev_tmp = j;
            }
        }
        if (ans[i] < ma + 1)
        {
            ans[i] = ma + 1;
            prev[i] = prev_tmp;
        }
    }
    int ma = 0;
    int start = 0;
    for(int i = 0; i < n; i++)
    {
        if (ans[i] > ma)
        {
            ma = ans[i];
            start = i;
        }
    }
    cout << ma << endl;
    vector<int> posl;
    posl.push_back(mas[start]);
    while (start != prev[start])
    {
        start = prev[start];
        posl.push_back(mas[start]);
    }
    for (int i = (int)posl.size() - 1; i >= 0; i--)
        cout << posl[i] << " ";
}
