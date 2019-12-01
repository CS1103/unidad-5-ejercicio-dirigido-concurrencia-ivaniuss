#include <iostream>
#include "CMatrix.h"
#include "functions.h"
using namespace std;
int main()
{
    string path = "../ejemplo4.txt";
    CMatrix<int> m1;
    CMatrix<int> m2;
    CMatrix<int> mr;

    read(path, m1, m2);
    mr = m1*m2;
    mr.show_matrix();
    cout << endl;


    return 0;
}