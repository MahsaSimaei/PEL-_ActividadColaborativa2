#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>
#include <vector>
#include "Listas.h"

using namespace std;

// =============================================================
// Clase base: Usuario
// =============================================================
class Usuario {
protected:
    string nombre;
    string apellido;
    string passwd;
    int id;
    bool alta;

public:
    Usuario() : nombre(""), apellido(""), passwd(""), id(0), alta(false) {}

    Usuario(string nombre, string apellido, string passwd, int id)
        : nombre(nombre), apellido(apellido), passwd(passwd), id(id), alta(true) {}

    virtual ~Usuario() = default;

    void darAlta() { alta = true; }
    void darBaja() { alta = false; }

    string getNombreCompleto() const { return nombre + " " + apellido; }
    string getNombre() const { return nombre; }
    string getPasswd() const { return passwd; }
    int getId() const { return id; }
    bool isAlta() const { return alta; }

    void setNombre(string n) { nombre = n; }
    void setApellido(string a) { apellido = a; }

    virtual string toString() const {
        string estado = alta ? "Alta" : "Baja";
        return "ID: " + to_string(id) + " | " + nombre + " " + apellido + " (" + estado + ")";
    }
};

// =============================================================
// Clase: Estudiante
// =============================================================
class Estudiante : public Usuario {
private:
    ListaDeObjetos<string>* mochila;         // Archivos digitales
    ListaDeObjetos<double>* calificaciones;  // Notas
    string clase;

public:
    Estudiante() : Usuario() {
        mochila = new ListaDeObjetos<string>();
        calificaciones = new ListaDeObjetos<double>();
        clase = "";
    }

    Estudiante(string nombre, string apellido, string passwd, int id)
        : Usuario(nombre, apellido, passwd, id) {
        mochila = new ListaDeObjetos<string>();
        calificaciones = new ListaDeObjetos<double>();
        clase = "";
    }

    ~Estudiante() {
        delete mochila;
        delete calificaciones;
    }

    void setClase(string clase_) { clase = clase_; }
    string getClase() const { return clase; }

    void agregarArchivo(const string& archivo) { mochila->append(archivo); }
    void eliminarArchivo(int pos) { mochila->erase(pos); }

    string verMochila() const { return mochila->toStringNoObj(); }

    void agregarCalificacion(double nota) { calificaciones->append(nota); }
    double getCalificacion(int pos) const { return calificaciones->get(pos); }

    string toString() const override {
        return "Estudiante: " + getNombreCompleto() + "\nClase: " + clase +
               "\nMochila:\n" + mochila->toStringNoObj() +
               "\nCalificaciones:\n" + calificaciones->toStringNoObj();
    }
};

// =============================================================
// Clase: Profesor
// =============================================================
class Profesor : public Usuario {
private:
    ListaDeObjetos<Estudiante>* clase;
    string asignatura;

public:
    Profesor() : Usuario() {
        clase = new ListaDeObjetos<Estudiante>();
        asignatura = "";
    }

    Profesor(string nombre, string apellido, string passwd, int id)
        : Usuario(nombre, apellido, passwd, id) {
        clase = new ListaDeObjetos<Estudiante>();
        asignatura = "";
    }

    ~Profesor() { delete clase; }

    void setAsignatura(string a) { asignatura = a; }
    string getAsignatura() const { return asignatura; }

    void agregarEstudiante(const Estudiante& e) { clase->append(e); }
    void eliminarEstudiante(int pos) { clase->erase(pos); }

    string toString() const override {
        return "Profesor: " + getNombreCompleto() +
               "\nAsignatura: " + asignatura +
               "\nEstudiantes:\n" + clase->toString();
    }
};

// =============================================================
// Clase: Admin
// =============================================================
class Admin : public Usuario {
public:
    Admin() : Usuario() {}
    Admin(string n, string a, string p, int id) : Usuario(n, a, p, id) {}
};

#endif
