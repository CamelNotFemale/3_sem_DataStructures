#include <iostream>
#include <clocale>
#include <cstdlib>
#include <ctime>
using namespace std;
const int NMAX=26;
#include "Set.h" //Реализация структур данных
int Set :: N = NMAX, Set :: cnt = 0; // Определение статических членов класса

const long rolls = 100000; //Количество итераций

int main()
{
    srand(time(nullptr));
    char Q;
    char A_0[NMAX+1], B_0[NMAX+1], C_0[NMAX+1], D_0[NMAX+1];

    cout << "Randomly generated sets:" << endl;
    Set A('A'), B('B'), C('C'), D('D'), E;
    cout << endl << "Do you want to enter your sets? Enter 1 - Yes, 0 - Use randomly generated" << endl;
    cin >> Q;
    if (Q=='1')
    {
        cout << "A: "; cin >> A_0; cout << "B: "; cin >> B_0; cout << "C: "; cin >> C_0; cout << "D: "; cin >> D_0;
        A.rewrite(A_0);  B.rewrite(B_0); C.rewrite(C_0); D.rewrite(D_0);
    }

    clock_t start = clock();
    for (int i = 0;i<rolls;i++) {
        E = ((A & ~B) & ~C) & ~D;
    }
    clock_t ticks = clock() - start;

    cout << "\nResult:\n";
    E.Show('E');
    cout << " Middle power = " << (A.power()+B.power()+C.power()+D.power()+E.power())/5 << " Time: " << 1000 * ((((double) ticks) / CLOCKS_PER_SEC) / rolls) << " ms" << endl;

    return 0;
}
