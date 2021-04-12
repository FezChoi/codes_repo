#include <iostream>
#include <vector>
using namespace std;

/* Input format */
int input[20][5] = {
    {8, 11},  // 8 vertexes, 11 edges
    {0, 1, 2},// "A,B,2", // "source, destination, cost"
    {0, 6, 6},// "A,G,6",
    {1, 2, 7},// "B,C,7",
    {1, 4, 2},// "B,E,2",
    {2, 3, 3},// "C,D,3",
    {2, 5, 3},// "C,F,3",
    {3, 7, 2},// "D,H,2",
    {4, 5, 2},// "E,F,2",
    {4, 6, 1},// "E,G,1",
    {5, 7, 2},// "F,H,2",
    {6, 7, 4} // "G,H,4"
};

/* Define fixed variables. */
#define MAX_NODES 1024
#define INFINITY 1000000000

/* Global variables. */
int numVertex, numEdge;
int costGraph[MAX_NODES][MAX_NODES] = { 0 };
vector<int> path;

/* Enum class of label, which represents the state of each node. */
enum class Label { permanent, tentative };

/* Find Shortest Path.
   Parameter 'soure' is the starting node, 'target' is the destination. */
void shortest_path(int source, int target) {
    struct State {          // State structure of each node.
        int predecessor;    // the node pointing the current node.
        int length;         // totoal distance from the starting node.
        Label label;        // state of the current node.
    }state[MAX_NODES];

    /* Initialize states. */
    struct State* ptr;      // read the state of all nodes using a pointer.
    for (ptr = &state[0]; ptr < &state[numVertex]; ptr++) {
        ptr->predecessor = -1;          // initial predecessor is nothing.
        ptr->length = INFINITY;         // initial length is Infinity.
        ptr->label = Label::tentative;  // initial state is tentative.
    }
    state[source].length = 0;               // starting node has length of 0.
    state[source].label = Label::permanent; // starting node state will never be changed.
    cout << (char)(source + 65) << "(" << state[source].length << ", " << "-)" << endl;


    /* Scan the Graph. */
    int nowVertex = source; // a current node is the starting node.
    do { 
        /* Check all the connected & changable nodes. */
        for (int next = 0; next < numVertex; next++) {
            bool isConnected = (costGraph[nowVertex][next] != 0);       // 0 cost means disconnected.
            bool isTentative = (state[next].label == Label::tentative); // tentative means changable.
            if (isConnected && isTentative) {
                int nowLength = state[nowVertex].length + costGraph[nowVertex][next]; // get added length.
                if (nowLength < state[next].length) {    // if the added length is smaller than prior length,
                    state[next].predecessor = nowVertex; // predecessor becomes the current node.
                    state[next].length = nowLength;      // length becomes the smaller one.
                }
            }
        }

        /* Find the tentatively labeled with smallest length. 
           Change the state length to the smallest, then make it permanentally labeled. */
        nowVertex = 0;             // start from the first node.
        int minLength = INFINITY;  // initialize minimum length.
        for (int vertex = 0; vertex < numVertex; vertex++) {                // scan all nodes.
            bool isTentative = (state[vertex].label == Label::tentative);   // tentative means changable.
            bool isShorter = (state[vertex].length < minLength);            // length smaller than minimum length.
            if (isTentative && isShorter) {
                minLength = state[vertex].length;        // update the minimum length.
                nowVertex = vertex;                      // the current node becomes the node with minimum length.
            }
        }
        state[nowVertex].label = Label::permanent;  // make the current node permanently labeled.

        /* Print the permanently labeled node. */
        char permanentVertex = (char)(nowVertex + 65);
        char permanentPredecessor = (char)(state[nowVertex].predecessor + 65);
        cout << permanentVertex << "(" << state[nowVertex].length << ", " << permanentPredecessor << ")" << endl;
    } while (nowVertex != target);  // loop until the current node arrives at the destination.

    /* Save the path into the output path vector. */
    nowVertex = target;  // start from the destination.
    do{
        path.push_back(nowVertex);                // path saved in reverse order.
        nowVertex = state[nowVertex].predecessor; // predecessors are the nodes on the same path.
    } while (nowVertex >= source);  // loop until the current node becomes the starting node.

    /* Save the length of the shortest path found */
    path.push_back(state[target].length); // the length at the end of the output path vector. 
}

int main() {
    /* Get the number of nodes and edges. */
    numVertex = input[0][0]; numEdge = input[0][1];
    
    /* Get the information about graph. */
    int src, dst, wgt;
    for (int i = 1; i <= numEdge; i++) {
        src = input[i][0];         // source node.
        dst = input[i][1];         // destination node.
        wgt = input[i][2];         // cost from source to destination.
        costGraph[src][dst] = wgt; // source and destination is connected with the cost of weight.
        costGraph[dst][src] = wgt; // make it bidirectional.
    }

    /* Find the shortest path from starting node A(0) to destination node D(3). */
    shortest_path(0, 3);


    /* Print the minimum length */
    vector<int>::reverse_iterator riter = path.rbegin();
    cout << "Minimum Cost from A to D is : " << *riter << endl;
    path.pop_back(); // pop the value saved at the end of the path vector.

    /* Print the path in the reverse order. */
    cout << "Minimum Cost Path from A to D is : ";
    for (riter = path.rbegin(); riter != path.rend(); ++riter) {
        cout << (char)(*riter + 65) << " "; // change the number into the alphabet.
    }

    cout << endl;
    return 0;
}