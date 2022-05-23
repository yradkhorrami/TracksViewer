#ifndef MyTracksViewer_h
#define MyTracksViewer_h 1

#include "lcio.h"
#include <marlin/Processor.h>
#include <marlin/Global.h>
#include "marlin/VerbosityLevels.h"
#include <marlinutil/HelixClass.h>
#include <marlinutil/GeometryUtil.h>
#include "UTIL/LCRelationNavigator.h"
#include "EVENT/LCStrVec.h"
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <EVENT/Track.h>
#include "DD4hep/Detector.h"
#include <GeometryUtil.h>
#include "DDMarlinCED.h"

using namespace lcio ;
using namespace marlin ;
class TracksViewer : public Processor
{
public:
	virtual Processor *newProcessor()
	{
		return new TracksViewer;
	}
	TracksViewer();
	virtual ~TracksViewer() = default;
	TracksViewer( const TracksViewer& ) = delete;
	TracksViewer &operator = ( const TracksViewer& ) = delete;
	virtual void init();
	virtual void processRunHeader();
	virtual void processEvent( EVENT::LCEvent *pLCEvent );
	virtual void check();
	virtual void end();
	dd4hep::Detector& _theDetector = dd4hep::Detector::getInstance();

private:

	std::string				m_inputReconstructedParticleCollection{};
	std::string				m_inputOriginalTracks{};
	std::string				m_inputRefittedTracks{};
	std::string				m_TrackMCTruthLinkCollection{};
	std::string				m_MCTruthTrackLinkCollection{};
	int					m_nRun;
	int					m_nEvt;
	int					m_nRunSum;
	int					m_nEvtSum;
	double					m_Bfield;
};
#endif
