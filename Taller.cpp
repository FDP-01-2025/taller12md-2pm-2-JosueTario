
#include <iostream>
#include <fstream>
using namespace std;

struct Estudiante {
    string nombre;
    string carnet;
    int edad;
};

// Función para agregar estudiante (CREATE)
void agregarEstudiante() {
    Estudiante e;
    cout << "Nombre (sin espacios): ";
    cin >> e.nombre;
    cout << "Carnet: ";
    cin >> e.carnet;
    cout << "Edad: ";
    cin >> e.edad;

    ofstream archivo("estudiantes.txt", ios::app);
    if (archivo.is_open()) {
        archivo << e.nombre << " " << e.carnet << " " << e.edad << endl;
        archivo.close();
        cout << "Estudiante agregado correctamente.\n";
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}

// Función para mostrar estudiantes (READ)
void mostrarEstudiantes() {
    ifstream archivo("estudiantes.txt");
    Estudiante e;

    if (archivo.is_open()) {
        cout << "\n--- Lista de Estudiantes ---\n";
        while (archivo >> e.nombre >> e.carnet >> e.edad) {
            cout << "Nombre: " << e.nombre 
                 << ", Carnet: " << e.carnet
                 << ", Edad: " << e.edad << endl;
        }
        archivo.close();
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}


// Funcion para modificar estudiante 
void modificarEstudiante() {
    ifstream archivo("estudiantes.txt");
    ofstream temp("temp.txt");

    if (archivo.is_open() && temp.is_open()) {
        string carnetBuscado;
        cout << "Ingrese el carnet del estudiante a modificar: ";
        cin >> carnetBuscado;

        Estudiante e;
        bool encontrado = false;

        while (archivo >> e.nombre >> e.carnet >> e.edad) {
            if (e.carnet == carnetBuscado) {
                encontrado = true;
                cout << "Ingrese el nuevo nombre (o presione Enter para mantenerlo): ";
                string nuevoNombre;
                cin.ignore();
                getline(cin, nuevoNombre);
                if (!nuevoNombre.empty()) e.nombre = nuevoNombre;

                cout << "Ingrese el nuevo carnet (o presione Enter para mantenerlo): ";
                string nuevoCarnet;
                getline(cin, nuevoCarnet);
                if (!nuevoCarnet.empty()) e.carnet = nuevoCarnet;

                cout << "Ingrese la nueva edad (o presione Enter para mantenerla): ";
                string nuevaEdad;
                getline(cin, nuevaEdad);
                if (!nuevaEdad.empty()) e.edad = stoi(nuevaEdad);

                cout << "Estudiante modificado correctamente.\n";
            }
            temp << e.nombre << " " << e.carnet << " " << e.edad << endl;
        }

        archivo.close();
        temp.close();

        remove("estudiantes.txt");
        rename("temp.txt", "estudiantes.txt");

        if (!encontrado) {
            cout << "Carnet no encontrado.\n";
        }
    } else {
        cout << "Error al abrir los archivos.\n";
    }
}


// Función para eliminar estudiante (DELETE)
void eliminarEstudiante() {
    ifstream archivo("estudiantes.txt");
    ofstream temp("temp.txt");
    Estudiante e;
    string buscado;
    bool eliminado = false;

    cout << "Ingrese carnet a eliminar: ";
    cin >> buscado;

    if (archivo.is_open() && temp.is_open()) {
        while (archivo >> e.nombre >> e.carnet >> e.edad) {
            if (e.carnet == buscado) {
                eliminado = true;               // No se copia: se “borra”
            } else {
                temp << e.nombre << " " << e.carnet << " " << e.edad << endl;
            }
        }
        archivo.close();
        temp.close();
        remove("estudiantes.txt");
        rename("temp.txt", "estudiantes.txt");

        if (eliminado)
            cout << "Estudiante eliminado correctamente.\n";
        else
            cout << "Carnet no encontrado.\n";
    } else {
        cout << "Error abriendo los archivos.\n";
    }
}

// Menú principal
int main() {
    int opcion;
    do {
        cout << "\n=== CRUD de Estudiantes ===\n";
        cout << "1. Agregar estudiante\n";
        cout << "2. Mostrar todos\n";
        cout << "3. Modificar estudiante\n";
        cout << "4. Eliminar estudiante\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: agregarEstudiante(); break;
            case 2: mostrarEstudiantes(); break;
            case 3: modificarEstudiante(); break;  
            case 4: eliminarEstudiante(); break;
            case 5: cout << "Saliendo...\n"; break;
            default: cout << "Opción inválida.\n";
        }

    } while (opcion != 5);

    return 0;
}


