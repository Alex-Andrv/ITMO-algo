#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const long double xp = 0, yp = 1, xf = 1, yf = 0;

long double vp, vf;

long double way(long double point, long double a_f)
{
    long double wey_p = sqrt((xp - point) * (xp - point) + (yp - a_f) * (yp - a_f));
    long double wey_f = sqrt((xf - point) * (xf - point) + (yf - a_f) * (yf - a_f));
    return wey_p / vp + wey_f / vf;
}

int main()
{
    //cout << sqrt(9);
    cin >> vp >> vf;
    long double a;
    cin >> a;
    double l = 0, r = 1;
    for (int i = 0; i < 320; i++)
    {
        long double x1 = l + (r - l) / 3, x2 = l + (r - l) / 3 * 2;
        if (way(x1, a) < way(x2, a))
            r = x2;
        else
            l = x1;
    }
    cout << fixed << setprecision(9) << l;
}
