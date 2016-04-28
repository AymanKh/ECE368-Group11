#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

struct gnode {
	int name;
	int fnums[24];
};

void parseline(string line, gnode *g, int j);
int *traveled(struct gnode GRAPH[], int tally[24]);
int main () {
    struct gnode graph[24];
	ifstream infile;
    infile.open("Social2.txt");
	if (infile.is_open() != 1) {
		printf("Error, could not open file");
		return 0;
	}
	int i = 0;
    int *travel;
    string line;
	while (i < 24) {
		getline(infile, line);
		parseline(line, graph, i);
        i++;
	}
    //printf("GRAPH[2].fnums[0] = %d\n", graph[2].fnums[0]);
    //printf("GRAPH[2].fnums[1] = %d\n", graph[2].fnums[1]);
    //printf("GRAPH[2].fnums[2] = %d\n", graph[2].fnums[2]);
    //printf("GRAPH[2].fnums[3] = %d\n", graph[2].fnums[3]);
    
    int tally[24] = {0};
    //printf("INITIAL (0,0) = %d\n", graph[0].fnums[0]);
    travel = traveled(graph, tally);
	
	infile.close();
	return 0;
}

void parseline(string line, gnode *g, int j)
{
    int i = 0;
    string curr;
    istringstream iss(line);
    getline(iss, curr, ':');
    g[j].name = stoi(curr, nullptr, 10);
    while (i < 24) {
        getline(iss, curr, ',');
        g[j].fnums[i] = stoi(curr, nullptr, 10);
        i++;
    }
    //printf("parseline GRAPH[2].fnums[1] = %d %d %d %d\n", g.fnums[0], g.fnums[1], g.fnums[2], g.fnums[3]);
}


int *traveled(struct gnode GRAPH[], int tally[24])
{
    //printf("node: GRAPH[2].fnums[1] = %d\n", GRAPH[2].fnums[1]);
    int INF = 2147483647;
	int dist[24] = { INF };
	int Visited[24] = { 0 };
	int previous[24] = { -1 };
	int k = 0;
	int source;
    int n = 0;
	for (k = 0; k < 24; k++)//for each start point
	{
		int u = k;
		int loopi = 0;
		int exit = 0;
		double min = INF;
		int minindex;
		//clear prev, dist, visited
		int ci = 0;
		for (ci = 0; ci < 24; ci++)
		{
			dist[ci] = INF;
			Visited[ci] = 0;
			previous[ci] = -1;
		}
        dist[u] = 0;
		//prev, dist, visited cleared and ready to repopulate from a new start point and re-tally

		while (!exit) {
			loopi = 0;
			Visited[u] = 1;
			//printf("arrived at new node %d AKA %s\n",u,Territories[u].name);
			while (loopi<24)
			{
				if (GRAPH[u].fnums[loopi] != 0)//we have found a neighbor
				{
                    //printf("u = %d, loopi = %d, GRAPH[u].fnums[loopi] = %d\n", u, loopi, GRAPH[u].fnums[loopi]);
					if (dist[loopi] > dist[u] + (10 - GRAPH[u].fnums[loopi]))
					{
						//printf("updating %s %f to %f\n",Territories[loopi].name,Dist$
						dist[loopi] = dist[u] + (10 - GRAPH[u].fnums[loopi]);
						previous[loopi] = u;
					}
				}
				loopi++;
			}//now updated all neighbours distances+previous's
			 //find next node to go to
			 //printf("\nFinding NEXT\n");
			loopi = 0;
			min = INF;
			minindex = 0;
			exit = 1;//unless we find one to go to, exit
			while (loopi < 24)
			{
				if (dist[loopi] != INF) {
					if ((dist[loopi] < min) && (!Visited[loopi]))
					{
						exit = 0;//we found a node to go to, don't exit
								 //printf("id=%d distance=%f visited  %d min=%f\n",loopi,Distance_From_$
						min = dist[loopi];
						minindex = loopi;
					}
				}
				loopi++;
			}
			//now have next node to go to
			u = minindex;
		}//prev needs to be   tallied
        int zzz = 0;
        for (zzz = 0; zzz < 24; zzz++) {
            //printf("z = %d, previous = %d\n", zzz, previous[zzz]);
        }
		
		for (n = 0; n < 24; n++)
		{
			int p = n;
			while (previous[p] != -1)
			{
                //printf("%d\n", p);
				p = previous[p];
				tally[p]++;
			}
		}
		
	}
    for (n = 0; n < 24; n++)
	{
		printf("node=%d,tally=%d\n", n, tally[n]);
	}

}