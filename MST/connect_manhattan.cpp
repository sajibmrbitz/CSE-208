#include<iostream>
#include<vector>
#include<queue>
using namespace std;
int main(){
    int N;
    cin>>N;
    vector<pair<int,int>> points(N);
    for(int i=0;i<N;i++){
        int x,y;
        cin>>x>>y;
        points[i]={x,y};

    }
    vector<int> dist(N,INT_MAX);
    vector<bool> visited(N,false);
    dist[0]=0;
    int ans=0;
    
    priority_queue<pair<int,int>,
                   vector<pair<int,int>>,
                   greater<pair<int,int>>> pq;
    pq.push({0,0}) ;//weigght , source               
    while(!pq.empty()){
        auto cur=pq.top();
        pq.pop();
        int cost=cur.first;
        int u=cur.second;
        if(visited[u]) continue;
        visited[u]=true;
        ans+=cost;
        for(int v=0;v<N;v++){
            if(!visited[v]){
                int w = abs(points[u].first - points[v].first)
                      + abs(points[u].second - points[v].second);
                pq.push({w,v});
                }


        }
    }
    cout<<ans<<endl;
    
}