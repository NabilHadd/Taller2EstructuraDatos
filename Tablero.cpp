#include "Tablero.h"
#include <vector>
#include <iostream>
#include <string>


Tablero::Tablero(std::string player1, std::string player2) {
	this->setTablero();
	this->setPlayer1(player1);
	this->setPlayer2(player2);
}
Tablero::~Tablero() {
	std::cout << "Se ha destruido el tablero" << std::endl;
}


void Tablero::setTablero() {
	std::vector<std::string> vectorAux = {" "," "," "};
	this->tablero = { vectorAux, vectorAux, vectorAux };
}
void Tablero::setCasilla(int x, int y, std::string symbol) {
	this->tablero[y][x] = symbol;
}
std::vector<std::vector<std::string>> Tablero::getTablero() {
	return this->tablero;
}

void Tablero::setPlayer1(std::string nombre) {
	this->player1 = {"x", nombre};
}
std::vector<std::string> Tablero::getPlayer1() {
	return this->player1;
}

void Tablero::setPlayer2(std::string nombre) {
	this->player2 = { "o", nombre };
}
std::vector<std::string> Tablero::getPlayer2() {
	return this->player2;
}


void Tablero::mostrarTablero() {
	std::cout << "  1    2    3 " << std::endl;
	for (int i = 0; i < this->tablero.size(); i++) {
		std::cout << "    |   |   " << std::endl;
		for (int j = 0; j < this->tablero[i].size(); j++) {
			switch (j)
			{
			case 0:
				std::cout << i + 1 << " " << this->tablero[i][j] << " |";
				break;
			case 1:
				std::cout << " " << this->tablero[i][j] << " |";
				break;
			case 2:
				std::cout << " " << this->tablero[i][j]<< " ";
				break;
			default:
				break;
			}
			
		}
		std::cout << "" << std::endl;
		if (i == 2) {
			std::cout << "    |   |   " << std::endl;
		}
		else {
			std::cout << " ___|___|___" << std::endl;
		}
	}
}
bool Tablero::realizarMovimiento(std::vector<std::string> player, int x, int y, bool test) {
	this->tablero[y][x] = player[0];
	
	if (!test) {
		mostrarTablero();

		if (this->finDelJuego(y, x, player)) {
			std::cout << "\n=====================================================" << std::endl;
			std::cout << "Ganador: " << player[1] << " quien usaba: " << player[0] << std::endl;
			std::cout << "=====================================================" << std::endl;

			return 1;
		}
		if (this->tableroLleno() && !this->finDelJuego(x, y, player)) {
			std::cout << "\n=====================================================" << std::endl;
			std::cout << "Empate debido a que se lleno el tablero.";
			std::cout << "=====================================================" << std::endl;

			return 1;
		}
	}
	
	return 0;
}


bool Tablero::movimientoValido(int x, int y) {
	if (tablero[x][y] == " ") {
		return 1;
	}
	else {
		return 0;
	}
}
bool Tablero::tableroLleno() {
	for (int i = 0; i < this->tablero.size(); i++) {
		for (int j = 0; j < this->tablero[i].size(); j++) {
			if (tablero[i][j] == " ") {
				return 0;
			}
		}
	}
	return 1;
}

bool Tablero::dfs(int x, int y, int dx, int dy, int count, std::vector<std::string> player) {
	if (x < 0 || y<0 || x >= this->tablero.size() || y >= this->tablero.size() || tablero[x][y] != player[0]) {
		return 0;
	}
	if (count == 3) {
		return 1;
	}
	return this->dfs(x + dx, y + dy, dx, dy, count + 1, player);
}
bool Tablero::finDelJuego(int x, int y, std::vector<std::string> player){
	if (tablero[x][y] == player[0]) {
		if (this->dfs(x, y, 1, 1, 1, player)   ||
			this->dfs(x, y, 1, 0, 1, player)   ||
			this->dfs(x, y, 0, 1, 1, player)   ||
			this->dfs(x, y, -1, 0, 1, player)  ||
			this->dfs(x, y, 0, -1, 1, player)  ||
			this->dfs(x, y, -1, -1, 1, player) ||
			this->dfs(x, y, 1, -1, 1, player)  ||
			this->dfs(x, y, -1, 1, 1, player))  {
			return 1;
		}
	}
	return 0;
}