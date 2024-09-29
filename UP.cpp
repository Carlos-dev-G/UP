#include <iostream>
#include <windows.h>
#include <cstring>
#include "UP.hpp"

int main(int argc, char *argv[])
{
    // Variable para indicar si se encontró el argumento -I
    bool foundI = false;

    // Iterar sobre los argumentos proporcionados desde la línea de comandos
    for (int i = 1; i < argc; ++i) // Comenzamos en 1 para evitar argv[0] que es el nombre del programa
    {
        // Comparar el argumento actual con las opciones "-i" o "-I"
        if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "-I") == 0)
        {
            foundI = true; // Marcamos que encontramos -I o -i
            
            // Verificar si hay un siguiente argumento que contiene el valor del ejecutable
            if (i + 1 < argc)
            {
                // Llamar a la función UP_PROCES pasando el siguiente argumento (ruta del ejecutable)
                bool resultado = UP_PROCES(argv[i + 1], true);

                // Verificar el resultado de la ejecución del proceso
                if (resultado)
                {
                    std::cout << "Proceso ejecutado con éxito." << std::endl;
                    Sleep(1500);
                    // Intentar limpiar los rastros con UP_CLEAR
                    if (UP_CLEAR())
                    {
                        std::cout << "Rastro eliminado con éxito" << std::endl;
                    }
                    else
                    {
                        std::cout << "Error al eliminar el rastro" << std::endl;
                    }
                }
                else
                {
                    std::cout << "Error al ejecutar el proceso." << std::endl;
                }
                return 0; // Finalizamos la ejecución correctamente o con error
            }
            else
            {
                // Si no se proporciona un valor después de -I o -i
                std::cout << "Error: Falta el valor para -I." << std::endl;
                return 1; // Indicamos error de uso
            }
        }
        // Opción para mostrar el menú de ayuda si se pasa "-h" o "-H"
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-H") == 0)
        {
            std::cout << " -- MENU DE AYUDA -- " << std::endl;
            std::cout << " Uso: UP.exe -i c:\\ruta_del_executable.exe" << std::endl;
            std::cout << " Uso: UP.exe -I c:\\ruta_del_executable.exe" << std::endl;
            return 0; // Mostramos el menú de ayuda y salimos
        }
    }

    // Si el argumento -I no fue proporcionado
    if (!foundI)
    {
        std::cout << "Error: -I no fue proporcionado." << std::endl;
        return 1; // Indicamos error si no se encontró -I o -i
    }

    return 0; // Éxito
}
