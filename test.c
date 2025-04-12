#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -------- ESTRUCTURAS Y FUNCIONES --------

// Enumeración para representar la prioridad de los tickets
typedef enum { BAJO, MEDIO, ALTO } Prioridad;

// Estructura que define un ticket en la lista enlazada
typedef struct Ticket {
    int id;                         // ID único del ticket
    char descripcion[256];          // Descripción del problema
    Prioridad prioridad;            // Prioridad del ticket
    time_t hora_registro;           // Hora en que se registró el ticket
    struct Ticket* siguiente;       // Puntero al siguiente ticket en la lista
} Ticket;

Ticket* lista = NULL; // Lista enlazada que almacena los tickets pendientes

// Función para registrar un nuevo ticket en la lista
void registrar_ticket(int id, const char* descripcion){
    Ticket* nuevo = (Ticket*)malloc(sizeof(Ticket));
    nuevo->id = id;
    strcpy(nuevo->descripcion, descripcion);
    nuevo->prioridad = BAJO; // Prioridad inicial por defecto
    nuevo->hora_registro = time(NULL); // Tiempo actual
    nuevo->siguiente = NULL;

    // Agregar al final de la lista
    if(lista == NULL){
        lista = nuevo;
    } else {
        Ticket* actual = lista;
        while(actual->siguiente) actual = actual->siguiente;
        actual->siguiente = nuevo;
    }
    printf("Ticket registrado con ID %d.\n", id);
}

// Función para asignar una nueva prioridad a un ticket específico
void asignar_prioridad(int id, Prioridad nueva_prioridad){
    Ticket* actual = lista;
    while(actual){
        if(actual->id == id){
            actual->prioridad = nueva_prioridad;
            printf("Prioridad actualizada\n");
            return;
        }
        actual = actual->siguiente;
    }
    printf("Ticket con ID %d no encontrado.\n", id);
}

// Función para mostrar todos los tickets pendientes ordenados por prioridad (ALTO -> BAJO)
void mostrar_tickets(){
    if(lista == NULL){
        printf("No hay tickets pendientes.\n");
        return;
    }

    const char* nombres_prioridad[] = { "BAJO", "MEDIO", "ALTO" };
    Prioridad niveles[] = { ALTO, MEDIO, BAJO }; // Orden inverso para mostrar primero los más urgentes

    printf("\n*****Tickets pendientes*****\n");
    for (int i = 0; i < 3; i++) {
        Prioridad prioridad_actual = niveles[i];
        Ticket* actual = lista;

        while (actual) {
            if (actual->prioridad == prioridad_actual) {
                printf("ID: %d | Prioridad: %s | Fecha y Hora: %sDescripcion: %s\n",
                       actual->id,
                       nombres_prioridad[actual->prioridad],
                       ctime(&(actual->hora_registro)),
                       actual->descripcion);
            }
            actual = actual->siguiente;
        }
    }
}

// Función para procesar el ticket más urgente (mayor prioridad y más antiguo)
void procesar_ticket(){
    if(!lista){
        printf("No hay tickets pendientes.\n");
        return;
    }

    Ticket *anterior = NULL, *actual = lista;
    Ticket *mejor = NULL, *mejor_ant = NULL;

    // Buscar el ticket con mayor prioridad (y si hay empate, el más antiguo)
    for(; actual; anterior = actual, actual = actual->siguiente){
        if(!mejor || actual->prioridad > mejor->prioridad ||
           (actual->prioridad == mejor->prioridad &&
            actual->hora_registro < mejor->hora_registro)){
            mejor = actual;
            mejor_ant = anterior;
        }
    }

    // Eliminar el ticket de la lista
    if(mejor_ant){
        mejor_ant->siguiente = mejor->siguiente;
    } else {
        lista = mejor->siguiente;
    }

    // Mostrar la información del ticket procesado
    char* hora = ctime(&mejor->hora_registro);
    hora[strlen(hora) - 1] = '\0'; // Quitar salto de línea
    printf("Procesando ticket ID %d\nDescripcion: %s\nPrioridad: %d\nFecha y Hora: %s\n",
           mejor->id, mejor->descripcion, mejor->prioridad, hora);

    free(mejor); // Liberar memoria del ticket procesado
}

// Función para buscar un ticket por ID e imprimir su información
void buscar_ticket(int id){
    Ticket* actual = lista;
    while(actual){
        if(actual->id == id){
            char* hora = ctime(&actual->hora_registro);
            hora[strlen(hora) - 1] = '\0';
            printf("ID: %d\nDescripcion: %s\nPrioridad: %d\nFecha y Hora: %s\n",
                   actual->id, actual->descripcion, actual->prioridad, hora);
            return;
        }
        actual = actual->siguiente;
    }
    printf("Ticket no encontrado.\n");
}

// -------- PROGRAMA PRINCIPAL --------

int main(){
    int opcion;

    do{
        // Menú de opciones para el usuario
        printf("\n*****SISTEMA DE TICKETS*****\n");
        printf("1. Registrar Ticket\n");
        printf("2. Asignar Prioridad al ticket\n");
        printf("3. Mostrar lista de tickets pendientes\n");
        printf("4. Procesar siguiente ticket\n");
        printf("5. Buscar ticket por ID\n");
        printf("0. Exit\n");
        scanf("%d", &opcion);
        getchar(); // Limpiar buffer

        // Lógica de opciones del menú
        if(opcion == 1){
            int id;
            char descripcion[256];
            printf("Ingrese ID del ticket: ");
            scanf("%d", &id);
            getchar();
            printf("Ingrese descripcion del problema: ");
            fgets(descripcion, sizeof(descripcion), stdin);
            descripcion[strcspn(descripcion, "\n")] = 0; // Eliminar salto de línea
            registrar_ticket(id, descripcion);
        } else if(opcion == 2){
            int id, prioridad;
            printf("Ingrese ID del ticket: ");
            scanf("%d", &id);
            printf("Ingrese la Prioridad (0=BAJO, 1=MEDIO, 2=ALTO): ");
            scanf("%d", &prioridad);
            if(prioridad >= 0 && prioridad <= 2){
                asignar_prioridad(id, (Prioridad)prioridad);
            } else {
                printf("Prioridad Invalida.\n");
            }
        } else if(opcion == 3){
            mostrar_tickets();
        } else if(opcion == 4){
            procesar_ticket();
        } else if(opcion == 5){
            int id;
            printf("Ingrese ID del ticket a buscar: ");
            scanf("%d", &id);
            buscar_ticket(id);
        } else if(opcion == 0){
            printf("Saliendo del sistema...\n");
        } else {
            printf("Opcion no valida.\n");
        }

    } while(opcion != 0);

    return 0;
}
