#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct{
    // int id;
    char titulo[20];
    char genero[20];
    char duracion[4];
    char descripcion[50];
    char puntaje[2];
    char linkImagen[50];
    // int flagRegistro;
}EMovie;

EMovie ingresoDatosPelicula(char* titulo);

void ingresoTitulo(char* titulo);

int agregarPelicula();

void listarDatosPelicula(EMovie movie);

EMovie* cargarPeliculasEnArray(int* cantPeliculas);

int tomarTituloYchequearExistencia(char titulo[], int alta);

int contarPeliculasEnArchivo();

void listarPeliculas();

int modificarPelicula();

int borrarPelicula();

/**
 *  Borra una pelicula del archivo binario
 *  @param movie la estructura a ser eliminada al archivo
 *  @return retorna 1 o 0 de acuerdo a si pudo eliminar la pelicula o no
 */
//int borrarPelicula(EMovie movie);

/**
 *  Genera un archivo html a partir de las peliculas cargadas en el archivo binario.
 *  @param lista la lista de peliculas a ser agregadas en el archivo.
 *  @param nombre el nombre para el archivo.
 */
void generarPagina(EMovie lista[], char nombre[]);

#endif // FUNCIONES_H_INCLUDED
