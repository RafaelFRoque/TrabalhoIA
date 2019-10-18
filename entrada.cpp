#include <iostream>
#include <cstdlib>
#include <float.h>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <ctime>
#include <cmath>
#include <map>
#include <set>

#define fi first
#define se second

#define DEBUG 0
#define WALL '-'
#define FREE_PATH '*'
#define VISITED 'o'
#define MINIMUM_PATH '0'
#define START '#'
#define GOAL '$'

#define SIDE_COST 1
#define DIAGONAL_COST 1.41421356	// sqrt(2)
#define MOVEMENT_COST(i, j) ((i == 0 || j == 0) ? (SIDE_COST) : (DIAGONAL_COST))
#define SET_MATRIX_AT(matrix, point, value) matrix[point.first][point.second] = value
#define IS_POS_VALID(pos) (pos.fi >= 0 && pos.fi < rowSize && pos.se >= 0 && pos.se < colSize)
#define CALCULATE_DIST_TO_GOAL(pos, goal) (sqrt ((pos.fi - goal.fi)*(pos.fi - goal.fi)  +(pos.se - goal.se)*(pos.se - goal.se)))

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
					}
					else if(labyrinth[i][j] == '$'){
						end = make_pair(i, j);
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
				cout << endl;
				cout << "Custo do caminho " << cost << endl;
				printVisited();
			}
			timerB = clock();
			return (double)(timerB - timerA)/(double)(CLOCKS_PER_SEC);				
		}

		void printVisited() {
			for(int i = 0; i < visitedCol+2; i++)
				cout<< "- ";
			
			cout << endl;
			for(int i = 0; i < visitedRow; i++){
				cout << "| ";
				for(int j = 0; j < visitedCol; j++){
					if(visited[i][j] == '+')
						cout << "* ";
					else{
						cout << visited[i][j]<< " ";
					}
				}
				
				cout << "|"<< endl;
			}
			for(int i = 0; i < visitedCol+2; i++)
				cout<< "- ";
			cout << endl;
		}

		// inicialmente, vamos tentar pintar só de uma cor. depois, podemos utilizar mais cores para encontrar o melhor caminho
		// nos labirintos pequenos (menor ou igual a 10x10)
		int search(pair<int, int> pos) {
			if(pos == end){
				path.push(pos);
				return 1;
			}
			visited[pos.fi][pos.se] = '+';
			//norte
			if(pos.fi > 0 and visited[pos.fi-1][pos.se] != '-' and visited[pos.fi-1][pos.se] != '+'){
				cost += 1.0;
				if(search(make_pair(pos.fi-1, pos.se))) {
					path.push(pos);
					return 1;
				}
				cost -= 1.0;
			}
			//nordeste
			if(pos.fi > 0 and pos.se < visitedCol-1 and visited[pos.fi-1][pos.se+1] != '-' and visited[pos.fi-1][pos.se+1] != '+'){
				cost += sqrt(2);
				if(search(make_pair(pos.fi-1, pos.se+1))) {
					path.push(pos);
					return 1;
				}
				cost -= sqrt(2);
			}
			//leste
			if(pos.se < visitedCol-1 and visited[pos.fi][pos.se+1] != '-' and visited[pos.fi][pos.se+1] != '+'){
				cost += 1.0;
				if(search(make_pair(pos.fi, pos.se+1))) {
					path.push(pos);
					return 1;
				}
				cost -= 1.0;
			}
			//sudeste
			if(pos.fi < visitedRow-1 and pos.second < visitedCol-1 and visited[pos.fi+1][pos.se+1] != '-' and visited[pos.fi+1][pos.se+1] != '+'){
				cost += sqrt(2);
				if(search(make_pair(pos.fi+1, pos.se+1))) {
					path.push(pos);
					return 1;
				}
				cost -= sqrt(2);
			}
			//sul
			if(pos.fi < visitedRow-1 and visited[pos.fi+1][pos.se] != '-' and visited[pos.fi+1][pos.se] != '+'){
				cost += 1.0;
				if(search(make_pair(pos.fi+1, pos.se))) {
					path.push(pos);
					return 1;
				}
				cost -= 1.0;
			}
			//sudoeste
			if(pos.fi < visitedRow-1 and pos.se > 0 and visited[pos.fi+1][pos.se-1] != '-' and visited[pos.fi+1][pos.se-1] != '+'){
				cost += sqrt(2);
				if(search(make_pair(pos.fi+1, pos.se-1))) {
					path.push(pos);
					return 1;
				}
				cost -= sqrt(2);
			}
			//oeste
			if(pos.se > 0 and visited[pos.fi][pos.se-1] != '-' and visited[pos.fi][pos.se-1] != '+'){
				cost += 1.0;
				if(search(make_pair(pos.fi, pos.se-1))) {
					path.push(pos);
					return 1;
				}
				cost -= 1.0;
			}
			//noroeste
			if(pos.fi > 0 and pos.se > 0 and visited[pos.fi-1][pos.se-1] != '-' and visited[pos.fi-1][pos.se-1] != '+'){
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
				cout << endl;
				cost = parent[end.fi][end.se].se;
				cout << "Custo do caminho " << cost << endl;
				printVisited();
			}
			timerB = clock();
			return (double)(timerB-timerA)/(double)(CLOCKS_PER_SEC);
							
		}

		int search(){
			queue<pair<int, int>> q;
			visited[start.fi][start.se] = '+';
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
					if(aux.fi > 0 and visited[aux.fi-1][aux.se] != '-' and visited[aux.fi-1][aux.se] != '+'){
						visited[aux.fi-1][aux.se] = '+';
						q.push(make_pair(aux.fi-1, aux.se));
						parent[aux.fi-1][aux.se] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//nordeste
					if(aux.fi > 0 and aux.se < visitedCol-1 and visited[aux.fi-1][aux.se+1] != '-' and visited[aux.fi-1][aux.se+1] != '+'){
						visited[aux.fi-1][aux.se+1] = '+';
						q.push(make_pair(aux.fi-1, aux.se+1));
						parent[aux.fi-1][aux.se+1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
					//leste
					if(aux.se < visitedCol-1 and visited[aux.fi][aux.se+1] != '-' and visited[aux.fi][aux.se+1] != '+'){
						visited[aux.fi][aux.se+1] = '+';
						q.push(make_pair(aux.fi, aux.se+1));
						parent[aux.fi][aux.se+1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//sudeste
					if(aux.fi < visitedRow-1 and aux.second < visitedCol-1 and visited[aux.fi+1][aux.se+1] != '-' and visited[aux.fi+1][aux.se+1] != '+'){
						visited[aux.fi+1][aux.se+1] = '+';
						q.push(make_pair(aux.fi+1, aux.se+1));
						parent[aux.fi+1][aux.se+1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
					//sul
					if(aux.fi < visitedRow-1 and visited[aux.fi+1][aux.se] != '-' and visited[aux.fi+1][aux.se] != '+'){
						visited[aux.fi+1][aux.se] = '+';
						q.push(make_pair(aux.fi+1, aux.se));
						parent[aux.fi+1][aux.se] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//sudoeste
					if(aux.fi < visitedRow-1 and aux.se > 0 and visited[aux.fi+1][aux.se-1] != '-' and visited[aux.fi+1][aux.se-1] != '+'){
						visited[aux.fi+1][aux.se-1] = '+';
						q.push(make_pair(aux.fi+1, aux.se-1));
						parent[aux.fi+1][aux.se-1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
					//oeste
					if(aux.se > 0 and visited[aux.fi][aux.se-1] != '-' and visited[aux.fi][aux.se-1] != '+'){
						visited[aux.fi][aux.se-1] = '+';
						q.push(make_pair(aux.fi, aux.se-1));
						parent[aux.fi][aux.se-1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//noroeste
					if(aux.fi > 0 and aux.se > 0 and visited[aux.fi-1][aux.se-1] != '-' and visited[aux.fi-1][aux.se-1] != '+'){
						visited[aux.fi-1][aux.se-1] = '+';
						q.push(make_pair(aux.fi-1, aux.se-1));
						parent[aux.fi-1][aux.se-1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
				}
			}
			return 0;
		}

		void printVisited() {
			for(int i = 0; i < visitedCol+2; i++)
				cout<< "- ";
			
			cout << endl;
			for(int i = 0; i < visitedRow; i++){
				cout << "| ";
				for(int j = 0; j < visitedCol; j++){
					if(visited[i][j] == '+')
						cout << "* ";
					else{
						cout << visited[i][j]<< " ";
					}
				}
				
				cout << "|"<<endl;
			}
			for(int i = 0; i < visitedCol+2; i++)
				cout<< "- ";
			cout << endl;
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
				cout << endl;
				cost = parent[end.fi][end.se].se;
				cout << "Custo do caminho " << cost << endl;
				printVisited();
			}
			timerB = clock();

			return (double)(timerB - timerA)/(double)(CLOCKS_PER_SEC);
							
		}

		int search(){
			priority_queue <pair<int, pair<int, int> > > q;

			visited[start.fi][start.se] = '+';
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
					if(aux.fi > 0 and visited[aux.fi-1][aux.se] != '-' and visited[aux.fi-1][aux.se] != '+'){
						manhattan = abs((aux.fi-1 - end.fi) + (aux.se - end.se));
						visited[aux.fi-1][aux.se] = '+';
						q.push(make_pair(-manhattan, make_pair(aux.fi-1, aux.se)));
						parent[aux.fi-1][aux.se] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//nordeste
					if(aux.fi > 0 and aux.se < visitedCol-1 and visited[aux.fi-1][aux.se+1] != '-' and visited[aux.fi-1][aux.se+1] != '+'){
						manhattan = abs((aux.fi-1 - end.fi) + (aux.se+1 - end.se));
						visited[aux.fi-1][aux.se+1] = '+';
						q.push(make_pair(-manhattan, make_pair(aux.fi-1, aux.se+1)));
						parent[aux.fi-1][aux.se+1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
					//leste
					if(aux.se < visitedCol-1 and visited[aux.fi][aux.se+1] != '-' and visited[aux.fi][aux.se+1] != '+'){
						manhattan = abs((aux.fi - end.fi) + (aux.se+1 - end.se));
						visited[aux.fi][aux.se+1] = '+';
						q.push(make_pair(-manhattan, make_pair(aux.fi, aux.se+1)));
						parent[aux.fi][aux.se+1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//sudeste
					if(aux.fi < visitedRow-1 and aux.second < visitedCol-1 and visited[aux.fi+1][aux.se+1] != '-' and visited[aux.fi+1][aux.se+1] != '+'){
						manhattan = abs((aux.fi+1 - end.fi) + (aux.se+1 - end.se));
						visited[aux.fi+1][aux.se+1] = '+';
						q.push(make_pair(-manhattan, make_pair(aux.fi+1, aux.se+1)));
						parent[aux.fi+1][aux.se+1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
					//sul
					if(aux.fi < visitedRow-1 and visited[aux.fi+1][aux.se] != '-' and visited[aux.fi+1][aux.se] != '+'){
						manhattan = abs((aux.fi+1 - end.fi) + (aux.se - end.se));
						visited[aux.fi+1][aux.se] = '+';
						q.push(make_pair(-manhattan, make_pair(aux.fi+1, aux.se)));
						parent[aux.fi+1][aux.se] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//sudoeste
					if(aux.fi < visitedRow-1 and aux.se > 0 and visited[aux.fi+1][aux.se-1] != '-' and visited[aux.fi+1][aux.se-1] != '+'){
						manhattan = abs((aux.fi+1 - end.fi) + (aux.se-1 - end.se));
						visited[aux.fi+1][aux.se-1] = '+';
						q.push(make_pair(-manhattan, make_pair(aux.fi+1, aux.se-1)));
						parent[aux.fi+1][aux.se-1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
					//oeste
					if(aux.se > 0 and visited[aux.fi][aux.se-1] != '-' and visited[aux.fi][aux.se-1] != '+'){
						manhattan = abs((aux.fi - end.fi) + (aux.se-1 - end.se));
						visited[aux.fi][aux.se-1] = '+';
						q.push(make_pair(-manhattan, make_pair(aux.fi, aux.se-1)));
						parent[aux.fi][aux.se-1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + 1.0);
					}
					//noroeste
					if(aux.fi > 0 and aux.se > 0 and visited[aux.fi-1][aux.se-1] != '-' and visited[aux.fi-1][aux.se-1] != '+'){
						manhattan = abs((aux.fi-1 - end.fi) + (aux.se-1 - end.se));
						visited[aux.fi-1][aux.se-1] = '+';
						q.push(make_pair(-manhattan, make_pair(aux.fi-1, aux.se-1)));
						parent[aux.fi-1][aux.se-1] = make_pair(((aux.fi)*visitedCol + aux.se), parent[aux.fi][aux.se].se + sqrt(2));
					}
				}
			}
			return 0;
		}

		void printVisited() {
			for(int i = 0; i < visitedCol+2; i++){
				cout<< "- ";
			}
			cout << endl;
			for(int i = 0; i < visitedRow; i++){
				cout << "| ";
				for(int j = 0; j < visitedCol; j++){
					if(visited[i][j] == '+')
						cout << "* ";
					else{
						cout << visited[i][j]<< " ";
					}
				}
				
				cout << "|"<<endl;
			}
			for(int i = 0; i < visitedCol+2; i++)
				cout<< "- ";
			cout << endl;
		}

};

class Matrix {
	public:
		static void CreateCharMatrix(char** &matrix, int rows, int columns) {
			matrix = (char**) malloc(sizeof(char*) * rows);
			for (int i = 0; i < rows; ++i) {
				matrix[i] = (char*) malloc(sizeof(char) * columns);
			}
		}
		static void FreeCharMatrix(char** &matrix, int rows) {
			for (int i = 0; i < rows; ++i) {
				free(matrix[i]);
			}
			free(matrix);
		}
		static void PrintCharMatrix(char** &matrix, int rows, int columns) {
			for(int i = 0; i < rows; i++){
				for(int j = 0; j < columns; j++){
					printf("%c", matrix[i][j]);
				}
				printf("\n");
			}
			printf("\n");
		}
};

class Node {
	public:
		pair<int, int> parent;
		double f, g, h;
		Node() {
			parent = make_pair(-1, -1);
			f = FLT_MAX;
			g = FLT_MAX;
			h = FLT_MAX;
		}
		Node(int parentX, int parentY, int F, int G, int H) {
			parent = make_pair(parentX, parentY);
			f = F;
			g = G;
			h = H;
		}
		bool operator< (const Node &right) const {
			return f < right.f;
		}
		void Print() {
			printf("Parent: (%d, %d). f:%lf g:%lf h:%lf\n", parent.first, parent.second, f, g, h);
		}
};

class SetPos {
	public:
		pair<int, int> pos;
		double f;
		SetPos() {
			pos = make_pair(0, 0);
			f = 0;
		}
		SetPos(int x, int y, double F) {
			pos = make_pair(x, y);
			f = F;
		}
		bool operator< (const SetPos &right) const {
			return f < right.f;
		}
		void Print() {
			printf("pos: (%d, %d). f: %lf\n", pos.first, pos.second, f);
		}
};

class SearchBase {
	protected:
		int rowSize;
		int colSize;
		pair<int, int> start;
		pair<int, int> end;
		char **visited;
	public:
		void SetLabyrinthVariables(Labyrinth &lab) {
			rowSize = lab.getRow();
			colSize = lab.getCol();
			start =  lab.getStart();
			end =  lab.getEnd();
		}
		void CreateVisitedMatrix(Labyrinth &lab) {
			Matrix::CreateCharMatrix(visited, rowSize, colSize);
			for(int i = 0; i < rowSize; i++)
				for(int j = 0; j < colSize; j++)
					visited[i][j] = lab.labyrinth[i][j];
		}
};

class A_StarSearch : public SearchBase {
	private:
		double cost;
		Node** posDetails;
	public:
		A_StarSearch(Labyrinth &lab) {
			cost = 0.0;
			SetLabyrinthVariables(lab);
			CreateVisitedMatrix(lab);

			posDetails = (Node**) malloc(sizeof(Node*) * rowSize);
			for (int i = 0; i < rowSize; ++i) {
				posDetails[i] = (Node*) malloc(sizeof(Node) * colSize);
				std::fill(posDetails[i], posDetails[i]+colSize, Node());
			}
		}
		~A_StarSearch() {
			Matrix::FreeCharMatrix(visited, rowSize);
			
			// Destroi a matriz com as infos de cada nó
			for (int i = 0; i < rowSize; ++i)
				free(posDetails[i]);
			free(posDetails);
		}

		void PrintPath() {
			pair<int, int> pos = end;
			stack<pair<int, int>> path;

			while (!(posDetails[pos.first][pos.second].parent.first == pos.first &&
					 posDetails[pos.first][pos.second].parent.second == pos.second)) {
				path.push (pos);
				visited[pos.first][pos.second] = MINIMUM_PATH;
				pos = posDetails[pos.first][pos.second].parent;
			}
			path.push (pos);
			visited[pos.first][pos.second] = MINIMUM_PATH;

			while (!path.empty()) {
				pos = path.top();
				path.pop();
				printf("(%d, %d) ", pos.first, pos.second);
			}
			printf("\n");
		}

		void Run() {
			int returned = Search(start);
			if (returned){
				PrintPath();
				printf("Custo do caminho %.4lf\n", cost);
				PrintVisited();
			}
		}

		int Search(pair<int, int> currentPos){
			if (currentPos == end){
				if(DEBUG)printf("You are already in the end!\n");
				return 1;
			}

			// Criando a matriz com os detalhes de cada nó já conhecido

			// Inicializando com a posição inicial
			int x = currentPos.first, y = currentPos.second;
			posDetails[x][y].parent = make_pair(x, y);
			posDetails[x][y].f = 0;
			posDetails[x][y].g = 0;
			posDetails[x][y].h = 0;

			// Set com os candidatos para a próxima movimentação
			set<SetPos> candidates;
			
			candidates.insert(SetPos(x, y, 0));

			bool goalReached = false;

			while(!candidates.empty()) {
				SetPos p = *candidates.begin();
				candidates.erase(candidates.begin());

				if(DEBUG) p.Print();
				// Marca como visitado
				x = p.pos.first;
				y = p.pos.second;
				visited[x][y] = VISITED;

				double newF, newG, newH;

				for (int i = -1; i < 2; ++i) {
					for (int j = -1; j < 2; ++j) {
						pair<int, int> newPos(x+i, y+j);
						//if(DEBUG) printf("Pos == %d,%d\n", newPos.fi, newPos.se);
						// Se i e j forem iguais a zero, a nova posição é a mesma que a atual.
						// Portanto, deve-se ignorar este caso. O mesmo acontece caso a nova posição
						// esteja fora da dimensão do labirinto.
						if ((i != 0 || j != 0) && IS_POS_VALID(newPos)) {
							//if(DEBUG) printf("Pos válida\n");

							// Chegou ao fim!
							if (newPos == end) {
								posDetails[newPos.first][newPos.second].parent = make_pair(x, y);
								if(DEBUG)printf("CHEGOU AO FIM A*!\n");
								goalReached = true;
								cost = posDetails[x][y].g + MOVEMENT_COST(i, j);
								return 1;
							}
							else if(visited[newPos.first][newPos.second] == FREE_PATH){
								newG = posDetails[x][y].g + MOVEMENT_COST(i, j);
								newH = CALCULATE_DIST_TO_GOAL(newPos, end);
								newF = newG + newH;

								if (posDetails[newPos.first][newPos.second].f == FLT_MAX ||
									posDetails[newPos.first][newPos.second].f > newF) {

									posDetails[newPos.first][newPos.second].parent = make_pair(x, y);
									posDetails[newPos.first][newPos.second].f = newF;
									posDetails[newPos.first][newPos.second].g = newG;
									posDetails[newPos.first][newPos.second].h = newH;

									candidates.insert(SetPos(newPos.first, newPos.second, newF));
								}
							}
						}
					}
				}
			}

			if (goalReached == false)
				printf("Caminho não encontrado.\n");

			return 0;
		}
		void PrintVisited() {
			for (int i = 0; i < colSize+2; ++i)
				printf("- ");
			printf("\n");

			for (int i = 0; i < rowSize; ++i) {
				printf("| ");
				for (int j = 0; j < colSize; ++j)
					printf("%c ", (visited[i][j] == VISITED) ? '*' : visited[i][j]);
				printf("|\n");
			}

			for (int i = 0; i < colSize+2; ++i)
				printf("- ");
			printf("\n");
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
		DepthSearch ds(lab);
		timeDepthSearch += ds.run();
		BreadthSearch bs(lab);
		timeBreadthSearch += bs.run();
		BestSearch bests(lab);
		timeBestSearch += bests.run();
		A_StarSearch aStar(lab);
		aStar.Run();
	}
	
	timeDepthSearch = timeDepthSearch/cases;
	timeBreadthSearch =  timeBreadthSearch/cases;
	timeBestSearch =  timeBestSearch/cases;

	printf("Media DS: %lf\n", timeDepthSearch);
	printf("Media BS: %lf\n", timeBreadthSearch);
	printf("Media BestS: %lf\n", timeBestSearch);
	
	return 0;
}
