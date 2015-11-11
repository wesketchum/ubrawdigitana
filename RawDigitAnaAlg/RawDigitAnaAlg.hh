/**
 * \file RawDigitAnaAlg.h
 *
 * 
 * \brief Little sample program for establishing a user analysis space.
 *
 * @author wketchum
*/

#ifndef TEST_RAWDIGITANAALG_HH
#define TEST_RAWDIGITANAALG_HH

#include <string>

#include "TTree.h"

#include "RawData/RawDigit.h"

namespace tpc{
  class RawDigitAnaAlg;
}

class tpc::RawDigitAnaAlg{
  
public:
  
  /// Default constructor
  RawDigitAnaAlg();

  /// Default destructor
  virtual ~RawDigitAnaAlg(){};

  void RunAnalysis(std::vector<raw::RawDigit> const&);
  void SetupOutputTree(TTree*);
  
 private:

  std::string fAlgName;
  TTree*      fTree;

  UInt_t     waveform_chan;
  Double_t   waveform_ped;
  Double_t   waveform_rms;
  UInt_t     waveform_samples;
  UInt_t     waveform_size;
  
  
  void PrintInfo();

  void AnalyzeWaveform(raw::RawDigit const&);
  
};

#endif
