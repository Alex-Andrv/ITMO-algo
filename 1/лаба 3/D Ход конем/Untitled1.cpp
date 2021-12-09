#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int> > pereh{{2, 1}, {-2, 1}, {2, -1}, {-2, -1},
    {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

vector<vector<char>> tel{{'1', '2', '3'}, {'4', '5', '6'},
        {'7', '8', '9'}, {'-', '0', '-'}};

int mod = 1e9;

bool isValid(int x, int y)
{
    return x >= 0 && x < 4 && y >= 0 && y < 3 && tel[x][y] != '-';
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int> > ans(n, vector<int> (10, 0));
    for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
            {
                if (tel[i][j] != '-')
                    ans[0][tel[i][j] - '0'] = 1;
            }
    for (int n1 = 1; n1 < n; n1++)
    {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
            {
                if (tel[i][j] != '-')
                {
                    ans[n1][tel[i][j] - '0'] = 0;
                    for (int k = 0; k < pereh.size(); k++)
                    {
                        if (isValid(i + pereh[k].first, j + pereh[k].second))
                            ans[n1][tel[i][j] - '0'] = (ans[n1][tel[i][j] - '0'] + ans[n1 - 1][tel[i + pereh[k].first][j + pereh[k].second] - '0']) % mod;
                    }
                }
            }
    }
    int ansver = 0;
    for (int i = 0; i < 4; i++)
            for (int j = 0; j < 3; j++)
            {
                if (tel[i][j] != '0' && tel[i][j] != '8' && tel[i][j] != '-')
                {
                    ansver = (ansver + ans[n - 1][tel[i][j] - '0']) % mod;
                }
            }
    cout << ansver;
}
