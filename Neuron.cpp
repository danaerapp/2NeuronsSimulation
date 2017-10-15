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
	
	if (temps_pause > 0){ //Neuron is refractory
		--temps_pause; //h est notre pas de temps
		
		if (temps_pause <= 0){
			potential=Vreset;
			
		}
		
	}else if ( (PSP > 0.0) ){ ///For now we consider that the transmission is immediate
		potential=exphtau*potential+PSP*(1-exphtau) + J; //Since I =V/R quand V est constant
		PSP=0.0; //Reset the PSP
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

void Neuron::receive(double potential, int time){
	PSP += potential;//The neurone receives the potential of an other neuron's spike
}

Neuron::Neuron()
: potential(Vreset),spikesNumber(0.0),temps_pause(0.0), clock_(0), J(0.0), PSP(0.0)
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
