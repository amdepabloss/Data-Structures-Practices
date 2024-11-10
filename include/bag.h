#ifndef __BAG_H__
#define __BAG_H__
#include "vector"
#include <cerrno>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

/**
 *  \brief TDA abstracto Bolsa
 *
 *  Este TDA abstracto nos permite trabajar con una colección de elementos que
 *  permite la extracción de elementos de forma aleatoria sin reemplazamiento
 *  @param v Vector que almacena un conjunto de elementos tantas veces como
 *  estos estén repetidos. El elemento es de tipo genérico.
 */

template <class T>
class Bag {

private:
    vector<T> v;

public:

    /**
       * @brief Constructor por defecto, sin parámetros, de un Bag
       * @post El bag creado está vacío
       */
    Bag(){
        v.begin() = v.end();
    }

    /**
     * @brief Constructor por copia de un Bag
     * @param other Objeto de tipo Bag<T> a copiar
     */
    Bag(const Bag<T> & other){
        v = other.v;
    }

    /**
     * @brief Añade un elemento al final de un Bag
     * @param element Elemento de tipo T que se introduce en el Bag
     */
    void add(const T & element){
        v.push_back(element);
    }

    /**
     * @brief Extrae un elemento aleatorio de la bolsa y lo elimina de la bolsa
     * @pre La bolsa no está vacía
     * @returns Elemento de tipo T extraído de la bolsa
     * @post EL elemento devuelto se ha eliminado de la bolsa
     */
    T get(){
        T aux;
        if (!empty()){
            // Generar una posición aleatoria del vector
            int num;
            srand(time(NULL));
            num = rand()%size();
            // Devolver el elemento en esa posición
            aux = v[num];
            // Eliminar el elemento en esa posición
            v.erase(v.begin()+num);
        }
        else cout << "La bolsa esta vacia" << endl;

        return aux;
    }

    /**
     * @brief Elimina todos los elementos de la bolsa
     * @post La bolsa se queda vacía
     */
    void clear(){
        v.clear();
    }

    /**
     * @brief Tamaño de la bolsa
     * @return Número de elementos que hay en la bolsa
     */
    unsigned int size() const{
        return v.size();
    }

    /**
     * @brief Comprueba si la bolsa está vacía
     * @return true si la bolsa está vacía, false en caso contrario
     */
    bool empty(){
        return v.empty();
    }

    /**
     * @brief Sobrecarga del operador de asignación
     * @param other Bag<T> a copiar
     * @return Referencia al objeto al que se asigna
     */
    const Bag<T>&operator=(const Bag<T>& other){
        v = other.v;
        return *this;
    }
};

#endif
