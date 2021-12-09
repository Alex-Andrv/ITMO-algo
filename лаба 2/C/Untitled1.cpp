#include <bits/stdc++.h>

using namespace std;

struct my_deque
{
    vector<int> body;
    vector<int> head;
    void COUT()
    {
        cout << "!!!:" << endl;
        for (int i = (int)(body.size()) - 1; i >= 0; i--)
            cout << body[i] << " ";
        cout << endl;
        for (int i = 0; i < head.size(); i++)
            cout << head[i] << " ";
        cout << ",,,,,," << endl;
    }
    void balance()
    {
        //COUT();
        vector<int> tmp;
        if (body.size() == 0)
        {
            int len = head.size();
            for (int i = 0; i < len / 2; i++)
            {
                tmp.push_back(head.back());
                head.pop_back();
            }
            for (int i = len / 2; i < len; i++)
            {
                body.push_back(head.back());
                head.pop_back();
            }
            for (int i = 0; i < len / 2; i++)
            {
                head.
                push_back(tmp.back());
                tmp.pop_back();
            }
           // COUT();
        }
        else
        {
            if (head.size() == 0)
            {
                int len = body.size();
                for (int i = 0; i < len / 2; i++)
                {
                    tmp.push_back(body.back());
                    body.pop_back();
                }
                for (int i = len / 2; i < len; i++)
                {
                    head.push_back(body.back());
                    body.pop_back();
                }
                for (int i = 0; i < len / 2; i++)
                {
                    body.push_back(tmp.back());
                    tmp.pop_back();
                }
            }
        }
        //COUT();
    }
    void push(int number)
    {
        head.push_back(number);
        //COUT();
    }
    void pop_b()
    {
        if (head.size() != 0)
        {
            head.pop_back();
        }
        else
        {
            balance();
            head.pop_back();
        }
        //COUT();

    }
    void pop_f()
    {
        if (body.size() != 0)
        {
            body.pop_back();
        }
        else
        {
            balance();
            body.pop_back();
        }
        //COUT();
    }
    int f()
    {
        if (body.size() != 0)
        {
            return body.back();
        }
        else
        {
            balance();
            return body.back();
        }
        //COUT();
    }
    int find_el(int number)
    {
        for (int i = 0; i < head.size(); i++)
        {
            if (head[i] == number)
                return i + body.size();
        }
        for (int i = (int)body.size() - 1; i >= 0; i--)
        {
            if (body[i] == number)
                return body.size() - i - 1;
        }
        //COUT();
    }
};



int main()
{
    int n;
    cin >> n;
    my_deque dq;
    for (int i = 0; i < n; i++)
    {
        int b;
        cin >> b;
        if (b == 1)
        {
            int number;
            cin >> number;
            dq.push(number);
        }
        if (b == 2)
        {
            dq.pop_f();
        }
        if (b == 3)
        {
            dq.pop_b();
        }
        if (b == 4)
        {
            int number;
            cin >> number;
            cout << dq.find_el(number) << "\n";
        }
        if (b == 5)
        {
            cout << dq.f() << "\n";
        }
    }
}
