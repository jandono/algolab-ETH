/*
    Instead of doing a classical min-max approach, calculate the smallest amount of steps for holmes to win.
    Then calculate smallest amount of steps for Moriarty to win.
    Then compare these results.
*/

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int n, m, r, b, u, v;
vector<vector<int>> adj_list;
vector<int> best, worst;

void read_testcase(){

    cin >> n >> m;
    cin >> r >> b; r--; b--;

    adj_list = vector<vector<int>>(n);
    best = vector<int>(n, INT_MAX);
    worst = vector<int>(n, INT_MIN);

    for(int i=0;i<m;i++){
        cin >> u >> v; u--; v--;
        adj_list[u].push_back(v);
    }
}

int maxi(int pos);

int mini(int pos){

    if(best[pos] != INT_MAX)
        return best[pos];

    if(pos == n-1){
        best[pos] = 0;
        return 0;
    }

    for(auto next_move : adj_list[pos]){
        best[pos] = min(best[pos], 1 + maxi(next_move));
    }

    return best[pos];
}

int maxi(int pos){

    if(worst[pos] != INT_MIN)
        return worst[pos];

    if(pos == n-1){
        worst[pos] = 0;
        return 0;
    }

    for(auto next_move : adj_list[pos]){
        worst[pos] = max(worst[pos], 1 + mini(next_move));
    }

    return worst[pos];
}

void solve_testcase(){

    int score_h = mini(r);
    int score_m = mini(b);

    if(score_h < score_m || (score_h == score_m && score_h % 2 == 1))
        cout << 0 << endl;
    else
        cout << 1 << endl;
}

void testcase(){
    read_testcase();
    solve_testcase();
}

int main(){
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) testcase();

    return 0;
}
