#ifndef MOCHILADIGITAL_H
#define MOCHILADIGITAL_H

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include "Listas.h"
#include "Fichero.h"

namespace fs = std::filesystem;

class MochilaDigital {
private:
    ListaDeObjetos<Fichero> documentos;
    std::string carpeta; // Carpeta asociada a la mochila

    // Auxiliar para asegurar extensión .txt
    std::string asegurarExtensionTxt(const std::string& nombreArchivo) const {
        if (nombreArchivo.size() >= 4 &&
            nombreArchivo.substr(nombreArchivo.size() - 4) == ".txt") {
            return nombreArchivo;
        } else {
            return nombreArchivo + ".txt";
        }
    }

    // Chequear si existe el documento con esa ruta completa
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

    // Cargar todos los .txt existentes al empezar
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

        Fichero doc(rutaCompleta);
        if (doc.getContenido() == "[No se pudo crear el archivo]") {
            std::cout << "No se pudo crear el archivo '" << nombreConTxt << "'.\n";
        } else {
            documentos.append(doc);
            std::cout << "Documento '" << nombreConTxt << "' agregado a la mochila.\n";
        }
    }

    void eliminarDocumento(int pos) {
        // pos es base 1 para ListaDeObjetos
        if (pos < 1 || pos > documentos.getSize()) {
            std::cout << "Posición inválida.\n";
            return;
        }
        std::string rutaCompleta = documentos.get(pos).getNombre();
        std::cout << "Eliminando '" << fs::path(rutaCompleta).filename().string() << "' de la mochila...\n";
        fs::remove(rutaCompleta); // Borra el archivo físico
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

    void verContenidoDocumento(int pos) const {
        if (pos < 1 || pos > documentos.getSize()) {
            std::cout << "Posición inválida.\n";
            return;
        }
        std::cout << "Contenido de '" << fs::path(documentos.get(pos).getNombre()).filename().string() << "':\n";
        std::cout << documentos.get(pos).getContenido() << "\n";
        std::cout << "---------------------------\n";
    }

    void editarContenidoDocumento(int pos) {
        if (pos < 1 || pos > documentos.getSize()) {
            std::cout << "Posición inválida.\n";
            return;
        }
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
            std::cout << "Archivo actualizado correctamente.\n";
            documentos.get(pos).setContenido(nuevoContenido + "\n");
        } else {
            std::cout << "No se pudo abrir el archivo para editar.\n";
        }
    }
};

#endif // MOCHILADIGITAL_H