# Sistema de Gestión de Tickets

Este programa permite registrar, priorizar y gestionar tickets de soporte mediante una lista enlazada y un sistema de prioridades.

------------------------------------

## Cómo compilar y ejecutar ##

### Requisitos:
- Tener instalado `gcc` (compilador de C)
- Sistema operativo con terminal (Linux, macOS, WSL en Windows o cualquier terminal que soporte gcc)

### Pasos para compilar:
```bash
gcc test.c -o test
```

### Para ejecutar el programa:
```bash
./test
```
------------------------------------

## ✅ Funcionalidades implementadas

1. Registrar un ticket con ID y descripción.
2. Asignar prioridad (BAJO, MEDIO, ALTO) a un ticket existente.
3. Mostrar todos los tickets pendientes ordenados por prioridad y hora.
4. Procesar el siguiente ticket (prioriza los más urgentes).
5. Buscar un ticket por su ID.
6. Salir del sistema.


## ❌ Funcionalidades no implementadas o errores conocidos

- El sistema **no guarda los tickets en archivos**, por lo tanto, al cerrar el programa **se pierden los datos registrados**.
- No hay validación para IDs duplicados. Se pueden registrar dos tickets con el mismo ID.
- No hay validación para campos vacíos o incorrectos (excepto para la prioridad).

---------------------------------------------------------------------

## 🧪 Ejemplo de uso (interacción con el programa)

```text
*****SISTEMA DE TICKETS*****
1. Registrar Ticket
2. Asignar Prioridad al ticket
3. Mostrar lista de tickets pendientes
4. Procesar siguiente ticket
5. Buscar ticket por ID
0. Exit
> 1

Ingrese ID del ticket: 101
Ingrese descripcion del problema: No enciende el PC
Ticket registrado con ID 101.

> 2
Ingrese ID del ticket: 101
Ingrese la Prioridad (0=BAJA, 1=MEDIA, 2=ALTA)
> 2
Prioridad actualizada

> 3
--- Tickets pendientes ---
ID: 101 | Prioridad: ALTO | Hora: Sat Apr 11 16:00:00 2025
Descripción: No enciende el PC

> 4
Procesando ticket ID 101
Desc: No enciende el PC
Prioridad: 2
Hora: Sat Apr 11 16:00:00 2025

> 0
Saliendo del sistema...
```