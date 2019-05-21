#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <queue>
#include "Application.h"

const double probability = 0.1;


struct Node{
    Application *app;
    Node *parent;
    int height, cnt_child, cnt_tree,min_mark, max_mark, sum;
    std::vector <Node*> children;

    Node(Application * _a){
        app = _a;
        height = 1;
        cnt_child = 0;
        cnt_tree = 1;
        min_mark = app->mark;
        max_mark = app->mark;
        sum = app->mark;
        parent = nullptr;
    }

    double average(){
        return 1.0*sum/cnt_tree;
    }


};

bool add_node(Node* root, Node* new_node){
    if(root == nullptr)
        return false;
    if(root == new_node->parent){
        root->children.push_back(new_node);
        if(!root->cnt_child)
            root->height = 2;
        root->cnt_child++;

        root->min_mark = std::min(root->min_mark,new_node->min_mark);
        root->max_mark = std::max(root->max_mark,new_node->max_mark);
        root->sum += new_node->sum;
        root->cnt_tree++;
    }
    else{
        for(auto ch : root->children){
            root->sum -= ch->sum;
            if(add_node(ch,new_node)){
                root->sum += ch->sum;
                root->height = std::max(root->height,1+ch->height);
                root->min_mark = std::min(root->min_mark,ch->min_mark);
                root->max_mark = std::max(root->max_mark,ch->max_mark);
                root->cnt_tree++;
                break;
            }
            root->sum += ch->sum;
        }
    }
        return (add_node(root->left,new_node) | add_node(root->right,new_node));

}

std::vector <Node*> build_tree(std::vector <Application*> apps){
    std::vector <Node*> roots;
    int n = apps.size()
    for(int i = 0; i <n; i++){
        Node* new_node = new Node(apps[i]);
        if(apps[i]->prototype == nullptr)
            roots.push_back(new_node);
        else{
            for(int i = 0, k = roots.size(); i < k; i++){
                if(add_node(roots[i],new_node))
                    break;
            }
        }
    }
    return roots;
}

void swap_trees(Node* a, Node* b){
    if(!a->parent && !b->parent){
        swap(a,b);
        return;
    }
    Node* pa, *pb;
    pa = a->parent;
    pb = b->parent;
}

void swap_min_max_trees(Node* root){
    Node* min_tree = find_min_tree(root);
    Node* max_tree = find_max_tree(root);
    swap_trees(min_tree, max_tree);

}
/*
std::vector <Node*> build_tree(std::vector <Application*> apps, std::vector <std::pair <int, std::pair <int,int>>> distances){
    std::vector <Node*> root;

    int n = distances.size();
    std::cout << "Size: " << n << std::endl;
    for(int i = 0; i <n; i++){
        std::pair <int, std::pair <int,int>> p = distances[i];
        Node* new_node = new Node(apps[p.second.first],apps[p.second.second],p.first);
        if(root.size() < 0 || randomInt(1,1000)*0.1/100.0 < probability) {
            std::cout << "&" << i << std::endl;
            root.push_back(new_node);
        }
        else{
            std::cout << "^" << i << std::endl;
            int par = randomInt(0,root.size()-1);
            add_node(root[i],new_node);
        }
    }
    return root;

}
*/
/*
int create_new_node(std::vector <Node*> root, Application* a, Application* b){
    Node* new_node = new Node(a,b,distance(a,b));
    if(randomInt(1,1000)*0.1/100.0 < probability)
        root.push_back(new_node);
    else{
        int par = randomInt(0,root.size()-1);
        add_node(root[par],new_node);
    }
}
*/
void print_node_right(Node* root){
    std::cout << root->dist << " ";
    for(auto ch:root->children)
        print_node_right(ch);
}

void print_tree_right(std::vector <Node*> roots){
    int n = roots.size();
    for(int i = 0; i < n; i++){
        print_node_right(roots[i]);
    }
}

void print_tree(Binary_Node *root, int depth = 0) {
    if (!root)
        return;
    std::cout << '|';
    for (int i = 0; i < depth; i++)
        std::cout << '\t' << '|';
    std::cout << root->dist << std::endl;
    for(auto ch : root->children)
        print_tree(ch,depth+1);

}

int depth(Node* root){
    if(root == nullptr)
        return 0;
    if(root->children.size() == 0){
        return 1;
    }
    int maxDep = -1;
    for(auto ch : root->children)
        maxDep = std::max(maxDep,depth(ch));
    return 1+maxDep;
}

void delete_node_by_value(Node* root, int val){
    if(root->dist == val){
        if(root->parent == nullptr) {
            root->right->parent = root->left;
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

