#ifndef FICHERO_H
#define FICHERO_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Fichero {
private:
    std::string nombre;
    std::string contenido;

public:
    Fichero() : nombre(""), contenido("") {}

    Fichero(const std::string& nombreArchivo) : nombre(nombreArchivo), contenido("") {
        std::ifstream file(nombreArchivo);
        if (file) {
            std::stringstream buffer;
            buffer << file.rdbuf();
            contenido = buffer.str();
        } else {
            // Si no existe, lo crea vacío
            std::ofstream nuevoArchivo(nombreArchivo);
            if(nuevoArchivo){
                contenido = "";
            } else {
                contenido = "[No se pudo crear el archivo]";
            }
        }
    }

    std::string getNombre() const { return nombre; }
    std::string getContenido() const { return contenido; }
    void setContenido(const std::string& nuevoContenido) {
        contenido = nuevoContenido;
    }
};

#endif //FICHERO_H