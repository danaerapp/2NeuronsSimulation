#include <iostream>
#include <fstream>
#include "Constantes.hpp"
#include "Neuron.hpp"

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

	Neuron neurone1;
	Neuron neurone2;
	
	int nb_steps(t_stop/Neuron::h); //0.1ms est notre pas de temps
	
	for (int t(0); t < nb_steps; ++t){
		if (sortie.fail()){
			cerr<< "Erreur d'ouverture du fichier" << endl;
		}else{
			
			if ( (neurone1.getPotential() >= Neuron::Vth) and not(neurone1.isRefractory_)){
				neurone2.update(neurone1.getPotential()/Neuron::R); // I=V/R quand V est constant
			}else{
				neurone2.update(0.0);
			}
			neurone1.update(ExtCurrent);
			sortie << neurone2.getPotential() << endl;
		}
	}
	
	cout << "Pour le premier neurone : " << endl;
	for (size_t i(0); i < neurone1.getSpikesNumber();++i){
		cout << "spike au temps : " << neurone1.getTime(i)*Neuron::h << endl;
	}
	
	return 0;
}
