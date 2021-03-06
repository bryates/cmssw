// -*- C++ -*-
//
// Package:    HGCalNumberingTester
// Class:      HGCalNumberingTester
// 
/**\class HGCalNumberingTester HGCalNumberingTester.cc test/HGCalNumberingTester.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Sunanda Banerjee
//         Created:  Mon 2014/03/21
// $Id: HGCalNumberingTester.cc,v 1.0 2014/032/21 14:06:07 sunanda Exp $
//
//


// system include files
#include <memory>
#include <iostream>
#include <fstream>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESTransientHandle.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DetectorDescription/Core/interface/DDCompactView.h"
#include "DetectorDescription/Core/interface/DDExpandedView.h"
#include "DetectorDescription/Core/interface/DDSpecifics.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "Geometry/HGCalCommonData/interface/HGCalDDDConstants.h"

#include "CoralBase/Exception.h"

//
// class decleration
//

class HGCalNumberingTester : public edm::EDAnalyzer {
public:
  explicit HGCalNumberingTester( const edm::ParameterSet& );
  ~HGCalNumberingTester();

  
  virtual void analyze( const edm::Event&, const edm::EventSetup& );
private:
  // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
HGCalNumberingTester::HGCalNumberingTester(const edm::ParameterSet& ) {}


HGCalNumberingTester::~HGCalNumberingTester() {}


//
// member functions
//

// ------------ method called to produce the data  ------------
void HGCalNumberingTester::analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup ) {
  
  edm::ESHandle<HGCalDDDConstants> pHGNDC;

  iSetup.get<IdealGeometryRecord>().get("HGCalEESensitive",pHGNDC);
  const HGCalDDDConstants hgeedc(*pHGNDC);
  std::cout << "EE Layers = " << hgeedc.layers(false) << " Sectors = " 
	    << hgeedc.sectors() << std::endl;
  for (unsigned int i=0; i<hgeedc.layers(false); ++i) {
    std::vector<int> ncells = hgeedc.numberCells(i+1,false);
    std::cout << "Layer " << i+1 << " with " << ncells.size() << " rows\n";
    int ntot(0);
    for (unsigned int k=0; k<ncells.size(); ++k) {
      ntot += ncells[k];
      std::cout << "Row " << k << " with " << ncells[k] << " cells\n";
    }
    std::cout << "Total Cells " << ntot << ":" << hgeedc.maxCells(i+1,false) 
	      << std::endl;
    i += 19;
  }

  iSetup.get<IdealGeometryRecord>().get("HGCalHESiliconSensitive",pHGNDC);
  const HGCalDDDConstants hghesidc(*pHGNDC);
  std::cout << "HE Silicon Layers = " << hghesidc.layers(false) << " Sectors = " 
	    << hghesidc.sectors() << std::endl;
  for (unsigned int i=0; i<hghesidc.layers(false); ++i) {
    std::vector<int> ncells = hghesidc.numberCells(i+1,false);
    std::cout << "Layer " << i+1 << " with " << ncells.size() << " rows\n";
    int ntot(0);
    for (unsigned int k=0; k<ncells.size(); ++k) {
      ntot += ncells[k];
      std::cout << "Row " << k << " with " << ncells[k] << " cells\n";
    }
    std::cout << "Total Cells " << ntot << ":" << hghesidc.maxCells(i+1,false) 
	      << std::endl;
    i += 9;
  }

  iSetup.get<IdealGeometryRecord>().get("HGCalHEScintillatorSensitive",pHGNDC);
  const HGCalDDDConstants hghescdc(*pHGNDC);
  std::cout << "HE Scintillator Layers = " << hghescdc.layers(false) <<" Sectors = "
	    << hghescdc.sectors() << std::endl;
  for (unsigned int i=0; i<hghescdc.layers(false); ++i) {
    std::vector<int> ncells = hghescdc.numberCells(i+1,false);
    std::cout << "Layer " << i+1 << " with " << ncells.size() << " rows\n";
    int ntot(0);
    for (unsigned int k=0; k<ncells.size(); ++k) {
      ntot += ncells[k];
      std::cout << "Row " << k << " with " << ncells[k] << " cells\n";
    }
    std::cout << "Total Cells " << ntot << ":" << hghescdc.maxCells(i+1,false) 
	      << std::endl;
    i += 9;
  }
}


//define this as a plug-in
DEFINE_FWK_MODULE(HGCalNumberingTester);
