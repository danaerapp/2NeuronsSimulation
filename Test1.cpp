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
}

