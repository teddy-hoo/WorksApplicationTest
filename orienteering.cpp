#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

char START      = 'S';
char GOAL       = 'G';
char CHECKPOINT = '@';
char OPENBLOCK  = '.';
char CLOESBLOCK = '#';

typedef struct Nodes
{
	int cost;
	int index;
	char flag;
	int pos[2];
	Nodes * next;

	Nodes(char f, int i, int c, Nodes* n, int p[2]){
		index = i;
		flag = f;
		cost = c;
		next = n;
		pos[0] = p[0];
		pos[1] = p[1];
	}
} Node;

class Orienteering{

private:

	vector<Node *> graph;
	vector<vector<char> > metrix;
	int startPoint[2];
	string endPoint;
	int checkPointCount;
	int passedCP;
	int steps;
	int height;
	int width;

public:
	Orienteering(){
		height = -1;
		width  = -1;
		checkPointCount = 0;
	}

	void main(){
		
		readData();

		if(checkParams()){
			cout << -1 << endl;
		}

		buildGraph();
		cout << findPath() << endl;

	}

private:

	int findPath(){
		int max = -1;

		stack<Node *> sn;
		vector<int> si;
		sn.push(graph[0]);
		si.push_back(0);

		int path = 0;
		while(!sn.empty()){
			if(si.size() == graph.size()){
				int top = si.back();
				if(graph[top]->flag == GOAL){
					max = path > max ? path : max;
				}
				break;
				si.pop_back();
				sn.pop();
			}
			Node * cur = sn.top();
			Node * next = cur->next;

			while(next != NULL){
				bool has = false;
				for(int i = 0; i < si.size(); i++){
					if(si[i] == next->index){
						has = true;
					}
				}
				if(has == false){
					break;
				}
				next = next->next;
			}
			if(next == NULL){
				sn.pop();
				si.pop_back();
			}

			else{
				path += next->cost;
				sn.pop();
				sn.push(next);
				si.push_back(next->index);
				sn.push(graph[next->index]);
			}
		}
		return max;
	}

	void readData(){

		string line;
		
		cin >> width >> height;
		
		for(int i = 0; i < height; ++i){
			cin >> line;
			buildMatrix(line, i);
		}

	}

	bool checkParams(){
		if( width < 1 || width > 100 ||
			height < 1 || width > 100 ||
			checkPointCount > 18){
			return true;
		}
		return false;
	}

	void buildMatrix(string line, int curRow){
		vector<char> row;
		char curGrid;
		for(int i = 0; i < width; ++i){
			curGrid = line[i];
			row.push_back(curGrid);

			if(curGrid == CHECKPOINT){
				++checkPointCount;
			}
			else if(curGrid == START){
				startPoint[0] = metrix.size();
				startPoint[1] = i;
			}
		}
		metrix.push_back(row);
	}

	void buildGraph(){

		int count = 0;

		Node *s = new Node(START, 0, -1, NULL, startPoint);
		graph.push_back(s);

		while( count < checkPointCount + 2 ){
			int row = graph[count]->pos[0];
			int col = graph[count]->pos[1];

			vector<Node *> neighbors = findNeighbor(row, col);

			Node* curNode = graph[count];
			for( int i = 0; i < neighbors.size(); i++){
				Node * n = neighbors[i];
				int index = notExists(graph, n->pos[0], n->pos[1]);
				if(index < 0){
					graph.push_back(n);
					n->index = graph.size() - 1;
				}
				else{
					n->index = index;
				}
				Node * another = graph[n->index];
				while(another->next != NULL){
					another = another->next;
				}
				another->next = graph[count];
				curNode->next = n;
				curNode = n;
			}
			curNode->next = NULL;

			metrix[row][col] = '#';
			count++;
		}
	}

	int notExists(vector<Node *> &nodes, int r, int c){
		for(int i = 0; i < nodes.size(); i++){
			if(nodes[i]->pos[0] == r && nodes[i]->pos[1] == c){
				return i;
			}
		}
		return -1;
	}

	void addNeighbor(vector<Node *> &neighbors, int r, int c, int cost){
		if(notExists(neighbors, r, c) < 0){
			int pos[2];
			pos[0] = r;
			pos[1] = c;
			Node * e = new Node(metrix[r][c], -1, cost, NULL, pos);
			neighbors.push_back(e);
		}
	}

	vector<Node *> findNeighbor(int row, int col){
		vector<Node *> neighbors;

		int top = false, left = false, right = false, bottom = false;
		// form four direction to find neighbors, top left right bottom
		
		int r = row - 1; //top
		int c = col;
		while(metrix[r][c] == OPENBLOCK && r >= 0){ 

			int mc = c - 1;
			while(metrix[r][mc] == OPENBLOCK && mc >= 0){ //top left
				mc --;
			}
			if(mc >= 0 && metrix[r][mc] == CHECKPOINT || metrix[r][mc] == GOAL){
				addNeighbor(neighbors, r, mc, r + mc - row - col);
			}

			mc = c + 1;
			while(metrix[r][mc] == OPENBLOCK && mc < width){ //top right
				mc ++;
			}
			if(mc < width && metrix[r][mc] == CHECKPOINT || metrix[r][mc] == GOAL){
				addNeighbor(neighbors, r, mc, r + mc - row - col);
			}

			r --;
		}
		if(r >= 0 && metrix[r][c] == CHECKPOINT || metrix[r][c] == GOAL){
			addNeighbor(neighbors, r, c, r + c - row - col);
		}

		r = row; //left
		c = col - 1;
		while(metrix[r][c] == OPENBLOCK && c >= 0){ 

			int mr = r - 1;
			while(metrix[mr][c] == OPENBLOCK && mr >= 0){ //left top
				mr --;
			}
			if(mr >= 0 && metrix[mr][c] == CHECKPOINT || metrix[mr][c] == GOAL){
				addNeighbor(neighbors, mr, c, mr + c - row - col);
			}

			mr = r + 1;
			while(metrix[mr][c] == OPENBLOCK && mr < height){ //left bottom
				mr ++;
			}
			if(mr < height && metrix[mr][c] == CHECKPOINT || metrix[mr][c] == GOAL){
				addNeighbor(neighbors, mr, c, mr + c - row - col);
			}
			c--;
		}
		if(c >= 0 && metrix[r][c] == CHECKPOINT || metrix[r][c] == GOAL){
			addNeighbor(neighbors, r, c, r + c - row - col);
		}

		r = row; //right
		c = col + 1;
		while(metrix[r][c] == OPENBLOCK && c < width){ 

			int mr = r - 1;
			while(metrix[mr][c] == OPENBLOCK && mr >= 0){ //right top
				mr --;
			}
			if(mr >= 0 && metrix[mr][c] == CHECKPOINT || metrix[mr][c] == GOAL){
				addNeighbor(neighbors, mr, c, mr + c - row - col);
			}

			mr = r + 1;
			while(metrix[mr][c] == OPENBLOCK && mr < height){ //top right
				mr ++;
			}
			if(mr < height && metrix[mr][c] == CHECKPOINT || metrix[mr][c] == GOAL){
				addNeighbor(neighbors, mr, c, mr + c - row - col);
			}
			c++;

		}
		if(c < width && metrix[r][c] == CHECKPOINT || metrix[r][c] == GOAL){
			addNeighbor(neighbors, r, c, r + c - row - col);
		}

		r = row + 1; //
		c = col;
		while(metrix[r][c] == OPENBLOCK && r < height){ 

			int mc = c - 1;
			while(metrix[r][mc] == OPENBLOCK && mc >= 0){ //bottom left
				mc --;
			}
			if(mc >= 0 && metrix[r][mc] == CHECKPOINT || metrix[r][mc] == GOAL){
				addNeighbor(neighbors, r, mc, r + mc - row - col);
			}

			mc = c + 1;
			while(metrix[r][mc] == OPENBLOCK && mc < width){ //bottom right
				mc ++;
			}
			if(mc < width && metrix[r][mc] == CHECKPOINT || metrix[r][mc] == GOAL){
				addNeighbor(neighbors, r, mc, r + mc - row - col);
			}
			r ++;
		}
		if(r < height && metrix[r][c] == CHECKPOINT || metrix[r][c] == GOAL){
			addNeighbor(neighbors, r, c, r + c - row - col);
		}

		return neighbors;
	}
};

int main(int argc, char* argv[]){

	Orienteering o;

	o.main();

	return 0;
}