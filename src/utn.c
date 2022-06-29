#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



static int esNumerica(char* cadena, int limite);
static int getInt(int* pResultado);
static int esFlotante(char* cadena);
static int getFloat(float* pResultado);
static int getString(char* cadena, int longitud);
static int esNombre(char* cadena,int longitud);
static int getNombre(char* pResultado,int longitud);
static int esDescripcion(char* cadena,int longitud);
static int getDescripcion(char* pResultado, int longitud);

static int getString(char* cadena, int longitud)
{
	int retorno=-1;
	char bufferString[4096];

	if(cadena != NULL && longitud > 0)
	{
		fflush(stdin);
		if(fgets(bufferString,sizeof(bufferString),stdin) != NULL)
		{
			if(bufferString[strnlen(bufferString,sizeof(bufferString))-1] == '\n')
			{
				bufferString[strnlen(bufferString,sizeof(bufferString))-1] = '\0';
			}
			if(strnlen(bufferString,sizeof(bufferString)) <= longitud)
			{
				strncpy(cadena,bufferString,longitud);
				retorno=0;
			}
		}
	}
	return retorno;
}

static int getInt(int* pResultado)
{
    int retorno=-1;
    char bufferString[50];
    if(	pResultado != NULL &&
    	getString(bufferString,sizeof(bufferString)) == 0 &&
    	esNumerica(bufferString,sizeof(bufferString)))
	{
		retorno=0;
		*pResultado = atoi(bufferString) ;

	}
    return retorno;
}

static int esNumerica(char* cadena, int limite)
{
	int retorno = -1; // ERROR
	int i;
	if(cadena != NULL && limite > 0)
	{
		retorno = 1; // VERDADERO
		for(i=0;i<limite && cadena[i] != '\0';i++)
		{
			if(i==0 && (cadena[i] == '+' || cadena[i] == '-'))
			{
				continue;
			}
			if(cadena[i] < '0'||cadena[i] > '9')
			{
				retorno = 0;
				break;
			}

		}

	}
	return retorno;
}

int utn_getNumero(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos)
{
	int retorno = -1;
	int bufferInt;
	do
	{
		printf("%s",mensaje);
		if(	getInt(&bufferInt) == 0 &&
			bufferInt >= minimo &&
			bufferInt <= maximo)
		{
			retorno = 0;
			*pResultado = bufferInt;
			break;
		}
		printf("%s",mensajeError);
		reintentos--;
	}while(reintentos>=0);

	return retorno;
}

static int getFloat(float* pResultado)
{
    int retorno=-1;
    char buffer[64];

    if(pResultado != NULL)
    {
    	if(getString(buffer,sizeof(buffer))==0 && esFlotante(buffer))
    	{
			*pResultado = atof(buffer);
			retorno = 0;
		}
    }
    return retorno;
}

static int esFlotante(char* cadena)
{
	int i=0;
	int retorno = 1;
	int contadorPuntos=0;

	if(cadena != NULL && strlen(cadena) > 0)
	{
		for(i=0 ; cadena[i] != '\0'; i++)
		{
			if(i==0 && (cadena[i] == '-' || cadena[i] == '+'))
			{
				continue;
			}
			if(cadena[i] < '0' || cadena[i] > '9' )
			{
				if(cadena[i] == '.' && contadorPuntos == 0)
				{
					contadorPuntos++;
				}
				else
				{
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}

int utn_getNumeroFlotante(float* pResultado, char* mensaje, char* mensajeError, float minimo, float maximo, int reintentos)
{
	float bufferFloat;
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getFloat(&bufferFloat) == 0)
		{
			if(bufferFloat >= minimo && bufferFloat <= maximo)
			{
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}
		}
		printf("%s",mensajeError);
	}
	return retorno;
}

int  limpiarBarraN(char cadena[], int tam)
{
    int todoOk = 0;

    if(cadena != NULL && tam > 0)
    {
        for(int i=0; i < tam; i++)
        {
            if(cadena[i] == '\n')
            {
                cadena[i] = '\0';
                break;
            }
        }
        todoOk = 1;
    }
    return todoOk;
}

int convertFirstLetterStringUpper(char string1[])
{
	int todoOk = -1;

	if(string1!=NULL)
	{
		strlwr(string1);

		for(int i = 0; string1[i]!= '\0';i++)
		{
			if(i==0)
			{
				if((string1[i]>'a' && string1[i]<='z'))
				{
					string1[i] = string1[i]-32;
					continue;
				}
			}
			if(string1[i]== ' ')
			{
				i++;
				if((string1[i]>'a' && string1[i]<='z'))
				{
					string1[i] = string1[i]-32;
					continue;
				}
			}
			else
			{
				if(string1[i]>='A' && string1[i]<='Z')//TODAS LAS MAYUSCYLAS PASAN A MINUSCULAS
				{
					string1[i]=string1[i]+32;
				}
			}
		}
	}
	return todoOk;
}

static int getNombre(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer))==0 &&
    		esNombre(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

static int esNombre(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if((cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int utn_getNombre(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getNombre(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}

static int getDescripcion(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer))==0 &&
    		esDescripcion(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

static int esDescripcion(char* cadena,int longitud)
{
	int i=0;
	int retorno = 1;

	if(cadena != NULL && longitud > 0)
	{
		for(i=0 ; cadena[i] != '\0' && i < longitud; i++)
		{
			if(cadena[i] != '.' && cadena[i] != ' ' && (cadena[i] < 'A' || cadena[i] > 'Z' ) && (cadena[i] < 'a' || cadena[i] > 'z' ) && (cadena[i] < '0' || cadena[i] > '9' ) )
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int utn_getDescripcion(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getDescripcion(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}

static int getDni(char* pResultado, int longitud)
{
    int retorno=-1;
    char buffer[4096];

    if(pResultado != NULL)
    {
    	if(	getString(buffer,sizeof(buffer))==0 &&
    		esNumerica(buffer,sizeof(buffer)) &&
			strnlen(buffer,sizeof(buffer))<longitud)
    	{
    		strncpy(pResultado,buffer,longitud);
			retorno = 0;
		}
    }
    return retorno;
}

int utn_getDni(char* pResultado, int longitud,char* mensaje, char* mensajeError, int reintentos)
{
	char bufferString[4096];
	int retorno = -1;
	while(reintentos>=0)
	{
		reintentos--;
		printf("%s",mensaje);
		if(getDni(bufferString,sizeof(bufferString)) == 0 && strnlen(bufferString,sizeof(bufferString)) < longitud )
		{
			strncpy(pResultado,bufferString,longitud);
			retorno = 0;
			break;
		}
		printf("%s",mensajeError);
	}
	return retorno;
}

int getGender(char message[],char errorMessage[],char userGender[])
{
	int todoOk = -1;

	char auxSex;

	if(userGender!=NULL && message!=NULL && errorMessage!=NULL)
	{
		printf("%s ", message);
		fflush(stdin);
		scanf("%c", &auxSex);
		auxSex=toupper(auxSex);
		while(auxSex!='F' && auxSex!='M' && auxSex!='B')
		{
			printf("%s ", errorMessage);
			fflush(stdin);
			scanf("%c", &auxSex);
			auxSex=toupper(auxSex);
		}
		todoOk=0;
	}

	*userGender = auxSex;

	return todoOk;
}

char getChar(char mensaje[])
{
    char auxiliar;
    printf("%s",mensaje);
    fflush(stdin);
    scanf("%c",&auxiliar);
    auxiliar=toupper(auxiliar);
    return auxiliar;
}

void getStringAlfanumerica(char mensaje[],char input[])
{
    printf("%s",mensaje);
    fflush(stdin);
    fgets(input,300,stdin);
    limpiarBarraN(input,300);
}


int getValidStringAlpha(char requestMessage[],char errorMessageLenght[],char input[], int lowLimit,int maxLenght)
{
    int retorno=-1;
    char buffer[999];

    while(1)
    {
    	getStringAlfanumerica(requestMessage, buffer);
        if(strlen(buffer) > maxLenght || strlen(buffer) < lowLimit)
        {
            printf ("%s",errorMessageLenght);
            continue;

        }
        retorno=0;
        strcpy(input,buffer);
        break;
    }

     return retorno;
}


int esAlfaNumerico(char string[],char message[],int maxLimit)
{
	int todoOk = 0;
	int i = 0;

	if(string!=NULL)
	{
		getStringAlfanumerica(message, string);
		while(string[i]!='\0')
		{
			if((string[i]!=' ')&&(string[i]<'a' || string[i]>'z')&&(string[i]<'A'||string[i]>'Z')&&(string[i]<'0' || string[i]>'9') && (string[i]!='.'))
			{
				todoOk = 0;
				i++;
			}
			else if((string[i]>maxLimit))
			{
				printf("\nSE EXCEDIO EL LIMITE");
				todoOk = 1;
			}
		}
	}
	return todoOk;
}

int getUserConfirmation(char* confirUser,char message[],char errorMessage[])
{
	int todoOk = -1;

	char auxConf;

	if(confirUser!=NULL && message!=NULL && errorMessage!=NULL)
	{
		printf("%s ", message);
		fflush(stdin);
		scanf("%c", &auxConf);
		auxConf=tolower(auxConf);
		while(auxConf!='s' && auxConf!='n')
		{
			printf("%s ", errorMessage);
			fflush(stdin);
			scanf("%c", &auxConf);
			auxConf=tolower(auxConf);
		}

		*confirUser = auxConf;
		todoOk=0;
	}

	return todoOk;
}

void limpioPantalla()
{
	printf("\n\n\n\n\n");
}

void showMessage(char string[])
{
	printf("%s\n",string);
}

int getUserMenuOption(char* confirUser,char message[],char errorMessage[])
{
	int todoOk = -1;

	char auxConf;

	if(confirUser!=NULL && message!=NULL && errorMessage!=NULL)
	{
		printf("%s ", message);
		fflush(stdin);
		scanf("%c", &auxConf);
		auxConf=toupper(auxConf);
		while(auxConf!='A' && auxConf!='B' && auxConf!='C' && auxConf!='D'  && auxConf!='E')
		{
			printf("%s ", errorMessage);
			fflush(stdin);
			scanf("%c", &auxConf);
			auxConf=toupper(auxConf);
		}

		*confirUser = auxConf;
		todoOk=0;
	}

	return todoOk;
}


int getUserMenuOptionInt(int* confirUser,char message[],char errorMessage[],int minOption,int maxOption)
{
	int todoOk = -1;

	int auxConf;

	if(confirUser!=NULL && message!=NULL && errorMessage!=NULL)
	{
		printf("%s ", message);
		scanf("%d", &auxConf);
		while(auxConf<minOption || auxConf>maxOption)
		{
			printf("%s ", errorMessage);
			scanf("%d", &auxConf);
		}
		*confirUser = auxConf;
		todoOk=0;
	}
	return todoOk;
}
