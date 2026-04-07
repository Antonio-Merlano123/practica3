#ifndef PUNTO3_CRYPTO_H
#define PUNTO3_CRYPTO_H

void encriptarPunto3(const char* texto, int n, unsigned char clave, int rot, char*& salida);
void desencriptarPunto3(const char* texto, int n, unsigned char clave, int rot, char*& salida);
void liberarPunto3(char*& buffer);

#endif
