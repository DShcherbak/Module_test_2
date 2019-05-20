#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <queue> 
#include "Application.h"

const int MAX_VERTICES = 500;
const double inf = 100000000.1;

struct Graph{
    int vertices;
    int adj[MAX_VERTICES][MAX_VERTICES];
    int min_dist[MAX_VERTICES][MAX_VERTICES];


    Graph(std::vector <std::pair <int, std::pair <int,int>>> distances, int v, double threshold){
        int from;
        int to;
        vertices = v;
        std::pair <int, std::pair <int,int>> p;
        
        for(int i = 0; i < vertices; i++)
            for (int j = 0; j < vertices; j++)
                min_dist[i][j] = inf;

        for(int i = 0; i < distances.size(); i++){
            p = distances[i];
            if(p.first > threshold){
                adj[p.second.first][p.second.second] = p.first;
                adj[p.second.second][p.second.first] = p.first;
            }
        }
    }

    Graph(std::vector <Application*> apps, double threshold){
        int from;
        int to;
        double d;
        vertices = apps.size();

        for(int i = 0; i < vertices; i++)
            for (int j = 0; j < vertices; j++)
                min_dist[i][j] = inf;


        for(int i = 1; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if(i > j)
                    d = distance(apps[i], apps[j]);
                else if(i == j)
                    d = 0;
                else
                    continue;
                if (d > threshold){
                    adj[i][j] = d;
                    adj[j][i] = d;
                }
                else{
                    adj[i][j] = -1;
                    adj[j][i] = -1;
                }
            }
        }
    }


};

void dfs_component(Graph* G, int cur, std::vector <bool> &visited){
    std::cout << cur << " ";
    visited[cur] = 0;
    for(int i = 0, n = G->vertices; i < n; i++)
        if(!visited[i] && G->adj[cur][i] != -1)
            dfs_component(G,i,visited);
}

void Dijkstra(Graph* G, int st){
	std::vector <bool> visited;
	
	int cur, vert = G->vertices, v = -1, d = inf;
	visited.resize(vert);
    G->min_dist[st][st] = 0;
    while(true){
        v = -1;
        d = inf;
        for(int i = 0; i < vert; i++) {
            if (!visited[i] && G->min_dist[st][i] < d) {
                d = G->min_dist[st][i];
                v = i;
            }
        }
        if(v == -1)
            break;
        visited[v] = true;
        for(int i = 0; i < vert; i++) {
            if(G->adj[v][i] != -1) {
                G->min_dist[st][i] = std::min(G->min_dist[st][i],G->min_dist[st][v] + G->adj[v][i]);
            }
        }
    }
}

