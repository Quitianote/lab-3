#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void conv(int*, int, string*);
void codi1(string* , int, int);
void codi1cam(string* , string*, int, int, int);
void codi2(string* , int, int);
void codi2cam(string* , string*, int, int);
void cambit1(string*, int);

int main(){
    ifstream texto;
    ofstream binario;
    int i = 0;
    int n = 0;
    int codi = 0;
    char nom[60] = "";
    char bin[60] = "";
    int caracter[256];
    string escri[1];

    cout << "Ingrese nombre del archivo: "; cin >> nom;
    cout << "Ingrese nombre del archivo binario: "; cin >> bin;
    cout << "Ingrese semilla: "; cin >> n;
    cout << "Ingrese metodo de codificacion: "; cin >> codi;
    while(codi != 1 && codi != 2){
        cout << "//ERROR//::Ingrese metodo de codificacion 1 o 2: "; cin >> codi;
    }
    texto.open(nom);
    binario.open(bin, ofstream::binary);

    if(texto.is_open())cout << "Esta abierto texto" << endl;
    else cout << "Esta cerrado texto" << endl;
    if(binario.is_open())cout << "Esta abierto binario" << endl;
    else cout << "Esta cerrado binario" << endl;

    while(texto.good()){//leer texto y pasar a entero
        char temp = texto.get();

        if((temp - 0) != (-1)){
            caracter[i] = (temp - 0);
            i ++;
        }

    }
    conv(caracter, i, escri);

    if(codi == 1)codi1(escri, n, i);//codificar
    else codi2(escri, n, i);

    binario << escri[0];//escribir en archivo bin

    texto.close();
    binario.close();

    return 0;
}

void conv(int cadena[], int tam, string escri[]){//pasar de numero a binario
    double num = 0;
    float resi = 0;
    int cont = 0;
    int cont1 = 0;
    int let = 0;
    int divi = 0;
    int i = 0;
    string str;
    stringstream ss;

    for(; i < tam; i++){
        let = cadena[i];
        divi = let/2;

        while(divi != (1/2)){//mientras la division sea diferente a la ultima division que se hace, o sea la ultima division que se hace es dividir por 1
            divi = let/2;
            resi = float(let%2);
            num = (num/float(10)) + resi/float(10);
            let /= 2;
            cont ++;
        }
        cont1 = cont;

        while(cont > 0){//pasando de decimal a binario
            num *= 10;
            cont --;
        }
        ss << int(num);//metiendo variable int en el objeto ss
        str = ss.str();//pasando string a str

        while(cont1 < 8){
            str.insert(0, "0");//inserto en la primera posicion el caracter "0"
            cont1 ++;
        }
        escri[0] = escri[0].insert(8*i, str);
        cont = 0;
        num = 0;
        ss.str("");//vaciando ss
    }
}

void codi1(string escri[], int n, int tam){//metodo de codificacion 1
    int i = 0;
    int semi = n;//copia de semilla
    int noriginal = n;//copia de valor de semilla original
    string cop[1] = {escri[0]};//copia de string original

    for(; i < tam*8; i ++){//entrando bit por bit, tam*8 es igual a la cantidad de bits, ya que tam son los bytes
        if(i == 0){//primer cambio de semilla
            cambit1(escri, n);
            continue;
        }
        else if(i == semi){//verificar si i es igual a la semilla
            if(i + n > tam*8){//mirando si i + n(o sea la variable final) se pasa del rango
                n = tam*8 - i;
            }
            codi1cam(escri, cop, noriginal, i, i + n);//codificando la semilla n
            semi += n;
        }
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

void codi1cam(string cad[], string cop[], int semi, int ini, int fin){//codificacion 1
    int inicop = ini;//copia de valor inicial
    int fincop = fin;//copia de valor final
    int cont = 1;
    int cont0 = 0;
    int cont1 = 0;

    ini -= semi;//posicion de la semilla que se va a contar
    fin -= semi;//posicion final de la semilla que se va a contar

    for(; ini < fin; ini ++){//contando 0 y 1
        if(cop[0][ini] == '0')cont0 ++;
        else cont1 ++;
    }

    ini = inicop;//dandole al valor inicial su valor inicial original
    fin = fincop;//dandole al valor final su valor final original

    if(cont1 == cont0){//primera condicion
        for(; ini < fin; ini ++){
            switch(cad[0][ini]){
                case '1':
                    cad[0][ini] = '0';
                    break;
                case '0':
                    cad[0][ini] = '1';
                    break;
            }
        }
    }

    if(cont0 > cont1){//segunda condicion
        for(; ini < fin; ini ++){
            if(cont%2 == 0){
                switch(cad[0][ini]){
                    case '1':
                        cad[0][ini] = '0';
                        break;
                    case '0':
                        cad[0][ini] = '1';
                        break;
                }
            }
            cont ++;
        }
    }

    if(cont1 > cont0){//tercera condicion
        for(; ini < fin; ini ++){
            if(cont%3 == 0){
                switch(cad[0][ini]){
                    case '1':
                        cad[0][ini] = '0';
                        break;
                    case '0':
                        cad[0][ini] = '1';
                        break;
                }
            }
            cont ++;
        }
    }
}

void codi2(string escri[], int n, int tam){
    int i = 0;
    int semi = n;//copia de semilla
    string cop[1] = {escri[0]};//copia de string original

    for(; i < tam*8; i ++){//entrando bit por bit, tam*8 es igual a la cantidad de bits, ya que tam son los bytes
        if(i == semi || i == 0){//verificando si i es igual a la semilla
            if(i + n > tam*8){//mirando si i + n(o sea la variable final) se pasa del rango, se multiplica por 8 a tam, porque son 8 bits
                n = tam*8 - i;
            }
            codi2cam(escri, cop, i, i + n);//codificando la semilla n
            if(i != 0)semi += n;
        }
    }
}

void codi2cam(string cad[], string cop[], int ini, int fin){
    cad[0][ini] = cop[0][fin - 1];//la posicion final darle la posicion inicial

    for(; ini < fin - 1; ini ++){//intercambiar posiciones
        cad[0][ini+1] = cop[0][ini];
    }
}






