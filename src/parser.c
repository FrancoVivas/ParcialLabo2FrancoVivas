#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utn.h"
#include "LinkedList.h"
#include "movie.h"


int parser_MoviesFromText(FILE* pFile , LinkedList* pArrayMovies)
{
	int todoOk = 0;

	eMovie *pAuxMovie;
	char auxId[5000];
	char auxTitle[5000];
	char auxGenero[5000];
	char auxRating[5000];

	int elementoUno = 1;

	if(pFile!=NULL)
	{
		while (!feof(pFile))
		{

			if(elementoUno)
			{
				fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", auxId, auxTitle,
						auxGenero,auxRating);
				elementoUno = 0;
			}
			fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", auxId, auxTitle,
					auxGenero,auxRating);

			pAuxMovie = Movie_newParametros(auxId, auxTitle, auxGenero, auxRating);

			if(pAuxMovie!=NULL)
			{
				ll_add(pArrayMovies, pAuxMovie);
				todoOk=1;
			}
		}
	}
	 return todoOk;
}
