#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <sstream>
#include<limits.h>
#include<vector>

using namespace std;
#define SIZE 24
//#define INF INT_MAX

struct gnode {
	int name;
	int fnums[24];
};



void parseline(string line, gnode *g, int j);
int *traveled(struct gnode GRAPH[], int tally[24]);
void printMinSpanClusters(int parent[], struct gnode GRAPH[]);
int findMaxEdge(int distanceN[],bool checked[]);
void MinSpan(struct gnode GRAPH[]);



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
    //travel = traveled(graph, tally);
    printf("HELLO: %d",graph[23].fnums[22]);
    MinSpan(graph);


	infile.close();
	return 0;
}


void printMinSpanClusters(int parent[], struct gnode GRAPH[])
{
   printf("Edge   Weight\n");
   std::vector<int> group[SIZE];

   for (int i = 1; i < SIZE; i++)
   {
	   if (GRAPH[i].fnums[parent[i]] > 1) // Expensive Edge, disconnect it
	   {
		   //GRAPH[i].fnums[parent[i]] = 0;
	   }
	   else
	   {
		   group[i].push_back(parent[i]);
		   group[parent[i]].push_back(i);
	   }
	   printf("%d - %d    %d \n", parent[i], i, GRAPH[i].fnums[parent[i]]);

   }

   // print parent
   for(int h = 0; h < SIZE; h++)
      {
   	   cout << "node" << h << "'s parent: " << parent[h];
//   	   for (std::vector<int>::const_iterator i = group[h].begin(); i != group[h].end(); ++i)
//   	   {
//             std::cout << *i << ' ';
//   	   }
   	   std::cout << "\n";
      }



   for(int i = SIZE-1; i > -1; i--)
   {
	   for(int j = SIZE-1; j > -1; j--)
	   {
		   if(std::find(group[i].begin(), group[i].end(), j) != group[i].end()) {
			   /* group[i] contains j */
			   group[i].insert( group[i].end(), group[j].begin(), group[j].end() );

		   } else {
			   /* group[i] does not contain j */
		   }
	   }
	   // only unique elements
	   sort( group[i].begin(), group[i].end() );
	   group[i].erase( unique( group[i].begin(), group[i].end() ), group[i].end() );
   }

   for(int i = SIZE-1; i > -1; i--)
      {
   	   for(int j = SIZE-1; j > -1; j--)
   	   {
   		   if(std::find(group[i].begin(), group[i].end(), j) != group[i].end()) {
   			   /* group[i] contains j */
   			   group[i].insert( group[i].end(), group[j].begin(), group[j].end() );

   		   } else {
   			   /* group[i] does not contain j */
   		   }
   	   }
   	   // only unique elements
   	   sort( group[i].begin(), group[i].end() );
   	   group[i].erase( unique( group[i].begin(), group[i].end() ), group[i].end() );
      }



   for(int h = 0; h < SIZE; h++)
   {
	   cout << "node" << h << ": ";
	   for (std::vector<int>::const_iterator i = group[h].begin(); i != group[h].end(); ++i)
	   {
          std::cout << *i << ' ';
	   }
	   std::cout << "\n";
   }

}

int findMaxEdge(int distanceN[],bool checked[])
{

	int min = INT_MAX;
	int min_index;

	   for (int i = 0; i < SIZE; i++)
	   {
	     if (checked[i] == false && distanceN[i] < min)
	     {
	         min = distanceN[i];
	         min_index = i;
	     }
	   }
	   return min_index;

}

void MinSpan(struct gnode GRAPH[])
{
	// initilize distances and checked array to inf, and false
	bool checked[SIZE];
	int parent[SIZE];
	int distanceN[SIZE];

	for (int i = 0; i< SIZE;i++)
	{
		distanceN[i] = INT_MAX;
		checked[i] = false;
	}

	// substract 9 from all edges' values', so life becomes easier
	for(int i = 0;i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++)
		{
			GRAPH[i].fnums[j] = 10 - GRAPH[i].fnums[j];
		}
	}

	parent[0] = -1; // the first node has no parent
	distanceN[0] = 0; // distance from first node to itself is zero

	for (int i = 0; i < SIZE-1; i++)
	{
		//checked[i] = true;
		// find the strongest connection to this node
		int index = findMaxEdge(distanceN,checked);
		// the new index is visited
		checked[index] = true;

		// update vertices that are adjacent to 'index'
		for (int j = 0;j < SIZE;j++)
		{
			if(GRAPH[index].fnums[j] && checked[j] == false && GRAPH[index].fnums[j] < distanceN[j])
			{
				parent[j] = index;
				distanceN[j] = GRAPH[index].fnums[j];
			}
		}

	}
	printMinSpanClusters(parent,GRAPH);
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
