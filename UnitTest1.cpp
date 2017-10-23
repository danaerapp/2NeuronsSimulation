#include "googletest/include/gtest/gtest.h"
#include <cmath>
#include "Neuron.hpp"

TEST (NeuronTest, ShouldNotSpike){
	Neuron neurone;
	double Iext(1.0);
	double potential(0.0);
	
	for (int i(0); i < 5000; ++i){ //500 ms
		neurone.update(Iext);
		potential = exp(-0.1/20.0)*potential+20.0*(1-exp(-0.1/20.0));
	}
	
	EXPECT_EQ(neurone.getPotential(), potential);
	EXPECT_EQ(0,neurone.getSpikesNumber()); //Should not have spiked
	///EXPECT_EQ(neurone.getTime(0),); l'instruction neurone.getTime(0) should fail !
}

TEST (NeuronTest, ShouldSpike){
	Neuron neurone;
	double Iext(1.01);
	double potential(0.0);
	int temps_spike(0);
	
for (int i(1); i < 1000; ++i){ //100 ms, On initialise i à 1, car le prermier update doit se faire après le premier laps de temps
		neurone.update(Iext);
		potential = exp(-0.1/20.0)*potential+Iext*20.0*(1-exp(-0.1/20.0));
		
		if ( (potential >= Neuron::Vth) and (temps_spike==0)){ //Prendre le premier temps où le potentiel dépasse le threshold potential
			temps_spike = i;
		}
	}
	
	EXPECT_EQ(temps_spike,neurone.getTime(0)); 
	EXPECT_EQ(1,neurone.getSpikesNumber());
	
}

TEST (TwoNeurons, CorrespondanceWithJ){
	Neuron neurone1;
	Neuron neurone2;
	double Iext(1.01);
	
	for (int i(1); i <= 924+Neuron::delay/0.1; ++i){
		neurone1.update(Iext);
		neurone2.update(0.0);
		
		if ( (neurone1.getPotential() >= Neuron::Vth) and not(neurone1.isRefractory())){ //Prendre le premier temps où le potentiel dépasse le threshold potential
			neurone2.receive(0.1, Neuron::delay);
		}
	}
	EXPECT_EQ(0.1,neurone2.getPotential());
	EXPECT_EQ(0,neurone2.getSpikesNumber());
	EXPECT_EQ(1,neurone1.getSpikesNumber());
}

TEST (TwoNeurons, TimeDelay){
	Neuron neurone1;
	Neuron neurone2;
	double Iext(1.01);
	int reception_time(0);
	
	for (int i(1); i <= 924+Neuron::delay/0.1; ++i){
		neurone1.update(Iext);
		neurone2.update(0.0);
		
		if ( (neurone1.getPotential() >= Neuron::Vth) and not(neurone1.isRefractory())){ //Prendre le premier temps où le potentiel dépasse le threshold potential
			neurone2.receive(0.1, Neuron::delay);
		}
		
		if (neurone2.getPotential() == 0.1){
			reception_time = i;
		}
	}
	EXPECT_EQ(924+Neuron::delay/0.1,reception_time);
}
