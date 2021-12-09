#include <bits/stdc++.h>

using namespace std;

int main()
{
    while (true)
    {
        ofstream fout ("input.txt");
        set<pair<int, int>> ss;
        set<pair<int, int>> se;
        int n, m, q;
        n = rand() % 10 + 1;
        m = n - 1;
        q = rand() % 10 + 1;
        fout << n << " " << m << " " << q << endl;
        for (int i = 0; i < m; i++)
        {
            int f, s;
            f = rand() % n + 1;
            s = rand() % n + 1;
            while (s == f || ss.find({s, 2}) != ss.end() || ss.find({f, 2}) != ss.end() || se.find({f, s}) != se.end())
            {
                f = rand() % n + 1;;
                s = rand() % n + 1;
            }
            fout << f << " " << s << endl;
            se.insert({f, s});
            se.insert({s, f});
            if (ss.find({s, 1}) == ss.end())
            {
                ss.insert({s, 1});
            }
            else
            {
                ss.insert({s, 2});
            }
            if (ss.find({f, 1}) == ss.end())
            {
                ss.insert({f, 1});
            }
            else
            {
                ss.insert({f, 2});
            }
        }
        for (int i = 0; i < q; i++)
        {
            int c = rand() % 3;
            while (c == 1 && ss.size() == 0 || c == 0 && se.size() == 2 * m)
            {
                c = rand() % 3;
            }
            if (c == 0)
            {
                int f, s;
                f = rand() % n + 1;;
                s = rand() % n + 1;;
                while (s == f || ss.find({s, 2}) != ss.end() || ss.find({f, 2}) != ss.end() || se.find({f, s}) != se.end())
                {
                    f = rand() % n + 1;;
                    s = rand() % n + 1;;
                }
                fout << "+ " << f << " " << s << endl;
                se.insert({f, s});
                se.insert({s, f});
                if (ss.find({s, 1}) == ss.end())
                {
                    ss.insert({s, 1});
                }
                else
                {
                    ss.insert({s, 2});
                }
                if (ss.find({f, 1}) == ss.end())
                {
                    ss.insert({f, 1});
                }
                else
                {
                    ss.insert({f, 2});
                }
            }
            if (c == 1)
            {
                int f, s;
                f = rand() % n + 1;
                s = rand() % n + 1;
                while (s == f || se.find({f, s}) == se.end())
                {
                    f = rand() % n + 1;
                    s = rand() % n + 1;
                }
                fout << "- " << f << " " << s << endl;
                se.erase({f, s});
                se.erase({s, f});
                if (ss.find({s, 2}) == ss.end())
                {
                    ss.erase({s, 1});
                }
                else
                {
                    ss.erase({s, 2});
                }
                if (ss.find({f, 2}) == ss.end())
                {
                    ss.erase({f, 1});
                }
                else
                {
                    ss.erase({f, 2});
                }

            }
            if (c == 2)
            {
                int f, s;
                f = rand() % n + 1;
                s = rand() % n + 1;
                fout << "? " << f << " " << s << endl;
            }
        }
        fout.close();
        system("un.exe");
        system("Untitled6.exe");
        ifstream fin("output.txt");
        ifstream fin2("output1.txt");
        int ans1, ans2;
        while (fin >> ans1 && fin2 >> ans2)
        {
            if (ans1 != ans2)
            {
                cout << "Error";
                fin.close();
                fin2.close();
                char ccccc;
                cin >> ccccc;
            }
        }
        fin.close();
        fin2.close();
    }
}
