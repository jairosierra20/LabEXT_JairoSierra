#include "Matriz.h"
#include <string>
using std::string;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <cmath>
Matriz::Matriz()
{
}
Matriz::Matriz(string pnombre, int ptam)
{
    this->nombre = pnombre;
    this->tam = ptam;
}
string Matriz::getNombre()
{
    return nombre;
}
void Matriz::setNombre(string pnombre)
{
    nombre = pnombre;
}
int Matriz::getTam()
{
    return tam;
}
void Matriz::setTam(int ptam)
{
    tam = ptam;
}
int **Matriz::getMatriz()
{
    return matriz;
}
void Matriz::setMatriz(int **pmatriz)
{
    matriz = pmatriz;
}
int **Matriz::provisionarMatriz(int size)
{
    matriz = new int *[size];
    for (int i = 0; i < tam; i++)
    {
        matriz[i] = new int[size];
    }
    return matriz;
}
void Matriz::liberarMatriz(int **&matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (matrix[i] != NULL)
        {
            delete[] matrix[i];
            matrix[i] = NULL;
        }
    }
}
void Matriz::printMatrix(int **matrix, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << "[" << matrix[i][j] << "] ";
        }
        cout << endl;
    }
}
void Matriz::llenarmatriz(int **matrix, int size)
{
    int num = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout<<"Ingrese el numero: "<<endl;
            cin>>num;
            matrix[i][j] = num; //numero aletorio
        }
    }
}
int Matriz::determinante(int **matrix, int size)
{
    int determinante = 0;
    if (size == 1)
    {
        determinante = matrix[0][0];
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            determinante = determinante + matrix[0][i] * cofactor(matrix, size, 0, i);
        }
    }
    return determinante;
}
int Matriz::cofactor(int **matrix, int size, int fila, int columna)
{
    int **submatriz = NULL;
    int orden = size - 1;
    submatriz = provisionarMatriz(orden);
    int x = 0, y = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i != fila && j != columna)
            {
                submatriz[x][y] = matrix[i][j];
                y++;
                if (y >= orden)
                {
                    x++;
                    y = 0;
                }
            }
        }
    }
    return pow(-1.0, fila + columna) * determinante(submatriz, orden);
}
int **Matriz::suma(int **matrixA, int **matrixB, int size)
{
    int **matrixTotal = NULL;
    matrixTotal = provisionarMatriz(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrixTotal[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    return matrixTotal;
}
int **Matriz::incremento(int **matriz, int size, int determinante)
{
    int diferencia = determinante - size;
    int absoluto = abs(diferencia);
    int **matrixTotal = NULL;
    matrixTotal = provisionarMatriz(size);
    cout << absoluto << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrixTotal[i][j] = absoluto + matriz[i][j];
        }
    }
    return matrixTotal;
}
int **Matriz::decremento(int **matriz, int size, int determinante)
{
    int diferencia = determinante - size;
    int absoluto = abs(diferencia);
    int **matrixTotal = NULL;
    matrixTotal = provisionarMatriz(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrixTotal[i][j] = absoluto - matriz[i][j];
        }
    }
    return matrixTotal;
}
int **Matriz::multiplicacion_escalar(int **matriz, int escalar, int size)
{
    int **matrixTotal = NULL;
    matrixTotal = provisionarMatriz(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrixTotal[i][j] = escalar * matriz[i][j];
        }
    }
    return matrixTotal;
}
int **Matriz::producto(int **matrizA, int **matrizB, int size)
{
    int **matrixTotal = NULL;
    matrixTotal = provisionarMatriz(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                matrixTotal[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    return matrixTotal;
}
int **Matriz::suma_espacio(int **matrizA, int **matrizB, int size)
{
    int **matrixTotal = NULL;
    matrixTotal = provisionarMatriz(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                matrixTotal[i][j] = 2 * (matrizA[i][j] - matrizB[i][j]);
            }
            else
            {
                matrixTotal[i][j] = matrizA[i][j] + matrizB[i][j];
            }
        }
    }
    return matrixTotal;
}
int **Matriz::transpuesta(int **matrix, int size)
{
    int **matrixTotal = NULL;
    matrixTotal = provisionarMatriz(size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrixTotal[j][i] = matrix[i][j];
        }
    }
    return matrixTotal;
}
int **Matriz::multiplicacion_espacio(int **matrix, int size, int determinante, int num)
{
    int escalar = 0;
    int **matrixAuxiliar = NULL;
    matrixAuxiliar = provisionarMatriz(size);
    int **matrixTotal = NULL;
    matrixTotal = provisionarMatriz(size);
    matrixAuxiliar = transpuesta(matrix, size);
    //printMatrix(matrixAuxiliar,size);
    escalar = (determinante) / (num);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            matrixTotal[i][j] = escalar * matrixAuxiliar[i][j];
        }
    }
    return matrixTotal;
}