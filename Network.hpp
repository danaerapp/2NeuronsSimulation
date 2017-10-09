#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <array>
#include <vector>

class Network{
	private:
		array<int , nb_neurons> all_neurons;
		array<array<bool,nb_neurons>, nb_neurons> relation;
		
	public:
	
		static constexpr nb_neurons = 2;
		
		vector<int> getNeighbours(int n) const;
		void connect(int from, int to, double current_weight); //Transmettre un courant aux voisins après un spike 
		
		~Network();
		Network();
};

#endif
