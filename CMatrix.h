//
// Created by Ivan Mamani on 1/12/2019.
//

#ifndef PD4_CMATRIX_H
#define PD4_CMATRIX_H

#include<vector>
#include <iostream>
#include <iomanip>
#define NUM_HILOS 2
using namespace std;

template <typename T>
vector<vector<T>> matriz1;
template <typename T>
vector<vector<T>> matriz2;
template <typename T>
vector<vector<T>> matriz3;

struct datos {
    long thread_id;
    int num_filas1;
    int num_filas2;
    int num_columnas1;
    int num_columnas2;
};

struct datos datos_pasar[NUM_HILOS];


template<typename T>
class CMatrix {
public:
    int filas;
    int columnas;
    vector<vector<T>> matriz;
    CMatrix(){}
    CMatrix(int filas, int columnas) : filas{filas}, columnas{columnas}{}
    void llenarMatriz( vector<T> &nums){

        for (auto it = nums.begin() ; it < nums.end();){
            for(auto i=0;i<filas;i++){
                vector<T> vec;
                for(int j=0;j<columnas;j++){
                    vec.push_back(*it);
                    it++;
                }
                matriz.push_back(vec);
            }
        }

    }
    void show_matrix(){

        for(int i=0;i<filas;i++){
            for(int j=0;j<columnas;j++){
                cout<< right << setw(7) << matriz[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    CMatrix<T> operator * (CMatrix<T> matriz);
};



template <typename T>
void* multiplicar_paralelo(void* parametros) {

    int filas1, columnas1, columnas2;
    long  lim_inf, lim_sup, t;
    struct datos* mis_datos;

    mis_datos=(struct datos*)parametros;
    t = mis_datos->thread_id;
    filas1 = mis_datos->num_filas1;
    columnas1 = mis_datos->num_columnas1;
    columnas2 = mis_datos->num_columnas2;

    if(filas1%NUM_HILOS != 0 && t==NUM_HILOS-1){
        lim_inf = t * (filas1 / NUM_HILOS);
        lim_sup = (t + 1) * (filas1 / NUM_HILOS) +1;
    }
    else{
        lim_inf = t * (filas1 / NUM_HILOS);
        lim_sup = (t + 1) * (filas1 / NUM_HILOS);
    }

    T sum=0;

    for (long i = lim_inf; i < lim_sup; i++){
        for (int j = 0; j < columnas2; j++){
            for (int z = 0; z < columnas1; z++) {
                sum += matriz1<T>[i][z]*matriz2<T>[z][j];
            }
            matriz3<T>[i][j]=sum;
            sum=0;
        }
    }

    pthread_exit(nullptr);
}



template<typename T>
CMatrix<T> CMatrix<T>::operator * (CMatrix<T> m){

    if(columnas == m.filas ){
        CMatrix<T> R =CMatrix<T>(filas,m.columnas);
        for(int i=0;i<filas;i++)
        {
            vector<T> a;
            for(int j=0;j<m.columnas;j++){
                a.push_back(0);
            }
            matriz3<T>.push_back(a);
        }

        matriz1<T>  =matriz;
        matriz2<T>  =m.matriz;

        int rc;
        long t;
        void* status;

        pthread_t hilos[NUM_HILOS];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        for (t = 0;t < NUM_HILOS; t++) {
            datos_pasar[t].thread_id=t;
            datos_pasar[t].num_filas1=filas;
            datos_pasar[t].num_columnas1=columnas;
            datos_pasar[t].num_filas2=m.filas;
            datos_pasar[t].num_columnas2=m.columnas;

            rc = pthread_create(&hilos[t],&attr,multiplicar_paralelo<T>,(void*)&datos_pasar[t]);

            if (rc) {
                cout << "ERROR "<< rc;
                exit(-1);
            }


        }

        pthread_attr_destroy(&attr);

        for(t=0;t<NUM_HILOS;t++) {
            rc = pthread_join(hilos[t],&status);
            if (rc) {
                cout<<"ERROR\n"<<rc<<endl;
                exit(-1);
            }
        }
        cout<<endl;
        R.matriz = matriz3<T>;
        R.show_matrix();

        pthread_exit(nullptr);

    }
    else
        throw runtime_error("Error");



}

#endif //PD4_CMATRIX_H
