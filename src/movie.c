#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "utn.h"
#include "LinkedList.h"
#include "controller.h"
#include "movie.h"

//CONSTRUCTORES
eMovie* Movie_new()
{
	eMovie* auxMovie;

	auxMovie = (eMovie*) malloc(sizeof(eMovie));

	if(auxMovie!=NULL)//INICIALIZO LOS CAMPOS DE LA STRUCT
	{
		auxMovie->id = 0;
		strcpy(auxMovie->title,"INVALID TITLE");  //[NO LAST NAME]
		auxMovie->rating = 0.0;
		strcpy(auxMovie->genero,"NN");
	}
	return auxMovie;
}

eMovie* Movie_newParametros(char* idStr,char* titleStr,char* generoStr,char* ratingStr)
{
	eMovie *this;

	this = Movie_new();//GUARDO LO QUE DEVUELVE LA FUNCION

	int auxId;
	float auxRating;

	auxId = atoi(idStr);
	auxRating = atof(ratingStr);

	if(this!=NULL && idStr!=NULL && titleStr!=NULL && generoStr!=NULL && ratingStr!=NULL)//VALIDO TODO
	{
		if(!(Movie_setId(this, auxId) &&
			Movie_setTitle(this, titleStr) &&
			Movie_setRating(this, auxRating) &&
			Movie_setGenero(this, generoStr)))//[VALIDACION DE CADA CAMPO]
		{
			Movie_delete(this);
			this=NULL;
		}
	}
	return this;
}

//DESTRUCTOR
void Movie_delete(eMovie* this)
{
	if(this!=NULL)
	{
		free(this);
	}
}

//SETTERS
int Movie_setTitle(eMovie* this,char* title)
{
	int todoOk = -1;
	if(this!=NULL && title!=NULL && strlen(title)<50 && strlen(title)>=2)
	{
		strlwr(title);
		title[0] = toupper(title[0]);
		strncpy(this->title,title,49);
		todoOk=1;
	}
	return todoOk;
}

int Movie_setId(eMovie* this,int id)
{
	int todoOk=-1;

	if(this!=NULL && id>=0)
	{
		this->id = id;
		todoOk=1;
	}

	return todoOk;
}

int Movie_setGenero(eMovie* this,char* genero)
{
	int todoOk = -1;
	if(this!=NULL && genero!=NULL && strlen(genero)<24  && strlen(genero)>=2)
	{
		strlwr(genero);
		genero[0] = toupper(genero[0]);
		strncpy(this->genero,genero,24);
		todoOk=1;
	}
	return todoOk;
}

int Movie_setRating(eMovie* this,float rating)
{
	int todoOk = 0;

	if (this != NULL && rating>=0 && rating <=10)
	{
		this->rating = rating;
		todoOk = 1;
	}
	return todoOk;
}

//GETTERS
int Movie_getTitle(eMovie* this,char* title)
{
	int todoOk=-1;
	if(this!=NULL && title!=NULL)
	{
		todoOk=1;
		strcpy(title,this->title);
	}
	return todoOk;
}

int Movie_getId(eMovie* this,int* id)
{
	int todoOk=-1;

	if(this!=NULL && id!=NULL)
	{
		*id = this->id;
		todoOk = 1;
	}
	return todoOk;
}

int Movie_getHigherId(eMovie* this,int* id)
{
    int todoOk = -1;

    if(this != NULL)
    {
       Movie_getId(this,id);
        todoOk = 0;
    }
    return todoOk;
}

int Movie_getRating(eMovie* this,float* rating)
{
	int todoOk = 0;

	if (this != NULL && rating != NULL)
	{
		*rating = this->rating;
		todoOk = 1;
	}
	return todoOk;
}

int Movie_getGenero(eMovie* this,char* genero)
{
	int todoOk=-1;
	if(this!=NULL && genero!=NULL)
	{
		todoOk=1;
		strcpy(genero,this->genero);
	}
	return todoOk;
}

//OTROS
int Movie_ShowOnlyOne(eMovie *eMovie)
{
	int todoOk=0;

	int id;
	char title[79];
	char genero[25];
	float rating;

	if(eMovie!=NULL)
	{
		Movie_getId(eMovie, &id);
		Movie_getTitle(eMovie, title);
		Movie_getRating(eMovie, &rating);
		Movie_getGenero(eMovie, genero);

		printf("|%4d |%-40s|    %15s    |          %2.1f              |\n",id,title,genero,rating);

		printf("|-----|----------------------------------------|-----------------------|---------------------------|\n");

		todoOk=1;
	}

	return todoOk;
}

//SORT
int Movie_sortByGenero(void* genero1,void* genero2)
{
	int todoOk = 0;

	eMovie* auxMovie1;
	eMovie* auxMovie2;

	if(genero1!=NULL && genero2!=NULL)
	{
		auxMovie1 = (eMovie*) genero1;
		auxMovie2 = (eMovie*) genero2;

		todoOk = strcmp(auxMovie1->genero,auxMovie2->genero);
	}

	return todoOk;
}


int Movie_sortByRating(void* rating1,void* rating2)
{
	int todoOk = 0;

	eMovie* auxMovie1;
	eMovie* auxMovie2;

	if(rating1!=NULL && rating2!=NULL)
	{
		auxMovie1 = (eMovie*) rating1;
		auxMovie2 = (eMovie*) rating2;

		if(auxMovie1->rating>auxMovie2->rating)
		{
			todoOk=1;
		}
		else if(auxMovie1->rating<auxMovie2->rating)
		{
			todoOk=-1;
		}
	}
	return todoOk;
}
