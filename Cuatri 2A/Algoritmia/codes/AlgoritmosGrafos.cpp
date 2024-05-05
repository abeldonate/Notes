using namespace std;
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

using ll = long long;
using P = pair<int, int>;
using VP = vector<P>;
using VVP = vector<VP>;
using VI = vector<int>;
using VVI = vector<VI>;
using VB = vector<bool>;

VVI M;  // Matriz de adyacencia
VVI G;  // Lista de aristas
VP V;   // Pair con las aristas
VVP GP; // Conjunto de veritces en pairs (con costes)
int n = M.size();
int m = G.size();
int INF = 1e9;

//=========================================
// DFS 
// O(n+m)
VI visited(n, false);
void DFS(int u) {
  if (visited[u])
    return;
  visited[u] = true;
  cout << u << endl;
  for (int v : G[u]) {
    DFS(v);
  }
}

//=========================================
// BFS
// O(n+m)
void BFS(int u) {
  VI visited(n, false);
  queue<int> Q;
  visited[u] = true;
  Q.push(u);
  while (not Q.empty()) {
    int x = Q.front();
    Q.pop();
    cout << x << endl;
    for (int y : G[x])
      if (not visited[y]) {
        visited[y] = true;
        Q.push(y);
      }
  }
}

//=========================================
// Dijkstra
// O(n+ln(m))
void Dijkstra(int ini) {
  VI dist(n, INF);
  VI pare(n);
  priority_queue<P> Q;
  dist[ini] = 0;
  Q.push(P(0, ini));
  while (not Q.empty()) {
    P p = Q.top();
    Q.pop();
    int d = -p.first;
    int x = p.second;
    if (d == dist[x]) {
      for (P arc : GP[x]) {
        int c = arc.first;
        int y = arc.second;
        int d2 = d + c;
        if (d2 < dist[y]) {
          dist[y] = d2;
          pare[y] = x;
          Q.push(P(-d2, y));
        }
      }
    }
  }
}

//=========================================
// Distancia minima entre dos vertices
// O(n^3)
VVI FloydWarshall() {
  for (int k = 0; k < n; ++k)
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
        M[i][j] = min(M[i][j], M[i][k] + M[k][j]);

  return M;
}

//==========================================
// Longitud del camino mas largo en DAG (Dinamica)
// O(n+m)
VI R(n, -1);
int f(int x) {
  int &res = R[x];
  if (res != -1)
    return res;
  res = 0;
  for (int y : G[x])
    res = max(res, 1 + f(y));
  return res;
}

//=========================================
//Arbol generador
VI pare(n);
int repre(int x) {
  if (pare[x] == -1)
    return x;
  int r = repre(pare[x]);
  pare[x] = r;
  return r;
}

void arbre_generador() {
  pare = VI(n, -1);
  int compo = n;
  for (P p : V) {
    int x = p.first;
    int y = p.second;
    int rx = repre(x);
    int ry = repre(y);
    if (rx != ry) {
      pare[ry] = rx;
      // pare[y] = x; error tipico
      cout << x << ' ' << y << endl;
      if (--compo == 1)
        return;
    }
  }
  cout << "graf no connex!" << endl; // n > 1
}

//=========================================
// Ordenacion topologica
// O(n+m)
void TopoSort() {
  VI deg(n, 0); // grados de cada nodo (rellenar al leer)
  stack<int> pila;
  for (int x = 0; x < n; ++x) {
    if (deg[x] == 0)
      pila.push(x);
    while (not pila.empty()) {
      int x = pila.top();
      pila.pop();
      cout << x << endl;
      for (int y : G[x]) {
        if (--deg[y] == 0)
          pila.push(y);
      }
    }
  }
}

int main() {}
