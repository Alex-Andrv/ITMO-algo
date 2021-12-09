#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen ("input.txt","r",stdin);
    freopen ("output.txt","w",stdout);
    int n, k;
    cin >> n >> k;
    vector<int> mas(n);
    for (int i = 1; i < n - 1 ; i++)
    {
        cin >> mas[i];
    }
    vector<int> ans(n);
    vector<int> prev(n);
    prev[0] = 0;
    for (int i = 1; i < n; i++)
    {
        int ma = INT_MIN;
        int pos_ma = 0;
        for (int j = max(0, i - k); j < i; j++)
        {
            if (ans[j] > ma)
            {
                ma = ans[j];
                pos_ma = j;
            }
        }
        prev[i] = pos_ma;
        ans[i] = ma + mas[i];
    }
    vector<int> answer;
    int b = prev[n - 1];
    answer.push_back(n);
    while (b != 0)
    {
        answer.push_back(b + 1);
        b = prev[b];
    }
    answer.push_back(1);
    reverse(answer.begin(), answer.end());
    cout << ans[n - 1] << endl;
    cout << ((int)answer.size()) - 1 << endl;
    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << " ";
    fclose (stdout);
    fclose (stdin);
}

