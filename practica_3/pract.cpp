#include <iostream>
#include <fstream>


using namespace std;

int main(){
    ifstream users;

    users.open("usuarios.txt");

    if(users.is_open())cout << "esta abierto" << endl;
    else cout << "esta cerrado" << endl;
    
    leer(users);

    users.close();

    return 0;
}


