#ifndef RECURSOS_COMUNES_H
#define RECURSOS_COMUNES_H

#include <iostream>
#include <random>
#include <limits>
#include <cmath>

// ==================== Juego "Adivina el número" ====================
class JuegoAdivinaNumero {
private:
    int numero_secreto;
    int intentos;
public:
    JuegoAdivinaNumero() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 100);
        numero_secreto = dis(gen);
        intentos = 0;
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
            intentos++;
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
                std::cout << "¡Felicidades! Adivinaste el número en " << intentos << " intentos!\n";
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
    if (y != 0) {
        std::cout << x << " / " << y << " = " << (x / y) << std::endl;
    } else {
        std::cout << "Error: División entre 0." << std::endl;
    }
}

inline void sumaMat(int** a, int** b, int** resultado, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            resultado[i][j] = a[i][j] + b[i][j];
}

inline void restaMat(int** a, int** b, int** resultado, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            resultado[i][j] = a[i][j] - b[i][j];
}

inline void multiplicacionMat(int** a, int** b, int** resultado, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            resultado[i][j] = 0;
            for (int k = 0; k < n; ++k)
                resultado[i][j] += a[i][k] * b[k][j];
        }
}

inline void imprimirMatriz(int** matriz, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << matriz[i][j] << " ";
        std::cout << std::endl;
    }
}

inline void inicioCalculadora() {
    int opcion1 = -1, opcion2 = -1, num1, num2, n;
    int** matrizA = nullptr;
    int** matrizB = nullptr;
    int** resultado = nullptr;

    while (opcion1 != 0) {
        std::cout << " *******   C A L C U L A D O R A  ******* " << std::endl;
        std::cout << " ---------------------------------------- " << std::endl;
        std::cout << "          1. Operaciones básicas: " << std::endl;
        std::cout << "          2. Operaciones con matrices: " << std::endl;
        std::cout << " ---------------------------------------- " << std::endl;
        std::cout << "          0. Salir " << std::endl;
        std::cin >> opcion1;

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

                    matrizA = new int*[n];
                    matrizB = new int*[n];
                    resultado = new int*[n];

                    for (int i = 0; i < n; ++i) {
                        matrizA[i] = new int[n];
                        matrizB[i] = new int[n];
                        resultado[i] = new int[n];
                    }

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
                }
            }
        }
        // Liberación de memoria para matrices dinámicas
        if (matrizA != nullptr) {
            for (int i = 0; i < n; ++i) {
                delete[] matrizA[i];
                delete[] matrizB[i];
                delete[] resultado[i];
            }
            delete[] matrizA;
            delete[] matrizB;
            delete[] resultado;
            matrizA = matrizB = resultado = nullptr;
        }
    }
}

#endif // RECURSOS_COMUNES_H