#include <iostream>
#include <fstream>

using namespace std;

int main(){

    string vrstica;
    int vsota=0, najvec=0;

    fstream file;
    
    file.open("AoC_22-1-input.txt", ios::in);
    while(!file.eof()){
        getline(file, vrstica);
        if(vrstica.length() == 0){
            if(vsota > najvec) najvec = vsota;
            vsota = 0;
        }
        else vsota += stoi(vrstica);
    }
    file.close();
    cout << "Najvecja vsota je " << najvec << endl;

    system("pause");
    return 0;
}