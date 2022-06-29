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
	Node* pNodo = NULL;

	if(this!=NULL && nodeIndex>=0 && nodeIndex<ll_len(this))
	{
		pNodo = this->pFirstNode;

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

    if(this!=NULL && nodeIndex<=ll_len(this) &&  nodeIndex>=0)
    {
    	pNodo = (Node*) malloc(sizeof(Node));
    	if(pNodo!=NULL)
    	{
    		pNodo->pElement = pElement;
    		pNodo->pNextNode = getNode(this, nodeIndex);

    		if(nodeIndex==0)
    		{
    			this->pFirstNode = pNodo;
    		}
    		else
    		{
        		(getNode(this, nodeIndex-1))->pNextNode=pNodo;
    		}
    		this->size++;

    		returnAux = 0;
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

    if(this!=NULL)
    {
    	if(!addNode(this, ll_len(this), pElement))
    	{
    		returnAux=0;
    	}
    }

    return returnAux;
}


void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;

    Node* pNode;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	pNode = getNode(this,index);
    	if(pNode !=NULL)
    	{
    		returnAux = pNode->pElement;
    		pNode=NULL;
    	}
    }
    return returnAux;
}


int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;

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
    	pNode = getNode(this, index);
    	if(pNode!=NULL)
    	{
        	if(index==0)
        	{
        		this->pFirstNode = pNode->pNextNode;
        	}
        	else
        	{
        		pNodeAnterior = getNode(this, index - 1);
        		if(pNodeAnterior!=NULL)
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


int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    int falla = 1;

    if(this!=NULL)
    {
    	while(!ll_isEmpty(this))
    	{
    		if(ll_remove(this, 0)==-1)
    		{
    			falla=0;
    			break;
    		}
    		if(falla)
    		{
    	    	returnAux = 0;
    		}
    	}
    }
    return returnAux;
}


int ll_deleteLinkedList(LinkedList* this)
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
    	for(int i=0;i<ll_len(this);i++)
    	{
            if(ll_get(this, i) == pElement)
            {
            	returnAux = i;
            	break;
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
    	returnAux = 0;
    	if(!ll_len(this))
    	{
    		returnAux=1;
    	}
    }

    return returnAux;
}


int ll_push(LinkedList* this, int index, void* pElement)
{
    return addNode(this, index, pElement);
}


void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;

    if(this!=NULL && index>=0 && index<ll_len(this))
    {
    	returnAux = ll_get(this, index);
    	ll_remove(this, index);
    }

    return returnAux;
}


int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL)
    {
    	returnAux = 0;
    	if(ll_indexOf(this, pElement) != -1)
    	{
    		returnAux = 1;
    	}
    }
    return returnAux;
}


int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;

    int sizeThis2;

    if(this!=NULL && this2!=NULL)
    {
    	returnAux = 1;
    	sizeThis2 = ll_len(this2);
    	for(int i=0;i<sizeThis2;i++)
    	{
    		if(!ll_contains(this, ll_get(this2, i)))
    		{
    			returnAux = 0;
    			break;
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
    	cloneArray = ll_newLinkedList();
    	if(cloneArray!=NULL)
    	{
    		for(int i = from;i <to;i++)
    		{
    			pElemento = ll_get(this, i);
    			ll_add(cloneArray, pElemento);
    		}
    	}
    }
    return cloneArray;
}


LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this!=NULL)
    {
    	cloneArray = ll_subList(this, 0, ll_len(this));
    }

    return cloneArray;
}


int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;

    void* pElementoI = NULL;
    void* pElementoJ = NULL;

    if(this!=NULL && pFunc!=NULL && order>=0 && order<=1)
    {
    	for(int i = 0;i<ll_len(this)-1;i++)
    	{
    		for(int j=i+1;j<ll_len(this);j++)
    		{
    			pElementoI = ll_get(this, i);
    			pElementoJ = ll_get(this, j);
    			if((pFunc(pElementoI,pElementoJ) > 0 && order) || (pFunc(pElementoI,pElementoJ) < 0 && !order))
    			{
    				ll_set(this, i, pElementoJ);
    				ll_set(this, j, pElementoI);
    				returnAux = 0;
    			}
    		}
    	}
    }
    return returnAux;
}

int ll_sortBy2Func(LinkedList *this, int (*pFunc)(void*, void*),int (*pFunc2)(void*, void*), int criterio)
{

	void *pElement1;
	void *pElement2;

	int sizeOfList;
	int todoOk = 0;

	if (this != NULL && pFunc != NULL && (criterio == 1 || criterio == 0))
	{
		sizeOfList =  ll_len(this);
		for (int i = 0; i < sizeOfList -1; i++)
		{
			for (int j = i + 1; j < sizeOfList; j++)
			{
				pElement1 = ll_get(this, i);
				pElement2 = ll_get(this, j);

				if ((pFunc(pElement1, pElement2) > 0 && criterio)||(pFunc(pElement1, pElement2) < 0 && !criterio))
				{
					ll_set(this, i, pElement2);
					ll_set(this, j, pElement1);
				}
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
	LinkedList* nuevaLinked = NULL;
	void* pAux = NULL;
	int sizeLinked;

	if(this!=NULL && pFunc!=NULL)
	{
		nuevaLinked = ll_newLinkedList();

		if(nuevaLinked !=NULL)
		{
			sizeLinked = ll_len(this);

			for(int i = 0;i<sizeLinked;i++)
			{
				pAux = ll_get(this, i);
				if(pFunc(pAux))
				{

					if(ll_add(nuevaLinked, pAux))
					{
						ll_deleteLinkedList(nuevaLinked);
						nuevaLinked = NULL;
						break;
					}
				}
			}
			pAux = NULL;
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
			{
				pElement = ll_get(this, i);
				pElement = pFunc(pElement);
				if(pElement!=NULL)
				{
					ll_add(mappList, pElement);
				}
			}
		}
	}

	return mappList;
}
