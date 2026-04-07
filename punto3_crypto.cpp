#include "punto3_crypto.h"

unsigned char rotarIzq(unsigned char b, int n) {
    if (n == 0) return b;
    return (unsigned char)((b << n) | (b >> (8 - n)));
}

unsigned char rotarDer(unsigned char b, int n) {
    if (n == 0) return b;
    return (unsigned char)((b >> n) | (b << (8 - n)));
}

void encriptarPunto3(const char* texto, int n, unsigned char clave, int rot, char*& salida) {
    salida = new char[n + 1];
    for (int i = 0; i < n; i++) {
        unsigned char x = (unsigned char)texto[i];
        x = rotarIzq(x, rot);
        x = (unsigned char)(x ^ clave);
        salida[i] = (char)x;
    }
    salida[n] = '\0';
}

void desencriptarPunto3(const char* texto, int n, unsigned char clave, int rot, char*& salida) {
    salida = new char[n + 1];
    for (int i = 0; i < n; i++) {
        unsigned char x = (unsigned char)texto[i];
        x = (unsigned char)(x ^ clave);
        x = rotarDer(x, rot);
        salida[i] = (char)x;
    }
    salida[n] = '\0';
}

void liberarPunto3(char*& buffer) {
    if (buffer) delete[] buffer;
    buffer = 0;
}
