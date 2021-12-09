#include <bits/stdc++.h>

using namespace std;

int main1(int n,const vector<int> mas)
{
    //int n;
    //cin >> n;
    //vector<int> mas(n);
    //for (int i = 0; i < n; i++)
    //   cin >> mas[i];
    vector<vector<int> > ans(n + 1, vector<int> (n + 2, INT_MAX - 10000));
    ans[0][0] = 0;
    for (int j = 1; j < n + 2; j++)
        ans[0][j] = INT_MAX - 10000;
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
        if (mi > ans[n][j])
        {
            mi = ans[n][j];
            start = j;
        }
    }
    return mi;
    /*cout << mi << endl << start << " ";
    int co = 0;
    vector<int> pos;
    for (int i = n; i >= 1; i--)
    {
       // cout << start << endl;
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

    */
}
int main2(int n,const vector<int> a)
{
    //int n;
    //cin » n;
    vector<int>  b;
    vector<vector<int> > d;
    d.resize(n+1);
    //for (int i = 0; i < n; i++)
    //  cin » a[i];
    for (int i = 0; i < n + 1; i++)
        d[i].resize(n + 1);
    for (int i = 0; i < n+1; i++)
    {
        d[0][i] = 30001;
        d[i][0] = 0;
    }
    for (int i = 1; i < n + 1; i++)
        for (int j = 1; j < n + 1; j++)
            if (j > i)
                d[i][j] = 30001;
    for (int i = 1; i < n + 1; i++)
        for (int j = 0; j < i + 1; j++)
            if (a[i - 1] <= 100)
                d[i][j] = min(d[i - 1][j] + a[i - 1], d[i - 1][j + 1]);
            else if (j == 0)
                d[i][j] = min(30001 + a[i - 1], d[i - 1][j + 1]);
            else
                d[i][j] = min(d[i - 1][j - 1] + a[i - 1],d[i - 1][j + 1]);
    /*for (int i = 0; i < n+1; i++)
    {
    for (int j = 0; j < n+1; j++)
    cout « d[i][j] « " ";
    cout « endl;
    }
    cout « endl;*/
    int ans = d[n][0];
    int ind_ans = 0;
    for (int i = 1; i < n + 1; i++)
        if (d[n][i] > 0 && d[n][i] <= ans)
        {
            ans = d[n][i];
            ind_ans = i;
        }
    int n1 = n;
    int ind = ind_ans;
    if (ans != 0)
        while (n1 > 0)
        {
            if ( a[n1 - 1] <= 100 )
                if (d[n1][ind] == d[n1-1][ind+1])
                {
                    b.push_back(n1);
                    n1--;
                    ind++;
                }
                else
                    n1--;
            else if (d[n1][ind] == d[n1-1][ind+1])
            {
                b.push_back(n1);
                n1--;
                ind++;
            }
            else
            {
                n1--;
                ind--;
            }
        }
    sort(b.begin(), b.end());
    return  ans;
    /*cout « ind_ans « " " « b.size() « endl;
    for (int i = 0; i < b.size(); i++)
    {
        cout « b[i] « endl;
    }*/
}


int main()
{
    srand( time(0) );
    while (true)
    {
        int n = rand() % 10;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
            a[i] = rand() % 300;
        int f = (main1(n, a));
        int s = (main2(n, a));
        cout << (int)(f == s);
        if (f == s)
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << ":" << main1(n, a) << " " << n <<  " " << main2(n, a) << endl;
            cout << n << endl;
            for (int i = 0; i < n; i++)
                cout << a[i] << endl;
            char c;
            cin >> c;
        }
    }
}
