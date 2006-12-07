#ifndef FastSimulation_TrackingRecHitProducer_SiTrackerGaussianSmearingRecHitConverter_h
#define FastSimulation_TrackingRecHitProducer_SiTrackerGaussianSmearingRecHitConverter_h

//---------------------------------------------------------------------------
//! \class SiTrackerGaussianSmearingRecHits
//!
//! \brief EDProducer to create RecHits from PSimHits with Gaussian smearing
//!
//---------------------------------------------------------------------------

// Framework
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Geometry
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"

// PSimHit
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"

// Gaussian Smearing
#include "DataFormats/TrackerRecHit2D/interface/SiTrackerGSRecHit2DCollection.h"

// CLHEP
#include "Geometry/Vector/interface/Point3DBase.h"
#include "Geometry/Surface/interface/LocalError.h"
#include "Geometry/CommonDetAlgo/interface/AlgebraicObjects.h"

// STL
#include <vector>
#include <string>

class TFile;
class TH1F;

namespace cms
{
  class SiTrackerGaussianSmearingRecHitConverter : public edm::EDProducer
  {
  public:
    //--- Constructor, virtual destructor (just in case)
    explicit SiTrackerGaussianSmearingRecHitConverter(const edm::ParameterSet& conf);
    virtual ~SiTrackerGaussianSmearingRecHitConverter();
    
    //--- The top-level event method.
    virtual void produce(edm::Event& e, const edm::EventSetup& c);
    
    // Begin Job
    virtual void beginJob(const edm::EventSetup& c);
    
    //--- Execute the position estimator algorithm(s).
    //--- New interface with DetSetVector
    
    void run(MixCollection<PSimHit>& input,
	     SiTrackerGSRecHit2DCollection& output,
	     edm::ESHandle<TrackerGeometry>& geom);
    
  private:
    //
    bool gaussianSmearing(const PSimHit& simHit, Local3DPoint& position , LocalError& error, unsigned int& alphaMult, unsigned int& betaMult);
    //
    void loadPixelData();
    //
    void loadPixelData(TFile* pixelDataFile, unsigned int nMultiplicity, std::string histName,
		       std::vector<TH1F*>& theMultiplicityCumulativeProbabilities);
    //
    //
    // parameters
    edm::ParameterSet conf_;
    int theVerboseLevel;
    std::string theRecHitsTag;
    std::vector<std::string> trackerContainers;
    double deltaRaysPCut; // GeV/c
    bool trackingPSimHits; // in case it is true make RecHit = replica of PSimHit without errors (1 um)
    //
    edm::ESHandle<TrackerGeometry> geometry;
    //
    // Pixel
    std::string thePixelMultiplicityFileName;
    std::string thePixelBarrelResolutionFileName;
    std::string thePixelForwardResolutionFileName;
    TFile* thePixelDataFile;
    TFile* thePixelBarrelResolutionFile;
    TFile* thePixelForwardResolutionFile;
    //
    // multiplicity bins
    unsigned int nAlphaBarrel, nBetaBarrel, nAlphaForward, nBetaForward;
    // internal vector: bins ; external vector: multiplicity
    std::vector<TH1F*> theBarrelMultiplicityAlphaCumulativeProbabilities;
    std::vector<TH1F*> theBarrelMultiplicityBetaCumulativeProbabilities;
    std::vector<TH1F*> theForwardMultiplicityAlphaCumulativeProbabilities;
    std::vector<TH1F*> theForwardMultiplicityBetaCumulativeProbabilities;
    // resolution bins
    double resAlphaBarrel_binMin , resAlphaBarrel_binWidth;
    unsigned int resAlphaBarrel_binN;
    double resBetaBarrel_binMin  , resBetaBarrel_binWidth;
    unsigned int resBetaBarrel_binN;
    double resAlphaForward_binMin , resAlphaForward_binWidth;
    unsigned int resAlphaForward_binN;
    double resBetaForward_binMin  , resBetaForward_binWidth;
    unsigned int resBetaForward_binN;
    //
    double theHitFindingProbability_PXB;
    double theHitFindingProbability_PXF;
    //
    // Strips
    // TIB
    double localPositionResolution_TIB1x; // cm
    double localPositionResolution_TIB1y; // cm
    double localPositionResolution_TIB2x; // cm
    double localPositionResolution_TIB2y; // cm
    double localPositionResolution_TIB3x; // cm
    double localPositionResolution_TIB3y; // cm
    double localPositionResolution_TIB4x; // cm
    double localPositionResolution_TIB4y; // cm
    //
    double theHitFindingProbability_TIB1;
    double theHitFindingProbability_TIB2;
    double theHitFindingProbability_TIB3;
    double theHitFindingProbability_TIB4;
    //
    // TID
    double localPositionResolution_TID1x; // cm
    double localPositionResolution_TID1y; // cm
    double localPositionResolution_TID2x; // cm
    double localPositionResolution_TID2y; // cm
    double localPositionResolution_TID3x; // cm
    double localPositionResolution_TID3y; // cm
    //
    double theHitFindingProbability_TID1;
    double theHitFindingProbability_TID2;
    double theHitFindingProbability_TID3;
    //
    // TOB
    double localPositionResolution_TOB1x; // cm
    double localPositionResolution_TOB1y; // cm
    double localPositionResolution_TOB2x; // cm
    double localPositionResolution_TOB2y; // cm
    double localPositionResolution_TOB3x; // cm
    double localPositionResolution_TOB3y; // cm
    double localPositionResolution_TOB4x; // cm
    double localPositionResolution_TOB4y; // cm
    double localPositionResolution_TOB5x; // cm
    double localPositionResolution_TOB5y; // cm
    double localPositionResolution_TOB6x; // cm
    double localPositionResolution_TOB6y; // cm
    //
    double theHitFindingProbability_TOB1;
    double theHitFindingProbability_TOB2;
    double theHitFindingProbability_TOB3;
    double theHitFindingProbability_TOB4;
    double theHitFindingProbability_TOB5;
    double theHitFindingProbability_TOB6;
    //
    // TEC
    double localPositionResolution_TEC1x; // cm
    double localPositionResolution_TEC1y; // cm
    double localPositionResolution_TEC2x; // cm
    double localPositionResolution_TEC2y; // cm
    double localPositionResolution_TEC3x; // cm
    double localPositionResolution_TEC3y; // cm
    double localPositionResolution_TEC4x; // cm
    double localPositionResolution_TEC4y; // cm
    double localPositionResolution_TEC5x; // cm
    double localPositionResolution_TEC5y; // cm
    double localPositionResolution_TEC6x; // cm
    double localPositionResolution_TEC6y; // cm
    double localPositionResolution_TEC7x; // cm
    double localPositionResolution_TEC7y; // cm
    //
    double theHitFindingProbability_TEC1;
    double theHitFindingProbability_TEC2;
    double theHitFindingProbability_TEC3;
    double theHitFindingProbability_TEC4;
    double theHitFindingProbability_TEC5;
    double theHitFindingProbability_TEC6;
    double theHitFindingProbability_TEC7;
    //
    // valid for all the detectors
    double localPositionResolution_z; // cm
    //
    typedef std::map<unsigned int, std::vector<PSimHit>,std::less<unsigned int> > simhit_map;
  };
}


#endif
