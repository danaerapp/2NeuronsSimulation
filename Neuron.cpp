#include "Neuron.hpp"

double Neuron::getPotential() const{
	return potential;
}

double Neuron::getPSP() const{
	return PSP;
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
	
bool Neuron::isRefractory() const{
	if ( (temps_pause > 0) and (potential > Vth) and (temps_pause < (tauRef/h))){ // Si temps_pause == tauRef, on veut encore que le neurone puisse transmettre sosn potentiel (et donc être considéré comme non-refractaire)
		return true;
	}
	return false;
}
				
void Neuron::update(double Current){
	
	++clock_;
	
	bufferUpdate();
	
	if (temps_pause > 0){ //Neuron is refractory
		--temps_pause; //h est notre pas de temps
		
		if (temps_pause <= 0){
			potential=Vreset;
			
		}
		
	}else if (buffer[0] > 0.0){
		potential=Neuron::exphtau*potential+Current*(1-exphtau) + 0.5*buffer[0]; //On prend que J = 0.5*le potentiel post synaptique
		///std::cout << "Réception au temps " << clock_*h << std::endl; Test
		buffer[0] -= buffer[0]; //Reset the PSP
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

void Neuron::bufferUpdate(){
	
	for (size_t i(0); i < buffer.size()-1 ;++i){
		buffer[i] = buffer[i+1]; //On décale tout et insert un 0 à la fin
	}
	buffer[buffer.size()-1] = 0.0;
}

void Neuron::receive(double p, int t){
	buffer[t-1]+=p; //The neurone receives the potential of an other neuron's spike
}

Neuron::Neuron()
: potential(Vreset),spikesNumber(0.0),temps_pause(0.0), clock_(0), PSP(0.0), buffer({0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0})
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
