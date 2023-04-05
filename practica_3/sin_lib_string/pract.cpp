#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void conv(int*, int, string*);
void imprimir(int*, int);
void codi1(string* , int, int);
void codi2(string* , int, int);
void cambit1(string*, int);


int main(){
    ifstream texto;
    ofstream binario;
    int numtext = 0;
    int i = 0;
    int n = 0;
    int cont = 0;
    int codi = 0;
    char nom[60] = "";
    char bin[60] = "";
    int caracter[256];
    string escri[256];

    cout << "Ingrese nombre del archivo: "; cin >> nom;
    cout << "Ingrese nombre del archivo binario: "; cin >> bin;
    cout << "Ingrese semilla: "; cin >> n;
    cout << "Ingrese metodo de codificacion: "; cin >> codi;
    
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

    //if(codi == 1)codi1(escri, n, i);

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
    stringstream ss;

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
        ss << int(num);
        str = ss.str();
        while(cont1 < 8){
            str.insert(0, "0");//inserto en la primera posicion el caracter "0"
            cont1 ++;
        }
        escri[0] = str.insert(8*i, str);
        cadena[i] = num;
        cont = 0;
        cont1= 0;
        num = 0;
        ss.str("");//vaciando ss
    }

}

void imprimir(int caracter[], int i){
    int cont = 0;
    for(; cont < i; cont ++){
        cout << caracter[cont] << endl;

    }

}

void arrstr(string str[], int tam){//convirtiendo arreglo en un string
    int i = 0;
    int let = 0;
    int pos = 1;
    string cad[0] = str[0];//copiando arreglo
    for(; i < tam; i ++){
        for(; let < 8; let ++){
            str[i][let] = str[i].insert(pos,cad[0][let]);
            
        }


    }
}

void codi1(string escri[], int n, int tam){
    int i = 0;
    int dif = 0;
    int let = 0;
    int cont1 = 0;
    int con0 = 0;
    char temp[256] = "";
    if(n > 8){
        dif = n-8;
    }
    for(; i < tam; i ++){//entrando a byte
        if(i == 8){
            i = n - 8;
        }
        for(; let < 8; let ++){//entrando a bit
            if(i == 0){//primer cambio de bit
                cambit1(escri, n);
                continue;
                //break;
            }
            if(let + 1 == n){


            }
            temp[let] = escri[i][let];



        }
        
        break;
    }    
}

void cambit1(string escri[], int n){//primer cambio de bit codi1    

    int i = 0;
    int bit = 0;
    for(; i < n; i ++){
        bit = escri[0][i];
        if(bit == '1')escri[0][i] = '0';
        else escri[0][i] = '1';
    }
}

void codi1cam(char cad[], int tam){
    int i = 0;
    int cont0 = 0;
    int cont1 = 0;


    for(; i < tam; i ++){
        if(cad[i] == '0')cont0 ++;
        else cont1 ++;
    }
    if(cont1 == cont)

}

void codi2(string escri[], int n){




}





