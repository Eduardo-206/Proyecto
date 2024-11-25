/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion. 
	(Vilchis Avila Mario Eduardo 322253896)
	
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.
	
******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario	
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void	Diccionario			(char *szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int &iNumElementos)
{

	//Sustituya estas lineas por su código
	FILE* diccionario;
	char szNombre[TAMTOKEN];
	char szPalabras[98000][TAMTOKEN];
	int iEstadisticas[98000];
	int numElementos = 0;

	printf("Archivo para el diccionario: ");
	fgets(szNombre, TAMTOKEN, stdin);
	szNombre[strcspn(szNombre, "\n")] = '\0';
	diccionario = fopen(szNombre, "r");

	if (diccionario == NULL) {
		printf("Error al abrir el archivo.\n");
		return 1;
	}

	char* palabra;
	while (fgets(szPalabras[numElementos], TAMTOKEN, diccionario)) {
		szPalabras[numElementos][strcspn(szPalabras[numElementos], "\n")] = '\0';
		palabra = strtok(szPalabras[numElementos], " \t\n");

		while (palabra != NULL) {
			int pe;
			for (pe = 0; pe < numElementos; pe++) {
				if (strcmp(palabra, szPalabras[pe]) == 0) {
					iEstadisticas[pe]++;
					break;
				}
			}

			if (pe == numElementos) {
				strcpy(szPalabras[numElementos], palabra);
				iEstadisticas[numElementos] = 1;
				numElementos++;
			}

			palabra = strtok(NULL, " \t\n");
		}
	}
	int pe;
	for (pe = 0; pe < numElementos; pe++) {
		printf("%s %d\n", szPalabras[pe], iEstadisticas[pe]);
	}

	fclose(diccionario);
	return 0;
	iNumElementos=1;
	strcpy(szPalabras[0],"AquiVaElDiccionario");
	iEstadisticas[0] = 1; // la primer palabra aparece solo una vez.
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
void	ListaCandidatas		(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
{

	//Sustituya estas lineas por su código

	iNumLista = 0; 

	// Percorre cada palavra sugerida
	for (int i = 0; i < iNumSugeridas; i++) {
		for (int j = 0; j < iNumElementos; j++) {
			if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0) {
				strcpy(szListaFinal[iNumLista], szPalabrasSugeridas[i]);
				iPeso[iNumLista] = iEstadisticas[j];
				iNumLista++;
			}
		}
	}

	strcpy(szListaFinal[0], szPalabrasSugeridas[ 0] ); //la palabra candidata
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
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
{
	//Sustituya estas lineas por su código
	char letras[32] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	letras[27] = 160;
	letras[28] = 130;
	letras[29] = 161;
	letras[30] = 162;
	letras[31] = 163;
	letras[32] = 164;

	int len = strlen(szPalabraLeida);
	int numInsercoes = 2;

	int indiceSugerencia = 0;

	for (int i = 0; i < len; i++) {
		for (int j = 0; j < 32; j++) {
			strcpy(szPalabrasSugeridas[indiceSugerencia], szPalabraLeida);
			szPalabrasSugeridas[indiceSugerencia][i] = letras[j];
			indiceSugerencia++;
		}
	}

	for (int in = 0; in <= len; in++) {
		for (int ji = 0; ji < numInsercoes; ji++) {
			for (int ki = 0; ki < 33; ki++) {
				strcpy(szPalabrasSugeridas[indiceSugerencia], szPalabraLeida);
				memmove(&szPalabrasSugeridas[indiceSugerencia][in + ji + 1], &szPalabrasSugeridas[indiceSugerencia][in + ji], len - in - ji);
				szPalabrasSugeridas[indiceSugerencia][in + ji] = letras[ki];
				indiceSugerencia++;
			}
		}
	}

	iNumSugeridas = indiceSugerencia;

	strcpy(szPalabrasSugeridas[0], szPalabraLeida); //lo que sea que se capture, es sugerencia
	iNumSugeridas = 1;							//Una sola palabra sugerida
}
