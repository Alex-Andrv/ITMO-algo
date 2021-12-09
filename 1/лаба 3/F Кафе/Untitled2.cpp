#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> mas(n);
    for (int i = 0; i < n; i++)
       cin >> mas[i];
    vector<vector<int> > ans(n + 1, vector<int> (n + 2, 30009));
    ans[0][0] = 0;
    for (int j = 1; j < n + 2; j++)
        ans[0][j] = 30009;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            ans[i][j] = ans[i - 1][j + 1];
            if (mas[i - 1] <= 100 && ans[i][j] > ans[i - 1][j] + mas[i - 1])
            {
                ans[i][j] = ans[i - 1][j] + mas[i - 1];
            }
            if (mas[i - 1] > 100 && j != 0 && ans[i][j] > ans[i - 1][j - 1] + mas[i - 1])
            {
                ans[i][j] = ans[i - 1][j - 1] + mas[i - 1];
            }
        }
    }
    /*for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
            cout << ans[i][j] << " ";
        cout << endl;
    }*/
    int mi = INT_MAX;
    int start = 0;
    for (int j = 0; j <= n; j++)
    {
        if (mi >= ans[n][j])
        {
            mi = ans[n][j];
            start = j;
        }
    }
    cout << mi << endl << start << " ";
    int co = 0;
    vector<int> pos;
    for (int i = n; i >= 1; i--)
    {
        //cout << start << endl;
        if (start == 0)
        {
            if (ans[i - 1][start + 1] < ans[i - 1][start] + mas[i - 1])
            {
                co++;
                pos.push_back(i);
                start = start + 1;
            }
        }
        else
        {
            if (ans[i - 1][start + 1] < ans[i - 1][start - (mas[i - 1] > 100 ? 1:0)] + mas[i - 1])
            {
                co++;
                pos.push_back(i);
                start = start + 1;
            }
            else
            {
                start = start - (mas[i - 1] > 100 ? 1:0);
            }
        }
    }
    cout << co << endl;
    for (int i = co - 1; i >= 0; i--)
        cout << pos[i] << endl;
}
