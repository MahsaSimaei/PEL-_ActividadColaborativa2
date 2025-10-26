#ifndef PEL__ACTIVIDADCOLABORATIVA2_LISTAS_H
#define PEL__ACTIVIDADCOLABORATIVA2_LISTAS_H

#include <iostream>
#include <string>

template<typename T>
class ListaDeObjetos {
private:
    T* lista;
    size_t size;
    size_t last;
public:
    ListaDeObjetos() {
        size = 2;
        last = 0;
        lista = new T[size];
    }

    ~ListaDeObjetos() {
        delete[] lista;
    }

    void append(const T& valor) {
        if (last == size) {
            size *= 2;
            T* aux = new T[size];
            for (size_t i = 0; i < last; i++)
                aux[i] = lista[i];
            delete[] lista;
            lista = aux;
        }
        lista[last] = valor;
        last++;
    }

    T& get(int pos) {
        if (pos > 0 && pos <= (int)last)
            return lista[pos - 1];
        throw std::out_of_range("Posición inválida en get()");
    }

    const T& get(int pos) const {
        if (pos > 0 && pos <= (int)last)
            return lista[pos - 1];
        throw std::out_of_range("Posición inválida en get()");
    }

    void set(int pos, const T& valor) {
        if (pos > 0 && pos <= (int)last)
            lista[pos - 1] = valor;
    }

    void erase(int pos) {
        if (pos <= 0 || pos > (int)last) {
            std::cout << "La posicion indicada es invalida" << std::endl;
            return;
        }
        last--;
        for (int i = pos - 1; i < (int)last; i++) {
            lista[i] = lista[i + 1];
        }
    }

    T pop() {
        if (last == 0) {
            std::cout << "La lista esta vacia" << std::endl;
            return T{};
        }
        last--;
        return lista[last];
    }

    int getSize() const {
        return (int)last;
    }

    std::string toString() const {
        std::string ret;
        for (size_t i = 0; i < last; i++) {
            ret += std::to_string(i + 1) + ". " + lista[i].toString() + "\n";
        }
        return ret;
    }

    std::string toStringNoObj() const {
        std::string ret;
        for (size_t i = 0; i < last; i++)
            ret += std::to_string(i + 1) + ". " + std::to_string(lista[i]) + "\n";
        return ret;
    }
};

#endif //PEL__ACTIVIDADCOLABORATIVA2_LISTAS_H