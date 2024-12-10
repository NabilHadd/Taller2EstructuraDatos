#pragma once
#include <iostream>
#include <string>
#include <vector>

class Tablero {
private:

	std::vector<std::vector<std::string>> tablero;
	std::vector<std::string> player1;
	std::vector<std::string> player2;

public:

	Tablero(std::string player1, std::string player2);
	~Tablero();

	void setTablero();
	std::vector<std::vector<std::string>> getTablero();

	void setPlayer1(std::string nombre);
	std::vector<std::string> getPlayer1();

	void setPlayer2(std::string nombre);
	std::vector<std::string> getPlayer2();
	
	void mostrarTablero();
	
	void setCasilla(int x, int y, std::string symbol);
	bool realizarMovimiento(std::vector<std::string> player, int x, int y, bool test);
	bool dfs(int x, int y, int dx, int dy, int count, std::vector<std::string> player);
	bool movimientoValido(int x, int y);
	bool tableroLleno();
	bool finDelJuego(int x, int y, std::vector<std::string> player);


};