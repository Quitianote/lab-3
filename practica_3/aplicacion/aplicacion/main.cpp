#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void separar(string cade[], string datos[256][4] , int nom, int tam);
void codi2(string escri[], int n, int tam);
void codi2cam(string cad[], string cop[], int ini, int fin);
void conv(string cad[], int numeros[], int tam);

int main(){

    while(true){
        int inicio = 0;
        ifstream texto;
        ofstream binario;
        int i = 0;
        int tam = 0;
        int cont = 0;
        int contnom = 0;
        int n = 4;//semilla
        string caracter[1];
        char bit;

        texto.open("sudo.txt");//abriendo archivo de texto
        //binario.open(bin, ofstream::binary);

        if(texto.is_open())cout << "Esta abierto texto" << endl;
        else cout << "Esta cerrado texto" << endl;
        if(binario.is_open())cout << "Esta abierto binario" << endl;
        else cout << "Esta cerrado binario" << endl;

        while(texto.good()){//leer texto y pasar a entero
            bit = texto.get();
            if(bit != (-1)){
                caracter[0] = caracter[0] + bit;
                cont ++;
                if(cont%8 == 0)tam ++;
                cout << "bit: " << bit << endl;
            }
        }

        int numeros[tam];
        cout << "pase por aca" << endl;

        codi2(caracter, n, tam);//decodificando
        conv(caracter, numeros, tam);//pasar de binario a decimal

        cout << numeros[0] << " numero" << endl;

        caracter[0] = "";
        for(; i < tam; i ++){//pasar de numeros a ascii
            caracter[0] = caracter[0] + char(numeros[i]);
        }
        cout << "caracteres: " << caracter[0] << endl;
        cout << "tam: " << tam << endl;
        for(i = 0; i < tam;i ++){//contar cuantos usuarios hay
            if(caracter[0][i] == '!' || caracter[0][i] == '*')contnom ++;
        }
        string datos[contnom][4];
        cout << "pase por aca 2.55555555" << endl;
        separar(caracter, datos, contnom, tam);//separando datos
        cout << "pase por aca 2" << endl;












        cout << "Ingrese \n1-Para iniciar como administrador \n2-Para iniciar como usuario" << endl; cin >> inicio;//ingreso
        while(inicio != 1 && inicio != 2){//verificando numero de ingreso
            cout << "//Error::numero incorrecto, por favor ingresar numero valido" << endl; cin >> inicio;
        }
        if(inicio == 1){

        }








    }

    return 0;
}

void codi2(string escri[], int n, int tam){
    int i = 0;
    int semi = n;//copia de semilla
    string cop[1] = {escri[0]};//copia de string original
    cout << "pase por aca 3" << endl;

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


void separar(string cade[], string datos[][4], int nom, int tam){
    int i = 0;
    int fila = 0;
    int elem = 0;
    cout << "pase por aca 4" << endl;
    cout << "nom: " << nom << " tam: " << tam << endl;

    //for(; fila < nom; fila ++){//recorriendo filas de datos
        for(; i < tam; i ++){//recorriendo caracteres de cade, para encontrar inicio de usuario
            char cara = cade[0][i];
            if(cara == '!' || cara == '*'){
                datos[fila][0] = cade[0][i];
                elem = i + 1;
                cout << "mirando inicio de usuario: " << datos[fila][0] << endl;
                for(;;elem ++){//construyendo string nombre
                    if(cade[0][elem] != ';'){
                        datos[fila][1] = datos[fila][1] + cade[0][elem];
                    }
                    else{
                        elem ++;
                        break;
                    }
                }
                for(;;elem ++){//construyendo string contraseña
                    if(cade[0][elem] != ','){
                        datos[fila][2] = datos[fila][2] + cade[0][elem];
                    }
                    else{
                        elem ++;
                        break;
                    }
                }
                for(;;elem ++){//construyendo string dinero
                    if(cade[0][elem] != '/'){
                        datos[fila][3] = datos[fila][3] + cade[0][elem];
                    }
                    else break;
                }
                fila ++;
            }
        }
    //}
    cout << "pase por aca 5" << endl;
    for(i = 0; i < 2; i ++){
        for(int col = 0; col < 3; col ++){
            cout << datos[i][col] << endl;
        }

    }
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
        while(ini < final){//creando byte
            bytes.insert(pos, 1, cad[0][ini]);//creando byte, bit por bit, insertando cada bit al final de anterior bit
            ini ++;
            pos ++;
        }
        for(; i > -1; i --){//recorriendo bits
            if(bytes[i] == '1'){//mirando si el bit es 1 pa elevarlo
                if(i != 7){
                    for(; mul < expo; mul ++){//elevando numero
                        resul *= 2;//se multiplica por 2 dependiendo de que tan grande es i
                    }
                    num += resul;
                }
                else num ++;

            }
            expo ++;
            mul = 0;
            resul = 1;
        }
        i = 7;
        numeros[reco] = num;
        ini = final;
        final += 8;
        num = 0;
        bytes = "";
        pos = 0;
        expo = 0;
    }
}






























