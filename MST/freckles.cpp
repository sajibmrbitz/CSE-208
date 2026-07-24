#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<iomanip>
using namespace std;

int parent[105];

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

    int T;
    cin>>T;

    while(T--){

        int n;
        cin>>n;

        vector<pair<double,double>> points;

        for(int i=0;i<n;i++){
            double x,y;
            cin>>x>>y;
            points.push_back({x,y});
        }

        // {weight,{u,v}}
        vector<pair<double,pair<int,int>>> edges;

        // Generate all possible edges
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){

                double dx = points[i].first - points[j].first;
                double dy = points[i].second - points[j].second;

                double dist = sqrt(dx*dx + dy*dy);

                edges.push_back({dist,{i,j}});
            }
        }

        sort(edges.begin(),edges.end());

        for(int i=0;i<n;i++){
            parent[i]=i;
        }

        double ans=0.0;

        for(auto e:edges){

            double w=e.first;
            int u=e.second.first;
            int v=e.second.second;

            if(unite(u,v)){
                ans+=w;
            }
        }

        cout<<fixed<<setprecision(2)<<ans<<"\n";

        if(T) cout<<"\n";
    }

    return 0;
}