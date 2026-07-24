#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<algorithm>
using namespace std;
int parent[105];
int find(int x){
    if(parent[x]==x){
        return x;
    }
    return parent[x]=find(parent[x]);
}
bool unite(int a, int b){
    a=find(a);
    b=find(b);
    if(a==b) return false;
    parent[a]=b;
    return true;
}
float dist(pair<int,int> a,pair <int,int>b){
    int dx=a.first-b.first;
    int dy=a.second-b.second;
    float ans=dx*dx+dy*dy;
    return sqrt(ans);
}
int main(){
    int S,OP;
    cin>>S>>OP;
    vector<pair<float,pair<int,int>>> edges;
    vector<pair<int,int>> points(OP);
    for(int i=0;i<OP;i++){
        int u,v;
        cin>>u>>v;
        points[i]={u,v};
    }
    for(int i=0;i<OP-1;i++){
        for(int j=i+1;j<OP;j++)
        {
            float w=dist(points[i],points[j]);
            edges.push_back({w,{i,j}});
        }
    }
    sort(edges.begin(),edges.end());
    for(int i=0;i<OP;i++){
        parent[i]=i;
    }
    float road_cost=0;
    vector<float> mst_edges;
    for(int i=0;i<edges.size();i++){
        float w=edges[i].first;
        int u=edges[i].second.first;
        int v=edges[i].second.second;
        if(unite(u,v)){
           

            mst_edges.push_back(w);

        }
    }
    sort(mst_edges.begin(),mst_edges.end(),greater<float>());
    double ans=0;
    if(S-1>=mst_edges.size()){
        cout<<0.00<<endl;
    }
    else{
        ans=mst_edges[S-1];
    }

}