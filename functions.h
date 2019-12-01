//
// Created by Ivan Mamani on 1/12/2019.
//

#ifndef PD4_FUNCTIONS_H
#define PD4_FUNCTIONS_H
#include <fstream>
#include <regex>
#include "CMatrix.h"

template <typename T>
void read(const string &fileName, CMatrix<T> &m1, CMatrix<T> &m22) {

    int n=0, m=0, n2=0, m2=0, contador = 0;
    T a;

    vector<T> num;
    vector<T> num2;

    ifstream inFile(fileName);

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {

            istringstream iss(line);
            vector<string> parts((istream_iterator<string>(iss)), istream_iterator<string>());

            if (contador == 0) {
                n = stoi(parts[0]);
                m = stoi(parts[1]);
            }

            if (0 < contador && contador <= n) {
                for (auto &part : parts) {
                    a = stoi(part);
                    num.push_back(a);
                }
            }

            if (contador == (n + 1)) {
                n2 = stoi(parts[0]);
                m2 = stoi(parts[1]);
            }

            if (contador > (n + 1)) {
                for (auto &part : parts) {
                    a = stoi(part);
                    num2.push_back(a);
                }
            }
            contador++;
        }

        m1.filas=n;
        m1.columnas=m;
        m22.filas=n2;
        m22.columnas=m2;

    } else
        cout<<"ERROR";

    inFile.close();

    m1.llenarMatriz(num);
    m22.llenarMatriz(num2);
}

#endif //PD4_FUNCTIONS_H
