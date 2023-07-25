#include <iostream>
#include <unistd.h> //linux OS(server)
#include <time.h>

//#include <windows.h> //windows OS
//Sleep(millis);

//using namespace std;

//!	LINUX VERZIJA
/*
Za Windows OS nadomesti "unistd.h" z "windows.h" in namesto usleep(micros) uporabi Sleep(1000);
*/

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
	    void show(){
	        std::cout << GOTOXY(1, 1);
		    prikaziLuci(semafor[0]);
		    std::cout << "\n\n";
		    prikaziLuci(semafor[1]);
		    std::cout << std::endl;
	    }
	    
	    void emergencyStop(time_t& start){
	        std::cout << GOTOXY(1, 4) << "EMERGENCY STOP";
	        semafor[0].pesci = false;
	        semafor[1].pesci = false;
	        
	        for(int i = 0; i < 2; i++){
    	        if(semafor[i].zelena){
    	            semafor[i].zelena = false;
    	            semafor[i].rumena = true;
    	        }
	        }
	        usleep(2 * micros);
	        
	        for(int i = 0; i <2; i++){
    	        semafor[i].rumena = false;
    	        semafor[i].rdeca = true;
	        }
	        usleep(10 * micros);
	        start = time(0);
	        std::cout << "\x1B[2J";
	    }
	    
	public:
		Krizisce(){
			semReset(semafor[0]);
			semReset(semafor[1]);
		}
		void run(){
		    time_t start = time(0);
		    int cajt, prev_cajt;
		    bool em_stop = false;
		    em_stop = false;
		    while(true){
		        prev_cajt = cajt;
			    cajt = difftime(time(0), start);
			    prizgiLuci(cajt%16, (cajt/16)%2);
			    
			    if(em_stop){
                    emergencyStop(start);
                    em_stop = false;
			    }
			    
			    if(cajt != prev_cajt){
			        show();
			    }
		    }
		}
};

int main(){
    
    srand(time(NULL));
    
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
