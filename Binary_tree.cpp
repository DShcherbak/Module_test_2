#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <queue>
#include "Application.h"

const double probability = 0.1;


struct Node{
    Application *a, *b;
    double dist;
    Node* left, *right, *parent;



    Node(Application * _a, Application * _b, double _d){
        a = _a;
        b = _b;
        dist = _d;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    bool operator <(Node* a){
        return a->dist < this->dist;
    }
};

void add_node(Node* cur, Node* new_node){
    if(cur < new_node){
        if(cur->right)
            add_node(cur->right,new_node);
        else{
            cur->right = new_node;
            new_node->parent = cur;
        }
    }
    else{
        if(cur->left)
            add_node(cur->left,new_node);
        else{
            cur->left = new_node;
            new_node->parent = cur;
        }
    }

}

std::vector <Node*> build_tree(std::vector <Application*> apps){
    std::vector <Node*> root;

    int n = apps.size();
    for(int i = 0; i <n; i++){
        for(int j = 0; j < n; j++){
            if(i==j)
                continue;
            Node* new_node = new Node(apps[i],apps[j],distance(apps[i],apps[j]));
            if(randomInt(1,1000)*0.1/100.0 < probability)
                root.push_back(new_node);
            else{
                int par = randomInt(0,root.size()-1);
                add_node(root[par],new_node);
            }
        }
    }
}

std::vector <Node*> build_tree(std::vector <Application*> apps, std::vector <std::pair <int, std::pair <int,int>>> distances){
    std::vector <Node*> root;

    int n = distances.size();
    for(int i = 0; i <n; i++){
        std::pair <int, std::pair <int,int>> p = distances[i];
        Node* new_node = new Node(apps[p.second.first],apps[p.second.second],p.first);
        if(randomInt(1,1000)*0.1/100.0 < probability)
            root.push_back(new_node);
        else{
            int par = randomInt(0,root.size()-1);
            add_node(root[i],new_node);
        }
    }
}

int create_new_node(std::vector <Node*> root, Application* a, Application* b){
    Node* new_node = new Node(a,b,distance(a,b));
    if(randomInt(1,1000)*0.1/100.0 < probability)
        root.push_back(new_node);
    else{
        int par = randomInt(0,root.size()-1);
        add_node(root[par],new_node);
    }
}

void print_node_right(Node* cur){
    std::cout << cur->dist << " ";
    if(cur->left)
        print_node_right(cur->left);
    if(cur->right)
        print_node_right(cur->right);
}

void print_tree_right(std::vector <Node*> roots){
    int n = roots.size();
    for(int i = 0; i < n; i++){
        print_node_right(roots[i]);
    }
}

int depth(Node* cur){
    if(cur == nullptr)
        return 0;
    if(cur->left == nullptr && cur->right == nullptr){
        return 1;
    }
    return 1+std::max(depth(cur->left),depth(cur->right));
}

void delete_node_by_value(Node* cur, int val){
    if(cur->dist == val){
        if(cur->parent == nullptr) {
            cur->right->parent = cur->left;
        }
    }
}

void delete_root_by_value(Node* root, int val){
    if(root->dist == val){
        //delete
    }
    else if(root->dist < val)
        delete_node_by_value(root->left,val);
    else
        delete_node_by_value(root->right,val);
}


/*
void print_node_tree(Node* cur, int d, int right){

}

void print_as_tree(std::vector <Node*> roots){
    int n = roots.size();
    std::queue <std::pair <Node*, int> Q;
    for(int i = 0; i < n; i++){

    }
}
*/

