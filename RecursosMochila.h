#ifndef RECURSOS_MOCHILA_H
#define RECURSOS_MOCHILA_H

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include "Listas.h"

// --------------------------------------------------------
// Clase Fichero: Representa un archivo con nombre y contenido
// --------------------------------------------------------
class Fichero {
private:
    std::string nombre;      // Nombre y ruta del archivo
    std::string contenido;   // Contenido del archivo
public:
    // Constructor por defecto
    Fichero() : nombre(""), contenido("") {}

    // Constructor que inicializa el nombre y carga el contenido desde disco
    Fichero(const std::string& nombreArchivo) : nombre(nombreArchivo), contenido("") {
        recargarContenido();
    }

    // Devuelve el nombre del archivo
    std::string getNombre() const { return nombre; }
    // Devuelve el contenido del archivo
    std::string getContenido() const { return contenido; }
    // Establece el contenido del archivo (en memoria)
    void setContenido(const std::string& nuevoContenido) {
        contenido = nuevoContenido;
    }

    // Recarga el contenido desde el archivo en disco
    void recargarContenido() {
        std::ifstream file(nombre);
        if (file) { // Si el archivo se abrió correctamente
            std::stringstream buffer;
            buffer << file.rdbuf();      // Lee todo el archivo
            contenido = buffer.str();    // Guarda el contenido en la variable
        } else {
            contenido = "";              // Si no existe, deja vacío
        }
    }
};

// Alias para el namespace filesystem
namespace fs = std::filesystem;

// --------------------------------------------------------
// Clase MochilaDigital: Gestiona una lista de archivos txt
// --------------------------------------------------------
class MochilaDigital {
private:
    ListaDeObjetos<Fichero> documentos; // Lista de archivos en la mochila
    std::string carpeta;                // Carpeta donde se guardan los archivos

    // Asegura que el nombre del archivo termine en .txt
    std::string asegurarExtensionTxt(const std::string& nombreArchivo) const {
        if (nombreArchivo.size() >= 4 &&
            nombreArchivo.substr(nombreArchivo.size() - 4) == ".txt") {
            return nombreArchivo;
        } else {
            return nombreArchivo + ".txt";
        }
    }

    // Verifica si el documento ya existe en la mochila
    bool existeDocumento(const std::string& rutaCompleta) const {
        for (int i = 1; i <= documentos.getSize(); ++i) {
            if (documentos.get(i).getNombre() == rutaCompleta) {
                return true;
            }
        }
        return false;
    }

public:
    // Constructor: inicializa la mochila y carga los archivos de la carpeta
    MochilaDigital(const std::string& carpetaMochila) : carpeta(carpetaMochila) {
        if (!fs::exists(carpeta))
            fs::create_directory(carpeta); // Crea la carpeta si no existe
        cargarArchivosDeCarpeta();
    }
    // Destructor por defecto
    ~MochilaDigital() = default;

    // Carga todos los archivos .txt de la carpeta a la lista de documentos
    void cargarArchivosDeCarpeta() {
        for (const auto& entry : fs::directory_iterator(carpeta)) {
            if (entry.is_regular_file() && entry.path().extension() == ".txt") {
                std::string nombreArchivo = entry.path().filename().string();
                std::string rutaCompleta = carpeta + "/" + nombreArchivo;
                if (!existeDocumento(rutaCompleta)) {
                    documentos.append(Fichero(rutaCompleta));
                }
            }
        }
    }

    // Agrega un archivo nuevo a la mochila
    void agregarDocumento(const std::string& nombreArchivo) {
        std::string nombreConTxt = asegurarExtensionTxt(nombreArchivo);
        std::string rutaCompleta = carpeta + "/" + nombreConTxt;

        if (existeDocumento(rutaCompleta)) { // Si ya existe, no lo agrega
            std::cout << "El documento '" << nombreConTxt << "' ya está en la mochila.\n";
            return;
        }

        std::ofstream nuevoArchivo(rutaCompleta); // Crea el archivo vacío
        if (!nuevoArchivo) {
            std::cout << "No se pudo crear el archivo '" << nombreConTxt << "'.\n";
            return;
        }
        nuevoArchivo.close();

        Fichero doc(rutaCompleta);      // Crea el objeto Fichero
        documentos.append(doc);         // Lo añade a la lista
        std::cout << "Documento '" << nombreConTxt << "' agregado a la mochila.\n";
    }

    // Elimina un archivo de la mochila por posición
    void eliminarDocumento(int pos) {
        if (pos < 1 || pos > documentos.getSize()) { // Verifica la posición válida
            std::cout << "Posición inválida.\n";
            return;
        }
        std::string rutaCompleta = documentos.get(pos).getNombre();
        std::cout << "Eliminando '" << fs::path(rutaCompleta).filename().string() << "' de la mochila...\n";
        fs::remove(rutaCompleta);     // Elimina el archivo físico
        documentos.erase(pos);        // Quita el archivo de la lista
    }

    // Muestra todos los documentos en la mochila
    void verDocumentos() const {
        if (documentos.getSize() == 0) {
            std::cout << "La mochila está vacía.\n";
            return;
        }
        std::cout << "Documentos en la mochila:\n";
        for (int i = 1; i <= documentos.getSize(); ++i) {
            std::cout << i << ". " << fs::path(documentos.get(i).getNombre()).filename().string() << "\n";
        }
    }

    // Muestra el contenido de un documento por posición
    void verContenidoDocumento(int pos) {
        if (pos < 1 || pos > documentos.getSize()) {
            std::cout << "Posición inválida.\n";
            return;
        }
        documentos.get(pos).recargarContenido(); // Recarga el contenido desde disco
        std::cout << "Contenido de '" << fs::path(documentos.get(pos).getNombre()).filename().string() << "':\n";
        std::cout << documentos.get(pos).getContenido() << "\n";
        std::cout << "---------------------------\n";
    }

    // Permite editar el contenido de un documento por posición
    void editarContenidoDocumento(int pos) {
        if (pos < 1 || pos > documentos.getSize()) {
            std::cout << "Posición inválida.\n";
            return;
        }
        documentos.get(pos).recargarContenido(); // Recarga el contenido actual
        std::cout << "Contenido actual de '" << fs::path(documentos.get(pos).getNombre()).filename().string() << "':\n";
        std::cout << documentos.get(pos).getContenido() << "\n";
        std::cout << "Ingrese el nuevo contenido (escriba la línea y pulse ENTER):\n";
        std::string nuevoContenido;
        std::getline(std::cin, nuevoContenido);

        std::string rutaCompleta = documentos.get(pos).getNombre();
        std::ofstream archivo(rutaCompleta); // Abre el archivo para escritura
        if (archivo) {
            archivo << nuevoContenido << std::endl; // Guarda el nuevo contenido
            archivo.close();
            documentos.get(pos).recargarContenido(); // Actualiza el contenido en memoria
            std::cout << "Archivo actualizado correctamente.\n";
        } else {
            std::cout << "No se pudo abrir el archivo para editar.\n";
        }
    }
};

#endif // RECURSOS_MOCHILA_H