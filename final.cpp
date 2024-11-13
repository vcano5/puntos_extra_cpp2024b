#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <set>
using namespace std;

// Clase base para los elementos del juego
class Casilla {
	private:
	    char contenido;
	    bool vacio;
	
	public:
	    Casilla(): contenido(' '), vacio(true) {}
	    void setContenido(char c) { contenido = c; vacio = false; }
	    char getContenido() const { return contenido; }
	    bool estaVacio() const { return vacio; }
};

class Jugador {
	private:
	    string nombre;
	    string contrasena;
	    int puntuacion;
	    bool enturno;
	    int intentos_fallidos;
	    char simbolo;
	
	public:
	    Jugador(string nombre = "", string contrasena = ""): 
	        nombre(nombre), 
	        contrasena(contrasena), 
	        puntuacion(0), 
	        enturno(false), 
	        intentos_fallidos(0),
	        simbolo(' ') {}

    string getNombre() const { 
		return nombre; 
	}
    void setNombre(const string& n) { 
		nombre = n; 
	}
    bool verificarContrasena(const string& input) const { 
		return contrasena == input; 
	}
    int getIntentosFallidos() const { 
		return intentos_fallidos; 
	}
    void incrementarIntentosFallidos() { 
		intentos_fallidos++; 
	}
    void resetearIntentos() { 
		intentos_fallidos = 0; 
	}
    void setPuntuacion(int puntos) { 
		puntuacion = puntos; 
	}
    void setTurno(bool turno) { 
		enturno = turno; 
	}
    void setSimbolo(char s) { 
		simbolo = s; 
	}
    char getSimbolo() const { 
		return simbolo; 
	}
    int getPuntuacion() const { 
		return puntuacion; 
	}
    bool getTurno() const { 
		return enturno; 
	}
    void setContrasena(const string& contra) {
		 contrasena = contra; 
	}
};

class Juego {
	public:
	    vector<Jugador> jugadores;
	    int enCurso, ganador;
	    Juego(): enCurso(1), ganador(-1) {}
	    virtual void avanzarTurno() {}
	    virtual void iniciar() {}
	    virtual void comprobarGanador() {}
};

class Gato : public Juego {
	private:
	    vector<vector<Casilla>> tablero;
	    char obtenerValorEnCasilla(int fila, int columna) const {
	        if (tablero[fila][columna].estaVacio()) {
	            return ' ';
	        }
	        return tablero[fila][columna].getContenido();
	    }
	public:
	    Gato() {
	        // Inicializar tablero 3x3
	        tablero = vector<vector<Casilla>>(3, vector<Casilla>(3));
	        enCurso = 1;
	        ganador = -1;
	    }
	
	    void mostrarTablero() const {
	        cout << "\n       |       |" << endl;
	        cout << "   " << obtenerValorEnCasilla(0,0) << "   |   " 
	             << obtenerValorEnCasilla(1,0) << "   |   " 
	             << obtenerValorEnCasilla(2,0) << endl;
	        cout << "  (1,1)|  (2,1)| (3,1)" << endl;
	        cout << "----------------------" << endl;
	        cout << "       |       |" << endl;
	        cout << "   " << obtenerValorEnCasilla(0,1) << "   |   " 
	             << obtenerValorEnCasilla(1,1) << "   |   " 
	             << obtenerValorEnCasilla(2,1) << endl;
	        cout << "  (1,2)|  (2,2)| (3,2)" << endl;
	        cout << "-----------------------" << endl;
	        cout << "       |       |" << endl;
	        cout << "   " << obtenerValorEnCasilla(0,2) << "   |   " 
	             << obtenerValorEnCasilla(1,2) << "   |   " 
	             << obtenerValorEnCasilla(2,2) << endl;
	        cout << "  (1,3)|  (2,3)| (3,3)" << endl;
	    }
	
	    bool realizarMovimiento(int x, int y, int jugadorActual) {
	        if (x < 1 || x > 3 || y < 1 || y > 3) {
	            cout << "Posicion fuera del tablero" << endl;
	            return false;
	        }
	        
	        x--; y--;
	        
	        if (!tablero[x][y].estaVacio()) {
	            cout << "\n**** La casilla no esta vacia ****\n";
	            return false;
	        }
	
	        tablero[x][y].setContenido(jugadores[jugadorActual].getSimbolo());
	        return true;
	    }
	
	    void iniciar() override {
	        if (jugadores.size() < 2) {
	            cout << "Se necesitan dos jugadores para iniciar el juego" << endl;
	            return;
	        }
	
	        // Asignar simbolos a los jugadores si no los tienen
	        if (jugadores[0].getSimbolo() == ' ') jugadores[0].setSimbolo('X');
	        if (jugadores[1].getSimbolo() == ' ') jugadores[1].setSimbolo('O');
	
	        int turnoActual = 0;
	        int x, y;
	        
	        while (enCurso) {
	            mostrarTablero();
	            cout << "Turno de " << jugadores[turnoActual].getNombre() 
	                 << " (" << jugadores[turnoActual].getSimbolo() << ")"
	                 << "\n\t(Formato de entrada 'x,y'): ";
	            
	            if (scanf("%d,%d", &x, &y) == 2) {
	                if (realizarMovimiento(x, y, turnoActual)) {
	                    comprobarGanador();
	                    turnoActual = (turnoActual + 1) % 2;
	                }
	            } else {
	                cout << "Formato invalido. Use x,y (ejemplo: 1,1)" << endl;
	                cin.clear();
	                cin.ignore(1000, '\n');
	            }
	        }
	
	        mostrarTablero();
	        if (ganador != -1) {
	            cout << "\nEl juego termino. El ganador es: " 
	                 << jugadores[ganador].getNombre() << endl;
	            jugadores[ganador].setPuntuacion(jugadores[ganador].getPuntuacion() + 1);
	        } else {
	            cout << "\nEl juego termino en EMPATE" << endl;
	        }
	    }
	
	    void comprobarGanador() override {
	        // Comprobar filas
	        for (int i = 0; i < 3; i++) {
	            if (!tablero[i][0].estaVacio() && 
	                tablero[i][0].getContenido() == tablero[i][1].getContenido() && 
	                tablero[i][1].getContenido() == tablero[i][2].getContenido()) {
	                enCurso = 0;
	                ganador = (tablero[i][0].getContenido() == jugadores[0].getSimbolo()) ? 0 : 1;
	                return;
	            }
	        }
	
	        // Comprobar columnas
	        for (int i = 0; i < 3; i++) {
	            if (!tablero[0][i].estaVacio() && 
	                tablero[0][i].getContenido() == tablero[1][i].getContenido() && 
	                tablero[1][i].getContenido() == tablero[2][i].getContenido()) {
	                enCurso = 0;
	                ganador = (tablero[0][i].getContenido() == jugadores[0].getSimbolo()) ? 0 : 1;
	                return;
	            }
	        }
	
	        // Comprobar diagonales
	        if (!tablero[0][0].estaVacio() && 
	            tablero[0][0].getContenido() == tablero[1][1].getContenido() && 
	            tablero[1][1].getContenido() == tablero[2][2].getContenido()) {
	            enCurso = 0;
	            ganador = (tablero[0][0].getContenido() == jugadores[0].getSimbolo()) ? 0 : 1;
	            return;
	        }
	
	        if (!tablero[0][2].estaVacio() && 
	            tablero[0][2].getContenido() == tablero[1][1].getContenido() && 
	            tablero[1][1].getContenido() == tablero[2][0].getContenido()) {
	            enCurso = 0;
	            ganador = (tablero[0][2].getContenido() == jugadores[0].getSimbolo()) ? 0 : 1;
	            return;
	        }
	
	        // Comprobar empate
	        bool tableroLleno = true;
	        for (int i = 0; i < 3; i++) {
	            for (int j = 0; j < 3; j++) {
	                if (tablero[i][j].estaVacio()) {
	                    tableroLleno = false;
	                    break;
	                }
	            }
	        }
	        
	        if (tableroLleno) {
	            enCurso = 0;
	            ganador = -1; // Empate
	        }
	    }
};

class Login: public Juego {
	private:
	    bool registrarJugador() {
	        string nombre, password, confirmacion;
	        char simbolo;
	        cout << "---- Registro de nuevo usuario -----\n";
	        cout << "Usuario: ";
	        cin >> nombre;
	        
	        // Verificar si el usuario ya existe
	        for (const auto& jugador : jugadores) {
	            if (jugador.getNombre() == nombre) {
	                cout << "El usuario ya existe.\n";
	                return false;
	            }
	        }
	        
	        do {
	            cout << "Contraseña: ";
	            cin >> password;
	            cout << "Repita contraseña: ";
	            cin >> confirmacion;
	            
	            if (password != confirmacion) {
	                cout << "Las contraseñas no coinciden. Intente nuevamente.\n";
	            }
	        } while (password != confirmacion);
	        
	        cout << "Simbolo preferido: ";
	        cin >> simbolo;
	        
	        Jugador nuevoJugador(nombre, password);
	        nuevoJugador.setSimbolo(simbolo);
	        jugadores.push_back(nuevoJugador);
	        cout << "Registro completado correctamente.\n";
	        return true;
	    }
	
	    bool iniciarSesion() {
	        string nombre, password;
	        cout << "Usuario: ";
	        cin >> nombre;
	        cout << "Contraseña: ";
	        cin >> password;
	
	        for (auto& jugador : jugadores) {
	            if (jugador.getNombre() == nombre) {
	                if (jugador.verificarContrasena(password)) {
	                    jugador.resetearIntentos();
	                    cout << "Bienvenido " << nombre << ". Ultimo inicio de sesion: hoy\n";
	                    return true;
	                } else {
	                    jugador.incrementarIntentosFallidos();
	                    cout << "Contraseña incorrecta. " << jugador.getIntentosFallidos() 
	                         << " intentos incorrectos\n";
	                    if (jugador.getIntentosFallidos() >= 3) {
	                        cout << "Cuenta bloqueada por multiples intentos fallidos.\n";
	                        return false;
	                    }
	                }
	                return false;
	            }
	        }
	        cout << "Usuario no encontrado.\n";
	        return false;
	    }
	
	public:
	    Juego* juego;
	    int eleccion;
	
	    void mostrarMenu() {
	        int opcion;
	        bool sesionIniciada = false;
	
	        do {
	            cout << "\n1) Registrar nuevo usuario\n"
	                 << "2) Iniciar sesion\n"
	                 << "3) Salir\n"
	                 << "Elija una opcion: ";
	            cin >> opcion;
	
	            switch (opcion) {
	                case 1:
	                    registrarJugador();
	                    break;
	                case 2:
	                    sesionIniciada = iniciarSesion();
	                    if (sesionIniciada) {
	                        mostrarMenuJuegos();
	                    }
	                    break;
	                case 3:
	                    cout << "Hasta luego!\n";
	                    break;
	                default:
	                    cout << "Opcion invalida\n";
	            }
	        } while (opcion != 3 && !sesionIniciada);
	    }
	
	    void mostrarMenuJuegos() {
	        cout << "\n1) Jugar gato (PvP)\n"
	             << "2) Jugar ahorcado (PvP)\n"
	             << "3) Jugar gato AI\n"
	             << "4) Cerrar sesion\n"
	             << "Elija una opcion: ";
	        cin >> eleccion;
	        
	        switch(eleccion) {
	            case 1: {
	                if (jugadores.size() >= 2) {
	                    Gato* gato = new Gato();
	                    gato->jugadores = jugadores;
	                    gato->iniciar();
	                    delete gato;
	                } else {
	                    cout << "Se necesitan al menos 2 jugadores registrados para jugar.\n";
	                }
	                break;
	            }
	            case 2:
	                cout << "Ahorcado en desarrollo...\n";
	                break;
	            case 3:
	                cout << "Gato AI en desarrollo...\n";
	                break;
	            case 4:
	                cout << "Cerrando sesion...\n";
	                break;
	            default:
	                cout << "Opcion invalida\n";
	        }
	    }
};

int main() {
    Login m;
    m.mostrarMenu();
    return 0;
}