

#ifndef P04_JUEGO_LETRAS_SOLVER_H
#define P04_JUEGO_LETRAS_SOLVER_H
#include "letters_set.h"
#include "dictionary.h"
#include <vector>
#include <string>

using namespace std;

class solver {

private:
    /**
     * brief clase que permite resolver una partida del juego de las letras, compuesta por un diccionario de
     * tipo Dictionary que almacena las posibles palabras que se pueden formar y un conjunto de letras de tipo
     * LetterSer que contiene la información necesaria para calcular la puntuación de cada palabra y su
     * disponibilidad
     */
    Dictionary diccionario;
    LettersSet letras;

    /**
     * @brief Comprueba si una palabra se puede formar según las letras del available_letters
     * @param available_letters Vector que contiene las letras de las que se disponen
     * @param palabra Palabra a comprobar
     * @return Devuelve un bool, true si la palabra se puede formar y false en caso de que no se pueda formar
     */
    bool comprobar_palabra (vector<char> available_letters, string palabra);

    /**
     * @brief Calcula la puntuación de una palabra según el modo de juego
     * @param palabra Palabra a la que se le calcula la puntuación
     * @param score_game bool que indica el modo de juego, true si calcula la puntuación según el valor de las letras,
     * false si la calcula según la longitud de la palabra
     * @return La puntuación de la palabra
     */
    int getPuntuacion(const string palabra, bool score_game);

public:

    /**
     * Constructor con parámetros. Crea un solver que tiene asociado un Dictionary y un LettersSet
     * @param dict diccionario a copiar en nuestro objeto
     * @param letters_set LettersSet a copiar en nuestro objeto
     */

    solver (const Dictionary & dict, const LettersSet & letters_set);

    /**
     * @brief Construye el vector de soluciones a partir de las letras de una partida
     * @param available_letters Vector de letras disponibles para la partida
     * @param score_game Bool indicando el tipo de partida. True indica que la partida se juega a puntuación, false que
     * se juega a longitud
     * @return pair <vector<string>,int> con el vector de palabras que constituyen las mejores soluciones (puede haber
     * empates) y la puntuación que obtienen
     */
    pair<vector <string>, int> getSolutions (const vector<char> &available_letters, bool score_game);

    /**
     * @brief getter de las letras del solver
     * @return LetterSet con las letras de la partida
     */
    LettersSet getLetras() const;

    /**
     * @brief Construye el vector de soluciones de forma eficiente a partir de las letras de una partida
     * @param available_letters Vector de letras disponibles para la partida
     * @param score_game Bool indicando el tipo de partida. True indica que la partida se juega a puntuación, false que
     * se juega a longitud
     * @return pair <vector<string>,int> con el vector de palabras que constituyen las mejores soluciones (puede haber
     * empates) y la puntuación que obtienen
     */
    pair<vector <string>, int> getSolutionsEficiente (const vector<char> &available_letters, bool score_game);

};
#endif //P04_JUEGO_LETRAS_SOLVER_H
