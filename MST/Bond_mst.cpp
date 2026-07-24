#include<iostream>
#include<vector>
#include<queue>
#include<cmath>
#include<algorithm>
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
    int n,m;
    cin>>n>>m;
    vector<pair<int,pair<int,int>>> edges(m+1);
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges[i]={w,{u,v}};
    }


int Q;
cin>>Q;
vector<pair<int,int>> st;
for(int i=1;i<=Q;i++){
int s,t;
cin>>s>>t;
st.push_back({s,t});
}


for(int i=1;i<=n;i++){
    parent[i]=i;
}
sort(edges.begin()+1,edges.end());
int mst_ans=0;
vector<pair<int,int>>  adj[1005];

for(int i=1;i<=m;i++){
    int w=edges[i].first;
    int u=edges[i].second.first;
    int v=edges[i].second.second;
    if(unite(u,v)){
        mst_ans+=w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
}
for(int i=0;i<Q;i++){
vector<bool> visited(n+1,false);
int s=st[i].first;
int t=st[i].second;

queue<pair<int,int>> q; //node,current max
q.push({s,0});
visited[s]=true;
while (!q.empty())
{
    auto cur=q.front();
    q.pop();
    int u=cur.first;
    int mx=cur.second;
    if(u==t){
        cout<<mx<<"\n";
        break;
    }
    for(auto it: adj[u]){
        int v=it.first;
        int w= it.second;
        if(!visited[v]){
            visited[v]=true;
            q.push({v,max(w,mx)});
        }
    }
}



}
}
