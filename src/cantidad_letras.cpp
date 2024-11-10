#include "dictionary.h"
#include "letters_set.h"
#include <iostream>
#include <fstream>

using namespace std;

LettersSet readFromFileLetter(const char filename[]){

    ifstream f;
    LettersSet l;

    f.open(filename);
    if(!f)
        cout << "Error abriendo el fichero." << endl;
    else
    {
        f >> l;
        f.close();
    }
    return l;
}

Dictionary readFromFileDic(const char filename[]){

    ifstream f;
    Dictionary d;

    f.open(filename);
    if(!f)
        cout << "Error abriendo el fichero." << endl;
    else
    {
        f >> d;
        f.close();
    }
    return d;
}


int main (int nargs, char *argv[]){

    if (nargs != 3){
        cout << "Los parametros son: " << endl;
        cout << "1.- El fichero con el diccionario" << endl;
        cout << "2.- El fichero con las letras" << endl;
        return 1;
    }
    Dictionary d = readFromFileDic(argv[1]); //minúscula
    LettersSet l = readFromFileLetter(argv[2]); //minúscula

    cout << "Letra\tUsos\tOcurrencias" << endl;
    map <char, LetterInfo>::const_iterator pos;
    char letramayus;
    for(pos = l.cbegin(); pos != l.cend(); ++pos){
        letramayus = toupper((*pos).first);
        cout << letramayus << "\t" << d.getTotalUsages((*pos).first) << "\t" << d.getOccurrences((*pos).first) << endl;
        //Calculamos el número de veces que aparece cada letra en el diccionario
    }
}
