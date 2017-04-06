/***********************************************************************
* Programa: Calculadora de 5 funciones
*
* Objetivo:
* Realizar calculos matematicos con 2 numeros (solicitados al usuario)
*
* Version: 1.0 - 02/04/2017
* Autor: Alejandro Ben
*
***********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"


int main()
{
    char seguir='s'; // variable a verificar para seguir cargando operandos o realizar calculos
    int opcion=0; // variable para guardar la opcion elegida del menu
    float x, y; // variables de los operandos 1 y 2
    int flagX=0, flagY=0; // variables a utilizar paraa verificar que se hayan ingresado los ooperandos
    int i=0; // variable auxiliar necesaria para resolver la opcion de calcular todas las operaciones (indica la cantidad de calculos a realizar)

    while(seguir=='s')
    {
        infDatosIng(flagX, flagY , opcion, x); // Agrega leyendas y aclaraciones para el usuario
        printf("\n");

        // Menu de opciones:
        printf("1- Ingresar 1er operando (A=");
        if ( flagX == 1 )
            { printf("%f)\n",x); }
        else
            { printf("Sin valor asignado)\n"); }
        printf("2- Ingresar 2do operando (B=");
        if ( flagY == 1 )
            { printf("%f)\n",y); }
        else
            { printf("Sin valor asignado)\n"); }
        printf("3- Calcular la suma (A+B)\n");
        printf("4- Calcular la resta (A-B)\n");
        printf("5- Calcular la division (A/B)\n");
        printf("6- Calcular la multiplicacion (A*B)\n");
        printf("7- Calcular el factorial (A!)\n");
        printf("8- Calcular todas las operaciones\n");
        printf("9- Salir\n");

        opcion = pedirIntVal("\nElija una opcion", "La opcion ingresada es invalida! (debe ingresar un valor del 1 al 9)", 1, 9, 9); // Llamo a la funcion para pedir ingresar una opcion y validarla. Si se supera la cantidad de ingresos que devuelva 9 para de esa forma terminar la funcion main

        if ( (flagX + flagY) == 2 || opcion < 3 || opcion == 9 || (opcion == 7 && flagX ==1) ) // controlo que se puedan hacer las operaciones solo si previamente se cargaron los valores correspondientes
        {
            do //agrego este bucle para poder calcular y mostrar todas las operaciones en caso de que el usuario elija la opcion 8. Para ello utilizo el contador i (variable auxiliar)
            {
                switch(opcion)
                {
                    case 1: // Se pide ingresar 1er operando:
                        printf("Ingrese el valor del primer operando (con hasta 6 decimales): ");
                        fflush(stdin); //limpia el buffer
                        scanf("%f",&x);
                        flagX = 1;
                        break;
                    case 2: // Se pide ingresar 2do operando:
                        printf("Ingrese el valor del segundo operando (con hasta 6 decimales): ");
                        fflush(stdin); //limpia el buffer
                        scanf("%f",&y);
                        flagY = 1;
                        break;
                    case 3: // Calcular la suma (A+B)
                        printf("\n El resultado de la suma es: %f \n", suma(x, y) );
                        break;
                    case 4: // Calcular la resta (A-B)
                        printf("\n El resultado de restar %f a %f es: %f \n", y, x, resta(x, y) );
                        break;
                    case 5: // Calcular la division (A/B)
                        printf("\n El resultado de dividir %f por %f es: %f \n", x, y, division(x, y) );
                        break;
                    case 6: // Calcular la multiplicacion (A*B)
                        printf("\n El resultado de la multiplicacion es: %f \n", multiplicacion(x, y) );
                        break;
                    case 7: // Calcular el factorial (A!)
                        if (x>=0 && x<=100) // limito la opcion de c�lculo de factorial a un rango para el cual puedo mostrar la solucion (<=100) o que exista solucion (>=0)
                            { printf("\n El factorial de la parte entera de %f es: %.0f", x, factorial(x) ); }
                        else
                            { factorial(x); }// para mostrar las leyendas de la funcion factorial cuando el valor de A esta fuera del rango de calculo
                        break;
                    case 8: // Calcular todas las operaciones\n
                        i = 6; // cantidad de operaciones a calcular + 1 (ya que al salir del switch la linea de codigo "i--;" va a restar 1 valor al contador)
                        break;
                    case 9: // Salir
                        seguir = 'n';
                        printf("Proceso terminado.");
                        break;
                }

                opcion = 9 - i; // Nro. de operacion a calcular y mostrar
                i--; // bajo el contador de cantidad de operaciones a calcular, si se habia solicitado calcular solo 1 se sale del while.
            } while (i>0);
        }
        printf("\n"); // salteo de renglon por consola
    }
    return 0; // fin de la funcion main
}
