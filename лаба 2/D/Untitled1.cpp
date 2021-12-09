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
    void push_b(int number)
    {
        head.push_back(number);
        //COUT();
    }
    void push_f(int number)
    {
        body.push_back(number);
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
    int b()
    {
        if (head.size() != 0)
        {
            return head.back();
        }
        else
        {
            balance();
            return head.back();
        }
        //COUT();
    }
    int s()
    {
        return head.size() + body.size();
    }
};

int main()
{
    int n;
    cin >> n;
    my_deque left, right;
    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        if (c == '+')
        {
            int tmp;
            cin >> tmp;
            right.push_b(tmp);
        }
        if (c == '-')
        {
            cout << left.f() << endl;
            left.pop_f();
        }
        if (c == '*')
        {
            int tmp;
            cin >> tmp;
            right.push_f(tmp);
        }
        if (right.s() > left.s())
        {
            left.push_b(right.f());
            right.pop_f();
        }
    }
}
