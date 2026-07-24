#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int parent[1005];

int find(int x){
    if(parent[x]==x) return x;
    return parent[x]=find(parent[x]);
}

bool unite(int a,int b){
    a=find(a);
    b=find(b);
    if(a==b) return false;
    parent[a]=b;
    return true;
}

double dist(pair<int,int> a, pair<int,int> b){
    double dx = a.first - b.first;
    double dy = a.second - b.second;
    return sqrt(dx*dx + dy*dy);
}

int main(){
    int n;
    double r;
    cin >> n >> r;

    vector<pair<int,int>> city(n);

    for(int i=0;i<n;i++){
        cin >> city[i].first >> city[i].second;
    }

    vector<pair<double,pair<int,int>>> edges;

    // build complete graph
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            double d = dist(city[i], city[j]);
            edges.push_back({d,{i,j}});
        }
    }

    sort(edges.begin(), edges.end());

    for(int i=0;i<n;i++) parent[i]=i;

    double road = 0, rail = 0;
    int states = 1;

    for(auto &e : edges){
        double w = e.first;
        int u = e.second.first;
        int v = e.second.second;

        if(unite(u,v)){
            if(w <= r){
                road += w;
            }else{
                rail += w;
                states++;
            }
        }
    }

    cout << states << " "
         << (long long)round(road) << " "
         << (long long)round(rail);

    return 0;
}