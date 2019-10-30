/*
    Modified Dijkstra such that: 
        distances[i][j] = distance to vertex i encountering j waters on the way.
        visited[{u, {v, w}}] = amount of times we have visited the u-v edge with weight w.
*/

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <climits>

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, pair<int, int> > iii;

vector<ii> adj_list[10001];
map<iii, bool> water_along_edge;
map<iii, int> edge_visited;
map<int,int> distances[10001];

int n, m, k, s, t, u, v, w, d, dist_to_u, k_w;

void dijkstra(int s){
    priority_queue< iii, vector<iii>, greater<iii> > q;

    q.push({0,{s,0}});
    while(!q.empty()){
        pair<int, pair<int,int> > curr = q.top();
        dist_to_u = curr.first;
        u = curr.second.first;
        k_w = curr.second.second;
        q.pop();

        if(u == t && k_w >= k)
            break;

        for(auto neighbor : adj_list[u]){
            v = neighbor.first;
            w = neighbor.second;
            int water = water_along_edge[{u, {v, w}}];

            if(edge_visited[{u,{v, w}}]>=k+1)
                continue;

            if(!distances[v].count(k_w + water)){
                distances[v][k_w + water] = INT_MAX;
            }

            if(distances[v][k_w+water] > dist_to_u + w){
                distances[v][k_w+water] = dist_to_u + w;
                q.push({distances[v][k_w+water], {v, k_w + water}});
                edge_visited[{u,{v,w}}]++;
            }
        }
    }

    int mini_dist = INT_MAX;
    for(auto el: distances[t]){
        int k_w = el.first;
        int dist = el.second;

        if(k_w >= k && dist < mini_dist){
            mini_dist = dist;
        }
    }

    cout << mini_dist << endl;
}

void test_case(){

    cin >> n >> m >> k >> s >> t;

    for(int i=0;i<n;i++){
        adj_list[i].clear();
        distances[i].clear();
    }
    water_along_edge.clear();
    edge_visited.clear();

    for(int i=0;i<m;i++){
        cin >> u >> v >> w >> d;

        adj_list[u].push_back({v, w});
        adj_list[v].push_back({u, w});
        if(d){
            water_along_edge[{u, {v, w}}] = 1;
            water_along_edge[{v, {u, w}}] = 1;
        }else{
            water_along_edge[{u, {v, w}}]  = 0;
            water_along_edge[{v, {u, w}}] = 0;
        }
        edge_visited[{u,{v,w}}] = 0;
        edge_visited[{v,{u,w}}] = 0;
    }

    distances[s][0] = 0;
    dijkstra(s);
}

int main()
{
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--){test_case();}

    return 0;
}