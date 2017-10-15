#include "Network.hpp"

Network::Network()
{
	for(int i(0); i<nb_neurons;++i){
		all_neurons[i]=i;
	}
	
	for (int i(0);i<nb_neurons;++i){ //par défaut, aucun n'est connecté
		for (int j(0);j<nb_neurons;++j){
			connection[i][j]=false;
		}
	}
	
	/*for (int i(0); i<nb_neurons;++i){
		for (int j(0); j<nb_neurons;++j){
			if (i!=j){
				connection[i][j]=...; 
				///voisins aléatoirement attribués selon Connection=epsilon*NbNeurons
			}
		}
	}*/// Pour plus tard, quand nb_neurons > 2
	//mais ici nous considérons seulement 2 neurones : 0 connecté à 1, 1 connecté à personne
	
	connection[0][1]=true;
	connection[1][0]=false;
}

Network::~Network(){}

std::vector<int> Network::getTargets(int n) const{
	
	std::vector<int> targets;
	
	for (int i(0); i<nb_neurons;++i){
		if (connection[n][i]){
			targets.push_back(i);
		}
	}
	
	return targets;
}
