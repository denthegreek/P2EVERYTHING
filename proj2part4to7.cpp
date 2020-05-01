/*
Name:		Dimostenis Nikolakopoulos
UCID:		dn242
Studnt num:	31387555
Class:		CS435 002 
Project: 	2
Part: 		(4-7)
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h> 
#include <map>

using namespace std;
  
  
struct Node{
    string value="";
    vector<Node*> edges;
    bool checked=false;
    int inDegree=0;
    vector<int> weights; //same index as in edges. 
};

struct gridNode{//Only for question 6!
    string value="";
    vector<gridNode*> edges;
    bool checked=false;
    int inDegree=0;
    int x;
    int y;
    int toDestination;
    int fromStart;
};

//Printers----------------------------------------------------------------------

void printGraphAdvanced(vector<Node> graph){
    int count=0;
	for(int i=0; i<graph.size(); i++){
	    count++;
        cout<<count<<". Node:  "<<graph[i].value<<"   ";
        cout<<"Pointed by:  "<<graph[i].inDegree<<" node(s)   ";
        cout<<"Connections:  [ ";
        for(int j=0; j<graph[i].edges.size(); j++){
            if(j!=graph[i].edges.size()-1){
                cout<<graph[i].edges[j]->value<<" , ";
            }
            else{
                cout<<graph[i].edges[j]->value<<" ";
            }
        }
        cout<<"]   ";
        cout<<"Weights:  [ ";
        for(int j=0; j<graph[i].weights.size(); j++){
            if(j!=graph[i].weights.size()-1){
                cout<<graph[i].weights[j]<<" , ";
            }
            else{
                cout<<graph[i].weights[j]<<" ";
            }
        }
        cout<<"]\n";
    } 
}

void printDirectedGraph(vector<Node> graph){
    int count=0;
	for(int i=0; i<graph.size(); i++){
	    count++;
        cout<<count<<". Node:  "<<graph[i].value<<"   ";
        cout<<"Pointed by:  "<<graph[i].inDegree<<" node(s)   ";
        cout<<"Connections:  [ ";
        for(int j=0; j<graph[i].edges.size(); j++){
            if(j!=graph[i].edges.size()-1){
                cout<<graph[i].edges[j]->value<<" , ";
            }
            else{
                cout<<graph[i].edges[j]->value<<" ";
            }
        }
        cout<<"]\n";
    } 
}

void printGridGraph(vector<gridNode> graph){
    int count=0;
	for(int i=0; i<graph.size(); i++){
	    count++;
        cout<<count<<". gridNode:  "<<graph[i].value<<"   ";
        cout<<"Available:  "<<graph[i].inDegree<<" move(s)   ";
        cout<<"Connections:  [ ";
        for(int j=0; j<graph[i].edges.size(); j++){
            if(j!=graph[i].edges.size()-1){
                cout<<graph[i].edges[j]->value<<" , ";
            }
            else{
                cout<<graph[i].edges[j]->value<<" ";
            }
        }
        cout<<"]   ";
        cout<<"Coordinates:  x:"<<graph[i].x<<"  y:"<<graph[i].y<<endl;
    }
}

void onlyVals(vector<gridNode> graph){
    int count=0;
	for(int i=0; i<graph.size(); i++){
	    if(count==10){
	        cout<<endl;
	        count=0;
	    }
        cout<<graph[i].value;
        if(i<graph.size()-1){
            cout<<" -> ";
        }
        count++;
    }
    cout<<endl;
}
//------------------------------------------------------------------------------
//Qestions 4 and 5 section------------------------------------------------------

class DirectedGraph{
    public:
	void addNode(string nodeVal, vector<Node> &graph){ 
		Node newNode;
		newNode.value=nodeVal;
		
		graph.push_back(newNode);
	} 

	void addDirectedEdge(string first, string second, vector<Node> &graph){ 
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
				indexSecond =i;
			}
			if(firstPtr!=NULL && secondPtr!=NULL){
				break;
			}
		}
		graph[indexFirst].edges.push_back(secondPtr);
		graph[indexSecond].inDegree+=1;
	}


	void removeDirectedEdge(Node first, Node second, vector<Node> &graph){ 
		int ofTheTwo=0;
		
		string First = first.value;
		string Second = second.value;
		
		for(int i =0; i<graph.size() ; i++){
			if(graph[i].value== First){
				for (auto it = graph[i].edges.begin(); it != graph[i].edges.end(); ++it){
					
					if((*it)->value==Second){
						graph[i].edges.erase(it);
						ofTheTwo++;
						
						break;
					}
				}
			}
			else if(graph[i].value== Second){
				graph[i].inDegree-=1;
			}
			if(ofTheTwo > 1){
				//cout<<"Exit loop\n";
				break;
			}
		}
	}   

	vector<Node> getAllNodes(vector<Node> &graph){
		vector<Node> HashSet;
		for(int i=0 ; i<graph.size() ; i++ ){
			HashSet.push_back(graph[i]);
		}
		return HashSet;
	}


	vector<Node> createDAGraphIter(int n){
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
		for(int j=0 ; j < m; j++){
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
			randomGraph[index2].inDegree+=1;
		}
		
		//return Adjacency Vector:
		return randomGraph;
	}
};


class TopSort{
    public:
	vector<Node> Kahns(vector<Node> &graph){
		vector<Node> kiwi;//Know that it was intended to be named "queue" but it is not available as a name. So kiwi is a false-close name.
		bool atleastone=false;
		for(int k=0; k<graph.size() ; k++){
			if(graph[k].edges.size()==0 && graph[k].inDegree==0){
				kiwi.push_back(graph[k]);
				graph[k].inDegree=-1;
			}
		}
		while(true){//I break it when I find no zero indegrees
			for(int i=0 ; i < graph.size() ; i++){
				if(graph[i].inDegree == 0){
					kiwi.push_back(graph[i]);
					for(int j=0;j<graph[i].edges.size();j++){
						graph[i].edges[j]->inDegree-=1;
					}
					graph[i].inDegree-=1;
					atleastone=true;
				}
				
			}
			if(!atleastone){
				break;
			}
			else{
				atleastone=false;
			}
		}
		
		if(graph.size()!=kiwi.size()){
			cout<<"\n\n***Not a DAG!!! ERROR!***\n\n";
			exit(3);
		}
		
		return kiwi;
	}
};


class WeightedGraph{
    public:
	void addNode(string nodeVal, vector<Node> &graph){ 
		Node newNode;
		newNode.value=nodeVal;
		
		graph.push_back(newNode);
	} 
	
	void addWeightedEdge(string first, string second, int Weightededge, vector<Node> &graph){ 
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
				indexSecond =i;
			}
			if(firstPtr!=NULL && secondPtr!=NULL){
				break;
			}
		}
		graph[indexFirst].edges.push_back(secondPtr);
		graph[indexFirst].weights.push_back(Weightededge);
		graph[indexSecond].inDegree+=1;
	}
	
	void removeDirectedEdge(Node first, Node second, vector<Node> &graph){ 
		int ofTheTwo=0;
		
		string First = first.value;
		string Second = second.value;
		int indexedWeight=0;
		int indexedGraph=0;
		
		for(int i =0; i<graph.size() ; i++){
			if(graph[i].value== First){
				for (auto it = graph[i].edges.begin(); it != graph[i].edges.end(); ++it){
					if((*it)->value==second.value){
					    (*it)->inDegree--;
						graph[i].edges.erase(it);
						ofTheTwo++;
						indexedGraph=i;
						break;
					}
					indexedWeight++;
				}
				
			}
			if(ofTheTwo > 1){
				//cout<<"Exit loop\n";
				break;
			}
		}
		vector<int>::iterator iter=graph[indexedGraph].weights.begin()+indexedWeight;
		graph[indexedGraph].weights.erase(iter);
	} 
	
	vector<Node> getAllNodes(vector<Node> &graph){
		vector<Node> HashSet;
		for(int i=0 ; i<graph.size() ; i++ ){
			HashSet.push_back(graph[i]);
		}
		return HashSet;
	}
	
	vector<Node> createRandomCompleteWeightedGraph(int n){
	    vector<Node> graph;
	    for(int i=0 ; i<n ; i++){
	        string temp=to_string(rand()% (n + 0) + 0);
	        bool found=false;
	        for(int j=0 ; j<graph.size() ; j++){
	            if(temp==graph[j].value){
	                found=true;
	            }
	        }
	        if(!found){
	            addNode(temp,graph);
	        }
	        else{
	            i--;
	        }
	        found=false;
	    }
	    
	    for(int i=0 ; i < (n*(n-1)) ; i++){
	        string temp=to_string(rand()% (n + 0) + 0);
	        bool found=false;
	        int index=rand()% (n + 0) + 0;
	        while(graph[index].value==temp){
	            temp=to_string(rand()% (n + 0) + 0);
	            index=rand()% (n + 0) + 0;
	        }
	        for(int j=0 ; j<graph[index].edges.size() ;j++){
	            if(temp==graph[index].edges[j]->value){
	                found=true;
	            }
	        }
	        if(!found){
	            for(int k=0 ; k<graph.size() ; k++){
	                if(graph[k].value==temp){
	                     graph[index].edges.push_back(&graph[k]);
	                     graph[k].inDegree++;
	                }
	            }
	           
	            graph[index].weights.push_back(rand()% (10 + 1) + 1);
	            
	        }
	        else{
	            i--;
	           found=false;
	        }
	        
	    }
	    return graph;
	}
};




vector<Node> createLinkedList(int n){
    vector<Node> graph;
    WeightedGraph wg;
    for(int i=0 ; i<n ; i++){
        wg.addNode(to_string(i),graph);
    }
    for(int i=0 ; i<n ; i++){
        if(i!=n-1){
            graph[i].edges.push_back(&graph[i+1]);
            graph[i].weights.push_back(i);
            if(i!=0){
                graph[i].inDegree++;
            }
        }
        else{
            graph[i].inDegree++;
        }
    }
    return graph;
}

map<string,int> dijksttras(Node &start){
    map<string,int> dijkstasTable;
    vector<Node*> lista;
    vector<Node*> helperList;
    
    dijkstasTable.insert(pair<string, int>(start.value,0));
    
    for(int i=0 ; i<start.edges.size() ; i++){
        lista.push_back(start.edges[i]);
        dijkstasTable.insert(pair<string, int>(start.edges[i]->value,start.weights[i]));
    }
    
    while(lista.size()>0){
        for(int i=0 ; i<lista.size() ; i++){
            for(int j=0 ; j<lista[i]->edges.size() ; j++){
                bool found=false;
                for(int k=0 ; k<helperList.size() ; k++){
                    if(helperList[k]->value == lista[i]->edges[j]->value){
                        found=true;
                        break;
                    }
                }
                if(!found && lista[i]->edges[j]->inDegree>0){
                    helperList.push_back(lista[i]->edges[j]);
                    lista[i]->edges[j]->inDegree--;
                }
                if(dijkstasTable.find(lista[i]->edges[j]->value) != dijkstasTable.end()){
                    
                    if(dijkstasTable[lista[i]->edges[j]->value] > lista[i]->weights[j]+dijkstasTable[lista[i]->value]){
                        dijkstasTable[lista[i]->edges[j]->value]=lista[i]->weights[j]+dijkstasTable[lista[i]->value];
                    }
                    
                }
                else{
                    dijkstasTable.insert(pair<string, int>(lista[i]->edges[i]->value,lista[i]->weights[i]+dijkstasTable[lista[i]->value]));
                }
            }
        }
        
        lista.clear();
        for(int i=0 ; i<helperList.size() ; i++){
            lista.push_back(helperList[i]);
        }
        helperList.clear();
    }
    
    return dijkstasTable;
}
//Qestions 4 and 5 section ends here--------------------------------------------

//------------------------------------------------------------------------------

//Question 6 section------------------------------------------------------------
class GridGraph{
    public:
    void addGridNode(int x, int y, string nodeVal, vector<gridNode> &graph){ 
    	gridNode newNode;
    	newNode.value=nodeVal;
    	newNode.x=x;
    	newNode.y=y;
    	graph.push_back(newNode);
    } 
    
    void addUdirectedEdge(string first, string second, vector<gridNode> &graph){ 
    	gridNode* firstPtr = NULL;
    	gridNode* secondPtr = NULL;
    	
    	int indexFirst, indexSecond;
    	
    	for(int i =0; i<graph.size() ; i++){
    		if(graph[i].value== first){
    			firstPtr = &graph[i];
    			indexFirst=i;
    		}
    		else if(graph[i].value== second){
    			secondPtr = &graph[i];
    			indexSecond =i;
    		}
    		if(firstPtr!=NULL && secondPtr!=NULL){
    			break;
    		}
    	}
    	bool hommies=false;
    	if(((graph[indexFirst].x==graph[indexSecond].x-1)||(graph[indexFirst].x==graph[indexSecond].x+1))&&(graph[indexFirst].y==graph[indexSecond].y)){
    	    hommies=true;
    	}
    	else if(((graph[indexFirst].y==graph[indexSecond].y-1)||(graph[indexFirst].y==graph[indexSecond].y+1))&&(graph[indexFirst].x==graph[indexSecond].x)){
    	    hommies=true;
    	}
    	if(hommies){
        	graph[indexFirst].edges.push_back(secondPtr);
        	graph[indexSecond].edges.push_back(firstPtr);
        	graph[indexSecond].inDegree+=1;
        	graph[indexFirst].inDegree+=1;
    	}
    }
    
    void removeUdirectedEdge(gridNode &first, gridNode &second){ 
    	for(vector<gridNode*>::iterator it=first.edges.begin() ; it!=first.edges.end() ; ++it){
    	    if((*it)->value==second.value){
    	        first.edges.erase(it);
    	        break;
    	    }
    	}
    	for(vector<gridNode*>::iterator it=second.edges.begin() ; it!=second.edges.end() ; ++it){
    	    if((*it)->value==first.value){
    	        second.edges.erase(it);
    	        break;
    	    }
    	}
    	
    	first.inDegree-=1;
    	second.inDegree-=1;
    }
    
    vector<gridNode> getAllNodes(vector<gridNode> &graph){
        vector<gridNode>toBeReturned;
        
        for(int i=0 ; i<graph.size() ; i++){
            toBeReturned.push_back(graph[i]);
        }
        
        return toBeReturned;
    }
};

vector<gridNode> createRandomRandomGridGraph(int n){
    vector<gridNode> graph;
    GridGraph gd;
    for(int y=0 ; y<n ; y++){
        for(int x=0 ; x<n ; x++){
            string val=to_string((rand() % (n*n))+1);
            bool found=false;
            for(int i=0 ; i<graph.size() ; i++){
                if(graph[i].value==val){
                    found=true;
                    x--;
                }
            }
            if(!found){
                gd.addGridNode(x,y,val,graph);
            }
            
        }
    }
    
    for(int i=0 ; i<graph.size() ; i++){
        int chance1;
        int chance2;
        
        if((i+1)%n!=0){//right
            chance1=(rand()%2);
            if(chance1==1){//i-th right chance.
                graph[i].edges.push_back(&graph[i+1]);
                graph[i+1].edges.push_back(&graph[i]);
                graph[i].inDegree++;
                graph[i+1].inDegree++;
            }
            
            chance2=(rand()%2);
            if((chance2==1)&&(chance1==0)){//i+1 left chance.
                graph[i+1].edges.push_back(&graph[i]);
                graph[i].edges.push_back(&graph[i+1]);
                graph[i].inDegree++;
                graph[i+1].inDegree++;
            }
        }
        
        if(i<((n*n))-n){//down
            chance1=(rand()%2);
            if(chance1==1){//i-th down chance.
                graph[i].edges.push_back(&graph[i+n]);
                graph[i+n].edges.push_back(&graph[i]);
                graph[i+n].inDegree++;
                graph[i].inDegree++;
            }
            chance2=(rand()%2);
            if((chance2==1)&&(chance1==0)){//i+n up chance.
                graph[i+n].edges.push_back(&graph[i]);
                graph[i].edges.push_back(&graph[i+n]);
                graph[i+n].inDegree++;
                graph[i].inDegree++;
            }
        }
        
    }
    
    return graph;
}

vector<gridNode> astar(gridNode &sourceNode, gridNode &destNode){
    vector<gridNode> grid;
    vector<gridNode*> visited;
    vector<gridNode*> alternatives;
    vector<gridNode*> farAlternatives;
    
    gridNode* current=&sourceNode;
    gridNode* next;
    
    int toDest= (destNode.x+destNode.y) - (current->x+current->y);
    current->toDestination=toDest;
    current->fromStart=0;
    current->checked=true;
    
    visited.push_back(current);
    
    int count=0;
    while(current->value!=destNode.value){// && count<5){
        count++;
        bool foundConnection=false;
        for(int i=0 ; i<current->edges.size() ; i++){
            current->edges[i]->fromStart=current->fromStart+1;
            current->edges[i]->toDestination=(destNode.x+destNode.y) - (current->edges[i]->x+current->edges[i]->y);
            if((current->edges[i]->toDestination < toDest)&&(current->edges[i]->checked==false)){
                next=current->edges[i];
                toDest=current->edges[i]->toDestination;
                foundConnection=true;
            }
            else if((current->edges[i]->toDestination == toDest)&&(current->edges[i]->checked==false)){
                alternatives.push_back(current->edges[i]);
            }
            else if((current->edges[i]->toDestination > toDest)&&(current->edges[i]->checked==false)){
                farAlternatives.push_back(current->edges[i]);
            }
        }
        if(foundConnection){
            current=next;
            current->checked=true;
            visited.push_back(current);
        }
        else{
            
            if((alternatives.size()==0)&&(farAlternatives.size()==0)&&(current->value!=destNode.value)){
                cout<<"No way to the destination. Try another grid that is solavable!\n";
                grid.clear();
                return grid;
            }
            
            if(alternatives.size()==0){
                alternatives.push_back(farAlternatives[farAlternatives.size()-1]);
                farAlternatives.pop_back();
            }
            
            current=alternatives[alternatives.size()-1];
            current->checked=true;
            alternatives.pop_back();
            visited.push_back(current);
        }
    }
    auto it = grid.insert(grid.begin(), *current);
    for(int i=visited.size()-1 ; i>0 ; i--){
        if((current->x==visited[i]->x)&&((current->y==visited[i]->y+1)||(current->y==visited[i]->y-1))){
            it = grid.insert(grid.begin(), *visited[i]);
            current=visited[i];
        }
        else if((current->y==visited[i]->y)&&((current->x==visited[i]->x+1)||(current->x==visited[i]->x-1))){
            it = grid.insert(grid.begin(), *visited[i]);
            current=visited[i];
        }
    }
    it = grid.insert(grid.begin(), *visited[0]);
    if((grid.size()==2)&&(grid[0].value==grid[1].value)){
        grid.pop_back();
    }
    return grid;
}
//Qestions 6 section ends here--------------------------------------------------

//------------------------------------------------------------------------------

int main() 
{ 
    string response="";
    int n;
    //Question 4:===============================================================
    cout<<"If you type y \"Question 4\" section is going to start. If you type s it will skip \"Question 4\".\n";
    cin>>response;
    while((response!="y")&&(response!="s")){
        cin.ignore();
        cout<<"Incorrect input! Please type y or s.\n";
        cin>>response;
    }
    if(response=="y"){
        DirectedGraph dg;
        
        vector<Node> graph;
        
        dg.addNode("a",graph);
        dg.addNode("c",graph);
    	dg.addNode("b",graph);
    	dg.addNode("d",graph);
    	dg.addNode("e",graph);
        
        dg.addDirectedEdge("a","b",graph);
        dg.addDirectedEdge("b","c",graph);
        dg.addDirectedEdge("e","c",graph);
        dg.addDirectedEdge("e","b",graph);
        dg.addDirectedEdge("d","b",graph);
        dg.addDirectedEdge("d","e",graph);
        dg.addDirectedEdge("a","d",graph);
        
        cout<<"-------------------------------------------------------------------\n";
        cout<<"Printing a five node (manual) graph:\n";
    	printDirectedGraph(graph);
    	
    	cout<<"\n-------------------------------------------------------------------\n";
    	cout<<"Printing graph with edge from "<<graph[0].value<<" to "<<graph[2].value<<" removed:\n";
    	dg.removeDirectedEdge(graph[0],graph[2],graph);
        printDirectedGraph(graph);
        
        cout<<"\n-------------------------------------------------------------------\n";
        cout<<"Printing a graph returned from getAllNodes() on the above:\n";
        printDirectedGraph(dg.getAllNodes(graph));
        
        cout<<"\n-------------------------------------------------------------------\n";
        cout<<"If you want to make a random n node (n=5) graph type 1\nIf you want to give it a new value n type 2\n";
    	n=5;
        cin>>response;
        while((response!="1")&&(response!="2")){
            cin.ignore();
            cout<<"Incorrect input! Please type 1 or 2.\n";
            cin>>response;
        }
        if(response=="2"){
            cout<<"Give a number (or crush the program) for a new n.\n";
            cin.ignore();
            cin>>response;
            n=stoi(response);
        }
        
        graph.clear();
        graph=dg.createDAGraphIter(n);
        
        cout<<"\n-------------------------------------------------------------------\n";
        cout<<"A random graph with n nodes (n="<<n<<") has been successfully created.\n";
        cout<<"If you want to print the random graph type y. If not type n. (It will print n lines)\n";
        
        cin>>response;
        while((response!="y")&&(response!="n")){
            cin.ignore();
            cout<<"Incorrect input! Please type y or n.\n";
            cin>>response;
        }
        if(response=="y"){
            cout<<"\n-------------------------------------------------------------------\n";
        	cout<<"Printing random graph: \n";
        	printDirectedGraph(graph);
        }
        
        cout<<"\n-------------------------------------------------------------------\n";
        cout<<"Vector returned by Kahns's: \n";
        TopSort ts;
        vector<Node> solution=ts.Kahns(graph);
        printDirectedGraph(solution);
        
    }
    
    
    //Question 5:===============================================================
    cout<<"\n\nIf you type y \"Question 5\" section is going to start. If you type s it will skip \"Question 5\".\n";
    cin>>response;
    while((response!="y")&&(response!="s")){
        cin.ignore();
        cout<<"Incorrect input! Please type y or s.\n";
        cin>>response;
    }
    if(response=="y"){
        vector<Node> graph;
        WeightedGraph wg;
        
        wg.addNode("a",graph);
        wg.addNode("c",graph);
    	wg.addNode("b",graph);
    	wg.addNode("d",graph);
    	wg.addNode("e",graph);
        
        wg.addWeightedEdge("a","b",6,graph);
        wg.addWeightedEdge("b","c",5,graph);
        wg.addWeightedEdge("e","c",5,graph);
        wg.addWeightedEdge("e","b",2,graph);
        wg.addWeightedEdge("d","b",2,graph);
        wg.addWeightedEdge("d","e",1,graph);
        wg.addWeightedEdge("a","d",1,graph);
        
        cout<<"-------------------------------------------------------------------\n";
        cout<<"Printing a five node (manual) graph:\n";
    	printGraphAdvanced(graph);
    	
    	
    	cout<<"\n-------------------------------------------------------------------\n";
    	cout<<"Printing graph with edge from "<<graph[0].value<<" to "<<graph[2].value<<" removed:\n";
    	wg.removeDirectedEdge(graph[0],graph[2],graph);
    	printGraphAdvanced(graph);
    	
    	cout<<"\n\nEnter any not empty string to continue to the linked list.\n\n";
    	cin>>response;
    	graph.clear();
    	cout<<"\n-------------------------------------------------------------------\n";
        cout<<"Printing linked list: \n";
        graph=createLinkedList(5);
        printGraphAdvanced(graph);
        cout<<"\n-------------------------------------------------------------------\n";
    	
    	cout<<"If you want to make a random n node (n=5) graph type 1\nIf you want to give it a new value n type 2\n";
    	n=5;
        cin>>response;
        while((response!="1")&&(response!="2")){
            cin.ignore();
            cout<<"Incorrect input! Please type 1 or 2.\n";
            cin>>response;
        }
        if(response=="2"){
            cout<<"Give a number (or crush the program) for a new n.\n";
            cin.ignore();
            cin>>response;
            n=stoi(response);
        }
        cout<<"\n-------------------------------------------------------------------\n";
        
    	graph.clear();
    	
    	graph=wg.createRandomCompleteWeightedGraph(n);
    	cout<<"A random graph with n nodes (n="<<n<<") has been successfully created.\n";
        cout<<"If you want to print the random graph type y. If not type n. (It will print n lines)\n";
        
        cin>>response;
        while((response!="y")&&(response!="n")){
            cin.ignore();
            cout<<"Incorrect input! Please type y or n.\n";
            cin>>response;
        }
        if(response=="y"){
            cout<<"\n-------------------------------------------------------------------\n";
        	cout<<"Printing random graph: \n";
        	printGraphAdvanced(graph);
        }
    	
        
        map<string,int> some=dijksttras(graph[0]);
        cout<<"\n-------------------------------------------------------------------\n";
        cout<<"Printing distances from the one with distance --> 0 :\n";
        for(map<string,int>::iterator it = some.begin(); it != some.end(); ++it) {
            cout << it->first << " --> " << it->second<<endl;
        }
        cout<<"\n-------------------------------------------------------------------\n";
    }
	
	//Question 6:===============================================================
    cout<<"If you type \"Question 6\" section is going to start. If you type e it will exit the program.\n";
    cin>>response;
    while((response!="y")&&(response!="e")){
        cin.ignore();
        cout<<"Incorrect input! Please type y or e.\n";
        cin>>response;
    }
    if(response=="e"){
        return 0;
    }
    vector<gridNode> graph;
    GridGraph gd;
    
    gd.addGridNode(1,1,"a",graph);
    gd.addGridNode(0,2,"b",graph);
    gd.addGridNode(1,2,"c",graph);
    gd.addGridNode(3,1,"d",graph);
    
    gd.addUdirectedEdge("a","b",graph);
    gd.addUdirectedEdge("a","c",graph);
    gd.addUdirectedEdge("c","b",graph);
    gd.addUdirectedEdge("c","d",graph);
    cout<<"-------------------------------------------------------------------\n";
    cout<<"Printing a four (manual) graph:\n";
    printGridGraph(graph);
    
    cout<<"\n-------------------------------------------------------------------\n";
    cout<<"Printing the above with the connection from "<<graph[0].value<<" to "<<graph[2].value<<" removed:\n";
    gd.removeUdirectedEdge(graph[0],graph[2]);
    printGridGraph(graph);
    
    cout<<"\n-------------------------------------------------------------------\n";
    cout<<"Printing graph of getAllNodes:\n";
    gd.getAllNodes(graph);
    printGridGraph(graph);
    
    cout<<"\n-------------------------------------------------------------------\n";
    graph.clear();
    n=100;
    cout<<"If you want to make a random 100x100 grid type 1\nIf you want to give it a new value n for an n x n grid type 2\n";
    cin>>response;
    while((response!="1")&&(response!="2")){
        cin.ignore();
        cout<<"Incorrect input! Please type 1 or 2.\n";
        cin>>response;
    }
    if(response=="2"){
        cout<<"Give a number (or crush the program) for a new n.\n";
        cin.ignore();
        cin>>response;
        n=stoi(response);
    }
    
    cout<<"\n-------------------------------------------------------------------\n";
    cout<<"Grid is being created.\nPlease wait.\n";
    graph=createRandomRandomGridGraph(n);
    
    cout<<"A random grid n by n (n="<<n<<") has been successfully created.\n";
    cout<<"If you want to print the random graph nodes with their info type y. If not type n. (It will print n*n lines)\n";
    cin>>response;
    while((response!="y")&&(response!="n")){
        cin.ignore();
        cout<<"Incorrect input! Please type y or n.\n";
        cin>>response;
    }
    if(response=="y"){
        cout<<"\n-------------------------------------------------------------------\n";
        cout<<"Printing the random "<<n<<" by "<<n<<"\n";
        printGridGraph(graph);
    }
    cout<<"\n-------------------------------------------------------------------\n";
    cout<<"A* is currently running to find the quickest path.\nPlease Wait.\n";
    vector<gridNode> path=astar(graph[0],graph[(n*n)-1]);
    cout<<"A* has successfully returned the path.\n";
    
    cout<<"\n-------------------------------------------------------------------\n";
    cout<<"Printing returned path:\n";
    if(path.size()==0){
        cout<<"The path is empty. (There was no path reaching the destination.)";
        return 0;
    }
    onlyVals(path);
    cout<<"\nThe size of the path is:   "<<path.size()<<"\n(with sourceNode and destNode included in this path)"<<endl;
    
    return 0;
}
