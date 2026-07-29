#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios::sync_with_stdio(false); cin.tie(nullptr);
#define ll long long
#define nl '\n'
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define YES cout<<"YES\n"
#define NO  cout<<"NO\n"

int edmondsKarp(int n,vector<vector<int>>& capacity,vector<vector<int>>& adj){

    int source=0, sink=n-1;
    int maxflow=0;

    while(1){
    
        vector<int> parent(n,-1);
        queue<int> bfsq;

        bfsq.push(source);
        parent[source]=-2;

        while(!bfsq.empty()){

            int curr=bfsq.front();
            bfsq.pop();

            for(int next:adj[curr]){
                if(parent[next]==-1 && capacity[curr][next]>0){
                    parent[next]=curr;
                    if(next==sink) break;
                    bfsq.push(next);
                }
            }
        }

        if(parent[sink]==-1) break;     // sink unreachable

        int pathflow=INT_MAX;
        int currentNode=sink;

        while(currentNode!=source){

            int prevNode=parent[currentNode];
            pathflow=min(pathflow,capacity[prevNode][currentNode]);
            currentNode=prevNode;

        }

        currentNode=sink;
        while(currentNode!=source){

            int prevNode=parent[currentNode];
            capacity[prevNode][currentNode]-=pathflow;
            capacity[currentNode][prevNode]+=pathflow;

            currentNode=prevNode;

        }

        maxflow+=pathflow;
    }

    return maxflow;
}



int main() {

    FAST_IO

    int n,m;
    cin>>n>>m;

    vector<vector<int>> capacity(n, vector<int>(n));
    vector<vector<int>> adj(n);

    for(int i=0;i<m;i++){

        int u,v,w;
        cin>>u>>v>>w;

        capacity[u][v]+=w;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    cout<<edmondsKarp(n,capacity,adj)<<nl;

    return 0;
}