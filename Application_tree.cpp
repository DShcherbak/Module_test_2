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
    int height, cnt_child, cnt_tree;
    double min_mark, max_mark, sum;
    std::vector <Node*> children;

    Node(Application * _a){
        app = _a;
        height = 1;
        cnt_child = 0;
        cnt_tree = 1;
        min_mark = app->mark;
        max_mark = app->mark;
        sum = app->mark;
    }

    double average(){
        return 1.0*sum/cnt_tree;
    }


};

bool add_node_to_root(Node* root, Node* new_node){
    bool result = false;
    if(root == nullptr)
        return false;
 //   std::cout << root->app->mark << " * " << new_node->parent->app->mark << std::endl;
 if(root->app == new_node->app->prototype){
        new_node->parent = root;
        root->children.push_back(new_node);
        root->height = std::max(root->height,1+new_node->height);
        root->cnt_child++;
        root->min_mark = std::min(root->min_mark,new_node->min_mark);
        root->max_mark = std::max(root->max_mark,new_node->max_mark);
        root->sum += new_node->sum;
        root->cnt_tree++;
        return true;
    }
    else{
        for(auto ch : root->children){
            root->sum -= ch->sum;
            if(add_node_to_root(ch,new_node)){
                result = true;
                root->sum += ch->sum;
                root->height = std::max(root->height,1+ch->height);
                root->min_mark = std::min(root->min_mark,ch->min_mark);
                root->max_mark = std::max(root->max_mark,ch->max_mark);
                root->cnt_tree++;
                return true;
            }
            root->sum += ch->sum;
        }
    }
        return false;
}

std::vector <Node*> build_tree(std::vector <Application*> apps){
    std::vector <Node*> roots;
    int n = apps.size();
    for(int i = 0; i <n; i++){
        Node* new_node = new Node(apps[i]);
        if(apps[i]->prototype == nullptr)
            roots.push_back(new_node);
        else{
            for(int i = 0, k = roots.size(); i < k; i++){
                if(add_node_to_root(roots[i],new_node))
                    break;
            }
        }
    }
    return roots;
}

void add_app_to_tree(std::vector <Node*> &roots, Application* app){
    Node* new_node = new Node(app);
    if(new_node->parent == nullptr){
        roots.push_back(new_node);
        return;
    }
    for(auto root : roots)
        if(add_node_to_root(root,new_node))
            return;
}

Node* find_min_tree(Node* root, int level){
   // std::cout << root->max_mark << " with " << level << std::endl;
    Node* res = nullptr;
    Node* temp;
    if(level == 0)
        return root;
    for(auto ch : root->children){
        temp = find_min_tree(ch,level-1);
        if(temp == nullptr)
            continue;
        if(res == nullptr || temp->max_mark < res->max_mark)
            res = temp;
    }
    return res;
}

Node* find_max_tree(Node* root, int level){
    Node* res = nullptr;
    Node* temp;
    if(level == 0)
        return root;
    for(auto ch : root->children){
        temp = find_max_tree(ch,level-1);
        if(temp == nullptr)
            continue;
        if(res == nullptr || temp->min_mark > res->min_mark)
            res = temp;
    }
    return res;
}

void global_recount(Node* root){
    for(auto ch : root->children)
        global_recount(ch);
    root->sum = root->app->mark;
    root->cnt_tree = 1;
    root->min_mark = root->sum;
    root->max_mark = root->sum;
    root->height = 1;
    for(auto ch : root->children){
        root->sum += ch->sum;
        root->cnt_tree += ch->cnt_tree;
        root->min_mark = std::min(root->min_mark,ch->min_mark);
        root->max_mark = std::max(root->max_mark,ch->max_mark);
        root->height = std::max(root->height,ch->height+1);
    }
}

void swap_trees(Node* a, Node* b){
    if(!a->parent && !b->parent){
        std::swap(a,b);
        return;
    }
    Node* pa = a->parent;
    Node* pb = b->parent;
    pa->sum -= a->sum;
    pb->sum -= b->sum;
    for(int i = 0; i < pa->cnt_child; i++)
        if (pa->children[i] == a) {
            pa->children[i] = b;
            break;
        }
    for(int i = 0; i < pb->cnt_child; i++)
        if (pb->children[i] == b) {
            pb->children[i] = a;
            break;
        }
    a->parent = pb;
    b->parent = pa;
}

void swap_min_max_trees(Node* root, int level){
    Node* min_tree = find_min_tree(root,level);
    Node* max_tree = find_max_tree(root,level);
    //std::cout << "Hello!" << std::endl;
    if(min_tree == max_tree){
        std::cout << "The min-max tree and max-min tree are the same tree for this level.\n Try again later or try another level.\n";
        return;
    }
    std::cout << "Min-max tree: " << min_tree->app->mark << "\n";
    std::cout << "Max-min tree: " << max_tree->app->mark << "\n";
    swap_trees(min_tree, max_tree);
    global_recount(root);
    std::cout << "Swaping done!\n";
}

void print_node_right(Node* root){
    std::cout << root->app->mark << " ";
    for(auto ch:root->children)
        print_node_right(ch);
}

void print_tree_right(std::vector <Node*> roots){
    int n = roots.size();
    for(int i = 0; i < n; i++){
        print_node_right(roots[i]);
    }
}

void print_node(Node* root, int type){
    switch(type){
        case 0:
            std::cout << root->app->mark << std::endl;
            return;
        case 1:
            std::cout << root->min_mark << std::endl;
            return;
        case 2:
            std::cout << root->max_mark << std::endl;
            return;
        case 3:
            std::cout << root->height << std::endl;
            return;
        case 4:
            std::cout << root->cnt_tree << std::endl;
            return;
        case 5:
            std::cout << (1.0*root->sum)/(1.0*root->cnt_tree) << std::endl;
            return;
    }
}

void print_tree(Node *root,int type = 0,  int depth = 0) {
    if (!root)
        return;
    std::cout << '|';
    for (int i = 0; i < depth; i++)
        std::cout << '\t' << '|';
    print_node(root,type);
    for(auto ch : root->children)
        print_tree(ch,type,depth+1);

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


