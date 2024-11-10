

#include "solver.h"
solver::solver (const Dictionary & dict, const LettersSet & letters_set){
    diccionario = dict;
    letras = letters_set;
}

LettersSet solver::getLetras() const{
    return letras;
}

bool solver::comprobar_palabra (vector<char> available_letters, string palabra){
    bool palabra_existe = true; //consideramos que la palabra es válida hasta que falte una letra
    bool letra_existe;
    for (int i=0; i<palabra.size() && palabra_existe; i++){ //cada letra de la palabra
        //comprobamos que existe letra por letra
        letra_existe = false;
        for (vector<char>::iterator it = available_letters.begin() ; it != available_letters.end() && !letra_existe; ++it){//cada available_letter
            if(palabra[i] == (*it)) {
                letra_existe = true;
                it = available_letters.erase(it); //quitar letra del conjunto
            }
        }
        //si una letra no existe, la palabra tampoco
        if (!letra_existe) palabra_existe = false;
    }
    return palabra_existe;

}


int solver::getPuntuacion(const string palabra, bool score_game){
    int puntuacion;
    //score_game: true a puntuación, false a longitud
    if (score_game) puntuacion = letras.getScore(palabra);
    else puntuacion = palabra.size();

    return puntuacion;
}

pair<vector <string>, int> solver::getSolutions (const vector<char> &available_letters, bool score_game){

    pair<vector <string>, int> sol; //palabras con puntuación máxima y puntuación máxima
    sol.second=0;

    //recorrer todas las palabras
    for (Dictionary::iterator it = diccionario.begin(); it != diccionario.end(); ++it){ //cada palabra
        if (getPuntuacion((*it), score_game) >= sol.second){
            //para cada palabra con puntuación mayor o igual a la máxima, comprobar si todas sus letras están disponibles en available_letter
            if(comprobar_palabra(available_letters,(*it))) {
                if (getPuntuacion((*it), score_game) > sol.second) sol.first.clear();
                sol.first.push_back((*it));
                //actualizar máxima puntuación
                sol.second = getPuntuacion((*it), score_game);
            }
        }
    }
    return sol;
}

pair<vector <string>, int> solver::getSolutionsEficiente (const vector<char> &available_letters, bool score_game) {
    pair<vector <string>, int> sol; //palabras con puntuación máxima y puntuación máxima
    sol.second=0;

    //recorrer todas las palabras
    for (Dictionary::possible_words_iterator it = diccionario.possible_words_begin(available_letters);
         it != diccionario.possible_words_end(); ++it) { //cada palabra válida
        if (getPuntuacion((*it), score_game) >= sol.second){
            if (getPuntuacion((*it), score_game) > sol.second) sol.first.clear();
            sol.first.push_back((*it));
            //actualizar máxima puntuación
            sol.second = getPuntuacion((*it), score_game);
        }
    }

    return sol;
}


