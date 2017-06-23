
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ArrayList.h"
#include "funcAux.h"
#include "Destinatarios.h"

#define ALL 0
#define ACTIVE 1
#define DELETED 2


void listarDestinatarios(ArrayList* listaDestinatarios)
{
    //FILE* pArchivo = abrirArchivo();

    FILE* pArchivo = NULL;
    pArchivo = fopen("destinatarios.csv","r"); ///  Abrirlo como solo lectura
    if ( pArchivo == NULL )
        printf("\n El archivo no pudo ser abierto! La ejecucion se detendra. \n");
    else
    //if ( pArchivo != NULL )
        parserDestinatario(pArchivo, listaDestinatarios);
}

int parserDestinatario(FILE* pFile, ArrayList* listaDestinatarios)
{
    int retorno = 0;

    while(!feof(pFile))
    {
        Destinatario* pDestinatario = malloc(sizeof(Destinatario));
        if ( pDestinatario != NULL )
        {
            fscanf(pFile,"%[^,],%[^\n]\n",pDestinatario->nombre,pDestinatario->email);
            if ( listaDestinatarios->add(listaDestinatarios, pDestinatario) == -1)
            {
                retorno = -1;
                break;
            }
        }
        //printf("\n Nombre %s \t - Email %s \r\n",pDestinatario->nombre,pDestinatario->email);
    }
    return retorno;
}


/**
 * \brief Abre el archivo con los datos de destinatarios
 * \param
 * \return pArchivo* Retorna un puntero al archivo o NULL en caso de error.
 */
FILE* abrirArchivo()
{
    char* nombreArchivo[50];
    tomarNombreArchivo(nombreArchivo); //"destinatarios.csv"
    //printf("Nombre archivo: %s", nombreArchivo);
    FILE* pArchivo = NULL;
    pArchivo = fopen(*nombreArchivo,"r"); ///  Abrirlo como solo lectura
    if ( pArchivo == NULL )
        printf("\n El archivo no pudo ser abierto! La ejecucion se detendra. \n");
    return pArchivo;
}



/**
 * @brief muetra por pantalla los datos de un usuario.
 * @param pDestinatario el puntero al usuario se pasa por parametro.
 * @param flagRegistro recibe como parametro el estado del usuario.
 * @return no devuelve nada.
 */
void printUsuario(Destinatario* pDestinatario)
{
    if(pDestinatario != NULL)
        printf("\n Nombre %s \t - Email %s \r\n",pDestinatario->nombre,pDestinatario->email);
}


/**
 * @brief lista por pantalla los datos de usuarios.
 * @param pDestinatario el puntero al usuario se pasa por parametro.

 * @return no devuelve nada.
 */
void printDestinatarios(ArrayList* listaDestinatarios)
{
    int i;

    if( listaDestinatarios == NULL )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else if ( listaDestinatarios->isEmpty(listaDestinatarios) == 1 )
        printf("\n No se pueden listar usuarios porque no hay ninguno cargado! \n");
    else
    {
        printf("\n LISTA DE DESTINATARIOS \n");
        printf(" ----------------------------------------------------------------------------- ");
        for (i=0; i<listaDestinatarios->size; i++)
            printUsuario( listaDestinatarios->get(listaDestinatarios, i) ); // la funcion printUsuario se encarga de verificar si get obtiene un puntero nulo
        printf("\n ----------------------------------------------------------------------------- ");
        printf("\n FIN LISTA DE DESTINATARIOS \n");
    }
}


void cargarDestinatariosEnArray(ArrayList* listaDestinatarios)
{
    FILE* pArchivo = NULL;
    pArchivo = fopen("destinatarios.csv","r"); ///  Abrirlo como solo lectura
    if ( pArchivo == NULL )
        printf("\n El archivo no pudo ser abierto! La ejecucion se detendra. \n");
    else if ( listaDestinatarios != NULL )
    //if ( pArchivo != NULL )
        parserDestinatario(pArchivo, listaDestinatarios);
}


void cargarListaNegraEnArray(ArrayList* listaDestinatarios)
{
    FILE* pArchivo = NULL;
    pArchivo = fopen("black_list.csv","r"); ///  Abrirlo como solo lectura
    if ( pArchivo == NULL )
        printf("\n El archivo no pudo ser abierto! La ejecucion se detendra. \n");
    else if ( listaDestinatarios != NULL )
    //if ( pArchivo != NULL )
        parserDestinatario(pArchivo, listaDestinatarios);
}



/**
 * @brief pide al usuario el nombre del archivo y lo carga en un puntero char.
 * @param recibe el puntero a char como parametro.
 * @return no devuelve nada.
 */
void tomarNombreArchivo(char* nombreArchivo)
{
    //char password[50];
    char arrayCharsAdmitidos[1]=".";
    getType("\n Ingrese el nombre del archivo: ", "\n El dato ingresado es invalido!\
        \n Solo se adminten letras, numeros, el caracter '.' y que no exceda los 49 caracteres \n",1,2,arrayCharsAdmitidos,49,nombreArchivo);
}










/**
 * @brief lista por pantalla la lista de usuarios activos ordenados por promedio de calificaciones
 * @param pDestinatario el puntero al usuario se pasa por parametro.
 * @param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * @param order int  [1] indicate UP - [0] indicate DOWN
 * @return no devuelve nada.
 */
void listarDestinatariosFiltrados(ArrayList* listaDestinatarios, ArrayList* listaNegra, int (*pFuncCompare)(char*,char*) )
{
    int flag = 0;
    ArrayList* cloneListaDestinatarios = NULL;
    ArrayList* cloneListaDestinatarios2 = NULL;

    if ( listaDestinatarios != NULL && listaNegra != NULL  &&  pFuncCompare != NULL  )
    {
     // cloneListaDestinatarios = listaDestinatarios->filter(listaDestinatarios, pFuncCompare, filter, pCompare);
        cloneListaDestinatarios = (ArrayList*)al_filter(listaDestinatarios, listaNegra, pFuncCompare, 0);

       /* do
        {

        }while( cloneListaDestinatarios2 != NULL ) */
        //cloneListaDestinatarios2 = cloneListaDestinatarios;
        //cloneListaDestinatarios = (ArrayList*)al_filter(cloneListaDestinatarios, cloneListaDestinatarios2, pFuncCompare, 1);



        if ( cloneListaDestinatarios != NULL )
        {
            printf("\n LISTA DE DESTINATARIOS FILTRADOS: \n");
            printf(" ----------------------------------------------------------------------------- ");
            printDestinatarios(cloneListaDestinatarios);
            al_deleteArrayList(cloneListaDestinatarios);
            flag = 1;
        }
    }
    if (flag == 0)
        printf("\n Error de memoria y/o parametros! La lista no puede ser informada. \n");
}



int compararDestinatario(char* pDestinatarioA, char* pDestinatarioB)
{
    int retorno = -2;

    //printf ("Destinatario %s",pDestinatarioA );

    if ( pDestinatarioA != NULL && pDestinatarioB != NULL )
    {
        retorno =  stricmp ( pDestinatarioA, pDestinatarioB );
    }
    return retorno;
}
