#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int parent[105];

int find(int x){
    if(parent[x]==x){
        return x;
    }
    return parent[x]=find(parent[x]);
}
bool unite(int a,int b){
    a=find(a);
    b=find(b);
    if(a==b) return false;
    parent[a]=b;
    return true;
}

int main(){
    int N,M,A;
    cin>>N>>M>>A;
    vector<pair<int,pair<int,int>> > edges;
    for(int i=0;i<M;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({w,{u,v}});
    }
    sort(edges.begin(),edges.end());
    for(int i=1;i<=N;i++){
        parent[i]=i;
    }
    int road_cost=0;
    int components=N;
    for(int i=0;i<M;i++){
        int w=edges[i].first;
        int u=edges[i].second.first;
        int v=edges[i].second.second;
        if(w>=A) continue;

        if(unite(u,v)){
            road_cost+=w;
            components--;
        }
    }
    int total_cost=road_cost+components*A;
    cout<<total_cost<<" "<<components<<endl;
    return 0;

}