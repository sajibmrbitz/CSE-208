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

        while(true){
            string u,v;
            int w;
            cin >> u >> v >> w;

            if(u=="0" && v=="0" && w==0) break;

            if(!id.count(u)) id[u] = ++cnt;
            if(!id.count(v)) id[v] = ++cnt;

            int a = id[u];
            int b = id[v];

            edges.push_back({w,{a,b}});
        }

        int n = cnt;

        // ---------- MINIMUM SPANNING TREE ----------
        for(int i=1;i<=n;i++) parent[i]=i;

        sort(edges.begin(), edges.end());

        int minCost = 0;
        int used = 0;

        for(auto e : edges){

            int w = e.first;
            int u = e.second.first;
            int v = e.second.second;

            if(unite(u,v)){
                minCost += w;
                used++;
            }
        }

        // ---------- MAXIMUM SPANNING TREE ----------
        for(int i=1;i<=n;i++) parent[i]=i;

        sort(edges.rbegin(), edges.rend());

        int maxCost = 0;
        used = 0;

        for(auto e : edges){

            int w = e.first;
            int u = e.second.first;
            int v = e.second.second;

            if(unite(u,v)){
                maxCost += w;
                used++;
            }
        }

        // ---------- OUTPUT ----------
        cout << "Case " << tc << ": ";

        if(used != n-1){
            cout << "Impossible\n";
        }
        else{
            int p = minCost + maxCost;
            int q = 2;


            if(q == 1) cout << p << "\n";
            else cout << p << "/" << q << "\n";
        }
    }

    return 0;
}