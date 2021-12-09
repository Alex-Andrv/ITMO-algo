#include <bits/stdc++.h>

using namespace std;

int main()
{
    string st, st1;
    cin >> st >> st1;
    vector<vector<int>> ans(st.size() + 1, vector<int> (st1.size() + 1, 0));
    for (int i = 0; i <= st.size(); i++)
        ans[i][0] = i;
    for (int j = 0; j <= st1.size(); j++)
        ans[0][j] = j;
    for (int i = 1; i <= st.size(); i++)
        for (int j = 1; j <= st1.size(); j++)
        {
            if (st[i - 1] == st1[j - 1])
                ans[i][j] = ans[i - 1][j - 1];
            else
            {
                ans[i][j] = min(ans[i - 1][j], min(ans[i][j - 1], ans[i - 1][j - 1])) + 1;
            }
        }
    cout << ans[st.size()][st1.size()];

}
