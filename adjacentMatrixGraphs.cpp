#include <bits/stdc++.h>
#include <iostream>
#include <string.h>

using namespace std;

const int INF = 9999999;

void addEdge(vector<vector<int>> &matrix, int x, int y, int weight) {
  matrix[x][y] = weight;
}

void printGraph(vector<vector<int>> graphs) {
  for (int i = 0; i < graphs.size(); i++) {
    cout << "[" << i << "]";
    for (auto &k : graphs[i]) {
      if (k == INF) {
        cout << " => "
             << "INF";
      } else
        cout << " => " << k;
    }
    cout << endl;
  }
}

void floydWarshall(vector<vector<int>> &graph) {
  int size = graph.size();
  vector<vector<int>> dist(size, vector<int>(size, INF));

  for (int i = 0; i < size; i++) {
    for (int c = 0; c < size; c++) {
      if (graph[i][c] > 0) {
        dist[i][c] = graph[i][c];
      }
    }
  }

  for (int i = 0; i < size; i++) {
    for (int c = 0; c < size; c++) {
      for (int l = 0; l < size; l++) {
        if (dist[c][l] > dist[c][i] + dist[i][l]) {
          dist[c][l] = dist[c][i] + dist[i][l];
        }
      }
    }
    printGraph(dist);
    cout<<endl;
  }
  // printGraph(dist);
}

int main() {
  int sizeMatrix = 4;
  // cout << "Digite quantas vertices: ";
  // cin >> sizeMatrix;
  vector<vector<int>> graphs(sizeMatrix, vector<int>(sizeMatrix, 0));

  graphs = {{INF,3,INF,7},
    {8, INF, 2, INF},
    {5, INF, INF, 1},
            {2, INF, INF, INF}};
  
  // addEdge(graphs, 0, 1, 5);
  // addEdge(graphs, 0, 3, 10);

  // addEdge(graphs, 1, 2, 3);

  // addEdge(graphs, 2, 3, 1);
  printGraph(graphs);
  cout << "==========" << endl;
  floydWarshall(graphs);

  // addEdge(graphs,7,1,20);
  // addEdge(graphs,6,6,30);
  // addEdge(graphs,5,2,40);
  // addEdge(graphs,3,""""""""1,15);
  // addEdge(graphs,2,1,2);

  return 0;
}
