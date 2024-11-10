#ifndef _LETTERS_BAG_H_
#define _LETTERS_BAG_H_
#include <bag.h>
#include <letters_set.h>

/**
 * @brief TDA LettersBag
 *
 * Este TDA almacena un conjunto de chars utilizado en el juego de letras.
 * La estructura de datos subyacente es una lista de chars.
 * @param letters Bag formada por datos de tipo char, es decir, letras.
 */

class LettersBag {
private:
    Bag <char> letters;
public:

    /**
    * @brief Constructor por defecto sin parámetros de un LettersBag
    * @post El LettersBag creado está vacío
    */
    LettersBag();

    /**
     * @brief Rellena un LettersBag con las letras de un LettersSet,
     * introduciendo cada letra el número de veces que sus repeticiones indiquen
     * @param letterSet a copiar
     */
    LettersBag(const LettersSet & letterSet);

    /**
    * @brief Introduce una letra en la bolsa
    * @param l Letra que se va a insertar en nuestro LettersBag
    */
    void insertLetter(const char l);

    /**
     * @brief Extrae una letra aleatoria de la bolsa y la elimina del conjunto de letras
     * @return Letra extraída de la bolsa
     */
    char extractLetter();

    /**
     * @brief Extrae un conjunto de letras de la LettersBag, eliminándolas del conjunto
     * @param num de letras a extraer
     * @return Lista con las letras extraídas aleatoriamente
     */
    vector<char> extractLetters(int num);


    /**
     * @brief Elimina el contenido de la LettersBag
     * @post La bolsa se queda completamente vacía
     */
    void clear();

    /**
     * @brief Tamaño de la bolsa
     * @return int con el tamaño de la bolsa
     */
    unsigned int size()const;

    /**
     * @brief Sobrecarga del operador de asignación
     * @param other LettersBag a copiar
     * @return Referencia al objeto LettersBag al que se le asigna
     */
    LettersBag& operator=(const LettersBag & other);
};

#endif
