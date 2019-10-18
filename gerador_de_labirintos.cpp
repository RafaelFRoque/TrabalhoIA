#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main (){
    int a, b, n, p;
    cin >> a >> b >> n >> p;
	cout<< n << endl;
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        char mat[a][b];
        for(int j = 0; j < a; j++)
            for(int k = 0; k < b; k++)
                mat[j][k] = '*';
        int parede = rand()%p;
        if(parede < 3)
            parede = 3;
        for(int j = 0; j < parede; j++){
            int init = rand()%(a*b);
            while(mat[(int)init/b][init%b] == '-' )
                init = rand()%(a*b);
            int qtd = rand()%((a<b)? a-2: b-2);

			if(qtd < 4)
				qtd = 4;
            int dir = rand()%4;
            for(int k = 0; k < qtd; k++){
                switch (dir){
                case 0:
                    if(init%b < b-1){
						
                        if(mat[init/b][(init%b) + 1] == '-'){
                            k--;
							dir = rand()%4;
						}
						else if(init%b < b-2 and mat[init/b][(init%b) + 2] == '-'){
							k--;
							dir = rand()%4;
						}
						else if(init/b < a-1 and mat[(init/b) + 1][(init%b)+1] == '-'){
							k--;
							dir = rand()%4;
						}
						else if(init/b > 0 and mat[(init/b) - 1][(init%b)+1] == '-'){
							k--;
							dir = rand()%4;
						}
                        else{
                            mat[init/b][(init%b)+ 1]  = '-';
							init = init + 1;
						}
                    }
                    break;
                case 1:
                    if(init/b < a-1){
                        if(mat[(init/b)+1][(init%b) ] == '-'){
                            k--;
							dir = rand()%4;
						}
						else if(init/b < a-2 and mat[(init/b)+2][(init%b) ] == '-'){
							k--;
							dir = rand()%4;
						}
						else if(init%b < b-1 and mat[(init/b) + 1][(init%b)+1] == '-'){
							k--;
							dir = rand()%4;
						}
						else if(init%b > 0 and mat[(init/b) + 1][(init%b) - 1] == '-'){
							k--;
							dir = rand()%4;
						}
                        else{
                            mat[(init/b)+1][(init%b)]= '-';
							init += b;
						}
                    }
                    break;
                case 3:
                    if(init/b > 0){
                        if(mat[(init/b)-1][(init%b) ] == '-'){
                            k--;
							dir = rand()%4;
						}
						else if(init/b > 1 and mat[(init/b)-2][(init%b) ] == '-'){
							k--;
							dir = rand()%4;
						}
						else if(init%b < b-1 and mat[(init/b) - 1][(init%b)+1] == '-'){
							k--;
							dir = rand()%4;
						}
						else if(init%b > 0 and mat[(init/b) - 1][(init%b) - 1] == '-'){
							k--;
							dir = rand()%4;
						}
                        else{
                            mat[(init/b)-1][(init%b)]= '-';
							init-=b;
						}

                    }
                    break;
                case 4:
                    if(init%b > 0){
						if(mat[init/b][(init%b) - 1] == '-'){
                            k--;
							dir = rand()%4;
						}
						else if(init%b > 1 and mat[init/b][(init%b) - 2] == '-'){
							k--;
							dir = rand()%4;
						}
						else if(init/b < a-1 and mat[(init/b) + 1][(init%b)-1] == '-'){
							k--;
							dir = rand()%4;
						}
						else if(init/b > 0 and mat[(init/b) - 1][(init%b)-1] == '-'){
							k--;
							dir = rand()%4;
						}
                        else{
                            mat[init/b][(init%b)-1] = '-';
							init-=1;	
						}
                    }
                    break;
                }
            }
    	}
		int entrada = rand()%(a*b);
		while(mat[entrada/b][entrada%b] == '-')
			entrada = rand()%(a*b);
		mat[entrada/b][entrada%b] = '#';
		int saida = rand()%(a*b);
		while(mat[saida/b][saida%b] == '-' or saida == entrada)
			saida = rand()%(a*b);
		mat[saida/b][saida%b] = '$';
		cout << a << " " << b << endl;
		for(int j = 0; j < a; j++){
			for(int k = 0; k < b; k++)
				cout << mat[j][k] << " "; 
			cout << endl;
		}
    }



    return 0;
}