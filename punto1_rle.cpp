#include "punto1_rle.h"
using namespace std;

bool esNumero(char c) {
    return c >= '0' && c <= '9';
}

string comprimirRLE(const string& texto) {
    string salida;
    int n = (int)texto.size();
    int i = 0;
    while (i < n) {
        char letra = texto[i];
        int num = 1;
        i++;
        while (i < n && texto[i] == letra) {
            num++;
            i++;
        }
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
        if (!esNumero(comprimido[i])) throw "Formato invalido";
        int num = 0;
        while (i < n && esNumero(comprimido[i])) {
            num = (num * 10) + (comprimido[i] - '0');
            i++;
        }
        if (i >= n || num <= 0) throw "Formato invalido";
        char letra = comprimido[i];
        i++;
        for (int j = 0; j < num; j++) {salida += letra;}
    }
    return salida;
}
