#include<bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back

const ll INF=4e18;

/*=========================================================
    QUICK DECISION GUIDE - read this first during the test

    1. read n,m -> always call initFloyd first
    2. read edges -> addDirectedEdge+addEdge, or the
       undirected versions if problem says undirected
    3. match the problem statement:
         "negative weights", small n           -> floydWarshall
         negative weights + need the path       -> floydWarshallPath
         "non negative weights", large n        -> repeatedDijkstra
         "detect negative cycle"                -> hasNegativeCycle (after floyd)
         "print all pairs distances"            -> printMatrix
    4. for each query, match the wording:
         "shortest distance between s and d"    -> dist[s][d]
         "print the path" / "print the route"   -> getPath + printPath
         "is d reachable from s"                -> hasPath
         "must pass through vertex x"           -> viaNode
         "must pass through A or B"             -> viaTwoNodes
=========================================================*/

// STEP 1, always run first: resets dist to INF and nxt to -1, sets dist[i][i]=0
void initFloyd(int n,vector<vector<ll>> &dist,vector<vector<int>> &nxt){
    dist.assign(n+1,vector<ll>(n+1,INF));
    nxt.assign(n+1,vector<int>(n+1,-1));
    for(int i=1;i<=n;i++){
        dist[i][i]=0;
        nxt[i][i]=i;
    }
}

// STEP 2 (directed graph): call once per edge while reading input, feeds the floyd matrix
void addDirectedEdge(int u,int v,ll w,vector<vector<ll>> &dist,vector<vector<int>> &nxt){
    if(w<dist[u][v]){
        dist[u][v]=w;
        nxt[u][v]=v;
    }
}

// STEP 2 (undirected graph): swap in for addDirectedEdge if problem says undirected
void addUndirectedEdge(int u,int v,ll w,vector<vector<ll>> &dist,vector<vector<int>> &nxt){
    addDirectedEdge(u,v,w,dist,nxt);
    addDirectedEdge(v,u,w,dist,nxt);
}

// STEP 2 (directed graph): call once per edge while reading input, feeds the dijkstra adjacency list
void addEdge(int u,int v,ll w,vector<vector<pair<int,ll>>> &adj){
    adj[u].pb({v,w});
}

// STEP 2 (undirected graph): swap in for addEdge if problem says undirected
void addUndirectedAdjEdge(int u,int v,ll w,vector<vector<pair<int,ll>>> &adj){
    adj[u].pb({v,w});
    adj[v].pb({u,w});
}

// STEP 3, if problem allows negative weights and just wants distances: run once after reading all edges
void floydWarshall(int n,vector<vector<ll>> &dist){
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(dist[i][k]==INF||dist[k][j]==INF) continue;
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
}

// STEP 3, if problem allows negative weights AND wants the actual path printed: run this instead of floydWarshall
void floydWarshallPath(int n,vector<vector<ll>> &dist,vector<vector<int>> &nxt){
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                if(dist[i][k]==INF||dist[k][j]==INF) continue;
                if(dist[i][j]>dist[i][k]+dist[k][j]){
                    dist[i][j]=dist[i][k]+dist[k][j];
                    nxt[i][j]=nxt[i][k];
                }
            }
}

// STEP 3, if weights are all non negative and n is too big for floyd's n^3: run this instead, needs adj built with addEdge
vector<ll> dijkstra(int n,vector<vector<pair<int,ll>>> &adj,int src){
    vector<ll> dist(n+1,INF);
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    dist[src]=0;
    pq.push({0,src});
    while(!pq.empty()){
        pair<ll,int> top=pq.top();
        pq.pop();
        ll d=top.first;
        int u=top.second;
        if(d!=dist[u]) continue;
        for(int idx=0;idx<(int)adj[u].size();idx++){
            int v=adj[u][idx].first;
            ll w=adj[u][idx].second;
            if(dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                pq.push({dist[v],v});
            }
        }
    }
    return dist;
}

// wrapper that runs dijkstra from every vertex, call this one directly, not the single source version above
vector<vector<ll>> repeatedDijkstra(int n,vector<vector<pair<int,ll>>> &adj){
    vector<vector<ll>> ans(n+1,vector<ll>(n+1));
    for(int i=1;i<=n;i++) ans[i]=dijkstra(n,adj,i);
    return ans;
}

// STEP 3, if problem says "detect negative cycle": call after floydWarshall/floydWarshallPath, prints nothing itself
bool hasNegativeCycle(int n,vector<vector<ll>> &dist){
    for(int i=1;i<=n;i++)
        if(dist[i][i]<0) return true;
    return false;
}

// STEP 3, if problem wants the full distance table shown: call after floyd/dijkstra has filled dist
void printMatrix(int n,vector<vector<ll>> &dist){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(dist[i][j]==INF) cout<<"INF ";
            else cout<<dist[i][j]<<" ";
        }
        cout<<'\n';
    }
}

// STEP 4, per query, if problem says "is d reachable from s"
bool hasPath(int u,int v,vector<vector<ll>> &dist){
    return dist[u][v]!=INF;
}

// STEP 4, per query, if problem says "print the path/route from s to d": needs floydWarshallPath run first
vector<int> getPath(int src,int dest,vector<vector<int>> &nxt){
    if(nxt[src][dest]==-1) return {};
    vector<int> path;
    while(src!=dest){
        path.pb(src);
        src=nxt[src][dest];
    }
    path.pb(dest);
    return path;
}

// STEP 4, prints whatever getPath returned, call right after it
void printPath(vector<int> &path){
    if(path.empty()){
        cout<<"NO PATH\n";
        return;
    }
    for(int x:path) cout<<x<<" ";
    cout<<'\n';
}

// STEP 4, per query, if problem says the path from s to d must pass through a given vertex x
ll viaNode(int s,int x,int d,vector<vector<ll>> &dist){
    if(dist[s][x]==INF||dist[x][d]==INF) return INF;
    return dist[s][x]+dist[x][d];
}

// STEP 4, per query, if problem says the path from s to d must pass through A or through B (whichever is cheaper)
pair<ll,int> viaTwoNodes(int s,int d,int A,int B,vector<vector<ll>> &dist){
    ll da=viaNode(s,A,d,dist);
    ll db=viaNode(s,B,d,dist);
    if(da==INF&&db==INF) return {INF,-1};
    if(da<=db) return {da,A};
    return {db,B};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,m;
    cin>>n>>m;

    // STEP 1: reset the tables before touching any edges
    vector<vector<ll>> dist;
    vector<vector<int>> nxt;
    initFloyd(n,dist,nxt);

    vector<vector<pair<int,ll>>> adj(n+1);

    // STEP 2: read all m edges, pick directed or undirected based on the problem statement
    for(int i=0;i<m;i++){
        int u,v;
        ll w;
        cin>>u>>v>>w;

        // default: directed graph, keep this if problem doesn't say undirected
        addDirectedEdge(u,v,w,dist,nxt);
        addEdge(u,v,w,adj);

        // if problem says undirected: comment out the two lines above, uncomment these two
        // addUndirectedEdge(u,v,w,dist,nxt);
        // addUndirectedAdjEdge(u,v,w,adj);
    }

    // STEP 3: uncomment exactly the one algorithm the problem needs, see decision guide at top of file
    // floydWarshall(n,dist);
    // floydWarshallPath(n,dist,nxt);
    // auto allDist=repeatedDijkstra(n,adj);

    // STEP 3b: only if problem explicitly asks to detect a negative cycle, run after floyd
    // if(hasNegativeCycle(n,dist))
    //     cout<<"NEGATIVE CYCLE\n";

    // STEP 3c: only if problem wants the full distance table printed
    // printMatrix(n,dist);

    //==================================================
    // STEP 4: only if problem gives multiple (s,d) queries, uncomment the block matching what's asked
    //==================================================

    /*
    int q;
    cin>>q;

    while(q--){
        int s,d;
        cin>>s>>d;

        // "shortest distance from s to d"
        // cout<<dist[s][d]<<'\n';

        // "print the path from s to d" (needs floydWarshallPath in step 3)
        // printPath(getPath(s,d,nxt));

        // "is d reachable from s"
        // cout<<hasPath(s,d,dist)<<'\n';

        // "path must pass through vertex x"
        // int x;
        // cin>>x;
        // cout<<viaNode(s,x,d,dist)<<'\n';

        // "path must pass through A or B"
        // int A,B;
        // cin>>A>>B;
        // auto ans=viaTwoNodes(s,d,A,B,dist);
        // cout<<ans.first<<" "<<ans.second<<'\n';
    }
    */

    return 0;
}