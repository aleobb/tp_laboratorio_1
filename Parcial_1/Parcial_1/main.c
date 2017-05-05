/********************************************************************************************
 *
 * Programa: Venta de Productos
 *
 * Version: 1.0 04 de Mayo de 2017.
 *
 * Autor: Ben Alejandro
 *
 ********************************************************************************************/


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

#define QTYUSUARIO 100
#define QTYPRODUCTO 1000

/* int main()
{
printf("1- Alta del Usuario\n");

return 0;
} */

int main()
{
    EUsuario arrayUsuarios[QTYUSUARIO];
    EProducto arrayProductos[QTYPRODUCTO];

    char seguir='s';
    int opcion=0;


    if ( initArrayUsuarios(arrayUsuarios,QTYUSUARIO)==0 || initArrayProductos(arrayProductos,QTYPRODUCTO)==0 )
        seguir='n';

    /// cargaAutomaticaUsuarios(arrayUsuarios,QTYUSUARIO);
    /// cargaAutomaticaProductos(arrayProductos,QTYPRODUCTO,arrayUsuarios);

    while(seguir=='s')
    {
        /// listarUsuarios(arrayUsuarios,QTYUSUARIO);
        /// listarProductos(arrayProductos,QTYPRODUCTO);

        printf("\n");
        printf("1- Alta de Usuario\n");
        printf("2- Modificar datos del Usuario\n");
        printf("3- Baja del Usuario\n");
        printf("4- Publicar Producto\n");
        printf("5- Modificar Publicacion\n");
        printf("6- Informar nombre y apellido del Usuario con mas reclamos\n");
        printf("7- Informar reclamo mas realizado\n");
        printf("8- Informar reclamo que en promedio mas demora en ser resuelto\n");
        printf("\n");
        printf("9- Salir\n");

        printf("\nIngrese una opcion: ");
        scanf("%d",&opcion);

        switch(opcion)
        {
            case 1:
                altaUsuario(arrayUsuarios,QTYUSUARIO);
                break;
            case 2:
                modificarUsuarioPorId(arrayUsuarios,QTYUSUARIO);
                break;
            case 3:
                bajaUsuarioPorId(arrayUsuarios,QTYUSUARIO,arrayProductos,QTYPRODUCTO);
                break;
            case 4:
                nuevaPublicacion(arrayProductos, QTYPRODUCTO,arrayUsuarios,QTYUSUARIO);
                break;
            case 5:
              ///  modificarLlamadaPorId(arrayProductos,QTYPRODUCTO);
                break;
            case 6:
                /// listarUsuarioConMasMenosReclamos(arrayUsuarios,QTYUSUARIO,1);
                break;
            case 7:
              ///  listarMotivoLlamadaMasRealizado(arrayProductos,QTYPRODUCTO);
                break;
            case 8:
              ///  listarReclamoQueMasDemora(arrayProductos,QTYPRODUCTO);
                break;
            case 9:

                break;
            case 0:
                seguir = 'n';
                break;
            default:
                printf("\n La opcion ingresada es invalida! Intente nuevamente. \n");
                break;
        }
    }

    return 0;
}

