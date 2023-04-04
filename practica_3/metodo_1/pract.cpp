#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void conv(int*, int, string*);
void imprimir(int*, int);


int main(){
    ifstream texto;
    ofstream binario;
    int numtext = 0;
    int i = 0;
    int n = 0;
    int cont = 0;
    char nom[60] = "";
    char bin[60] = "";
    int caracter[256];
    string escri[256];

    cout << "Ingrese nombre del archivo: "; cin >> nom;
    cout << nom << endl;
    cout << "Ingrese nombre del archivo binario: "; cin >> bin;
    cout << bin << endl;
    cout << "Ingrese semilla: "; cin >> n;
    


    texto.open(nom);
    binario.open(bin, ofstream::binary);

    if(texto.is_open())cout << "esta abierto" << endl;
    else cout << "esta cerrado" << endl;
    if(binario.is_open())cout << "esta abierto binario" << endl;
    else cout << "esta cerrado binario" << endl;
    
    while(texto.good()){
        char temp = texto.get();
        caracter[i] = (temp - 0);
        i ++;
    }
    
    imprimir(caracter, i);

    conv(caracter, i, escri);

    imprimir(caracter, i);

    for(; cont < i; cont ++){
        binario << escri[cont];
    }
    
    texto.close();
    binario.close();

    return 0;
}

void conv(int cadena[], int tam, string escri[]){//pasar de numero a binario
    float num = 0;
    float resi = 0;
    int cont = 0;
    int cont1 = 0;
    int let = 0;
    int divi = 0;
    int i = 0;
    int n = 0;
    string str;
    for(; i < tam; i++){
        let = cadena[i];
        divi = let/2;
        while(divi != (1/2)){
            divi = let/2;
            resi = float(let%2);
            num = (num/float(10)) + resi/float(10);
            let /= 2;
            cont ++;
        }
        cont1 = cont;
        while(cont > 0){
            num *= 10;
            cont --;
        }
        str = to_string(int(num));
        while(cont1 < 8){
            str = "0" + str;
            cont1 ++;
        }
        escri[i] = str;
        cadena[i] = num;
        cont = 0;
        cont1= 0;
        num = 0;
    }

}

void imprimir(int caracter[], int i){
    int cont = 0;
    for(; cont < i; cont ++){
        cout << caracter[cont] << endl;

    }

}








