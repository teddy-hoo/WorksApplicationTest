#include<iostream>
#include<fsteam>
#include<string>
#include<vector>
#include<map>

using namespace std;

class Orienteering{

private:
	vector<vector<char> > metrix;
	map<string, vector<string> > pathGraph;
	map<string, vector<string> >::iterator iter;
	map<string, bool> isPassed;
	string startPoint;
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

	void readData(){
		
		cin >> width >> height;
		
		for(int i = 0; i < width; ++i){
			cin >> line;
			o.addEdge(line, i, height);
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

	string getName(char simbol, int col, int row){
		string name(1, simbol);
		name.append(col - '0');
		name.append(row - '0');
		return name;
	}

	string findNearest(string curPos){
		
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
			string name = getName(curGrid, curRow, i);
			isPassed[name] = false;
			if(curGrid == '@'){
				++checkPointCount;
			}
			else if(curGrid == 'S'){
				startPoint = name;
			}
			else if(curGrid == 'G'){
				endPoint = name;
			}
			vector<string> nodes;
			string name1;
			if(i - 1 >= 0 && row[i - 1] != '#'){
				name1 = getName(row[i - 1], curRow, i - 1);
				iter = pathGraph.find(name1);
				if(iter == pathGraph.end()){
					nodes.clear();
					nodes.push_back(name);
					pathGraph[name1] = nodes;
				}
				else{
					iter->second.push_back(name);
				}
				iter = pathGraph.find(name);
				if(iter == pathGraph.end()){
					nodes.clear();
					nodes.push_back(name1);
					pathGraph[name] = nodes;
				}
				else{
					iter->second.push_back(name1);
				}
			}
			if(curRow - 1 >= 0 && metrix[curRow - 1][i] != '#'){
				name1 = getName(metrix[curRow - 1], curRow - 1, i);
				iter = pathGraph.find(name1);
				if(iter == pathGraph.end()){
					nodes.clear();
					nodes.push_back(name);
					pathGraph[name1] = nodes;
				}
				else{
					iter->second.push_back(name);
				}
				iter = pathGraph.find(name);
				if(iter == pathGraph.end()){
					nodes.clear();
					nodes.push_back(name1);
					pathGraph[name] = nodes;
				}
				else{
					iter->second.push_back(name1);
				}
			}
		}
		metrix.append(row);
	}

	int findPath(){
		string curPos = startPoint;
		while(curPos[0] != 'G'){
			curPos = findNearest(curPos);
		}		
	}
};

int main(int argc, char* argv[]){

	Orienteering o;

	o.main();

	return 0;
}