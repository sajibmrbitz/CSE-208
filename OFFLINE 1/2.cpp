#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios::sync_with_stdio(false); cin.tie(nullptr);
#define ll long long
#define nl '\n'
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define YES cout<<"YES\n"
#define NO  cout<<"NO\n"


class Flight{

public:                             // to avoid setter-getters
    string flightID;
    string departureCity;
    string arrivalCity;
    int departureTime;
    int arrivalTime;

    Flight(){}

    Flight(string id,string from,string to,int departure,int arrival){
        this->flightID=id;
        this->departureCity=from;
        this->arrivalCity=to;
        this->departureTime=departure;
        this->arrivalTime=arrival;
    }
};

int convertTime(string time){      // hh:mm format

    int hours=stoi(time.substr(0,2));
    int minutes=stoi(time.substr(3,2));

    return hours*60+minutes;
}

bool canConnect(Flight& f1, Flight&f2){
    return f1.arrivalCity==f2.departureCity && f1.arrivalTime+180<=f2.departureTime;
}

void buildFlowNetwork(vector<Flight>& flights,vector<vector<int>>& capacity,vector<vector<int>>& adjacencyList){

    int flightCount=flights.size();

    int source=0;
    int sink=2*flightCount+1;

    for(int i=0;i<flightCount;i++){

        int leftNode=i+1;
        int rightNode=i+flightCount+1;

        capacity[source][leftNode]=1;
        adjacencyList[source].pb(leftNode);
        adjacencyList[leftNode].pb(source);

        capacity[rightNode][sink]=1;
        adjacencyList[rightNode].pb(sink);
        adjacencyList[sink].pb(rightNode);
    }

    for(int i=0;i<flightCount;i++){
        for(int j=0;j<flightCount;j++){

            if(i==j) continue;

            if(canConnect(flights[i],flights[j])){

                int leftNode=i+1;
                int rightNode=j+flightCount+1;

                capacity[leftNode][rightNode]=1;

                adjacencyList[leftNode].pb(rightNode);
                adjacencyList[rightNode].pb(leftNode);
            }
        }
    }
}

void reconstructRoutes(vector<Flight>& flights, vector<vector<int>>& capacity){

    int flightCount=flights.size();

    vector<int> nextFlight(flightCount,-1);
    vector<int> previousFlight(flightCount,-1);

    for(int i=0;i<flightCount;i++){

        int leftNode=i+1;

        for(int j=0;j<flightCount;j++){

            int rightNode=j+flightCount+1;

            if(capacity[rightNode][leftNode]>0){

                nextFlight[i]=j;
                previousFlight[j]=i;
            }
        }
    }

    int aircraftNumber=1;

    for(int i=0;i<flightCount;i++){

        if(previousFlight[i]!=-1) continue;

        cout<<"Aircraft "<<aircraftNumber++<<": ";

        int currentFlight=i;

        while(currentFlight!=-1){

            cout<<flights[currentFlight].flightID;

            currentFlight=nextFlight[currentFlight];

            if(currentFlight!=-1)
                cout<<" -> ";
        }

        cout<<nl;
    }
}


int edmondsKarp(int n,vector<vector<int>>& capacity,vector<vector<int>>& adj){

    int source=0, sink=n-1;
    int maxflow=0;

    while(1){
    
        vector<int> parent(n,-1);
        queue<int> bfsq;

        bfsq.push(source);
        parent[source]=-2;

        while(!bfsq.empty()){

            int curr=bfsq.front();
            bfsq.pop();

            for(int next:adj[curr]){
                if(parent[next]==-1 && capacity[curr][next]>0){
                    parent[next]=curr;
                    if(next==sink) break;
                    bfsq.push(next);
                }
            }
        }

        if(parent[sink]==-1) break;     // sink unreachable

        int pathflow=INT_MAX;
        int currentNode=sink;

        while(currentNode!=source){

            int prevNode=parent[currentNode];
            pathflow=min(pathflow,capacity[prevNode][currentNode]);
            currentNode=prevNode;

        }

        currentNode=sink;
        while(currentNode!=source){

            int prevNode=parent[currentNode];
            capacity[prevNode][currentNode]-=pathflow;
            capacity[currentNode][prevNode]+=pathflow;

            currentNode=prevNode;

        }

        maxflow+=pathflow;
    }

    return maxflow;
}

int main(){

    FAST_IO

    int flightCount;
    cin>>flightCount;

    vector<Flight> flights;

    for(int i=0;i<flightCount;i++){

        string id,from,to,departure,arrival;

        cin>>id>>from>>to>>departure>>arrival;
        flights.pb(Flight(id,from,to,convertTime(departure),convertTime(arrival)));
    }

    int totalNodes=2*flightCount+2;   // source+sink
    vector<vector<int>> capacity(totalNodes, vector<int>(totalNodes, 0));
    vector<vector<int>> adj(totalNodes);

    buildFlowNetwork(flights,capacity,adj);
    int maxFlow=edmondsKarp(totalNodes,capacity,adj);

    cout<<"Number of Aircraft:"<<flightCount-maxFlow<<nl;
    reconstructRoutes(flights,capacity);

    return 0;
}