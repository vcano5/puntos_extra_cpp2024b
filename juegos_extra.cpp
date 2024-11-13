#include <iostream>
#include <vector>
#include <memory>
#include <set>

using namespace std;

class Jugador {
	string nombre;
	int puntuacion; // Puede ser puntacion positiva y que baje por errores, o por 
	bool enturno;
};

// Gato es 3x3 casillas, ahorcado son 1xN casillas
class Casilla {
	char contenido;
	int vacio; // oculto o vacio;
};

class Juego {
	public:
		vector <Casilla> casillas;
		vector<Jugador> jugadores;
		Juego();
		int enCurso, ganador;
		void avanzarTurno();
		void iniciar();
		void comprobarGanador();
};

Juego::Juego(): enCurso(1) {
}

class Login: public Juego {
	public:
		vector<Jugador> usuarios;
		multiset<int, Casilla> contrasenas;
		vector<int> intentos;
		Juego *juego; // Un puntero para crear juegos con new y delete para poder manipularlos desde otras funciones.
		int eleccion;
		void registrarUsuario();
		void comprobarGanador(); // Comprobar que la contrasena sea correcta
		void mostrarMenu(); 
};

void Login::mostrarMenu() {
	cout << "1)\tRegistrar nuevo usuario.\n2) Jugar gato (PvP).\n3) Jugar ahorcado (PvP).\n4) Jugar gato AI\nElija una opcion: ";
	cin >> this->eleccion;
	if(eleccion == 1) {
		
	}
}


class Gato: public Juego {
	void comprobarGanador() {
		// Verificiar que las casillas tengan 3 consecutivos
		this->ganador = 1;
		this->enCurso = 0;
	}
};

class Ahorcado: public Juego {
	void comprobarGanador() {
		// todas las casillas no estan ocultas y los errores son menores al total
	}
};

int main() {
	Login m;
	while(m.enCurso) {
		m.mostrarMenu();
		// Registrar usuarios, minimo 1
	}
	return 1;
}