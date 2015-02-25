#ifndef IDEFS_
#define IDEFS_
/*
 Irene dependent includes and defs
*/


#include <string>
#include <vector>
#include <irene/Event.h>
#include <irene/Track.h>
#include <irene/Particle.h>


namespace alex {
typedef const irene::Particle* IParticle;
typedef const irene::Track* ITrack;
typedef std::vector<const irene::Particle*> IParticles;
typedef std::vector<const irene::Track*> ITracks;
typedef std::vector<std::pair<TLorentzVector,double> > IHits ;
}
#endif