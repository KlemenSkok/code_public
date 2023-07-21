#include <iostream>
#include <unistd.h> //linux OS(server)
#include <time.h>

//#include <windows.h> //windows OS
//Sleep(millis);

//using namespace std;

#define GOTOXY(x, y) "\x1B[" #y ";" #x "H"

const unsigned int micros = 1000000;
//usleep(3 * micros); // 3 sekunde delay

struct Semafor{
    bool zelena;
    bool rumena;
    bool rdeca;
    bool pesci;
};

class Krizisce{
	private:
		Semafor semafor[2];
		
		void semReset(Semafor& tmp){
			tmp.rdeca = true;
			tmp.rumena = false;
			tmp.zelena = false;
			tmp.pesci = false;
		}
		
		void prizgiLuci(int cas, int index){
		    switch(cas){
		        case 0:
		            semReset(semafor[index]);
		            break;
	            case 2:
	                semafor[index].rumena = true;
	                break;
                case 3:
                    semafor[index].rdeca = false;
                    semafor[index].rumena = false;
                    semafor[index].zelena = true;
                    semafor[index].pesci = true;
		            break;
	            case 11:
	                semafor[index].pesci = false;
	                break;
                case 13:
                    semafor[index].rumena = true;
                    semafor[index].zelena = false;
                    break;
                case 15:
                    semafor[index].rdeca = true;
                    semafor[index].rumena = false;
                default:
                    break;
		    }
		}
		
		void prikaziLuci(Semafor tmp){
            if(tmp.rdeca) 
                std::cout << "\033[101m  \033[m";
            else std::cout << "--";
            if(tmp.rumena) 
                std::cout << "\033[103m  \033[m";
            else std::cout << "--";
            if(tmp.zelena) 
                std::cout << "\033[102m  \033[m";
            else std::cout << "--";
            std::cout << "  ";
            if(!tmp.pesci) 
                std::cout << "\033[101m  \033[m--";
            if(tmp.pesci)
                std::cout << "--\033[102m  \033[m";
        }
		
	public:
		Krizisce(){
			semReset(semafor[0]);
			semReset(semafor[1]);
		}
		void run(){
		    time_t start = time(0);
		    while(true){
			    int cajt = difftime(time(0), start);
			    prizgiLuci(cajt%16, ((cajt/16)%2 == 1) ? 0:1);
			    std::cout << GOTOXY(1, 1);
			    prikaziLuci(semafor[0]);
			    std::cout << "\n\n";
			    prikaziLuci(semafor[1]);
			    std::cout << std::endl;
			    usleep(micros);
		    }
		}
};

int main(){
    
    Krizisce xyz;
    xyz.run();
    
    
    
    return 0;
}

/*
            |       |
            |   !   |
            |       |
            |   !   |
____________|       |____________

--  --  --  -       --  --  --  -            
_____________        ____________
            |   !   |
            |       |
            |   !   |
            |       |


*/


