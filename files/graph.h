#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
using namespace std;

class Node
{
    private:
        int NodeID;
        string NodeName;
        
    public:
        Node() {};
        Node(const string n, int i) { NodeID = i; NodeName = n; };
        int id() const { return NodeID; };
        const string & name() const { return NodeName; }; 
};

class Graph
{
    private:
        vector<Node> nodes;
        vector<list<Node> > adjList;
        vector<string> colors;
        
    public:
        Graph() {};
        Graph(string filename) { scan(filename); initColor(); };
        size_t num_nodes() { return nodes.size(); };
        
        void addEdge(const Node & a, const Node & b) {
            adjList.resize(nodes.size());
            adjList[a.id()].push_back(b);
            adjList[b.id()].push_back(a);
        }
        
        void addNode(const Node & n) { nodes.push_back(n); };
        const Node & getNode(size_t i) { return nodes[i]; };
        
        list<Node> & getAdjNodes(Node & n) { return adjList[n.id()]; };
        
        void setColor(size_t i, string color) { colors[i] = color; };
        string getColor(size_t i) { return colors[i]; };
        
        void initColor() { 
            for(size_t i = 0; i < num_nodes(); i++) {
                colors.push_back("NULL");
            }
        }
        
        void scan(string file) {
            string line;
            size_t id = 0;
            bool check = false;
            
            ifstream readFile;
            readFile.open(file.c_str());
            if(readFile.is_open())
            {
                getline(readFile, line);
                while(!readFile.eof())
                {
                    check = false;
                    string c = "";
                    string d = "";
                    getline(readFile, line);
                    if (line == "")
                    {
                        readFile.close();
                        return;
                    }
                    c.append(string(1, line.at(0)));
                    d.append(string(1, line.at(2)));

                    if (num_nodes() == 0)
                    { 
                        Node a = Node(c, id);
                        id++;
                        Node b = Node(d, id);
                        addNode(a);
                        addNode(b);
                        addEdge(a, b);
                        id++;
                        check = true;
                    }

                    for(size_t i = 0; i < num_nodes(); i++)
                    {
                        if(check)
                            break;
                        if(c == getNode(i).name())
                        {
                            for(size_t j = 0; j < num_nodes(); j++)
                            {
                                if(d == getNode(j).name())
                                {
                                    addEdge(getNode(i), getNode(j));
                                    check = true;
                                    break;
                                }
                            }
                        }
                    }
                    if(!check)
                    {
                        for(size_t i = 0; i < num_nodes(); i++)
                        {
                            if(c == getNode(i).name())
                            {
                                Node b = Node(d, id);
                                addNode(b);
                                addEdge(getNode(i), b);
                                id++;
                                check = true;
                                break;
                            }
                        }
                    }
                    if(!check)
                    {
                        for(size_t i = 0; i < num_nodes(); i++)
                        {
                            if(d == getNode(i).name())
                            {
                                Node a = Node(c, id);
                                addNode(a);
                                addEdge(a, getNode(i));
                                id++;
                                check = true;
                                break;
                            }
                        }
                    }
                    if(!check)
                    {
                        Node a = Node(c, id);
                        id++;
                        Node b = Node(d, id);
                        addNode(a);
                        addNode(b);
                        addEdge(a, b);
                        id++;
                    }
                }
            }
            
            readFile.close();
        };
        
        bool failure() {
            for(size_t i = 0; i < num_nodes(); i++) {
                for(list<Node>::iterator j = adjList[i].begin(); j != adjList[i].end(); j++) {
                    Node a = nodes[i];
                    Node b = *j;
                    if(colors[a.id()] == colors[b.id()] && colors[a.id()] != "NULL")
                        return true;
                }
            }
            
            return false;
        };
        
        bool terminal() {
            for(size_t i = 0; i < num_nodes(); i++) {
                if(colors[i] == "NULL")
                    return false;
            }
            
            return true;
        };
                        
};
                    