#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include<windows.h>

using namespace std;

void imprimir_matriz (vector<vector<int>> &matriz, int filas, int columnas, vector<int> &ofertas, vector<int> &demandas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << ' ';
        }
        cout << ofertas[i] <<'\n';
        if (i == filas - 1) {
            for (int j = 0; j < columnas; j++) {
                cout << demandas[j] << ' ';
            }
            cout << '\n';
        } 

    }
}


int main() {
    int m, n; // m: número de filas, n: número de columnas
    cout << "Ingrese el numero de filas (m): ";
    cin >> m;
    cout << "Ingrese el numero de columnas (n): ";
    cin >> n;

    vector<vector<int>> costos (m, vector<int>(n, 0));


    vector<int> oferta(m);
    vector<int> demanda(n);


    vector<vector<int>> final(m, vector<int>(n, 0));

    int option;
    do {
        system("cls");
        cout << "Matriz de Costos :\n";
        imprimir_matriz(costos, m, n, oferta, demanda);


        cout << "Matriz de asignacion (sin ofertas ni demandas):\n";
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << final[i][j] << " ";
            }
            cout << endl;
        }

        int costo_total = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                costo_total += costos[i][j] * final[i][j];
            }
        }
        cout << "Resultado Final: "<< '\n';
        cout << costo_total << '\n';


        cout << "\nOpciones:\n0. Redimencionar Filas y Columnas \n1. Cambiar matriz de costos\n2. Cambia ofertas \n3. Cambiar demandas \n4. Hallar Matriz de Asignacion \n5. Salir \n Elija una opcion: ";
        cin >> option;

        if (option == 0) {
            system("cls");
            cout << "Ingrese el nuevo numero de filas (m): ";
            cin >> m;
            cout << "Ingrese el nuevo numero de columnas (n): ";
            cin >> n;
            costos.clear();
            oferta.clear();
            demanda.clear();
            final.clear();
            costos.clear();
            costos.resize(m, vector<int>(n, 0));
            oferta.resize(m, 0);
            demanda.resize(n, 0);
            final.resize(m, vector<int>(n, 0));
        } else if (option == 1) {
            system("cls");

            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    cout << "Ingrese la matriz de costos:\n";
                    cout << "insertar en fila " << i << " y columna " << j << "\n";
                    imprimir_matriz(costos, m, n, oferta, demanda);
                    cin >> costos[i][j];
                    system("cls");
                }
            }
            cout << endl;

        } else if (option == 2) {
            system("cls");
            for (int i = 0; i < m; ++i) {
                cout << "Ingrese las ofertas:\n";
                cout << "insertar oferta fila numero: " << i << '\n';
                imprimir_matriz(costos, m, n, oferta, demanda);
                cin >> oferta[i];
                system("cls");
            }
            cout << endl;

        } else if (option == 3) {
            system("cls");
            for (int j = 0; j < n; ++j) {
                cout << "Ingrese las demandas:\n";
                cout << "insertar demanda columna numero: :" << j << '\n';
                imprimir_matriz(costos, m, n, oferta, demanda);
                cin >> demanda[j];
                system("cls");
            }
            cout << endl;
        } else if (option == 4) {
            while (true) {
                // Buscar la mayor oferta
                int indice_oferta_max = -1;
                int oferta_max = 0;
                for (int i = 0; i < m; ++i) {
                    if (oferta[i] > oferta_max) {
                        // se encuentra la mayor oferta
                        oferta_max = oferta[i];
                        // se guarda su indice
                        indice_oferta_max = i;
                    }
                }

                // Si no hay más ofertas, salir
                if (indice_oferta_max == -1) break;

                // Calcular el promedio de costos en la fila
                double sum = 0;
                for (int j = 0; j < n; ++j) {
                    sum += costos[indice_oferta_max][j];
                }
                double promedio = sum / n;

                // Buscar el costo más cercano al promedio
                int indice_del_mas_cercano_al_promedio = -1;
                double closestDiff = 1e9; // Infinito
                //
                // se pasa por todos los costos que esten disponibles (cuando la demanda de la columna aun necesite asignacion)
                for (int j = 0; j < n; ++j) {
                    if (demanda[j] > 0) { // si es negativo ya no es necesario pasar por la columna de esa demanda 
                        double diff = abs(costos[indice_oferta_max][j] - promedio);
                        if (diff < closestDiff) {
                            closestDiff = diff;
                            indice_del_mas_cercano_al_promedio = j;
                        }
                    }
                }

                // siendo j el costo mas cercano al promedio se elige la columna para asignar la oferta ( siempre y cuando aun haya una )

                // Asignar la oferta
                if (indice_del_mas_cercano_al_promedio != -1) {
                    int quantity = min(oferta[indice_oferta_max], demanda[indice_del_mas_cercano_al_promedio]);
                    final[indice_oferta_max][indice_del_mas_cercano_al_promedio] = quantity;
                    oferta[indice_oferta_max] -= quantity;
                    demanda[indice_del_mas_cercano_al_promedio] -= quantity;
                }
            }


        } 
    } while (option != 5);



    return 0;
}

