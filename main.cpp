#include "Tablero.h"
#include <algorithm>
#include <vector>
#include <climits>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;


/**
 Esta función evalúa el estado del tablero y devuelve un puntaje según si un jugador ha ganado.

 @param tablero Un puntero al objeto 'Tablero' que contiene el estado del juego.

 @return Un entero que indica el puntaje:
         - 10 si el jugador 2 (IA) ha ganado,
         - -10 si el jugador 1 (usuario) ha ganado,
         - 0 si no hay ganador aún.
 */
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

/*
 Esta funcion Implementa el algoritmo Minimax con poda alfa-beta para decidir el mejor movimiento en un juego.
 
 @param tablero Puntero a un objeto Tablero que representa el estado actual del juego.
 @param ia Un booleano que indica si es el turno del agente o del jugador (1 y 0 respectivamente)
 @param profundidad Un valor entero que indica la profundidad del árbol de búsqueda.
 @param alfa El valor máximo que el jugador puede asegurar en su turno
 @param beta El valor mínimo que el jugador puede asegurar en su turno
 
 @return El mejor puntaje que la IA o el jugador pueden obtener desde el estado actual del tablero.
          Los puntajes son 10 (victoria del agente), -10 (victoria del jugador), y 0 para el empate.
 */
int minimax(Tablero* tablero, bool ia, int profundidad, int alfa, int beta) {
    int puntaje = evaluar(tablero);

    if (puntaje == -10 || puntaje == 10) { // Si alguien ha ganado, retornamos el puntaje.
        return puntaje;
    }

    if (tablero->tableroLleno()) { // Si el tablero está lleno, es un empate.
        return 0;
    }

    if (ia) { // Turno del agente
        int mejor = INT_MIN;
        for (int i = 0; i < tablero->getTablero().size(); i++) {
            for (int j = 0; j < tablero->getTablero()[i].size(); j++) {
                if (tablero->movimientoValido(j, i)) {
                    tablero->setCasilla(i, j, "o");
                    mejor = max(mejor, minimax(tablero, false, profundidad + 1, alfa, beta));
                    tablero->setCasilla(i, j, " ");
                    alfa = max(alfa, mejor); // Actualiza alfa
                    if (beta <= alfa) { // Poda  el arbol
                        break;
                    }
                }
            }
        }
        return mejor;
    }
    else { // Turno del jugador
        int mejor = INT_MAX;
        for (int i = 0; i < tablero->getTablero().size(); i++) {
            for (int j = 0; j < tablero->getTablero()[i].size(); j++) {
                if (tablero->movimientoValido(j, i)) {
                    tablero->setCasilla(i, j, "x");
                    mejor = min(mejor, minimax(tablero, true, profundidad + 1, alfa, beta));
                    tablero->setCasilla(i, j, " ");
                    beta = min(beta, mejor); // Actualiza beta
                    if (beta <= alfa) { // Poda el arnbol
                        break;
                    }
                }
            }
        }
        return mejor;
    }
}

/**
 Esta funcion encuenta la mejor jugada para la IA utilizando Minimax con poda alfa-beta.
 
 @param tablero Puntero al objeto Tablero que representa el estado actual del juego.
 
 @return Un par de enteros que representa la posicion de la mejor jugada para robocop
 */
pair<int, int> mejorMovimiento(Tablero* tablero) {
    tablero->mostrarTablero(); // Muestra el tablero actual.

    int mejorPuntaje = INT_MIN;
    pair<int, int> posicion = { -1, -1 };

    int alfa = INT_MIN; //se adignan los valores de alfa y beta
    int beta = INT_MAX; 

    // Recorre todas las casillas del tablero.
    for (int i = 0; i < tablero->getTablero().size(); i++) {
        for (int j = 0; j < tablero->getTablero()[i].size(); j++) {
            if (tablero->movimientoValido(j, i)) { // Verifica si la casilla está vacía.
                tablero->setCasilla(i, j, "o"); //simula un movimiento
                int puntaje = minimax(tablero, false, 0, alfa, beta);//calcula un puntaje para cada movimiento
                tablero->setCasilla(i, j, " "); //Deshace el movimiento.

                if (puntaje > mejorPuntaje) {
                    mejorPuntaje = puntaje;//actualiza el mejor puntaje
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
    int x, y, start;//start es usado para saber si empezara el jugador o robocop

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



    while (start) {//while en caso de que comience el humano
        cout << tablero->getPlayer1()[1] << " Ingrese las coordenadas de su movimiento." << endl;
        cout << "X (horizontal): "; cin >> x;
        cout << "" << endl;
        cout << "Y (vertical): "; cin >> y;
        cout << "" << endl;

        while (!tablero->movimientoValido(y - 1, x - 1)) {//buce en caso de que el movimiento sea invalido, hasdta que ingrese algo valido
            cout << tablero->getPlayer1()[1] << " Coordenadas erroneas, ingreselas nuevamente" << endl;
            cout << "X (horizontal): "; cin >> x;
            cout << "" << endl;
            cout << "Y (vertical): "; cin >> y;
            cout << "" << endl;
        }

        if (tablero->realizarMovimiento(tablero->getPlayer1(), x - 1, y - 1, 0)) {//hace el movimiento y ademas consulta si gano alguien o empato 
            break;
        }

        float inicio = clock();
        cout << "" << endl;
        cout << "robocop esta pensando." << endl;
        cout << "" << endl;
        pair<int, int> par = mejorMovimiento(tablero);
        float final = clock();
        cout << "robocop se demoro: " << (final - inicio) / 1000 << " segundos." << endl;

        if (tablero->realizarMovimiento(tablero->getPlayer2(), par.first, par.second, 0)) {//hace el movimiento y ademas consulta si gano alguien o empato 
            break;
        }
             
    }

    while (!start) {//while en caso de que comience robocop

        float inicio = clock();
        cout << "" << endl;
        cout << "robocop esta pensando." << endl;
        cout << "" << endl;
        pair<int, int> par = mejorMovimiento(tablero);
        float final = clock();
        cout << "robocop se demoro: " << (final - inicio) / 1000 << " segundos." << endl;

        if (tablero->realizarMovimiento(tablero->getPlayer2(), par.first, par.second, 0)) {//hace el movimiento y ademas consulta si gano alguien o empato 
            break;
        }

        cout << tablero->getPlayer1()[1] << " Ingrese las coordenadas de su movimiento." << endl;
        cout << "X (horizontal): "; cin >> x;
        cout << "" << endl;
        cout << "Y (vertical): "; cin >> y;
        cout << "" << endl;

        while (!tablero->movimientoValido(y - 1, x - 1)) {//buce en caso de que el movimiento sea invalido, hasdta que ingrese algo valido
            cout << tablero->getPlayer1()[1] << " Coordenadas erroneas, ingreselas nuevamente" << endl;
            cout << "X (horizontal): "; cin >> x;
            cout << "" << endl;
            cout << "Y (vertical): "; cin >> y;
            cout << "" << endl;
        }

        if (tablero->realizarMovimiento(tablero->getPlayer1(), x - 1, y - 1, 0)) {//hace el movimiento y ademas consulta si gano alguien o empato 
            break;
        }
    }

    delete tablero;
    return 0;


}

