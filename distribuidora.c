#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define tareaInicial 1000;

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

Nodo *ingresarTareas(Nodo *tareasPendientes);
void mostrar(Nodo *tareasPendientes);

//Luego modularizar con el nombre To-Do
int main(){
    Nodo *tareasPendientes;
    Nodo *tareasRealizadas;
    //int cantPendientes;

    ingresarTareas(tareasPendientes);
    
    /*tareasPendientes=(Nodo *)malloc(cantPendientes*sizeof(Nodo));
    for (int i = 1; i <= cantPendientes; i++)
    {

    }*/
    return 0;
}

Nodo *ingresarTareas(Nodo *tareasPendientes){
    Nodo *nuevaTarea;
    int cargar=1; //bandera para cargar tareas
    int i=0; //contador para asignarle tamaño al puntero
    char descripcion[50];
    
    while(cargar!=0){
        Nodo *nuevaTarea=(Nodo *)malloc((i+1)*sizeof(Nodo));
        
        nuevaTarea->T.TareaID=i+tareaInicial; //muestra 1000 no suma;
        printf("Ingresar descripcion de la tarea %d:", nuevaTarea->T.TareaID);
        fflush(stdin);
        gets(descripcion);
        int tamCadena = strlen(descripcion);

        nuevaTarea->T.Descripcion=(char *)malloc(tamCadena*sizeof(char) + 1);
        strcpy(nuevaTarea->T.Descripcion,descripcion);  //copiar descripcion en el puntero descripcion
        puts(nuevaTarea->T.Descripcion);

        printf("ingrese la duracion de la tarea (en horas):");
        scanf("%d",&nuevaTarea->T.Duracion);

        nuevaTarea->Siguiente=tareasPendientes; //apunto nuevo nodo a la tarea anterior
        tareasPendientes=nuevaTarea; //apunto start a la nueva tarea o nodo

        printf("Desea cargar otra tarea? si(escribir 1)/no(escribir 0):");
        scanf("%d",&cargar);
        i++;
    }
    return tareasPendientes;
}
