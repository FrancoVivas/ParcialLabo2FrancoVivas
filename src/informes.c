#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utn.h"
#include "LinkedList.h"
#include "controller.h"
#include "movie.h"

int showOptionMenuFilter()
{
	int opcion;
	printf("\n___________________________________________________");
	printf("\n                                                   |");
	printf("\n            FILTRAR MOVIES POR GENERO              |\n");
	printf("___________________________________________________|\n");
	printf("__________________________");
	printf("\n|1)GENERO DRAMA           |\n|"
			"2)GENERO COMEDIA         |\n|"
			"3)GENERO ACCION          |\n|"
			"4)GENERO TERROR          |\n");
	printf("|_________________________|");
	utn_getNumero(&opcion, "\nINGRESA UNA OPCION: ", "\n[VALOR INVALIDO, REINTENTA]: ", 1,4, 10);

	return opcion;
}


int filterByDramaGenre(void* pElement)
{
	int todoOk = 0;

	if(!strcmp(((eMovie*) pElement)->genero,"Drama"))
	{
		todoOk = 1;
	}
	return todoOk;
}

int filterByComediaGenre(void* pElement)
{
	int todoOk = 0;

	if(!strcmp(((eMovie*) pElement)->genero,"Comedia"))
	{
		todoOk = 1;
	}
	return todoOk;
}

int filterByAccionGenre(void* pElement)
{
	int todoOk = 0;

	if(!strcmp(((eMovie*) pElement)->genero,"Accion"))
	{
		todoOk = 1;
	}
	return todoOk;
}

int filterByTerrorGenre(void* pElement)
{
	int todoOk = 0;

	if(!strcmp(((eMovie*) pElement)->genero,"Terror"))
	{
		todoOk = 1;
	}
	return todoOk;
}
