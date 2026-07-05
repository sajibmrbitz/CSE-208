#include<iostream>
#include<vector>
#include<queue>
using namespace std;
vector<int> parent;
int find(int x){
    if(parent[x]==x){
        return x;

    }
    return parent[x]=find(parent [x]);
}
bool Union(int x,int y){
    int px=find(x);
    int py=find(y);
    if(px!=py){
        parent [py]=px;
        return true;
    }
    return false;
}
int main(){
    int N;
    cin>>N;
    vector<pair<int,int>> X,Y,Z;
    for(int i=0;i<N;i++){
        int x,y,z;
        cin>>x>>y>>z;
        X.push_back({x,i});
        Y.push_back({y,i});
        Z.push_back({z,i});

    }
    sort(X.begin(),X.end());
    sort(Y.begin(), Y.end());
    sort(Z.begin(), Z.end());

    vector<tuple<int,int,int>> edges;
    for(int i=0;i<N-1;i++){
        edges.push_back({X[i+1].first-X[i].first,
                        X[i].second,X[i+1].second});

         edges.push_back({
            Y[i + 1].first - Y[i].first,
            Y[i].second,
            Y[i + 1].second
        });

        edges.push_back({
            Z[i + 1].first - Z[i].first,
            Z[i].second,
            Z[i + 1].second
        });
    }
    sort(edges.begin(),edges.end());
    parent.resize(N);
    for(int i=0;i<N;i++){
        parent [i]=i;
    }
    int ans=0;
    for(auto [w,v,u]:edges){
        
    if(Union(u,v)){
        ans+=w;
    }
        
    }
    cout<<ans<<endl;





}