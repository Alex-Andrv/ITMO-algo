#include <bits/stdc++.h>

using namespace std;

long long toInt(string &st)
{
    long long res = 0;
    long long zn = 1;
    long long i = 0;
    if (st[0] == '-')
    {
        zn = -1;
        i++;
    }
    for (i; i < st.size(); i++)
    {
        res = res * 10 + (st[i] - '0');
    }
    return res * zn;
}


int main()
{
    vector<long long> arr;
    string tmp;
    while (cin >> tmp)
    {
        /*for (long longi = 0; i < arr.size(); i++)
            cout << arr[i] << " ";
        cout << endl;*/
        if (tmp == "+")
        {
            long long f, s;
            f = arr.back();
            arr.pop_back();
            s = arr.back();
            arr.pop_back();
            arr.push_back(f + s);
        }
        if (tmp ==  "-")
        {
            long long f, s;
            f = arr.back();
            arr.pop_back();
            s = arr.back();
            arr.pop_back();
            arr.push_back(s - f);
        }
        if (tmp == "*")
        {
            long long f, s;
            f = arr.back();
            arr.pop_back();
            s = arr.back();
            arr.pop_back();
            arr.push_back(f * s);
        }
        if (tmp != "-" && tmp != "+" && tmp != "*")
            arr.push_back(toInt(tmp));
    }
    cout << arr.back();
}
