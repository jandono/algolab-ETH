#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cassert>
#include <unordered_set>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel EK;

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<long> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef std::pair<long, long> ii;
ii loc_gang_members[90000], loc_agent;
std::vector<long> info_leak_gm[90000], working_agents;

long z, www[3], a, g, x_i, y_i, u_i, v_i, w_i, z_i, gang, agent_to_gang[4000];
std::pair<int, ii> agents[4000];
std::unordered_set<int> assigned_agent;

EK::FT mini_dist, dist;

void init_test_case(){

	working_agents.clear();
	assigned_agent.clear();
}

void read_test_case(){

	std::cin >> z >> www[0] >> www[1] >> www[2];

	std::cin >> a >> g;

	for(int i=0;i<g;i++){
		std::cin >> x_i >> y_i >> u_i >> v_i >> w_i;
		loc_gang_members[i] = {x_i, y_i};
		std::vector<long> info_leak(3);
		info_leak.push_back(u_i); info_leak.push_back(v_i); info_leak.push_back(w_i);
		info_leak_gm[i] = info_leak;
	}

	for(int i=0;i<a;i++){
		std::cin >> x_i >> y_i >> z_i;
		agents[i] = {z_i, {x_i, y_i}};
	}

	sort(agents, agents + a);
}


void assign_agents(){

	for(int i=0;i<a;i++){
		loc_agent = agents[i].second;
		mini_dist = CGAL::squared_distance(EK::Point_2(loc_agent.first, loc_agent.second), 
			EK::Point_2(loc_gang_members[0].first, loc_gang_members[0].second));
		for(int j=1;j<g;j++){

			dist = CGAL::squared_distance(EK::Point_2(loc_agent.first, loc_agent.second), 
				EK::Point_2(loc_gang_members[j].first, loc_gang_members[j].second));

			if(dist < mini_dist){
				mini_dist = dist;
				gang = j;
			}
		}

		if(!assigned_agent.count(gang)){
			assigned_agent.insert(gang);
			agent_to_gang[i] = gang;
			working_agents.push_back(i);
		}else{
			agent_to_gang[i] = -1;
		}
	}
}

void test_case(){

	init_test_case();
	read_test_case();
	assign_agents();
	
	Program lp (CGAL::SMALLER, true, 0, true, 25);

	for(int j=0;j<3;j++){
		int i=0;
		for(auto agen:working_agents){
			int gm_index = agent_to_gang[agen];
			long val = info_leak_gm[gm_index][j];
			lp.set_a(i, j, -1 * val);
			i++;
		}
		lp.set_b(j, www[j]);
	}

	Solution s = CGAL::solve_linear_program(lp, ET());
	assert(s.solve_linear_program(lp));

	std::cout << s;
}

int main(){

	std::ios_base::sync_with_stdio(false);

	int T;
	std::cin >> T;
	while(T--) test_case();

	return 0;
}