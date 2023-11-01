// corrector.h
#define TAMTOKEN 50
void Diccionario(
    char* szNombre, //Nombre del archivo, desde donde se lee el diccionario
    char szPalabras[][TAMTOKEN], //Lista de palabras del diccionario
    int iEstadisticas[], //Numero de veces que aparece la palabra en el archivo
    int& iNumElementos //Numero de elementos
);

void ClonaPalabras(
    char* szPalabraLeida, //Palabra a clonar
    char szPalabrasSugeridas[][TAMTOKEN], //Lista final de palabras clonadas
    int& iNumSugeridas //Numero de elementos en la lista
);

void ListaCandidatas(
    char szPalabrasSugeridas[][TAMTOKEN], //Lista de palabras clonadas
    int iNumSugeridas, //Lista de palabras clonadas
    char szPalabras[][TAMTOKEN], //Lista de palabras del diccionario 
    int iEstadisticas[], //Lista de las frecuencias de las palabras
    int iNumElementos, //Numero de elementos en el diciionario
    char szListaFinal[][TAMTOKEN], //Lista final de palabras a sugerir
    int iPeso[], //Peso de las palabras en la lista final
    int iNumLista //Numero de elementos en la szListaFinal
);