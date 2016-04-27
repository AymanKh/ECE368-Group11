#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#define INF 2147483647

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

int *traveled(struct gnode graph[], int tally[24])
{
	int dist[24] = { INF };
	int visit[24] = { 0 };
	int previous[24] = { -1 };
	int k = 0;
	int source;
	for (k = 0; k < 24; k++)
	{
		int clearindex=0;
		while (clearindex < 24)
		{
			dist[clearindex] = INF;
			visit[clearindex] = 0;
			previous[clearindex] = -1;
			clearindex++;
		}
		source = k;
		dist[source] = 0;
		int z = 0;
		for (z = 0; z < 24; z++)
		{
			if (graph[source].fnums[z] != 0)
			{
				dist[z] = 10 - graph[source].fnums[z];
				previous[z] = source;
			}
		}
		visit[source] = 1;
		//now do this same process 24 times
		int i = 1;
		int least=INF;
		int leastaddress=-1;
		for (i = 1; i < 24; i++)
		{
			//find least unvisited node left
			for (int ii = 1; i < 24; i++)
			{
				if ((!visit[ii])&&(dist[ii] < least))
				{
					least = dist[ii];
					leastaddress = ii;
				}
			}
			//update leastaddress' neighbors distances
			for (z = 0; z < 24; z++)
			{
				if (graph[leastaddress].fnums[z] != 0)//found valid neighbor
				{
					previous[z] = source;
				}
			}

		}
	}



}