#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "funcionesAuxiliares.h"
#include "Usuarios.h"
#include "Publicaciones.h"
#include "Productos.h"
#include "Informes.h"


#define EL_DATO_ES_VALIDO 1
#define EL_DATO_NO_ES_VALIDO 0

#define EMPTY 0
#define USED 1
#define DELETED 2

#define TRUE 1
#define FALSE 0

/**
 * @brief Realiza la inicializacion del arrayProductos ingresando el valor EMPTY en el campo flagRegistro.
 * @param array el array se pasa como parametro.
 * @param sizeArrayProductos el tamaño del array se pasa como parametro.
 * @return devuelve 1 si se pudo inicializar el array (o 0 si no se pudo porque se paso un tamaño del array invalido o un puntero NULO)
 */
int initArrayProductos(EProducto* arrayProductos, int sizeArrayProductos)
{
    int i;
    int retorno=0;
    if ( arrayProductos==NULL || sizeArrayProductos<=0 )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else
    {
        for (i=0; i<sizeArrayProductos; i++)
        {
            arrayProductos[i].flagRegistro=EMPTY;
            arrayProductos[i].id=0;
        }
        retorno=1;
    }
    return retorno;
}


/**
 * @brief Obtiene el primer indice libre del array.
 * @param arrayProductos el array se pasa como parametro.
 * @param sizeArrayProductos el tamaño del array se pasa como parametro.
 * @return devuelve el primer indice disponible (o -1 si no exite ninguno disponible o si el tamaño del array es invalido o un puntero NULO)
 */
int obtenerPosicionLibreArrayProductos(EProducto* arrayProductos, int sizeArrayProductos)
{
    int i;
    if ( arrayProductos==NULL || sizeArrayProductos<=0 )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else
    {
        for (i=0; i<sizeArrayProductos; i++)
            if (arrayProductos[i].flagRegistro==EMPTY)
                return i;
        printf("\n No se puede agregar Producto porque se agoto el espacio disponible! \n");
    }
    return -1;
}


/**
 * @brief busca si se encuentra cargado un id de Producto.
 * @param arrayProductos el array se pasa como parametro.
 * @param sizeArrayProductos el tamaño del array se pasa como parametro.
 * @param idProducto se pasa como como parametro.
 * @return devuelve el indice en que esta guardado los datos de ese Producto (o -1 si no exite o si el tamaño del array es invalido o un puntero NULO)
 */
int buscarProductoPorId(EProducto* arrayProductos, int sizeArrayProductos, int idProducto)
{
    int i;
    if ( arrayProductos==NULL && sizeArrayProductos<=0 )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else
        for (i=0; i<sizeArrayProductos; i++)
            if (arrayProductos[i].flagRegistro==USED && arrayProductos[i].id==idProducto)
                return i;
    return -1;
}


/**
 * \brief Realiza el ingresdo de datos de una Producto
 * \param arrayProductos se le pasa como parametro el array-estructura donde se van a cargar los datos
 * \param sizeArrayProductos es el tamaño del array-estructura donde se van a guardar los datos
 * \param arrayUsuarios se le pasa como parametro el array-estructura de usuarios para validar su existencia
 * \param sizeArrayUsuarios es el tamaño del array-estructura usuarios
 * \return devuelve (0) si Tamaño invalido o puntero NULL pointer o sin espacio disponible - (1) si la carga se pudo realizar.
 */
int nuevaPublicacion(EProducto* arrayProductos, int sizeArrayProductos, EUsuario* arrayUsuarios, int sizeArrayUsuarios)
{
    EProducto arrayAuxiliarProducto[1]; /// es el array-estructura donde se van a guardar provisoriamente los datos
    int retorno=0;
    int indice = obtenerPosicionLibreArrayProductos(arrayProductos,sizeArrayProductos);
    int existeUsuario=-1;

    if ( existenUsuarios(arrayUsuarios, sizeArrayUsuarios)==0 )
        printf("\n No se pueden cargar Productos porque no existe ningun usuario cargado! \n");
    else if (indice!=-1)
    {
        arrayAuxiliarProducto[0].id=calcularIdProducto(arrayProductos,sizeArrayProductos);
        printf("\n El nro de id para el Producto a cargar es: %d \n",arrayAuxiliarProducto[0].id);
        while(existeUsuario==-1)
        {
            arrayAuxiliarProducto[0].idUsuario=ingresoIdUsuario();
            existeUsuario=buscarUsuarioPorId(arrayUsuarios,sizeArrayUsuarios,arrayAuxiliarProducto[0].idUsuario);
            if (existeUsuario==-1)
                printf("\n El id de usuario ingresado no se encuentra cargado! \n ");
        }

        cargaNombreProducto(arrayAuxiliarProducto);
        arrayAuxiliarProducto[0].precio=ingresoPrecioProducto();
        arrayAuxiliarProducto[0].stock=ingresoStockProducto();
        arrayAuxiliarProducto[0].cantidadVendida=0;
        arrayAuxiliarProducto[0].isPublished=TRUE;
        arrayAuxiliarProducto[0].flagRegistro=USED;

        arrayProductos[indice]=arrayAuxiliarProducto[0];
        retorno=1;
        printf("\n El Producto ha sido cargado correctamente. \n");
    }
    return retorno;
}


/**
 * \brief Realiza la modificacion de datos de un Producto
 * \param arrayProductos se le pasa como parametro el array-estructura donde se van a modificar los datos
 * \param sizeArrayProductos es el tamaño del array-estructura donde se van a guardar los datos
 * \return devuelve (0) si Tamaño invalido o puntero NULL pointer o si no se encuentra el Producto - (1) si la modificacion se pudo realizar.
 */
int modificarProductoPorIdUsuario(EProducto* arrayProductos, int sizeArrayProductos, EUsuario* arrayUsuarios, int sizeArrayUsuarios)
{
    EProducto arrayAuxiliarProducto[1];  /// es el array-estructura donde se van a guardar provisoriamente los datos
    int retorno=0;
    int existeProducto;
    int existeUsuario;
    int sigue=TRUE;
    char salir='n';

    if ( existenProductosPublicados(arrayProductos, sizeArrayProductos)==0 )
    {
        printf("\n No se pueden modificar datos de Productos porque no hay ninguno cargado! \n");
        salir='s';
    }
    while (salir!='s' && salir!='S')
    {
        while(sigue==TRUE)
        {
            existeUsuario=ingresoIdUsuario();
            if ( buscarUsuarioPorId(arrayUsuarios, sizeArrayUsuarios, existeUsuario) != -1)
            {
                printf("\n El nro. de id del usuario NO se encuentra ingresado! Reingrese \n");
                sigue=FALSE;
            }
        }
        arrayAuxiliarProducto[0].idUsuario=existeUsuario;

        listarProductosUsuario(arrayProductos,sizeArrayProductos,existeUsuario);

        arrayAuxiliarProducto[0].id=ingresoIdProducto();
        existeProducto=buscarProductoPorId(arrayProductos,sizeArrayProductos,arrayAuxiliarProducto[0].id);
        if(existeProducto>=0)
        {
            cargaNombreProducto(arrayAuxiliarProducto);
            arrayAuxiliarProducto[0].precio=ingresoPrecioProducto();
            arrayAuxiliarProducto[0].stock=ingresoStockProducto();
            arrayAuxiliarProducto[0].cantidadVendida=ingresoCantidadVendidaProducto(arrayAuxiliarProducto[0].stock);
            arrayAuxiliarProducto[0].isPublished=TRUE;
            arrayAuxiliarProducto[0].flagRegistro=USED;

            arrayProductos[existeProducto]=arrayAuxiliarProducto[0];
            break;
        }
        else
            getString("\n El nro. de id del Producto NO se encuentra ingresado! \
                \n Ingrese 'S' para salir de la carga de datos o cualquier otra tecla para continuar: ",&salir);
    }
    return retorno;
}


/**
 * @brief pide al usuario los datos de nombre del producto y los carga (validados) en un array auxiliar recibido como parametro.
 * @param arrayAuxiliar el array se pasa como parametro.
 * @return no devuelve nada.
 */
void cargaNombreProducto(EProducto* arrayAuxiliarProducto)
{
    char arrayCharsAdmitidos[1]=" ";
    getType("\n Ingrese el nombre del producto: ", "\n El dato ingresado es invalido!\
        \n Solo se adminten letras, numeros, espacios y que no exceda los 49 caracteres \n",1,2,arrayCharsAdmitidos,49,arrayAuxiliarProducto[0].nombre);

}


/**
 * @brief pide al usuario el id de el Producto y lo devuelve validado dentro de un rango de enteros.
 * @param no recibe parametros.
 * @return el id validado como int.
 */
int ingresoIdProducto()
{
    int idProducto;
    getInt(&idProducto, "\n Ingrese el id de el Producto: ", "\n El dato ingresado es invalido!\
        \n El numero de Producto debe ser un numero positvo entre 1 y 31999",1,1,1,1,31999);
    return idProducto;
}


/**
 * @brief pide al usuario el precio de el Producto y lo devuelve validado dentro de un rango de flotantes.
 * @param no recibe parametros.
 * @return el id validado como float.
 */
float ingresoPrecioProducto()
{
    float precio;
    getFloat(&precio, "\n Ingrese el precio del Producto: ", "\n El dato ingresado es invalido!\
        \n El precio de Producto debe ser un numero positvo entre 1 y 31999",1,1,1,1,31999);
    return precio;
}

/**
 * @brief pide al usuario la cantidad vendida del Producto y lo devuelve validado dentro de un rango de enteros.
 * @param no recibe parametros.
 * @return el id validado como int.
 */
int ingresoCantidadVendidaProducto(int stock)
{
    int cantidadVendida=0;
    do
    {
        getInt(&cantidadVendida, "\n Ingrese la cantidad vendida del Producto: ", "\n El dato ingresado es invalido!\
            \n El precio de Producto debe ser un numero positvo entre 1 y 31999",1,1,1,1,31999);

    }while(cantidadVendida<=stock);
    return cantidadVendida;
}

/**
 * @brief pide al usuario el stock del Producto y lo devuelve validado dentro de un rango de enteros.
 * @param no recibe parametros.
 * @return el id validado como int.
 */
int ingresoStockProducto()
{
    float stock;
    getInt(&stock, "\n Ingrese el precio del Producto: ", "\n El dato ingresado es invalido!\
        \n El precio de Producto debe ser un numero positvo entre 1 y 31999",1,1,1,1,31999);
    return stock;
}


/**
 * @brief cacula el proximo numero de id de Producto en una secuencia autoincrementable.
 * @param arrayProductos el array se pasa como parametro.
 * @param sizeArrayProductos el tamaño del array se pasa como parametro.
 * @return devuelve el proximo id (o -1 si no exite ninguno disponible o si el tamaño del array es invalido o un puntero NULO)
 */
int calcularIdProducto(EProducto* arrayProductos, int sizeArrayProductos)
{
    int nextIdProducto=0;
    int i;
    if ( arrayProductos==NULL || sizeArrayProductos<=0 )
        printf("\n La ejecucion se detendrá! Tamaño de array invalido o puntero NULO \n");
    else
        for (i=0; i<sizeArrayProductos; i++)
            if ( i==0 || ( arrayProductos[i].flagRegistro==USED && arrayProductos[i].id>=nextIdProducto ) )
                nextIdProducto=arrayProductos[i].id+1;
    return nextIdProducto;
}


/**
 * @brief cacula si el array de Productos no está vacio
 * @param arrayProductos el array se pasa como parametro.
 * @param sizeArrayProductos el tamaño del array se pasa como parametro.
 * @return devuelve 0 si no exite ninguna Producto cargada o si el tamaño del array es invalido o un puntero NULO), de lo contrario devuelve 1.
 */
int existenProductosPublicados(EProducto* arrayProductos, int sizeArrayProductos)
{
    int i;
    if ( arrayProductos==NULL || sizeArrayProductos<=0 )
        printf("\n La ejecucion se detendra! Tamaño de array invalido o puntero NULO \n");
    else
        for (i=0; i<sizeArrayProductos; i++)
            if ( arrayProductos[i].flagRegistro==USED && arrayProductos[i].isPublished==TRUE )
                return 1;
    return 0;
}


/**
 * @brief realiza una baja logica de todas las Productos de un usuario que fue dado de baja.
 * @param arrayProductos el array se pasa como parametro.
 * @param sizeArrayProductos el tamaño del array se pasa como parametro.
 * @return devuelve 0 si no exite ninguna Producto para ese usuario o si el tamaño del array es invalido o un puntero NULO, de lo contrario devuelve 1.
 */
int eliminarProductosPorBajaUsuario(EProducto* arrayProductos, int sizeArrayProductos, int idUsuario)
{
    int retorno=0;
    int i;
    if ( arrayProductos==NULL || sizeArrayProductos<=0 )
        printf("\n La ejecucion se detendra! Tamaño de array invalido o puntero NULO \n");
    else
        for (i=0; i<sizeArrayProductos; i++)
            if ( arrayProductos[i].idUsuario==idUsuario && arrayProductos[i].flagRegistro==USED )
            {
                arrayProductos[i].flagRegistro=DELETED;
                arrayProductos[i].isPublished=FALSE;
                retorno=1;
            }
    return retorno;
}



/**
 * @brief muetra por pantalla un listado con los Productos.
 * @param arrayProductos el array se pasa como parametro.
 * @param idUsuario se pasa como parametro.
 * @param sizeArrayProductos el tamaño del array se pasa como parametro.
 * @return no devuelve nada.
 */
void listarProductosUsuario(EProducto* arrayProductos, int sizeArrayProductos, int idUsuario)
{
    int i;
    for (i=0; i<sizeArrayProductos; i++)
        if (arrayProductos[i].flagRegistro!=EMPTY && arrayProductos[i].isPublished==TRUE && arrayProductos[i].idUsuario==idUsuario)
            printf("\n Id %d - idUsuario %d - Precio: %.2f - Stock: %d - Cantidad Vendida: %d - FlagRegistro %d\
                   ", arrayProductos[i].id, arrayProductos[i].idUsuario, arrayProductos[i].precio, arrayProductos[i].stock-arrayProductos[i].cantidadVendida, arrayProductos[i].cantidadVendida, arrayProductos[i].flagRegistro);
    printf("\n");
}


/*

void cargaAutomaticaLlamadas(EProducto* arrayProductos, int sizeArrayProductos, EUsuario* arrayUsuarios)
{
    arrayProductos[0].id=1;
    arrayProductos[0].idUsuario=1;
    arrayUsuarios[0].contadorLlamadas++;
    arrayProductos[0].motivo=FALLA_3G;
    arrayProductos[0].estado=EN_CURSO;
    arrayProductos[0].tiempo=0;
    arrayProductos[0].flagRegistro=USED;

    arrayProductos[1].id=2;
    arrayProductos[1].idUsuario=2;
    arrayUsuarios[1].contadorLlamadas++;
    arrayProductos[1].motivo=FALLA_EQUIPO;
    arrayProductos[1].estado=EN_CURSO;
    arrayProductos[1].tiempo=0;
    arrayProductos[1].flagRegistro=USED;

    arrayProductos[2].id=3;
    arrayProductos[2].idUsuario=2;
    arrayUsuarios[1].contadorLlamadas++;
    arrayProductos[2].motivo=FALLA_EQUIPO;
    arrayProductos[2].estado=EN_CURSO;
    arrayProductos[2].tiempo=0;
    arrayProductos[2].flagRegistro=USED;

    arrayProductos[3].id=4;
    arrayProductos[3].idUsuario=3;
    arrayUsuarios[2].contadorLlamadas++;
    arrayProductos[3].motivo=FALLA_LTE;
    arrayProductos[3].estado=SOLUCIONADO;
    arrayProductos[3].tiempo=15;
    arrayProductos[3].flagRegistro=USED;

}

*/

