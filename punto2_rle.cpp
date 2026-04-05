#include "punto2_rle.h"

int largoEntrada(const int* pref, int idx) {
    int n = 0;
    while (idx > 0) {
        n++;
        idx = pref[idx];
    }
    return n;
}

void reconstruirEntrada(const int* pref, const char* car, int idx, char* salida, int& largo) {
    largo = largoEntrada(pref, idx);
    int p = largo - 1;
    while (idx > 0) {
        salida[p] = car[idx];
        p--;
        idx = pref[idx];
    }
}

void comprimirLZ78(const char* texto, int n, CodigoLZ78*& codigos, int& cantidadCodigos) {
    // diccionario en dos arrays: prefijo + caracter
    int* pref = new int[n + 1];
    char* car = new char[n + 1];
    codigos = new CodigoLZ78[n + 1];
    char* temp = new char[n + 1];

    int tamDic = 0;
    int tamCod = 0;
    int pos = 0;

    while (pos < n) {
        int mejor = 0;
        int mejorL = 0;

        // 1) buscar la frase mas larga que ya exista
        for (int i = 1; i <= tamDic; i++) {
            int l = 0;
            reconstruirEntrada(pref, car, i, temp, l);
            if (l <= mejorL || pos + l > n) continue;

            bool igual = true;
            for (int k = 0; k < l; k++) {
                if (temp[k] != texto[pos + k]) {
                    igual = false;
                    break;
                }
            }

            if (igual) {
                mejor = i;
                mejorL = l;
            }
        }

        // 2) guardar par (indice, caracter)
        bool tiene = (pos + mejorL < n);
        codigos[tamCod].prefijo = mejor;
        codigos[tamCod].caracter = tiene ? texto[pos + mejorL] : '\0';
        codigos[tamCod].tieneCaracter = tiene;
        tamCod++;

        // 3) agregar nueva entrada al diccionario
        if (tiene) {
            tamDic++;
            pref[tamDic] = mejor;
            car[tamDic] = texto[pos + mejorL];
        }

        pos += mejorL + (tiene ? 1 : 0);
    }

    cantidadCodigos = tamCod;
    delete[] pref;
    delete[] car;
    delete[] temp;
}

void descomprimirLZ78(const CodigoLZ78* codigos, int cantidadCodigos, char*& texto, int& nTexto) {
    int* pref = new int[cantidadCodigos + 1];
    char* car = new char[cantidadCodigos + 1];
    char* temp = new char[cantidadCodigos + 1];

    int tamDic = 0;
    int total = 0;

    // primero calculo el tamanio final
    for (int i = 0; i < cantidadCodigos; i++) {
        total += largoEntrada(pref, codigos[i].prefijo);
        if (codigos[i].tieneCaracter) total++;

        if (codigos[i].tieneCaracter) {
            tamDic++;
            pref[tamDic] = codigos[i].prefijo;
            car[tamDic] = codigos[i].caracter;
        }
    }

    texto = new char[total + 1];
    nTexto = 0;
    tamDic = 0;

    // reconstruyo texto y diccionario al mismo tiempo
    for (int i = 0; i < cantidadCodigos; i++) {
        int l = 0;
        reconstruirEntrada(pref, car, codigos[i].prefijo, temp, l);
        for (int k = 0; k < l; k++) texto[nTexto++] = temp[k];

        if (codigos[i].tieneCaracter) {
            texto[nTexto++] = codigos[i].caracter;
            tamDic++;
            pref[tamDic] = codigos[i].prefijo;
            car[tamDic] = codigos[i].caracter;
        }
    }

    texto[nTexto] = '\0';
    delete[] pref;
    delete[] car;
    delete[] temp;
}

void liberarCodigosLZ78(CodigoLZ78*& c) {
    if (c) delete[] c;
    c = 0;
}

void liberarTextoLZ78(char*& t) {
    if (t) delete[] t;
    t = 0;
}

int contarLen(const char* t) {
    int n = 0;
    while (t[n] != '\0') n++;
    return n;
}

bool sonIguales(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}
