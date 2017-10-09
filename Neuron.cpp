#include "Neuron.hpp"

double Neuron::getPotential() const{
	return potential;
}

double Neuron::getSpikesNumber() const{
	return spikesNumber;
}

double Neuron::getTime(unsigned int i) const{
	return times[i];
}


		
void Neuron::setPotential(double i){
	potential =i;
}

void Neuron::addSpike(){
	spikesNumber+=1;
}

void Neuron::addTime(double i){
	times.push_back(i);
}
				
void Neuron::update(double Current){
	
	++clock_;
	
	if (temps_pause > 0.0){ //Neuron is refractory
		--temps_pause; //h est notre pas de temps
		isRefractory_=true;
		
		if (temps_pause <= 0.0){
			potential=Vreset;
			isRefractory_=false;
		}
		
	}else{ 
		//Calcul du potentiel
		double new_potential(0.0);
		new_potential=exphtau*potential+Current*R*(1-exphtau);
		
		if (new_potential >= Vth){ //Le neurone spike
			addTime(clock_);
			addSpike();
			temps_pause=(tauRef/h);
		}
		
		potential=new_potential;
	}
}

Neuron::Neuron()
: potential(Vreset),spikesNumber(0.0),temps_pause(0.0), clock_(0.0), isRefractory_(false)
{
	times.clear();
}

Neuron::Neuron(double p, double s, std::vector<double> t)
:potential(p), spikesNumber(s), temps_pause(0.0)
{
	for (unsigned int i(0); i<t.size();++i){
		times[i]=t[i];
	}
}
