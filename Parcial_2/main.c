#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ELEMENTS 5

#include "ArrayList.h"
#include "funcAux.h"
#include "Destinatarios.h"

#define ALL 0
#define ACTIVE 1
#define DELETED 2

#define SALIR 5

int main(void)
{
    int opcion=0;

    ArrayList* listaDestinatarios = al_newArrayList();
    ArrayList* listaNegra = al_newArrayList();

    if ( listaDestinatarios == NULL || listaNegra == NULL )
        opcion=SALIR;


    while(opcion!=SALIR)
    {
        printf("\n");
        printf(" 1- Cargar Destinatarios \n");
        printf(" 2- Cargar lista negra \n");
        printf(" 3- Depurar \n");
        printf(" 4- Listar \n");
        printf("\n");
        printf("%d- Salir \n", SALIR);

        getInt(&opcion,"\n Ingrese una opcion: ","\n\n La opcion ingresada es incorrecta! Debe elegir una opcion del 1 al SALIR. \n",1,1,1,1,SALIR);

        switch(opcion)
        {
            case 1:
                //abrirArchivo();
                cargarDestinatariosEnArray(listaDestinatarios);
                //printDestinatarios(listaDestinatarios);
                //printf("\n size: %d", listaDestinatarios->size);
                printf("\n Lista cargada correctamente \n");
                break;
            case 2:
                //abrirArchivo();
                cargarListaNegraEnArray(listaNegra);
                //printDestinatarios(listaNegra);
                //printf("\n size: %d", listaNegra->size);
                printf("\n Lista cargada correctamente \n");
                break;
            case 3:
                //abrirArchivo();
                printf("\n Funcion no terminada aun. \n");
                break;
            case 4:
                //listarDestinatarios(listaDestinatarios);
                //parserDestinatario( abrirArchivo(), listaDestinatarios);
                //
                //printDestinatarios(listaDestinatarios);
                //printDestinatarios(listaNegra);

                listarDestinatariosFiltrados(listaDestinatarios, listaNegra, compararDestinatario );
                break;
            case SALIR:
                printf("\n\n PROCESO TERMINADO. \n");
                break;
        }
    }
    return 0;
}




