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

		cout << findPath() << endl;

	}

private:

	int findPath(){
		int flag[100][100];

		for(int i = 0; i < height; i++){
			for(int j = 0; j < width; j++){
				flag[i][j] = 0;
			}
		}

		int steps = 0;
		int count = 0;
		int min = 100000;

		stack<int> s1;
		stack<int> s2;
		stack<int> s3;
		s1.push(startPoint[0]);
		s2.push(startPoint[1]);
		s3.push(0);
		while(!s1.empty()){
			int x = s1.top();
			int y = s2.top();
			int d = s3.top();
			s3.pop();
	
			d++;
			if(d == 1){
				if( x - 1 >= 0 &&
				    flag[x - 1][y] < 2 &&
				    metrix[x - 1][y] != '#'){
					if(metrix[x - 1][y] == 'G'){
						if(count == checkPointCount){
							steps++;
							min = min > steps ? steps : min;
							steps--;
						}
					}
					else if(metrix[x - 1][y] == '@' && flag[x - 1][y] < 1){
						count++;
					}
					steps++;
					flag[x - 1][y]++;
					s3.push(d);
					s1.push(x - 1);
					s2.push(y);
					s3.push(0);
				}
				else{
					s3.push(d);
				}
			}
			else if(d == 2){
				if( x + 1 < width &&
				    flag[x][y + 1] < 2 &&
				    metrix[x][y + 1] != '#'){
					if(metrix[x][y + 1] == 'G'){
						if(count == checkPointCount){
							steps++;
							min = min > steps ? steps : min;
							steps--;
						}
					}
					else if(metrix[x][y + 1] == '@' && flag[x][y + 1] < 1){
						count++;
					}
					steps++;
					flag[x][y + 1]++;
					s3.push(d);
					s1.push(x);
					s2.push(y + 1);
					s3.push(0);
				}
				else{
					s3.push(d);
				}
			}
			else if(d == 3){
				if( x + 1 < height &&
				    flag[x + 1][y] < 2 &&
				    metrix[x + 1][y] != '#'){
					if(metrix[x + 1][y] == 'G'){
						if(count == checkPointCount){
							steps++;
							min = min > steps ? steps : min;
							steps--;
						}
					}
					else if(metrix[x + 1][y] == '@' && flag[x + 1][y] < 1){
						count++;
					}
					steps++;
					flag[x + 1][y]++;
					s3.push(d);
					s1.push(x + 1);
					s2.push(y);
					s3.push(0);;
				}
				else{
					s3.push(d);
				}
			}
			else if(d == 4){
				if( y - 1 >= 0 &&
				    flag[x][y - 1] < 2 &&
				    metrix[x][y - 1] != '#'){
					if(metrix[x][y - 1] == 'G'){
						if(count == checkPointCount){
							steps++;
							min = min > steps ? steps : min;
							steps--;
						}
					}
					else if(metrix[x][y - 1] == '@' && flag[x][y - 1] < 1){
						count++;
					}
					steps++;
					flag[x][y - 1]++;
					s3.push(d);
					s1.push(x);
					s2.push(y - 1);
					s3.push(0);
				}
				else{
					flag[x][y]--;
					steps--;
					if(metrix[x][y] == '@' && flag[x][y] == 0){
						count--;
					}
					s1.pop();
					s2.pop();
				}
			}
			else{
				flag[x][y]--;
				steps--;
				if(metrix[x][y] == '@' && flag[x][y] == 0){
					count--;
				}
				s1.pop();
				s2.pop();
			}
		}
		return min;
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

};


int main()
{

	Orienteering o;

	o.main();
	return 0;
}

