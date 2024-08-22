#include <iostream>
#include <string>
#include <windows.h>  // Para la función gotoxy

#define MAX_VIAJEROS 100

using namespace std;

// Definiciones de colores
const int COLOR_BLACK = 0;
const int COLOR_WHITE = 15;
const int COLOR_LIGHT_BLUE = 9;
const int COLOR_LIGHT_YELLOW = 14;
const int COLOR_LIGHT_GREEN = 10;

// Estructuras
struct Viajero {
    int id;
    string nombre;
    string direccion;
};

struct Ingreso {
    int idViajero;
    string fechaIngreso;
    string lugarIngreso;
};

struct Salida {
    int idViajero;
    string fechaSalida;
    string lugarSalida;
};

// Funciones
void agregarViajero();
void registrarIngreso();
void registrarSalida();
void consultarViajero();
void eliminarViajero();
void generarReporte();
void menu();
void gotoxy(int x, int y);
void setColor(int textColor, int bgColor);

// Arreglos para almacenar la información
Viajero viajeros[MAX_VIAJEROS];
Ingreso ingresos[MAX_VIAJEROS];
Salida salidas[MAX_VIAJEROS];

// Variables globales para contar el número de registros
int totalViajeros = 0;
int totalIngresos = 0;
int totalSalidas = 0;

// Función para mover el cursor a una posición específica en la consola
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole, coord);
}

// Función para establecer el color del texto y el fondo
void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void menu() {
    int opcion;
    const int menuWidth = 70;  // Ancho del cuadro del menú
    const int menuHeight = 25; // Alto del cuadro del menú

    do {
        gotoxy(10, 8); // Mover el cursor a la posición inicial

        // Dibuja el marco del menú
        
        for (int i = 0; i < menuWidth; ++i) {
            gotoxy(i, 0);
            cout << '-'; // Parte superior del cuadro
            gotoxy(i, menuHeight - 1);
            cout << '-'; // Parte inferior del cuadro
        }

        for (int i = 1; i < menuHeight - 1; ++i) {
            gotoxy(0, i);
            cout << '|'; // Lado izquierdo del cuadro
            gotoxy(menuWidth - 1, i);
            cout << '|'; // Lado derecho del cuadro
        }

        gotoxy(10, 8); // Escribe la esquina superior izquierda del cuadro
        cout << '+';
        gotoxy(menuWidth - 1, 0); // Escribe la esquina superior derecha del cuadro
        cout << '+';
        gotoxy(0, menuHeight - 1); // Escribe la esquina inferior izquierda del cuadro
        cout << '+';
        gotoxy(menuWidth - 1, menuHeight - 1); // Escribe la esquina inferior derecha del cuadro
        cout << '+';

        // Imprime el contenido del menú dentro del cuadro
        
        gotoxy(2, 2);
        cout << "Sistema de Control de Migracion"<<endl;

        gotoxy(2, 4);
        cout << "1. Ingresar nuevo viajero"<<endl;

        gotoxy(2, 6);
        cout << "2. Registrar ingreso"<<endl;

        gotoxy(2, 8);
        cout << "3. Registrar salida"<<endl;

        gotoxy(2, 10);
        cout << "4. Consultar informacion de viajero"<<endl;

        gotoxy(2, 12);
        cout << "5. Eliminar viajero"<<endl;

        gotoxy(2, 14);
        cout << "6. Generar reportes"<<endl;
        gotoxy(2, 16);
        cout << "0. Salir"<<endl;

        gotoxy(2, 18); // Espacio para el input
        cout << "Seleccione una opcion: "<<endl;;
        cin >> opcion;
        
        // Limpiar el buffer de entrada
        cin.ignore();

        switch(opcion) {
            case 1: agregarViajero(); break;
            case 2: registrarIngreso(); break;
            case 3: registrarSalida(); break;
            case 4: consultarViajero(); break;
            case 5: eliminarViajero(); break;
            case 6: generarReporte(); break;
            case 0: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion invalida.\n"; break;
        }
    } while(opcion != 0);
}

void agregarViajero() {
    if (totalViajeros < MAX_VIAJEROS) {
        const int boxWidth = 50;
        const int boxHeight = 12;

        // Dibuja el marco del cuadro
        
        for (int i = 0; i < boxWidth; ++i) {
            gotoxy(i, 0);
            cout << ' '; // Parte superior del cuadro
            gotoxy(i, boxHeight - 1);
            cout << ' '; // Parte inferior del cuadro
        }

        for (int i = 1; i < boxHeight - 1; ++i) {
            gotoxy(0, i);
            cout << ' '; // Lado izquierdo del cuadro
            gotoxy(boxWidth - 1, i);
            cout << ' '; // Lado derecho del cuadro
        }

        gotoxy(10, 8); // Escribe la esquina superior izquierda del cuadro
        cout << '+';
        gotoxy(boxWidth - 1, 0); // Escribe la esquina superior derecha del cuadro
        cout << '+';
        gotoxy(0, boxHeight - 1); // Escribe la esquina inferior izquierda del cuadro
        cout << '+';
        gotoxy(boxWidth - 1, boxHeight - 1); // Escribe la esquina inferior derecha del cuadro
        cout << '+';

        // Imprime el contenido dentro del cuadro
        
        gotoxy(3, 1);cout << "Ingrese ID del viajero: "<<endl;

        Viajero nuevoViajero;
		cin >> nuevoViajero.id;
        cin.ignore();  // Limpiar el buffer de entrada

        gotoxy(3, 5);cout << "Ingrese nombre del viajero: "<<endl;
        getline(cin, nuevoViajero.nombre);

        gotoxy(3, 7);cout << "Ingrese direccion del viajero: "<<endl;
        getline(cin, nuevoViajero.direccion);

        viajeros[totalViajeros] = nuevoViajero;
        totalViajeros++;

        gotoxy(3, 9);cout << "Viajero agregado con exito."<<endl;

        // Restablece el color a blanco sobre negro
        setColor(COLOR_WHITE, COLOR_BLACK);
    } else {
        cout << "No se pueden agregar mas viajeros.\n"<<endl;
    }
}

void registrarIngreso() {
    if (totalIngresos < MAX_VIAJEROS) {
        Ingreso nuevoIngreso;
        gotoxy(0, 2); // Mueve el cursor a la fila 2
        cout << "Ingrese ID del viajero: "<<endl;
        cin >> nuevoIngreso.idViajero;
        cin.ignore();  // Limpiar el buffer de entrada

        gotoxy(0, 4); // Mueve el cursor a la fila 4
        cout << "Ingrese fecha de ingreso (dd/mm/yyyy): "<<endl;
        getline(cin, nuevoIngreso.fechaIngreso);

        gotoxy(0, 6); // Mueve el cursor a la fila 6
        cout << "Ingrese lugar de ingreso: "<<endl;
        getline(cin, nuevoIngreso.lugarIngreso);
        
        ingresos[totalIngresos] = nuevoIngreso;
        totalIngresos++;
        gotoxy(0, 8); // Mueve el cursor a la fila 8
        cout << "Ingreso registrado con exito.\n"<<endl;
    } else {
        gotoxy(0, 8); // Mueve el cursor a la fila 8 para mostrar el mensaje de error
        cout << "No se pueden registrar mas ingresos.\n"<<endl;
    }
}

void registrarSalida() {
    if (totalSalidas < MAX_VIAJEROS) {
        Salida nuevaSalida;

        gotoxy(0, 2); // Mueve el cursor a la fila 2
        cout << "Ingrese ID del viajero: "<<endl;
        cin >> nuevaSalida.idViajero;
        cin.ignore();  // Limpiar el buffer de entrada

        gotoxy(0, 4); // Mueve el cursor a la fila 4
        cout << "Ingrese fecha de salida (dd/mm/yyyy): "<<endl;
        getline(cin, nuevaSalida.fechaSalida);

        gotoxy(0, 6); // Mueve el cursor a la fila 6
        cout << "Ingrese lugar de salida: "<<endl;
        getline(cin, nuevaSalida.lugarSalida);
        
        salidas[totalSalidas] = nuevaSalida;
        totalSalidas++;

        gotoxy(0, 8); // Mueve el cursor a la fila 8
        cout << "Salida registrada con exito.\n"<<endl;
    } else {
        gotoxy(0, 10); // Mueve el cursor a la fila 8 para mostrar el mensaje de error
        cout << "No se pueden registrar mas salidas.\n"<<endl;
    }
}

void consultarViajero() {
    int id;
    cout << "Ingrese ID del viajero a consultar: "<<endl;
    cin >> id;
    
    for (int i = 0; i < totalViajeros; i++) {
        if (viajeros[i].id == id) {
            gotoxy(20,15);cout << "ID: " << viajeros[i].id << endl;
            gotoxy(22,17);cout << "Nombre: " << viajeros[i].nombre << endl;
            gotoxy(24,19);cout << "Direccion: " << viajeros[i].direccion << endl;
            return;
        }
    }
    cout << "Viajero no encontrado.\n";
}

void eliminarViajero() {
    const int boxWidth = 40;
    const int boxHeight = 10;

    // Dibuja el marco del cuadro
   
    for (int i = 0; i < boxWidth; ++i) {
        gotoxy(i, 0);cout << ' '; // Parte superior del cuadro
        gotoxy(i, boxHeight - 1);cout << ' '; // Parte inferior del cuadro
    }

    for (int i = 1; i < boxHeight - 1; ++i) {
        gotoxy(0, i);cout << ' '; // Lado izquierdo del cuadro
        gotoxy(boxWidth - 1, i);cout << ' '; // Lado derecho del cuadro
    }

    gotoxy(10, 8); cout << '+';
    gotoxy(boxWidth - 1, 7); 
    cout << '+';
    gotoxy(5, boxHeight - 1); cout << '+';gotoxy(boxWidth - 1, boxHeight - 1); 
    cout << '+';

    // Imprime el contenido dentro del cuadro
    setColor(COLOR_BLACK, COLOR_LIGHT_BLUE);  
    gotoxy(2, 1);cout << "Ingrese ID del viajero a eliminar: "<<endl;

    int id;
    gotoxy(2, 3);
    cin >> id;

    // Buscar y eliminar el viajero
    bool encontrado = false;
    for (int i = 0; i < totalViajeros; i++) {
        if (viajeros[i].id == id) {
            encontrado = true;
            // Mover los elementos después del viajero eliminado
            for (int j = i; j < totalViajeros - 1; j++) {
                viajeros[j] = viajeros[j + 1];
            }
            totalViajeros--;
            break;
        }
    }

    // Mensaje de éxito o error
    gotoxy(2, 5);
    if (encontrado) {
        setColor(COLOR_BLACK, COLOR_LIGHT_GREEN); 
        cout << "Viajero eliminado con exito."<<endl;
    } else {
     
        cout << "Viajero no encontrado."<<endl;
    }

    
    
}

void generarReporte() {
    const int reportWidth = 60; 
    const int reportHeight = 20; 

    // Dibuja el marco del reporte
   
    for (int i = 0; i < reportWidth; ++i) {
        gotoxy(i, 0);
        cout << ' '; // Parte superior del cuadro
        gotoxy(i, reportHeight);
        cout << ' '; // Parte inferior del cuadro
    }
    
    for (int i = 1; i < reportHeight; ++i) {
        gotoxy(0, i);
        cout << ' '; // Lado izquierdo del cuadro
        gotoxy(reportWidth - 1, i);
        cout << ' '; // Lado derecho del cuadro
    }

    gotoxy(0, 0); // Escribe la esquina superior izquierda del cuadro
    cout << '+';
    gotoxy(reportWidth - 1, 0); // Escribe la esquina superior derecha del cuadro
    cout << '+';
    gotoxy(0, reportHeight); // Escribe la esquina inferior izquierda del cuadro
    cout << '+';
    gotoxy(reportWidth - 1, reportHeight); // Escribe la esquina inferior derecha del cuadro
    cout << '+';

    // Imprime el contenido del reporte dentro del cuadro
    
    gotoxy(2, 1);
    cout << "Reporte de Viajeros:";

    for (int i = 0; i < totalViajeros; i++) {
        gotoxy(2, 3 + i);
        cout << "ID: " << viajeros[i].id << ", Nombre: " << viajeros[i].nombre << ", Direccion: " << viajeros[i].direccion;
    }

    gotoxy(2, 5 + totalViajeros);
    cout << "\nReporte de Ingresos:";

    for (int i = 0; i < totalIngresos; i++) {
        gotoxy(2, 7 + totalViajeros + i);
        cout << "ID Viajero: " << ingresos[i].idViajero << ", Fecha: " << ingresos[i].fechaIngreso << ", Lugar: " << ingresos[i].lugarIngreso;
    }

    gotoxy(2, 9 + totalViajeros + totalIngresos);
    cout << "\nReporte de Salidas:";

    for (int i = 0; i < totalSalidas; i++) {
        gotoxy(2, 11 + totalViajeros + totalIngresos + i);
        cout << "ID Viajero: " << salidas[i].idViajero << ", Fecha: " << salidas[i].fechaSalida << ", Lugar: " << salidas[i].lugarSalida;
    }

    // Restablece el color a blanco sobre negro
    
}

int main() {
    menu();
    return 0;
}




