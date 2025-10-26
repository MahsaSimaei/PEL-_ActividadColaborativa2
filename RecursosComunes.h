#include <iostream>
#include <random>
#include <limits>
#include <cmath>
#include <iomanip>
#include "Listas.h"

// ==================== Juego "Adivina el número"  ====================
class JuegoAdivinaNumero {
private:
    int numero_secreto;
    ListaDeObjetos<int> intentos;
public:
    JuegoAdivinaNumero() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        numero_secreto = dis(gen);
    }
    void jugar() {
        int adivinanza;
        bool adivinado = false;
        while (!adivinado) {
            std::cout << "Introduce tu adivinanza (1-100): ";
            if (!(std::cin >> adivinanza)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Entrada no válida. Por favor, introduce un número (1-100).\n";
                continue;
            }
            intentos.append(adivinanza);
            int diferencia = std::abs(adivinanza - numero_secreto);
            if (adivinanza < numero_secreto) {
                if (diferencia > 10)
                    std::cout << "Demasiado bajo. ¡Intentalo de nuevo!\n";
                else
                    std::cout << "Bajo. ¡Intentalo de nuevo!\n";
            } else if (adivinanza > numero_secreto) {
                if (diferencia > 10)
                    std::cout << "Demasiado alto. ¡Intentalo de nuevo!\n";
                else
                    std::cout << "Alto. ¡Intentalo de nuevo!\n";
            } else {
                std::cout << "¡Felicidades! Adivinaste el número en " << intentos.getSize() << " intentos!\n";
                std::cout << "Tus intentos fueron: ";
                for (int i = 1; i <= intentos.getSize(); i++)
                    std::cout << intentos.get(i) << " ";
                std::cout << std::endl;
                adivinado = true;
            }
        }
    }
};

inline void jugarAdivinaNumero() {
    JuegoAdivinaNumero juego;
    juego.jugar();
}

// ==================== Calculadora Avanzada ====================

inline int** matrizInt(int n) {
    int** m = new(std::nothrow) int*[n];
    if (!m) return nullptr;
    for (int i = 0; i < n; ++i) {
        m[i] = new(std::nothrow) int[n];
        if (!m[i]) {
            for (int j = 0; j < i; ++j) delete[] m[j];
            delete[] m;
            return nullptr;
        }
        for (int j = 0; j < n; ++j) m[i][j] = 0;
    }
    return m;
}

inline void eliminarMatrizInt(int** m, int n) {
    if (!m) return;
    for (int i = 0; i < n; ++i) delete[] m[i];
    delete[] m;
}

inline void imprimirMatriz(int** matriz, int n) {
    if (!matriz) return;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << matriz[i][j] << " ";
        std::cout << std::endl;
    }
}

inline void sumaMat(int** a, int** b, int** resultado, int n) {
    if (!a || !b || !resultado) return;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            resultado[i][j] = a[i][j] + b[i][j];
}
inline void restaMat(int** a, int** b, int** resultado, int n) {
    if (!a || !b || !resultado) return;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            resultado[i][j] = a[i][j] - b[i][j];
}
inline void multiplicacionMat(int** a, int** b, int** resultado, int n) {
    if (!a || !b || !resultado) return;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            resultado[i][j] = 0;
            for (int k = 0; k < n; ++k)
                resultado[i][j] += a[i][k] * b[k][j];
        }
}

inline double** matrizDouble(int n) {
    double** m = new(std::nothrow) double*[n];
    if (!m) return nullptr;
    for (int i = 0; i < n; ++i) {
        m[i] = new(std::nothrow) double[n];
        if (!m[i]) {
            for (int j = 0; j < i; ++j) delete[] m[j];
            delete[] m;
            return nullptr;
        }
        for (int j = 0; j < n; ++j) m[i][j] = 0.0;
    }
    return m;
}
inline void eliminarMatrizDouble(double** m, int n) {
    if (!m) return;
    for (int i = 0; i < n; ++i) delete[] m[i];
    delete[] m;
}
inline void imprimirMatrizDouble(double** matriz, int n) {
    if (!matriz) return;
    std::cout << std::fixed << std::setprecision(6);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << matriz[i][j] << " ";
        std::cout << std::endl;
    }
}
inline void multiplicacionMatDouble(double** a, double** b, double** resultado, int n) {
    if (!a || !b || !resultado) return;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            double sum = 0.0;
            for (int k = 0; k < n; ++k)
                sum += a[i][k] * b[k][j];
            resultado[i][j] = sum;
        }
}
inline bool invertirMatriz(double** A, double** inv, int n) {
    const double EPS = 1e-12;
    double** aug = matrizDouble(n);
    if (!aug) return false;
    for (int i = 0; i < n; ++i) {
        aug[i] = new(std::nothrow) double[2 * n];
        if (!aug[i]) {
            for (int j = 0; j < i; ++j) delete[] aug[j];
            eliminarMatrizDouble(aug, n);
            return false;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) aug[i][j] = A[i][j];
        for (int j = 0; j < n; ++j) aug[i][n + j] = (i == j) ? 1.0 : 0.0;
    }
    for (int col = 0; col < n; ++col) {
        int pivot_row = col;
        double maxabs = std::fabs(aug[col][col]);
        for (int r = col + 1; r < n; ++r) {
            double v = std::fabs(aug[r][col]);
            if (v > maxabs) { maxabs = v; pivot_row = r; }
        }
        if (maxabs < EPS) {
            for (int i = 0; i < n; ++i) delete[] aug[i];
            delete[] aug;
            return false;
        }
        if (pivot_row != col) {
            double* tmp = aug[col];
            aug[col] = aug[pivot_row];
            aug[pivot_row] = tmp;
        }
        double pivot = aug[col][col];
        for (int c = 0; c < 2 * n; ++c) aug[col][c] /= pivot;
        for (int r = 0; r < n; ++r) {
            if (r == col) continue;
            double factor = aug[r][col];
            if (std::fabs(factor) > 0.0) {
                for (int c = 0; c < 2 * n; ++c)
                    aug[r][c] -= factor * aug[col][c];
            }
        }
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            inv[i][j] = aug[i][n + j];
    for (int i = 0; i < n; ++i) delete[] aug[i];
    delete[] aug;
    return true;
}
inline bool divisionInversaMat(int** a, int** b, double** resultado, int n) {
    double** Ad = matrizDouble(n);
    double** Bd = matrizDouble(n);
    double** invB = matrizDouble(n);
    if (!Ad || !Bd || !invB) {
        eliminarMatrizDouble(Ad, n);
        eliminarMatrizDouble(Bd, n);
        eliminarMatrizDouble(invB, n);
        return false;
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            Ad[i][j] = static_cast<double>(a[i][j]);
            Bd[i][j] = static_cast<double>(b[i][j]);
        }
    bool ok = invertirMatriz(Bd, invB, n);
    if (!ok) {
        eliminarMatrizDouble(Ad, n);
        eliminarMatrizDouble(Bd, n);
        eliminarMatrizDouble(invB, n);
        return false;
    }
    multiplicacionMatDouble(Ad, invB, resultado, n);
    eliminarMatrizDouble(Ad, n);
    eliminarMatrizDouble(Bd, n);
    eliminarMatrizDouble(invB, n);
    return true;
}

inline void suma(int x, int y) {
    std::cout << x << " + " << y << " = " << (x + y) << std::endl;
}
inline void resta(int x, int y) {
    std::cout << x << " - " << y << " = " << (x - y) << std::endl;
}
inline void multiplicacion(int x, int y) {
    std::cout << x << " x " << y << " = " << (x * y) << std::endl;
}
inline void division(int x, int y) {
    if (y != 0) std::cout << x << " / " << y << " = " << (x / y) << std::endl;
    else std::cout << "Error: División entre 0." << std::endl;
}

inline void inicioCalculadora() {
    int opcion1 = -1, opcion2 = -1, num1, num2, n;
    ListaDeObjetos<int**> matricesGuardadas;
    while (opcion1 != 0) {
        std::cout << " *******   C A L C U L A D O R A  ******* " << std::endl;
        std::cout << " ---------------------------------------- " << std::endl;
        std::cout << "          1. Operaciones básicas: " << std::endl;
        std::cout << "          2. Operaciones con matrices: " << std::endl;
        std::cout << " ---------------------------------------- " << std::endl;
        std::cout << "          0. Salir " << std::endl;
        std::cin >> opcion1;
        int** matrizA = nullptr;
        int** matrizB = nullptr;
        int** resultado = nullptr;
        if (opcion1 == 1 || opcion1 == 2) {
            opcion2 = -1;
            while (opcion2 != 0) {
                if (opcion1 == 1) {
                    std::cout << " *******   C A L C U L A D O R A  ******* " << std::endl;
                    std::cout << " ---------------------------------------- " << std::endl;
                    std::cout << "          Operaciones básicas: " << std::endl;
                    std::cout << "          1. + Suma " << std::endl;
                    std::cout << "          2. - Resta " << std::endl;
                    std::cout << "          3. x Multiplicación " << std::endl;
                    std::cout << "          4. / División " << std::endl;
                    std::cout << " ---------------------------------------- " << std::endl;
                    std::cout << "          0. Regresar " << std::endl;
                    std::cin >> opcion2;
                } else if (opcion1 == 2) {
                    std::cout << " *******   C A L C U L A D O R A  ******* " << std::endl;
                    std::cout << " ---------------------------------------- " << std::endl;
                    std::cout << "          Operaciones con matrices: " << std::endl;
                    std::cout << " ---------------------------------------- " << std::endl;
                    std::cout << "Ingrese el tamaño (n) de la matriz (n x n): " << std::endl;
                    std::cin >> n;
                    matrizA = matrizInt(n);
                    matrizB = matrizInt(n);
                    resultado = matrizInt(n);
                    if (!matrizA || !matrizB || !resultado) {
                        std::cout << "Error reservando memoria para las matrices." << std::endl;
                        eliminarMatrizInt(matrizA, n);
                        eliminarMatrizInt(matrizB, n);
                        eliminarMatrizInt(resultado, n);
                        matrizA = matrizB = resultado = nullptr;
                        opcion2 = 0;
                        continue;
                    }
                    matricesGuardadas.append(matrizA);
                    matricesGuardadas.append(matrizB);
                    matricesGuardadas.append(resultado);
                    std::cout << "Ingrese los elementos de la primera matriz:" << std::endl;
                    for (int i = 0; i < n; ++i)
                        for (int j = 0; j < n; ++j)
                            std::cin >> matrizA[i][j];
                    std::cout << "Ingrese los elementos de la segunda matriz:" << std::endl;
                    for (int i = 0; i < n; ++i)
                        for (int j = 0; j < n; ++j)
                            std::cin >> matrizB[i][j];
                    std::cout << "Matriz A:" << std::endl;
                    imprimirMatriz(matrizA, n);
                    std::cout << "Matriz B:" << std::endl;
                    imprimirMatriz(matrizB, n);
                    std::cout << " ---------------------------------------- " << std::endl;
                    std::cout << "       Seleccione una operación:  " << std::endl;
                    std::cout << "          5. + Suma " << std::endl;
                    std::cout << "          6. - Resta " << std::endl;
                    std::cout << "          7. x Multiplicación " << std::endl;
                    std::cout << "          8. / División " << std::endl;
                    std::cout << " ---------------------------------------- " << std::endl;
                    std::cout << "          0. Regresar " << std::endl;
                    std::cin >> opcion2;
                }
                switch (opcion2) {
                    case 1:
                        std::cout << "Ingrese el primer número: " << std::endl;
                        std::cin >> num1;
                        std::cout << "Ingrese el segundo número: " << std::endl;
                        std::cin >> num2;
                        suma(num1, num2);
                        break;
                    case 2:
                        std::cout << "Ingrese el primer número: " << std::endl;
                        std::cin >> num1;
                        std::cout << "Ingrese el segundo número: " << std::endl;
                        std::cin >> num2;
                        resta(num1, num2);
                        break;
                    case 3:
                        std::cout << "Ingrese el primer número: " << std::endl;
                        std::cin >> num1;
                        std::cout << "Ingrese el segundo número: " << std::endl;
                        std::cin >> num2;
                        multiplicacion(num1, num2);
                        break;
                    case 4:
                        std::cout << "Ingrese el primer número: " << std::endl;
                        std::cin >> num1;
                        std::cout << "Ingrese el segundo número: " << std::endl;
                        std::cin >> num2;
                        division(num1, num2);
                        break;
                    case 5:
                        sumaMat(matrizA, matrizB, resultado, n);
                        std::cout << "Resultado de la suma:" << std::endl;
                        imprimirMatriz(resultado, n);
                        opcion2 = 0;
                        break;
                    case 6:
                        restaMat(matrizA, matrizB, resultado, n);
                        std::cout << "Resultado de la resta:" << std::endl;
                        imprimirMatriz(resultado, n);
                        opcion2 = 0;
                        break;
                    case 7:
                        multiplicacionMat(matrizA, matrizB, resultado, n);
                        std::cout << "Resultado de la multiplicación:" << std::endl;
                        imprimirMatriz(resultado, n);
                        opcion2 = 0;
                        break;
                    case 8: {
                        double** resultadoD = matrizDouble(n);
                        if (!resultadoD) {
                            std::cout << "Error reservando memoria para la matriz de resultado." << std::endl;
                            break;
                        }
                        bool ok = divisionInversaMat(matrizA, matrizB, resultadoD, n);
                        if (ok) {
                            std::cout << "Resultado de la división:" << std::endl;
                            imprimirMatrizDouble(resultadoD, n);
                        } else {
                            std::cout << "No se pudo invertir B (es singular)." << std::endl;
                        }
                        eliminarMatrizDouble(resultadoD, n);
                        opcion2 = 0;
                        break;
                    }
                }
            }
        }
        // Liberación de matrices creadas (desde la lista)
        for (int i = 1; i <= matricesGuardadas.getSize(); i++) {
            int** mat = matricesGuardadas.get(i);
            if (mat) eliminarMatrizInt(mat, n);
        }
    }
}