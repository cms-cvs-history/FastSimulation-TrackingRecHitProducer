#ifndef FastSimulation_TrackingRecHitProducer_SiStripGaussianSmearingRecHitConverterAlgorithm_h
#define FastSimulation_TrackingRecHitProducer_SiStripGaussianSmearingRecHitConverterAlgorithm_h

//---------------------------------------------------------------------------
//! \class SiTrackerGaussianSmearingRecHits
//!
//! \brief EDProducer to create RecHits from PSimHits with Gaussian smearing
//!
//---------------------------------------------------------------------------

// PSimHit
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"

// Vectors
#include "Geometry/Vector/interface/Point3DBase.h"
#include "Geometry/Surface/interface/LocalError.h"

// CLHEP
#include "Geometry/CommonDetAlgo/interface/AlgebraicObjects.h"

// STL
#include <vector>
#include <string>

class RandomEngine;

class SiStripGaussianSmearingRecHitConverterAlgorithm {

public:
  //--- Constructor, virtual destructor (just in case)
  explicit SiStripGaussianSmearingRecHitConverterAlgorithm();
  virtual ~SiStripGaussianSmearingRecHitConverterAlgorithm() {;}
  
  // return results
  const Local3DPoint& getPosition() const {return thePosition;}
  double             getPositionX() const {return thePositionX;}
  double             getPositionY() const {return thePositionY;}
  double             getPositionZ() const {return thePositionZ;}
  const LocalError&  getError()     const {return theError;}
  double             getErrorX()    const {return theErrorX;}
  double             getErrorY()    const {return theErrorY;}
  double             getErrorZ()    const {return theErrorZ;}
  //
  void smearHit( const PSimHit& simHit , 
		 double localPositionResolutionX,
		 double localPositionResolutionY,
		 double localPositionResolutionZ);
  
private:

  // output
  Local3DPoint thePosition;
  double       thePositionX;
  double       thePositionY;
  double       thePositionZ;
  LocalError   theError;
  double       theErrorX;
  double       theErrorY;
  double       theErrorZ;
  //

  // The random engine
  RandomEngine* random;
  
};


#endif
