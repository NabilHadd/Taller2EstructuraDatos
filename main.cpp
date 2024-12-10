#include "Tablero.h"
#include <algorithm>
#include <vector>
#include <climits>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

int evaluar(Tablero* tablero) {

    for (int i = 0; i < tablero->getTablero().size(); i++) {
        for (int j = 0; j < tablero->getTablero().size(); j++) {
            if (tablero->finDelJuego(i, j, tablero->getPlayer2())) {
                return 10;
            }if (tablero->finDelJuego(i, j, tablero->getPlayer1())) {
                return -10;
            }
            else {
                return 0;
            }
        }
    }
}

int minimax(Tablero* tablero, bool ia, int profundidad, int alfa, int beta) {
    int puntaje = evaluar(tablero);

    if (puntaje == -10 || puntaje == 10) { // caso base: alguien "ganó"
        return puntaje;
    }

    if (tablero->tableroLleno()) { // caso base: empate
        return 0;
    }

    if (ia) { 
        int mejor = INT_MIN;
        for (int i = 0; i < tablero->getTablero().size(); i++) {
            for (int j = 0; j < tablero->getTablero()[i].size(); j++) {
                if (tablero->movimientoValido(j, i)) {
                    tablero->setCasilla(i, j, "o");  
                    mejor = max(mejor, minimax(tablero, false, profundidad + 1, alfa, beta));
                    tablero->setCasilla(i, j, " "); 
                    alfa = max(alfa, mejor);
                    if (beta <= alfa) { 
                        break;
                    }
                }
            }
        }
        return mejor;
    }
    else { 
        int mejor = INT_MAX;
        for (int i = 0; i < tablero->getTablero().size(); i++) {
            for (int j = 0; j < tablero->getTablero()[i].size(); j++) {
                if (tablero->movimientoValido(j, i)) {
                    tablero->setCasilla(i, j, "x"); 
                    mejor = min(mejor, minimax(tablero, true, profundidad + 1, alfa, beta));
                    tablero->setCasilla(i, j, " "); 
                    beta = min(beta, mejor); 
                    if (beta <= alfa) {
                        break;
                    }
                }
            }
        }
        return mejor;
    }
}

pair<int, int> mejorMovimiento(Tablero* tablero) {
    tablero->mostrarTablero();

    int mejorPuntaje = INT_MIN;
    pair<int, int> posicion = { -1, -1 };

    int alfa = INT_MIN; 
    int beta = INT_MAX; 

    for (int i = 0; i < tablero->getTablero().size(); i++) {
        for (int j = 0; j < tablero->getTablero()[i].size(); j++) {
            if (tablero->movimientoValido(j, i)) {
                tablero->setCasilla(i, j, "o"); 
                int puntaje = minimax(tablero, false, 0, alfa, beta); 
                tablero->setCasilla(i, j, " "); 
                if (puntaje > mejorPuntaje) {
                    mejorPuntaje = puntaje;
                    posicion = { i, j };
                }
            }
        }
    }

    return posicion;
}

int main(){

    cout << "========================================" << endl;
    cout << "|| Bienvenido a 3 en ralla VS robocop ||" << endl;
    cout << "========================================" << endl;
    cout << "" << endl;

    string player1;
    int x, y, start;

    cout << "Ingrese el nombre del valiente." << endl;
    cout << "Jugador (x): ";
    cin >> player1;
    cout << "" << endl;

    cout << "¿Quien empieza? (" << player1 <<" ->1, Robocop ->0)" << endl;
    cout << "respuesta: ";
    cin >> start;
    cout << "" << endl;

    Tablero* tablero = new Tablero(player1, "Robocop");
    tablero->mostrarTablero();



    while (start) {
        cout << tablero->getPlayer1()[1] << " Ingrese las coordenadas de su movimiento." << endl;
        cout << "X (horizontal): "; cin >> x;
        cout << "" << endl;
        cout << "Y (vertical): "; cin >> y;
        cout << "" << endl;

        while (!tablero->movimientoValido(y - 1, x - 1)) {
            cout << tablero->getPlayer1()[1] << " Coordenadas erroneas, ingreselas nuevamente" << endl;
            cout << "X (horizontal): "; cin >> x;
            cout << "" << endl;
            cout << "Y (vertical): "; cin >> y;
            cout << "" << endl;
        }

        if (tablero->realizarMovimiento(tablero->getPlayer1(), x - 1, y - 1, 0)) {
            break;
        }

        float inicio = clock();
        cout << "" << endl;
        cout << "robocop esta pensando." << endl;
        cout << "" << endl;
        pair<int, int> par = mejorMovimiento(tablero);
        float final = clock();
        cout << "robocop se demoro: " << (final - inicio) / 1000 << " segundos." << endl;

        if (tablero->realizarMovimiento(tablero->getPlayer2(), par.first, par.second, 0)) {
            break;
        }
             
    }

    while (!start) {

        float inicio = clock();
        cout << "" << endl;
        cout << "robocop esta pensando." << endl;
        cout << "" << endl;
        pair<int, int> par = mejorMovimiento(tablero);
        float final = clock();
        cout << "robocop se demoro: " << (final - inicio) / 1000 << " segundos." << endl;

        if (tablero->realizarMovimiento(tablero->getPlayer2(), par.first, par.second, 0)) {
            break;
        }

        cout << tablero->getPlayer1()[1] << " Ingrese las coordenadas de su movimiento." << endl;
        cout << "X (horizontal): "; cin >> x;
        cout << "" << endl;
        cout << "Y (vertical): "; cin >> y;
        cout << "" << endl;

        while (!tablero->movimientoValido(y - 1, x - 1)) {
            cout << tablero->getPlayer1()[1] << " Coordenadas erroneas, ingreselas nuevamente" << endl;
            cout << "X (horizontal): "; cin >> x;
            cout << "" << endl;
            cout << "Y (vertical): "; cin >> y;
            cout << "" << endl;
        }

        if (tablero->realizarMovimiento(tablero->getPlayer1(), x - 1, y - 1, 0)) {
            break;
        }
    }

    delete tablero;
    return 0;


}

