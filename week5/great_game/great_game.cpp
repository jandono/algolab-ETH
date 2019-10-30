#include <iostream>
#include <vector>
#include <unordered_map>
#include <boost/functional/hash.hpp>

using namespace std;

int n, m, r, b, u, v;
vector<vector<int>> adj_list;
unordered_map<vector<int>, int, boost::hash<vector<int>>> memo;

void read_testcase(){

    memo.clear();

    cin >> n >> m;
    cin >> r >> b;

    adj_list = vector<vector<int>>(n);
    for(int i=0;i<m;i++){
        cin >> u >> v; u--; v--;
        adj_list[u].push_back(v);
    }
}

int moriarty(int r, int b, int step);

int holmes(int r, int b, int step){

    if(memo.count({r, b, step}))
        return memo[{r, b, step}];

    if(r == n-1){
        memo[{r, b, step}] = 1;
        return 1;
    }

    if(b == n-1){
        memo[{r, b, step}] = -1;
        return -1;
    }

    if(step % 4 == 0){
        memo[{r, b, step}] = -1;

        for(auto next_move : adj_list[r]){
            memo[{r, b, step}] = max(memo[{r,b,step}], moriarty(next_move, b, (step+1)%4));
            if(memo[{r, b, step}] == 1)
                return 1;
        }
    }else{
        memo[{r, b, step}] = -1;
        for(auto next_move : adj_list[b]){
            memo[{r, b, step}] = max(memo[{r,b,step}], moriarty(r, next_move, (step+1)%4));
            if(memo[{r, b, step}] == 1)
                return 1;
        }
    }

    return memo[{r, b, step}];
}

int moriarty(int r, int b, int step){

    if(memo.count({r, b, step}))
        return memo[{r, b, step}];

    if(r == n-1){
        memo[{r, b, step}] = 1;
        return 1;
    }

    if(b == n-1){
        memo[{r, b, step}] = -1;
        return -1;
    }

    if(step % 4 == 1){
        memo[{r, b, step}] = 1;

        for(auto next_move : adj_list[b]){
            memo[{r, b, step}] = min(memo[{r,b,step}], holmes(r, next_move, (step+1)%4));
            if(memo[{r, b, step}] == -1)
                return -1;
        }
    }else{
        memo[{r, b, step}] = 1;
        for(auto next_move : adj_list[r]){
            memo[{r, b, step}] = min(memo[{r,b,step}], holmes(next_move, b, (step+1)%4));
            if(memo[{r, b, step}] == -1)
                return -1;
        }
    }

    return memo[{r, b, step}];
}

void solve_testcase(){

    int score_holmes = holmes(r-1, b-1, 0);

    if(score_holmes > 0)
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


