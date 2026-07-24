#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<algorithm>
using namespace std;
int parent[1005];
int find(int x){
    if(parent[x]==x)
    return x;
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
    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>> edges;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({w,{u,v}});
    }
    sort(edges.begin(),edges.end());
    for(int i=0;i<n;i++){
        parent[i]=i;
    }
    vector<int> ans;

    for(int i=0;i<m;i++){
        int w=edges[i].first;
        int u=edges[i].second.first;
        int v=edges[i].second.second;

        if(!unite(u,v)){
            ans.push_back(w);
        }
    }
    for(auto p:ans){
        cout<<p<<" ";
    }

}