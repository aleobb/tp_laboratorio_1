#include <stdio.h>
#include <stdlib.h>

/*
* \brief solicitar al usuario un numero y validarlo dentro de un rango de enteros (en este caso una opcion del menu)
* \param mensaje: leyenda para pedir el dato
* \param mensjaeError: leyenda a mostrar si el dato no esta dentro del rango
* \param int y max: minimos y maximos validos
* \return devuelve el dato tomado y validado (en este caso la opcion del menu)
*/
int pedirIntVal(char mensaje[], char mensajeError[], int min, int max)
{
    int option;
    int i=5; // cantidad maxima de ingresos erronos
    printf("%s: ",mensaje);
    fflush(stdin); //limpia el buffer
    scanf("%d",&option);
    printf("\n");

    while( option < min || option > max ) //controla que el valor ingresado este dentro del rango valido, sino lo vuelve a pedir con un maximo de intentos
    {
        printf("%s",mensajeError);
        printf("%s ",mensaje);
        printf("(Cantidad de intentos maximos: %d): ",i);
        fflush(stdin); //limpia el buffer
        scanf("%d",&option);
        printf("\n");
        i--; // se reduce la cantidad intentos de ingreso de un dato valido
        if (i==0)
            { option = 9; } //igualo a la opcion de salir del menu para terminar y salir del programa
    }
    return option;
}

/*
* \brief Informa al usuario limitaciones en las operaciones posibles a realizar.
* \param flagA y flagB verifican si el usuario ya ingreso los valores de A y B respectivamente (x e y en main.c)
* \param option es la opcion del menu elegida por el usuario
* \A es el valor del primer operando
* \return no devuelve nada al proceso que llamo a la funcion
*/
void infDatosIng(int flagA, int flagB, int option, float A)
{
    if ( (option>2 && (flagA + flagB)<2) || option==0 )
    {
        printf("\n\n Atencion!! No se puede realizar niguna operacion ");
        if (flagA == 1) // si solo se ingreso el dato A )(x en main.c)
        {
            if (A<0)
            { printf("\n (ni siquiera factorial) porque el valor del primer operando es negativo y "); }
            else
            { printf("\n (salvo factorial) porque "); }
            printf("falta ingresar el valor del 2do operando. \n\n ");
            printf("Aclaraciones: \n * Solo se calculara el factorial de numeros enteros del 0 al 100 \n ");
            printf("* En caso de haber ingresado un numero con decimales se calculara el factorial de la porcion entera. \n ");
        }
        else if (flagB == 1) // si solo se ingreso el dato B )(y en main.c)
            { printf("\n porque falta ingresar el valor del 1er operando. \n"); }
        else // si todavia no se ingreso ningun dato de A y B)(x e y en main.c)
            { printf("\n porque todavia no ha ingresado el valor de ningun operando. \n"); }
    }
    printf(" (La precision de la calculadora es con hasta 8 digitos para el valor de los operandos) \n");
    if ( (flagA + flagB)==2 && A<0 )
        { printf("\n No se podra calcular factorial porque el valor del primer operando es negativo. \n"); }
}

/*
* \brief calcula la suma entre 2 numeros A y B
* \param A y B son los valores con los que se va a calcular la suma
* \return devuelve el resultado de la suma
*/
float suma(float A, float B)
{
    return (A+B);
}

/*
* \brief calcula la resta entre 2 numeros A y B
* \param A y B son los valores con los que se va a calcular la resta
* \return devuelve el resultado de la resta
*/
float resta(float A, float B)
{
    return (A-B);
}

/*
* \brief calcula la division de A por B
* \param A y B son los valores con los que se va a calcular la division
* \return devuelve el resultado de la division
*/
float division(float A, float B)
{
    if ( B == 0 ) //controla el error de dividir por 0
    {
        printf("\n El divisor es igual a 0 y por tanto no puede realizarse la division. Modifiquelo e intente nuevamente. \n\n");
        return 0;
    }
    else
        { return (A/B); }
}

/*
* \brief calcula la multiplicacion entre 2 numeros A y B
* \param A y B son los valores con los que se va a calcular la multiplicacion
* \return devuelve el resultado de la multiplicacion
*/
double multiplicacion(float A, float B)
{
    return (A*B);
}

/*
* \brief calcula el factorial del numero A
* \param A es el valor utilizado para realizar el calculo
* \return devuelve el resultado del factorial de A
*/
double factorial(int A)
{
    double factA=1; // el resultado a devolver de la funcion sera 1 cuando A sea cero
    double aux; // variable auxiliar necesaria para poder hacer el calculo
    if ( A < 0 ) // controla que el factorial pueda calcularse (es decir el valor base no puede ser negativo)
    {
        printf("\n El valor factorial no puede calcularse debido a que el 1er operando es un numero negativo.\n Modifiquelo e intente nuevamente. \n\n");
        return 0;
    }
    else if ( A > 100 ) // limita el calculo a valores no superiores a 100
    {
        printf("\n El valor factorial de 1er operando no se calculara porque es mayor a 100 \n Modifiquelo e intente nuevamente. \n\n");
        return 0;
    }
    else
    {
        for (aux = A; aux > 1; aux--) // si A es mayor a 1 realiza el calculo sino no
            { factA = factA * aux; }
        return factA; //devuelve el resultado del calculo
    }
}
