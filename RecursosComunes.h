
#ifndef RECURSOS_COMUNES_H
#define RECURSOS_COMUNES_H

// Inclusión de librerías estándar para entrada/salida, generación de números aleatorios, límites, matemáticas y formato
#include <iostream>       // Entrada y salida estándar (cout, cin)
#include <random>         // Generador de números aleatorios
#include <limits>         // Definición de límites numéricos de tipos estándar
#include <cmath>          // Funciones matemáticas (abs, fabs)
#include <iomanip>        // Formato de salida (setprecision)
#include "Listas.h"       // Archivo personalizado (implementación de listas, se asume su existencia)

// ==================== Juego "Adivina el número"  ====================
// Definición de la clase que implementa el juego "Adivina el número"
class JuegoAdivinaNumero {
private:
    int numero_secreto;                      // Variable para guardar el número secreto a adivinar
    ListaDeObjetos<int> intentos;            // Lista de los intentos realizados por el usuario
public:
    // Constructor que inicializa el número secreto de forma aleatoria entre 1 y 100
    JuegoAdivinaNumero() {
        std::random_device rd;               // Dispositivo de generación de semilla aleatoria
        std::mt19937 gen(rd());              // Motor de generación de números aleatorios (Mersenne Twister)
        std::uniform_int_distribution<> dis(1, 100); // Distribución uniforme entre 1 y 100
        numero_secreto = dis(gen);           // Asignación del número secreto
    }
    // Método principal del juego
    void jugar() {
        int adivinanza;                      // Variable para guardar la adivinanza del usuario
        bool adivinado = false;              // Bandera para indicar si el número fue adivinado
        while (!adivinado) {                 // Ciclo principal del juego, se repite hasta adivinar
            std::cout << "Introduce tu adivinanza (1-100): ";
            if (!(std::cin >> adivinanza)) { // Validación de entrada: si no es número
                std::cin.clear();            // Limpia el estado de error de cin
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignora el resto de la línea
                std::cout << "Entrada no válida. Por favor, introduce un número (1-100).\n";
                continue;                    // Repite el ciclo sin procesar el intento
            }
            intentos.append(adivinanza);     // Guarda el intento en la lista
            int diferencia = std::abs(adivinanza - numero_secreto); // Calcula la diferencia absoluta
            if (adivinanza < numero_secreto) {                      // Si el intento es menor
                if (diferencia > 10)
                    std::cout << "Demasiado bajo. ¡Intentalo de nuevo!\n";
                else
                    std::cout << "Bajo. ¡Intentalo de nuevo!\n";
            } else if (adivinanza > numero_secreto) {               // Si el intento es mayor
                if (diferencia > 10)
                    std::cout << "Demasiado alto. ¡Intentalo de nuevo!\n";
                else
                    std::cout << "Alto. ¡Intentalo de nuevo!\n";
            } else {                                                // Si el intento es igual al secreto
                std::cout << "¡Felicidades! Adivinaste el número en " << intentos.getSize() << " intentos!\n";
                std::cout << "Tus intentos fueron: ";
                for (int i = 1; i <= intentos.getSize(); i++)
                    std::cout << intentos.get(i) << " ";           // Imprime todos los intentos realizados
                std::cout << std::endl;
                adivinado = true;                                  // Termina el ciclo
            }
        }
    }
};

// Función inline que inicia el juego llamando al método jugar de la clase
inline void jugarAdivinaNumero() {
    JuegoAdivinaNumero juego;
    juego.jugar();
}

// ==================== Calculadora Avanzada ====================

// Crea una matriz dinámica de enteros de tamaño n x n inicializada en 0
inline int** matrizInt(int n) {
    int** m = new(std::nothrow) int*[n];       // Reserva memoria para n punteros a filas
    if (!m) return nullptr;                    // Si falla la reserva, retorna nullptr
    for (int i = 0; i < n; ++i) {
        m[i] = new(std::nothrow) int[n];       // Reserva memoria para cada fila
        if (!m[i]) {                           // Si falla la reserva de una fila
            for (int j = 0; j < i; ++j) delete[] m[j]; // Libera filas ya reservadas
            delete[] m;
            return nullptr;
        }
        for (int j = 0; j < n; ++j) m[i][j] = 0; // Inicializa cada elemento en 0
    }
    return m;                                   // Retorna el puntero a la matriz
}

// Libera la memoria de una matriz dinámica de enteros
inline void eliminarMatrizInt(int** m, int n) {
    if (!m) return;                             // Si el puntero es nulo, no hace nada
    for (int i = 0; i < n; ++i) delete[] m[i];  // Libera cada fila
    delete[] m;                                 // Libera el arreglo de punteros a filas
}

// Imprime una matriz de enteros de tamaño n x n en consola
inline void imprimirMatriz(int** matriz, int n) {
    if (!matriz) return;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << matriz[i][j] << " ";   // Imprime cada elemento de la fila
        std::cout << std::endl;                 // Nueva línea al final de la fila
    }
}

// Suma dos matrices de enteros elemento a elemento y guarda el resultado en una tercera matriz
inline void sumaMat(int** a, int** b, int** resultado, int n) {
    if (!a || !b || !resultado) return;         // Verifica que los punteros no sean nulos
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            resultado[i][j] = a[i][j] + b[i][j]; // Suma correspondiente
}

// Resta dos matrices de enteros elemento a elemento y guarda el resultado en una tercera matriz
inline void restaMat(int** a, int** b, int** resultado, int n) {
    if (!a || !b || !resultado) return;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            resultado[i][j] = a[i][j] - b[i][j];
}

// Multiplica dos matrices de enteros siguiendo la regla de multiplicación de matrices
inline void multiplicacionMat(int** a, int** b, int** resultado, int n) {
    if (!a || !b || !resultado) return;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            resultado[i][j] = 0;               // Inicializa el valor
            for (int k = 0; k < n; ++k)
                resultado[i][j] += a[i][k] * b[k][j]; // Suma el producto de filas por columnas
        }
}

// Crea una matriz dinámica de dobles de tamaño n x n inicializada en 0.0
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

// Libera la memoria de una matriz dinámica de dobles
inline void eliminarMatrizDouble(double** m, int n) {
    if (!m) return;
    for (int i = 0; i < n; ++i) delete[] m[i];
    delete[] m;
}

// Imprime una matriz de dobles con formato fijo y 6 decimales
inline void imprimirMatrizDouble(double** matriz, int n) {
    if (!matriz) return;
    std::cout << std::fixed << std::setprecision(6); // Formato de 6 decimales
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            std::cout << matriz[i][j] << " ";
        std::cout << std::endl;
    }
}

// Multiplica dos matrices de dobles siguiendo la regla de multiplicación de matrices
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

// Invierte una matriz de dobles A y guarda el resultado en inv usando el método de Gauss-Jordan
inline bool invertirMatriz(double** A, double** inv, int n) {
    const double EPS = 1e-12;                       // Tolerancia para cero numérico
    double** aug = matrizDouble(n);                  // Matriz aumentada (A | I)
    if (!aug) return false;
    for (int i = 0; i < n; ++i) {
        aug[i] = new(std::nothrow) double[2 * n];    // Reserva columnas dobles para A|I
        if (!aug[i]) {
            for (int j = 0; j < i; ++j) delete[] aug[j];
            eliminarMatrizDouble(aug, n);
            return false;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) aug[i][j] = A[i][j];            // Copia A
        for (int j = 0; j < n; ++j) aug[i][n + j] = (i == j) ? 1.0 : 0.0; // Copia I
    }
    for (int col = 0; col < n; ++col) {
        int pivot_row = col;
        double maxabs = std::fabs(aug[col][col]);     // Encuentra el mayor pivote absoluto
        for (int r = col + 1; r < n; ++r) {
            double v = std::fabs(aug[r][col]);
            if (v > maxabs) { maxabs = v; pivot_row = r; }
        }
        if (maxabs < EPS) {                           // Si el pivote es demasiado pequeño, la matriz es singular
            for (int i = 0; i < n; ++i) delete[] aug[i];
            delete[] aug;
            return false;
        }
        if (pivot_row != col) {                       // Intercambia filas si el pivote no está en la diagonal
            double* tmp = aug[col];
            aug[col] = aug[pivot_row];
            aug[pivot_row] = tmp;
        }
        double pivot = aug[col][col];
        for (int c = 0; c < 2 * n; ++c) aug[col][c] /= pivot; // Normaliza la fila del pivote
        for (int r = 0; r < n; ++r) {
            if (r == col) continue;
            double factor = aug[r][col];
            if (std::fabs(factor) > 0.0) {
                for (int c = 0; c < 2 * n; ++c)
                    aug[r][c] -= factor * aug[col][c];         // Elimina la columna en otras filas
            }
        }
    }
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            inv[i][j] = aug[i][n + j];                        // Copia la parte invertida de aug a inv
    for (int i = 0; i < n; ++i) delete[] aug[i];
    delete[] aug;
    return true;                                               // Retorna éxito
}

// Divide dos matrices de enteros: convierte a double, invierte la segunda, multiplica por la primera
inline bool divisionInversaMat(int** a, int** b, double** resultado, int n) {
    double** Ad = matrizDouble(n);         // Crea matriz double para a
    double** Bd = matrizDouble(n);         // Crea matriz double para b
    double** invB = matrizDouble(n);       // Crea matriz double para la inversa de b
    if (!Ad || !Bd || !invB) {             // Verifica memoria
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
    bool ok = invertirMatriz(Bd, invB, n); // Intenta invertir Bd
    if (!ok) {                             // Si falla, libera memoria y retorna false
        eliminarMatrizDouble(Ad, n);
        eliminarMatrizDouble(Bd, n);
        eliminarMatrizDouble(invB, n);
        return false;
    }
    multiplicacionMatDouble(Ad, invB, resultado, n); // Multiplica Ad por invB y guarda en resultado
    eliminarMatrizDouble(Ad, n);
    eliminarMatrizDouble(Bd, n);
    eliminarMatrizDouble(invB, n);
    return true;
}

// Operaciones básicas entre dos enteros, muestran el resultado en consola
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

// Menú principal para la calculadora avanzada
inline void inicioCalculadora() {
    int opcion1 = -1, opcion2 = -1, num1, num2, n; // Variables para opciones, números y tamaño de matriz
    ListaDeObjetos<int**> matricesGuardadas;        // Lista para guardar los punteros de matrices creadas
    while (opcion1 != 0) {                          // Menú principal, sale si opción1 es 0
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
        if (opcion1 == 1 || opcion1 == 2) {         // Si elige operaciones básicas o con matrices
            opcion2 = -1;
            while (opcion2 != 0) {                  // Menú secundario
                if (opcion1 == 1) {                 // Operaciones básicas
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
                } else if (opcion1 == 2) {          // Operaciones con matrices
                    std::cout << " *******   C A L C U L A D O R A  ******* " << std::endl;
                    std::cout << " ---------------------------------------- " << std::endl;
                    std::cout << "          Operaciones con matrices: " << std::endl;
                    std::cout << " ---------------------------------------- " << std::endl;
                    std::cout << "Ingrese el tamaño (n) de la matriz (n x n): " << std::endl;
                    std::cin >> n;
                    matrizA = matrizInt(n);         // Reserva matrizA
                    matrizB = matrizInt(n);         // Reserva matrizB
                    resultado = matrizInt(n);       // Reserva matriz resultado
                    if (!matrizA || !matrizB || !resultado) {
                        std::cout << "Error reservando memoria para las matrices." << std::endl;
                        eliminarMatrizInt(matrizA, n);
                        eliminarMatrizInt(matrizB, n);
                        eliminarMatrizInt(resultado, n);
                        matrizA = matrizB = resultado = nullptr;
                        opcion2 = 0;
                        continue;
                    }
                    matricesGuardadas.append(matrizA);    // Guarda punteros en la lista
                    matricesGuardadas.append(matrizB);
                    matricesGuardadas.append(resultado);
                    std::cout << "Ingrese los elementos de la primera matriz:" << std::endl;
                    for (int i = 0; i < n; ++i)
                        for (int j = 0; j < n; ++j)
                            std::cin >> matrizA[i][j];     // Solicita elementos de matrizA
                    std::cout << "Ingrese los elementos de la segunda matriz:" << std::endl;
                    for (int i = 0; i < n; ++i)
                        for (int j = 0; j < n; ++j)
                            std::cin >> matrizB[i][j];     // Solicita elementos de matrizB
                    std::cout << "Matriz A:" << std::endl;
                    imprimirMatriz(matrizA, n);            // Imprime matrizA
                    std::cout << "Matriz B:" << std::endl;
                    imprimirMatriz(matrizB, n);            // Imprime matrizB
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
                // Selección de operación según opción2
                switch (opcion2) {
                    case 1:
                        std::cout << "Ingrese el primer número: " << std::endl;
                        std::cin >> num1;
                        std::cout << "Ingrese el segundo número: " << std::endl;
                        std::cin >> num2;
                        suma(num1, num2);                  // Suma dos números
                        break;
                    case 2:
                        std::cout << "Ingrese el primer número: " << std::endl;
                        std::cin >> num1;
                        std::cout << "Ingrese el segundo número: " << std::endl;
                        std::cin >> num2;
                        resta(num1, num2);                 // Resta dos números
                        break;
                    case 3:
                        std::cout << "Ingrese el primer número: " << std::endl;
                        std::cin >> num1;
                        std::cout << "Ingrese el segundo número: " << std::endl;
                        std::cin >> num2;
                        multiplicacion(num1, num2);        // Multiplica dos números
                        break;
                    case 4:
                        std::cout << "Ingrese el primer número: " << std::endl;
                        std::cin >> num1;
                        std::cout << "Ingrese el segundo número: " << std::endl;
                        std::cin >> num2;
                        division(num1, num2);              // Divide dos números
                        break;
                    case 5:
                        sumaMat(matrizA, matrizB, resultado, n); // Suma dos matrices
                        std::cout << "Resultado de la suma:" << std::endl;
                        imprimirMatriz(resultado, n);
                        opcion2 = 0;
                        break;
                    case 6:
                        restaMat(matrizA, matrizB, resultado, n); // Resta dos matrices
                        std::cout << "Resultado de la resta:" << std::endl;
                        imprimirMatriz(resultado, n);
                        opcion2 = 0;
                        break;
                    case 7:
                        multiplicacionMat(matrizA, matrizB, resultado, n); // Multiplica dos matrices
                        std::cout << "Resultado de la multiplicación:" << std::endl;
                        imprimirMatriz(resultado, n);
                        opcion2 = 0;
                        break;
                    case 8: {
                        double** resultadoD = matrizDouble(n); // Reserva matriz de dobles para resultado
                        if (!resultadoD) {
                            std::cout << "Error reservando memoria para la matriz de resultado." << std::endl;
                            break;
                        }
                        bool ok = divisionInversaMat(matrizA, matrizB, resultadoD, n); // Divide matrices
                        if (ok) {
                            std::cout << "Resultado de la división:" << std::endl;
                            imprimirMatrizDouble(resultadoD, n);
                        } else {
                            std::cout << "No se pudo invertir B (es singular)." << std::endl;
                        }
                        eliminarMatrizDouble(resultadoD, n); // Libera resultadoD
                        opcion2 = 0;
                        break;
                    }
                }
            }
        }
        // Libera las matrices creadas durante el ciclo
        for (int i = 1; i <= matricesGuardadas.getSize(); i++) {
            int** mat = matricesGuardadas.get(i);
            if (mat) eliminarMatrizInt(mat, n); // Libera cada matriz si existe
        }
    }
}
#endif // RECURSOS_COMUNES_H