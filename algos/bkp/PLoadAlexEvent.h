
#ifndef PLoadAlexEvent_
#define PLoadAlexEvent_
#include <string>
#include <vector>


namespace irene
{
	class Particle;
}



namespace alex {
	
	class AParticle;	
  class PLoadAlexEvent {

  public:
    // You can add here public functions and variables to be used by derived algos
    std::vector<alex::AParticle*> 
  	AlexParticles(std::vector<const irene::Particle*> iParticles, 
  								std::string logger,std::string debug);

  protected:
    // You can add here functions and variables to be used by derived algos
    
  };
}
#endif 
