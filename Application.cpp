#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

const int VARIANT = 3;


int randomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);

}

int power(int a, int b){
    if(b ==  0)
        return 1;
    if(b == 1)
        return a;
    int c = power(a,b/2)*power(a,b/2);
    if(b%2 == 0)
        return c;
    return a*c;

}

class Application {
public:
    static int CNT_APPS;
    std::string name;
    Application* prototype;
    std::vector <std::pair <std::string,int>> functionality; // SIZE LESS THAN 7
    double ar = 1.0;
    double mark;

    Application(std::string n, Application* p, std::vector <std::pair <std::string,int>> f, double a){
        name = n;
        prototype = p;
        functionality = f;
        std::sort(functionality.begin(),functionality.end());
        ar = a;
        int mrk = 0;
        for(int i = 0, k = functionality.size(); i < k; i++){
            mrk += power((functionality[i].second),2);
        }
        mark = power(mrk, VARIANT+(int)(ar / 2));
        CNT_APPS++;
    }
};

int Application::CNT_APPS = 0;

Application* create_random_application(){
    std::string n = "RandomNodeNumber" + std::to_string(Application::CNT_APPS);
    Application* p = nullptr;
    std::vector <std::pair <std::string, int> > f;
    int size = randomInt(1,7);
    for(int i = 0; i < size; i++){
        std::pair <std::string, int> p;
        p.first = "app" ;
        p.first += (char)('Z' -randomInt(0,25));
        p.first += (char)('Z' - randomInt(0,25));
     //   std::cout << "-" << p.first << "-\n";

        p.second = randomInt(1,100);
        f.push_back(p);
    }
    double a = randomInt(1,5000)*1.0/1000.0;
    return new Application(n,p,f,a);
}

double distance(Application* a, Application* b){
    if(a->functionality.size() < b->functionality.size())
        std::swap(a,b);
    int i = 0;
    double sum = 0.1;
    for(;i < b->functionality.size(); i++){
        sum += power((a->functionality[i].second - b->functionality[i].second),2);
    }
    for(;i < a->functionality.size(); i++){
        sum += power(a->functionality[i].second,2);
    }
    double p = std::min(a->ar,b->ar)/5.0-3*VARIANT;
    double res = pow((double)sum,p);
    return -log(res);
}

double distance(Application a, Application b){
    if(a.functionality.size() < b.functionality.size())
        std::swap(a,b);
    int i = 0, sum = 0;
    for(;i < b.functionality.size(); i++){
        sum += power((a.functionality[i].second - b.functionality[i].second),2);
    }
    for(;i < a.functionality.size(); i++){
        sum += power(a.functionality[i].second,2);
    }
    return pow(sum,std::min(a.ar,b.ar)/5-3*VARIANT);
}

bool operator < (Application a, Application b){
    return a.ar < b.ar;
}

std::ostream& operator<<(std::ostream& os, Application* &p)
{
    os << "--------------------------------------\n{\n";
    os << "Name: " << p->name << "\n";
    os << "Mark: " << p->mark << "\n";
    os << "Prototype: " << (p->prototype ? p->prototype->name : "No prototype.")  << "\n";
    os << "Rating: " << p->ar << "\n";
    os << "Functionality: \n";
    for(auto i : p->functionality){
        os << " - " << i.first << " : " << i.second << "\n";
    }
    os << "}\n";
    return os;
}

void merge(std::vector <Application*> &a, int l1, int r1, int l2, int r2){
    std::vector<Application*> b;
    int p1 = r1, p2 = r2;
    int cnt = r2-l1+1;
    b.resize(cnt--);
    while(cnt >= 0){
        if(p2 < l2)
            b[cnt--] = a[p1--];
        else if(p1 < l1)
            b[cnt--] = a[p2--];
        else if (a[p1]->mark > a[p2]->mark)
            b[cnt--] = a[p1--];
        else
            b[cnt--] = a[p2--];
    }

    for(int i = 0; i <= r2-l1; i++)
        a[l1+i] = b[i];
}

void sort(std::vector <Application*> &a, int left, int right){
    if(left >= right) return;
    int middle = (left+right)>>1;
    sort(a,left,middle);
    sort(a,middle+1,right);
    merge(a,left,middle,middle+1,right);
}

void print(std::vector <Application*> apps){
    for(auto a : apps){
        std::cout << a << std::endl;
    }
}





