#ifndef __LETTER_SET_H__
#define __LETTER_SET_H__
#include <iostream>
#include <map>


using namespace std;

/**
 * @brief TDA LetterInfo
 *
 * Contiene información sobre un determinado carácter del juego de las
 * letras. En concreto, almacena información sobre el número de repeticiones de
 * la letra en la partida y de la puntuación que otorga al utilizarse en una
 * palabra
 */

    struct LetterInfo {
        /**
         * @brief repetitions Número de veces que se repite una letra
         */
        int repetitions;
        /**
         * @brief score Puntuación asignada a cada letra
         */
        int score;

        /**
         * @brief Constructor por defecto sin parámetros de un LetterInfo
         * @post Las repeticiones y la puntuación se inicializan a 0
         */
        LetterInfo(){
            repetitions = 0;
            score = 0;
        }

        /**
         * @brief Constructor con parámetros de un LetterInfo
         * @param repeticiones Número de repeticiones de una letra
         * @param puntuacion Puntuación de una letra
         */
        LetterInfo(int repeticiones, int puntuacion) {
            repetitions = repeticiones;
            score = puntuacion;
        }

        /**
         * @brief  Devueve información sobre un LetterInfo
         * @param os Flujo de salida
         * @param l Letterinfo que se va a imprimir.
         * @return Devuelve el flujo de salida
         */
        friend ostream & operator<<(ostream &os, const LetterInfo & l) {
            os << l.repetitions << '\t' << l.score;
            return os;
        }

        /**
        * @brief Guarda información sobre un LetterInfo a partir de datos
        * @param is Flujo de entrada
        * @param l LetterInfo donde se guarda la información
        */
        friend istream & operator>>(istream &is, LetterInfo & l) {
            is >> l.repetitions >> l.score;
            return is;
        }
    };



/**
 * @brief TDA LettersSet
 *
 * Este TDA representa un conjunto de letras, con la información necesaria para
 * jugar una partida al juego de las letras, es decir, el número de repeticiones
 * que tenemos de la letra y la puntuación que dicha letra otorga cuando se
 * utiliza en una palabra
 * @param letters Map que contiene una pareja de una letra y un LetterInfo asociado
 * a esta. Las letras no se repiten.
 */
    class LettersSet{
    private:
        map <char, LetterInfo> letters;

    public:

        /**
         * @brief Constructor por defecto sin parámetros de un LetterSet
         * @post El LetterSet creado está vacío
         */
        LettersSet();

        /**
         * @brief  Constructor de copia de un LetterSet
         * @param otro Letterset a copiar
         */
        LettersSet (const LettersSet & otro);

        /**
         * @brief  Inserta una nueva letra, con la correspondiente información de la misma (repeticiones y puntuación
         * @param val Pair que contiene una letra determinada y su información (repeticiones y puntuación)
         * @return Si se ha podido insertar o no. Si ya se encontraba la letra, devolverá false, puesto que solo inserta en caso de que no estuviera
         */
        bool insert (const pair<char, LetterInfo> & val);

        /**
        * @brief Elimina un elemento del LetterSet
        * @param key Letra que se quiere borrar del LetterSet
        * @post Si la letra no está en el LetterSet este no se modifica
        * @return Si se ha posido eliminar o no
        */
        bool erase(const char & key);

        /**
         * @brief  Elimina todas las letras de un LetterSet
         * @post El LetterSet queda vacío
         */
        void clear();

        /**
        * @brief Consulta si el LetterSet está vacío
        * @return true si está vacío, false en caso contrario
        * @post El LetterSet no se modifica
        */
        bool empty() const;

        /**
        * @brief Consulta el tamaño del LetterSet
        * @return  Número de elementos en el LetterSet
        * @post El LetterSet no se modifica
        */
        unsigned int size() const;

        /**
        * @brief Calcula la puntuación de una palabra
        * @param word Palabra a la que se calcula la puntuación
        * @return Puntuación de la palabra introducida
        */
        int getScore(string word);

        /**
        * @brief Sobrecargar del operador de asignación.
        * @param cl Letterset a copiar
        * @return Referencia al objeto this para poder encadenar el operador
        **/
        LettersSet & operator=(const LettersSet & cl);

        /**
        * @brief Obtiene los valores asignados a una letra en LetterSet
        * @param val Letra de la cual se obtienen sus valores
        * @return LetterInfo con las repeticiones y la puntuación asignados a una letra
        */
        LetterInfo & operator[](const char & val);

        /**
         * @brief  Devueve información sobre un LettersSet
         * @param os Flujo de salida donde escribir el LettersSet
         * @param cl LettersSet que se va a imprimir.
         * @return Devuelve el flujo de salida
         */
        friend ostream & operator << (ostream & os, const LettersSet & cl);

        /**
       * @brief Guarda información sobre un LettersSet a partir de datos
       * @param is Flujo de entrada
       * @param cl LettersSet donde se guarda la información
       * @return Devuelve el flujo de entrada
       */
        friend istream & operator >> (istream & is, LettersSet & cl);

        /**
       * @brief Iterador que indica la primera posición del LetterSet
       * @return Devuelve un iterador que apunta a la primera posición del LetterSet
       */
        map<char,LetterInfo>::iterator begin();

        /**
      * @brief Iterador para LetterSet
      * @return Iterador que apunta a la posición siguiente a la última del LetterSet
      */
        map<char,LetterInfo>::iterator end();

        /**
    * @brief Iterador constante que indica la primera posición del LetterSet
    * @return Devuelve un iterador que apunta a la primera posición del LetterSet
    */
        map<char,LetterInfo>::const_iterator cbegin()const;

        /**
      * @brief Iterador constante para LetterSet
      * @return Iterador que apunta a la posición siguiente a la última del LetterSet
      */
        map<char,LetterInfo>::const_iterator cend()const;
    };
#endif
