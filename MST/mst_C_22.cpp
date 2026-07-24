#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int parent[1005];

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

bool isSafe(int city, vector<int> &riskyCity){
    for(int x : riskyCity){
        if(x==city){
            return false;
        }
    }
    return true;
}

int main(){

    int N,M,P;
    int K;

    cin>>N>>M>>P;
    cin>>K;

    vector<int> riskyCity(K);

    for(int i=0;i<K;i++){
        cin>>riskyCity[i];
    }

    vector<pair<int,pair<int,int>>> edges;

    for(int i=0;i<M;i++){
        int u,v,w;
        cin>>u>>v>>w;
        edges.push_back({w,{u,v}});
    }

    vector<pair<int,pair<int,int>>> safeEdges;
    vector<pair<int,pair<int,int>>> riskyEdges;

    for(auto it:edges){

        int w=it.first;
        int u=it.second.first;
        int v=it.second.second;

        int endCount=0;

        for(int i=0;i<K;i++){
            if(riskyCity[i]==u || riskyCity[i]==v){
                endCount++;
            }
        }

        int penalty=w+(P*endCount);

        if(endCount==0){
            safeEdges.push_back(it);
        }
        else{
            riskyEdges.push_back({penalty,{u,v}});
        }
    }

    for(int i=0;i<N;i++){
        parent[i]=i;
    }

    sort(safeEdges.begin(),safeEdges.end());
    sort(riskyEdges.begin(),riskyEdges.end());

    int mst_cost=0;

    // Phase 1
    for(auto it:safeEdges){

        int w=it.first;
        int u=it.second.first;
        int v=it.second.second;

        if(unite(u,v)){
            mst_cost+=w;
        }
    }

    // Check if all safe cities are connected
    int root=-1;
//finding first safe city
    for(int i=0;i<N;i++){
        if(isSafe(i,riskyCity)){
            root=find(i);
            break;
        }
    }

    bool connected=true;
//checking connection using dsu
    for(int i=0;i<N;i++){
        if(isSafe(i,riskyCity) && find(i)!=root){
            connected=false;
            break;
        }
    }

    // Phase 2
    if(!connected){

        for(auto it:riskyEdges){

            int w=it.first;
            int u=it.second.first;
            int v=it.second.second;

            if(unite(u,v)){
                mst_cost+=w;
            }
        }

        // Check again
        connected=true;

        for(int i=0;i<N;i++){
            if(isSafe(i,riskyCity) && find(i)!=root){
                connected=false;
                break;
            }
        }
    }

    if(connected){
        cout<<mst_cost<<endl;
    }
    else{
        cout<<-1<<endl;
    }

    return 0;
}