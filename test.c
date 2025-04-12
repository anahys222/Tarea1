#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// -------- ESTRUCTURAS Y FUNCIONES --------

typedef enum { BAJO, MEDIO, ALTO } Prioridad;

typedef struct Ticket {
    int id;
    char descripcion[256];
    Prioridad prioridad;
    time_t hora_registro;
    struct Ticket* siguiente;
} Ticket;

Ticket* lista = NULL;

void registrar_ticket(int id, const char* descripcion){
    Ticket* nuevo = (Ticket*)malloc(sizeof(Ticket));
    nuevo->id = id;
    strcpy(nuevo->descripcion, descripcion);
    nuevo->prioridad = BAJO;
    nuevo->hora_registro = time(NULL);
    nuevo->siguiente = NULL;

    if(lista == NULL){
        lista = nuevo;
    }else{
        Ticket* actual = lista;
        while(actual->siguiente) actual = actual->siguiente;
        actual->siguiente = nuevo;
    }
    printf("Ticket registrado con ID %d.\n", id);
}

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

void mostrar_tickets(){
    if(lista == NULL){
        printf("No hay tickets pendientes.\n");
        return;
    }

    const char* nombres_prioridad[] = { "BAJO", "MEDIO", "ALTO" };
    Prioridad niveles[] = { ALTO, MEDIO, BAJO }; 

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

void procesar_ticket(){
    if(!lista){
        printf("No hay tickets pendientes.\n");
        return;
    }
    Ticket* anterior = NULL, *actual = lista, *mejor = NULL, *mejor_ant = NULL;
    for(; actual; anterior = actual, actual= actual->siguiente){
        if(!mejor || actual->prioridad > mejor->prioridad ||
           (actual->prioridad == mejor->prioridad &&
            actual->hora_registro < mejor->hora_registro)){
            mejor = actual;
            mejor_ant = anterior;
        }
    }

    if(mejor_ant){
        mejor_ant->siguiente = mejor->siguiente;
    }else{
        lista = mejor->siguiente;
    }

    char* hora = ctime(&mejor->hora_registro);
    hora[strlen(hora) - 1] = '\0';
    printf("Procesando ticket ID %d\nDescripcion: %s\nPrioridad: %d\nFecha y Hora: %s\n",
           mejor->id, mejor->descripcion, mejor->prioridad, hora);
    free(mejor);
}

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
        printf("\n*****SISTEMA DE TICKETS*****\n");
        printf("1. Registrar Ticket\n");
        printf("2. Asignar Prioridad al ticket\n");
        printf("3. Mostrar lista de tickets pendientes\n");
        printf("4. Procesar siguiente ticket\n");
        printf("5. Buscar ticket por ID\n");
        printf("0. Exit\n");
        scanf("%d", &opcion);
        getchar();

        if(opcion == 1){
            int id;
            char descripcion[256];
            printf("Ingrese ID del ticket: ");
            scanf("%d", &id);
            getchar();
            printf("Ingrese descripcion del problema: ");
            fgets(descripcion, sizeof(descripcion), stdin);
            descripcion[strcspn(descripcion, "\n")] = 0;
            registrar_ticket(id, descripcion);
        }else if(opcion == 2){
            int id, prioridad;
            printf("Ingrese ID del ticket: ");
            scanf("%d", &id);
            printf("Ingrese la Prioridad (0=BAJO, 1=MEDIO, 2=ALTO): ");
            scanf("%d", &prioridad);
            if(prioridad >= 0 && prioridad <= 2){
                asignar_prioridad(id, (Prioridad)prioridad);
            }else{
                printf("Prioridad Invalida.\n");
            }
        }else if(opcion == 3){
            mostrar_tickets();
        }else if(opcion == 4){
            procesar_ticket();
        }else if(opcion == 5){
            int id;
            printf("Ingrese ID del ticket a buscar: ");
            scanf("%d", &id);
            buscar_ticket(id);
        }else if(opcion == 0){
            printf("Saliendo del sistema...\n");
        }else{
            printf("Opcion no valida.\n");
        }
    }while(opcion != 0);
    return 0;
}
