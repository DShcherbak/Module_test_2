#include <iostream>
#include <vector>
#include <cmath>

const int VARIANT = 3;

int power(int a, int b){
    if(b ==  0)
        return 1;
    if(b == 1)
        return a;
    int c = power(a,b/2)*power(a,b/2);
    if(b%2 == 0)
        return c
    return a*c;

}

class Application {
    std::string name;
    Application* prototype;
    vector <pair <std::string,int>> functionality; // SIZE LESS THAN 7
    double ar = 1.0;
    double mark;

    Application(std::string n, Application* p, vector <pair <std::string,int>> f, double a){
        name = n;
        prototype = p;
        functionality = f;
        sort(functionality.begin(),functionality.end());
        ar = a;
        int mrk = 0;
        for(int i = 0, k = functionality.size(); i < k; i++){
            mrk += power((functionality[i].second),2);
        }
        mark = power(mrk, VARIANT+(int)(ar / 2));

    }
};

double distance(Application a, Application b){
    if(a.functionality.size() < b.functionality.size())
        swap(a,b);
    int i = 0, sum = 0;
    for(;i < b.functionality.size(); i++){
        sum += power((a.functionality[i] - b.functionality[i]),2);
    }
    for(;i < a.functionality.size(); i++){
        sum += power(a.functionality[i],2);
    }
    return pow(sum,ar/5-3*VARIANT);
}



