//
// Created by fluque1995 on 8/9/21.
//

#ifndef TREE_DICTIONARY_HPP
#define TREE_DICTIONARY_HPP

#include "tree.h"
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <set>

using namespace std;

class Dictionary {
private:
    /**
     * @brief Struct to represent a character inside the tree.
     *
     * The struct contains information about the character it that node, and
     * information marking if a valid word of the dictionary finishes in
     * that character
     */
    struct char_info {
        char character;
        bool valid_word;

        /**
         * Default constructor
         */
        inline char_info() : character(0), valid_word(false) {}

        /**
         * @brief Parameters constructor
         *
         * @param character Character to be inserted
         * @param valid Marker for word validity
         */
        inline char_info(char character, bool valid = false) : character(character), valid_word(valid) {}

        inline bool operator==(const char_info &rhs) {
            return this->character == rhs.character && this->valid_word == rhs.valid_word;
        }

        inline bool operator!=(const char_info &rhs) { return !(*this == rhs); }

        inline bool operator*() { return this->character; }

        inline friend std::ostream &operator<<(std::ostream &os, const char_info &other) {
            os << other.character << (other.valid_word ? "✓" : "×");
            return os;
        }
    };

    tree<char_info> words;
    int total_words;
    typedef tree<char_info>::node node;

    /**
     * @brief Find the lower bound of a character among the children of the current node
     *
     * If the character exists among the children of the current node, that node is returned. If not,
     * the returned node is the one with the biggest character (in terms of alphabetical order) smaller
     * than the searched one
     *
     * @param character Character to be found
     * @param current Reference node, the one whose children are going to be explored
     * @return Lower bound node for the seeked character
     */
    node findLowerBoundChildNode(char character, node current);

    /**
     * @brief Insert character as children of the current node
     *
     * This method tries to insert a new character in the tree, as a child of the current node.
     * If there already exists a node with that character, instead of inserting a new node, the
     * already existing node with the character is returned
     *
     * @param character Character to be inserted
     * @param current Reference node, the one that will be parent of the new inserted node
     * @return Node corresponding to the inserted character
     */
    node insertCharacter(char character, node current);

    /**
     * @brief Calcula el número de ocurrencias de un carácter en el diccionario
     * @param curr_node nodo del diccionario a partir del cual queremos obtener las ocurrencias
     * @param c letra de la que queremos obtener las ocurrencias
     * @return número de ocurrencias
     */

    int getOccurrences(node curr_node, char c);

    /**
     * @brief Cuenta el número de usos de un carácter para formar palabras en el diccionario
     * @param curr_node nodo del diccionario a partir del cual queremos obtener los usos
     * @param c letra de la que queremos obtener los usos
     * @return pair que contiene en primer lugar el número de usos y en segundo lugar el número de palabras completas
     */
    std::pair<int, int> getTotalUsages(node curr_node, char c);

public:

    /**
     * @brief Constructor por defecto
     *
     * Crea un Dictionary vacío
     */
    Dictionary();

    /**
     * @brief Constructor de copia
     *
     * Crea un Dictionary con el mismo contenido que el que se pasa como argumento
     *
     * @param other Dictionary que se quiere copiar
     */
    Dictionary(const Dictionary &other);

    /**
     * @brief Destructor
     *
     * Limpia todos los elementos del Dictionary antes de borrarlo
     */
    ~Dictionary();

    /**
     *  \brief Limpia el Dictionary
     *
     *  Elimina todas las palabras contenidas en el conjunto
     */
    void clear() { this->words.clear(); this->total_words = 0; }

    /**
     * @brief Tamaño del diccionario
     *
     * @return Número de palabras guardadas en el diccionario
     */
    unsigned int size() const { return this->total_words; }

    /**
     * @brief Comprueba si el diccionario está vacio.
     * @return true si el diccionario está vacío, false en caso contrario
     */
    bool empty() const { return this->total_words == 0; }

    /**
     * @brief Indica si una palabra esta en el diccionario o no.
     *
     * Este método comprueba si una determinada palabra se encuentra o no en el dicccionario
     *
     * @param palabra: la palabra que se quiere buscar.
     * @return Booleano indicando si la palabra existe o no en el diccionario
     */
    bool exists(const string &val);

    /**
     * @brief Inserta una palabra en el diccionario
     *
     * @param val palaba a insertar en el diccionario
     * @return Booleano que indica si la inserción ha tenido éxito. Una palabra se inserta
     * con éxito si no existía previamente en el diccionario
     */
    bool insert(const string &val);

    /**
     * @brief Elimina una palabra del diccionario
     *
     * @param val Palabra a borrar del diccionario
     *
     * @return Booleano que indica si la palabra se ha borrado del diccionario
     */
    bool erase(const string &val);

    /**
     * @brief Sobrecarga del operador de asignación
     */
    Dictionary &operator=(const Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de entrada
     *
     * Permite leer las palabras de un fichero de texto e introducirlas en el
     * diccionario
     *
     * @param is Flujo de entrada
     * @param dic Diccionario a rellenar
     * @return Flujo de entrada para poder encadenar el operador
     */
    friend istream &operator>>(istream &is, Dictionary &dic);

    /**
     * @brief Sobrecarga del operador de salida
     *
     * Permite imprimir el diccionario completo a un flujo de salida
     *
     * @param os Flujo de salida, donde imprimir el diccionario
     * @param dic Diccionario a imprimir
     * @return Flujo de salida, para poder encadenar el operador
     */
    friend ostream &operator<<(ostream &os, const Dictionary &dic);

    //////////////////////////////////////////////// Recursive functions ///////////////////////////////////////////////

    /**
     * @brief Calcula el número de ocurrencias de un carácter en el diccionario
     * @param c letra de la que queremos obtener las ocurrencias
     * @return número de ocurrencias
     */
    int getOccurrences(const char c);

    /**
     * @brief Cuenta el número de usos de un carácter para formar palabras en el diccionario
     * @param c letra de la que queremos obtener los usos
     * @return número de usos
     */
    int getTotalUsages(const char c);

    ///////////////////////////////////////////////////// Iterator ////////////////////////////////////////////////////

    class iterator {
    private:
        /**
        *  @brief iterador que recorre en preorden las letras de un diccionario formado a su vez por
        *  un iterador de árbol iter y un string curr_word que indica la palabra formada hasta el momento
        */
        std::string curr_word;
        tree<char_info>::const_preorder_iterator iter;

    public:

        iterator();

        /**
         * @brief Constructor por copia del iterador
         * @param iter iterador que se copia
         */
        iterator(tree<char_info>::const_preorder_iterator iter);

        /**
         * @brief Operador que devuelve la palabra formada hasta el momento
         * @return palabra actual
         */
        std::string operator*();

        /**
         * @brief Avanza el iterador interno hasta que se encuentre el siguiente nodo en el que
         * termina una palabra válida.
         * @return Nueva posición del iterador
         * @post Actualiza la palabra actual
         */
        iterator &operator++();

        /**
         * @brief Comprueba si el iterador actual es igual al pasado por parámetro
         * @param other Iterador que se quiere comprobar si es igual
         * @return bool que indica true si los dos iteradores son iguales
         */
        bool operator==(const iterator &other);

        /**
         * @brief Comprueba si el iterador actual es distinto al pasado por parámetro
         * @param other Iterador que se quiere comprobar si es distinto
         * @return bool que indica true si los dos iteradores son diferentes
         */
        bool operator!=(const iterator &other);

    };
    /**
    * @brief Iterador que apunta al principio del diccionario
    * @return Iterador que apunta a la primera palabra del diccionario
    */
    iterator begin() const;

    /**
     * @brief Iterador que apunta al final del diccionario
     * @return Iterador que apunta a la palabra vacía al final del diccionario
     */
    iterator end() const;

    ///////////////////////////////////////////////// Letters Iterator /////////////////////////////////////////////////

    class possible_words_iterator {
    private:

        /**
        *  @brief iterador que recorre un diccionario palabra a palabra (válida según estén o no las letras en el available_letters).
        * Está también formado por un nodo current_node que nos indica el nodo actual, una current_word que nos indica la
        * palabra por la que vamos, y finalmente un nivel que indica el nivel del árbol en el que nos encontramos.
        */
        multiset<char> available_letters;
        int level;
        node current_node;
        string current_word;

    public:

        /**
         * @brief Constructor por defecto del iterador
         */
        possible_words_iterator();

        /**
        * @brief Constructor con parámetros
        * @param current_node nodo actual
        * @param available_letters vector con las letras disponibles
        */
        possible_words_iterator(node current_node, vector<char> available_letters);

        /**
         * @brief Constructor por copia del iterador
         * @param other iterador que se copia
         */
        possible_words_iterator(const possible_words_iterator &other);


        /**
         * @brief Operador de asignación
         * @param other iterador que se quiere asignar al actual
         * @return Iterador actual con el nuevo valor
         * @post El iterador actual se modifica
         */
        possible_words_iterator &operator=(const possible_words_iterator &other);

        /**
         * @brief Comprueba si el iterador actual es igual al pasado por parámetro
         * @param other Iterador que se quiere comprobar si es igual
         * @return bool que indica true si los dos iteradores son iguales
         */
        bool operator==(const possible_words_iterator &other) const;

        /**
         * @brief Comprueba si el iterador actual es distinto al pasado por parámetro
         * @param other Iterador que se quiere comprobar si es distinto
         * @return bool que indica true si los dos iteradores son distintos
         */
        bool operator!=(const possible_words_iterator &other) const;

        /**
         * @brief Desplaza el iterador al siguiente nodo disponible
         */
        void next_nodo();

        /**
         * @brief Busca si hay un nodo disponible y actualiza el nodo actual a los nuevos valores
         * @param nodo Nodo a comprobar
         * @return bool que indica true en caso de si encontrarse un nodo al que desplazarse y false en caso contrario
         */
        bool nodoEncontrado(node nodo);

        /**
         * @brief Elimina la última letra de current_word y la inserta en available_letters
         */
        void extractLetter();

        /**
         * @brief Comprueba si el nodo pasado como parámetro esta disponible en nuestro available_letters y no es nulo
         * @param nodo Nodo a comprobar
         * @return bool que indica true en caso de si encontrarse en las letras disponibles y false en caso contrario
         */
        bool nodoDisponible(node nodo);

        /**
        * @brief Avanza el iterador interno hasta que se encuentre la siguiente palabra formada por
        * letras válidas en el diccionario
        * @return Nueva posición del iterador
        * @post Actualiza la palabra actual
        */

        possible_words_iterator &operator++();

        /**
         * @brief Operador que devuelve la palabra formada hasta el momento
         * @return palabra actual
         */
        std::string operator*() const;

    };
    //Dictionary

    /**
    * @brief Iterador que apunta al principio del diccionario
    * @return Iterador que apunta a la primera palabra válida del diccionario
    */
    possible_words_iterator possible_words_begin(vector<char> available_characters) const;

    /**
     * @brief Iterador que apunta al final del diccionario
     * @return Iterador que apunta a la palabra vacía al final del diccionario
     */
    possible_words_iterator possible_words_end() const;


};

#endif //TREE_DICTIONARY_HPP
