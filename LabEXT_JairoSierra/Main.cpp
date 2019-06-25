#include "Matriz.h"
#include <vector>
using std::vector;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
vector<Matriz *> matrices;
vector<int **> llenadas;
void Agregar();
void Listar();
void Eliminar();
void Operar();
int main()
{
    int opcion = 0;
    while (opcion != 5)
    {
        cout << "Menu" << endl
             << "1. Crear Matrices" << endl
             << "2. Listar Matrices" << endl
             << "3. Eliminar Matrices" << endl
             << "4. Operar con matrices" << endl
             << "5. Salir" << endl;
        cout << "Ingrese una opcion: " << endl;
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            Agregar();
            break;
        case 2:
            Listar();
            break;
        case 3:
            Eliminar();
            break;
        case 4:
            Operar();
            break;
        case 5:
            cout << "El programa se cerrara" << endl;
            // se liberar la memoria de las matrices del vector
            for (int i = 0; i < matrices.size(); i++)
            {
                matrices[i]->liberarMatriz(llenadas[i], matrices[i]->getTam());
            }
            //se liberan los vectores
            for (int i = 0; i < matrices.size(); i++)
            {
                delete matrices[i];
                matrices[i] = NULL;
            }
            matrices.clear();
            for (int i = 0; i < llenadas.size(); i++)
            {
                delete llenadas[i];
                llenadas[i] = NULL;
            }
            llenadas.clear();
            break;
        default:
            cout << "La opcion ingresada es incorrecta" << endl;
            break;
        }
    }
}
void Agregar()
{
    int size = 0;
    string nombre = "";
    cout << "Ingrese el nombre de la matriz: " << endl;
    cin >> nombre;
    cout << "Ingrese el orden de la matriz (2,3)" << endl;
    cin >> size;
    while (size < 2 || size > 3)
    {
        cout << "El tamaño es incorrecto" << endl;
        cout << "Ingrese el orden de la matriz (2,3)" << endl;
        cin >> size;
    }
    Matriz *auxiliar = new Matriz(nombre, size);
    matrices.push_back(auxiliar);
    int **matriz = auxiliar->provisionarMatriz(size);
    auxiliar->llenarmatriz(matriz, size);
    llenadas.push_back(matriz);
}
void Listar()
{
    int **matriz = NULL;
    for (int i = 0; i < matrices.size(); i++)
    {
        cout << i << "- Nombre: " << matrices[i]->getNombre() << endl;
        matrices[i]->printMatrix(llenadas[i], matrices[i]->getTam());
    }
}
void Eliminar()
{
    cout << "Lista de matrices" << endl;
    Listar();
    int pos = 0;
    cout << "Ingrese la posicion de la matriz que desea eliminar: " << endl;
    cin >> pos;
    matrices.erase(matrices.begin() + pos);
    llenadas.erase(llenadas.begin() + pos);
    cout << "Se elimino correctamente" << endl;
}
void Operar()
{
    cout << "Nomenclatura de las operaciones" << endl;
    cout << "MatrizA o MatrizB son los nombres de las matrices" << endl;
    cout << "MatrizA|MatrizB = para la suma" << endl
         << "++MatrizA = para el incremento" << endl
         << "--MatrizA = para el decremento" << endl
         << "Numero>MatrizA = para la multiplicacion por un escalar" << endl
         << "MatrizA&MatrizB = para la multiplicacion de las matrices" << endl
         << "MatrizA+MatrizB = para la suma dentro del espacio vectorial" << endl
         << "Numero*MatrizA = para la multiplicacion dentro del espacio vectorial" << endl;
    string cadena = "";
    cout << "Ingrese la cadena de la operacion: " << endl;
    cin >> cadena;
    int **matrizAuxiliar = NULL;
    int determinante = 0; //variable que almacena el determinante
    int escalar = 0;
    string num = "";  //string que almacena el escalar de la cadena al contener el signo >
    string num2 = ""; //string que almacena el escalar de la cadena al contener el signo *
    int espacio = 0;
    for (int i = 0; i < cadena.length(); i++)
    {
        if (cadena[i] == '>')
        {
            num = cadena.substr(0, i);
        }
        else if (cadena[i] == '*')
        {
            num2 = cadena.substr(0, i);
        }
    }
    escalar = atoi(num.c_str());  //convierte el numero que acompaña a > a un entero
    espacio = atoi(num2.c_str()); //convierte el numero que acompaña a * a un entero

    for (int i = 0; i < matrices.size(); i++)
    {
        for (int j = 0; j < matrices.size(); j++)
        {
            if (cadena == matrices[i]->getNombre() + "|" + matrices[j]->getNombre() && matrices[i]->getTam() == matrices[j]->getTam())
            {
                matrizAuxiliar = matrices[i]->suma(llenadas[i], llenadas[j], matrices[i]->getTam());
                cout << "La matriz resultante de sumar a " << matrices[i]->getNombre() << " y " << matrices[j]->getNombre() << " es: " << endl;
                matrices[j]->printMatrix(matrizAuxiliar, matrices[i]->getTam());
                matrices[i]->liberarMatriz(matrizAuxiliar, matrices[i]->getTam());
            }
            else if (cadena == matrices[i]->getNombre() + "&" + matrices[j]->getNombre() && matrices[i]->getTam() == matrices[j]->getTam())
            {
                matrizAuxiliar = matrices[i]->producto(llenadas[i], llenadas[j], matrices[i]->getTam());
                cout << "La matriz resultante de multiplicar a " << matrices[i]->getNombre() << " y " << matrices[j]->getNombre() << " es: " << endl;
                matrices[j]->printMatrix(matrizAuxiliar, matrices[i]->getTam());
                matrices[i]->liberarMatriz(matrizAuxiliar, matrices[i]->getTam());
            }
            else if (cadena == matrices[i]->getNombre() + "+" + matrices[j]->getNombre() && matrices[i]->getTam() == matrices[j]->getTam())
            {
                matrizAuxiliar = matrices[i]->suma_espacio(llenadas[i], llenadas[j], matrices[i]->getTam());
                cout << "La matriz resultante de sumar dentro del espacio vectorial a " << matrices[i]->getNombre() << " y " << matrices[j]->getNombre() << " es: " << endl;
                matrices[j]->printMatrix(matrizAuxiliar, matrices[i]->getTam());
                matrices[i]->liberarMatriz(matrizAuxiliar, matrices[i]->getTam());
            }
        }
        if (cadena == "++" + matrices[i]->getNombre())
        {
            determinante = matrices[i]->determinante(llenadas[i], matrices[i]->getTam());
            matrizAuxiliar = matrices[i]->incremento(llenadas[i], matrices[i]->getTam(), determinante);
            cout << "La matriz resultante de incrementar a " << matrices[i]->getNombre() << " es: " << endl;
            matrices[i]->printMatrix(matrizAuxiliar, matrices[i]->getTam());
            matrices[i]->liberarMatriz(matrizAuxiliar, matrices[i]->getTam());
        }
        else if (cadena == "--" + matrices[i]->getNombre())
        {
            determinante = matrices[i]->determinante(llenadas[i], matrices[i]->getTam());
            matrizAuxiliar = matrices[i]->decremento(llenadas[i], matrices[i]->getTam(), determinante);
            cout << "La matriz resultante de decrementar a " << matrices[i]->getNombre() << " es: " << endl;
            matrices[i]->printMatrix(matrizAuxiliar, matrices[i]->getTam());
            matrices[i]->liberarMatriz(matrizAuxiliar, matrices[i]->getTam());
        }
        else if (cadena == num + ">" + matrices[i]->getNombre())
        {
            matrizAuxiliar = matrices[i]->multiplicacion_escalar(llenadas[i], escalar, matrices[i]->getTam());
            cout << "La matriz resultante de multiplicar a " << matrices[i]->getNombre() << " por " << escalar << " es: " << endl;
            matrices[i]->printMatrix(matrizAuxiliar, matrices[i]->getTam());
            matrices[i]->liberarMatriz(matrizAuxiliar, matrices[i]->getTam());
        }
        else if (cadena == num2 + "*" + matrices[i]->getNombre())
        {
            determinante = matrices[i]->determinante(llenadas[i], matrices[i]->getTam());
            matrizAuxiliar = matrices[i]->multiplicacion_espacio(llenadas[i], matrices[i]->getTam(), determinante, espacio);
            cout << "La matriz resultante de multiplicar en el espacio a " << matrices[i]->getNombre() << " por el escalar " << num2 << " es: " << endl;
            matrices[i]->printMatrix(matrizAuxiliar, matrices[i]->getTam());
            matrices[i]->liberarMatriz(matrizAuxiliar, matrices[i]->getTam());
        }
    }
}