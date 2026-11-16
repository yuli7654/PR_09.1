#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

// глобальні змінні (простір імен nsVar)
namespace nsVar {
    int n;                              // кількість доданків
    double x, x_p, x_k, dx, e, a, s;    // аргумент, межі, крок, точність,
};                                      // поточний доданок, сума ряду

// обчислення доданку (простір імен nsDod)
namespace nsDod {
    void dod() {
        using namespace nsVar;
        a *= x * x * (2 * n - 1) * (2 * n - 1)
            / (2 * n * (2 * n + 1.0));   // доданок домножується на
    }                                         // коефіцієнт рекурентності
};

// обчислення суми ряду (простір імен nsSum)
namespace nsSum {
    void sum() {
        using namespace nsDod;
        using namespace nsVar;

        const double PI = 3.14159265358979323846;

        n = 0;
        a = x;                          // перший доданок ряду
        s = a;
        do {
            n++;
            dod();                      // виклик обчислення доданку
            s += a;
        } while (fabs(a) > e);

        s = PI / 2 - s;                 // arccos x = pi/2 - ( x + ... )
    }
};

using namespace nsSum;
using namespace nsVar;

#ifndef UNIT_TEST                       // у unit-тесті main вимкнено
int main()
{
    cout << "x_p = "; cin >> x_p;
    cout << "x_k = "; cin >> x_k;
    cout << "dx  = "; cin >> dx;
    cout << "e   = "; cin >> e;
    cout << endl;

    // ряд збігається лише при |x| < 1
    if (x_p <= -1 || x_k >= 1 || dx <= 0 || x_p > x_k) {
        cout << "Error: потрібно -1 < x_p <= x_k < 1 та dx > 0" << endl;
        return 1;
    }

    cout << "arccos x = pi/2 - ( x + sum(1*3*...*(2n-1)*x^(2n+1)"
        << " / (2*4*...*2n*(2n+1))) )" << endl;
    cout << "+-------+-------------+-------------+-----+" << endl;
    cout << "|   x   |  arccos(x)  |  sum of row |  n  |" << endl;
    cout << "+-------+-------------+-------------+-----+" << endl;

    x = x_p;
    while (x <= x_k + dx / 2) {        // dx/2 – запас на похибку x += dx
        sum();                          // виклик процедури обчислення суми

        cout << "|" << setw(6) << fixed << setprecision(3) << x << " "
            << "|" << setw(12) << setprecision(6) << acos(x) << " "
            << "|" << setw(12) << s << " "
            << "|" << setw(4) << n << " |" << endl;   // форматний вивід

        x += dx;
    }
    cout << "+-------+-------------+-------------+-----+" << endl;

    cin.get(); cin.get();
    return 0;
}
#endif