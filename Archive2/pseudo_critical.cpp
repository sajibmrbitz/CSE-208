#include<iostream>
#include<vector>
#include <algorithm>
#include<climits>
using namespace std;
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int parent[205];

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
    vector<vector<int>> edges;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({u,v,w,i});
    }
    sort(edges.begin(),edges.end(),[](vector<int> &a,vector<int> &b){
        return a[2]<b[2];
    });
    for(int i=0;i<n;i++){
        parent[i]=i;
    }
    int mstCost=0;
    int used=0;
    for(auto e:edges){
        int u=e[0];
        int v=e[1];
        int w=e[2];
        if(unite(u,v)){
            mstCost+=w;
            used++;
        }
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            parent[j]=j;
        }
        int cst=0,cnt=0;
        for(int j=0;j<m;j++){
            if(j==i) continue;
            int u=edges[j][0];
        }
    }
}