#include <iostream>
#include "Application.h"
#include "Application_tree.h"
#include "GraphNode.h"
#include "Binary_tree.h"

const int MAX_SIZE = 500;
const int TEST_SIZE = 132;
const int SORT_SIZE = 14;

void  Task1() {
    std::vector <Application*> apps;

    std::cout << "Task 1:\n";
    double pos;
    apps.resize(TEST_SIZE);
    int father = -1;
    apps[0] = create_random_application();
    for(int i = 1; i < TEST_SIZE; i++){
        apps[i] = create_random_application();
        pos = randomInt(0,1000)*0.001;
        if(pos > probability){
            father = randomInt(0,i-1);
            apps[i]->prototype = apps[father];
        }
       // std::cout << "Debug." << std::endl;

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

}

void Task2() {
    std::vector<Application *> apps;
    std::vector<Node *> roots;
    std::cout << "Task 2:\n";
    int n = 40, father;
    double pos;
    apps.resize(n);
    apps[0] = create_random_application();
    for (int i = 1; i < n; i++) {
        apps[i] = create_random_application();
        pos = randomInt(0, 1000) * 0.001;
        if (pos > probability) {
            father = randomInt(0, i - 1);
            apps[i]->prototype = apps[father];
        }
    }
    roots = build_tree(apps);
    std::cout << "Now the random tree is generated and build, you may see it:\n";
    for (auto root : roots)
        print_tree(root);
    std::cout << "Also random nodes can be generated and added to the tree.\n";
    Application *new_app = create_random_application();
    pos = randomInt(0, 1000) * 0.001;
    if (pos > probability) {
        father = randomInt(0, n - 1);
        new_app->prototype = apps[father];
    }

    add_app_to_tree(roots, new_app);

    apps.push_back(new_app);
    n++;
    int type = 0;
    while(type != 9) {

        std::cout << "You can also see some specific trees:\n";
        std::cout << "Please, enter:\n";
        std::cout << "1 - to get a tree of values\n";
        std::cout << "2 - to get a tree of minimums\n";
        std::cout << "3 - to get a tree of maximums\n";
        std::cout << "4 - to get a tree of heights\n";
        std::cout << "5 - to get a tree of numbers of elements in subtree\n";
        std::cout << "6 - to get a tree of maximums\n";
        std::cout << "0 - to call a special function\n";
        std::cout << "9 - to exit.\n";
        std::cin >> type;
        if(type == 9) {
            break;
        }
        else if(type == 0){
            int level;
            int rt;
            std::cout << "And now let's see the most interesting function: \n";
            std::cout << "Enter the level of trees and the progra will exchange \n";
            std::cout << "The tree with the maximum value of minimum and\n";
            std::cout << "The tree with the minimum value of maximum\n";
            std::cout << "Your level:";
            std::cin >> level;
            std::cout << "You should also enter number of root in tree:";
            std::cin >> rt;
            swap_min_max_trees(roots[rt], level);
        }else if (type < 7 && type > 0){
            for (auto root : roots)
                print_tree(root, type-1);
        }


    }
}

void Task3(){
    std::vector <Application*> apps;
    std::cout << "Task 3:\n";
    int V = 40; // NUMBER OF VERTICES
    apps.resize(V);
    for(int i = 0; i < V; i++){
        apps[i] = create_random_application();
    }
    std::cout << "For this task I will need threshold value - \n";
    std::cout << "maximum distance between a and b, with which\n";
    std::cout << "vertexes and b will be connected with an edge\n";
    std::cout << "(You are free to choose this value, but I \nstrongly recommend values in [86;89])\n";
    std::cout << "Threshold:";

    double threshold;
    std::cin >> threshold;
    Graph* G = new Graph(apps,threshold);
    print(G);
    std::cout << "Graph's components:\n";
    std::vector <bool> visited;
    visited.resize(V,false);
    int cnt_component = 0;
    for(int i = 0; i < V; i++)
        if(!visited[i]){
            dfs_component(G,i,visited);
            std::cout << "\n";
            cnt_component++;
        }
    std::cout << "Number of components: " << cnt_component << "\n";
    std::cout << "Enter number of vertex which will be a start for a Dijkstra algorithm:\n";
    int start;
    std::cin >> start;
    Dijkstra(G,start);
    std::cout << "Distances from start to :\n";
    for(int i = 0; i < V; i++){
        if(G->min_dist[start][i] == inf)
            std::cout << i << ": Different components.\n";
        else
            std::cout << i << ": " << G->min_dist[start][i] << "\n";
    }
}

void Task4(){
    std::vector <Application*> apps;
    std::cout << "Task 4:\n";
    int n = 10; // NUMBER OF PAIRS WILL BE n*n-1/2 = 45;
    apps.resize(n);
    for(int i = 0; i < n; i++){
        apps[i] = create_random_application();
    }
    sort(apps,0,n-1);
   // print(apps);
    Binary_Node* root = build_binary_tree(apps);
    int dep = depth(root);
    std::cout << "Done. Depth is " << dep << "\n";
    print_tree(root);
    std::cout << "Now that you have seen the tree, we can search for values in it.\n";
    std::cout << "Enter the value that is looked for:";
    double val, eps;
    std::cin >> val;
    std::cout << "Enter the precision:";
    std::cin >> eps;
    std::cout << "Values in [" << val-eps << ", " << val+eps << "]:\n";
    std::vector <double> src = search_precision_vec(root,val-eps,val+eps);
    sort(src.begin(),src.end());
    for(double d : src)
        std::cout << "(" << d << ")\n";
    std::cout << "Thanks for your attention! :) \n";

}

int main(){
    Task1();
    Task2();
    Task3();
    Task4();
    return 0;
}