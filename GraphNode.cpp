##include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <priority_queue>
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
        
        for(int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
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

        for(int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
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

void Dijkstra(Graph* G, int start){
	std::vector <bool> visited;
	
	int cur; int v = G.vertices;
	visited.resize(v);
    min_dist[start][start] = 0;
    priority_queue<pair<double,int>> Q;
    for(int i = 0; i < v; i++){
    	min_dist[st][i] = adj[st][i];
    	Q.enqueue({min_dist[st][i],i});
    }
    visited[start]
    while(!Q.empty()){
    	cur = Q.pop(). second ();
    	for(int i = 0; i < v; i++){
    		if(!visited[i]){
    			min_dist[start][i] = 
    				std::min(min_dist[start][i],
    		min_dist[start][cur]+
    			adj[cur][i]);
    			Q.push({min_dist[start][i], i});
    		}
    	}
    }
}
