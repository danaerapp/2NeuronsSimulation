#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <array>
#include <vector>

class Network{
	private:
	
		static constexpr int nb_neurons = 2;
	
		std::array<int , nb_neurons> all_neurons;
		std::array<std::array<bool,nb_neurons>, nb_neurons> connection; //Matrice carrée, si connection[i][j]=true --> i est connecté à j (et non l'inverse!)
		
	public:
		
		std::vector<int> getTargets(int n) const;
		
		~Network();
		Network();
};

#endif
