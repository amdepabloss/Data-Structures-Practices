#include "letters_bag.h"

/**
 *
 */
LettersBag::LettersBag(){
    Bag<char>();
}

LettersBag::LettersBag (const LettersSet & letterSet){
    int repeticiones;
    map <char, LetterInfo>::const_iterator pos;
    for(pos = letterSet.cbegin(); pos != letterSet.cend(); ++pos) {
        repeticiones = (*pos).second.repetitions;
        for (int i=0; i<repeticiones; i++){
            insertLetter((*pos).first);
        }
    }
}

void LettersBag::insertLetter(const char l){
    letters.add(l);
}

char LettersBag::extractLetter(){
    return letters.get();
}

vector<char> LettersBag::extractLetters(int num){
    vector<char> v;
    for (int i=0; i<num; i++){
        v.push_back(extractLetter());
    }
    return v;
}

void LettersBag::clear(){
    letters.clear();
}

unsigned int LettersBag::size()const{
    return letters.size();
}

LettersBag& LettersBag::operator=(const LettersBag & other){
    letters = other.letters;
    return *this;
}
