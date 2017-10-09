#include "Network.hpp"

Network::Network()
{
	for(int i(0); i<nb_neurons;++i){
		all_neurons.push_back(i);
	}
	
	for (int i(0); i<nb_neurons;++i){
		for (int j(0); j<nb_neurons;++j){
			if (i!=j){
				relation[i][j]=true; ///voisins aléatoirement attribués ?
			}
		}
	}
}

Network::~Network(){
	for(int i(0); i<nb_neurons;++i){
		delete all_neurons[i];
	}
	all_neurons.clear()
}

vector<int> Network::getNeighbours(int n) const{
	
	vector<int> Neighbours;
	
	for (int i(0); i<nb_neurons;++i){
		if (relation[n][i]){
			Neighbours.push_back(i);
		}
	}
	
	return Neighbours;
}

void connect(int from, int to, double current_weight){
	if (relation[from][to]){
		
	}
}
