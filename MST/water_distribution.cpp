#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
int parent [1005];
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
int main(){
    int N;
    cin>>N;
    vector<pair<int,pair<int,int>>> edges;
    for(int i=0;i<N;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({w,{u,v}});
    }
    for(int i=1;i<=N;i++){
        int u;
        cin>>u;
        edges.push_back({u,{0,i}});
    }
    sort(edges.begin(),edges.end());
    for(int i=0;i<=N;i++){
        parent[i]=i;
    }
    int mst_cost=0;
    int cnt=0;
    for(int i=0;i<edges.size();i++){
        int w=edges[i].first;
        int u=edges[i].second.first;
        int v=edges[i].second.second;
        if(unite(u,v)){
            mst_cost+=w;
            cnt++;
        }
    }
    if(cnt==N) cout<<"mst cost"<<mst_cost<<endl;
    else cout<<"impossible"<<endl;
    return 0;
}
