#include <iostream>
#include <fstream>

using namespace std;

void conv(int*, int);
void imprimir(int*, int);


int main(){
    ifstream texto;
    int numtext = 0;
    int i = 0;
    int cont = 0;
    char nom[60] = "";
    int caracter[256];

    cout << "Ingrese nombre del archivo: "; cin >> nom;
    cout << nom << endl;

    texto.open(nom);

    if(texto.is_open())cout << "esta abierto" << endl;
    else cout << "esta cerrado" << endl;
    
    while(texto.good()){
        char temp = texto.get();
        caracter[i] = (temp - 0);
        i ++;
    }
    
    imprimir(caracter, i);

    conv(caracter, i);

    imprimir(caracter, i);
    
    texto.close();

    return 0;
}

void conv(int cadena[], int tam){
    int i = 0;
    float num = 0;
    float resi = 0;
    int cont = 0;
    int let = 0;
    int divi = 0;
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
        while(cont > 0){
            num *= 10;
            cont --;
        }
        cadena[i] = num;
        cont = 0;
        num = 0;
    }

}

void imprimir(int caracter[], int i){
    int cont = 0;
    for(; cont < i; cont ++){
        cout << caracter[cont] << endl;

    }

}
