/*
    2 x One dimensional DPs.
    DP[i] is tracking with how many moves can I obtain the pattern x everywhere
    DP_FLIPPED[i] is tracking with how many moves can I obtain the pattern x_flipped everywhere
    Two functions for working with bits:
        dist(x, y) = number of different bits between X and Y
        flip(x) = flips the bits of an integer considering it of size K. K is global.
*/

#include <iostream>
#include <vector>

using namespace std;

int n, k, x, x_flipped, m, bit;

vector<int> patches, patches_flipped;

int dist(int x, int y){

    if(x == 0 && y==0)
        return 0;

    return ((x & 1) != (y & 1)) + dist(x>>1, y>>1);
}

int flip(int x){

    int mask = (1 << k) - 1;

    return x ^ mask;
}

void read_testcase(){

    patches.clear();

    cin >> n >> k >> x;
    x_flipped = flip(x);

    m = n / k;
    for(int i=0;i<m;i++){

        int bit_segment = 0;
        for(int j=0;j<k;j++){

            cin >> bit;
            bit_segment += (bit << (k - j - 1));
        }

        patches.push_back(bit_segment);
    }
}

void solve(){

    int dp[m], dp_flipped[m];

    dp[0] = min(dist(patches[0], x), dist(patches[0], x_flipped) + 1);
    dp_flipped[0] = min(dist(patches[0], x_flipped), dist(patches[0], x) + 1);

    for(int i=1;i<m;i++){

        dp[i] = min(dp[i-1] + dist(patches[i], x), dp_flipped[i-1] + dist(patches[i], x_flipped) + 1);
        dp_flipped[i] = min(dp_flipped[i-1] + dist(patches[i], x_flipped), dp[i-1] + dist(patches[i], x) + 1);
    }

    cout << dp[m-1] << endl;
}

void testcase(){

    read_testcase();
    solve();
}

int main(){

    ios_base::sync_with_stdio(true);

    int T;
    cin >> T;
    while(T--) testcase();

    return 0;
}
