#include <iostream>
#include <string>
#include "Recursos.h"
#include "Usuario.h"
using namespace std;
//Listas de usuarios
ListaDeObjetos<Estuadiante> estudiantes;
ListaDeObjetos<Profesor> profesores;
Admin admin("Admin","González", "xyz",3);


// Menú de Profesor
void menuProfesor() {
    int opcion = -1;
    //Mostrar menu de inicio
    while (opcion != 0){
        do{
            
    std::cout << "\n===== MENU PROFESOR =====" << std::endl;
    std::cout << "1. Visualizar estudiantes" << std::endl;
    std::cout << "2. Visualizar datos de la clase" << std::endl;
    std::cout << "3. Calculadora avanzada" << std::endl;
    std::cout << "4. Juego de adivinanza" << std::endl;
    std::cout << "0. Cerrar sesion" << std::endl;
    std::cout << "Opcion: ";
    std::cin >> opcion;
        }while(opcion < 0 || opcion > 4);
    //Llamar a la función correspondiente de acuerdo a la elección del usuario
        switch(opcion) {
            case 1: //Visualizar estudiantes
                break;
            case 2: //Visualizar clase
                break;
            case 3: //Calculadora avanzada
                inicioCalculadora();
            break;
            case 4: //Juego de Adivinanza 
                juegoRecurso5();
            break;
            case 0: //Cerrar Sesión
            std::cout << "Saliendo...." << std::endl;
            break;
        }
    }        
}

// Menú de Estudiante
void menuEstudiante() {
    int opcion = -1; //Inicializar en -1 para entrar en el bucle
    //Mostrar menú de inicio
    while(opcion!= 0){
        do{
            
    std::cout << "\n===== MENU ESTUDIANTE =====" << std::endl;
    std::cout << "1. Cargar fichero a la mochila" << std::endl;
    std::cout << "2. Ver contenido de la mochila" << std::endl;
    std::cout << "3. Calculadora avanzada" << std::endl;
    std::cout << "4. Juego de adivinanza" << std::endl;
    std::cout << "0. Cerrar sesion" << std::endl;
    std::cout << "Opcion: ";
    std::cin>> opcion; //Almacenar opcion
        }while(opcion < 0 || opcion > 3);
    //Llamar a función correspondiente de acuerdo a la elección del usuario
        switch(opcion){
            case 1: //Cargar fichero a la mochila
                break;
            case 2: //Ver contenido de la mochila
                break;
            case 3://Calculadora avanzada
                inicioCalculadora();
            break;
            case 4: //Juego de adivinanza
                juegoRecurso5();
            break;
            case 0: //Cerrar sesión
                std::cout << "Saliendo..." << std::endl;
            break;
        }
    }          
}

// Menú de Administrador
void menuAdministrador() {
    int opcion = -1;
    while(opcion != 0){
        do{
    std::cout << "\n===== MENU ADMINISTRADOR =====" << endl;
    std::cout << "1. Dar de alta usuario" << endl;
    std::cout << "2. Dar de baja usuario" << endl;
    std::cout << "3. Gestionar datos de usuario" << endl;
    std::cout << "4. Listar usuarios" << endl;
    std::cout << "0. Cerrar sesion" << endl;
    std::cout << "Opcion: ";
    std::cin >> opcion;
        }while(opcion < 0 || opcion > 3);
    //Llamar a función correspondiente de acuerdo a la elección del usuario

    switch(opcion){
        case 1: { //Dar de alta usuario
            //Pedir datos
            std::string nombre, pass, apellido;
            int id, tipo;
            std::cout << "===== ALTA USUARIO: =====" << std::endl;
            std::cout << " 1. Ingrese el nombre: " << std::endl;
            std::cin >> nombre;
            std::cout << " 2. Ingrese el apellido: "<< std::endl;
            std::cin >> apellido;
            std::cout << " 3. Ingrese la contraseña: " << std::endl;
            std::cin >> pass;
            std::cout << " 4. Ingrese el id: " << std::endl;
            std::cin >> id;
            std::cout << " 5. Ingrese el tipo de usuario: 1) Estudiante 2) Profesor " << std::endl;
            std::cin >> tipo;
            //Agregar usuario
            if(tipo == 1) { //Estudiante
                estudiantes.append(Estudiante(nombre,apellido,pass,id));
                std::cout << "Estudiante dado de alta correctamente!" << std::ednl;
            }else if(tipo == 2){ //Profesor
                profesores.append(Profesor(nombre,apellido,pass,id));
                std::cout << "Profesor dado de alta correctamente! << std::endl;
                    }
            break;
        }
        case 2: { //Dar de baja usuario
            int id, tipo;
            std::cout << "==== BAJA USUARIO: ====" std::endl;
            std::cout << " 1. Ingrese el tipo de usuario: 1) Estudiante 2) Profesor " << std::endl;
            std::cin >> tipo;
            std::cout << " 2. Ingrese el id del usuario: " << std::endl;
            std::cin >> id;
            if(tipo == 1) {
                for(int i = 1; i <= estudiantes.getSize(); i++){
                    if(estudiantes.get(i).getId() == id){
                        estudiantes.erase(i);
                        std::cout << "Estudiante dado de baja correctamente! " << std::endl;
                        break; //Salir del bucle una vez encontrado
                    }
                }
            }else if(tipo == 2){
                for(int i = 1; i <= profesores.getSize(); i++){
                    if(profesores.get(i).getId() == id){
                        profesores.erase(i);
                        std::cout << "Profesor dado de baja correctamente!" << std::endl;
                        break;
                    }
                }
            }
            break;
        }
        case 3: //Gestionar datos de usuario
        break;
        case 4: //Listar usuarios
        break;
        case 0: //Salir
        std::cout << "Saliendo...." << std::endl;
        break;
    }
}
}


