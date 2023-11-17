/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-
	Computadoras y programacion.
	(c) Ponga su nombre y numero de cuenta aqui.

	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.

******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
//#define DEPURAR 1

//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	FILE* fpDicc;
	char linea[7000];
	char palabraDetectada[TAMTOKEN];
	int i;
	int indicePD;
	iNumElementos = 0;
	fopen_s(&fpDicc, szNombre, "r");
	if (fpDicc != NULL)
	{
		indicePD = 0;
		while (fgets(linea,sizeof(linea),fpDicc) != NULL)
		{
			for (i = 0; i < strlen(linea); i++)
			{
				if (linea[i] == ' '|| linea[i] == '\n' || linea[i] == '\t' || linea[i] == '\r')
				{
					if (indicePD > 0)
					{
						palabraDetectada[indicePD] = '\0';
						for (int k = 0; palabraDetectada[k] != '\0'; k++)
						{
							switch (palabraDetectada[k])
							{
							case 'á': palabraDetectada[k] = 'a'; break;
							case 'é': palabraDetectada[k] = 'e'; break;
							case 'í': palabraDetectada[k] = 'i'; break;
							case 'ó': palabraDetectada[k] = 'o'; break;
							case 'ú': palabraDetectada[k] = 'u'; break;
							}
							palabraDetectada[k] = towlower(palabraDetectada[k]);
						}
						//Palabras Repetidas
						int indiceExistente = -1;
						for (int j = 0; j < iNumElementos && indiceExistente == -1; j++)
						{
							if (strcmp(szPalabras[j], palabraDetectada) == 0)
							{
								indiceExistente = j;
							}
						}
						if (indiceExistente != -1)
						{
							iEstadisticas[indiceExistente]++;
						}
						else
						{
							strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabraDetectada);
							iEstadisticas[iNumElementos] = 1;
							iNumElementos++;
						}
						indicePD = 0;
					}
				}
				else
				{
					if (linea[i] != '(' && linea[i] != ')' && linea[i] != ',' && linea[i] != '.')
					{
						palabraDetectada[indicePD] = linea[i];
						indicePD++;
					}
				}
			}

		}
		fclose(fpDicc);
		//Ordenamiento
		for (int i = 0; i < iNumElementos - 1; i++)
		{
			for (int j = 0; j < iNumElementos - i - 1; j++)
			{
				if (strcmp(szPalabras[j], szPalabras[j + 1]) > 0)
				{
					//Intercambiar 
					char temp[TAMTOKEN];
					strcpy_s(temp, TAMTOKEN, szPalabras[j]);
					strcpy_s(szPalabras[j], TAMTOKEN, szPalabras[j + 1]);
					strcpy_s(szPalabras[j + 1], TAMTOKEN, temp);
				}
			}
		}
	}
	else
	{
		printf("\nNo se abrio el archivo.");
	}
}

/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int& iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su código
	strcpy(szListaFinal[0], szPalabrasSugeridas[0]); //la palabra candidata
	iPeso[0] = iEstadisticas[0];			// el peso de la palabra candidata

	iNumLista = 1;							//Una sola palabra candidata
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char* szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int& iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su código
	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}