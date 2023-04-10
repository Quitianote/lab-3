#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void separar(string cade[], string datos[256][4] , int nom, int tam);
void codi2(string escri[], int n, int tam);
void codi2cam(string cad[], string cop[], int ini, int fin);
void conv1(string cad[], int numeros[], int tam);
void codi(string escri[], int n, int tam);
void codicam(string cad[], string cop[], int ini, int fin);
void conv(int cadena[], int tam, string escri[]);
bool verificar(string datos[][4], int tam, string usu, string con);
bool exis(string datos[][4], int tam, string usu, string con);
bool todonum(string usu);

int main(){
    int inicio = 0;
    ifstream texto;
    ofstream binario;
    string usuario;
    string contra;
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
        }
    }

    int numeros[tam];
    cout << "pase por aca" << endl;

    codi2(caracter, n, tam);//decodificando
    conv1(caracter, numeros, tam);//pasar de binario a decimal

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
    string datos[256][4];
    cout << "pase por aca 2.55555555" << endl;
    separar(caracter, datos, contnom, tam);//separando datos
    cout << "pase por aca 2" << endl;

    while(true){



        cout << "Ingrese \n1-Para iniciar como administrador \n2-Para iniciar como usuario \n0-Para salir" << endl; cin >> inicio;//ingreso
        while(inicio != 1 && inicio != 2 && inicio != 0){//verificando numero de ingreso
            cout << "//Error::numero incorrecto, por favor ingresar numero valido" << endl; cin >> inicio;
        }
        if(inicio == 0){
            break;
        }
        else if(inicio == 1){
            bool aux;
            while(true){//iniciar sesion
                cout << "Escriba nombre de usuario: \nSi desea salir escriba 0" << endl;cin >> usuario;//iniciando usuario
                cout << "Escriba contraseña: \nSi desea salir escriba 0:" << endl;cin >> contra;//contra
                aux = verificar(datos, contnom, usuario, contra);
                if(usuario == "0" || contra == "0")break;
                while(!aux){
                    cout << "//Error::usuario incorrecto, vuelva a escribir usuario: ";cin >> usuario;
                    if(usuario == "0" || contra == "0")break;
                    cout << "Escriba contraseña: \nSi desea salir escriba 0:" << endl;cin >> contra;
                    aux = verificar(datos, contnom, usuario, contra);
                    if(usuario == "0" || contra == "0")break;
                }
                break;
            }
            if(usuario == "0" || contra == "0")break;

            string deci;
            string saldo;
            string temp[4];
            temp[0] = "";

            cout << "Escriba nombre de usuario a registrar: \nSi desea salir escriba 0" << endl;cin >> usuario;//registrando usuario
            cout << "Escriba contraseña: \nSi desea salir escriba 0:" << endl;cin >> contra;//registrando contra
            if(usuario == "0" || contra == "0")break;
            bool aux2 = todonum( usuario);
            aux = exis(datos, contnom, usuario, contra);

            while(usuario.length() != 10 || !aux || !aux2){
                cout << "//Error::usuario existente o caracteres invalidos, vuelva a escribir usuario: ";cin >> usuario;
                if(usuario == "0" || contra == "0")break;
                cout << "Escriba contraseña: \nSi desea salir escriba 0:" << endl;cin >> contra;
                if(usuario == "0" || contra == "0")break;
                aux = verificar(datos, contnom, usuario, contra);
                aux2 = todonum( usuario);
            }
            if(usuario == "0" || contra == "0")break;
            cout << "Escriba saldo: " << endl;cin >> saldo;//registrando saldo
            temp[1] = usuario;
            temp[2] = contra;
            temp[3] = saldo;

            cout << "¿Desea que sea admin?(1 para si, 0 para no): ";cin >> deci;

            while(deci != "1" && deci != "0"){
                cout << "//Error::elija un valor correcto: ";cin >> deci;
            }
            if(deci == "1")datos[contnom][0] = "!";//creando admin
            else datos[contnom][0] = "*";

            for(i = 1; i < 4; i ++){//guardando datos de cuenta registrada
                datos[contnom][i] = temp[i];
            }
            contnom ++;
            cout << datos[contnom - 1][1] << " usuarios" << endl;












        }








    }

    return 0;
}

void codi2(string escri[], int n, int tam){//decodificar
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

void codi2cam(string cad[], string cop[], int ini, int fin){//decodificar
    cad[0][fin - 1] = cop[0][ini];//la posicion inicial darle la posicion final

    for(; ini < fin - 1; ini ++){//intercambiar posiciones
        cad[0][ini] = cop[0][ini + 1];
    }
}


void separar(string cade[], string datos[][4], int nom, int tam){//separar los datos
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

void conv1(string cad[], int numeros[], int tam){//pasar de binario a decimal
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

void codi(string escri[], int n, int tam){//codificar
    int i = 0;
    int semi = n;//copia de semilla
    string cop[1] = {escri[0]};//copia de string original

    for(; i < tam*8; i ++){//entrando bit por bit, tam*8 es igual a la cantidad de bits, ya que tam son los bytes
        if(i == semi || i == 0){//verificando si i es igual a la semilla
            if(i + n > tam*8){//mirando si i + n(o sea la variable final) se pasa del rango, se multiplica por 8 a tam, porque son 8 bits
                n = tam*8 - i;
            }
            codicam(escri, cop, i, i + n);//codificando la semilla n
            if(i != 0)semi += n;
        }
    }
}

void codicam(string cad[], string cop[], int ini, int fin){//codificar
    cad[0][ini] = cop[0][fin - 1];//la posicion final darle la posicion inicial

    for(; ini < fin - 1; ini ++){//intercambiar posiciones
        cad[0][ini+1] = cop[0][ini];
    }
}

void conv(int cadena[], int tam, string escri[]){//pasar de decimal a binario
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

bool verificar(string datos[][4], int tam, string usu, string con){//verificar que el usuario existe
    int i = 0;
    for(; i < tam; i ++){
        if(datos[i][0] == "!"){//mirar si es admin
            if(datos[i][1] == usu){//verificar usu
                if(datos[i][2] == con){//verificar contra
                    return true;
                }
            }
        }

    }
    return false;


}

bool exis(string datos[][4], int tam, string usu, string con){//verificar que el usuario no existe, para poder registrarlo
    int i = 0;
    for(; i < tam; i ++){
            if(datos[i][1] == usu)return false;//verificar usu
    }
    return true;


}

bool todonum(string usu){//verificar que todos los elementos son numeros
    int i = 0;
    for(; i < usu.length(); i ++){
        cout << int(usu[i]) << endl;
        if(int(usu[i]) < 48 || int(usu[i]) > 57){
            return false;
        }
    }
    return true;
}

















