#include <bits/stdc++.h>

using namespace std;

int main()
{
    /*ios_base::sync_with_stdio(false);
    cin.tie(NULL);*/
    int n;
    cin >> n;
    vector<int> bus;
    vector<int> cou;
    int coun = 0;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        if (bus.size() == 0)
        {
            bus.push_back(tmp);
            cou.push_back(1);
        }
        else
        {
            if (bus.back() != tmp)
            {
                if (cou.back() >= 3)
                {
                    coun += cou.back();
                    int c = cou.back();
                    for (int j = 0; j < c; j++)
                    {
                        bus.pop_back();
                        cou.pop_back();
                    }
                }
                if (bus.back() == tmp)
                {
                    bus.push_back(tmp);
                    cou.push_back(cou.back() + 1);
                }
                else
                {
                    bus.push_back(tmp);
                    cou.push_back(1);
                }
            }
            else
            {
                bus.push_back(tmp);
                cou.push_back(cou.back() + 1);
            }
        }
    }
    if (cou.back() >= 3)
    {
        coun += cou.back();
        int c = cou.back();
        for (int i = 0; i < c; i++)
        {
            bus.pop_back();
            cou.pop_back();
        }
    }
    cout << coun;
}
