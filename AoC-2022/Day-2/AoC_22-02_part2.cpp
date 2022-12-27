#include <iostream>
#include <fstream>

using namespace std;

int main(){
/*
A,X -> rock     - 1
B,Y -> paper    - 2
C,Z -> scissors - 3

A,B,C -> nasprotnik
X,Y,Z -> igralec

zmaga -> 6
neodloceno -> 3
poraz -> 0

X - poraz
Y - nedoloceno
Z - zmaga
*/
    string vrstica;
    int score = 0;
    char znak;

    fstream file;

    file.open("AoC_22-02-input.txt", ios::in);
    while(!file.eof()){
        getline(file, vrstica);
        if(vrstica[2] == 'X'){ //poraz
            if(vrstica[0] == 'A') znak = 'Z' ;
            else if(vrstica[0] == 'B') znak = 'X';
            else znak = 'Y';
        }
        else if(vrstica[2] == 'Y'){ //neodloceno
            if(vrstica[0] == 'A') znak = 'X';
            else if(vrstica[0] == 'B') znak = 'Y';
            else znak = 'Z';
        }
        else{ //zmaga
            if(vrstica[0] == 'A') znak = 'Y';
            else if(vrstica[0] == 'B') znak = 'Z';
            else znak = 'X';
        }
        switch(znak){
            case 'X': //rock
                score += 1;
                break;
            case 'Y': //paper
                score += 2;
                break;
            case 'Z': //scissors
                score += 3;
                break;
        }
        if((vrstica[0] == 'A' && znak == 'X') || (vrstica[0] == 'B' && znak == 'Y') || (vrstica[0] == 'C' && znak == 'Z')) score += 3; //draw -> +3 tocke
        else if(znak == 'X' && vrstica[0] == 'C') score += 6;// igralec ima X
        else if(znak == 'Y' && vrstica[0] == 'A') score += 6; //Y
        else if(znak == 'Z' && vrstica[0] == 'B') score += 6; //Z        
    }
    file.close();
    cout << "Final score is " << score;

    system("pause");
    return 0;
}