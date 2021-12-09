#include <bits/stdc++.h>

using namespace std;

void answ(string st, vector<vector<int>> dp, int len, int pos, vector<vector<int>> ek)
{
    if (dp[len][pos] == 0)
    {
        return;
    }
    if (dp[len][pos] * 2 == len)
    {
        cout << st.substr(pos, len);
        return;
    }
    if (st[pos] - st[pos + len - 1] >= -2 && st[pos] - st[pos + len - 1] < 0 && ek[len][pos] == -1)
    {
        cout << st[pos];
        answ(st, dp, len - 2, pos + 1, ek);
        cout << st[pos + len -1];
        return;
    }
    answ(st, dp, ek[len][pos], pos, ek);
    answ(st, dp, len - ek[len][pos], pos + ek[len][pos], ek);
}

int main()
{
    string st;
    cin >> st;
    //cout << '(' - ')' << " "<<'[' - ']' << " " << '{' -'}' << endl;
    vector<vector<int>> dp(st.size() + 1, vector<int> (st.size(), 0));
    vector<vector<int>> ek(st.size() + 1, vector<int> (st.size(), -1));
    for (int i = 2; i <= st.size(); i++) // len
    {
        for (int j = 0; j < st.size() + 1 - i; j++) // pos
        {
            //cout << i << " " << j << " " << st[j] << " " << st[j + i - 1] << endl;
            if (st[j] - st[j + i - 1] >= -2 && st[j] - st[j + i - 1] < 0)
            {
                dp[i][j] = dp[i - 2][j + 1] + 1;
            }
            int mk = -1;
            for (int k = 1; k < i; k++)
            {
                if (dp[k][j] + dp[i - k][j + k] > dp[i][j])
                {
                    mk = k;
                    dp[i][j] = dp[k][j] + dp[i - k][j + k];
                }
            }
            ek[i][j] = mk;
        }
    }
    /*for (int i = 0; i <= st.size(); i++) // len
    {
        for (int j = 0; j < st.size(); j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << dp[st.size()][0];*/
    answ(st, dp, st.size(), 0, ek);
}
