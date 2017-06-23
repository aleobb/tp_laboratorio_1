#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "funcAux.h"
#include "Destinatarios.h"

// funciones privadas
int resizeUp(ArrayList* pList);
int expand(ArrayList* pList,int index);
int contract(ArrayList* pList,int index);
int insertionSort(void** array, int size, int order, int (*pFunc)(void*,void*) );
int bubleSort2(void** array, int size, int order, int (*pFunc)(void*,void*) );
void swapElements(void* pElement1, void* pElement2);
int quickSort(void** array, int size, int order, int (*pFunc)(void*,void*) );


#define AL_INCREMENT      10
#define AL_INITIAL_VALUE  10
//___________________

/** \brief Allocate a new arrayList with AL_INITIAL_VALUE elements.
 * \param void
 * \return ArrayList* Return (NULL) if Error [if can't allocate memory]
 *                  - (pointer to new arrayList) if ok
 */
ArrayList* al_newArrayList(void)
{
    ArrayList* pList;
    ArrayList* returnAux = NULL;
    void* pElements;
    pList=(ArrayList *)malloc(sizeof(ArrayList));

    if(pList != NULL)
    {
        pElements = malloc(sizeof(void *)*AL_INITIAL_VALUE );
        if(pElements != NULL)
        {
            ///todas estas son las llamadas a los punteros de las funciones que se van cargando en el pList
            pList->size=0;
            pList->pElements=pElements;
            pList->reservedSize=AL_INITIAL_VALUE;
            pList->add=al_add;
            pList->len=al_len;
            pList->set=al_set;
            pList->remove=al_remove;
            pList->clear=al_clear;
            pList->clone=al_clone;
            pList->get=al_get;
            pList->contains=al_contains;
            pList->push=al_push;
            pList->indexOf=al_indexOf;
            pList->isEmpty=al_isEmpty;
            pList->pop=al_pop;
            pList->subList=al_subList;
            pList->containsAll=al_containsAll;
            pList->deleteArrayList = al_deleteArrayList;
            pList->sort = al_sort;

           // pList->filter=al_filter;  /// Funcion agregada a la estructura original

            returnAux = pList;
        }
        else
        {
            free(pList);
        }
    }

    return returnAux;
}


/** \brief  Add an element to arrayList and if is
 *          nessesary resize the array
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (0) if Ok
 *
 */
int al_add(ArrayList* this, void* pElement)
{
    int returnAux = -1;

    if ( this != NULL && pElement != NULL )
    {
        if ( resizeUp(this) == 0 )
        {
            this->pElements[ this->size ] = pElement;
            /// *( (this->pElements)+(this->size) ) = pElement;   esta linea es igual a la de arriba
            this->size++;
            returnAux = 0;
        }
    }
    return returnAux;

    /*
            if( this->size < this->reservedSize )
            {
                returnAux = 0;
                this->pElements[ this->size ] = pElement;
            /// *( (this->pElements)+(this->size) ) = pElement;   esta linea es igual a la de arriba
                this->size++;
            }
            if ( this->size == this->reservedSize )
            {
                if ( resizeUp(this) != 0 )
                {

                }
            }
    */
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Ok
 *
 */
int al_deleteArrayList(ArrayList* this)
{
    int returnAux = -1;

    if ( this!= NULL )
    {
        free(this);
        returnAux = 0;
    }

    return returnAux;
}

/** \brief  Delete arrayList
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return length of array or (-1) if Error [pList is NULL pointer]
 *
 */
int al_len(ArrayList* this)
{
    int returnAux = -1;

    if ( this!= NULL )
        returnAux = this->size;

    return returnAux;
}


/** \brief  Get an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return void* Return (NULL) if Error [pList is NULL pointer or invalid index] - (Pointer to element) if Ok
 *
 */
void* al_get(ArrayList* this, int index)
{
    void* returnAux = NULL;

    if ( this != NULL && index >= 0 && index <= this->size )
        returnAux = this->pElements[index];

    return returnAux;
}


/** \brief  Find if pList contains at least one element pElement
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer]
 *                  - ( 0) if Ok but not found a element
 *                  - ( 1) if this list contains at least one element pElement
 *
 */
int al_contains(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    int i;

    if ( this != NULL && pElement != NULL )
    {
        returnAux=0;
        for ( i=0 ; i < (this->size) ; i++ )
        {
            if (  al_get(this,i) == pElement )
            {
                returnAux = 1;
                break;
            }
        }
    }
    return returnAux;
}


/** \brief  Set a element in pList at index position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 *
 */
int al_set(ArrayList* this, int index,void* pElement)
{
    int returnAux = -1;

    if ( this!= NULL && pElement!=NULL && index >= 0 && index < this->size )
    {
        returnAux = 0;
      /*  if ( index = this->size )
            this->add(this, pElement);
        else */
            this->pElements[index] = pElement;
    }

    return returnAux;
}


/** \brief  Remove an element by index
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_remove(ArrayList* this, int index)
{
    int returnAux = -1;

    if ( this!= NULL && index >= 0 && index < this->size )
        if ( contract(this, index) == 0 )
            returnAux = 0;

    return returnAux;
}



/** \brief Removes all of the elements from this list
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer]
 *                  - ( 0) if Ok
 */
int al_clear(ArrayList* this)
{
    int returnAux = -1;
    //int i;
    if ( this!= NULL )
    {
        // NO HACE FALTA ESTO:
        //for ( i=(this->size) ; i < 0 ; i-- )
        //    contract(this, i);
        this->size = 0;
        returnAux = 0;
    }
    return returnAux;
}



/** \brief Returns an array containing all of the elements in this list in proper sequence
 * \param pList ArrayList* Pointer to arrayList
 * \return ArrayList* Return  (NULL) if Error [pList is NULL pointer]
 *                          - (New array) if Ok
 */
ArrayList* al_clone(ArrayList* this)
{
    ArrayList* returnAux = NULL;
    ArrayList* pListClone = al_newArrayList();
    int i;

    if ( this!= NULL && pListClone!= NULL )
    {
        for ( i=0 ; i < (this->size) ; i++ )
            if( al_add( pListClone, al_get(this,i) ) == -1)
                break;
        returnAux = pListClone;
    }
    return returnAux;
}




/** \brief Inserts the element at the specified position
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int al_push(ArrayList* this, int index, void* pElement)
{
    int returnAux = -1;
    if ( this!= NULL && pElement!=NULL && index >= 0 && index <= this->size )
    {
     // if ( this->size == 0)  No hace falta hacer esta evaluación y luego un al_add ya que expand() se encarga de eso
     //     al_add(this, pElement );
        if ( expand(this, index) == 0 )
            if ( al_set( this, index, pElement ) == 0);
                returnAux=0;
    }
    return returnAux;
}



/** \brief Returns the index of the first occurrence of the specified element
 * \param pList ArrayList* Pointer to arrayList
 * \param pElement void* Pointer to element
 * \return int Return (-1) if Error [pList or pElement are NULL pointer] - (index to element) if Ok
 */
int al_indexOf(ArrayList* this, void* pElement)
{
    int returnAux = -1;
    int i;

    if ( this != NULL && pElement != NULL )
    {
        for ( i=0 ; i < (this->size) ; i++ )
            if (  al_get(this,i) == pElement )
            {
                returnAux = i;
                break;
            }
    }
    return returnAux;
}



/** \brief Returns true if this list contains no elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer] - (0) if Not Empty - (1) if is Empty
 */
int al_isEmpty(ArrayList* this)
{
    int returnAux = -1;

    if ( this != NULL )
    {
        returnAux = 1;
        if ( al_len(this) > 0 )
            returnAux = 0;
    }
    return returnAux;
}




/** \brief Remove the item at the given position in the list, and return it.
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid index]
 *                  - ( element pointer) if Ok
 */
void* al_pop(ArrayList* this, int index)
{
    void* returnAux = NULL;

    if ( this!= NULL && index >= 0 && index < this->size )
    {
        returnAux = al_get(this, index);
        if ( al_remove(this, index) != 0 )
            returnAux = NULL;
     // contract(this, index); <= funciona también con esta línea en lugar de al_remove
    }
    return returnAux;
}


/** \brief Returns a new arrayList with a portion of pList between the specified
 *         fromIndex, inclusive, and toIndex, exclusive.
 * \param pList ArrayList* Pointer to arrayList
 * \param from int Initial index of the element (inclusive)
 * \param to int Final index of the element (exclusive)
 * \return int Return (NULL) if Error [pList is NULL pointer or invalid 'from' or invalid 'to']
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_subList(ArrayList* this, int from, int to)
{
    ArrayList* returnAux = NULL;
    ArrayList* pListClone = al_newArrayList();
    int i;

    if ( this != NULL  &&  pListClone != NULL  &&  from <= to  &&  from >= 0  &&  to <= this->size )
    {
        for ( i = from ; i < to ; i++ )
            if ( al_add( pListClone, this->pElements[i] ) == -1 )
            {
                free(pListClone);
                pListClone = NULL;
                break;
            }
        returnAux = pListClone;
    }

    return returnAux ;
}


/** \brief Returns a new arrayList with a portion of pList that meets the condition.
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param void* pCompare Pointer to Element to compare with
 * \param int filter  [0] indicates EQUAL - [1] indicates HIGHER - [-1] indicates LOWER - [2] indicates DIFFERENT
 * \return int Return (NULL) if Error [pList or pFunc are NULL pointer or invalid filter]
 *                  - ( pointer to new array) if Ok
 */
ArrayList* al_filter(ArrayList* this, ArrayList* this2, int (*pFuncCompare)(char*,char*), int filter )
{
    ArrayList* returnAux = NULL;
    ArrayList* pListClone = al_newArrayList();
    int i;
    int j;
    int compareResult;
    int flag = 0;

    if ( this != NULL  &&  pListClone != NULL  &&  pFuncCompare != NULL  )
    {
        for ( i = 0 ; i < this->size ; i++ )
        {
            for( j = 0 ; j < this2->size ; j++ )
            {
                //printf ("Destinatario %s \n", ( (Destinatario*)this->get(this,i) )->email );
                //printf ("Destinatario %s \n", ( (Destinatario*)this2->get(this2,j) )->email );
                compareResult = stricmp( ( (Destinatario*)this->get(this,i) )->email, ( (Destinatario*)this2->get(this2, j) )->email );
                //printf("\n compare result : %d", compareResult );
                if ( compareResult == filter )
                {
                    //printf ("Destinatario %s \n", ( (Destinatario*)this->get(this,i) )->email );
                    //printf ("Destinatario %s \n", ( (Destinatario*)this2->get(this2,j) )->email );
                    flag = 1;

                    break;
                }
            }
            if ( flag == 0 )
            {
                //printf("\n flag %d", flag);
                al_add( pListClone, this->get(this,i) );
            }


            flag = 0;
        }

        returnAux = pListClone;
    }
    return returnAux ;
}




/** \brief Returns true if pList list contains all of the elements of pList2
 * \param pList ArrayList* Pointer to arrayList
 * \param pList2 ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList or pList2 are NULL pointer]
 *                  - (0) if Not contains All - (1) if is contains All
 */
int al_containsAll(ArrayList* this, ArrayList* this2)
{
    int returnAux = -1;
    int i;

    if ( this != NULL && this2 != NULL )
    {
        returnAux = 0;
        for ( i=0 ; i < (this2->size) ; i++ )
        {
            returnAux = 1;
            if ( al_contains(this, this2->pElements[i] ) != 1 )
            {
                returnAux = 0;
                break;
            }
        }
    }
    return returnAux;
}

/** \brief Sorts objects of list, use compare pFunc
 * \param pList ArrayList* Pointer to arrayList
 * \param pFunc (*pFunc) Pointer to fuction to compare elements of arrayList
 * \param order int  [1] indicate UP - [0] indicate DOWN
 * \return int Return (-1) if Error [pList or pFunc are NULL pointer]
 *                  - (0) if ok
 */
int al_sort(ArrayList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux = -1;
    if ( this != NULL  &&  this->size > 1  &&  order >= 0  &&  order <= 1  &&  pFunc != NULL )
    {
        if( order == 0 ) /// Esta línea es necesaria porque pFunc compara tomando como parametros -1(DOWN) o 1(UP)
            order = -1;
        insertionSort(this->pElements, this->size, order, pFunc);
        //bubleSort2(this->pElements, this->size, order, pFunc);
        //quickSort(this->pElements, this->size, order, pFunc);
        returnAux = 0;
    }
    return returnAux;
}

/* (La función pFunc no la tengo que crear sino que ya está creada)
pFunc(void* pElement1 , void* pElement2)
{
    return strcmp( pElement1 , pElement2 );
} */

int insertionSort(void** array, int size, int order, int (*pFunc)(void*,void*) )
{
    int i,j;
    int retorno = -1;
    void* auxiliar;

    if ( array != NULL  &&  size > 1  &&  ( order == -1  ||  order == 1 )  &&  pFunc != NULL )
    {
        for(i = 1; i < size; i++)
        {
            auxiliar = array[i];
            j = i;
            while(j > 0 && order == pFunc(array[j - 1], auxiliar) )
            {
                array[j] = array[j - 1];
                j--;
            }
            array[j] = auxiliar;
        }
        retorno = 0;
    }
    return retorno;
}


int bubleSort2(void** array, int size, int order, int (*pFunc)(void*,void*) )
{
       int i;
       int retorno = -1;
       void* pElementAux;

       if ( array != NULL  &&  size > 1  &&  ( order == -1  ||  order == 1 )  &&  pFunc != NULL )
       {
           while(retorno)
           {
               retorno = 0;
               for ( i = 1 ; i < size ; i++ )
               {
                    if ( pFunc(array[i-1], array[i]) == order )
                    {
                        pElementAux = array[i];
                        array[i] = array[i-1];
                        array[i-1] = pElementAux;
                        retorno = -1;
                    }
               }
           }
       }
    return retorno;
}


void swapElements(void* pElement1, void* pElement2)
{
    void* pElementAux = pElement1;
    pElement1 = pElement2;
    pElement2 = pElementAux;
}


int quickSort(void** array, int size, int order, int (*pFunc)(void*,void*) )
{
    void* pivot;
    int i, j;
    int retorno = -1;
    void* pElementAux;

    if ( array != NULL  &&  size > 1  &&  ( order == -1  ||  order == 1 )  &&  pFunc != NULL )
    {
        if (size < 2)
            return retorno = 0;

        pivot = array[size/2];

        for ( (i=0, j=size-1) ;   ; (i++, j--) )
        {
            while ( order == pFunc(pivot, array[i]) ) //(array[i] < pivot)
                i++;
            while ( order == pFunc(array[j], pivot) ) //(array[j] > pivot)
                j--;

            if ( i >= j )
                break;

            pElementAux = array[i];
            array[i] =  array[j];
            array[j] =  pElementAux;
        }

        retorno = quickSort(array, i, order, pFunc);
        retorno = quickSort(array + i, size - i, order, pFunc);
    }
    return retorno;
}



/** \brief Increment the number of elements in pList in AL_INCREMENT elements.
 * \param pList ArrayList* Pointer to arrayList
 * \return int Return (-1) if Error [pList is NULL pointer or if can't allocate memory]
 *                  - (0) if ok
 */
int resizeUp(ArrayList* this)
{
    int returnAux = -1;
    //void** pElementsAux;  <= podria declararlo aca pero lo declaro directamente donde lo uso

    if ( this != NULL )
    {
        if ( this->size == this->reservedSize )
        {
            void** pElementsAux = (void**) realloc( this->pElements, sizeof(void*) * ( this->reservedSize + AL_INCREMENT ) );
            if ( pElementsAux != NULL )
            {
                this->pElements = pElementsAux;
                this->reservedSize += AL_INCREMENT;
                returnAux = 0;
            }
        }
        else if ( this->size < this->reservedSize )
            returnAux = 0;
    }

    return returnAux;

}

/** \brief  Expand an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int expand(ArrayList* this, int index)
{
    int returnAux = -1;
    int auxIndex;
    if ( this != NULL && index >= 0 && index <= this->size )
    {
        al_add(this, this->pElements[ (this->size)-1 ]);  /// Con esta linea me aseguro de aumentar el espacio para la lista de elementos en caso de que size = reservedSize
        returnAux=0;
        for ( auxIndex=(this->size-1); auxIndex > index ; auxIndex-- )  /// Arranco desde (this->size-1) ya que uno lo hice con al_add
            this->pElements[auxIndex] = this->pElements[auxIndex-1];
    /// this->size++;  esta linea no hace falta ya que al_add se encargó de expandirlo.
    }
    return returnAux;
}

/** \brief  Contract an array list
 * \param pList ArrayList* Pointer to arrayList
 * \param index int Index of the element
 * \return int Return (-1) if Error [pList is NULL pointer or invalid index]
 *                  - ( 0) if Ok
 */
int contract(ArrayList* this, int index)
{
    int returnAux = -1;
    if ( this != NULL && index >= 0 && index < this->size )
    {
        returnAux=0;
        for ( ; index < (this->size)-1 ; index++ )
            this->pElements[index] = this->pElements[index+1];
        this->size--;
    }
    return returnAux;
}

