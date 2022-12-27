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
*/
    string vrstica;
    int score = 0;

    fstream file;

    file.open("AoC_22-02-input.txt", ios::in);
    while(!file.eof()){
        getline(file, vrstica);
        switch(vrstica[2]){
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
        if((vrstica[0] == 'A' && vrstica[2] == 'X') || (vrstica[0] == 'B' && vrstica[2] == 'Y') || (vrstica[0] == 'C' && vrstica[2] == 'Z')) score += 3; //draw -> +3 tocke
        else if(vrstica[2] == 'X' && vrstica[0] == 'C') score += 6;// igralec ima X
        else if(vrstica[2] == 'Y' && vrstica[0] == 'A') score += 6; //Y
        else if(vrstica[2] == 'Z' && vrstica[0] == 'B') score += 6; //Z        
    }
    file.close();
    cout << "Final score is " << score;

    system("pause");
    return 0;
}