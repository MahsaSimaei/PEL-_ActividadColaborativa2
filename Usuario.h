#include <iostream>
#include <ostream>
#include <random>
#include "Listas.h"
class Usuario{
private:
 std::string nombre;
 std::string apellido;
 std::string passwd;
 int id;
 bool alta;
public:
 Usuario() {
  nombre = "";
  passwd = "";
  id = 0;
  alta = false;
 }
Usuario(std::string nombre, std::string apellido, std::string passwd, int id){
  this ->nombre = nombre;
  this ->apellido = apellido;
  this ->passwd = passwd;
  this ->id = id;
  alta = false;
}
void darAlta(){
  alta = true;
}
std::string getNombre() {
  return nombre + " " + apellido;
}
std::string getUsuario() {
  return nombre;
}
std::string getPwd() {
        return pwd;
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
