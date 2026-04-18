#include <iostream>
#include <fstream>
#include <string>

#include "punto1_rle.h"
#include "punto2_rle.h"
#include "punto3_crypto.h"
#include "punto4.h"

using namespace std;

void ejecutarPunto4() {
    int metodo;
    int clave_num;
    int rot;

    cout << "Metodo (1 RLE, 2 LZ78): ";
    cin >> metodo;
    cout << "Clave (0-255): ";
    cin >> clave_num;
    cout << "Rotacion (1-7): ";
    cin >> rot;

    if (clave_num < 0 || clave_num > 255) {
        cout << "Clave invalida\n";
        return;
    }
    if (rot < 1 || rot > 7) {
        cout << "Rotacion invalida\n";
        return;
    }

    // Archivo de entrada.
    string archivoEntrada = "dataset_Encriptado0.txt";

    // Lectura del texto base desde archivo.
    ifstream fin(archivoEntrada.c_str());
    if (!fin) {
        cout << "No se pudo abrir " << archivoEntrada << "\n";
        return;
    }

    string linea;
    string original = "";
    while (getline(fin, linea)) {
        original += linea;
        if (!fin.eof()) original += '\n';
    }
    fin.close();

    unsigned char clave = (unsigned char)clave_num;
    string final_texto;

    // elijo compresion con switch, como pidieron
    switch (metodo) {
    case 1: {
        // ruta simple: RLE -> encriptar -> desencriptar -> RLE inverso
        string comprimido = comprimirRLE(original);
        int ncomp = (int)comprimido.size();

        char* encriptado = 0;
        char* desencriptado = 0;
        encriptarPunto3(comprimido.c_str(), ncomp, clave, rot, encriptado);
        desencriptarPunto3(encriptado, ncomp, clave, rot, desencriptado);

        final_texto = descomprimirRLE(string(desencriptado));

        liberarPunto3(encriptado);
        liberarPunto3(desencriptado);
        break;
    }
    case 2: {
        // para LZ78 paso el string a char[]
        char* texto = 0;
        int n = (int)original.size();
        texto = new char[n + 1];
        for (int i = 0; i < n; i++) texto[i] = original[i];
        texto[n] = '\0';

        CodigoLZ78* codigos = 0;
        int cantidad = 0;
        comprimirLZ78(texto, n, codigos, cantidad);

        // convierto codigos a texto para poder encriptarlos
        int cap = n * 20 + 100;
        char* serial = new char[cap];
        int p = 0;

        for (int i = 0; i < cantidad; i++) {
            int pref = codigos[i].prefijo;
            int car = (int)(unsigned char)codigos[i].caracter;
            int tiene = codigos[i].tieneCaracter ? 1 : 0;

            char buf[16];
            int b = 0;

            if (pref == 0) {
                serial[p++] = '0';
            } else {
                while (pref > 0) {
                    buf[b++] = (char)('0' + (pref % 10));
                    pref /= 10;
                }
                for (int j = b - 1; j >= 0; j--) serial[p++] = buf[j];
            }
            serial[p++] = ',';

            b = 0;
            if (car == 0) {
                serial[p++] = '0';
            } else {
                while (car > 0) {
                    buf[b++] = (char)('0' + (car % 10));
                    car /= 10;
                }
                for (int j = b - 1; j >= 0; j--) serial[p++] = buf[j];
            }
            serial[p++] = ',';
            serial[p++] = (char)('0' + tiene);
            serial[p++] = ';';
        }
        serial[p] = '\0';
        int nserial = p;

        // encripto y luego revierto para recuperar esos codigos
        char* encriptado = 0;
        char* desencriptado = 0;
        encriptarPunto3(serial, nserial, clave, rot, encriptado);
        desencriptarPunto3(encriptado, nserial, clave, rot, desencriptado);

        CodigoLZ78* codigos2 = 0;
        int cantidad2 = 0;
        for (int i = 0; desencriptado[i] != '\0'; i++) {
            if (desencriptado[i] == ';') cantidad2++;
        }

        if (cantidad2 > 0) {
            codigos2 = new CodigoLZ78[cantidad2];
            int i = 0;
            int k = 0;

            while (desencriptado[i] != '\0' && k < cantidad2) {
                int pref = 0;
                while (desencriptado[i] >= '0' && desencriptado[i] <= '9') {
                    pref = pref * 10 + (desencriptado[i] - '0');
                    i++;
                }
                if (desencriptado[i] == ',') i++;

                int car = 0;
                while (desencriptado[i] >= '0' && desencriptado[i] <= '9') {
                    car = car * 10 + (desencriptado[i] - '0');
                    i++;
                }
                if (desencriptado[i] == ',') i++;

                int tiene = 0;
                while (desencriptado[i] >= '0' && desencriptado[i] <= '9') {
                    tiene = tiene * 10 + (desencriptado[i] - '0');
                    i++;
                }
                if (desencriptado[i] == ';') i++;

                codigos2[k].prefijo = pref;
                codigos2[k].caracter = (char)car;
                codigos2[k].tieneCaracter = (tiene == 1);
                k++;
            }
        }

        // descompresion final de LZ78
        char* recuperado = 0;
        int nrec = 0;
        descomprimirLZ78(codigos2, cantidad2, recuperado, nrec);

        final_texto = string(recuperado);

        delete[] texto;
        delete[] serial;
        liberarCodigosLZ78(codigos);
        liberarCodigosLZ78(codigos2);
        liberarTextoLZ78(recuperado);
        liberarPunto3(encriptado);
        liberarPunto3(desencriptado);
        break;
    }
    default:
        cout << "Metodo invalido\n";
        return;
    }

    // guardo resultado final para comparar con original
    ofstream fout("output.txt");
    if (!fout) {
        cout << "No se pudo escribir output.txt\n";
        return;
    }
    fout << final_texto;
    fout.close();

    cout << "Texto final: " << final_texto << "\n";
    if (final_texto == original) cout << "OK\n";
    else cout << "Error\n";
}
