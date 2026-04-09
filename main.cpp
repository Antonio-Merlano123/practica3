#include <iostream>
#include <string>

#include "punto1_rle.h"
#include "punto2_rle.h"
#include "punto3_crypto.h"
#include "punto4.h"

using namespace std;

int main() {
    int opcion;
    cout << "Opcion (1)RLE (2)LZ78 (3)Crypto (4)Punto4: ";
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
    } else if (opcion == 3) {
        cout << "Texto: ";
        char texto[1000];
        cin.getline(texto, 1000);

        int clave_num;
        int rot;
        cout << "Clave (0-255): ";
        cin >> clave_num;
        cout << "Rotacion (1-7): ";
        cin >> rot;

        if (clave_num < 0 || clave_num > 255) {
            cout << "Clave invalida\n";
            return 1;
        }
        if (rot < 1 || rot > 7) {
            cout << "Rotacion invalida\n";
            return 1;
        }

        int n = contarLen(texto);
        unsigned char clave = (unsigned char)clave_num;

        char* encriptado = 0;
        char* recuperado = 0;
        encriptarPunto3(texto, n, clave, rot, encriptado);
        desencriptarPunto3(encriptado, n, clave, rot, recuperado);

        cout << "Encriptado (bytes): ";
        for (int i = 0; i < n; i++) {
            cout << (int)(unsigned char)encriptado[i] << " ";
        }
        cout << "\nRecuperado: " << recuperado << "\n";

        if (sonIguales(texto, recuperado)) cout << "OK\n";
        else cout << "Error\n";

        liberarPunto3(encriptado);
        liberarPunto3(recuperado);
    } else if (opcion == 4) {
        ejecutarPunto4();
    } else {
        cout << "\nOpcion no valida\n";
    }

    return 0;
}
