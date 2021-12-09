#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> mas(n, vector<int> (n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> mas[i][j];
        }
    vector<vector<int>> dp(1 << n, vector<int> (n, INT_MAX / 2));
    vector<vector<int>> prev(1 << n, vector<int> (n));
    for (int i = 0; i < (1 << n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            if ((1 << j) & i)
            {
                if ((1 << j) == i)
                {
                    dp[1 << j][j] = 0;
                    prev[i][j] = j;
                }
                else
                {
                    for (int k = 0; k < n; k++)
                    {
                        if (((1 << k) & i) != 0 && j != k)
                        {
                            if (dp[i][j] >  dp[i ^ (1 << j)][k] + mas[k][j])
                            {
                                dp[i][j] = dp[i ^ (1 << j)][k] + mas[k][j];
                                prev[i][j] = k;
                            }
                            if (dp[i][j] < 0)
                                dp[i][j] = INT_MAX / 2;
                        }
                    }
                }
            }
        }
    }
    int m = INT_MAX;
    int start;
    for (int i = 0; i < n; i++)
    {
        if (m > dp[(1 << n) - 1][i])
        {
            m = dp[(1 << n) - 1][i];
            start = i;
        }
    }
    cout << m << endl;
    int mask = (1 << n) - 1;
    cout << start + 1 << endl;
    while (start != prev[mask][start])
    {
        int tmp_mask = mask ^ (1 << start);
        start = prev[mask][start];
        mask = tmp_mask;
        cout << start + 1 << endl;
    }
}

