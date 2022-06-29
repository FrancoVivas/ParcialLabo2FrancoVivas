#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "utn.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);


LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = (LinkedList*) malloc(sizeof(LinkedList));

    if(this!=NULL)
    {
    	this->size = 0;
    	this->pFirstNode = NULL;
    }
    return this;
}

int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this!=NULL)
    {
    	returnAux = this->size;
    }

    return returnAux;
}


static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pNodo = NULL;	//[Solicita nodo pasando una lista NULL] x ende presetearlo como NULL

	//ES UNA TAREA COMUN A VARIAS FUNCIONES DEVUELVE LA DIRECCION EN MEMORIA DE UN NODO
	if(this!=NULL && nodeIndex>=0 && nodeIndex<ll_len(this))//nodo si puede ser igual a 0 pero no menor y tampoco mayor al len de this
	{
		pNodo = this->pFirstNode;//apunto al primer vagon

		for(int i=0;i<nodeIndex;i++)
		{
			pNodo = pNodo->pNextNode;
		}

	}

    return pNodo;
}


Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;

    Node* pNodo = NULL;

   // Node* pPrevNode; //NODO PREVIO AL DE ADELANTE

    //pElement PUEDE SER NULL x eso no valido
    if(this!=NULL && nodeIndex<=ll_len(this) &&  nodeIndex>=0)
    {
    	pNodo = (Node*) malloc(sizeof(Node));
    	if(pNodo!=NULL)
    	{
    		pNodo->pElement = pElement;
    		pNodo->pNextNode = getNode(this, nodeIndex);//NECESITO LA DIRECCION EN MEMORIA ACTUAL

    	//	pPrevNode = getNode(this, nodeIndex-1);
    	//	pPrevNode->pNextNode = pNodo;
    		if(nodeIndex==0)//si el vagon es 0
    		{
    			this->pFirstNode = pNodo;// o lo engancho a la locomotora
    		}
    		else
    		{
        		//DEVUELVE LA DIRECCION EN MEMORIA DEL VAGON QUE ESTA ADELANTE DEL QUE VOY A INSERTAR
        		(getNode(this, nodeIndex-1))->pNextNode=pNodo; //o lo enganfo al de adelante
    		}
    		this->size++; //INCREMENTO EL TAM DEL LINKEDLIST

    		returnAux = 0;//todo salio bien
    	}
    }

    return returnAux;
}


int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL)//pElement PUEDE SER NULL
    {
    	if(!addNode(this, ll_len(this), pElement))//AGREGA EL NODO AL FINAL
    	{
    		returnAux=0;
    	}
    }

    return returnAux;
}


void* ll_get(LinkedList* this, int index)//RETORNAR ELEMENTO especificado
{
    void* returnAux = NULL;

    Node* pNode;

    if(this!=NULL && index>=0 && index<ll_len(this))//si pongo index> tira errores y index debe de ser menor y no igual
    {
    	pNode = getNode(this,index); //obtengo el nodo a mostrar

    	if(pNode !=NULL)
    	{
    		returnAux = pNode->pElement;//QUE ME RETORNE EL ELEMENTO ESPECIFICADO
    		pNode=NULL;//LO VUELVO A SETEAR COMO NULO LUEGO DE USARLO
    	}
    }
    return returnAux;
}


int ll_set(LinkedList* this, int index,void* pElement)//PISA UN ELEMENTO EN ESE NODO EN ESA POSICION
{
    int returnAux = -1;//obtener nodo get

    Node* pNode=NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	pNode = getNode(this, index);
        if(pNode!=NULL)
        {
        	pNode->pElement = pElement;
        	returnAux =0;
        }
    }

    return returnAux;
}


int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;

    Node* pNode = NULL;
    Node* pNodeAnterior;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	pNode = getNode(this, index); //OBTENGO EL NODO
    	if(pNode!=NULL)
    	{
        	if(index==0)
        	{
        		this->pFirstNode = pNode->pNextNode;//apunta al vagon 1 del pNextNode
        	}
        	else
        	{
        		pNodeAnterior = getNode(this, index - 1); //OBTENGO EL NODO DE LA POSICION ANTERIOR
        		if(pNodeAnterior!=NULL)//valido que no venga nulo
        		{
        			pNodeAnterior->pNextNode = pNode->pNextNode;
        		}
        	}
        	free(pNode);
        	this->size--;
    		returnAux=0;
    	}
    }
    return returnAux;
}


int ll_clear(LinkedList* this)//RECORRE Y LLAMA A REMOVE
{
    int returnAux = -1;

    int falla = 1; //1 no 0 si

    if(this!=NULL)
    {
    	//for(int i=ll_len(this)-1; i>=0;i--)//voy removiendo de atras hacia delante
    	//while(this->pFirstNode != NULL)//mientras apunte a algo, cuando deje de apuntar rompe (funca igualmente)
    	//while(ll_len(this)>0)//mientras tenga elementos sigo sacando, puedo usar un for...
    	while(!ll_isEmpty(this))//como otra opcion, mientras NO este vacia hago un clear...
    	{
    		if(ll_remove(this, 0)==-1)//utilizo return de remove para ver si fallo un remove
    		{
    			falla=0;//si fallo
    			break;//rompo entonces la iteracion
    		}
    		if(falla)
    		{
    	    	returnAux = 0;//no, que siga iterando
    		}
    	}
    }
    return returnAux;
}


int ll_deleteLinkedList(LinkedList* this)//LLAMA AL CLEAR
{
    int returnAux = -1;

    if(this!=NULL)
    {
    	if(!ll_clear(this))
    	{
    		free(this);
        	returnAux =0;
    	}
    }

    return returnAux;
}


int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL)
    {
    	for(int i=0;i<ll_len(this);i++)//recorro lista
    	{
            if(ll_get(this, i) == pElement)//busco esa ocurrencia
            {
            	returnAux = i;//retorno el indice
            	break;//rompo
            }
    	}
    }
    return returnAux;
}


int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this!=NULL)
    {
    	returnAux = 0;//tiene elementos
    	if(!ll_len(this))
    	{
    		returnAux=1;//NO tiene elementos
    	}
    }

    return returnAux;
}


int ll_push(LinkedList* this, int index, void* pElement)//METE UN NODO ENTRE DOS
{
    //creo un nodo y hago que apunte a pElement en la posicion indicada
    return addNode(this, index, pElement);//LO MISMO QUE RECIBO ES LO MISMO QUE PASO
}


void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	returnAux = ll_get(this, index);//obtengo el elemento del indice, lo devuelvo
    	ll_remove(this, index);//lo elimino el index si ya lo guarde en return.
    }

    return returnAux;
}


int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL)//ya tengo una funcion que me busca un elemento de la lista y la recorre...
    {
    	returnAux = 0; //NO ESTA EN CONTENIDO
    	if(ll_indexOf(this, pElement) != -1)//esta presente/contenido si es distinto a -1
    	{
    		returnAux = 1; //SI ESTA CONTENIDO
    	}
    }
    return returnAux;
}


int ll_containsAll(LinkedList* this,LinkedList* this2)//COMPARO Y ME FIJO SI ESTA EN LA OTRA NO ES NECESARIA LA MISMA CANTIDAD
{
    int returnAux = -1;

    int sizeThis2;

    if(this!=NULL && this2!=NULL)
    {
    	returnAux = 1; //estan contenidos
    	sizeThis2 = ll_len(this2);
    	for(int i=0;i<sizeThis2;i++)//recorro con el size de la segunda lista
    	{
    		if(!ll_contains(this, ll_get(this2, i)))
    		{
    			returnAux = 0;
    			break;//rompo xq ya comprobe que no esta contenido
    		}
    	}
    }
    return returnAux;
}


LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    void* pElemento = NULL;

    if(this!=NULL && from>=0 && from<ll_len(this) && to>from && to<=ll_len(this))
    {
    	cloneArray = ll_newLinkedList();//creo un nuevo array
    	if(cloneArray!=NULL)
    	{
    		for(int i = from;i <to;i++)//recorro mientras i<to
    		{
    			pElemento = ll_get(this, i);//obtengo el elemento en el indice
    			ll_add(cloneArray, pElemento);//pongo el elemento dentro de la nueva lista
    		}
    	}
    }
    return cloneArray;
}


LinkedList* ll_clone(LinkedList* this)//devuelve copia del original
{
    LinkedList* cloneArray = NULL;

    if(this!=NULL)
    {//llamo a sub lista que ya crea una nueva, le paso la lista a clonar, desde (0) y hasta (el final de this)
    	cloneArray = ll_subList(this, 0, ll_len(this));//y lo copio en cloneArray
    }

    return cloneArray;
}


int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;

    void* pElementoI = NULL;//backup/aux
    void* pElementoJ = NULL;//backup/aux

    if(this!=NULL && pFunc!=NULL && order>=0 && order<=1)
    {
    	for(int i = 0;i<ll_len(this)-1;i++)//hago burbujeo
    	{
    		for(int j=i+1;j<ll_len(this);j++)
    		{
    			pElementoI = ll_get(this, i);//obtengo el elemento en el indice de i
    			pElementoJ = ll_get(this, j);//obtengo el elemento en el indice de j
    			if((pFunc(pElementoI,pElementoJ) > 0 && order) || (pFunc(pElementoI,pElementoJ) < 0 && !order))
    			{
    				ll_set(this, i, pElementoJ);//tenog que pisar el I x eso paso j
    				ll_set(this, j, pElementoI);//tenog que pisar el j x eso paso i
    				returnAux = 0;//si se hizo swap 0
    			}
    		}
    	}
    }
    return returnAux;
}

int ll_sortBy2Func(LinkedList *this, int (*pFunc)(void*, void*),int (*pFunc2)(void*, void*), int criterio)
{
	//LinkedList* sortedList;

	void *pElement1;
	void *pElement2;

	int sizeOfList;
	int todoOk = 0;

	if (this != NULL && pFunc != NULL && (criterio == 1 || criterio == 0))
	{
		//sortedList = ll_newLinkedList();
		sizeOfList =  ll_len(this);
		for (int i = 0; i < sizeOfList -1; i++)
		{
			for (int j = i + 1; j < sizeOfList; j++)
			{
				pElement1 = ll_get(this, i); //OBTENGO EL PRIMER ELEMENTO y copio
				pElement2 = ll_get(this, j); //OBTENGO EL SEGUNDO ELEMENTO y copio

				//SI SON DISTINTOS LOS ELEMENTOS ORDENO POR CRITERIO
				if ((pFunc(pElement1, pElement2) > 0 && criterio)||(pFunc(pElement1, pElement2) < 0 && !criterio))
				{
					 //SWAPEO LOS ELEMENTOS
					ll_set(this, i, pElement2);
					ll_set(this, j, pElement1);
				}//SI NO, SI SON IGUALES ORDENO POR LA SEGUNDA FUNCION
				else if (pFunc(pElement1, pElement2) == 0)
				{
					if(pFunc2(pElement1,pElement2)>0)
					{
						ll_set(this, i, pElement2);
						ll_set(this, j, pElement1);
					}
				}
				todoOk = 1;
			}
		}
	}
	return todoOk;
}

LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*))
{
	LinkedList* nuevaLinked = NULL;//la nueva lista
	void* pAux = NULL;//Creo un auxiliar para guardar lo que filtro
	int sizeLinked;

	if(this!=NULL && pFunc!=NULL)
	{
		nuevaLinked = ll_newLinkedList();//creo la nueva lista

		if(nuevaLinked !=NULL)
		{
			sizeLinked = ll_len(this);//guardo el tam de la lista original

			for(int i = 0;i<sizeLinked;i++)//recorro la lista original
			{
				pAux = ll_get(this, i);//obtengo lo que esta en el indice i
				if(pFunc(pAux))//llamo a la funcion y le paso el pAux para que filtre
				{
					//paso esa nueva lista y lo que debe de aniadir
					if(ll_add(nuevaLinked, pAux))//add tiene retorno, si devuelve != 0 fallo
					{
						ll_deleteLinkedList(nuevaLinked);//hago un free de la lista
						nuevaLinked = NULL;//libero la memoria xq ll_delete NO retorna NULL
						break;//rompo xq fallo un add
					}
				}
			}
			pAux = NULL;//dejo de usarlo y lo vuelvo a poner en NULL
		}
	}
	return nuevaLinked;
}

LinkedList* ll_map(LinkedList* this, void* (*pFunc)(void* element))
{
	int sizeOfList;
	void* pElement;

	LinkedList* mappList = NULL;

	if(this!=NULL && pFunc!=NULL)
	{
		mappList = ll_newLinkedList();
		if(mappList!=NULL)
		{
			sizeOfList = ll_len(this);
			for(int i=0;i<sizeOfList;i++)
			{//se debera de iterar todos los elementos de la lista
				pElement = ll_get(this, i);
				pElement = pFunc(pElement);//el retorno de pFunc se agrega a la lista resultado
				if(pElement!=NULL)
				{
					ll_add(mappList, pElement);
				}
			}
		}
	}

	return mappList;
}
