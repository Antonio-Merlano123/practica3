#include "punto1_rle.h"

using namespace std;

// revisa si el caracter es un numero
bool esNumero(char c) {
    return c >= '0' && c <= '9';
}

string comprimirRLE(const string& texto) {
    if (texto.empty()) {
        return "";
    }

    string salida;
    int n = (int)texto.size();
    int i = 0;

    while (i < n) {
        // tomo una letra y cuento cuantas veces se repite seguida
        char letra = texto[i];
        int num = 1;
        i++;

        while (i < n && texto[i] == letra) {
            num++;
            i++;
        }

        // guardo el bloque como cantidad + letra
        salida += to_string(num);
        salida += letra;
    }

    return salida;
}

string descomprimirRLE(const string& comprimido) {
    string salida;
    int i = 0;
    int n = (int)comprimido.size();

    while (i < n) {
        // primero debe venir una cantidad
        if (!esNumero(comprimido[i])) {
            throw "Formato RLE invalido";
        }

        int num = 0;
        // puede ser de varios digitos (ej: 12A)
        while (i < n && esNumero(comprimido[i])) {
            num = (num * 10) + (comprimido[i] - '0');
            i++;
        }

        if (i >= n || num <= 0) throw "Formato RLE invalido";

        char letra = comprimido[i];
        i++;

        // reconstruyo el texto original
        for (int j = 0; j < num; j++) {
            salida += letra;
        }
    }

    return salida;
}
