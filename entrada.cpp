#include <iostream>
#include <cstdlib>
#include <float.h>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <cmath>
#include <map>
#include <set>

#define fi first
#define se second

#define DEBUG 1
#define WALL '-'
#define FREE_PATH '*'
#define VISITED 'o'
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
					if(labyrinth[i][j] == '#')
						start = make_pair(i, j);
					else if(labyrinth[i][j] == '$')
						end = make_pair(i, j);
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
		char **visited2;
	public:
		DepthSearch(Labyrinth lab) {
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

			visited2 = (char **) malloc(sizeof(char *) * visitedRow);        
			for(int i = 0; i < visitedRow; i++)
				visited2[i] = (char *) malloc(sizeof(char) * visitedCol);

			for(int i = 0; i < visitedRow; i++)
				for(int j = 0; j < visitedCol; j++)
					visited2[i][j] = lab.labyrinth[i][j];
		}
		~DepthSearch() {
			for(int i = 0; i < visitedRow; i++)
				free(visited[i]);
			free(visited);   
		}
		void run() {
			if(search(start)){
				while(!path.empty()){
					cout << "(" << path.top().fi << ", " << path.top().se << ")" << endl;
					path.pop();
				}
				cout << cost << endl;
				// teste();
				printVisited();
			}
				
		}
		// void teste(){
		// 	int t = (int)path.size();

		// 	for(int k=0; k<t; k++){
		// 		int a = path.top().fi;
		// 		int b = path.top().se;
		// 		path.pop();
		// 		visited2[a][b] = 'o'; 
		// 		for(int i = 0; i < visitedRow; i++) {
		// 			for(int j = 0; j < visitedCol; j++)
		// 				cout << visited2[i][j];
		// 			cout << endl;
		// 		}
		// 		cout << endl;
		// 	}
		// }
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
		int **parent;
		char **visited;
	public:
		BreadthSearch(Labyrinth lab) {
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

			parent = (int **) malloc(sizeof(int *) * visitedRow);        
			for(int i = 0; i < visitedRow; i++)
				parent[i] = (int *) malloc(sizeof(int) * visitedCol);

			for(int i = 0; i < visitedRow; i++)
				for(int j = 0; j < visitedCol; j++)
					parent[i][j] = -1;
		}
		~BreadthSearch() {
			for(int i = 0; i < visitedRow; i++)
				free(visited[i]);
			free(visited);

			for(int i = 0; i < visitedRow; i++)
				free(parent[i]);
			free(parent);   
		}
		void run() {
			queue<pair<int, int>> q;
			visited[start.fi][start.se] = 'o';
			q.push(start);
			while(!q.empty()) {
				pair<int, int> aux = q.front();
				q.pop();
				if(aux == end) {
					while(parent[aux.fi][aux.se] != -1) {
						
					}
					
				}


			}

				
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

	public:
		A_StarSearch(Labyrinth &lab) {
			cost = 0.0;
			SetLabyrinthVariables(lab);
			CreateVisitedMatrix(lab);
			
			Matrix::PrintCharMatrix(visited, rowSize, colSize);
		}
		~A_StarSearch() {
			Matrix::FreeCharMatrix(visited, rowSize);
		}
		void Run() {
			printf("Começando a busca A*\n");
			int returned = Search(start);
		}

		int Search(pair<int, int> currentPos){
			if (currentPos == end){
				printf("You are already in the end!\n");
				return 1;
			}

			// Criando a matriz com os detalhes de cada nó já conhecido
			Node** posDetails = (Node**) malloc(sizeof(Node*) * rowSize);
			for (int i = 0; i < rowSize; ++i) {
				posDetails[i] = (Node*) malloc(sizeof(Node) * colSize);
				std::fill(posDetails[i], posDetails[i]+colSize, Node());
			}

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
								printf("CHEGOU AO FIM!\n");
								goalReached = true;
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

									if(DEBUG) printf("(%d, %d) G: %lf, H: %lf, F: %lf\n", newPos.fi, newPos.se, newG, newH, newF);
									candidates.insert(SetPos(newPos.first, newPos.second, newF));
								}
							}
						}
					}
				}
			}

			if (goalReached == false)
				printf("Caminho não encontrado!!\n");
			
			// Destroi a matriz com as infos de cada nó
			for (int i = 0; i < rowSize; ++i)
				free(posDetails[i]);
			free(posDetails);

			return 0;
		}
		void PrintVisited() {
			Matrix::PrintCharMatrix(visited, rowSize, colSize);
		}
};

int main() { 

	int cases;
	int count = 0;
	cin >> cases;

	while(cases > 0) {
		cases--;
		int row, col;
		cin >> row >> col;
		Labyrinth lab(row, col); 
		//DepthSearch  
		lab.readInput();
		lab.printLab();
		//DepthSearch ds(lab);
		//ds.run();
		A_StarSearch aStar(lab);
		aStar.Run();
		aStar.PrintVisited();
	}
		
	

}