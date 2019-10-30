/*
    Sort bombs by expoding times.
    Deactivate bombs about to explode first recursively.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int T, n, t, total_time, bombs[66000];
bool deactivated[66000], fail = false;
vector< pair<int,int> > times;

void deactivate(int i){

    if(2*i + 1 < n && bombs[2*i+1] <= bombs[2*i+2]){

        if(!deactivated[2*i + 1]){
            deactivate(2*i + 1);
        }

        if(!deactivated[2*i + 2]){
            deactivate(2*i + 2);
        }
    }else
    if(2*i + 1 < n){
        if(!deactivated[2*i + 2]){
            deactivate(2*i + 2);
        }

        if(!deactivated[2*i + 1]){
            deactivate(2*i + 1);
        }
    }

    if(total_time >= bombs[i] || fail){
        fail = true;
        return;
    }

    deactivated[i] = true;
    total_time++;
}

int main()
{
    ios_base::sync_with_stdio(false);

    cin >> T;

    for(;T>0;T--){

        cin >> n;
        times.clear();
        total_time = 0;
        fail = false;

        for(int i=0;i<n;i++){
            cin >> t;
            bombs[i] = t;
            times.push_back(make_pair(t, i));
            deactivated[i] = false;
        }

        sort(times.begin(), times.end());

        for(int i=0;i<n;i++){

            if(!deactivated[times[i].second])
                deactivate(times[i].second);

            if(fail)
                break;
        }

        if(fail)
            cout << "no" << endl;
        else
            cout << "yes" << endl;
    }

    return 0;
}