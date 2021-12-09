#include <bits/stdc++.h>

using namespace std;

struct my_str
{
    int zn;
    int delay;
    my_str(int z = 0, int d = 0)
    {
        zn = z;
        delay = d;
    }
};

int fa(vector<my_str> &arr, int a)
{
    int tm = a;
    int de = 0;
    while (arr[tm].zn != tm)
    {
        tm = arr[tm].zn;
        if (arr[tm].zn != tm)
            de += arr[tm].delay;
    }
    int t = a;
    while (arr[a].zn != a)
    {
        if (t != a)
            de -= arr[a].delay;
        arr[a].delay += de;
        int b = a;
        a = arr[a].zn;
        arr[b].zn = tm;
    }
    return a;
}

void add (vector<my_str> &arr, int a, int bo)
{
    int f = fa(arr, a);
    arr[f].delay += bo;
}

void unions(vector<my_str> &arr, int a, int b)
{
    int f = fa(arr, a), s = fa(arr, b);
    if (arr[f].zn == arr[s].zn)
        return;
    arr[f].zn = s;
    arr[f].delay += (-arr[s].delay);
}

int main()
{
    int n;
    cin >> n;
    vector<my_str> arr(n);
    for (int i = 0; i < n; i++)
    {
        arr[i].zn = i;
        arr[i].delay = 0;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++)
    {
       /*for (int j = 0; j < arr.size(); j++)
            cout << arr[j].zn << " " << arr[j].delay << "\n";
        cout << "!!!! " << endl;*/
        string act;
        cin >> act;
        if (act == "join")
        {
            int a, b;
            cin >> a >> b;
            unions(arr, a - 1, b - 1);
        }
        if (act == "get")
        {
            int a;
            cin >> a;
            int f = fa(arr, a - 1);
            if (a - 1 != f)
                cout << arr[a - 1].delay + arr[f].delay<< endl;
            else
                cout << arr[a - 1].delay << endl;
        }
        if (act == "add")
        {
            int a, b;
            cin >> a >> b;
            add(arr, a - 1, b);
        }
    }
}

