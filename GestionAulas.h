#ifndef GESTIONAULAS_H
#define GESTIONAULAS_H

#include <string>
#include "Listas.h"
#include "Usuario.h"

using std::string;

// ------------------------
// Clase NotaPorAsignatura
// ------------------------
class NotaPorAsignatura {
private:
    ListaDeObjetos<string> asignaturas; // Lista para almacenar nombres de asignaturas
    ListaDeObjetos<float> notas;        // Lista para almacenar notas correspondientes
public:
    // Establece la nota para una asignatura dada
    void setNota(const string& asignatura, float nota) {
        for (int i = 1; i <= asignaturas.getSize(); ++i) { // Itera sobre las asignaturas
            if (asignaturas.get(i) == asignatura) {         // Si la asignatura existe
                notas.set(i, nota);                         // Actualiza la nota en la posición correspondiente
                return;                                     // Sale de la función
            }
        }
        // Si la asignatura no existe, agregar nueva asignatura y nota
        asignaturas.append(asignatura);
        notas.append(nota);
    }

    // Devuelve la nota de una asignatura dada, o -1.0 si no existe
    float getNota(const string& asignatura) const {
        for (int i = 1; i <= asignaturas.getSize(); ++i) { // Itera sobre las asignaturas
            if (asignaturas.get(i) == asignatura)           // Si la asignatura existe
                return notas.get(i);                        // Devuelve la nota correspondiente
        }
        return -1.0f; // Si no se encuentra, devuelve -1.0
    }

    // Devuelve una cadena con todas las asignaturas y sus notas
    string toString() const {
        string info;
        for (int i = 1; i <= asignaturas.getSize(); ++i) // Itera sobre las asignaturas
            info += asignaturas.get(i) + ": " + std::to_string(notas.get(i)) + "; "; // Añade asignatura y nota al string
        return info.empty() ? "Sin notas" : info; // Si no hay notas, devuelve mensaje
    }
};

// ------------------------
// Clase EstudianteConNotas
// ------------------------
class EstudianteConNotas {
private:
    Estudiante* estudiante; // Apunta al objeto Estudiante ya existente
    NotaPorAsignatura notas; // Almacena las notas del estudiante
public:
    // Constructor que recibe puntero a Estudiante
    EstudianteConNotas(Estudiante* est): estudiante(est) {}

    // Devuelve el puntero al estudiante
    Estudiante* getEstudiante() const { return estudiante; }

    // Devuelve referencia a las notas del estudiante
    NotaPorAsignatura& getNotas() { return notas; }

    // Devuelve una cadena con nombre completo y notas
    string toString() const {
        return estudiante->getNombreCompleto() + " | " + notas.toString();
    }
};

// ------------------------
// Clase GestionAulas
// ------------------------
class GestionAulas {
private:
    Profesor* profesor; // Apunta al profesor asociado al aula
    ListaDeObjetos<EstudianteConNotas*> estudiantes; // Lista de estudiantes con sus notas
public:
    // Constructor que recibe puntero a Profesor
    GestionAulas(Profesor* prof): profesor(prof) {}

    // Destructor: elimina los objetos EstudianteConNotas creados dinámicamente
    ~GestionAulas() {
        for (int i = 1; i <= estudiantes.getSize(); ++i)
            delete estudiantes.get(i);
    }

    // Agrega un nuevo estudiante al aula
    void agregarEstudiante(Estudiante* est) {
        estudiantes.append(new EstudianteConNotas(est));
    }

    // Devuelve el número de estudiantes inscritos
    int getNumeroInscritos() const { return estudiantes.getSize(); }

    // Devuelve un listado de estudiantes con sus IDs y nombres
    string listadoEstudiantes() const {
        string info;
        for (int i = 1; i <= estudiantes.getSize(); ++i) {
            EstudianteConNotas* ec = estudiantes.get(i);
            info += "ID: " + std::to_string(ec->getEstudiante()->getId()) +
                    " | " + ec->getEstudiante()->getNombreCompleto() + "\n";
        }
        return info;
    }

    // Busca un estudiante por su ID y devuelve el puntero correspondiente
    EstudianteConNotas* buscarEstudiante(int idEst) const {
        for (int i = 1; i <= estudiantes.getSize(); ++i)
            if (estudiantes.get(i)->getEstudiante()->getId() == idEst)
                return estudiantes.get(i);
        return nullptr; // Si no lo encuentra, devuelve nullptr
    }

    // Devuelve las notas de un estudiante por su ID
    string verNotasDeEstudiante(int idEst) const {
        EstudianteConNotas* ec = buscarEstudiante(idEst);
        if (ec) {
            return ec->getNotas().toString();
        }
        return "Estudiante no encontrado o sin notas.";
    }

    // Devuelve una cadena con la información general del aula
    string toStringAula() const {
        return "Profesor: " + profesor->getNombreCompleto() + "\n" +
               "Numero de inscritos: " + std::to_string(getNumeroInscritos()) + "\n" +
               "Listado:\n" + listadoEstudiantes();
    }
};

#endif //GESTIONAULAS_H