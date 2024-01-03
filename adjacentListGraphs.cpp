#include <iostream>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;
const int INF = 999999999;

void modifySize(vector<set<pair<int,int>>> &graphs,int size){
   graphs.resize(size);
}

void addAdjacent(vector<set<pair<int,int>>> &graphs,int x, int z, int weight){
   graphs[x].insert(make_pair(z,weight));
   graphs[z].insert(make_pair(x,weight));
}


void printGraph(vector<set<pair<int,int>>> graphs){
    for (int i = 0 ; i < graphs.size() ;i++){
        cout << "Grafo da lista de adjacencia: " << i << endl;
        cout << "Adjacentes ";
        for (auto& k: graphs[i]){
            cout << " => " << k.first << "(" << k.second << ")";
        }
        cout << endl;
    }
}

void depthGraph(vector<set<pair<int,int>>> graphs, int value){
    vector<bool> visited(graphs.size(), false);
    stack<int> stk;
    int cont = 0;
    stk.push(value);
    while(!stk.empty()){
        value = stk.top();
        cout<< value << " ";
        visited[value] = true;
        stk.pop();
        for(auto i: graphs[value]){
         if(!visited[i.first]){
           cont++;
           stk.push(i.first);
        }
      }
    }
    cout << "Arestas unicas: "<< cont << endl;
}

void widthGraph(vector<set<pair<int,int>>> adj, int s){
    vector<bool> visited(adj.size(), false);
    vector<int> distance(adj.size(),0);
    queue<int> queue_adj;
    visited[s] = true;
    queue_adj.push(s); 
    while(!queue_adj.empty()){
      s = queue_adj.front();
      queue_adj.pop();
      for(auto i: adj[s]){
        if(!visited[i.first]){
            visited[i.first] = true;
            distance[i.first] = distance[s]+1;
            queue_adj.push(i.first);
        }
       }
      }
    for (auto i: distance){
        cout << i << " ";
    }
    cout << endl;
  };

pair<int,vector<int>> dijkstra(vector<set<pair<int,int>>> adj,int first,int last){
   priority_queue<pair <int,int>, vector<pair<int,int>>,greater<pair <int,int>>> pqueue;
   vector<int> dist(adj.size(),INF);
   vector<int> previous(adj.size(),-1);
   pair<int,int> current(INF,INF);
   dist[first]=0;
   pqueue.push(make_pair(0,first));
 
   while(!pqueue.empty() && current.second != last){
       current = pqueue.top(); 
       pqueue.pop(); 
       for(auto value: adj[current.second]){
           if(dist[current.second] + value.second < dist[value.first]){
               dist[value.first] = dist[current.second] + value.second;
               previous[value.first] = current.second;
               pqueue.push(make_pair(dist[value.first],value.first));
           }
       }
   }
   return make_pair(dist[last],previous);
}

list<int> topologicalSort(vector<set<pair<int,int>>> adj){
  int size = adj.size();
  int current;
  list<int> values;
  vector<int> degree(size);
  queue<int> order;
  for (int i = 0;i < size;i++){
      for (auto c: adj[i])
        degree[c.first]++;
  }
  for (int v = 0; v < size;v++){
      if(degree[v] == 0){
          order.push(v);
      } 
  }
  while(!order.empty()){
      current = order.front();
      degree[current]--;
      values.push_back(current);
      order.pop();
      for (auto x: adj[current]){
          degree[x.first]--;
          if(degree[x.first] == 0){
              order.push(x.first);
          }
      }
      cout<<endl;
  }
  return values;
}

vector<set<pair<int,int>>> primS(vector<set<pair<int,int>>> adj, int start){
   vector<int> current(3);
   vector<set<pair<int,int>>> primsGraph(adj.size());
   priority_queue<vector<int>, vector<vector<int>>,greater<vector<int>>> pqueue;
   vector<bool> visited(adj.size(),false);
  
   pqueue.push({0,start,start});
   while(!pqueue.empty()){
       current = pqueue.top();
       if(current[1] != current[2] && !visited[current[2]]){
           addAdjacent(primsGraph,current[1],current[2],current[0]);
       }
       visited[current[2]] = true;
       pqueue.pop();
       for(auto value: adj[current[2]]){
           if(!visited[value.first]){
               pqueue.push({value.second,current[2],value.first});
           }
       }
   }
   return primsGraph;
}


int main(){
    int size = 6;
    int option;
    int value1,value2,times;
    int firstWitdh,secondWitdh;
    int weightVert;
    int current;

    pair<int,vector<int>> resultDijs;
    vector<set<pair<int,int>>> graphs;

    list<int> values; // var de list para usar no tropologic
    vector<set<pair<int,int>>> graphPrims;

    cout << "Digite o numero de vetores" << endl;
    cin >> size;
    modifySize(graphs,size);

    while (option != 8){
        cout << "[1] Adcionar adjacencia" << endl 
        << "[2] Mostrar grafos" << endl 
        << "[3] Profundidade(Arestas unicas)" << endl 
        << "[4] Largura" << endl
        << "[5] Dijkstra" << endl
        << "[6] Topologic" << endl
        << "[7] PrimS" << endl
        << "[8] Sair do programa" << endl
        << "Digite uma opcao: ";
        cin >> option;

        switch (option){          
      case 1:
          cout << "Quantas arestas deseja adcionar?" << endl;
          cin >> times;
          for (int i = 0; i < times; i++){
            cout << "Digite os valores adjacentes(Exemplo: 0 1)" << endl;
            cin >> value1 >> value2;
            cout << "Digite o peso dessa aresta" << endl;
            cin >> weightVert;
            addAdjacent(graphs,value1,value2,weightVert);
          }
          break;
      
        case 2:
            printGraph(graphs);
            break;

        case 3:
            cout << "Por qual vertice deseja começar?"<<endl;
            cin >> firstWitdh;
            depthGraph(graphs,firstWitdh);
            break;

        case 4:
            cout << "Por qual vertice deseja começar?"<<endl;
            cin >> firstWitdh;
            widthGraph(graphs,firstWitdh);
            break;

        case 5:
            cout << "Vertice inicial: ";
            cin >> firstWitdh;
            cout << "Vertice final: ";
            cin >> secondWitdh;
            resultDijs = dijkstra(graphs,firstWitdh,secondWitdh);
            cout << "Distancia minima: " << resultDijs.first << endl;
            cout << endl;
            current = secondWitdh;
            while(current != -1){
              cout << current << " => ";
              current = resultDijs.second[current];
            }
            cout << endl;
            break;

        case 6:
            cout << endl <<endl;
            values = topologicalSort(graphs);
            for (auto numbers: values){cout<< numbers <<" ";}
            cout << endl <<endl;
            break;
        case 7:
            cout << "Vertice inicial: ";
            cin >> firstWitdh;
            graphPrims = primS(graphs,firstWitdh);
            printGraph(graphPrims);
            break;
          
        case 8:
            cout << "Saindo...";
            break;
            
        default:
            cout << "Opcao invalida!" << endl ;
            break;
        }
    }
    return 0;
}


