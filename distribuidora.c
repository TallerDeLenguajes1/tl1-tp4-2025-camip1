#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define tareaInicial 1000

struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}typedef Tarea;

typedef struct Nodo Nodo; 

struct Nodo{
    Tarea T;
    Nodo *Siguiente;
}; 

Nodo * crearTarea(int i);
void ingresarPendientes(Nodo **tareasPendientes);
void mostrarTareas(Nodo *tareasPendientes, Nodo *tareasRealizadas);
void registrarRealizadas(Nodo **tareasPendientes, Nodo **tareasRealizadas);
void liberarLista(Nodo *lista);

//Luego modularizar con el nombre To-Do
int main(){
    Nodo *tareasPendientes = NULL;
    Nodo *tareasRealizadas = NULL;
    ingresarPendientes(&tareasPendientes);
    registrarRealizadas(&tareasPendientes,&tareasRealizadas);
    mostrarTareas(tareasPendientes,tareasRealizadas);
    
    liberarLista(tareasPendientes);
    liberarLista(tareasRealizadas);
    return 0;
}

void liberarLista(Nodo *lista) {
    while (lista) {
        Nodo *temp = lista;
        lista = lista->Siguiente;
        free(temp->T.Descripcion); // liberar descripción
        free(temp); // liberar nodo
    }
}

Nodo * crearTarea(int i){
    char descripcion[50];
    Nodo *nuevaTarea=(Nodo *)malloc(sizeof(Nodo));
    nuevaTarea->T.TareaID=i+tareaInicial; //muestra 1000 no suma;
    
    printf("Ingresar descripcion de la tarea %d:", nuevaTarea->T.TareaID);
    getchar();
    gets(descripcion);
    int tamCadena = strlen(descripcion);
    nuevaTarea->T.Descripcion=(char *)malloc(tamCadena*sizeof(char) + 1);
    strcpy(nuevaTarea->T.Descripcion,descripcion);  //copiar descripcion en el puntero descripcion
    
    do {
        printf("Ingrese la duracion de la tarea (entre 10 y 100): ");
        scanf("%d", &nuevaTarea->T.Duracion);
    } while(nuevaTarea->T.Duracion < 10 || nuevaTarea->T.Duracion > 100);
    
    nuevaTarea->Siguiente=NULL;
    return nuevaTarea;
}

void ingresarPendientes(Nodo **tareasPendientes){
    int cargar=1; //bandera para cargar tareas
    int i=0; //contador para asignarle numero a la tarea
    Nodo *nuevaTarea;
    while(cargar==1){
        nuevaTarea=crearTarea(i);
        nuevaTarea->Siguiente = *tareasPendientes; //apunto nuevo nodo a la tarea anterior
        *tareasPendientes = nuevaTarea; //apunto start a la nueva tarea o nodo
        printf("\nDesea cargar otra tarea? si(escribir 1)/no(escribir 0):");
        scanf("%d",&cargar);
        i++; 
    }
}

void registrarRealizadas(Nodo **tareasPendientes, Nodo **tareasRealizadas){
    int registrar=1; //bandera para cargar tareas
    int id; //para determinar la tarea a registrar
    Nodo **aux = tareasPendientes;

    while(registrar==1){
        printf("\ningrese el id de la tarea realizada:");
        scanf("%d",&id);

        aux = tareasPendientes;

        while (*aux!=NULL && (*aux)->T.TareaID!=id)
        {
            aux=&(*aux)->Siguiente;
        }

        if (*aux!=NULL)
        {
            Nodo *realizada=*aux;
            *aux=(*aux)->Siguiente;

            realizada->Siguiente=  *tareasRealizadas;
            *tareasRealizadas = realizada;
            
            printf("Tarea completada registrada.\n");
        }
        else {
            printf("ID invalido. Operacion cancelada.\n");
        }

        printf("\nDesea registrar otra tarea realizada? si(escribir 1)/no(escribir 0):");
        scanf("%d",&registrar);
    }
}


void mostrarTareas(Nodo *tareasPendientes, Nodo *tareasRealizadas){
    Nodo *aux;
    printf("\n\nTareas pendientes");
    if (tareasPendientes!=NULL){
        aux=tareasPendientes;
        while (aux!=NULL)
        {
            printf("\ntarea %d: %s\n", aux->T.TareaID, aux->T.Descripcion);
            printf("Duracion: %d", aux->T.Duracion);
            aux=aux->Siguiente;
        }
    }
    else{
        printf("\nVacia");
    }
    printf("\n\nTareas completadas");
    if (tareasRealizadas!=NULL)
    {
        aux=tareasRealizadas;
        while(aux!=NULL)
        {
            printf("\ntarea %d: %s\n",aux->T.TareaID, aux->T.Descripcion);
            printf("Duracion: %d",aux->T.Duracion);
            aux=aux->Siguiente;
        }
    }
    else{
        printf("\nVacia");
    }
}

/*
2)Implemente una interfaz para elegir qué tareas de la lista de pendientes deben ser
transferidas a la lista de tareas realizadas.
3) Implemente una funcionalidad que permita listar todas las tareas pendientes y realizadas.
4) Implemente una funcionalidad que permita consultar tareas por id o palabra clave y
mostrarlas por pantalla, indicando si corresponde a una tarea pendiente o realizada*/