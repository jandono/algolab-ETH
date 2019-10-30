/*
    Keep track of potential bikers, and whenever a new one arrives,
    check if he blocks some of the previous bikers.
    If so remove those bikers from the potentials list.
    If the new bikers is not blocked by anyone add him to the potentials list.
*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <tuple>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef pair<long long, long long> ll;
// typedef tuple<long long, K::Ray_2, int> t;
typedef tuple<long long, ll, int> t;

long long n, y, x2, y2, comp_i, comp_j;
K::Ray_2 rr;
t rays[500001];
K::FT slopes[500001];
vector<int> potentials;

bool compare(const t &left, const t &right){
    return get<0>(left) > get<0>(right);
}

void read_test_case(){
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> y >> x2 >> y2;
        get<0>(rays[i]) = y;
        //get<1>(rays[i]) = K::Ray_2(K::Point_2(0, y), K::Point_2(x2, y2));
        get<1>(rays[i]) = {x2, y2};
        get<2>(rays[i]) = i;
    }

    sort(rays, rays+n, compare);

    for(int i=0;i<n;i++){
        long long x1_ray1 = 0;
        long long y1_ray1 = get<0>(rays[i]);
        long long x2_ray1 = get<1>(rays[i]).first;
        long long y2_ray1 = get<1>(rays[i]).second;
        slopes[i] = K::FT(y1_ray1-y2_ray1) / K::FT(x1_ray1-x2_ray1);

        //rr = get<1>(rays[i]);
        //slopes[i] = rr.direction().dy() / rr.direction().dx();
    }
}

int check(int comp_i, int comp_j){

    K::FT k_i = slopes[comp_i];
    K::FT k_j = slopes[comp_j];

    if(k_i >= k_j){
        return 0; //do not intersect both are potentials
    }else{
        if(k_i >= 0){
            return 1; //comp_i is potential, comp_j is blocked
        }else{
            if(k_j<=0){
                return 2; //comp_j is potential, comp_i is blocked
            }else{
                if(k_i <= -k_j){
                    return 2; //comp_j is potential, comp_i is blocked
                }else{
                    return 1; //comp_i is potential, comp_j is blocked
                }
            }
        }
    }
}

void test_case(){
    potentials.clear();
    read_test_case();

    comp_i = 0;
    potentials.push_back(comp_i);
    comp_j = 1;
    while(comp_j<n){

        // check if comp_i and comp_j intersect if they do check which one survives
        int option = check(comp_i, comp_j);
        if(option == 0){ //both are potential
            potentials.push_back(comp_j);
            comp_i = comp_j;
        }else
        if(option == 2){ //comp_j is potential, remove all that would be blocked 
            bool flag = true;
            while(potentials.size()>0){

                comp_i = potentials[potentials.size()-1];
                option = check(comp_i, comp_j);

                if(option == 0){
                    break;
                }else
                if(option == 1){
                    flag = false;
                    break;
                }else{
                    potentials.pop_back();
                }
            }

            if(flag){
                potentials.push_back(comp_j);
                comp_i = comp_j;
            }
        }
        comp_j++;
    }

    set<int> solution;
    for(auto index : potentials){
        solution.insert(get<2>(rays[index]));
    }

    for(auto el : solution){
        cout << el << " ";
    }
    cout << endl;
}

int main()
{
    ios_base::sync_with_stdio(false);

    int T;
    cin >> T;
    while(T--) test_case();
    return 0;
}