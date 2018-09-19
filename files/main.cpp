#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include "graph.h"
using namespace std;

int minimaxDecision(Graph G);

int main()
{
    string file;
    
    cout << "Enter the filename for the graph you would like to test: ";
    cin >> file;
    
    Graph g = Graph(file);
    
    minimaxDecision(g);
    
    return 0;
}