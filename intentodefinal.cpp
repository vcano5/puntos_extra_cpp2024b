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
class Ahorcado : public Juego {
    private:
        static char datos_nombres[10][10];
        static char datos_colores[10][10];
        static char datos_paises[10][10];
        static char datos_utiles[10][10];
        static char datos_animales[10][10];
        
        string palabra;
        set<char> letrasCorrectas;
        set<char> letrasIncorrectas;
        int maxIntentos;
        
        string seleccionarPalabra() {
            int categoria;
            cout << "Seleccione una categoría:\n"
                 << "1. Nombres\n2. Colores\n3. Países\n4. Útiles\n5. Animales\n"
                 << "Categoría: ";
            cin >> categoria;
            srand(time(0));
            int indice = rand() % 10;
            
            switch (categoria) {
                case 1: return datos_nombres[indice];
                case 2: return datos_colores[indice];
                case 3: return datos_paises[indice];
                case 4: return datos_utiles[indice];
                case 5: return datos_animales[indice];
                default: return " ";
            }
        }
        
        void mostrarEstado() const {
            cout << "\nPalabra: ";
            for (char letra : palabra) {
                if (letrasCorrectas.count(letra)) cout << letra;
                else cout << "_";
            }
            cout << "\nIntentos restantes: " << maxIntentos - letrasIncorrectas.size()
                 << "\nLetras incorrectas: ";
            for (char letra : letrasIncorrectas) cout << letra << ' ';
            cout << endl;
        }

    public:
        Ahorcado() : maxIntentos(6) {
            palabra = seleccionarPalabra();
            letrasCorrectas.clear();
            letrasIncorrectas.clear();
        }

        void iniciar() override {
            char letra;
            while (enCurso && letrasIncorrectas.size() < maxIntentos) {
                mostrarEstado();
                cout << "Adivina una letra: ";
                cin >> letra;
                if (palabra.find(letra) != string::npos) {
                    letrasCorrectas.insert(letra);
                    if (letrasCorrectas.size() == set<char>(palabra.begin(), palabra.end()).size()) {
                        enCurso = 0;
                        ganador = 1;
                        cout << "\n¡Felicidades! Has adivinado la palabra: " << palabra << endl;
                    }
                } else {
                    letrasIncorrectas.insert(letra);
                }
                if (letrasIncorrectas.size() >= maxIntentos) {
                    enCurso = 0;
                    ganador = -1;
                    cout << "\nLo siento, has perdido. La palabra era: " << palabra << endl;
                }
            }
        }
};

// Inicialización de datos estáticos para Ahorcado
char Ahorcado::datos_nombres[10][10] = {"Andres", "Sofia", "Mateo", "Ana","Lucia", "Hugo", "Ian", "Carmen", "Manuel", "Maria"};
char Ahorcado::datos_colores[10][10] = {"Rojo", "Verde", "Amarillo", "Negro", "Azul", "Rosa", "Morado", "Cafe", "Blanco", "Turquesa"};
char Ahorcado::datos_paises[10][10] = {"Mexico", "Francia", "Peru", "Argentina", "Chile", "Colombia", "China", "Bolivia", "Venezuela", "Brasil"};
char Ahorcado::datos_utiles[10][10] = {"Regla", "Lapiz", "Pluma", "Cuaderno", "Pegamento", "Mochila", "Tijeras", "Colores", "Grapadora", "Libro"};
char Ahorcado::datos_animales[10][10] = {"Perro", "Gato", "Pez", "Leon", "Elefante", "Caracol", "Tortuga", "Tiburon", "Jirafa", "Tucan"};

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
	            cout << "Contrase�a: ";
	            cin >> password;
	            cout << "Repita contrase�a: ";
	            cin >> confirmacion;
	            
	            if (password != confirmacion) {
	                cout << "Las contrase�as no coinciden. Intente nuevamente.\n";
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
	        cout << "Contrase�a: ";
	        cin >> password;
	
	        for (auto& jugador : jugadores) {
	            if (jugador.getNombre() == nombre) {
	                if (jugador.verificarContrasena(password)) {
	                    jugador.resetearIntentos();
	                    cout << "Bienvenido " << nombre << ". Ultimo inicio de sesion: hoy\n";
	                    return true;
	                } else {
	                    jugador.incrementarIntentosFallidos();
	                    cout << "Contrase�a incorrecta. " << jugador.getIntentosFallidos() 
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
            case 2: {
                Ahorcado* ahorcado = new Ahorcado();
                ahorcado->iniciar();
                delete ahorcado;
                break;
            }
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
