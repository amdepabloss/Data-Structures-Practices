#include <iostream>
#include <fstream>
#include "letters_set.h"
#include "dictionary.h"
#include "letters_bag.h"
#include "solver.h"
#include <chrono>
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


int main (int argc, char * argv[]){

    if(argc != 5) {
        cout << "Los parametros son: " << endl;
        cout << "1.- Ruta al archivo que contiene el diccionario" << endl;
        cout << "2.- Ruta al archivo que contiene las letras y su puntuación" << endl;
        cout << "3.- Modo de juego (L = longitud, P = puntuación)" << endl;
        cout << "4.- Cantidad de letras para la partida" << endl;
        return 1;
    }
    else{
        solver s(readFromFileDic(argv[1]), readFromFileLetter(argv[2]));
        bool scoregame = true;
        char modojuego = argv[3][0]; //primera posición del string
        if(modojuego =='L') scoregame = false;   // Comprobar que solo se le puede pasar L o P
        int nletras = stoi(argv[4]);


        //crear bolsa con el LetterSet disponible
        LettersBag bolsa (s.getLetras());
        //sacar letras de la bolsa
        vector<char> letras = bolsa.extractLetters(nletras);

        pair<vector<string>, int> solucion;

        float media = 0;
        //buscar las mejores soluciones
        //for (int i=0; i<250; i++) {
        using namespace std::chrono;
        //inicio
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        solucion = s.getSolutions(letras, scoregame);
        //fin
        high_resolution_clock::time_point t2 = high_resolution_clock::now();
        duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
        media += time_span.count();
        //cout << time_span.count() << endl;
        //}

        cout << "LETRAS DISPONIBLES:" << endl;
        for (char letra: letras) cout << letra << "\t";
        cout << endl << "SOLUCIONES: " << endl;
        for (int i = 0; i < solucion.first.size(); i++) cout << solucion.first[i] << endl;
        cout << "PUNTUACION: " << endl;
        cout << solucion.second << endl;

        //media /= 250;
        //cout << endl << "La media es:" << media;
    }

    return 0;
}


