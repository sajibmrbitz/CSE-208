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
    int N;
    cin>>N;
    int old_cost=0;
    for(int i=0;i<N-1;i++){
        int u,v,w;
        cin>>u>>v>>w;
        old_cost+=w;
    }
    int K;
    cin>>K;
    vector<pair<int,pair<int,int>>> new_edges;
    for(int i=0;i<K;i++){
        int u,v,w;
        cin>>u>>v>>w;
        new_edges.push_back({w,{u,v}});
    }
    int M;
    cin>>M;

    vector<pair<int,pair<int,int>>> org_edges;
    for(int i=0;i<M;i++){
        int u,v,w;
        cin>>u>>v>>w;
        org_edges.push_back({w,{u,v}});
    }
    vector<pair<int,pair<int,int>>> edges;
    for(auto e:org_edges){
        edges.push_back(e);
    }
    for(auto e:new_edges){
        edges.push_back(e);
    }
    sort(edges.begin(),edges.end());
    for(int i=1;i<=N;i++){
        parent[i]=i;
    }
    int new_ans=0;
    for(auto it:edges){
        int w=it.first;
        int u=it.second.first;
        int v=it.second.second;
        if(unite(u,v)){
            new_ans+=w;
        }
    }
    cout<<old_cost<<" "<<new_ans;

}