#include <iostream>
#include <fstream>

using namespace std;

int conv(int, int);
int imprimir(int*, int);


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
    for(; cont < i; cont ++){
        cout << caracter[cont] << endl;

    }

    conv(caracter, i);

    imprimir(caracter, i);
    
    texto.close();

    return 0;
}

int conv(int cadena, int tam){
    int i = 0;
    float num = 0;
    int div = 0;
    int cont = 0;
    for(; i < tam; i++){
        while(div > 0){
            num = (cadena[i]%2)/10;
            cont ++;    
        }
        while(cont > 0){
            num *= 10;
            cont --;
        }
        cadena[i] = num;
    }

}

void imprimir(int caracter, int i){
    int cont = 0;
    for(; cont < i; cont ++){
        cout << caracter[cont] << endl;

    }

}
