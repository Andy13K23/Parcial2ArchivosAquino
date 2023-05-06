#include <iostream>
#include <fstream>
#include <filesystem>
#include <windows.h>

using namespace std;
namespace fs = filesystem;

void agregarTextoAarchivo(string file_path, int num_lineas) {
    ofstream file_stream(file_path, ios_base::app);

    for (int i = 1; i <= num_lineas; i++) {
        file_stream << "Texto de la línea " << i << endl;
    }

    file_stream.close();
}

string buscarArchivoMasGrande(string directory_path) {
    string archivo_mas_grande = "";
    uintmax_t size_mas_grande = 0;

    for (const auto& entry : fs::directory_iterator(directory_path)) {
        if (entry.is_regular_file()) {
            uintmax_t tamano_archivo = entry.file_size();
            if (tamano_archivo > size_mas_grande) {
                size_mas_grande = tamano_archivo;
                archivo_mas_grande = entry.path().filename().string();
            }
        }
    }

    return archivo_mas_grande;
}

int main() {
    int num_arch;
    cout << "HOLA POR FAVOR Ingresa la cantidad de archivos que deseas crear:"<<endl;
    cin >> num_arch;
    cout << endl;

    string directory_path;
    if (num_arch % 2 == 0) {
        directory_path = "C:/Users/ANDY13K/Documents/par/";
    } else {
        directory_path = "C:/Users/ANDY13K/Desktop/impar/";
    }

    for (int i = 1; i <= num_arch; i++) {
        string file_name = "file" + to_string(i) + ".txt";
        string file_path = directory_path + file_name;

        HANDLE file_handle = CreateFile(file_path.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (file_handle == INVALID_HANDLE_VALUE) {
            cout << "Error al crear el archivo " << file_path << endl;
        } else {
            cout << "Archivo " << file_path << " creado exitosamente." << endl;
            CloseHandle(file_handle);

            agregarTextoAarchivo(file_path, i);
            cout << "Texto agregado a los archivos " << file_path << " exitosamente." << endl;
        }
    }

    string archivo_mas_grande = buscarArchivoMasGrande(directory_path);
    if (archivo_mas_grande != "") {
        cout << "El archivo mas grande es " << archivo_mas_grande << endl;
    } else {
        cout << "No se encontraron archivos en la carpeta " << directory_path << endl;
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);

    cout << "" << endl;

    cout << "Created By --- Andy Aquino 0909-22-1669 ---" << endl;

    return 0;
}
