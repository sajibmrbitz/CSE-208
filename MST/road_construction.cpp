#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
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
    cin >> T;

    for(int tc=1; tc<=T; tc++){

        int m;
        cin >> m;

        map<string,int> id;
        int cnt = 0;

        vector<pair<int,pair<int,int>>> edges;

        // read all edges
        for(int i=0;i<m;i++){

            string u,v;
            int w;
            cin >> u >> v >> w;

            if(!id.count(u)) id[u] = ++cnt;
            if(!id.count(v)) id[v] = ++cnt;

            int a = id[u];
            int b = id[v];

            edges.push_back({w,{a,b}});
        }

        int n = cnt;

        // DSU init
        for(int i=1;i<=n;i++){
            parent[i]=i;
        }

        // sort edges
        sort(edges.begin(), edges.end());

        int cost = 0;
        int used = 0;

        // Kruskal MST
        for(auto &e : edges){

            int w = e.first;
            int u = e.second.first;
            int v = e.second.second;

            if(unite(u,v)){
                cost += w;
                used++;
            }
        }

        cout << "Case " << tc << ": ";

        if(used == n-1){
            cout << cost << "\n";
        }
        else{
            cout << "Impossible\n";
        }
    }

    return 0;
}