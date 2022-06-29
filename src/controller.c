#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utn.h"
#include "LinkedList.h"
#include "parser.h"
#include "informes.h"
#include "movie.h"


//LOAD FILE
int controller_loadFromText(char* path , LinkedList* pArrayMovies)
{
	int todoOk=0;

	FILE* pFile;

	pFile=fopen(path, "r");

	if(pFile != NULL)
	{
		parser_MoviesFromText(pFile, pArrayMovies);
		fclose(pFile);
		todoOk=1;
	}

    return todoOk;
}

//SAVE FILE
int controller_saveAsCSV(FILE *path , LinkedList *pArrayMovies)
{
	int retorno=-1;
	int i;

	eMovie *pAuto;
	int id;
	char title[79];
	char genre[25];
	float rating;
	int sizeOfList;
	int flagFantasma = 1;

	if(pArrayMovies != NULL && path != NULL)
	{
		retorno=0;
		sizeOfList = ll_len(pArrayMovies);
		for(i=0;i<sizeOfList;i++)
		{
			//CARGAMOS INFORMACION MEDIANTE GETTERS
			pAuto=(eMovie*)ll_get(pArrayMovies,i);
            if(pAuto!=NULL)//PUEDE DEVOLVER NULL
            {
               Movie_getId(pAuto, &id);
               Movie_getTitle(pAuto, title);
               Movie_getGenero(pAuto, genre);
               Movie_getRating(pAuto, &rating);
              //LO GUARDO CON UN ENCABEZADO PARA QUE NO ME PISE EL PRIMER ELEMENTO AL REABRIRLO
              if(flagFantasma)
              {
        		fprintf(path, "%s,%s,%s,%s\n", "ID", "TITLE", "GENRE", "RATING");
        		flagFantasma = 0;
              }
    			fprintf(path,"%d,%s,%s,%f\n",id,title,genre,rating);
            }
		}
	}
	return retorno;
}

int controller_saveAsText(char *path, LinkedList *this)
{
	int todoOk = 0;
	FILE *fpArchivo = fopen(path, "w"); // abro el archivo

	if (fpArchivo != NULL && controller_saveAsCSV(fpArchivo, this))
	{ //si el archivo no es null y pude escribir, retorno 1
		todoOk = 1;
	}
	fclose(fpArchivo); // cierro el archivo.
	ll_clear(this); //vacio el array
	return todoOk;
}

//MOVIE RELATED
int controller_ListMovies(LinkedList* pArrayMovies)
{
	int todoOk = 0;

	eMovie *pAuxMovie;
	int sizeOf;

	if(pArrayMovies==NULL)
	{
		printf("\nERROR!");
	}
	else
	{
		if(ll_isEmpty(pArrayMovies))
		{//se verifica que la lista no este vacia o en caso de abrir un archivo filtrado y buscar algun tipo
		//avise que no encontro ese tipo...
		//	printf("\nNO MOVIES REGISTERED TO SHOW THE LIST!\n");
			todoOk =2;
	    }
		else
		{
			printf("\n\n");
			printf("|--------------------------------------------------------------------------------------------------|\n");
			printf("|				       MOVIES   LIST                                               | \n");
			printf("|--------------------------------------------------------------------------------------------------|\n");
			printf("|  ID |	           TITLE                       |	   GENRE       |         RATING            |\n");
			printf("|-----|----------------------------------------|-----------------------|---------------------------|\n");
			todoOk=1;
			sizeOf = ll_len(pArrayMovies);
			for(int i=0;i<sizeOf;i++)
			{
				pAuxMovie = (eMovie*) ll_get(pArrayMovies, i);
				if(pAuxMovie!=NULL)//PUEDE DEVOLVER NULL
				{
					Movie_ShowOnlyOne(pAuxMovie);
				}
			}
		}
	}
    return todoOk;
}

void* controller_CalcularRating(void* pMovie)
{
	int min = 10;
	int max = 100;
	float rating = -1;
	eMovie* auxMovie = NULL;

	if(pMovie!=NULL)
	{
		auxMovie = (eMovie*) pMovie;
		rating = (float)((rand()% (max - min +1))+ min) / 10;
		Movie_setRating(auxMovie, rating);
	}

	return auxMovie;
}

void* controller_CalcularGenero(void* pMovie)
{
	int min = 1;
	int max = 4;
	int genero = -1;
	char desc[25];
	eMovie* auxMovie = NULL;

	if(pMovie!=NULL)
	{
		auxMovie = (eMovie*) pMovie;
		genero = rand() % (max - min +1) + min;
		if(genero==1)
		{
			strcpy(desc,"DRAMA");
			Movie_setGenero(auxMovie, desc);
		}
		else if(genero==2)
		{
			strcpy(desc,"COMEDIA");
			Movie_setGenero(auxMovie, desc);
		}
		else if(genero == 3)
		{
			strcpy(desc,"ACCION");
			Movie_setGenero(auxMovie, desc);
		}
		else
		{
			strcpy(desc,"TERROR");
			Movie_setGenero(auxMovie, desc);
		}
	}
	return auxMovie;
}


//FILTRADO

int controller_filterByGenre(LinkedList* pArrayMovies)
{
	int todoOk = 0;

	LinkedList* filteredList = ll_newLinkedList();

	if(pArrayMovies!=NULL)
	{
		switch(showOptionMenuFilter())
		{
			case 1://DRAMA
				filteredList = ll_filter(pArrayMovies,filterByDramaGenre);
				if(filteredList!=NULL)
				{
					if(controller_ListMovies(filteredList) == 1)
					{
						if(controller_saveAsText("DramaGenre.csv", filteredList)==0)
						{
							printf("\nLA LISTA DE PELICULAS DE DRAMA FUERON GUARDADAS CON EXITO!");
							todoOk=1;
						}
					}
					else if(controller_ListMovies(filteredList) == 2)
					{
						printf("\nNO HAY PELICULAS DE DRAMA REGISTRADAS EN LA LISTA!\n");
					}
					ll_deleteLinkedList(filteredList);
				}
				break;
				case 2://COMEDIA
					filteredList = ll_filter(pArrayMovies, filterByComediaGenre);
					if(filteredList!=NULL)
					{
						if(controller_ListMovies(filteredList) == 1)
						{
							if(controller_saveAsText("ComediaGenre.csv", filteredList)==0)
							{
								printf("\nLA LISTA DE PELICULAS DE COMEDIA FUERON GUARDADAS CON EXITO!");
								todoOk=1;
							}
						}
						else if(controller_ListMovies(filteredList) == 2)
						{
							printf("\nNO HAY PELICULAS DE COMEDIA REGISTRADAS EN LA LISTA!\n");
						}
						ll_deleteLinkedList(filteredList);
					}
				break;
				case 3://ACCION
					filteredList = ll_filter(pArrayMovies, filterByAccionGenre);
					if(filteredList!=NULL)
					{
						if(controller_ListMovies(filteredList) == 1)
						{
							if(controller_saveAsText("AccionGenre.csv", filteredList)==0)
							{
								printf("\nLA LISTA DE PELICULAS DE ACCION FUERON GUARDADAS CON EXITO!");
								todoOk=1;
							}
						}
						else if(controller_ListMovies(filteredList) == 2)
						{
							printf("\nNO HAY PELICULAS DE ACCION REGISTRADAS EN LA LISTA!\n");
						}
						ll_deleteLinkedList(filteredList);
					}
				break;
				default://TERROR
					filteredList = ll_filter(pArrayMovies, filterByTerrorGenre);
					if(filteredList!=NULL)
					{
						if(controller_ListMovies(filteredList) == 1)
						{
							if(controller_saveAsText("TerrorGenre.csv", filteredList)==0)
							{
								printf("\nLA LISTA DE PELICULAS DE TERROR FUERON GUARDADAS CON EXITO!");
								todoOk=1;
							}
						}
						else if(controller_ListMovies(filteredList) == 2)
						{
							printf("\nNO HAY PELICULAS DE TERROR REGISTRADAS EN LA LISTA!\n");
						}
						ll_deleteLinkedList(filteredList);
					}
				break;
			}
	}
	return todoOk;
}
