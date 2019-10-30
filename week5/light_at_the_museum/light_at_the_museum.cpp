/*
    Regular split and list.
    Keep map of vectors.
*/

#include <iostream>
#include <climits>
#include <boost/functional/hash.hpp>
#include <unordered_map>

using namespace std;

int n, m;
long target[30], config[30][30][2];
unordered_map<vector<int>, int, boost::hash<vector<int>>> split_map;

void read_testcase(){

    split_map.clear();

    cin >> n >> m;
    for(int i=0;i<m;i++){
        cin >> target[i];
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> config[i][j][0] >> config[i][j][1];
        }
    }
}

int count_bits(int x){

    if(!x)
        return 0;

    return (x & 1) + count_bits(x >> 1);
}


void solve_testcase(){

    int half = n/2;
    int limit = 1 << half;

    int best = INT_MAX;

    for(int l=0;l<limit;l++){
        vector<int> map_entry(m, 0);
        for(int j=0;j<m;j++){
            for(int i=0;i<half;i++){
                map_entry[j] += config[i][j][(bool)(l & (1 << i))];
            }
        }

        if(split_map.count(map_entry))
            split_map[map_entry] = min(count_bits(l), split_map[map_entry]);
        else
            split_map[map_entry] = count_bits(l);
    }

    limit = 1 << (n - half);
    for(int l=0;l<limit;l++){
        vector<int> map_entry(m, 0);

        for(int j=0;j<m;j++){
            for(int i=0;i<n-half;i++){
                map_entry[j] += config[half + i][j][(bool)(l & (1 << i))];
            }

            map_entry[j] = target[j] - map_entry[j];
        }

        if(split_map.count(map_entry))
            best = min(best, count_bits(l) + split_map[map_entry]);
    }

    if(best == INT_MAX)
        cout << "impossible" << endl;
    else
        cout << best << endl;
}

void testcase(){
    read_testcase();
    solve_testcase();
}

int main(){
    ios_base::sync_with_stdio(true);

    int T;
    cin >> T;
    while(T--) testcase();

    return 0;
}
