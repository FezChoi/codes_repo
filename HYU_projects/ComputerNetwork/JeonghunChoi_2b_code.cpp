#include <iostream>
#include <vector>
#include <string>
using namespace std;
#define int_MAX 2147000000  // Maximum integer number

/* Graph information */
int info[5][3] = {
    {1, 2, 3},// "A,B,3", // "source, destination, cost"
    {2, 3, 4},// "B,C,4",
    {2, 4, 3},// "B,D,3",
    {3, 4, 2},// "C,D,2",
    {4, 5, 5},// "D,E,5"
};

/* Declare Edge struct. */
struct Edge{
    int src, dst, wgt;              
    Edge(int s, int d, int w){      // insertion function
        src = s; dst = d; wgt = w;
    }
}; // Edge has source, destination, weight(cost)

/* Declare global variables. */
vector<Edge> EdgeVector;                        // edges will be stored here.
vector<vector<vector<int>>> RoutingTable(10);   // Routing Table for each period.
int numNode = 5, numEdge = 5;                   // number of nodes and edges

/* Declare functions. */
void BellmanFord(int source); // Bellman-Ford Algorithm is applied.
void PrintTable(int period);  // Print Routing Table for each period.

int main(){
    /* Initialize the Graph */
    for(int i = 0; i < numEdge; i++){   // for all edges.
        int src = info[i][0];           // get the graph information
        int dst = info[i][1];
        int wgt = info[i][2];
        EdgeVector.push_back(Edge(src, dst, wgt)); // add edges.
        EdgeVector.push_back(Edge(dst, src, wgt)); // make the graph bidirectional.
    }

    /* Link between B and D is broken! */
    for(int i = 0; i < EdgeVector.size(); i++){
        if(EdgeVector[i].src == 2 && EdgeVector[i].dst == 4){
            EdgeVector.erase(EdgeVector.begin()+i); // erase edge from B to D.
        }
        if(EdgeVector[i].src == 4 && EdgeVector[i].dst == 2){
            EdgeVector.erase(EdgeVector.begin()+i); // erase edge from D to B.
        }        
    }    

    /* Run Bellman-Ford Algorithm to get Routing Table. */
    for(int i = 1; i <= numNode; i++) BellmanFord(i);

    /* Print the Routing Table. */
    string bar = "-------------------------------------------------\n";
    for(int period = 0; period <= 10; period++){    // for all periods.
        cout << bar << "Time : " << period << "T" << endl;
        PrintTable(period);     // print Routing Table.
        cout << bar;
    } 

    return 0;
}

/* Algorithm for finding Routing Table, the table of shortest distances. */
void BellmanFord(int source){
    vector<int> cost(6, int_MAX);   // declare cost(distance) vector.
    cost[source] = 0;               // reset self-distance
    for(int period = 0; period <= 10; period++){    // run 0T ~ 10T
        for(int j = 0; j < EdgeVector.size(); j++){ // go through all edges.
            int nowNode = EdgeVector[j].src;        // get edge information.
            int nextNode = EdgeVector[j].dst;
            int nextWeight = EdgeVector[j].wgt;
            if(cost[nowNode] == int_MAX) continue;  // if not updated, continue the loop.
            if(cost[nextNode] > cost[nowNode] + nextWeight){ // if shorter distance exist,
                cost[nextNode] = cost[nowNode] + nextWeight; // update the distance.
            }
        }
        RoutingTable[source].push_back(cost);   // store the updated distance vector.
    }
}

/* Function for printing the Routing Table. */
void PrintTable(int period){
    for(int source = 1; source <= numNode; source++){   // for all nodes.
        cout << "Routing Table : Node " << (char)(64+source) << "\t"; // invert integer into alphabet.
        for(int i = 1; i <= numNode; i++){              // for all updated distances.
            if(i == source) continue;                   // self-distance should not be included.
            cout << "to " << (char)(64+i) << "(";       // print the destination.           
            if(RoutingTable[source][period][i] == int_MAX) cout << "INF"; // if default, print INF.
            else cout << RoutingTable[source][period][i];   // else print the updated distance.
            cout << ")" << endl << "\t\t\t"; 
        }
        cout << endl;
    }
}