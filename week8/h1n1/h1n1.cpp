/*
	Using the Delaunay Triangulation build a graph where each face is a vertex
	plus one vertex for all infinite faces.
	Then the edges in the graph correspond to the edges between faces in the delaunay.

	From the infinite vertex find the bottleneck to all other vertices and use this
	to answer queries fast.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef Triangulation::All_faces_iterator All_faces_iterator;
typedef Triangulation::Finite_faces_iterator Finite_faces_iterator;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 Point;
typedef long long ll;

using namespace std;

typedef pair<ll, ll> ii;

ll n, m, x, y, d, elements;
vector<Point> infected_people;
map<Face_handle, int> face_to_index;
map<int, Face_handle> index_to_face;
vector<vector<ii>> adj_list;
vector<ll> values;
priority_queue<ii> pq;
Triangulation t;

void read_testcase(){

	face_to_index.clear();
	index_to_face.clear();
	infected_people.clear();

	for(int i=0;i<n;i++){
		cin >> x >> y;
		infected_people.push_back(Point(x, y));
	}
}

void build_graph(){

	t = Triangulation();
	t.insert(infected_people.begin(), infected_people.end());

	elements = 0;
	for(Finite_faces_iterator f = t.finite_faces_begin(); f != t.finite_faces_end(); f++){

		face_to_index[f] = elements;
		index_to_face[elements] = f;
		elements++;
	}

	adj_list = vector<vector<ii>>(elements + 1);

	for (Finite_faces_iterator f = t.finite_faces_begin(); f != t.finite_faces_end(); ++f){

		for(int i=0;i<3;i++){

			auto neighbor = f->neighbor(i);

			Triangulation::Edge e; 
			e.first = f;
			e.second = i;

			ll weight = t.segment(e).squared_length();

			if(t.is_infinite(neighbor)){
				adj_list[face_to_index[f]].push_back({elements, weight});
				adj_list[elements].push_back({face_to_index[f], weight});
			}else{
				adj_list[face_to_index[f]].push_back({face_to_index[neighbor], weight});
			}
		}
	}
}

void modified_dijkstra(){

	values = vector<ll>(elements + 1, -1);
	pq = priority_queue<ii>();

	values[elements] = LLONG_MAX;
	pq.push({LLONG_MAX, elements});

	while(!pq.empty()){

		ll curr_value = pq.top().first;
		ll curr_node = pq.top().second;
		pq.pop();

		if(values[curr_node] > curr_value)
			continue;

		for(auto neighbor : adj_list[curr_node]){

			ll neighbor_node = neighbor.first;
			ll neighbor_edge_weight = neighbor.second;

			ll tmp = min(values[curr_node], neighbor_edge_weight);

			if(tmp > values[neighbor_node]){
				values[neighbor_node] = tmp;
				pq.push({tmp, neighbor_node});
			}
		}
	}
}

void solve_testcase(){

	modified_dijkstra();

	cin >> m;
	for(int i=0;i<m;i++){
		cin >> x >> y >> d;

		Point p(x, y);

		Point nearest = t.nearest_vertex(p)->point();
		Face_handle f = t.locate(Point(x, y));

		bool success = t.is_infinite(f) || values[face_to_index[f]] >= d*4;
		success = success && (CGAL::squared_distance(nearest, p) >= d);

		cout << (success ? "y" : "n");
	}
	cout << endl;
}

void testcase(){
	read_testcase();
	build_graph();
	solve_testcase();
}

int main(){
	ios_base::sync_with_stdio(false);

	while(1){
		cin >> n;
		if(!n) break;
		testcase();
	}

	return 0;
}