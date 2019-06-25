#ifndef MATRIZ_H
#define MATRIZ_H
#include <string>
using std::string;
class Matriz
{
private:
    string nombre;
    int tam;
    int **matriz;

public:
    Matriz();
    Matriz(string, int);
    string getNombre();
    void setNombre(string);
    int getTam();
    void setTam(int);
    int **getMatriz();
    void setMatriz(int **);
    //Provisionar la matriz
    int **provisionarMatriz(int);
    //liberar memoria de la matriz
    void liberarMatriz(int **&, int);
    //imprimir la matriz
    void printMatrix(int **, int);
    //llenar la matriz a
    void llenarmatriz(int **, int);
    int cofactor(int **, int, int, int);
    int determinante(int **, int);
    int **suma(int **, int **, int);
    int **incremento(int **, int, int);
    int **decremento(int **, int, int);
    int **multiplicacion_escalar(int **, int, int);
    int **producto(int **, int **, int);
    int **suma_espacio(int **, int **, int);
    int **multiplicacion_espacio(int **, int, int, int);
    int **transpuesta(int **, int);
};
#endif