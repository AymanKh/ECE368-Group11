#include <iostream>
#include <istream>
#include <fstream>
#include <string>
using namespace std;

struct gnode {
	char name[40];
	int fnums[40];
} graph[40];

void parseline(string line, gnode graph);

int main () {
	ifstream infile;
    infile.open("example.txt");
	if (infile.is_open() != 1) {
		printf("Error, could not open file");
		return 0;
	}
	int i = 0;
    string line;
	while (i < 40) {
		getline(infile, line);
		parseline(line, graph[i]);
        i++;
	}
	
	infile.close();
	return 0;
}

void parseline(string line, gnode graph)
{
	int spaces = 0;
	int i = 0;
	int j = 0;
	while (spaces < 2) {
		graph.name[i] = line[i];
		i++;
		if (isspace(line[i])) {
			spaces++;
		}
	}
	while (j < 40) {
		graph.fnums[i] = line[j+i];
        j++;
	}
}