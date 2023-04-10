#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

void conv(string*, int*, int);
void codi1(string* , int, int);
void codi1cam(string*, string*, int, int, int);
void codi2(string*, int , int);
void codi2cam(string*, string*, int, int);
void cambit1(string*, int);

int main(){
    ofstream texto;
    ifstream binario;
    int n = 0;
    int cont = 0;
    int codi = 0;
    int contdef = 0;
    char byte;
    char nom[60] = "";
    char bin[60] = "";
    string cade[1];

    cout << "Ingrese nombre del archivo: "; cin >> nom;
    cout << "Ingrese nombre del archivo binario: "; cin >> bin;
    cout << "Ingrese semilla: "; cin >> n;
    cout << "Ingrese metodo de decodificacion: "; cin >> codi;

    while(codi != 1 && codi != 2){
        cout << "//ERROR//::Ingrese metodo de codificacion 1 o 2: "; cin >> codi;
    }
    texto.open(nom);
    binario.open(bin, ifstream::binary);

    if(texto.is_open())cout << "Esta abierto texto" << endl;
    else cout << "Esta cerrado texto" << endl;
    if(binario.is_open())cout << "Esta abierto binario" << endl;
    else cout << "Esta cerrado binario" << endl;

    while(binario.read(&byte, 1)) {//leyendo bits
        cade[0] = cade[0].insert(cont, 1, byte);
        cont ++;
        if(cont%8 == 0)contdef ++;//definiendo tamaño
    }
    if(codi == 1)codi1(cade, n, contdef);//decodificacion 1
    else codi2(cade, n, contdef);

    int numeros[contdef];//arreglo con numeros

    conv(cade, numeros, contdef);

    for(int i = 0; i < contdef; i ++){
        cout << numeros[i] << endl;
    }
    for(int i = 0; i < contdef; i ++){
        texto << char(numeros[i]);
    }

    texto.close();
    binario.close();

    return 0;
}

void conv(string cad[], int numeros[], int tam){
    int reco = 0;
    int ini = 0;
    int final = 8;
    int i = 7;
    int num = 0;
    int mul = 0;
    int resul = 1;
    int expo = 0;
    int pos = 0;
    string bytes = "";

    for(; reco < tam; reco ++){//recorriendo bytes
        cout <<  "aqui 1" << endl;
        while(ini < final){
            cout <<  "en bytes" << endl;
            cout <<  "ini: " << ini << " final: " << final << endl;
            bytes.insert(pos, 1, cad[0][ini]);
            ini ++;
            pos ++;
            cout << bytes << endl;
            cout <<  "bytes final" << endl;
        }
        for(; i > -1; i --){//recorriendo bits
            if(bytes[i] == '1'){//mirando si el bit es 1 pa elevarlo
                cout << "byte: " << bytes[i] << endl;
                if(i != 7){
                    cout << "i: " << i << endl;
                    cout << "expo: " << expo << endl;
                    for(; mul < expo; mul ++){//elevando numero
                        resul *= 2;//se multiplica por 2 dependiendo de que tan grande es i
                        cout << "resul: " << resul << " mul: " << mul << endl;
                    }
                    num += resul;
                }
                else num ++;

            }
            expo ++;
            mul = 0;
            resul = 1;
            cout <<  "num: " << num << endl;
        }
        i = 7;
        numeros[reco] = num;
        ini = final;
        final += 8;
        num = 0;
        bytes = "";
        pos = 0;
        expo = 0;
        cout <<  "aqui 2" << endl;
    }
}

void codi1(string escri[], int n, int tam){//metodo de descodificacion 1
    int i = 0;
    int semi = n;//copia de semilla
    int noriginal = n;//copia de valor de semilla original

    for(; i < tam*8; i ++){//entrando bit por bit, tam*8 es igual a la cantidad de bits, ya que tam son los bytes
        if(i == 0){//primer cambio de semilla
            cambit1(escri, n);
            continue;
        }
        else if(i == semi){//verificar si i es igual a la semilla
            if(i + n > tam*8){//mirando si i + n(o sea la variable final) se pasa del rango
                n = tam*8 - i;
            }
            string cop[1] = {escri[0]};//copia de string original
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
    cad[0][fin - 1] = cop[0][ini];//la posicion inicial darle la posicion final

    for(; ini < fin - 1; ini ++){//intercambiar posiciones
        cad[0][ini] = cop[0][ini + 1];
    }
}








