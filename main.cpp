#include <iostream>
#include <string>

#include "punto1_rle.h"
#include "punto2_rle.h"

using namespace std;

int main() {
    try {
        int opcion;
        cout << "Opcion (1)RLE (2)LZ78: ";
        cin >> opcion;
        cin.ignore(10000, '\n');

        if (opcion == 1) {
            cout << "Texto: ";

            string textoOriginal;
            getline(cin, textoOriginal);

            string comprimido = comprimirRLE(textoOriginal);
            string recuperado = descomprimirRLE(comprimido);

            cout << "Comprimido: " << comprimido << "\n";
            if (textoOriginal == recuperado) cout << "OK\n";
            else cout << "Error\n";
        } else if (opcion == 2) {
            cout << "Texto: ";

            char texto[1000];
            cin.getline(texto, 1000);

            int n = contarLen(texto);
            CodigoLZ78* codigos = 0;
            int cantidadCodigos = 0;
            comprimirLZ78(texto, n, codigos, cantidadCodigos);

            cout << "Pares:\n";
            for (int i = 0; i < cantidadCodigos; i++) {
                cout << "(" << codigos[i].prefijo << ",";
                cout << (codigos[i].tieneCaracter ? codigos[i].caracter : '-') << ")\n";
            }

            char* recuperado = 0;
            int nRec = 0;
            descomprimirLZ78(codigos, cantidadCodigos, recuperado, nRec);

            cout << "Recuperado: " << recuperado << "\n";
            if (sonIguales(texto, recuperado)) cout << "OK\n";
            else cout << "Error\n";

            liberarCodigosLZ78(codigos);
            liberarTextoLZ78(recuperado);
        } else {
            cout << "\nOpcion no valida\n";
        }
    } catch (const char*) {
        // mensaje fijo para que la salida sea clara
        cerr << "Error en los datos.\n";
        return 1;
    }

    return 0;
}
