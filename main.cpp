#include <iostream>
#include <string>

#include "punto1_rle.h"

using namespace std;

int main() {
    try {
        cout << "=== Punto 1: RLE (Compresion y Descompresion) ===\n";
        cout << "Ingresa el texto a comprimir: ";

        string textoOriginal;
        getline(cin, textoOriginal);

        // comprimo y luego descomprimo para validar
        string comprimido = comprimirRLE(textoOriginal);
        string recuperado = descomprimirRLE(comprimido);

        cout << "\nTexto original   : " << textoOriginal << "\n";
        cout << "Texto comprimido : " << comprimido << "\n";
        cout << "Texto recuperado : " << recuperado << "\n";

        if (textoOriginal == recuperado) {
            cout << "\nVerificacion OK: la descompresion coincide exactamente.\n";
        } else {
            cout << "\nError: la descompresion NO coincide con el original.\n";
        }
    } catch (const char*) {
        // mensaje fijo para que la salida sea clara
        cerr << "Error: formato RLE no valido.\n";
        return 1;
    }

    return 0;
}
