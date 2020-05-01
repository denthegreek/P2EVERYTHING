/*
Name:		Dimostenis Nikolakopoulos
UCID:		dn242
Studnt num:	31387555
Class:		CS435 002 
Project: 	2
Part: 		3.e) 
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> 

using namespace std;


struct Node{
    string value="";
    vector<Node*> edges;
    bool checked=false;
};

//Adjacency Vector:
vector<Node> graph;
    
class Graph{
    
    public:
    
    void addNode(string nodeVal){ 
        Node newNode;
        newNode.value=nodeVal;
    
        graph.push_back(newNode);
    } 
    
    void addEdge(string first, string second){ 
        Node* firstPtr = NULL;
        Node* secondPtr = NULL;
        
        int indexFirst, indexSecond;
        
        for(int i =0; i<graph.size() ; i++){
            if(graph[i].value== first){
                firstPtr = &graph[i];
                indexFirst=i;
            }
            else if(graph[i].value== second){
                secondPtr = &graph[i];
                indexSecond=i;
            }
            if(firstPtr!=NULL && secondPtr!=NULL){
                break;
            }
        }
         graph[indexFirst].edges.push_back(secondPtr);
         graph[indexSecond].edges.push_back(firstPtr);
        
    }
    
    void removeUndirectedEdge(Node first, Node second){ 
        int ofTheTwo=0;
        
        string First = first.value;
        string Second = second.value;
        
        for(int i =0; i<graph.size() ; i++){
            if(graph[i].value== First){
                for (auto it = graph[i].edges.begin(); it != graph[i].edges.end(); ++it){
                    if((*it)->value==Second){
                        graph[i].edges.erase(it);
                        ofTheTwo++;
                    }
                }
            }
            else if(graph[i].value== Second){
                for (auto it = graph[i].edges.begin(); it != graph[i].edges.end(); ++it){
                    if((*it)->value==First){
                        graph[i].edges.erase(it);
                        ofTheTwo++;
                    }
                }
            }
            if(ofTheTwo==2){
                break;
            }
        }
    }
    
    vector<Node> getAllNodes(){
        vector<Node> HashSet;
        for(int i=0 ; i<graph.size() ; i++ ){
            HashSet.push_back(graph[i]);
        }
        return HashSet;
    }
	
	vector<Node> createRandomUnweightedGraphIter(int n){
		vector<Node> randomGraph;
		
		for(int i=0 ; i < n ; i++){
			int x=rand() % (n + 1 -1) + 1;
			string str=to_string(x);
			bool inGraph=false;
			
			if(randomGraph.size() > 0){
				for(int j = 0 ; j < randomGraph.size() ; j++){
					if(randomGraph[j].value == str){
						inGraph=true;
						i--;
						break;
					}
				}
				if(inGraph==false){
					Node newNode;
					newNode.value=str;
					randomGraph.push_back(newNode);
				}
				else{
					inGraph==false;
				}
			}
			else{
				Node newNode;
				newNode.value=str;
				randomGraph.push_back(newNode);
			}
		}
		
		int m=rand() % (randomGraph.size()-1 + 1 - 0) + 1;
		for(int j=0 ; j < (m*(m-1))/2 ; j++){
			int index1 = rand() % (randomGraph.size()-1 + 1 - 0) + 0;
			int index2;
			
			bool inGraph=true;
			
			while(randomGraph[index1].edges.size()>=n-1){
					index1 = rand() % (randomGraph.size()-1 + 1 - 0) + 0;
			}
			
			while(index1==index2 || inGraph==true){
				inGraph=false;
				index2 = rand() % (randomGraph.size()-1 + 1 - 0) + 0;
				
				for(int k=0 ; k<randomGraph[index1].edges.size() ; k++){
					
					if(randomGraph[index1].edges[k]->value == randomGraph[index2].value){
						inGraph=true;
						break;
					}
				}
			}
			randomGraph[index1].edges.push_back(&randomGraph[index2]);
			randomGraph[index2].edges.push_back(&randomGraph[index1]);
		}
		
		//return Adjacency Vector:
		return randomGraph;
	}
};


class Main{
    
	public:
	
	vector<Node> createRandomUnweightedGraphIter(int n){
		vector<Node> randomGraph;
		
		for(int i=0 ; i < n ; i++){
			int x=rand() % (n + 1 -1) + 1;
			string str=to_string(x);
			bool inGraph=false;
			
			if(randomGraph.size() > 0){
				for(int j = 0 ; j < randomGraph.size() ; j++){
					if(randomGraph[j].value == str){
						inGraph=true;
						i--;
						break;
					}
				}
				if(inGraph==false){
					Node newNode;
					newNode.value=str;
					randomGraph.push_back(newNode);
				}
				else{
					inGraph==false;
				}
			}
			else{
				Node newNode;
				newNode.value=str;
				randomGraph.push_back(newNode);
			}
		}
		
		for(int i=1 ; i < randomGraph.size() ; i++){
			randomGraph[i-1].edges.push_back(&randomGraph[i]);
		}
		
		
		
		//return Adjacency Vector:
		return randomGraph;
	}
	
};

class GraphSearch{

    public:
    
	vector<Node> DFSIter(Node start, Node end){//Because it is conceptually more challenging I will comment more.
		vector<Node> solution;
		Node* indexedNode=&start;
		//In case we search for the first value:
		if (start.value == end.value){
			solution.push_back(start);//Just pass start
			return solution;//and return the first one.
		}
		//If not the above then push to the solution list the starting node:
		solution.push_back(*indexedNode);
		
		//Otherwise we "dive" into the graph: 
		while(indexedNode->edges.size()!=0){
			int indexForEdges=0;//initially-(changes in the nested while!)
			indexedNode->checked=true;//I've seen this room and I've walked this floor... (joke)
	 
			int iterations=0;//if we loop too many times in the edges list of the Node it is not in this fragment of the grapg. 
			while((indexedNode->edges[indexForEdges]->checked==true)||(indexedNode->edges[indexForEdges]->value==start.value)){
				indexForEdges++;//While we find an edge leading to checked element we keep looking.
				if((indexForEdges == indexedNode->edges.size()-1) && (indexedNode->edges[indexForEdges]->checked==true)){
					vector<Node> empty{};
					return empty;
				}
				else{
					iterations++;
				}
			}
			indexedNode=indexedNode->edges[indexForEdges];//go towards the Node oldest possible node connected to current.
			solution.push_back(*indexedNode);//put the one you got into to the solution list (it will bechecked on the next iter)
			if(indexedNode->value == end.value){
				break;//If value is found it is going to go out and return the solution list
			}
		}
		
		for(int i = 0 ; i < solution.size() ; i++){
			for(int j =0 ; j < solution[i].edges.size() ; j++ ){
				if(solution[i].edges[j]->checked==true){
					solution[i].edges[j]->checked=false;
				}
			}
		}
		
		return solution;//It is best advised to print it using the printGraph() with input a copy of this return. (It will make sense)
	}
	
	vector<Node> BFSIter(Node start, Node end){//Because it is conceptually more challenging I will comment more.
		vector<Node> solution;
		Node* indexedNode=&start;
		//In case we search for the first value:
		if (start.value == end.value){
			solution.push_back(start);//Just pass start
			return solution;//and return the first one.
		}
		
		vector<Node> byLevel;
		
		//If not the above then push to the solution list the starting node:
		byLevel.push_back(*indexedNode);
		
		int index=0;
		
		bool found=false;
		
		Node* n = indexedNode->edges[0];
		for(int i =0 ; i < n->edges.size() ; i++){
			if(n->edges[i]->value == start.value){
				n->edges[i]->checked=true;
			}
		}
		
		int count=0;
		int prevSize=-1;
		while(true){
			//cout<<"Big loop:\t"<<index<<"\n";
			int indexForEdges=0;
			while(indexForEdges < indexedNode->edges.size()){
				//cout<<"\tInner loop: "<<indexForEdges<<endl;
				if(!indexedNode->edges[indexForEdges]->checked){
					//cout<<"\t\t"<<indexedNode->edges[indexForEdges]->value<<" unchecked\n";
					if((!indexedNode->edges[indexForEdges]->checked) && (indexedNode->edges[indexForEdges]->value != start.value)){
						indexedNode->edges[indexForEdges]->checked=true;
						//cout<<"\t\t"<<"Action: push_back("<<indexedNode->edges[indexForEdges]->value<<")"<<endl;
						string tempo=indexedNode->edges[indexForEdges]->value;
						byLevel.push_back(*(indexedNode->edges[indexForEdges]));
						if(tempo == end.value){
							return byLevel;
						}
					}
					
				}
				indexForEdges++;
			}
			index++;
			
			indexedNode=&(byLevel[index]);
			if(index==1 && count == 0 ){index--;count++;}
			if(byLevel.size() == prevSize){
				vector<Node> empty;
				return empty;
			}
			else{
				prevSize=byLevel.size();
			}
		}
		
		return byLevel;//It is best advised to print it using the printGraph() with input a copy of this return. (It will make sense)
	}
	
};

void printGraph(vector<Node> graph){
	for(int i=0; i<graph.size(); i++){
        cout<<"Node:\t\t"<<graph[i].value<<endl<<"Connections:\t[ ";
        for(int j=0; j<graph[i].edges.size(); j++){
            cout<<graph[i].edges[j]->value<<" ";
        }
        cout<<"]\n"<<endl;
    }
}

int main()
{
    //this is the .cpp where everything is together I recomend for best resaults to use the individual codes but it is up to you.
    return 0;
}