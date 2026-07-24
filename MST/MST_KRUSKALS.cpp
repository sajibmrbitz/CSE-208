#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
using namespace std;
class DSU{
    vector<int> parent;
    public:
    DSU(int n){
        parent.resize(n);
        for(int i=0;i<n;i++){
            parent[i]=i;
        }
    }
    int find(int x){
        if(parent[x]==x){
            return x;

        }
        return parent[x]=find(parent [x]);
    }
    void unite(int x,int y){
        int px=find(x);
        int py=find(y);
        if(px!=py){
            parent [py]=px;
        }
    }

};
class Edge{
public:
    int u, v, w;
    Edge() = default;
    Edge(int uu, int vv, int ww) : u(uu), v(vv), w(ww) {}
    bool operator<(const Edge &other) const { return w < other.w; }
};
int KRUSKAL(int V,vector<Edge> & edges){
    sort(edges.begin(),edges.end());
    DSU dsu(V);
    int mstCost=0;
    int edgesUsed=0;
    for(const auto& edge:edges){
        int u=edge.u;
        int v=edge.v;
        int w=edge.w;
        if(dsu.find(u)!=dsu.find(v)){
            dsu.unite(u,v);
            mstCost+=w;
            edgesUsed++;
            if(edgesUsed== V-1) break;
        }
    }
    return mstCost;
}
int main(){
    int V=4;
        vector<Edge> edges;

    edges.push_back({0,1,10});
    edges.push_back({0,3,30});
    edges.push_back({0,2,15});
    edges.push_back({1,3,40});
    edges.push_back({2,3,50});

    cout << "Cost of MST kruskal= "
         << KRUSKAL(V, edges)
         << endl;
}