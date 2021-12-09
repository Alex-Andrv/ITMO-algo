#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen ("input.txt","r",stdin);
    freopen ("output.txt","w",stdout);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> mas(n, vector<int> (m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> mas[i][j];
    vector<vector<int>> ans(n, vector<int> (m));
    vector<vector<char>> prev(n, vector<char> (m));
    prev[0][0] = '0';
    ans[0][0] = mas[0][0];
    for (int i = 1; i < n; i++)
    {
        ans[i][0] = ans[i - 1][0] + mas[i][0];
        prev[i][0] = 'D';
    }
    for (int j = 1; j < m; j++)
    {
        ans[0][j] = ans[0][j - 1] + mas[0][j];
        prev[0][j] = 'R';
    }
    for (int i = 1; i < n; i++)
        for (int j = 1; j < m; j++)
        {
            if (ans[i - 1][j] > ans[i][j - 1])
            {
                prev[i][j] = 'D';
                ans[i][j] = ans[i - 1][j] + mas[i][j];
            }
            else
            {
                prev[i][j] = 'R';
                ans[i][j] = ans[i][j - 1] + mas[i][j];
            }
        }
    vector<char> answer;
    cout << ans[n - 1][m - 1] << endl;
    int i = n - 1;
    int j = m - 1;
    char b = prev[i][j];
    //cout << b << endl;
    while (b != '0')
    {
        answer.push_back(b);
        if (b == 'D')
        {
            i--;
        }
        else
        {
            j--;
        }
        b = prev[i][j];
    }
    reverse(answer.begin(), answer.end());
    for (int i = 0; i < answer.size(); i++)
        cout << answer[i];
    fclose (stdout);
    fclose (stdin);
}


