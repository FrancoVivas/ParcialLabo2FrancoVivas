#include "LinkedList.h"

#ifndef CONTROLLER_H_
#define CONTROLLER_H_



#endif /* CONTROLLER_H_ */

//FILES
/**
 * @fn int controller_saveAsText(char*, LinkedList*)
 * @brief guarda un archivo en formato texto
 *
 * @param path
 * @param this
 * @return
 */
int controller_saveAsText(char *path, LinkedList *this);

/**
 * @fn int controller_saveAsCSV(FILE*, LinkedList*)
 * @brief guarda un archivo como un csv con encabezado para no pisar el primer elemento
 * 		  al reabrirlo
 *
 * @param path
 * @param pArrayMovies
 * @return
 */
int controller_saveAsCSV(FILE *path , LinkedList *pArrayMovies);

/**
 * @fn int controller_loadFromText(char*, LinkedList*)
 * @brief carga un archivo de texto
 *
 * @param path
 * @param pArrayMovies
 * @return
 */
int controller_loadFromText(char* path , LinkedList* pArrayMovies);

//MOVIE RELATED
/**
 * @fn int controller_ListMovies(LinkedList*)
 * @brief lista todos los elementos de la lista
 *
 * @param pArrayMovies
 * @return
 */
int controller_ListMovies(LinkedList* pArrayMovies);

/**
 * @fn void controller_CalcularRating*(void*)
 * @brief calcula el rating de las peliculas de forma aleatoria
 *
 * @param pMovie
 */
void* controller_CalcularRating(void* pMovie);

/**
 * @fn void controller_CalcularGenero*(void*)
 * @brief calcula un numero aleatorio para las peliculas y les asigna un genero
 *
 * @param pMovie
 */
void* controller_CalcularGenero(void* pMovie);

//FILTRO
/**
 * @fn int controller_filterByGenre(LinkedList*)
 * @brief filtra a las peliculas por el genero elegido y las guarda en un archivo igual al original
 * 		  (formato .csv)
 *
 * @param pArrayMovies
 * @return
 */
int controller_filterByGenre(LinkedList* pArrayMovies);
