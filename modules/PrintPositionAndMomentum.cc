/*
 *  Delphes: a framework for fast simulation of a generic collider experiment
 *  Copyright (C) 2012-2014  Universite catholique de Louvain (UCL), Belgium
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


/** \class PrintPositionAndMomentum
 *
 *  Performs transverse momentum resolution smearing.
 *
 *  \author P. Demin - UCL, Louvain-la-Neuve
 *
 */

#include "modules/PrintPositionAndMomentum.h"

#include "classes/DelphesClasses.h"
#include "classes/DelphesFactory.h"
#include "classes/DelphesFormula.h"

#include "ExRootAnalysis/ExRootResult.h"
#include "ExRootAnalysis/ExRootFilter.h"
#include "ExRootAnalysis/ExRootClassifier.h"

#include "TMath.h"
#include "TString.h"
#include "TFormula.h"
#include "TRandom3.h"
#include "TObjArray.h"
#include "TDatabasePDG.h"
#include "TLorentzVector.h"

#include <algorithm> 
#include <stdexcept>
#include <iostream>
#include <sstream>


//------------------------------------------------------------------------------

PrintPositionAndMomentum::PrintPositionAndMomentum() :
  fItInputArray(0)
{
}

//------------------------------------------------------------------------------

PrintPositionAndMomentum::~PrintPositionAndMomentum()
{
}

//------------------------------------------------------------------------------

void PrintPositionAndMomentum::Init()
{

  // import input array
  fInputArray = ImportArray(GetString("InputArray", "ParticlePropagator/stableParticles"));
  fItInputArray = fInputArray->MakeIterator();


}

//------------------------------------------------------------------------------

void PrintPositionAndMomentum::Finish()
{
  if(fItInputArray) delete fItInputArray;
}

//------------------------------------------------------------------------------

void PrintPositionAndMomentum::Process()
{
  std::cout << "Dumping eta phi" << std::endl;
  Candidate *candidate, *mother;
  Double_t pt, eta, phi, e, res;

  fItInputArray->Reset();
  while((candidate = static_cast<Candidate*>(fItInputArray->Next())))
  {
    const TLorentzVector &candidatePosition = candidate->Position;
    const TLorentzVector &candidateMomentum = candidate->Momentum;

    double_t momentumEta = candidateMomentum.Eta();
    double_t momentumPhi = candidateMomentum.Phi();
    double_t positionEta = candidatePosition.Eta();
    double_t positionPhi = candidatePosition.Phi();

    std::cout << "Pos " << positionEta << ", " << positionPhi << " - Mom " << momentumEta << ", " << momentumPhi << std::endl;
  }
}


//------------------------------------------------------------------------------
