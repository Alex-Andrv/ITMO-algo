#include <bits/stdc++.h>

using namespace std;

void sift_up (vector<int> &a, int i)
{
    if (i == 0)
        return;
    if (a[i] > a[(i - 1) / 2])
    {
        swap(a[i], a[(i - 1) / 2]);
        sift_up(a, (i - 1) / 2);
    }
}

void insert_el(vector<int> &a, int value)
{
    a.push_back(value);
    sift_up(a, a.size() - 1);
}

void sift_down(vector<int> &a, int i)
{
    while (true)
    {
        int j = i;
        if (2 * i + 1 < a.size() && a[2 * i + 1] > a[j])
            j = 2 * i + 1;
        if (2 * i + 2 < a.size() && a[2 * i + 2] > a[j])
            j = 2 * i + 2;
        if (i == j)
            break;
        swap(a[i], a[j]);
        i = j;
    }
}

int extract_max(vector<int> &a)
{
    swap(a[0], a[a.size() - 1]);
    int ans = a[a.size() - 1];
    a.resize(a.size() - 1);
    sift_down(a, 0);
    return ans;
}



int main()
{
    vector<int> a;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int zn;
        cin >> zn;
        if (zn == 0)
        {
            int value;
            cin >> value;
            insert_el(a, value);
            /*for (int i = 0; i < a.size(); i++)
                cout << a[i] << " ";
            cout << endl;*/
        }
        else
        {
            cout << extract_max(a) << endl;
            /*for (int i = 0; i < a.size(); i++)
                cout << a[i] << " ";
            cout << endl;*/
        }
    }
}
