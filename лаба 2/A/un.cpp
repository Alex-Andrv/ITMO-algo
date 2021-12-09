#include <bits/stdc++.h>

using namespace std;

int main()
{
    long long n;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    vector<long long> my_stack;
    vector<long long> min_stack;
    for (long long i = 0; i < n; i++)
    {
        long long b;
        cin >> b;
        if (b == 1)
        {
            long long tmp;
            cin >> tmp;
            my_stack.push_back(tmp);
            if (min_stack.size() == 0 || min_stack.back() > tmp)
                min_stack.push_back(tmp);
            else
                min_stack.push_back(min_stack.back());
        }
        if (b == 2)
        {
            my_stack.pop_back();
            min_stack.pop_back();
        }
        if (b == 3)
        {
           cout << min_stack.back() << "\n";
        }
    }
}
