#include <iostream>
#include <fstream>

using namespace std;

int conv(char);


int main(){
    ifstream texto;
    char temp[256];
    int numtext = 0;
    char nom[60] = "";

    cout << "Ingrese nombre del archivo: "; cin >> nom;
    cout << nom << endl;

    texto.open(nom);

    if(texto.is_open())cout << "esta abierto" << endl;
    else cout << "esta cerrado" << endl;
    
    while(texto.good()){
        temp = texto.get();
        if(texto.good())numtext = numtext*10 + (temp - '0');



    }

    texto.close();

    return 0;
}

int conv(char texto){



}
