#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int main(){
    int N;
    cin>>N;
    vector<vector<pair<int,int>>> adj(N+1);

    for(int i=0;i<N;i++){
        int x;
        cin>>x;
        adj[0].push_back({i,x});
        adj[i].push_back({0,x});
        
    }
    int M;
    cin>>M;
    for(int i=0;i<M;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({i,w});
        adj[v].push_back({u,w});
    }
    vector<bool> vis (N+1,false);
    priority_queue<pair<int,int>,
vector<pair<int,int>>,greater<pair<int,int>>> pq;
    int ans=0;
    pq.push({0,0});
    while(!pq.empty()){
        auto pair=pq.top();
        pq.pop();
        int wt=pair.first;
        int u=pair.second;
        if(vis[u]) continue;
        vis[u]=true;
        ans+=wt;
        for(auto it: adj[u]){
            int v,wt;
            v=it.first;
            wt=it.second;
            if(!vis[v]){
                pq.push({wt,v});
            }
        }
    }
    cout<<ans<<endl;
}