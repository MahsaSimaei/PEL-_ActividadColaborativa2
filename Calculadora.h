//
// Created by athin on 23/10/2025.
//

#ifndef PEL__ACTIVIDADCOLABORATIVA2_CALCULADORA_H
#define PEL__ACTIVIDADCOLABORATIVA2_CALCULADORA_H
void suma(int x, int y) {
    std::cout << x << " + " << y << " = " << (x + y) << std::endl;
}

void resta(int x, int y) {
    std::cout << x << " - " << y << " = " << (x - y) << std::endl;
}

void multiplicacion(int x, int y) {
    std::cout << x << " x " << y << " = " << (x * y) << std::endl;
}

void division(int x, int y) {
    if (y != 0) {
        std::cout << x << " / " << y << " = " << (x / y) << std::endl;
    } else {
        std::cout << "Error: División entre 0." << std::endl;
    }
}

// -- Funciones de matrices (usando punteros dobles)
void sumaMat(int** a, int** b, int** resultado, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            resultado[i][j] = a[i][j] + b[i][j];
        }
    }
}

void restaMat(int** a, int** b, int** resultado, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            resultado[i][j] = a[i][j] - b[i][j];
        }
    }
}

void multiplicacionMat(int** a, int** b, int** resultado, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            resultado[i][j] = 0; // Inicializa el elemento en 0
            for (int k = 0; k < n; ++k) {
                resultado[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void imprimirMatriz(int** matriz, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << matriz[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Función inicial de calculadora
void inicioCalculadora() {
    int opcion1, opcion2, num1, num2, n;
    // Crear matrices dinámicamente
    int** matrizA;
    int** matrizB;
    int** resultado;

    while (opcion1 != 0) {
        std::cout << " *******   C A L C U L A D O R A  ******* " << std::endl;
        std::cout << " ---------------------------------------- " << std::endl;
        std::cout << "          1. Operaciones básicas: " << std::endl;
        std::cout << "          2. Operaciones con matrices: " << std::endl;
        std::cout << " ---------------------------------------- " << std::endl;
        std::cout << "          0. Salir " << std::endl;
        std::cin >> opcion1;

        if (opcion1 == 1 || opcion1 == 2) {
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

                    // Llenar matrices
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

                    // Ingresar valores para la primera matriz
                    std::cout << "Ingrese los elementos de la primera matriz:" << std::endl;
                    for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < n; ++j) {
                            std::cin >> matrizA[i][j];
                        }
                    }

                    // Ingresar valores para la segunda matriz
                    std::cout << "Ingrese los elementos de la segunda matriz:" << std::endl;
                    for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < n; ++j) {
                            std::cin >> matrizB[i][j];
                        }
                    }

                    // Imprimir datos
                    std::cout << "Matriz A:" << std::endl;
                    imprimirMatriz(matrizA, n);
                    std::cout << "Matriz B:" << std::endl;
                    imprimirMatriz(matrizB, n);

                    // Seleccionar opción
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
                    // Operaciones básicas
                    case 1: // Suma
                        std::cout << "Ingrese el primer número: " << std::endl;
                        std::cin >> num1;
                        std::cout << "Ingrese el segundo número: " << std::endl;
                        std::cin >> num2;
                        suma(num1, num2); // Llamar función
                    break;
                    case 2: // Resta
                        std::cout << "Ingrese el primer número: " << std::endl;
                        std::cin >> num1;
                        std::cout << "Ingrese el segundo número: " << std::endl;
                        std::cin >> num2;
                        resta(num1, num2);// Llamar función
                    break;
                    case 3: // Multiplicación
                        std::cout << "Ingrese el primer número: " << std::endl;
                        std::cin >> num1;
                        std::cout << "Ingrese el segundo número: " << std::endl;
                        std::cin >> num2;
                        multiplicacion(num1, num2); // Llamar función
                    break;
                    case 4: // Division
                        std::cout << "Ingrese el primer número: " << std::endl;
                        std::cin >> num1;
                        std::cout << "Ingrese el segundo número: " << std::endl;
                        std::cin >> num2;
                        division(num1, num2); // Llamar función
                    break;

                    // Operaciones con matrices
                    case 5: // Suma de matrices
                        sumaMat(matrizA, matrizB, resultado, n);
                        std::cout << "Resultado de la suma:" << std::endl;
                        imprimirMatriz(resultado, n);
                        opcion2 = 0; // Regresar a menú de operaciones
                        break;
                    case 6: // Resta de matrices
                        restaMat(matrizA, matrizB, resultado, n);
                        std::cout << "Resultado de la resta:" << std::endl;
                        imprimirMatriz(resultado, n);
                        opcion2 = 0; // Regresar a menú de operaciones
                    break;
                    case 7: // Multiplicación de matrices
                        multiplicacionMat(matrizA, matrizB, resultado, n);
                        std::cout << "Resultado de la multiplicación:" << std::endl;
                        imprimirMatriz(resultado, n);
                        opcion2 = 0; // Regresar a menú de operaciones
                    break;
                    break;
                }
            }
        }
    }
}

#endif //PEL__ACTIVIDADCOLABORATIVA2_CALCULADORA_H