/*
	Create an edge between two students only if they share more characteristics
	than the minimum number of common characteristics over all pairs of buddies
	in Dr. Fuzzman's solution.
	Try edmunds maximum cardinality matching. 
	If it succeeds output "not optimal", else output "optimal".
*/

#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <set>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
								no_property,
								no_property> Graph;

typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef graph_traits<Graph>::edge_descriptor Edge;

map <string, int> char_to_index;
map <int, string> index_to_char;
set<int> characterestics[401], connected;
string characterestic;
int n, c, f;
bool success;
Edge e; 
Graph g;

void init_test_case(){
	for(int i=0;i<n;i++)
		characterestics[i].clear();
	index_to_char.clear();
	char_to_index.clear();
	connected.clear();
}

void read_and_build_graph(){

	cin >> n >> c >> f;
	int index = 0;
	for(int i=0;i<n;i++){
		for(int j=0;j<c;j++){

			cin >> characterestic;
			if(!char_to_index.count(characterestic)){
				char_to_index[characterestic] = index;
				index_to_char[index] = characterestic;
				index++;
			}
			characterestics[i].insert(char_to_index[characterestic]);
		}
	}

	g = Graph(n);
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			int w = 0;
			for(auto c : characterestics[i]){
				if(characterestics[j].count(c)){
					w++;
					if(w > f)
						break;
				}
			}

			if(w > f){
				connected.insert(i);
				connected.insert(j);
				tie(e, success) = add_edge(i, j, g);
			}
		}
	}

	success = connected.size() == n;
}

void test_case(){

	init_test_case();
	read_and_build_graph();

	if(!success){
		cout << "optimal" << endl;
		return;
	}

	vector<Vertex> mate(n);
	edmonds_maximum_cardinality_matching(
		g,
		make_iterator_property_map(mate.begin(), get(vertex_index, g))
	);

	for(int i=0;i<n;i++){
		if(mate[i] == graph_traits<Graph>::null_vertex()){
			success = false;
			break;
		}
	}

	if(success)
		cout << "not optimal" << endl;
	else 
		cout << "optimal" << endl;
}


int main(){
	ios_base::sync_with_stdio(false);

	int T;
	cin >> T;
	while(T--) test_case();

	return 0;
}