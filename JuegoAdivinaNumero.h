#ifndef JUEGO_ADIVINA_NUMERO_H
#define JUEGO_ADIVINA_NUMERO_H

#include <iostream>
#include <random>
#include <limits>
#include <cmath>

class JuegoAdivinaNumero {
private:
    int numero_secreto;
    int intentos;

public:
    JuegoAdivinaNumero() {
        std::random_device rd;           // Mejor aleatoriedad que time(0)
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

// Función  para llamar desde el menú
void jugarAdivinaNumero() {
    JuegoAdivinaNumero juego;
    juego.jugar();
}

#endif // JUEGO_ADIVINA_NUMERO_H