
#ifndef PEL__ACTIVIDADCOLABORATIVA2_LISTAS_H
#define PEL__ACTIVIDADCOLABORATIVA2_LISTAS_H

#endif //PEL__ACTIVIDADCOLABORATIVA2_LISTAS_H

#ifndef LISTAS_H
#define LISTAS_H

template<typename T> class ListaDeObjetos {
private:
    T *lista;
    size_t size;
    size_t last;
public:
    ListaDeObjetos() {
        size = 2;
        last = 0;
        lista = new T[size];
    }

    void append(T valor) {
        lista[last] = valor;
        last++;
        if (last == size) {
            size *= 2;
            T *aux = new T[size];
            for (int i = 0; i < last; i++)
                aux[i] = lista[i];
            delete[] lista;
            lista = aux;
        }
    }

    T get(int pos) {
        T ret;
        if (pos > 0 && pos < last)
            ret = lista[pos-1];
        return ret;
    }

    void erase(int pos) {
        if(pos == 1)
            this->pop();
        else if (pos < last && pos >= 0) {
            last--;
            for(int i = pos; i < last; i++) {
                lista[i] = lista[i + 1];
            }
        }
        else
            std::cout << "La posicion indicada es invalida" << std::endl;
    }

    T pop() {
        if (last == 0)
            std::cout << "La lista esta vacia" << std::endl;
        else
            last--;
        return lista[last];
    }

    int getSize() {
        return last; //*******************************
    }

    std::string toString() {
        std::string ret;
        for(int i = 0; i < last; i++) {
            ret += std::to_string(i+1) + "." + lista[i].toString() + "\n";
        }
        return ret;
    }

    std::string toStringNoObj() {
        std::string ret;
        for(int i = 0; i < last; i++)
            ret += std::to_string(i+1) + ". " + std::to_string(lista[i]) + "\n";
        return ret;
    }
};

#endif //LISTAS_H

