#include <iostream>
#include <vector>
#include <map>

using namespace std;

int k, n, q, a[10], b[10], r;
map<vector<int>, int> experiments;

void test_case(){
	experiments.clear();

	cin >> k >> n >> q;

	for(int i=0;i<k;i++){
		cin >> a[i] >> b[i];
	}

	for(int i=0;i<n;i++){
		vector<int> params(k);
		for(int j=0;j<k;j++){
			cin >> params[j];
		}
		cin >> r;
		experiments[params] = r;
	}

	for(int i=0;i<q;i++){
		vector<int> params(k);
		for(int j=0;j<k;j++){
			cin >> params[j];
		}

		if(experiments.count(params))
			cout << experiments[params] << endl;
		else
			cout << -1 << endl;
	}
}

int main(){

	int T;
	cin >> T;
	while(T--) test_case();
	return 0;
}
