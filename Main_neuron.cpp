#include <iostream>
#include <fstream>
#include "Neuron.hpp"
#include "Network.hpp"

using namespace std;

//Système avec 2 neurones : le 2ème neurone réagit au potentiel post-synaptique du premier
//On écrit dans un fichier les valeurs du potentiel du 2ème neurone

int main(){
	
	//We say t_start=0
	double t_stop(0.0);
	cout << "Determine a time to stop :";
	cin >> t_stop;
	cout << endl;
	
	double ExtCurrent(0.0);
	cout << "Determine an external current ([1;100] pA) :";
	cin >> ExtCurrent;
	cout << endl;
		
	ofstream sortie("Data.txt");
	
	Network network;
	int nb_neurons(2);
	
	vector<Neuron> all;
	
	for (int i(0);i<nb_neurons;++i){ //On initialise des neurones
		Neuron n;
		all.push_back(n);
	}
	
	int nb_steps(t_stop/Neuron::h); //0.1ms est notre pas de temps
	
	
	for (int t(0); t < nb_steps; ++t){
		if (sortie.fail()){
			cerr<< "Erreur d'ouverture du fichier" << endl;
		}else{
			
			//sortie << "t = " << t << " : " << endl;
			
			for (size_t i(0);i<all.size();++i){
					
					if ( (all[i].getPotential() >= Neuron::Vth) and not(all[i].isRefractory())){//Si le neurone spike et qu'il n'est pas en période réfractaire --> il envoi un signal à ses "voisins"
						
						vector<int> targets(network.getTargets(i));//Vector contenant les neurones pouvant recevoir le signal
						
						for (size_t j(0); j<targets.size();++j){
							//sortie << "Transmission de " << i << " à " << targets[j] << endl;
							all[targets[j]].receive(all[i].getPotential(),t); //Transmission du potentiel post synaptique, les targets reçoive un PSP et enregistre le temps de transmission
						}
						
						all[i].update(ExtCurrent);
						
					}else{
						if (i==0){
							all[i].update(ExtCurrent);
						}else{
							all[i].update(0.0); //Pour l'instant nous voulons que le deuxième neurone réagisse uniquement au courant post synaptique
						}
					}
					if (i==1){
						sortie << all[i].getPotential() << endl;
					}
			}
		}
	}
	
	cout << "Pour le premier neurone : " << endl;
	for (size_t i(0); i < all[0].getSpikesNumber();++i){
		cout << "spike au temps : " << all[0].getTime(i)*Neuron::h << endl;
	}
	
	return 0;
}
