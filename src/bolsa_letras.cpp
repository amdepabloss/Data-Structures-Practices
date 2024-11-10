#include <iostream>
#include "letters_bag.h"
#include <fstream>
#include <string>
#include <cerrno>
using namespace std;

LettersSet readFromFile(const char filename[]){

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

int main(int nargs, char *argv[]){
    //Comprueba si el número de argumentos es 2, si no, saca un mensaje de error
    if (nargs != 2){
        cerr << "Número de parámetros incorrecto" << endl;
    }
    else{
        char letra;
        //Leemos un LetterSet desde un archivo
        LettersSet ls = readFromFile(argv[1]);
        //Rellenamos nuestro LettersBag con el LetterSet
        LettersBag lb(ls);
        //Sacamos todas las letras de la bolsa
        while (lb.size()!=0){
            letra = toupper(lb.extractLetter());
            cout << letra << endl;
        }
    }
}
