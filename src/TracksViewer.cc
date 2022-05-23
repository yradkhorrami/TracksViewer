#include "TracksViewer.h"
#include <iostream>
TracksViewer aTracksViewer;

TracksViewer::TracksViewer() :

Processor("TracksViewer"),
m_nRun(0),
m_nEvt(0),
m_nRunSum(0),
m_nEvtSum(0),
m_Bfield(0.f)
{
	_description = "TracksViewer displays tracks fitted with pion mass and refitted with true mass, shows trackers hits and compares with MCTruth informations";

	registerInputCollection(	LCIO::RECONSTRUCTEDPARTICLE,
					"RecoParticleCollection",
					"Name of Input Reconstrcuted Particle Collection",
					m_inputReconstructedParticleCollection,
					std::string("PandoraPFOs")
				);

	registerInputCollection(	LCIO::TRACK,
					"MarlinTrkTracksCollection" ,
					"Name of the MarlinTrkTracks collection (fitted with pion mass)"  ,
					m_inputOriginalTracks,
					std::string("MarlinTrkTracks")
				);
	registerInputCollection(	LCIO::TRACK,
					"MarlinTrkTracksCollectionRefitted" ,
					"Name of the MarlinTrkTracks collection refitted with true mass"  ,
					m_inputRefittedTracks,
					std::string("MarlinTrkTracksKaon")
				);

	registerInputCollection(	LCIO::LCRELATION,
					"TrackMCTruthLinkCollection",
					"Name of input TrackMCTruthLink Collection",
					m_TrackMCTruthLinkCollection,
					std::string("MarlinTrkTracksMCTruthLink")
				);
	registerInputCollection(	LCIO::LCRELATION,
					"MCTruthTrackLinkCollection",
					"Name of input MCTruthTrackLink Collection",
					m_MCTruthTrackLinkCollection,
					std::string("MCTruthMarlinTrkTracksLink")
				);

}

void TracksViewer::init()
{

	streamlog_out(DEBUG) << "	init called  " << std::endl;
	m_Bfield = MarlinUtil::getBzAtOrigin();
	printParameters();
	DDMarlinCED::init(this);
}

void TracksViewer::processRunHeader()
{
	m_nRun = 0;
	m_nEvt = 0;
	++m_nRunSum;
}

void TracksViewer::processEvent( EVENT::LCEvent *pLCEvent )
{
	m_nRun = pLCEvent->getRunNumber();
	m_nEvt = pLCEvent->getEventNumber();

	DDMarlinCED::newEvent( this ); // refresh
	DDMarlinCED::drawDD4hepDetector( this->_theDetector , 0 , std::vector<std::string>{} ); // draw geometry
	DDCEDPickingHandler& pHandler = DDCEDPickingHandler::getInstance();
	pHandler.update(pLCEvent);

	DDMarlinCED::draw( this , 1); // draw everything
	LCCollection *ReconstructedParticleCollection{};
	LCCollection *MarlinTrkTracksCollection{};
	LCCollection *MarlinTrkTracksRefittedCollection{};
}

void TracksViewer::check()
{}

void TracksViewer::end()
{}
