#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int parent[105];
int find(int x){
    if(parent[x]==x){
        return x;
    }
    return parent[x]=find(parent[x]);
}
bool unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    parent[a] = b;
    return true;
}
int kruskal(int n,vector<pair<int,pair<int,int>>> &edges,int skip,bool & ok){
    for(int i=1;i<=n;i++){
        parent[i]=i;
    }
    int ans=0;
    int cnt=0;
    for(int i=0;i<edges.size();i++){
        if(i==skip) continue;
        int w=edges[i].first;
        int u=edges[i].second.first;
        int v=edges[i].second.second;
        if(unite(u,v)){
            ans+=w;
            cnt++;
        }
    }
    ok=(cnt == n-1);
    return ans;
}


int main(){
    int inputs;
    cin>>inputs;
    static int case_num=1;
    while(inputs--){
        int V,E;
        cin>>V>>E;
        vector<pair<int,pair<int,int>>> edges;
        for(int i=0;i<E;i++){
            int u,v,w;
            cin>>u>>v>>w;
            edges.push_back({w,{u,v}});

    }
    sort(edges.begin(),edges.end());
    bool ok;
    int mst=kruskal(V,edges,-1,ok);
    cout<<"case #"<<case_num++<<": ";
    if(!ok){
        cout<<"No way"<<endl;
        continue;
    }
    int second=INT_MAX;
    bool found=false;
    for(int i=0;i<E;i++){
        bool valid;
        int cost=kruskal(V,edges,i,valid);
        if(valid && cost>mst){
            found=true;
            second=min(second,cost);
        }
    }
    if(!found){
        cout<<"No second way"<<endl;
    }else{
        cout<<second<<endl;
    }
    
}
return 0;
}