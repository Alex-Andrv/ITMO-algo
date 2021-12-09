#include <bits/stdc++.h>

using namespace std;

struct my_str
{
    int zn;
    int mi;
    int ma;
    int s;
};

int fa(vector<my_str> &arr, int a)
{
    int tm = a;
    while (arr[tm].zn != tm)
    {
        tm = arr[tm].zn;
    }
    while (arr[a].zn != a)
    {
        a = arr[a].zn;
        arr[a].zn = tm;
    }
    return a;
}

void unions(vector<my_str> &arr, int a, int b)
{
    int f = fa(arr, a), s = fa(arr, b);
    if (arr[f].zn == arr[s].zn)
        return;
    if (arr[f].s < arr[s].s)
    {
        arr[f].zn = s;
        arr[s].mi = min(arr[s].mi, arr[f].mi);
        arr[s].ma = max(arr[s].ma, arr[f].ma);
        arr[s].s += arr[f].s;
    }
    else
    {
        arr[s].zn = f;
        arr[f].mi = min(arr[s].mi, arr[f].mi);
        arr[f].ma = max(arr[s].ma, arr[f].ma);
        arr[f].s += arr[s].s;
    }

}

void get(vector<my_str> &arr, int a)
{
    int f = fa(arr, a);
    cout << arr[f].mi + 1 << " " << arr[f].ma + 1 << " " << arr[f].s << endl;
}

int main()
{
    int n;
    cin >> n;
    vector<my_str> arr(n);
    for (int i = 0; i < n; i++)
    {
        arr[i].zn = i;
        arr[i].mi = i;
        arr[i].ma = i;
        arr[i].s = 1;
    }
    string act;
    while (cin >> act)
    {
        /*for (int i = 0; i < arr.size(); i++)
            cout << arr[i].zn << " " << arr[i].mi << " " << arr[i].ma << " " << arr[i].s << "\n";
        cout << "!!!! " << endl;*/
        if (act == "union")
        {
            int a, b;
            cin >> a >> b;
            unions(arr, a - 1, b - 1);
        }
        else
        {
            int c;
            cin >> c;
            get(arr, c - 1);
        }
    }
}
