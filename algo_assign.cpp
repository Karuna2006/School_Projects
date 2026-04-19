#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <limits>
#include <utility>
#include <climits>
using namespace std;

/* ===========================
   DELIVERY STRUCTURE
=========================== */

struct Delivery {
    int id;
    int weight;
    int deadline;
    int priority;
    int distance;
};

/* ===========================
   MODULE 1: MERGE SORT
=========================== */

void merge(vector<Delivery>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Delivery> L(n1), R(n2);

    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while(i < n1 && j < n2) {
        if(L[i].deadline <= R[j].deadline) { // stable
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while(i < n1)
        arr[k++] = L[i++];
    while(j < n2)
        arr[k++] = R[j++];
}

void mergeSort(vector<Delivery>& arr, int left, int right) {
    if(left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid+1, right);
    merge(arr, left, mid, right);
}

/* ===========================
   MODULE 2: DIJKSTRA
=========================== */

typedef pair<int,int> pii;

vector<int> dijkstra(int V, vector<vector<pii>>& adj, int source) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while(!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(d > dist[u]) continue;

        for(auto edge : adj[u]) {
            int v = edge.first;
            int weight = edge.second;

            if(dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

/* ===========================
   MODULE 2: KRUSKAL MST
=========================== */

struct Edge {
    int u, v, weight;
};

bool cmpEdge(Edge a, Edge b) {
    return a.weight < b.weight;
}

class DisjointSet {
    vector<int> parent, rank;
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i=0;i<n;i++)
            parent[i] = i;
    }

    int find(int x) {
        if(parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);

        if(px == py) return;

        if(rank[px] < rank[py])
            parent[px] = py;
        else if(rank[px] > rank[py])
            parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

int kruskal(int V, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), cmpEdge);

    DisjointSet ds(V);
    int mstWeight = 0;

    for(auto e : edges) {
        if(ds.find(e.u) != ds.find(e.v)) {
            mstWeight += e.weight;
            ds.unite(e.u, e.v);
        }
    }
    return mstWeight;
}

/* ===========================
   MODULE 3: FRACTIONAL KNAPSACK
=========================== */

struct Item {
    int weight;
    int value;
};

bool cmpItem(Item a, Item b) {
    return (double)a.value/a.weight > (double)b.value/b.weight;
}

double fractionalKnapsack(int capacity, vector<Item>& items) {
    sort(items.begin(), items.end(), cmpItem);

    double totalValue = 0.0;

    for(auto item : items) {
        if(capacity >= item.weight) {
            capacity -= item.weight;
            totalValue += item.value;
        } else {
            totalValue += item.value * ((double)capacity/item.weight);
            break;
        }
    }
    return totalValue;
}

/* ===========================
   MODULE 4: 0/1 KNAPSACK (DP)
=========================== */

int knapsackDP(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    for(int i = 1; i <= n; i++) {
        for(int w = 0; w <= W; w++) {
            if(wt[i-1] <= w) {
                dp[i][w] = max(dp[i-1][w],
                               val[i-1] + dp[i-1][w-wt[i-1]]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    return dp[n][W];
}

/* ===========================
   MAIN DRIVER
=========================== */

int main() {

    cout << "=== LOGISTICS OPTIMIZATION SYSTEM ===\n";

    // -------- Sorting Demo --------
    vector<Delivery> deliveries = {
        {1, 10, 5, 2, 15},
        {2, 20, 2, 1, 10},
        {3, 15, 7, 3, 20}
    };

    mergeSort(deliveries, 0, deliveries.size()-1);

    cout << "\nSorted by Deadline:\n";
    for(auto d : deliveries)
        cout << "ID: " << d.id << " Deadline: " << d.deadline << endl;

    // -------- Dijkstra Demo --------
    int V = 5;
    vector<vector<pii>> adj(V);

    adj[0].push_back({1, 4});
    adj[0].push_back({2, 1});
    adj[2].push_back({1, 2});
    adj[1].push_back({3, 1});
    adj[2].push_back({3, 5});
    adj[3].push_back({4, 3});

    vector<int> dist = dijkstra(V, adj, 0);

    cout << "\nShortest Distances from Node 0:\n";
    for(int i = 0; i < V; i++)
        cout << "To " << i << " = " << dist[i] << endl;

    // -------- Fractional Knapsack --------
    vector<Item> items = {{10,60}, {20,100}, {30,120}};
    cout << "\nFractional Knapsack Value: "
         << fractionalKnapsack(50, items) << endl;

    // -------- 0/1 Knapsack --------
    vector<int> wt = {10,20,30};
    vector<int> val = {60,100,120};
    cout << "\n0/1 Knapsack Value: "
         << knapsackDP(50, wt, val, 3) << endl;

    return 0;
}