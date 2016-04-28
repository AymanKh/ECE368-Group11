#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct gnode {
	int name;
	int fnums[24];
} graph[24];

void parseline(string line, gnode graph);

int main () {
	ifstream infile;
    infile.open("Social2.txt");
	if (infile.is_open() != 1) {
		printf("Error, could not open file");
		return 0;
	}
	int i = 0;
    string line;
	while (i < 24) {
		getline(infile, line);
		parseline(line, graph[i]);
        i++;
	}
	
	infile.close();
	return 0;
}

void parseline(string line, gnode graph)
{
    int i = 0;
    string curr;
    istringstream iss(line);
    getline(iss, curr, ':');
    graph.name = stoi(curr, nullptr, 10);
    while (i < 24) {
        getline(iss, curr, ',');
        graph.fnums[i] = stoi(curr, nullptr, 10);
        i++;
    }
}