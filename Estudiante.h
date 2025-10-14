#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>
#include "Usuario.h"
#include "MochilaDigital.h"

class Estudiante : public Usuario {
private:
    MochilaDigital* mochila; // En el heap

public:
    Estudiante() : Usuario() {
        // Por defecto, usamos "mochila_default" como carpeta
        mochila = new MochilaDigital("mochila_default");
    }

    Estudiante(std::string nombre, std::string apellido, std::string passwd, int id)
        : Usuario(nombre, apellido, passwd, id) {
        // Carpeta mochila personalizada por nombre de usuario
        mochila = new MochilaDigital("mochila_" + nombre);
    }

    ~Estudiante() {
        delete mochila;
    }

    MochilaDigital* getMochila() const { return mochila; }
};

#endif //ESTUDIANTE_H