#ifndef PEL__ACTIVIDADCOLABORATIVA2_LISTAS_H
#define PEL__ACTIVIDADCOLABORATIVA2_LISTAS_H

#include <iostream>
#include <string>

// -------------------------------------------------------
// Clase plantilla ListaDeObjetos: Lista dinámica de objetos
// -------------------------------------------------------
template<typename T>
class ListaDeObjetos {
private:
    T* lista;          // Puntero al array de elementos
    size_t size;       // Capacidad actual del array
    size_t last;       // Número de elementos (posición del último + 1)
public:
    // Constructor: inicializa la lista con capacidad 2
    ListaDeObjetos() {
        size = 2;
        last = 0;
        lista = new T[size];
    }

    // Destructor: libera la memoria del array
    ~ListaDeObjetos() {
        delete[] lista;
    }

    // Añade un elemento al final de la lista
    void append(const T& valor) {
        if (last == size) {              // Si el array está lleno
            size *= 2;                   // Duplica la capacidad
            T* aux = new T[size];        // Crea nuevo array más grande
            for (size_t i = 0; i < last; i++)
                aux[i] = lista[i];       // Copia los elementos actuales
            delete[] lista;              // Libera el array antiguo
            lista = aux;                 // Actualiza el puntero
        }
        lista[last] = valor;             // Inserta el nuevo valor
        last++;                          // Incrementa el contador
    }

    // Devuelve referencia al elemento en la posición dada (1-indexado)
    T& get(int pos) {
        if (pos > 0 && pos <= (int)last)
            return lista[pos - 1];
        throw std::out_of_range("Posición inválida en get()");
    }

    // Versión const de get (para listas constantes)
    const T& get(int pos) const {
        if (pos > 0 && pos <= (int)last)
            return lista[pos - 1];
        throw std::out_of_range("Posición inválida en get()");
    }

    // Asigna un valor a la posición dada (1-indexado)
    void set(int pos, const T& valor) {
        if (pos > 0 && pos <= (int)last)
            lista[pos - 1] = valor;
    }

    // Elimina el elemento en la posición dada (1-indexado)
    void erase(int pos) {
        if (pos <= 0 || pos > (int)last) {
            std::cout << "La posicion indicada es invalida" << std::endl;
            return;
        }
        last--; // Reduce el tamaño
        // Desplaza los elementos a la izquierda
        for (int i = pos - 1; i < (int)last; i++) {
            lista[i] = lista[i + 1];
        }
    }

    // Elimina y devuelve el último elemento de la lista
    T pop() {
        if (last == 0) {
            std::cout << "La lista esta vacia" << std::endl;
            return T{};
        }
        last--;
        return lista[last];
    }

    // Devuelve el número de elementos en la lista
    int getSize() const {
        return (int)last;
    }

    // Devuelve una cadena con los elementos, usando su método toString()
    std::string toString() const {
        std::string ret;
        for (size_t i = 0; i < last; i++) {
            ret += std::to_string(i + 1) + ". " + lista[i].toString() + "\n";
        }
        return ret;
    }

    // Devuelve una cadena con los elementos, usando std::to_string()
    std::string toStringNoObj() const {
        std::string ret;
        for (size_t i = 0; i < last; i++)
            ret += std::to_string(i + 1) + ". " + std::to_string(lista[i]) + "\n";
        return ret;
    }
};

#endif //PEL__ACTIVIDADCOLABORATIVA2_LISTAS_H