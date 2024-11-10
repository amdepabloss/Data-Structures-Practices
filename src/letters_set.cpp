#include "letters_set.h"
#include <map>




LettersSet::LettersSet(){
    letters.begin()=letters.end();
}

LettersSet::LettersSet(const LettersSet & otro){
    letters = otro.letters;
}

bool LettersSet::insert (const pair<char, LetterInfo> & val){
    return letters.insert(val).second;
}

bool LettersSet::erase(const char & key){
    return letters.erase(key);
}

void LettersSet::clear(){
    return letters.clear();
}

bool LettersSet::empty() const{
    return letters.empty();
}

unsigned int LettersSet::size() const{
    return letters.size();
}
int LettersSet::getScore(string word){
    int puntos = 0;
    for(int i=0;i<word.size();i++){
        puntos += letters.find(word[i])->second.score;
    }
    return puntos;
}

LettersSet & LettersSet::operator=(const LettersSet & cl){
    letters=cl.letters;
    return *this;
}

LetterInfo & LettersSet::operator[](const char & val){
    return letters[val];
}

ostream & operator << (ostream & os, const LettersSet & cl){

    os << "Letra Cantidad Puntos" << endl;

    map <char, LetterInfo>::const_iterator pos;
    for(pos = cl.letters.begin(); pos != cl.letters.end(); ++pos){
        os << (*pos).first << '\t' << (*pos).second << endl;
    }
    return os;
}



istream & operator >> (istream & is, LettersSet & cl){
    string cabeceras;
    char letra;
    int repetitions, score;

    getline(is, cabeceras);
    LetterInfo li;
    pair <char, LetterInfo> aux;

    while(is){
        //leo datos
        is >> letra >> repetitions >> score;
        letra = tolower(letra);
        //creo letra aux
        li.repetitions = repetitions;
        li.score = score;
        aux.first = letra;
        aux.second = li;
        //inserto letra en letters
        cl.insert(aux);
    }
    return is;
}

map<char,LetterInfo>::iterator LettersSet::begin(){
    return letters.begin();
}

map<char,LetterInfo>::iterator LettersSet::end(){
    return letters.end();
}

map<char,LetterInfo>::const_iterator LettersSet::cbegin()const{
    return letters.begin();
}

map<char,LetterInfo>::const_iterator LettersSet::cend()const{
    return letters.end();
}


