#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//#include <io.h>
#include <fcntl.h>


#include "funciones.h"
#include "funcArchivos.h"
#include "funcionesAuxiliares.h"

#define ARCHIVO "Peliculas.bin"
#define HTMLFILE "index.html"

#define LINK "\n<article class='col-md-4 article-intro'>\n<a href='#'>\n<img class='img-responsive img-rounded' src='"
#define TITULO "\'nalt=''>\n </a>\n <h3>\n <a href='#'>"
#define GENERO "</a>\n </h3>\n<ul>\n<li>Género:"
#define PUNTAJE "</li>\n<li>Puntaje:"
#define DURACION "</li>\n<li>Duración:"
#define DESCRIPCION "</li>\n</ul>\n <p>"
#define END "</p>\n</article>"



void imprimirArchivo()
{
    int i;
    FILE* pArchivo=NULL;
    int sizeArrayPeliculas;
    EMovie* arrayPeliculas=cargarPeliculasEnArray(&sizeArrayPeliculas);

    if ( sizeArrayPeliculas==0 )
        printf("\n No hay ninguna pelicula cargada en el archivo! \n");
    else if ( arrayPeliculas==NULL || sizeArrayPeliculas<0 )
        printf("\n El archivo que contiene las peliculas a listar NO se pudo abrir. \n");
    else
    {
        pArchivo = fopen(HTMLFILE,"w");
        if (pArchivo!=NULL)
        {
            for (i=0; i<sizeArrayPeliculas; i++)
            {
                fwrite(LINK,sizeof(char),strlen(LINK),pArchivo);
                fwrite(arrayPeliculas[i].linkImagen,sizeof(char),strlen(arrayPeliculas[i].linkImagen),pArchivo);

                fwrite(TITULO,sizeof(char),strlen(TITULO),pArchivo);
                fwrite(arrayPeliculas[i].titulo,sizeof(char),strlen(arrayPeliculas[i].titulo),pArchivo);

                fwrite(GENERO,sizeof(char),strlen(GENERO),pArchivo);
                fwrite(arrayPeliculas[i].genero,sizeof(char),strlen(arrayPeliculas[i].genero),pArchivo);

                //itoa(arrayPeliculas[i].puntaje,puntaje,10);
                fwrite(PUNTAJE,sizeof(char),strlen(PUNTAJE),pArchivo);
                fwrite(arrayPeliculas[i].puntaje,sizeof(char),strlen(arrayPeliculas[i].puntaje),pArchivo);

                fwrite(DURACION,sizeof(char),strlen(DURACION),pArchivo);
                fwrite(arrayPeliculas[i].duracion,sizeof(char),strlen(arrayPeliculas[i].duracion),pArchivo);
                //fwrite(*itoa(arrayPeliculas[i].duracion),sizeof(int),sizeof(arrayPeliculas[i].duracion)-1,pArchivo);

                fwrite(DESCRIPCION,sizeof(char),strlen(DESCRIPCION),pArchivo);
                fwrite(arrayPeliculas[i].descripcion,sizeof(char),strlen(arrayPeliculas[i].descripcion),pArchivo);

                fwrite(END,sizeof(char),strlen(END),pArchivo);
            }
            printf("\n El archivo HTMLFILE se pudo generar exitosamente! \n");
            free(arrayPeliculas);
            fclose(pArchivo);
        }
        else
            printf("\n Error de escritura del archivo html! El archivo HTMLFILE no se pudo generar. \n");


    }


}





int resizeFile()
{
    FILE* pArchivo = NULL;
    if( ( pArchivo = fopen(ARCHIVO,"r+b") ) == NULL )
        if( ( pArchivo = fopen(ARCHIVO,"wb") ) == NULL )
            printf("\n El archivo \"%s\" NO pudo ser abierto en modo escritura! La carga de la pelicula fue cancelada. \n", ARCHIVO);
    ///  http://programacion.yoreparo.com/programacion/como-borrar-datos-de-un-fichero-en-c--t51582.html
    chsize(1,1);
    return 0;
}


/**
 *  Abre un archivo binario en modo lectura
 *  @param pFile se le pasa el puntero al archivo como parametro
 *  @param paramArch Se le pasa la ubicacion, nombre y extension del archivo
 *  @return retorna 0 si se pudo abrir correctamente o -1 si no se pudo
 */
int abrirArchBinModoLectura(FILE* pFile, char paramArch[])
{
    int retorno=-1;
    pFile = fopen(paramArch,"rb"); ///  Abrirlo como solo lectura
    if (pFile!=NULL)
        retorno=0; /// printf("Archivo abierto correctamente \n");
    else
        printf("\n El archivo %s no pudo ser abierto! \n", paramArch);
    return retorno;
}


/**
 *  Abre un archivo binario en modo lectura escritura
 *  @param pFile se le pasa el puntero al archivo como parametro
 *  @param paramArch Se le pasa la ubicacion, nombre y extension del archivo
 *  @return retorna 0 si se pudo abrir correctamente o -1 si no se pudo
 */
int abrirArchBinModoEscritura(FILE* pFile, char paramArch[])
{
    int retorno=-1;
    if (abrirArchBinModoLectura(pFile,paramArch) == 0 ) ///  Abrirlo como solo lectura
    {
        pFile = fopen(paramArch,"wb"); ///  Abrirlo como lectura escritura
        if (pFile!=NULL)
            retorno=0; /// printf("Archivo abierto correctamente \n");
        else
            printf("\n El archivo %s no puede ser abierto! \n", paramArch);
    }
    return retorno;
}


/**
 *  Abre un archivo binario
 *  @param pFile se le pasa el puntero al archivo como parametro
 *  @param paramArch Se le pasa la ubicacion, nombre y extension del archivo
 *  @return retorna 0 si se pudo abrir correctamente o -1 si no se pudo
 */
int abrirArchBinModoAppend(FILE* pFile, char paramArch[])
{
    int retorno=-1;
    printf("\n paramArch: %s",paramArch);
    printf(" \n comparac %d ", stricmp(paramArch,"\"Peliculas.bin\"") );
    pFile = fopen(paramArch,"ab"); ///  Abrirlo para agregar datos
    if (pFile!=NULL)
        retorno=0; /// printf("Archivo abierto correctamente \n");
    else
        printf("\n El archivo %s no puede ser abierto! \n", paramArch);
    return retorno;
}


/**
 *  Cierra un archivo ya abierto
 *  @param pFile se le pasa el puntero al archivo como parametro
 *  @return retorna 0 si se pudo cerrar correctamente o -1 si no se pudo
 */
int cerrarArch(FILE* pFile)
{
    int retorno=-1;
    if( fclose(pFile) != -1 ) ///  Cerrar archivo
        retorno=0; /// printf("Archivo cerrado correctamente \n");
    else
        printf("\n El archivo no pudo ser cerrado! \n");
    return retorno;
}
