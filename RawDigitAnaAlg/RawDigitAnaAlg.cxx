#ifndef TEST_RAWDIGITANAALG_CXX
#define TEST_RAWDIGITANAALG_CXX

#include "RawDigitAnaAlg.hh"
#include <iostream>
#include <cmath>

tpc::RawDigitAnaAlg::RawDigitAnaAlg()
  : fAlgName("RawDigitAnaAlg")
{}

void tpc::RawDigitAnaAlg::SetupOutputTree(TTree* tfs_tree){
  fTree = tfs_tree;

  std::string title = fAlgName + " Tree";
  fTree->SetObject(fTree->GetName(),title.c_str());

  fTree->Branch("waveform_chan",&waveform_chan,"waveform_chan/i");
  fTree->Branch("waveform_ped",&waveform_ped,"waveform_ped/D");
  fTree->Branch("waveform_rms",&waveform_rms,"waveform_rms/D");
  fTree->Branch("waveform_samples",&waveform_samples,"waveform_samples/i");
  fTree->Branch("waveform_size",&waveform_size,"waveform_size/i");

}

void tpc::RawDigitAnaAlg::RunAnalysis(std::vector<raw::RawDigit> const& waveformVector){
  PrintInfo();

  for(auto const& waveform : waveformVector)
    AnalyzeWaveform(waveform);
}

void tpc::RawDigitAnaAlg::AnalyzeWaveform(raw::RawDigit const& waveform){

  long unsigned int sum_adc = 0;
  
  for(auto const& adctick : waveform.ADCs())
    sum_adc += adctick;

  waveform_ped = (double)(sum_adc)/(double)(waveform.Samples());
    
  double sum_adc_diff_sq = 0;
  
  for(auto const& adctick : waveform.ADCs())
    sum_adc_diff_sq = (waveform_ped - (double)adctick)*(waveform_ped - (double)adctick);

  waveform_rms = std::sqrt(sum_adc_diff_sq/(double)(waveform.Samples()));

  waveform_chan = waveform.Channel();

  waveform_size = waveform.ADCs().size();
  waveform_samples = waveform.Samples();
  fTree->Fill();
}

void tpc::RawDigitAnaAlg::PrintInfo(){
  std::cout << "\n================================== RawDigitAnaAlg ==========================" << std::endl;
  std::cout << "This is a ub_RawDigitAnaAlg class called " << fAlgName << std::endl;
  std::cout << "\tThere is an output tree called "
	    << fTree->GetName() << " (" << fTree->GetTitle() << ")" << std::endl;
  std::cout << "==========================================================================\n" << std::endl;
}

#endif
