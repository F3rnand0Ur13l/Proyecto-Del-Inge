#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "stdafx.h"

#define TAMTOKEN 50
#define NUMPALABRAS 7000

void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos) {
	FILE* fpDicc;
	char linea[7000];
	char palabraDetectada[TAMTOKEN];
	int i;
	int indicePD;
	iNumElementos = 0;

	fopen_s(&fpDicc, szNombre, "r");

	if (fpDicc != NULL) {
		indicePD = 0;
		int lectura;

		while ((lectura = fgetc(fpDicc)) != EOF) {
			for (i = 0; i < strlen(linea); i++) {
				if (linea[i] == ' ' || linea[i] == '\n' || linea[i] == '\t' || linea[i] == '\r') {
					if (indicePD > 0) {
						palabraDetectada[indicePD] = '\0';
						for (int k = 0; palabraDetectada[k] != '\0'; k++) {
							switch (palabraDetectada[k]) {
							case 'á': palabraDetectada[k] = 'a'; break;
							case 'é': palabraDetectada[k] = 'e'; break;
							case 'í': palabraDetectada[k] = 'i'; break;
							case 'ó': palabraDetectada[k] = 'o'; break;
							case 'ú': palabraDetectada[k] = 'u'; break;
							}
						}

						for (int k = 0; palabraDetectada[k] != '\0'; k++) {
							palabraDetectada[k] = tolower(palabraDetectada[k]);
						}

						int indiceExistente = -1;
						for (int j = 0; j < iNumElementos; j++) {
							if (strcmp(szPalabras[j], palabraDetectada) == 0) {
								indiceExistente = j;
							}
						}

						if (indiceExistente != -1) {
							iEstadisticas[indiceExistente]++;
						}
						else {
							strcpy_s(szPalabras[iNumElementos], TAMTOKEN, palabraDetectada);
							iEstadisticas[iNumElementos] = 1;
							iNumElementos++;
						}

						indicePD = 0;
					}
				}
				else {
					if (linea[i] != '(' && linea[i] != ')' && linea[i] != ',' && linea[i] != '.') {
						palabraDetectada[indicePD] = linea[i];
						indicePD++;
					}
				}
			}
		}

		fclose(fpDicc);

		for (int m = 0; m < iNumElementos - 1; m++) {
			for (int j = 0; j < iNumElementos - m - 1; j++) {
				if (strcmp(szPalabras[j], szPalabras[j + 1]) > 0) {
					char cambio[TAMTOKEN];
					strcpy_s(cambio, TAMTOKEN, szPalabras[j]);
					strcpy_s(szPalabras[j], TAMTOKEN, szPalabras[j + 1]);
					strcpy_s(szPalabras[j + 1], TAMTOKEN, cambio);
					int tempConteo = iEstadisticas[j];
					iEstadisticas[j] = iEstadisticas[j + 1];
					iEstadisticas[j + 1] = tempConteo;
				}
			}
		}
	}
	else {
		printf("\nNo se abrió el archivo.");
	}
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						//Palabra a clonar   palabra
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void ClonaPalabras(char* szPalabraLeida, char szPalabrasSugeridas[][TAMTOKEN], int& iNumSugeridas) {
	iNumSugeridas = 0;
	strcpy_s(szPalabrasSugeridas[iNumSugeridas++], szPalabraLeida);

	char aux[TAMTOKEN];

	// Itera sobre cada posición de la palabra original
	for (int p = 0; p < strlen(szPalabraLeida); p++) {
		// Itera sobre cada letra del alfabeto
		for (char letra = 'a'; letra <= 'z'; letra++) {
			// Clona la palabra cambiando la letra en la posición p
			strcpy_s(aux, TAMTOKEN, szPalabraLeida);
			aux[p] = letra;
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
		}
	}

	// Itera sobre cada posición de la palabra original
	for (int i = 0; i < strlen(szPalabraLeida); i++) {
		// Guarda la letra en la posición i
		aux[i] = szPalabraLeida[i];

		// Itera sobre cada letra del alfabeto
		for (char letra = 'a'; letra <= 'z'; letra++) {
			// Clona la palabra insertando la letra en la posición i
			aux[i] = letra;
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
		}
	}

	// Restaura la palabra original en la variable auxiliar
	strcpy_s(aux, szPalabraLeida);

	// Itera sobre cada posición de la palabra original
	for (int i = 0; i < strlen(szPalabraLeida) + 1; i++) {
		// Itera sobre cada letra del alfabeto
		for (char letra = 'a'; letra <= 'z'; letra++) {
			// Clona la palabra insertando la letra en la posición i
			aux[i] = letra;
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
		}
	}

	int contador = 0;

	// Itera sobre cada posición de la palabra original
	for (int i = 0; i < strlen(szPalabraLeida) && strlen(szPalabraLeida) != 1; i++) {
		// Itera sobre cada posición de la palabra original
		for (int j = 0; j < strlen(szPalabraLeida); j++) {
			if (j != i) {
				aux[contador++] = szPalabraLeida[j];
			}
		}

		aux[contador] = '\0';
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);

		strcpy_s(aux, szPalabraLeida);
		contador = 0;
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
void ListaCandidatas(
	char szPalabrasSugeridas[][TAMTOKEN],
	int iNumSugeridas,
	char szPalabras[][TAMTOKEN],
	int iEstadisticas[],
	int iNumElementos,
	char szListaFinal[][TAMTOKEN],
	int iPeso[],
	int& iNumLista)
{
	iNumLista = 0;

	// Comparar palabras sugeridas con palabras del diccionario
	for (int h = 0; h < iNumSugeridas; h++) {
		for (int u = 0; u < iNumElementos; u++) {
			if (strcmp(szPalabrasSugeridas[h], szPalabras[u]) == 0) {
				// Buscar en la lista final
				int iBandera = 1;
				for (int r = 0; r < iNumLista && iBandera; r++) {
					if (strcmp(szListaFinal[r], szPalabras[u]) == 0) {
						iBandera = 0;
					}
				}
				// Si no está en la lista final, agregar
				if (iBandera) {
					strcpy_s(szListaFinal[iNumLista], TAMTOKEN, szPalabrasSugeridas[h]);
					iPeso[iNumLista++] = iEstadisticas[u];
				}
			}
		}
	}

	// Ordenamiento de la lista final por peso
	for (int i = 0; i < iNumLista; i++) {
		for (int j = 0; j < iNumLista - 1; j++) {
			if (iPeso[j] < iPeso[j + 1]) {
				// Intercambiar
				char temp[TAMTOKEN];
				strcpy_s(temp, szListaFinal[j + 1]);
				strcpy_s(szListaFinal[j + 1], szListaFinal[j]);
				strcpy_s(szListaFinal[j], temp);
				int tempPeso = iPeso[j + 1];
				iPeso[j + 1] = iPeso[j];
				iPeso[j] = tempPeso;
			}
		}
	}
}

