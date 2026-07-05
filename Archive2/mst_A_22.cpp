#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int main(){
int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int>>> adj(n+1);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    vector<bool> vis(n+1,false);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    int ans=0;
    pq.push({0,1});
    while(!pq.empty()){
        auto pair=pq.top();
        int wt=pair.first;
        int u=pair.second;
        pq.pop();
        if(vis[u]) continue;
        vis[u]=true;
        ans*=wt;
        for(auto it:adj[u]){
            int v=it.first;
            int wt=it.second;
            if(!vis[v]){
                pq.push({wt,v});
            }
        }
    }



}