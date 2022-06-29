#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utn.h"
#include "LinkedList.h"
#include "controller.h"
#include "movie.h"

#define STATE_FILE_OPEN 1
#define STATE_FILE_CLOSED 0

int menu();

void pFunction(char* messageError1,char* messageError2,char* messageSucess,int* flag,int flagValue,
				LinkedList* array,int(*pFunction)(LinkedList*));

int menu()
{
	int opcion;

	printf("\n__________________________________________________________________________");
	printf("\n                                                                          |");
	printf("\n                       BIENVENIDO A CINEPOLIS                              |\n");
	printf("__________________________________________________________________________|\n");
	printf("_____________________________________________________________");
	printf("\n|1)CARGAR ARCHIVO                                            |\n|"
			"2)IMPRIMIR LISTA                                            |\n|"
			"3)ASIGNAR RATING                                            |\n|"
			"4)ASIGNAR GENERO                                            |\n|"
			"5)FILTRAR POR GENERO                                        |\n|"
			"6)ORDENAR PELICULAS                                         |\n|"
			"7)GUARDAR PELICULAS                                         |\n|"
			"8)EXIT APP                                                  |\n");
	printf("|____________________________________________________________|");
	utn_getNumero(&opcion, "\nINGRESA UNA OPCION: ", "\n[VALOR INVALIDO, REINTENTA.] ", 1, 8, 10);
	return opcion;
}

void pFunction(char* messageError1,char* messageError2,char* messageSucess,int* flag,int flagValue,
				LinkedList* array,int(*pFunction)(LinkedList*)){
	int flagForCompare = *flag;

	if(flagForCompare==flagValue)
	{
		printf("\n%s\n",messageError1);
	}else
	{
		if (!pFunction(array))
		{
			printf("\n%s\n",messageError2);
		}
		else
		{
			printf("\n%s\n",messageSucess);
		}
	}
}


int main(void) {
	setbuf(stdout,NULL);

	srand(time(NULL));

	char opcion = 'n';
	int fileState = 0;
	int generated = 0;
	char path[8000];

	LinkedList* listaPrincipal = ll_newLinkedList();

	if(listaPrincipal!=NULL)
	{
		if(ll_isEmpty(listaPrincipal)){
	   	    printf("\n[LISTA INICIALIZADA]");
	    }
		do
		{
			switch(menu())
			{
				case 1:
					limpioPantalla();
					if(fileState==1)
					{
						printf("\n[YA HAY UN ARCHIVO ABIERTO!]\n");
					}
					else
					{
						getValidStringAlpha("\nINGRESA EL NOMBRE DEL ARCHIVO: ", "\n[VALORES INVALIDOS, REINTENTA]: ", path, 3, 30);
						if(controller_loadFromText(path, listaPrincipal) == 1)
						{
							printf("\nEL ARCHIVO FUE ABIERTO CON EXITO!\n");
							fileState = 1;
						}
						else
						{
							printf("\n[OCURRIO UN ERROR AL INTENTAR ABRIR EL ARCHIVO!]\n");
						}
					}
					system("Pause");
				break;
				case 2:
					limpioPantalla();
					pFunction("\nPRIMERO DEBES DE CARGAR EL ARCHIVO!",
							"\nOCURRIO UN ERROR AL INTENTAR MOSTRAR LA LISTA, REINTENTA! ",
							"\nLA LISTA FUE MOSTRADA CON EXITO!",
							&fileState, STATE_FILE_CLOSED, listaPrincipal, controller_ListMovies);
					system("Pause");
				break;
				case 3:
					if(fileState == 1)
				 	 {
				 	 	listaPrincipal = ll_map(listaPrincipal, controller_CalcularRating);
						if(listaPrincipal!=NULL)
						{
							controller_ListMovies(listaPrincipal);
							printf("\n[RATINGS ASIGNADOS CON EXITO!]\n");
							generated = 1;
						}
						else
						{
							printf("\n[OCURRIO UN ERROR AL INTENTAR MAPPEAR LA LISTA!]\n");
						}
				 	 }
				 	 else
				 	 {
				 	 	 printf("\n[PRIMERO DEBES DE CARGAR EL ARCHIVO!]\n");
				 	 }
					system("Pause");
				break;
				case 4:
						if(fileState == 1 && generated == 1)
					 	 {
					 	 	listaPrincipal = ll_map(listaPrincipal, controller_CalcularGenero);
							if(listaPrincipal!=NULL)
							{
								controller_ListMovies(listaPrincipal);
								printf("\n[GENEROS ASIGNADOS CON EXITO!]\n");
								generated = 2;
							}
							else
							{
								printf("\n[OCURRIO UN ERROR AL INTENTAR MAPPEAR LA LISTA!]");
							}
					 	 }
					 	 else if(fileState==0)
					 	 {
					 	 	 printf("\n[PRIMERO DEBES DE CARGAR EL ARCHIVO!]\n");
					 	 }
					 	 else
					 	 {
					 		printf("\n[PRIMERO DEBES DE ASIGNAR EL RATING A LAS PELICULAS DE LA LISTA]\n");
					 	 }
						system("Pause");
				break;
				case 5:
					limpioPantalla();
					if(generated==2 || generated == 3)
					{
						pFunction("\nPRIMERO DEBES DE CARGAR EL ARCHIVO!",
								"\nOCURRIO UN ERROR AL INTENTAR FILTRAR LA LISTA, REINTENTA! ",
								"\nLA LISTA FUE FILTRADA CON EXITO!",
								&fileState, STATE_FILE_CLOSED, listaPrincipal, controller_filterByGenre);
					}
					else
					{
						printf("\n[PRIMERO DEBES DE ASIGNAR EL RATING DE LAS PELICULAS Y SU GENERO!]\n");
					}
					system("Pause");
				break;
				case 6:
					if(generated == 2)
					{
						if(listaPrincipal!=NULL)
						{
							ll_sortBy2Func(listaPrincipal, Movie_sortByGenero, Movie_sortByRating, 0);
							if(listaPrincipal!=NULL)
							{
								controller_ListMovies(listaPrincipal);
								generated =3;
								printf("\n[LA LISTA FUE SWAPPEADA CON EXITO!]\n");
							}
						}
					}
					else
					{
						printf("\n[PRIMERO DEBES DE ASIGNAR EL RATING DE LAS PELICULAS Y SU GENERO!]\n");
					}
					system("Pause");
				break;
				case 7:
					limpioPantalla();
					if(fileState==1 && generated==3)
					{
						if(!controller_saveAsText("Ordenada.txt", listaPrincipal))
						{
							fileState = 0;
							printf("\nEL ARCHIVO FUE GUARDADO Y CERRADO CON EXITO!\n");
						}
						else
						{
							printf("\n[OCURRIO UN ERROR AL INTENTAR GUARDAR EL ARCHIVO!]\n");
						}
					}
					else if(fileState==0)
					{
						printf("\n[PRIMERO DEBES DE CARGAR EL ARCHIVO!]\n");
					}
					else
					{
						printf("\n[DEBES DE GENERAR LA LISTA SWAPPEADA PARA PODER GUARDAR EL ARHIVO!]\n");
					}
					system("Pause");
				break;
				case 8:
					limpioPantalla();
					if(fileState!=0)
					{
						printf("\n[ANTES DE SALIR DEBES DE GUARDAR EL ARCHIVO!]\n");
					}
					else
					{
						getUserConfirmation(&opcion, "\nDESEA CERRAR LA APLICACION (S/N)?: ", "\nVALORES INVALIDOS, REINTENTA (S/N)!: ");
						if(opcion=='s')
						{
							printf("DECIDIO CERRAR LA APLICACION.....\n");
							ll_deleteLinkedList(listaPrincipal);
						}
						else
						{
							printf("DECIDIO SEGUIR USANDO LA APLICACION!\n");
						}
					}
					system("Pause");
				break;
			}
		}while(opcion!='s');
	}

	return EXIT_SUCCESS;
}
