

#include <string>
#include <vector>
#include <utility>
#include <set>
#include "dictionary.h"
#include <cmath>

///////////////////////////////////////////////////////////////////////////////
//                             Private functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::node Dictionary::findLowerBoundChildNode(char character, Dictionary::node current) {
    node prev_child, curr_child = current.left_child();

    for (; !curr_child.is_null() && (*curr_child).character <= character; curr_child = curr_child.right_sibling()){
        prev_child = curr_child;
        if ((*curr_child).character == character) {
            return curr_child;
        }
    }
    if (!prev_child.is_null()) {
        return prev_child;
    }
    return current;
}

Dictionary::node Dictionary::insertCharacter(char character, Dictionary::node current) {
    node insertion_position = findLowerBoundChildNode(character, current);
    if (insertion_position == current){
        this->words.insert_left_child(current, char_info(character));
        return insertion_position.left_child();
    } else if ((*insertion_position).character != character){
        this->words.insert_right_sibling(insertion_position, char_info(character));
        return insertion_position.right_sibling();
    } else {
        return insertion_position;
    }
}

int Dictionary::getOccurrences(node curr_node, char c){
    int ocurrencias = 0;
    //if (curr_node.parent().is_null()) ocurrencias=0;

    //si tengo left-child calculo ocurrencias
    if(!curr_node.left_child().is_null()){
        ocurrencias += getOccurrences(curr_node.left_child(), c);
    }
    //si tengo right-sibling calculo ocurrencias
    if(!curr_node.right_sibling().is_null()){
        ocurrencias += getOccurrences(curr_node.right_sibling(), c);
    }
    //comprobar si hay ocurrencia en nodo actual
    if(c == ((*curr_node).character)) ocurrencias++;
    return  ocurrencias;
}

std::pair<int, int> Dictionary::getTotalUsages(node curr_node, char c){

    pair<int,int> auxchild = {0,0};
    pair<int,int> auxsibling = {0,0};
    int complete_words = 0, current_usages = 0;


    if(!curr_node.left_child().is_null()){
        //si tengo left-child calculo usos y palabras
        auxchild = getTotalUsages(curr_node.left_child(), c);//usos, palabras
    }
    if(!curr_node.right_sibling().is_null()){
        //si tengo right-sibling calculo usos y palabras
        auxsibling = getTotalUsages(curr_node.right_sibling(), c); //usos, palabras
    }

    current_usages = auxchild.first + auxsibling.first;
    complete_words = auxchild.second + auxsibling.second;

    //CASO 1
    //si el char del nodo es el que buscamos, hay tantos usos como palabras haya debajo de ese nodo
    //aumenta tantas unidades como palabras terminen en el left-child
    if ((*curr_node).character == c) current_usages += auxchild.second;

    //CASO 2: cuando el char está al final de la palabra
    //cada vez que el nodo marque final de palabra se añade una palabra completa
    if((*curr_node).valid_word){
        complete_words++; //siempre aumenta de 1 en 1
        //si la última letra de la palabra es la que buscamos se añade un uso
        if ((*curr_node).character == c){
            current_usages++; //siempre aumenta de 1 en 1
        }
    }

    pair<int,int> res  = {current_usages, complete_words};
    return res;
}

///////////////////////////////////////////////////////////////////////////////
//                              Public functions                             //
///////////////////////////////////////////////////////////////////////////////

Dictionary::Dictionary() {
    this->words.set_root(char_info());
    this->total_words = 0;
}

Dictionary::Dictionary(const Dictionary &other) {
    this->words = other.words;
    this->total_words = other.total_words;
}

Dictionary::~Dictionary() {
    this->words.clear();
}

bool Dictionary::exists(const std::string & word) {
    node current = this->words.get_root();
    for (int i = 0; i < word.size(); ++i){
        current = this->findLowerBoundChildNode(word[i], current);
        if ((*current).character != word[i]) {
            return false;
        }
    }

    return (*current).valid_word;
}

bool Dictionary::insert(const std::string &word) {
    node current = this->words.get_root();
    for (int i = 0; i < word.size(); ++i){
        current = this->insertCharacter(word[i], current);
    }

    if (!(*current).valid_word) {
        (*current).valid_word = true;
        this->total_words++;
        return true;
    }

    return false;
}

bool Dictionary::erase(const std::string & val){
    node current = this->words.get_root();
    for (int i = 0; i < val.size(); ++i){
        current = this->findLowerBoundChildNode(val[i], current);
        if ((*current).character != val[i]) {
            return false;
        }
    }
    if ((*current).valid_word){
        (*current).valid_word = false;
        this->total_words--;
        return true;
    }
    return false;
}

Dictionary &Dictionary::operator=(const Dictionary &dic){
    if (this != &dic){
        this->words.clear();
        this->words = dic.words;
        this->total_words = dic.total_words;
    }
    return *this;
}

///////////////////////////////////////////////////////////////////////////////
//                               I/O overload                                //
///////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &os, const Dictionary &dict){
    for(Dictionary::iterator it = dict.begin();it != dict.end(); ++it){
        os << *it << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream &is, Dictionary &dict){
    std::string curr_word;
    while (getline(is, curr_word)){
        dict.insert(curr_word);
    }
    return is;
}

///////////////////////////////////////////////////////////////////////////////
//                            Recursive counters                             //
///////////////////////////////////////////////////////////////////////////////

int Dictionary::getOccurrences(const char c){
    return getOccurrences(words.get_root(),c);
}

int Dictionary::getTotalUsages(const char c){
    return getTotalUsages(words.get_root(),c).first;
}

///////////////////////////////////////////////////////////////////////////////
//                                 Iterator                                  //
///////////////////////////////////////////////////////////////////////////////

Dictionary::iterator::iterator() {
    this->curr_word = "";
}

Dictionary::iterator::iterator(tree<char_info>::const_preorder_iterator iter) {
    this->curr_word = "";
    this->iter = iter;
}

std::string Dictionary::iterator::operator*() {
    return this->curr_word;
}

Dictionary::iterator &Dictionary::iterator::operator++() {

    do {
        ++this->iter; //avanzar iterador
        //generar substring que empieza en el principio de la palabra y termina en la posición del nivel
        //superior al actual, o hasta el final de string si no es lo suficientemente largo
        curr_word = curr_word.substr(0, this->iter.get_level()-1);
        //si no estamos en la raíz añadimos a la palabra la letra de ese nodo, del nivel actual
        if (iter.get_level()!=0) curr_word += (*iter).character;

    } while (iter.get_level()!=0 && !(*iter).valid_word);
    return *this;
}

bool Dictionary::iterator::operator==(const iterator &other) {
    return this->iter == other.iter;
}

bool Dictionary::iterator::operator!=(const iterator &other) {
    return this->iter != other.iter;
}

Dictionary::iterator Dictionary::begin() const {
    iterator iter(this->words.cbegin_preorder());
    ++iter;
    return iter;
}

Dictionary::iterator Dictionary::end() const {
    iterator iter(this->words.cend_preorder());
    return iter;
}

///////////////////////////////////////////////////////////////////////////////
//                            Letters Iterator                               //
///////////////////////////////////////////////////////////////////////////////



Dictionary::possible_words_iterator Dictionary::possible_words_begin(vector<char> available_characters) const {
    possible_words_iterator iter(this->words.get_root() ,available_characters);
    return ++iter;
}

Dictionary::possible_words_iterator Dictionary::possible_words_end() const {
    return possible_words_iterator();
}

Dictionary::possible_words_iterator::possible_words_iterator(){
    /*string current_word
     multiset<char> available_words
     node current_node
     int level */
    //available_letters -> constructor por defecto de la stl
    //node -> constructor por defecto en node.tpp
    this->level = 0;
    this->current_word = "";
}

Dictionary::possible_words_iterator::possible_words_iterator(node current_node, vector<char> available_letters)
        :available_letters(available_letters.begin(), available_letters.end()) {
    this->current_node = current_node;
    this->level = 0;
    this->current_word = "";
}

Dictionary::possible_words_iterator::possible_words_iterator(const possible_words_iterator &other){
    this->current_node = other.current_node;
    this->current_word = other.current_word;
    this->level = other.level;
    this->available_letters = other.available_letters;
}


Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator=(const Dictionary::possible_words_iterator &other) {
    this->current_word = other.current_word;
    this->level = other.level;
    this->available_letters = other.available_letters;
    return *this;
}

bool Dictionary::possible_words_iterator::operator==(const Dictionary::possible_words_iterator &other) const {
    return (this->current_node==other.current_node && this->available_letters==other.available_letters);
}

bool Dictionary::possible_words_iterator::operator!=(const Dictionary::possible_words_iterator &other) const {
    return (this->current_node!=other.current_node && this->available_letters!=other.available_letters);
}

void Dictionary::possible_words_iterator::next_nodo(){
    if(!nodoEncontrado(current_node.left_child())){
        extractLetter();
        if(!nodoEncontrado(current_node.right_sibling())){
            bool encontrado = false;
            //busco los padres
            while (!current_node.parent().is_null() && !encontrado){
                current_node = current_node.parent();
                extractLetter();
                //ver todos los hermanos hasta que alguno este disponible o se acaben los hermanos
                if (nodoEncontrado(current_node.right_sibling())) encontrado = true;
            }

            //if(current_node.parent().is_null()) current_node = current_node.parent(); <- antes
            if(current_node.parent().is_null()) current_node = current_node.parent();
        }
    }
}

bool Dictionary::possible_words_iterator::nodoEncontrado(node nodo){

    bool encontrado = false;
    while(!nodo.is_null() && !encontrado){ //si no entra la primera vez, el nodo es nulo y encontrado se queda false

        if(nodoDisponible(nodo)) encontrado = true;
        else nodo = nodo.right_sibling(); //analiza todos los hermanos hasta que se acaben, sea nulo o esté disponible
    }
    if(encontrado){ //actualiza valores, si no entra aquí es porque llega a nodo nulo

        this->current_node = nodo;
        this->current_node.operator*().character = nodo.operator*().character;
        //elimina la letra de letras disponibles
        this->available_letters.erase(available_letters.lower_bound(nodo.operator*().character));
        //inserta última letra en la palabra
        this->current_word.push_back(nodo.operator*().character); //aquí current_node = nodo
    }
    return encontrado;
}

void Dictionary::possible_words_iterator::extractLetter(){
    this->available_letters.insert(this->current_word.back()); //devuelve la letra a letras disponibles
    this->current_word.pop_back(); //quita última letra de la palabra
}

bool Dictionary::possible_words_iterator::nodoDisponible(node nodo){
    bool disponible = false;
    if (!nodo.is_null()){

        for (multiset<char>::iterator it = this->available_letters.begin();
             it != this->available_letters.end() && !disponible; ++it) {
            if ((*it) == nodo.operator*().character) disponible = true;
        }
    }
    return disponible;
}


Dictionary::possible_words_iterator &Dictionary::possible_words_iterator::operator++(){
    do{
        this->next_nodo(); //vamos avanzando
        //hasta formar una palabra válida
    } while (!this->current_node.is_null() && !this->current_node.operator*().valid_word);
    if (this->current_node.is_null()) *this = possible_words_iterator(); //si estamos en raíz constructor por defecto
    return *this;
}

std::string Dictionary::possible_words_iterator::operator*() const {
    return this->current_word;
}









