#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> my_stack;
    int fr = INT_MIN;
    vector<string> ans;
    int tmp;
    cin >> tmp;
    my_stack.push_back(tmp);
    ans.push_back("push");
    for (int i = 1; i < n; i++)
    {
        cin >> tmp;
        if (tmp <= my_stack.back())
        {
            my_stack.push_back(tmp);
            ans.push_back("push");
        }
        else
        {
            while(my_stack.size() != 0 && my_stack.back() < tmp)
            {
                if (fr > my_stack.back())
                {
                    cout << "impossible";
                    return 0;
                }
                fr = my_stack.back();
                ans.push_back("pop");
                my_stack.pop_back();
            }
            my_stack.push_back(tmp);
            ans.push_back("push");
        }
    }
    while(my_stack.size() != 0)
    {
        if (fr > my_stack.back())
        {
            cout << "impossible";
            return 0;
        }
        fr = my_stack.back();
        ans.push_back("pop");
        my_stack.pop_back();
    }
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << endl;
    }
}
