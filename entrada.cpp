#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <ctime>
#include <cmath>
#include <map>
#define fi first
#define se second

using namespace std;

class Labyrinth {
	private:
		int rowSize;
		int colSize;
		pair<int, int> start;
		pair<int, int> end;
	public:
		char ** labyrinth;
		
		Labyrinth(int row, int col) {
			rowSize = row;
			colSize = col;

			labyrinth = (char **) malloc(sizeof(char *) * rowSize);        
			for(int i = 0; i < rowSize; i++)
				labyrinth[i] = (char *) malloc(sizeof(char) * colSize);
			
		}

		~Labyrinth() {
			for(int i = 0; i < rowSize; i++)
				free(labyrinth[i]);
			free(labyrinth);        
		}

		int getRow(){
			return rowSize;
		}

		int getCol() {
			return colSize;			
		}

		pair<int, int> getStart() {
			return start;
		}
		
		pair<int, int> getEnd() {
			return end;
		}

		void readInput() {
			for(int i = 0; i < rowSize; i++)
				for(int j = 0; j < colSize; j++){
					cin >> labyrinth[i][j];
					if(labyrinth[i][j] == '#'){
						start = make_pair(i, j);
						cout << "#" << i << " " << j << endl;
					}
					else if(labyrinth[i][j] == '$'){
						end = make_pair(i, j);
						cout << "$" << i << " " << j << endl;
					}
				}
			}

		void printLab() {
			for(int i = 0; i < rowSize; i++) {
				for(int j = 0; j < colSize; j++)
					cout << labyrinth[i][j];
				cout << endl;
			}
			cout << endl; 
		}


};

class DepthSearch {
	private:
		double cost;
		int visitedRow;
		int visitedCol;
		pair<int, int> start;
		pair<int, int> end;
		stack<pair<int, int>> path;
		char **visited;
	public:
		DepthSearch(Labyrinth &lab) {
			cost = 0.0;
			visitedRow = lab.getRow();
			visitedCol = lab.getCol();
			start =  lab.getStart();
			end =  lab.getEnd();

			visited = (char **) malloc(sizeof(char *) * visitedRow);        
			for(int i = 0; i < visitedRow; i++)
				visited[i] = (char *) malloc(sizeof(char) * visitedCol);

			for(int i = 0; i < visitedRow; i++)
				for(int j = 0; j < visitedCol; j++)
					visited[i][j] = lab.labyrinth[i][j];
		}
		~DepthSearch() {
			for(int i = 0; i < visitedRow; i++)
				free(visited[i]);
			free(visited);   
		}
		double run() {
			clock_t timerA;
			clock_t timerB;
			
			timerA = clock();
			if(search(start)){
				while(!path.empty()){
					cout << "(" << path.top().fi << ", " << path.top().se << ") "; 
					visited[path.top().fi][path.top().se] = '0';
					path.pop();
				}
				cout << cost << endl;
				printVisited();
			}
			timerB = clock();
			return (double)(timerB - timerA)/(double)(CLOCKS_PER_SEC);				
		}

		void printVisited() {
			for(int i = 0; i < visitedRow; i++){
				for(int j = 0; j < visitedCol; j++){
					cout << visited[i][j];
				}
				cout << endl;
			}
		}

		// inicialmente, vamos tentar pintar só de uma cor. depois, podemos utilizar mais cores para encontrar o melhor caminho
		// nos labirintos pequenos (menor ou igual a 10x10)
		int search(pair<int, int> pos) {
			if(pos == end){
				path.push(pos);
				return 1;
			}
			visited[pos.fi][pos.se] = 'o';
			//norte
			if(pos.fi > 0 and visited[pos.fi-1][pos.se] != '-' and visited[pos.fi-1][pos.se] != 'o'){
				cost += 1.0;
				if(search(make_pair(pos.fi-1, pos.se))) {
					path.push(pos);
					return 1;
				}
				cost -= 1.0;
			}
			//nordeste
			if(pos.fi > 0 and pos.se < visitedCol-1 and visited[pos.fi-1][pos.se+1] != '-' and visited[pos.fi-1][pos.se+1] != 'o'){
				cost += sqrt(2);
				if(search(make_pair(pos.fi-1, pos.se+1))) {
					path.push(pos);
					return 1;
				}
				cost -= sqrt(2);
			}
			//leste
			if(pos.se < visitedCol-1 and visited[pos.fi][pos.se+1] != '-' and visited[pos.fi][pos.se+1] != 'o'){
				cost += 1.0;
				if(search(make_pair(pos.fi, pos.se+1))) {
					path.push(pos);
					return 1;
				}
				cost -= 1.0;
			}
			//sudeste
			if(pos.fi < visitedRow-1 and pos.second < visitedCol-1 and visited[pos.fi+1][pos.se+1] != '-' and visited[pos.fi+1][pos.se+1] != 'o'){
				cost += sqrt(2);
				if(search(make_pair(pos.fi+1, pos.se+1))) {
					path.push(pos);
					return 1;
				}
				cost -= sqrt(2);
			}
			//sul
			if(pos.fi < visitedRow-1 and visited[pos.fi+1][pos.se] != '-' and visited[pos.fi+1][pos.se] != 'o'){
				cost += 1.0;
				if(search(make_pair(pos.fi+1, pos.se))) {
					path.push(pos);
					return 1;
				}
				cost -= 1.0;
			}
			//sudoeste
			if(pos.fi < visitedRow-1 and pos.se > 0 and visited[pos.fi+1][pos.se-1] != '-' and visited[pos.fi+1][pos.se-1] != 'o'){
				cost += sqrt(2);
				if(search(make_pair(pos.fi+1, pos.se-1))) {
					path.push(pos);
					return 1;
				}
				cost -= sqrt(2);
			}
			//oeste
			if(pos.se > 0 and visited[pos.fi][pos.se-1] != '-' and visited[pos.fi][pos.se-1] != 'o'){
				cost += 1.0;
				if(search(make_pair(pos.fi, pos.se-1))) {
					path.push(pos);
					return 1;
				}
				cost -= 1.0;
			}
			//noroeste
			if(pos.fi > 0 and pos.se > 0 and visited[pos.fi-1][pos.se-1] != '-' and visited[pos.fi-1][pos.se-1] != 'o'){
				cost += sqrt(2);
				if(search(make_pair(pos.fi-1, pos.se-1))) {
					path.push(pos);
					return 1;
				}
				cost -= sqrt(2);
			}
			return 0;
		}
};

class BreadthSearch {
	private:
		double cost;
		int visitedRow;
		int visitedCol;
		pair<int, int> start;
		pair<int, int> end;
		stack<pair<int, int>> path;
		pair<int, double> **parent;
		char **visited;
	public:
		BreadthSearch(Labyrinth &lab) {
			cost = 0.0;
			visitedRow = lab.getRow();
			visitedCol = lab.getCol();
			start =  lab.getStart();
			end =  lab.getEnd();

			visited = (char **) malloc(sizeof(char *) * visitedRow);        
			for(int i = 0; i < visitedRow; i++)
				visited[i] = (char *) malloc(sizeof(char) * visitedCol);

			for(int i = 0; i < visitedRow; i++)
				for(int j = 0; j < visitedCol; j++)
					visited[i][j] = lab.labyrinth[i][j];
		
			parent = (pair<int, double> **) malloc(sizeof(pair<int, double>*) * visitedRow);        
			for(int i = 0; i < visitedRow; i++)
				parent[i] = (pair<int, double> *) malloc(sizeof(pair<int, double>) * visitedCol);

			for(int i = 0; i < visitedRow; i++)
				for(int j = 0; j < visitedCol; j++)
					parent[i][j] = make_pair(-1, 0.0);
		}
		~BreadthSearch() {
			for(int i = 0; i < visitedRow; i++)
				free(visited[i]);
			free(visited);

			for(int i = 0; i < visitedRow; i++)
				free(parent[i]);
			free(parent);   
		}
		double run() {
			clock_t timerA;
			clock_t timerB;
			timerA = clock();
			if(search()){
				while(!path.empty()){
					cout << "(" << path.top().fi << ", " << path.top().se << ") ";
					visited[path.top().fi][path.top().se] = '0';
					path.pop();
				}
				cost = parent[end.fi][end.se].se;
				cout << cost << endl;
				printVisited();
			}
			timerB = clock();
			return (double)(timerB-timerA)/(double)(CLOCKS_PER_SEC);
							
		}

		int search(){
			queue<pair<int, int>> q;
			visited[start.fi][start.se] = 'o';
			q.push(start);
			while(!q.empty()) {
				pair<int, int> aux = q.front();
				q.pop();
				if(aux == end) {
					path.push(aux);
					while(parent[aux.fi][aux.se].fi != -1) {
						pair<int, double> prnt = parent[aux.fi][aux.se];
						aux = make_pair((int)(prnt.fi/visitedCol),(prnt.fi%visitedCol));
						path.push(aux);						
					}
					return 1;
				}
				else{
					//norte
					if(aux.fi > 0 and visited[aux.fi-1][aux.se] != '-' and visited[aux.fi-1][aux.se] != 'o'){
						visited[aux.fi-1][aux.se] = 'o';
						q.push(make_pair(aux.fi-1, aux.se));
						parent[aux.fi-1][aux.se] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//nordeste
					if(aux.fi > 0 and aux.se < visitedCol-1 and visited[aux.fi-1][aux.se+1] != '-' and visited[aux.fi-1][aux.se+1] != 'o'){
						visited[aux.fi-1][aux.se+1] = 'o';
						q.push(make_pair(aux.fi-1, aux.se+1));
						parent[aux.fi-1][aux.se+1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
					//leste
					if(aux.se < visitedCol-1 and visited[aux.fi][aux.se+1] != '-' and visited[aux.fi][aux.se+1] != 'o'){
						visited[aux.fi][aux.se+1] = 'o';
						q.push(make_pair(aux.fi, aux.se+1));
						parent[aux.fi][aux.se+1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//sudeste
					if(aux.fi < visitedRow-1 and aux.second < visitedCol-1 and visited[aux.fi+1][aux.se+1] != '-' and visited[aux.fi+1][aux.se+1] != 'o'){
						visited[aux.fi+1][aux.se+1] = 'o';
						q.push(make_pair(aux.fi+1, aux.se+1));
						parent[aux.fi+1][aux.se+1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
					//sul
					if(aux.fi < visitedRow-1 and visited[aux.fi+1][aux.se] != '-' and visited[aux.fi+1][aux.se] != 'o'){
						visited[aux.fi+1][aux.se] = 'o';
						q.push(make_pair(aux.fi+1, aux.se));
						parent[aux.fi+1][aux.se] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//sudoeste
					if(aux.fi < visitedRow-1 and aux.se > 0 and visited[aux.fi+1][aux.se-1] != '-' and visited[aux.fi+1][aux.se-1] != 'o'){
						visited[aux.fi+1][aux.se-1] = 'o';
						q.push(make_pair(aux.fi+1, aux.se-1));
						parent[aux.fi+1][aux.se-1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
					//oeste
					if(aux.se > 0 and visited[aux.fi][aux.se-1] != '-' and visited[aux.fi][aux.se-1] != 'o'){
						visited[aux.fi][aux.se-1] = 'o';
						q.push(make_pair(aux.fi, aux.se-1));
						parent[aux.fi][aux.se-1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//noroeste
					if(aux.fi > 0 and aux.se > 0 and visited[aux.fi-1][aux.se-1] != '-' and visited[aux.fi-1][aux.se-1] != 'o'){
						visited[aux.fi-1][aux.se-1] = 'o';
						q.push(make_pair(aux.fi-1, aux.se-1));
						parent[aux.fi-1][aux.se-1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
				}
			}
			return 0;
		}

		void printVisited() {
			for(int i = 0; i < visitedRow; i++){
				for(int j = 0; j < visitedCol; j++){
					cout << visited[i][j];
				}
				cout << endl;
			}
		}

};

class BestSearch {
	private:
		double cost;
		int visitedRow;
		int visitedCol;
		int manhattan;
		pair<int, int> start;
		pair<int, int> end;
		stack<pair<int, int>> path;
		pair<int, double> **parent;
		char **visited;
	public:
		BestSearch(Labyrinth &lab) {
			cost = 0.0;
			visitedRow = lab.getRow();
			visitedCol = lab.getCol();
			start =  lab.getStart();
			end =  lab.getEnd();

			visited = (char **) malloc(sizeof(char *) * visitedRow);        
			for(int i = 0; i < visitedRow; i++)
				visited[i] = (char *) malloc(sizeof(char) * visitedCol);

			for(int i = 0; i < visitedRow; i++)
				for(int j = 0; j < visitedCol; j++)
					visited[i][j] = lab.labyrinth[i][j];
		
			parent = (pair<int, double> **) malloc(sizeof(pair<int, double>*) * visitedRow);        
			for(int i = 0; i < visitedRow; i++)
				parent[i] = (pair<int, double> *) malloc(sizeof(pair<int, double>) * visitedCol);

			for(int i = 0; i < visitedRow; i++)
				for(int j = 0; j < visitedCol; j++)
					parent[i][j] = make_pair(-1, 0.0);
		}
		~BestSearch() {
			for(int i = 0; i < visitedRow; i++)
				free(visited[i]);
			free(visited);

			for(int i = 0; i < visitedRow; i++)
				free(parent[i]);
			free(parent);   
		}
		double run() {
			clock_t timerA;
			clock_t timerB;
			timerA = clock();
			if(search()){
				while(!path.empty()){
					cout << "(" << path.top().fi << ", " << path.top().se << ") ";
					visited[path.top().fi][path.top().se] = '0';
					path.pop();
				}
				cost = parent[end.fi][end.se].se;
				cout << cost << endl;
				printVisited();
			}
			timerB = clock();

			return (double)(timerB - timerA)/(double)(CLOCKS_PER_SEC);
							
		}

		int search(){
			priority_queue <pair<int, pair<int, int> > > q;

			visited[start.fi][start.se] = 'o';
			q.push(make_pair(0, start));
			while(!q.empty()) {

				pair<int, int> aux = q.top().se;
				q.pop();
				if(aux == end) {
					path.push(aux);
					while(parent[aux.fi][aux.se].fi != -1) {
						pair<int, double> prnt = parent[aux.fi][aux.se];
						aux = make_pair((int)(prnt.fi/visitedCol),(prnt.fi%visitedCol));
						path.push(aux);						
					}
					return 1;
				}
				else{
					//norte
					if(aux.fi > 0 and visited[aux.fi-1][aux.se] != '-' and visited[aux.fi-1][aux.se] != 'o'){
						manhattan = abs((aux.fi-1 - end.fi) + (aux.se - end.se));
						visited[aux.fi-1][aux.se] = 'o';
						q.push(make_pair(-manhattan, make_pair(aux.fi-1, aux.se)));
						parent[aux.fi-1][aux.se] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//nordeste
					if(aux.fi > 0 and aux.se < visitedCol-1 and visited[aux.fi-1][aux.se+1] != '-' and visited[aux.fi-1][aux.se+1] != 'o'){
						manhattan = abs((aux.fi-1 - end.fi) + (aux.se+1 - end.se));
						visited[aux.fi-1][aux.se+1] = 'o';
						q.push(make_pair(-manhattan, make_pair(aux.fi-1, aux.se+1)));
						parent[aux.fi-1][aux.se+1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
					//leste
					if(aux.se < visitedCol-1 and visited[aux.fi][aux.se+1] != '-' and visited[aux.fi][aux.se+1] != 'o'){
						manhattan = abs((aux.fi - end.fi) + (aux.se+1 - end.se));
						visited[aux.fi][aux.se+1] = 'o';
						q.push(make_pair(-manhattan, make_pair(aux.fi, aux.se+1)));
						parent[aux.fi][aux.se+1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//sudeste
					if(aux.fi < visitedRow-1 and aux.second < visitedCol-1 and visited[aux.fi+1][aux.se+1] != '-' and visited[aux.fi+1][aux.se+1] != 'o'){
						manhattan = abs((aux.fi+1 - end.fi) + (aux.se+1 - end.se));
						visited[aux.fi+1][aux.se+1] = 'o';
						q.push(make_pair(-manhattan, make_pair(aux.fi+1, aux.se+1)));
						parent[aux.fi+1][aux.se+1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
					//sul
					if(aux.fi < visitedRow-1 and visited[aux.fi+1][aux.se] != '-' and visited[aux.fi+1][aux.se] != 'o'){
						manhattan = abs((aux.fi+1 - end.fi) + (aux.se - end.se));
						visited[aux.fi+1][aux.se] = 'o';
						q.push(make_pair(-manhattan, make_pair(aux.fi+1, aux.se)));
						parent[aux.fi+1][aux.se] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//sudoeste
					if(aux.fi < visitedRow-1 and aux.se > 0 and visited[aux.fi+1][aux.se-1] != '-' and visited[aux.fi+1][aux.se-1] != 'o'){
						manhattan = abs((aux.fi+1 - end.fi) + (aux.se-1 - end.se));
						visited[aux.fi+1][aux.se-1] = 'o';
						q.push(make_pair(-manhattan, make_pair(aux.fi+1, aux.se-1)));
						parent[aux.fi+1][aux.se-1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
					//oeste
					if(aux.se > 0 and visited[aux.fi][aux.se-1] != '-' and visited[aux.fi][aux.se-1] != 'o'){
						manhattan = abs((aux.fi - end.fi) + (aux.se-1 - end.se));
						visited[aux.fi][aux.se-1] = 'o';
						q.push(make_pair(-manhattan, make_pair(aux.fi, aux.se-1)));
						parent[aux.fi][aux.se-1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//noroeste
					if(aux.fi > 0 and aux.se > 0 and visited[aux.fi-1][aux.se-1] != '-' and visited[aux.fi-1][aux.se-1] != 'o'){
						manhattan = abs((aux.fi-1 - end.fi) + (aux.se-1 - end.se));
						visited[aux.fi-1][aux.se-1] = 'o';
						q.push(make_pair(-manhattan, make_pair(aux.fi-1, aux.se-1)));
						parent[aux.fi-1][aux.se-1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
				}
			}
			return 0;
		}

		void printVisited() {
			for(int i = 0; i < visitedRow; i++){
				for(int j = 0; j < visitedCol; j++){
					cout << visited[i][j];
				}
				cout << endl;
			}
		}

};

int main() { 

	int cases;
	cin >> cases;
	int count = cases;
	double timeDepthSearch = 0.0;
	double timeBreadthSearch = 0.0;
	double timeBestSearch = 0.0;
	double timeA = 0.0;

	while(count > 0) {
		count--;
		int row, col;
		cin >> row >> col;
		Labyrinth lab(row, col); 
		lab.readInput();
		lab.printLab();
		DepthSearch ds(lab);
		timeDepthSearch += ds.run();
		BreadthSearch bs(lab);
		timeBreadthSearch += bs.run();
		BestSearch bests(lab);
		timeBestSearch += bests.run();

	}
	timeDepthSearch = timeDepthSearch/cases;
	timeBreadthSearch =  timeBreadthSearch/cases;
	timeBestSearch =  timeBestSearch/cases;

	printf("Media DS: %lf\n", timeDepthSearch);
	printf("Media BS: %lf\n", timeBreadthSearch);
	printf("Media BestS: %lf\n", timeBestSearch);
	
	return 0;
}
