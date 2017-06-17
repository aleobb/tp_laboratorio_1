#include <stdio.h>
#include <stdlib.h>

#include "../inc/ArrayList.h"

#include "funcAux.h"
#include <string.h>
#include "Usuarios.h"

#define ALL 0
#define ACTIVE 1
#define DELETED 2

/** \brief carga un nuevo usuario
 * \param se le pasan todos los datos de ese usuario
 * \return int Return (NULL) si no se pudo cargar el usuario - Puntero al usuario si se pudo cargar correctamente.
 */
Usuario* newUsuario(int id, char nombre[], char password[], int contadorCalificaciones, int acumuladorCalificaciones, int flagRegistro)
{
    Usuario* returnAux = NULL;
    Usuario* pUsuario = malloc(sizeof(Usuario));

    if(pUsuario != NULL)
    {
        pUsuario->id = id;
        strcpy(pUsuario->nombre,nombre);
        strcpy(pUsuario->password,password);
        pUsuario->contadorCalificaciones = contadorCalificaciones;
        pUsuario->acumuladorCalificaciones = acumuladorCalificaciones;
        pUsuario->flagRegistro = flagRegistro;
        returnAux = pUsuario;
    }
    return returnAux;
}


/**
 * @brief muetra por pantalla los datos de un usuario.
 * @param pUsuario el puntero al usuario se pasa por parametro.
 * @param flagRegistro recibe como parametro el estado del usuario.
 * @return no devuelve nada.
 */
void printUsuario(Usuario* pUsuario, int flagRegistro)
{
    if( flagRegistro == ALL )
        flagRegistro = pUsuario->flagRegistro;
    if ( pUsuario->flagRegistro == flagRegistro )
        printf("\n Id %d - Nombre %s - Password %s - ContCalif %d - AcumCalif %d - flaReg %d\
               ", pUsuario->id, pUsuario->nombre, pUsuario->password, pUsuario->contadorCalificaciones,
                pUsuario->acumuladorCalificaciones, pUsuario->flagRegistro);
    printf("\n");
}


/**
 * @brief lista por pantalla los datos de usuarios.
 * @param pUsuario el puntero al usuario se pasa por parametro.
 * @param flagRegistro recibe como parametro el estado del usuario.
 * @return no devuelve nada.
 */
void listarUsuarios(ArrayList* listaUsuarios, int flagRegistro)
{
    int i;
    for (i=0; i<listaUsuarios->size; i++)
        printUsuario( listaUsuarios->get(listaUsuarios, i), flagRegistro);
}

int cargaInicialUsuarios (ArrayList* listaUsuarios)
{
    Usuario* pAux1 = malloc(sizeof(Usuario));
    Usuario* pAux2 = malloc(sizeof(Usuario));
    Usuario* pAux3 = malloc(sizeof(Usuario));
    Usuario* pAux4 = malloc(sizeof(Usuario));

    pAux1 = newUsuario(1, "BBB" ,"fuckyou", 1, 5, ACTIVE);
    if ( pAux1 !=NULL )
        listaUsuarios->add(listaUsuarios,pAux1);

    pAux2 = newUsuario(2, "AAA" ,"fusdfsd", 3, 25, ACTIVE);
    if ( pAux2 !=NULL )
        listaUsuarios->add(listaUsuarios,pAux2);

    pAux3 = newUsuario(3, "CCC" ,"fdsfu", 2, 14, DELETED);
    if ( pAux3 !=NULL )
        listaUsuarios->add(listaUsuarios,pAux3);

    pAux4 = newUsuario(4, "ALE1" ,"fuTttttfsd", 0, 0, ACTIVE);
    if ( pAux4 !=NULL )
        listaUsuarios->add(listaUsuarios,pAux4);

    return 0;
}



/**
 * @brief busca si se encuentra cargado un id de usuario.
 * @param listaUsuarios se pasa como parametro.
 * @param idUsuario se pasa como como parametro.
 * @return devuelve el puntero a la ubicacion de memoria donde estan guardados los datos de ese usuario (o NULL si no exite o si el tamaño del array es invalido o un puntero NULO)
 */
Usuario* buscarUsuarioPorId(ArrayList* listaUsuarios, int idUsuario)
{
    Usuario* pUsuario = malloc(sizeof(Usuario));
    int i;

    if ( listaUsuarios == NULL || pUsuario == NULL )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else
        for (i=0; i<listaUsuarios->size; i++)
        {
            pUsuario=listaUsuarios->get(listaUsuarios, i);
            if ( pUsuario->flagRegistro == ACTIVE && pUsuario->id == idUsuario )
                  break;
        }
    return pUsuario;
}


/**
 * \brief Realiza el ingresdo de datos de un usuario
 * \param listaUsuarios se le pasa como parametro
 * \return devuelve -1 si Tamaño invalido o puntero NULL pointer o sin espacio disponible - (0) si la carga se pudo realizar.
 */
int altaUsuario(ArrayList* listaUsuarios)
{
    Usuario* pUsuario = malloc(sizeof(Usuario));
    int retorno = -1;

    if ( listaUsuarios == NULL || pUsuario == NULL )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else
    {
        //pUsuario.id=calcularIdUsuario(arrayUsuarios,sizeArrayUsuarios);
        //printf("\n El nro de id para el usuario a cargar es: %d \n",arrayAuxiliarUsuario[0].id);
        //if(arrayAuxiliarUsuario[0].id>0)

            pUsuario->id = calcularIdUsuario(listaUsuarios);
            printf("\n El id del usuario sera: %d \n", pUsuario->id);
            cargaNombreUsuario(pUsuario->nombre);
            cargaPasswordUsuario(pUsuario->password);
            pUsuario->flagRegistro=ACTIVE;
            pUsuario->contadorCalificaciones=0;
            pUsuario->acumuladorCalificaciones=0;

            listaUsuarios->add(listaUsuarios,pUsuario);
            retorno = 0;
            printf("\n El usuario ha sido cargado correctamente. \n");
    }
    return retorno;
}


/**
 * @brief pide al usuario los datos de nombre del usuario y los carga (validados) en un puntero char.
 * @param recibe el puntero a char como parametro.
 * @return no devuelve nada.
 */
void cargaNombreUsuario(char* nombre)
{
    //char nombre[50];
    char arrayCharsAdmitidos[1]="-";
    getType("\n Ingrese el nombre del usuario: ", "\n El dato ingresado es invalido!\
        \n Solo se adminten letras, numeros, el caracter '-' y que no exceda los 49 caracteres \n",1,2,arrayCharsAdmitidos,49,nombre);
}


/**
 * @brief pide al usuario los datos de password del usuario y los carga (validados) en un puntero char.
 * @param recibe el puntero a char como parametro.
 * @return no devuelve nada.
 */
void cargaPasswordUsuario(char* password)
{
    //char password[50];
    char arrayCharsAdmitidos[1]="-";
    getType("\n Ingrese el password del usuario: ", "\n El dato ingresado es invalido!\
        \n Solo se adminten letras, numeros, el caracter '-' y que no exceda los 49 caracteres \n",1,2,arrayCharsAdmitidos,49,password);
}


/**
 * @brief cacula el proximo numero de id de usuario en una secuencia autoincrementable.
 * @param arrayUsuarios el array se pasa como parametro.
 * @param sizeArrayUsuarios el tamaño del array se pasa como parametro.
 * @return devuelve el proximo id (o -1 si no exite ninguno disponible o si el tamaño del array es invalido o un puntero NULO)
 */
int calcularIdUsuario(ArrayList* listaUsuarios)
{
    int nextIdUsuario=-1;
    int i;
    Usuario* pUsuario = malloc(sizeof(Usuario));

    if ( listaUsuarios == NULL )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else if ( listaUsuarios->size == 0 )
        nextIdUsuario = 1;
    else
        for (i=0; i<listaUsuarios->size; i++)
        {
            pUsuario=listaUsuarios->get(listaUsuarios, i);
            if ( i==0 || ( pUsuario->id >= nextIdUsuario ) )
                nextIdUsuario=pUsuario->id+1;
        }
    return nextIdUsuario;
}


/**
 * \brief Realiza la baja logica de un usuario o lo borra definitivamente
 * \param listaUsuarios se le pasa como parametro
 * \return devuelve -1 si Tamaño invalido o puntero NULL pointer o sin espacio disponible - (0) si la baja se pudo realizar.
 */
int bajaUsuario(ArrayList* listaUsuarios)
{
    int retorno = -1;
    int opcion=0;
    int opcionMaxima=3;
    int indiceUsuario=-1;
    Usuario* pUsuario = malloc(sizeof(Usuario));


    if ( listaUsuarios == NULL || pUsuario == NULL )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else
    {
        if ( listaUsuarios->size == 0 )
            printf("\n No se puede eliminar un usuario porque no hay ninguno cargado! \n");
        else
        {
            indiceUsuario=tomarYcomprobarExistenciaUsuarioPorId(listaUsuarios, "\n La baja del usuario ha sido cancelada! \n");
            if ( indiceUsuario >= 0 )
            {
                pUsuario=listaUsuarios->get(listaUsuarios, indiceUsuario);
                printf("\n Datos del usuario a eliminar: \n");
                printUsuario(pUsuario, ALL);
                printf("\n");
                printf(" 1- Cancelar \n");
                printf(" 2- Eliminar definitivamente datos del Usuario \n");
                if ( pUsuario->flagRegistro != DELETED )
                    printf(" 3- Inhabilitar Usuario \n");
                else
                    opcionMaxima=2;
                getInt(&opcion,"\n Ingrese una opcion: ","\n\n La opcion ingresada es incorrecta! Debe elegir una opcion de la lista. \n",1,1,1,1,opcionMaxima);
                switch(opcion)
                {
                    case 1:
                        printf("\n La baja del usuario ha sido cancelada! \n");
                        break;
                    case 2:
                        listaUsuarios->remove(listaUsuarios, indiceUsuario);
                        printf("\n El usuario ha sido eliminado definitivamente en forma exitosa \n");
                        retorno=0;
                        break;
                    case 3:
                        pUsuario->flagRegistro = DELETED;
                        retorno=0;
                        printf("\n El usuario ha sido inhabilitado exitosamente \n");
                        break;
                }

            }
        }
    }
    return retorno;
}





/**
 * @brief pide al operador el id del usuario y comprueba que exista.
 * @param listaUsuarios el array se pasa como parametro.
 * @param leyendaCancelar Se le pasa la leyenda a mostrar en caso de desistir del ingreso
 * @return devuelve -1 si se desistio de la carga, -2 si el tamaño del array es invalido o un puntero NULO, de lo contrario devuelve el indice del idUsuario en listaUsuarios.
 */
int tomarYcomprobarExistenciaUsuarioPorId(ArrayList* listaUsuarios, char* leyendaCancelar)
{
    int retorno=-2;
    int idUsuario=0;
    int i;
    Usuario* pUsuario = malloc(sizeof(Usuario));

    if ( listaUsuarios == NULL || pUsuario == NULL )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else
        while(retorno<-1)
        {
            getInt(&idUsuario, "\n Ingrese el id del usuario (0 para cancelar): ", "\n El dato ingresado es invalido!\
                \n El id debe ser un numero positvo entre 0 y 31999",1,1,0,1,31999);
            if (idUsuario==0)
            {
                printf("%s",leyendaCancelar);
                retorno=-1;
            }
            else
            {
                for (i=0; i<listaUsuarios->size; i++)
                {
                    pUsuario = listaUsuarios->get(listaUsuarios, i);
                    if ( pUsuario->id == idUsuario )
                    {
                        retorno = i;
                        break;
                    }
                }
                if ( retorno < 0 )
                    printf("\n El nro. de id del usuario NO se encuentra ingresado! Reingrese \n");
            }
        }
    return retorno;
}


/**
 * \brief Realiza la modificacion de datos de un usuario
 * \param listaUsuarios se le pasa como parametro
 * \return devuelve -1 si Tamaño invalido o puntero NULL pointer o sin espacio disponible - (0) si la modificacion se pudo realizar.
 */
int modificarUsuarioPorId(ArrayList* listaUsuarios)
{
    int retorno = -1;
    char opcion='s';
    int indiceUsuario=-1;
    Usuario* pUsuario = malloc(sizeof(Usuario));

    if ( listaUsuarios == NULL || pUsuario == NULL )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else
    {
        if ( listaUsuarios->size == 0 )
            printf("\n No se puede modificar un usuario porque no hay ninguno cargado! \n");
        else
        {
            indiceUsuario=tomarYcomprobarExistenciaUsuarioPorId(listaUsuarios, "\n La baja del usuario ha sido cancelada! \n");
            if ( indiceUsuario >= 0 )
            {
                pUsuario=listaUsuarios->get(listaUsuarios, indiceUsuario);
                printf("\n Datos del usuario a modificar: \n");
                printUsuario(pUsuario, ALL);
                if ( pUsuario->flagRegistro == DELETED )
                {
                    printf("\n El usuario se encuentra inhabilitado. Desea continuar? (s/n): ");
                    scanf("%c",&opcion);
                }

                if( opcion=='s' || opcion=='S' )
                {
                    cargaNombreUsuario(pUsuario->nombre);
                    cargaPasswordUsuario(pUsuario->password);
                    retorno=0;
                }
                else
                    printf("\n La modificacion del usuario ha sido cancelada! \n");
            }
        }
    }
    return retorno;
}
