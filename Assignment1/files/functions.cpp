#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include "graph.h"
using namespace std;

vector<Graph> succ(Graph g, bool turn)
{
    vector<Graph> succ;
    if(turn == false)
    {
        for(size_t i = 0; i < g.num_nodes(); i++)
        {
            if(g.getColor(g.getNode(i).id()) == "NULL")
            {
                Graph temp = g;
                temp.setColor(g.getNode(i).id(), "BLUE");
                succ.push_back(temp);
            }
        }
    }
    else if(turn == true)
    {
        for(size_t i = 0; i < g.num_nodes(); i++)
        {
            if(g.getColor(g.getNode(i).id()) == "NULL")
            {
                Graph temp = g;
                temp.setColor(g.getNode(i).id(), "RED");
                succ.push_back(temp);
            }
        }
    }
    
    return succ;
}

int utility(Graph g, bool turn)
{
    int result = 0;
    if(g.failure() == true)
    {
        if(turn == false)
        {
            result = -1;
            return result;
        }
        else if(turn == true)
        {
            result = 1;
            return result;
        }
    }
    
    return result;
}

int minimaxValue(Graph g, bool turn)
{
    int max, min;
    vector<int> utilityValues;
    
    if(g.failure() || g.terminal())
        return utility(g, turn);
    
    if(turn == true)
    {
        vector<Graph> succ1 = succ(g, true);
        for(size_t i = 0; i < succ1.size(); i++)
        {
            utilityValues.push_back(minimaxValue(succ1[i], false));
        }
        
        max = utilityValues[0];
        for(size_t i = 1; i < utilityValues.size(); i++)
        {
            if(utilityValues[i] > max)
                max = utilityValues[i];
        }
        
        return max;
    }
    
    if(turn == false)
    {
        vector<Graph> succ2 = succ(g, false);
        for(size_t i = 0; i < succ2.size(); i++)
        {
            utilityValues.push_back(minimaxValue(succ2[i], true));
        }
        
        min = utilityValues[0];
        for(size_t i = 1; i < utilityValues.size(); i++)
        {
            if(utilityValues[i] < min)
                min = utilityValues[i];
        }
        
        return min;
    }
}

int minimaxDecision(Graph g)
{
    string move;
    vector<int> moveValues;
    vector<Graph> succ3 = succ(g, true);
    for(size_t i = 0; i < succ3.size(); i++)
    {
        moveValues.push_back(minimaxValue(succ3[i], false));
    }
    
    for(size_t i = 0; i < moveValues.size(); i++)
    {
        if(moveValues[i] == 1)
        {
            for(size_t j = 0; j < g.num_nodes(); j++)
            {
                if(succ3[i].getColor(j) != "NULL")
                {
                    move = succ3[i].getNode(j).name();
                    cout << "Victory is ensured if you color node " + move + "." << endl;
                    return 0;
                }
            }
        }
    }
    
    for(size_t i = 0; i < moveValues.size(); i++)
    {
        if(moveValues[i] == 0)
        {
            for(size_t j = 0; j < g.num_nodes(); j++)
            {
                if(succ3[i].getColor(j) != "NULL")
                {
                    move = succ3[i].getNode(j).name();
                    cout << "A tie is ensured if you color node " + move + "." << endl;
                    return 0;
                }
            }
        }
    }
    
    cout << "No win is possible." << endl;
}
    
           
        