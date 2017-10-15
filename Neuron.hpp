#ifndef NEURON_HPP
#define NEURON_HPP

#include <array>
#include <cmath>
#include <iostream>
#include <vector>

class Neuron{
	
	private:
	
	//Constantes de classe
		const double C = 1.0;
		const double tau = 20.0; //milliseconds, tau = R*C
		const double tauRef = 2.0; //milliseconds, refractory time
		const double Erepos = 0.0; //milliVolts
		const double Vreset = 0.0; //milliVolts, potentiel de repos
		const double exphtau = exp(-h/tau); //Constante dont on a besoin pour calculer le nouveau potentiel
		
		
	//Attributs
		double potential;
		double spikesNumber;
		std::vector<double> times;
		
		double PSP;//current weight, post synaptic potential amplitude (PSP amplitude), called J in the paper
		
		int temps_pause; //For the refractory time after a spike, in nb of steps
		
		int clock_; //in nb of steps (not in seconds)
		
		std::vector<double> buffer; //Our ring buffer will contain maximum 15 values, since we are moving 0.1ms at a time ans the delay is of 1.5ms
		
	public:
	
	//Attributs de classe
		static constexpr double h = 0.1; //milliseconds, laps de temps entre chaque mesures de potentiel
		static constexpr double Vth = 20.0;
		static constexpr double R = 20.0; //picoFarad, tau/C = R 
		static constexpr double delay = 15; //nb of steps between a spike and the reception of this spike by a target neurone
	
		double getPotential() const;
		double getPSP() const;
		double getSpikesNumber() const;
		double getTime(unsigned int i) const;
		void bufferUpdate();
		
		bool isRefractory() const;
		
		void setPotential(double i);
		void addSpike(); //Ajout d'un spike
		void addTime(double i);
		
		void update(double current);
		
		void receive(double PSP, int delay);
		
		Neuron();
		Neuron(double p, double s, std::vector<double> t);
		
		~Neuron(){}
	
};

#endif
