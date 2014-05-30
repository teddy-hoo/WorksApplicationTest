#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<queue>

using namespace std;

class Orienteering{
private:
	vector<vector<char> > metrix;
	map<string, vector<string> > pathGraph;
	map<string, vector<string> >::iterator iter;
	map<string, bool> isPassed;
	string startPoint;
	string endPoint;
	int chechPointCount;
	int passedCP;
	int steps;


public:
	Orienteering(){
		chechPointCount = 0;
		steps = 0;
	}

private:
	string getName(char simbol, int col, int row){
		string name(1, simbol);
		string colname(1, col - '0');
		string rowname(1, row - '0');
		name.append(colname);
		name.append(rowname);
		return name;
	}

	string findNearest(string curPos){
		int subStep = 0;
		queue<string> q;
		string neighbors;
		pushVector(q, pathGraph[curPos]);
		q.push("flag");
		while(!q.empty()){
			neighbors = q.front();
			q.pop();
			if(neighbors == "flag"){
				++subStep;
				if(q.empty()){
					return "failed";
				}
				q.push("flag");
			}
			if(neighbors[0] == '@'){
				steps += subStep;
				--chechPointCount;
				return neighbors;
			}
			if(chechPointCount == 0 && neighbors[0] == 'G'){
				return "success";
			}
			pushVector(q, pathGraph[neighbors]);
		}
	}

	void pushVector(queue<string> &q, vector<string> neighbors){
		for(int i = 0; i < neighbors.size(); ++i){
			if(isPassed[neighbors[i]]){
				q.push(neighbors[i]);
				isPassed[neighbors[i]] = false;
			}
		}
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
			isPassed[name] = true;
			if(curGrid == '@'){
				++chechPointCount;
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
				name1 = getName(metrix[curRow - 1][i], curRow - 1, i);
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
		metrix.push_back(row);
	}

	int findPath(){
		string curPos = startPoint;
		while(curPos != "success" && curPos != "failed"){
			curPos = findNearest(curPos);
		}
		if(curPos == "success"){
			return steps;
		}
		return -1;
	}
};

int main(int argc, char* argv[]){
	int width, height;
	string line;
	Orienteering o;

	cin >> width >> height;
	for(int i = 0; i < width; ++i){
		cin >> line;
		o.addEdge(line, i, height);
	}
	cout << o.findPath() << endl;
	return 0;
}