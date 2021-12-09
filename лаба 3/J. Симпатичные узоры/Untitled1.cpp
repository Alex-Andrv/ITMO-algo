#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    if (n < m)
        swap(n, m);
    vector<vector<long long>> dp(n, vector<long long> (1 << m));
    for (int j = 0; j < (1 << m); j++)
    {
        dp[0][j] = 1;
    }
    for (int i = 1; i < n; i++)
        for (int j = 0; j < (1 << m); j++)
        {
            for (int k = 0; k < (1 << m); k++)
            {
                int tmp = j ^ k;
                int tmp2 = j & k;
                int in = 0;
                while (tmp != 0 && (tmp % 4 != 0) || tmp2 % 4 == 1 || tmp2 % 4 == 2)
                {
                    in++;
                    tmp /= 2;
                    tmp2 /= 2;
                }
                if (in >= m - 1)
                    dp[i][j] += dp[i - 1][k];
            }
        }
    /*for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (1 << m); j++)
            cout << dp[i][j] << " ";
        cout << endl;
    }*/
    //cout << "!!!";
    long long ans = 0;
    for (int j = 0; j < (1 << m); j++)
        ans += dp[n - 1][j];
    cout << ans;
}

