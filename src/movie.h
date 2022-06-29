#ifndef MOVIE_H_
#define MOVIE_H_

typedef struct{

	int id;
	char title[80];
	char genero[25];
	float rating;

}eMovie;

#endif /* MOVIE_H_ */

eMovie* Movie_new();
eMovie* Movie_newParametros(char* idStr,char* titleStr,char* generoStr,char* ratingStr);
void Movie_delete(eMovie* this);
int Movie_setTitle(eMovie* this,char* title);
int Movie_setRating(eMovie* this,float rating);
int Movie_setGenero(eMovie* this,char* genero);
int Movie_setId(eMovie* this,int id);
int Movie_getTitle(eMovie* this,char* title);
int Movie_getId(eMovie* this,int* id);
int Movie_getRating(eMovie* this,float* rating);
int Movie_getHigherId(eMovie* this,int* id);
int Movie_getGenero(eMovie* this,char* genero);
int Movie_ShowOnlyOne(eMovie *eMovie);
int Movie_sortByGenero(void* genero1,void* genero2);
int Movie_sortByRating(void* rating1,void* rating2);
