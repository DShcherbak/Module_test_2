#include <iostream>
#include "Application.h"
#include "GraphNode.h"
#include "Binary_tree.h"

const int MAX_SIZE = 500;
const int TEST_SIZE = 132;
const int SORT_SIZE = 14;

std::vector <std::pair <int, std::pair <int,int>>> Task1(std::vector <Application*> &apps) {


    std::cout << "Task 1:\n";

    apps.resize(TEST_SIZE);
    for(int i = 0; i < TEST_SIZE; i++){
        apps[i] = create_random_application();

    }
    sort(apps,0,apps.size()-1);
    print(apps);

    int num_pairs = (TEST_SIZE*(TEST_SIZE-1))/2;
    std::cout << num_pairs << std::endl;
    std::vector <std::pair <int, std::pair <int,int>>> distances;
    distances.resize(num_pairs);
    int id = 0;
    for(int i = 1; i < TEST_SIZE; i++) {
        id += i - 1;
        for (int j = 0; j < TEST_SIZE; j++) {
            if (i > j)
                distances[id + j] = {distance(apps[i], apps[j]), {i, j}};
        }
    }
    std::sort(distances.begin(), distances.end());
    std::cout << "The smallest distances:\n";
    for(int i = 0; i < SORT_SIZE; i++) {
        std::cout << "{" << distances[i].first << ", (" << distances[i].second.first << ", " << distances[i].second.second << ")}\n";
    }
    std::cout << "The biggest distances:\n";
    for(int i = num_pairs-SORT_SIZE; i < num_pairs; i++) {
        std::cout << "{" << distances[i].first << ", (" << distances[i].second.first << ", " << distances[i].second.second << ")}\n";
    }

    Graph* G = new Graph(distances,TEST_SIZE,50);
    std::vector <bool> visited;
    visited.resize(TEST_SIZE,false);
    for(int i = 0; i < TEST_SIZE; i++){
        if(!visited[i])
        std::cout << i << "\n";//    dfs_component(i);
        std::cout << "\n";
    }
    return distances;
}

void Task2(){}
void Task3(){}

void Task4(std::vector <Application*> &apps, std::vector <std::pair <int, std::pair <int,int>>> distances){
    std::cout << "Task 4:\n";
    std::vector <Node*> roots = build_tree(apps);

}

int main(){
    std::vector <Application*> apps;
    std::vector <std::pair <int, std::pair <int,int>>> distances;
    distances = Task1(apps);
    Task2();
    Task3();
    Task4(apps,distances);
    return 0;
}