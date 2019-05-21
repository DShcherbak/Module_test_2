#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <queue>
#include "Application.h"
#define edge std::pair <int, std::pair <int,int>>
#define from second.first
#define to second.second
#define cost first

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
  //  std::cout << "Adding to " << cur->dist << std::endl;
    if(cur == nullptr){
        cur = new_node;
        return;
    }
    if(cur->dist < new_node->dist){
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

void random_shuffle(std::vector <edge> &e) {
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(e.begin(), e.end(), g);
}

Node* build_tree(std::vector <Application*> apps){
    int n = apps.size();
    std::cout << n << " elements.\n";
    Node* root = new Node(apps[1],apps[0],distance(apps[1],apps[0]));
    for(int i = 2; i < n; i++){
        for(int j = 0; j < i; j++){
            Node* new_node = new Node(apps[i],apps[j],distance(apps[i],apps[j]));
            add_node(root,new_node);
        }
    }
    return root;
}


Node* build_tree(std::vector <Application*> apps, std::vector <edge> distances){
    int n = distances.size();
    random_shuffle(distances);
    edge p = distances[0];
    Node* root = new Node(apps[p.from],apps[p.to],p.cost);
    for(int i = 1; i <n; i++){
        p = distances[i];
        Node* new_node = new Node(apps[p.from],apps[p.to],p.cost);
        add_node(root,new_node);
    }
    return root;

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


void print_tree(Node *root, int level = 0) {
    if (!level) std::cout << "Tree:" << std::endl;
    if (root != nullptr) {
        std::cout << '|';
        for (int i = 0; i < level; i++)
            std::cout << '\t' << '|';
        std::cout << root->dist << std::endl;
            print_tree(root->left, level + 1);
            print_tree(root->right, level + 1);
    }
}


