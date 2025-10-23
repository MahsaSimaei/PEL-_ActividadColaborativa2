#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include <ostream>
#include <random>
#include "Listas.h"

class Usuario {
private:
    std::string nombre;
    std::string apellido;
    std::string passwd;
    int id;
    bool alta;

public:
    Usuario() {
        nombre = "";
        apellido="";
        passwd = "";
        id = 0;
        alta = false;
    }

    Usuario(std::string nombre,std::string apellido, std::string pwd, int id) {
        this->nombre = nombre;
        this->apellido = apellido;
        this->passwd = passwd;
        this->id = id;
        alta = false;
    }

    void darAlta() {
        alta = true;
    }

    std::string getNombre() {
        return nombre + " " + apellido;
    }

    std::string getUsuario() {
        return nombre;
    }

    std::string getPasswd() {
        return passwd;
    }

    bool isAlta() {
        return alta;
    }

    int getId() {
        return id;
    }

    void setNombre(std::string nombre) {
        this->nombre = nombre;
    }

    void setApellido(std::string apellido) {
        this->apellido = apellido;
    }

    std::string toString() {
        std::string ret;
        ret = "Nombre: " + nombre + " " + apellido + ", ID: " + std::to_string(id);
        ret += alta ? ", Esta de alta." : ", Esta de baja";
        return ret;
    }

};

class Estudiante : public Usuario {
private:
    ListaDeObjetos<FILE> *mochila;
    ListaDeObjetos<double> *calificaciones;
    std::string clase;
public:
    Estudiante() {}

    Estudiante(std::string nombre, std::string apellido, std::string pwd, int id) : Usuario(nombre,apellido,pwd,id) {
        mochila = new ListaDeObjetos<FILE>();
        calificaciones = new ListaDeObjetos<double>();
        clase = "";
    }

    void setClase(std::string clase) {
        this->clase = clase;
    }

    std::string getClase() {
        return clase;
    }

    void agregarCalificacion(double nota) {
        calificaciones->append(nota);
    }

    double getCalificacion(int pos) {
        return calificaciones->get(pos);
    }

    void eliminarCalificacion(int pos) {
        calificaciones->erase(pos);
    }

    void agregarDoc(FILE doc) {
        mochila->append(doc);
    }

    FILE getDoc(int pos) {
        return mochila->get(pos);
    }

    void eliminarDoc(int pos) {
        calificaciones->erase(pos);
    }


    std::string toString() {
        return this->getNombre() + "\nNotas:\n" + calificaciones->toStringNoObj();
    }
};

class Profesor : public Usuario{
private:
    ListaDeObjetos<Estudiante> *clase;
    std::string asignatura;
public:
    Profesor(){}

    Profesor(std::string nombre, std::string apellido, std::string pwd, int id) : Usuario(nombre,apellido,pwd,id) {
        clase = new ListaDeObjetos<Estudiante>();
        asignatura = "";
    }

    void setAsignatura(std::string asignatura) {
        this->asignatura = asignatura;
    }

    std::string getAsignatura() {
        return asignatura;
    }

    void agregarEstudiante(Estudiante es) {
        clase->append(es);
    }

    Estudiante getEstudiante(int pos) {
        return clase->get(pos);
    }

    void eliminarEstudiante(int pos) {
        clase->erase(pos);
    }

    std::string toString() {
        return "Profesor: " + this->getNombre() + "\nClase: " + asignatura + "\nEstudiantes:\n" + clase->toString();
    }
};

class Admin : public Usuario{
public:
    Admin(){}

    Admin(std::string nombre, std::string apellido, std::string passwd, int id) : Usuario(nombre,apellido,passwd,id) {}

};



#endif //USUARIO_H
