# UP - Elevación de Privilegios

Este programa permite ejecutar aplicaciones como administrador aprovechando una vulnerabilidad en `fodhelper.exe`, elevando privilegios sin mostrar la ventana de UAC en sistemas Windows.

## Requisitos

- Windows (se recomienda Windows 10 o superior)
- Compilador compatible con C++11 o superior

## Compilación

Para compilar el proyecto, usa un compilador de C++ que soporte C++11 o superior. Por ejemplo, puedes usar g++:

```bash
g++ UP.cpp -o UP.exe
```

## Uso

El programa se ejecuta desde la línea de comandos. La sintaxis es la siguiente:

```bash
UP.exe -i <ruta_a_tu_executable.exe>
```

### Ejemplo

Para ejecutar un programa llamado `mi_programa.exe` ubicado en `C:\ruta\de\mi_programa.exe` como administrador, utiliza el siguiente comando:

```bash
UP.exe -i C:\ruta\de\mi_programa.exe
```

## Opciones

- `-i` o `-I`: Especifica el ejecutable que deseas ejecutar como administrador.
- `-h` o `-H`: Muestra el menú de ayuda.

## Notas

- Asegúrate de que tu programa se encuentre en una ruta accesible.
- El uso de este programa debe ser responsable y conforme a las políticas de seguridad de tu entorno.
