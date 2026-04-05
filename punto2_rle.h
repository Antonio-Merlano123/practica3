#ifndef PUNTO2_RLE_H
#define PUNTO2_RLE_H

struct CodigoLZ78 {
    int prefijo;
    char caracter;
    bool tieneCaracter;
};

void comprimirLZ78(const char* texto, int n, CodigoLZ78*& codigos, int& cantidadCodigos);
void descomprimirLZ78(const CodigoLZ78* codigos, int cantidadCodigos, char*& texto, int& nTexto);

void liberarCodigosLZ78(CodigoLZ78*& codigos);
void liberarTextoLZ78(char*& texto);

int contarLen(const char* t);
bool sonIguales(const char* a, const char* b);

#endif
