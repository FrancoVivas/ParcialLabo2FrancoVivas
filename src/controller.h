#include "LinkedList.h"

#ifndef CONTROLLER_H_
#define CONTROLLER_H_



#endif /* CONTROLLER_H_ */

int controller_saveAsText(char *path, LinkedList *this);
int controller_saveAsCSV(FILE *path , LinkedList *pArrayMovies);
int controller_loadFromText(char* path , LinkedList* pArrayMovies);
int controller_ListMovies(LinkedList* pArrayMovies);
void* controller_CalcularRating(void* pMovie);
void* controller_CalcularGenero(void* pMovie);
int controller_filterByGenre(LinkedList* pArrayMovies);
