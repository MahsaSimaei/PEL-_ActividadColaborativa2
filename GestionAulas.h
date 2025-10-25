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
    // Si no puedes usar std::map, usa dos listas paralelas
    ListaDeObjetos<string> asignaturas;
    ListaDeObjetos<float> notas;
public:
    void setNota(const string& asignatura, float nota) {
        for (int i = 1; i <= asignaturas.getSize(); ++i) {
            if (asignaturas.get(i) == asignatura) {
                notas.set(i, nota); // <---- cambio aquí
                return;
            }
        }
        // Si no existe, agregar nueva
        asignaturas.append(asignatura);
        notas.append(nota);
    }
    float getNota(const string& asignatura) const {
        for (int i = 1; i <= asignaturas.getSize(); ++i) {
            if (asignaturas.get(i) == asignatura)
                return notas.get(i);
        }
        return -1.0f;
    }
    string toString() const {
        string info;
        for (int i = 1; i <= asignaturas.getSize(); ++i)
            info += asignaturas.get(i) + ": " + std::to_string(notas.get(i)) + "; ";
        return info.empty() ? "Sin notas" : info;
    }
};

// ------------------------
// Clase EstudianteConNotas
// ------------------------
class EstudianteConNotas {
private:
    Estudiante* estudiante; // Apunta al objeto Estudiante ya existente
    NotaPorAsignatura notas;
public:
    EstudianteConNotas(Estudiante* est): estudiante(est) {}
    Estudiante* getEstudiante() const { return estudiante; }
    NotaPorAsignatura& getNotas() { return notas; }
    string toString() const {
        return estudiante->getNombreCompleto() + " | " + notas.toString();
    }
};

// ------------------------
// Clase GestionAulas
// ------------------------
class GestionAulas {
private:
    Profesor* profesor; // asociado
    ListaDeObjetos<EstudianteConNotas*> estudiantes;
public:
    GestionAulas(Profesor* prof): profesor(prof) {}
    ~GestionAulas() {
        for (int i = 1; i <= estudiantes.getSize(); ++i)
            delete estudiantes.get(i);
    }

    void agregarEstudiante(Estudiante* est) {
        estudiantes.append(new EstudianteConNotas(est));
    }

    int getNumeroInscritos() const { return estudiantes.getSize(); }

    string listadoEstudiantes() const {
        string info;
        for (int i = 1; i <= estudiantes.getSize(); ++i) {
            EstudianteConNotas* ec = estudiantes.get(i);
            info += "ID: " + std::to_string(ec->getEstudiante()->getId()) +
                    " | " + ec->getEstudiante()->getNombreCompleto() + "\n";
        }
        return info;
    }

    EstudianteConNotas* buscarEstudiante(int idEst) const {
        for (int i = 1; i <= estudiantes.getSize(); ++i)
            if (estudiantes.get(i)->getEstudiante()->getId() == idEst)
                return estudiantes.get(i);
        return nullptr;
    }

    string verNotasDeEstudiante(int idEst) const {
        EstudianteConNotas* ec = buscarEstudiante(idEst);
        if (ec) {
            return ec->getNotas().toString();
        }
        return "Estudiante no encontrado o sin notas.";
    }

    string toStringAula() const {
        return "Profesor: " + profesor->getNombreCompleto() + "\n" +
               "Numero de inscritos: " + std::to_string(getNumeroInscritos()) + "\n" +
               "Listado:\n" + listadoEstudiantes();
    }
};

#endif //GESTIONAULAS_H