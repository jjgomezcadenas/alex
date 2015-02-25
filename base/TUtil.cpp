

#include <alex/VectorOperations.h>

namespace alex {
	//--------------------------------------------------------------------
	std::string PrintTVector3(TVector3 t)
	//--------------------------------------------------------------------
	{
		std::stringstream s;  
		s << " x = " << t.X() << " y = " << t.Y() 
		<< " z = " << t.Z() << std::endl;

		return s.str();
	}

	//--------------------------------------------------------------------
	std::string PrintTLorentzVector(TLorentzVector t)
	//--------------------------------------------------------------------
	{
		std::stringstream s;  
		s << " Px = " << t.Px() << " Py = " << t.Py() 
		<< " Pz = " << t.Pz() <<  " E = " << t.E() << std::endl;
		return s.str();
	}
}
