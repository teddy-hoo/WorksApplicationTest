#include<iostream>
#include<fsteam>
#include<string>
#include<vector>
#include<map>

using namespace std;

class Orienteering{
private:
	vector<vector<char> > metrix;
	map<char, vector<char> > pathGraph;
	map<char, vector<char> >::iterator iter;
	int chechPointCount;
	int passedCP;


public:
	Orienteering(){
		chechPointCount = 0;
	}

public:
	void addEdge(string line, int curRow, int length){
		vector<char> row;
		char curGrid;
		for(int i = 0; i < length; ++i){
			curGrid = line[i];
			row.push_back(curGrid);
			if(curGrid == '#'){
				continue;
			}
			if(curGrid == '@'){
				++chechPointCount;
			}
			if(i - 1 > 0 && row[i - 1] != '#'){
				iter = pathGraph.find(row[i - 1]);
				if(iter == pathGraph.end()){
					vector<char> nodes;
					nodes.push_back(row[i - 1]);
					pathGraph[row[i]] = nodes;
				}
				else{
					iter->second.push_back(row[i - 1]);
				}
				iter = pathGraph.find(row[i]);
				if(iter == pathGraph.end()){
					vector<char> nodes;
					nodes.push_back(row[i - 1]);
					pathGraph[row[i]] = nodes;
				}
				else{
					iter->second.push_back(row[i - 1]);
				}
			}
		}
	}
};

int main(int argc, char* argv[]){
	int width, heght;
	string line;
	Orienteering o;

	cin >> width >> height;
	for(int i = 0; i < width; ++i){
		cin >> line;
		o.addEdge(line, i, height);
	}
	return 0;
}