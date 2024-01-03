#include <bits/stdc++.h>
#include <iostream>
#include <string.h>

using namespace std;
const int INF = 999999999;

void modifySize(vector<set<pair<int, int>>> &graphs, int size) {
  graphs.resize(size);
}

void addAdjacent(vector<set<pair<int, int>>> &graphs, int x, int z,
                 int weight) {
  graphs[x].insert(make_pair(z, weight));
  graphs[z].insert(make_pair(x, weight));
}

void printGraph(vector<set<pair<int, int>>> graphs) {
  for (int i = 0; i < graphs.size(); i++) {
    cout << "Grafo da lista de adjacencia: " << i << endl;
    cout << "Adjacentes ";
    for (auto &k : graphs[i]) {
      cout << " => " << k.first << "(" << k.second << ")";
    }
    cout << endl;
  }
}

pair<int, vector<int>> dijkstra(vector<set<pair<int, int>>> adj, int first,int last) {
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>pqueue;
  vector<int> dist(adj.size(), INF);
  vector<int> previous(adj.size(), -1);
  pair<int, int> current(INF, INF);
  dist[first] = 0;
  pqueue.push(make_pair(0, first));

  while (!pqueue.empty() && current.second != last) {
    current = pqueue.top();
    
    pqueue.pop();
    for (auto value : adj[current.second]) {
      if (dist[current.second] + value.second < dist[value.first]) {
        dist[value.first] = dist[current.second] + value.second;
        previous[value.first] = current.second;
        cout << dist[value.first] << " " << value.first << endl;
        pqueue.push(make_pair(dist[value.first], value.first));
      }
    }
  }
  return make_pair(dist[last], previous);
}

int main() {
  int size = 6;
  int option;
  int value1, value2, times;
  int firstWitdh, secondWitdh;
  int weightVert;
  int current;

  pair<int, vector<int>> resultDijs;
  vector<set<pair<int, int>>> graphs;

  list<int> values; // var de list para usar no tropologic
  vector<set<pair<int, int>>> graphPrims;

  cout << "Digite o numero de vetores" << endl;
  cin >> size;
  modifySize(graphs, size);

  while (option != 5) {
    cout << "[1] Adcionar adjacencia" << endl
         << "[2] Mostrar grafos" << endl
         << "[3] Dijkstra" << endl
         << "[4] Sair do programa" << endl
         << "Digite uma opcao: ";
    cin >> option;

    switch (option) {
    case 1:
      cout << "Quantas arestas deseja adcionar?" << endl;
      cin >> times;
      for (int i = 0; i < times; i++) {
        cout << "Digite os valores adjacentes(Exemplo: 0 1)" << endl;
        cin >> value1 >> value2;
        cout << "Digite o peso dessa aresta" << endl;
        cin >> weightVert;
        addAdjacent(graphs, value1, value2, weightVert);
      }
      break;

    case 2:
      printGraph(graphs);
      break;
    case 3:
      cout << "Vertice inicial: ";
      cin >> firstWitdh;
      cout << "Vertice final: ";
      cin >> secondWitdh;
      resultDijs = dijkstra(graphs, firstWitdh, secondWitdh);
      cout << "Distancia minima: " << resultDijs.first << endl;
      cout << endl;
      current = secondWitdh;
      while (current != -1) {
        cout << current << " => ";
        current = resultDijs.second[current];
      }
      cout << endl;
      break;

    case 4:
      cout << "Saindo...";
      break;

    default:
      cout << "Opcao invalida!" << endl;
      break;
    }
  }
  return 0;
}
