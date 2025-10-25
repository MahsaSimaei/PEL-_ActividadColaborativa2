#ifndef RECURSOS_MOCHILA_H
#define RECURSOS_MOCHILA_H

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>
#include "Listas.h"

class Fichero {
private:
    std::string nombre;
    std::string contenido;
public:
    Fichero() : nombre(""), contenido("") {}

    Fichero(const std::string& nombreArchivo) : nombre(nombreArchivo), contenido("") {
        recargarContenido();
    }

    std::string getNombre() const { return nombre; }
    std::string getContenido() const { return contenido; }
    void setContenido(const std::string& nuevoContenido) {
        contenido = nuevoContenido;
    }

    void recargarContenido() {
        std::ifstream file(nombre);
        if (file) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            contenido = buffer.str();
        } else {
            contenido = "";
        }
    }
};

namespace fs = std::filesystem;

class MochilaDigital {
private:
    ListaDeObjetos<Fichero> documentos;
    std::string carpeta;

    std::string asegurarExtensionTxt(const std::string& nombreArchivo) const {
        if (nombreArchivo.size() >= 4 &&
            nombreArchivo.substr(nombreArchivo.size() - 4) == ".txt") {
            return nombreArchivo;
        } else {
            return nombreArchivo + ".txt";
        }
    }

    bool existeDocumento(const std::string& rutaCompleta) const {
        for (int i = 1; i <= documentos.getSize(); ++i) {
            if (documentos.get(i).getNombre() == rutaCompleta) {
                return true;
            }
        }
        return false;
    }

public:
    MochilaDigital(const std::string& carpetaMochila) : carpeta(carpetaMochila) {
        if (!fs::exists(carpeta))
            fs::create_directory(carpeta);
        cargarArchivosDeCarpeta();
    }
    ~MochilaDigital() = default;

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

    void agregarDocumento(const std::string& nombreArchivo) {
        std::string nombreConTxt = asegurarExtensionTxt(nombreArchivo);
        std::string rutaCompleta = carpeta + "/" + nombreConTxt;

        if (existeDocumento(rutaCompleta)) {
            std::cout << "El documento '" << nombreConTxt << "' ya está en la mochila.\n";
            return;
        }

        std::ofstream nuevoArchivo(rutaCompleta);
        if (!nuevoArchivo) {
            std::cout << "No se pudo crear el archivo '" << nombreConTxt << "'.\n";
            return;
        }
        nuevoArchivo.close();

        Fichero doc(rutaCompleta);
        documentos.append(doc);
        std::cout << "Documento '" << nombreConTxt << "' agregado a la mochila.\n";
    }

    void eliminarDocumento(int pos) {
        if (pos < 1 || pos > documentos.getSize()) {
            std::cout << "Posición inválida.\n";
            return;
        }
        std::string rutaCompleta = documentos.get(pos).getNombre();
        std::cout << "Eliminando '" << fs::path(rutaCompleta).filename().string() << "' de la mochila...\n";
        fs::remove(rutaCompleta);
        documentos.erase(pos);
    }

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

    void verContenidoDocumento(int pos) {
        if (pos < 1 || pos > documentos.getSize()) {
            std::cout << "Posición inválida.\n";
            return;
        }
        documentos.get(pos).recargarContenido();
        std::cout << "Contenido de '" << fs::path(documentos.get(pos).getNombre()).filename().string() << "':\n";
        std::cout << documentos.get(pos).getContenido() << "\n";
        std::cout << "---------------------------\n";
    }

    void editarContenidoDocumento(int pos) {
        if (pos < 1 || pos > documentos.getSize()) {
            std::cout << "Posición inválida.\n";
            return;
        }
        documentos.get(pos).recargarContenido();
        std::cout << "Contenido actual de '" << fs::path(documentos.get(pos).getNombre()).filename().string() << "':\n";
        std::cout << documentos.get(pos).getContenido() << "\n";
        std::cout << "Ingrese el nuevo contenido (escriba la línea y pulse ENTER):\n";
        std::string nuevoContenido;
        std::getline(std::cin, nuevoContenido);

        std::string rutaCompleta = documentos.get(pos).getNombre();
        std::ofstream archivo(rutaCompleta);
        if (archivo) {
            archivo << nuevoContenido << std::endl;
            archivo.close();
            documentos.get(pos).recargarContenido();
            std::cout << "Archivo actualizado correctamente.\n";
        } else {
            std::cout << "No se pudo abrir el archivo para editar.\n";
        }
    }
};

#endif // RECURSOS_MOCHILA_H