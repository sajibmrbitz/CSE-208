#include<iostream>
#include <list>
#include<vector>
#include<queue>

using namespace std;

int MST_prims(int V,vector<vector<pair<int,int>>> adj){
    vector<bool> inMSTset(V,false);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    int mstCost=0;
    pq.push({0,0});
    while(pq.size()>0){
        auto pair=pq.top();
        int wt=pair.first;
        int u=pair.second;
        pq.pop();
        if(!inMSTset[u]){
            inMSTset[u]=true;
            mstCost+=wt;
            for(int i=0;i<adj[u].size();i++){
                int v=adj[u][i].first;
                int w=adj[u][i].second;
                pq.push({w,v});
            }
        }
    }
    return mstCost;

}
int main(){
    int V=4;
    

    vector<vector<pair<int,int>>> adj(V); //pair for edge weight
    adj[0].push_back({1, 10});
    adj[1].push_back({0, 10});

    adj[0].push_back({3,30});
    adj[3].push_back({0,30});

    adj[0].push_back({2,15});
    adj[2].push_back({0,15});

    adj[1].push_back({3,40});
    adj[3].push_back({1,40});


    adj[2].push_back({3,50});
    adj[3].push_back({2,50});

    cout<<"cost of mst is = "<<MST_prims(V,adj)<<endl;

    




}
