#include<iostream>
#include<vector>
#include<algorithm>
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
int dist(pair<int,int> a,pair<int,int> b){
    return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);

}
int main(){
    int cases;
    cin>>cases;
    static int case_num=1;
    while(cases--){
        int p_num,threshold;
        cin>>p_num>>threshold;
        vector<pair<int,int>> points (p_num);
        for(int i=0;i<p_num;i++){
            int x,y;
            cin>>x>>y;
            points[i]={x,y};
        }
        int r2=threshold*threshold;
        for(int i=0;i<p_num;i++){
            parent[i]=i;
        }
        for(int i=0;i<p_num;i++){
            for(int j=i+1;j<p_num;j++){
                if(dist(points[i],points[j])<=r2){
                    unite(i,j);
                }
            }
        }
        int states=0;
        for(int i=0;i<p_num;i++){
            if(find(i)==i){
                states++;
            }
        }
        vector<pair<int,pair<int,int>>> edges;
        for(int i=0;i<p_num;i++){
            for(int j=i+1;j<p_num;j++){
                int d=dist(points[i],points[j]);
                edges.push_back({d,{i,j}});
            }
        }
        sort(edges.begin(),edges.end());
        for(int i=0;i<p_num;i++){
            parent[i]=i;
        }
        int road=0,rail=0;
        for(int i=0;i<edges.size();i++){
            int d=edges[i].first;
            int u=edges[i].second.first;
            int v=edges[i].second.second;
            if(unite(u,v)){
                if(d<=r2){
                    road+=sqrt(d);
                }else{
                    rail+=sqrt(d);
                }
            }

        }
        cout<<"Case #"<<case_num++<<": "<<states<<" "<<road<<" "<<rail<<endl;

        


    }
    return 0;
}