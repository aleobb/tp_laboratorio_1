#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funciones.h"
#include "funcArchivos.h"
#include "funcionesAuxiliares.h"


#define TRUE 1
#define FALSE 0
#define DELETE 2

#define ARCHIVO "Peliculas.bin" // Para cadena con comillas usar: \"


/**
 * \brief Realiza el ingreso de datos de una pelicula
 * \param la cadena del campo titulo se le pasa como parametro
 * \return devuelve (0) si Tamaño invalido o puntero NULL pointer o sin espacio disponible - (1) si la carga se pudo realizar.
 */
EMovie ingresoDatosPelicula(char* titulo)
{
    EMovie auxPelicula; /// es la variable donde se van a guardar provisoriamente los datos
    char arrayCharsAdmitidos[20]="-";

    strcpy(auxPelicula.titulo, titulo);
    getType("\n Ingrese el genero: ", "\n El dato ingresado es invalido!\n Solo se adminten letras, numeros,\
el caracter '-' y que no exceda los 19 caracteres \n",1,2,arrayCharsAdmitidos,19,auxPelicula.genero);
    getType("\n Ingrese la descripcion: ", "\n El dato ingresado es invalido!\n Solo se adminten letras, numeros,\
el caracter '-' y que no exceda los 49 caracteres \n",1,2,arrayCharsAdmitidos,49,auxPelicula.descripcion);
    strcpy(arrayCharsAdmitidos,"0");
    getType("\n Ingrese la duracion de la pelicula en minutos: ", "\n El dato ingresado es invalido!\n \
La duracion debe ser un numero positvo entre 1 y 999 \n",1,3,arrayCharsAdmitidos,3,auxPelicula.duracion);
    //getInt(&auxPelicula.duracion, "\n Ingrese la duracion de la pelicula en minutos: ", "\n El dato ingresado es invalido!\n La duracion debe ser un numero positvo entre 1 y 500",1,1,1,1,500);
    getType("\n Ingrese el puntaje de la pelicula del 1 al 10: ", "\n El dato ingresado es invalido!\n \
La duracion debe ser un numero positvo entre 1 y 9 \n",1,3,arrayCharsAdmitidos,1,auxPelicula.puntaje);
    //getInt(&auxPelicula.puntaje, "\n Ingrese el puntaje de la pelicula del 1 al 10: ", "\n El dato ingresado es invalido!\n El puntaje debe ser un numero positvo entre 1 y 10",1,1,1,1,10);

    strcpy(arrayCharsAdmitidos,"-./+_@,:");
    getType("\n Ingrese el link de la Imagen: ", "\n El dato ingresado es invalido!\n Solo se adminten letras, numeros,\
el caracter '-' y que no exceda los 49 caracteres \n",1,2,arrayCharsAdmitidos,49,auxPelicula.linkImagen);

    return auxPelicula;
}


/**
 * \brief Pide al usuario el ingreso del titulo de una pelicula
 * \param no recibe parametros
 * \return no devuelve nada.
 */
void ingresoTitulo(char* titulo)
{
    char arrayCharsAdmitidos[]="-";
    getType("\n Ingrese el titulo: ", "\n El dato ingresado es invalido!\n Solo se adminten letras, numeros,\
             el caracter '-' y que no exceda los 19 caracteres \n",1,2,arrayCharsAdmitidos,19,titulo);
    // printf("\n %s",titulo);
}


/**
 *  \brief Agrega una pelicula al archivo binario
 *  \param no recibe parametros
 *  \return retorna 0 si se pudo agregar correctamente o -2 si no se pudo grabar y -1 si se pudo grabar pero no cerrar el archivo
 */
int agregarPelicula()
{
    FILE* pArchivo=NULL;
    int retorno=-2;
    char titulo[20];

    int posPelicula=tomarTituloYchequearExistencia(titulo, TRUE);

    if ( posPelicula == -3 )
        printf("\n El ingreso ha sido cancelado. \n");
    else if( posPelicula != -1 )
    {
        EMovie movie = ingresoDatosPelicula(titulo);
        // listarDatosPelicula(movie);
        pArchivo = fopen(ARCHIVO,"ab"); // if ( abrirArchBinModoAppend(pArchivo,ARCHIVO) == 0 )
        if (pArchivo!=NULL)
        {
            // printf("pArchivo abierto correctamente \n");
            if ( fwrite(&movie,sizeof(EMovie),1,pArchivo) == 1 )
            {
                printf("\n La pelicula fue agregada en el archivo correctamente \n");
                retorno=cerrarArch(pArchivo);
            }
            else
                printf("\n Error de escritura en el archivo \"%s\"! La pelicula NO pudo ser agregada. \n", ARCHIVO);
        }
        else
            printf("\n El archivo \"%s\" NO pudo ser abierto en modo escritura! La carga de la pelicula fue cancelada. \n", ARCHIVO);
    }
    return retorno;
}


/**
 *  \brief Modificar una pelicula al archivo binario
 *  \param no recibe parametros
 *  \return retorna 0 si se pudo modificar correctamente o -2 si no se pudo grabar y -1 si se pudo grabar pero no cerrar el archivo
 */
int modificarPelicula()
{
    FILE* pArchivo=NULL;
    int retorno=-2;
    char titulo[20];

    printf("\n INGRESE LOS DATOS DE LA PELICULA A MODIFICAR: \n ---------------------------------------------");
    int posPelicula=tomarTituloYchequearExistencia(titulo, FALSE);

    if ( posPelicula == -3 )
        printf("\n El ingreso ha sido cancelado. \n");
    else
        printf("\n INGRESE LOS DATOS NUEVOS DE LA PELICULA: \n ----------------------------------------");
    if( posPelicula >= 0 && tomarTituloYchequearExistencia(titulo, TRUE) == 0 )
    {
        EMovie movie = ingresoDatosPelicula(titulo);
        // listarDatosPelicula(movie);
        pArchivo = fopen(ARCHIVO,"rb"); // if ( abrirArchBinModoAppend(pArchivo,ARCHIVO) == 0 )

        if( ( pArchivo = fopen(ARCHIVO,"r+b") ) == NULL )
            if( ( pArchivo = fopen(ARCHIVO,"wb") ) == NULL )
                printf("\n El archivo \"%s\" NO pudo ser abierto en modo escritura! La carga de la pelicula fue cancelada. \n", ARCHIVO);

        if (pArchivo!=NULL) // printf("pArchivo abierto correctamente \n");
        {
            //rewind (FILE* pArchivo);
            fseek (pArchivo, posPelicula*sizeof(EMovie), SEEK_SET);

            if ( fwrite(&movie,sizeof(EMovie),1,pArchivo) == 1 )
            {
                printf("\n La pelicula fue modificada en el archivo correctamente \n");
                retorno=cerrarArch(pArchivo);
            }
            else
                printf("\n Error de escritura en el archivo \"%s\"! La pelicula NO pudo ser modificada. \n", ARCHIVO);
        }
    }

    return retorno;
}


/**
 *  \brief Eliminar una pelicula del archivo binario
 *  \param no recibe parametros
 *  \return retorna 0 si se pudo modificar correctamente o -2 si no se pudo grabar y -1 si se pudo grabar pero no cerrar el archivo
 */
int borrarPelicula()
{
    FILE* pArchivo=NULL;
    int retorno=-2;
    char titulo[20];
    char confirm='n';
    int i;

    printf("\n INGRESE LOS DATOS DE LA PELICULA A ELIMINAR: \n ---------------------------------------------");
    int posPelicula=tomarTituloYchequearExistencia(titulo, FALSE);
    if ( posPelicula == -3 )
        printf("\n El ingreso ha sido cancelado. \n");
    else if( posPelicula >= 0 )
    {
        printf("\n Confirma que desea eliminar la pelicula \"%s\" y todos sus datos? (s/n): ",titulo);
        scanf("%c",&confirm);
        if (confirm!='s' && confirm!='S')
        {
            printf("\n Operacion cancelada! La pelicula no ha sido eliminada");
            retorno=0;
        }
        else
        {
            int sizeArrayPeliculas;
            EMovie* arrayPeliculas=cargarPeliculasEnArray(&sizeArrayPeliculas);
            if ( arrayPeliculas==NULL || sizeArrayPeliculas<=0 )
                printf("\n El archivo que contiene las peliculas a listar NO se pudo abrir o no se pudo leer. \n");
            else
            {
                pArchivo = fopen(ARCHIVO,"wb");
                if (pArchivo!=NULL)
                {
                    // printf("pArchivo abierto correctamente \n");
                    //printf("\n Pelicula a borrar: %s ", arrayPeliculas[posPelicula].titulo);
                    *(arrayPeliculas+posPelicula)=*(arrayPeliculas+sizeArrayPeliculas-1);
                    //rewind (pArchivo);
                    //printf("\n sizeArrayPeliculas: %d",sizeArrayPeliculas);
                    //if ( fwrite(arrayPeliculas,sizeof(EMovie)*(sizeArrayPeliculas-1),sizeArrayPeliculas-1,pArchivo) == (sizeArrayPeliculas-1) )
                    //    printf("\n La pelicula fue borrada del archivo satisfactoriamente \n");
                    for (i=0; i<sizeArrayPeliculas-1; i++)
                        fwrite(arrayPeliculas+i,sizeof(EMovie),1,pArchivo);
                    //else
                    //    printf("\n Error de escritura en el archivo \"%s\"! La pelicula NO pudo ser borrada. \n", ARCHIVO);
                    retorno=cerrarArch(pArchivo);
                }
                else
                     printf("\n Error de escritura en el archivo \"%s\"! La pelicula NO pudo ser borrada. \n", ARCHIVO);
                free(arrayPeliculas);
            }
        }
    }
    return retorno;
}

/**
 * \brief Lista por pantalla los datos de una pelicula
 * \param la variable que contiene los datos de la pelicula del tipo EMovie se le pasa como parametro
 * \return no devuelve nada.
 */
void listarDatosPelicula(EMovie movie)
{
    printf("\n Titulo: \t %s",movie.titulo);
    printf("\n Genero: \t %s",movie.genero);
    printf("\n Duracion: \t %s",movie.duracion);
    printf("\n Descripcion: \t %s",movie.descripcion);
    printf("\n Puntaje: \t %s",movie.puntaje);
    printf("\n Link Imagen: \t %s",movie.linkImagen);
    printf("\n");
}


/**
 * \brief Lista por pantalla los datos de una pelicula
 * \param no se le pasan parametros
 * \return no devuelve nada.
 */
void listarPeliculas()
{
    int i;
    int sizeArrayPeliculas;
    EMovie* arrayPeliculas=cargarPeliculasEnArray(&sizeArrayPeliculas);

    if ( sizeArrayPeliculas==0 )
        printf("\n No hay ninguna pelicula cargada en el archivo! \n");
    else if ( arrayPeliculas==NULL || sizeArrayPeliculas<0 )
        printf("\n El archivo que contiene las peliculas a listar NO se pudo abrir. \n");
    else
    {
        for (i=0; i<sizeArrayPeliculas; i++)
            listarDatosPelicula( arrayPeliculas[i] );
        free(arrayPeliculas);
    }
}


/**
 * \brief busca una pelicula por su titulo en una array cargado en memoria con los datos del archivo donde se almacenan
 * \param titulo: se le pasa como parametro un puntero a una cadena de caracteres donde se va a guardar el titulo de la pelicula
 * \param alta: se pasa 1 para el alta de una nueva pelicula o 0 para modificar o borrar
 * \return retorna 0 o el indice del array si se pudo realizar la operacion, -3 si se canceló el ingreso -2 si no se pudo abrir el archivo o -1 si no se lo encontró o no se pudo abrir el archivo.
 */
int tomarTituloYchequearExistencia(char titulo[], int alta)  /// **************   DEVOLVER INDICE O EL PUNTERO AL ARRAY ?!?!?!? ******************
{
    int retorno=-1;
    int i;
    int flag=0;
    char seguir='s';
    char arrayCharsAdmitidos[]="-";
    int sizeArrayPeliculas;
    EMovie* arrayPeliculas=cargarPeliculasEnArray(&sizeArrayPeliculas);

    if ( sizeArrayPeliculas<0 && alta!=TRUE )
        printf("\n El archivo que contiene las peliculas NO se pudo abrir, y por tanto no se puede verificar la existencia del titulo a ingresar. \n");
    else if ( alta==FALSE && sizeArrayPeliculas==0 )
        printf("\n La opcion seleccionada no se puede ejecutar porque no hay peliculas guardadas en el archivo \n");
    else
    {
        while (retorno<0)
        {

            if (flag>3)
                printf("\n Se supero la cantidad de intentos! \n");
            else if (flag>0)
            {
                printf("\n Reintenta? (s/n): ");
                scanf("%c",&seguir);
            }
            if ( (seguir=='n' || seguir=='N') || flag>3 )
            {
                retorno=-3;
                break;
            }
            getType("\n Ingrese el titulo: ", "\n El dato ingresado es invalido!\n Solo se adminten letras, numeros,\
                     el caracter '-' y que no exceda los 19 caracteres \n",1,2,arrayCharsAdmitidos,19,titulo);
            // printf("\n %s",titulo);
            //if ( arrayPeliculas==NULL && alta!=TRUE)
            //    printf("\n La ejecucion se detendra! Error Puntero NULO.");
            for (i=0; i<sizeArrayPeliculas && arrayPeliculas!=NULL; i++)
                if( strcmp(arrayPeliculas[i].titulo,titulo)==0 )
                {
                    retorno=i;
                    break;
                }
            if (alta==TRUE && retorno>=0)
            {
                printf("\n El titulo ingresado ya se encuentra cargado en el archivo! Reintente. \n");
                retorno=-1;
            }
            else if (alta==TRUE) /// si se está dando de alta una pelicula (y no se encontró un titulo que coincida con el recien ingresado) cambio el valor de retorno para cortar el while
                retorno=0;
            else if (alta==FALSE && retorno<0)
                printf("\n El titulo ingresado no coincide con ninguno guardado en el archivo! Reintente. \n");
            flag++;
        }
        free(arrayPeliculas);
    }
    //printf("\n indice: %d",retorno);
    return retorno;
}


/**
 * \brief Carga los datos de las peliculas en un array
 * \param se le pasa la cantidad de peliculas que va a leer del archivo
 * \return EMovie* Retorna un puntero al array de peliculas (con todos sus datos) o NULL en caso de error
 */
EMovie* cargarPeliculasEnArray(int* cantPeliculas)
{
    FILE* pArchivo=NULL;
    EMovie* pPeliculas=NULL;
    *cantPeliculas=contarPeliculasEnArchivo();

    if ( (*cantPeliculas) > 0 )
    {
        pPeliculas = (EMovie*)malloc(sizeof(EMovie)*(*cantPeliculas)); /// Creo un array para la cantidad de peliculas guardadas en el archivo
        if( pPeliculas == NULL )
            printf("\n La ejecucion se detendra! No se pudo asignar espacio en memoria para realizar esta operacion. \n");
        else
        {
            pArchivo = fopen(ARCHIVO,"rb"); ///  Abrirlo como solo lectura
            //if ( pArchivo == NULL )
            //    printf("\n El archivo %s no pudo ser abierto! La ejecucion se detendra. \n", ARCHIVO);
            if ( pArchivo != NULL )
            {
                fread( pPeliculas, sizeof(EMovie), (*cantPeliculas), pArchivo );
                cerrarArch(pArchivo);
            }
        }
    }
    //else if  ( (*cantPeliculas) == 0 )
    //    printf("\n La opcion seleccionada no se puede ejecutar porque no hay peliculas guardadas en el archivo \n");
    return pPeliculas;
}


/**
 * \brief obtiene la cantidad de peliculas guardadas en el archivo
 * \param no recibe parametros
 * \return retorna la cantidad peliculas guardadas en el archivo o -1 en caso de error
 */
int contarPeliculasEnArchivo()
{
    int retorno=-1;
    FILE* pArchivo=NULL;
    pArchivo = fopen(ARCHIVO,"rb"); ///  Abrirlo como solo lectura

    //if ( pArchivo == NULL )
    //    printf("\n El archivo %s no pudo ser abierto! La ejecucion se detendra. \n", ARCHIVO);
    //else
    if ( pArchivo != NULL )
    {
        fseek(pArchivo, 0, SEEK_END);
        retorno= ( ftell(pArchivo)/sizeof(EMovie) );
        cerrarArch(pArchivo);
    }
    //printf("\n cant pelis: %d", retorno);
    return retorno;
}


///int borrarPelicula(EMovie movie)

///void generarPagina(EMovie* lista[], char nombre[])


