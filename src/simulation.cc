#include <sys/stat.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "TGraphErrors.h"
#include "TAxis.h"
#include "TF1.h"
#include "TText.h"
#include "TCanvas.h"
#include "TPad.h"

#include "simulation.h"


// ==================================================================

void Simulation::SetFile(std::string filename){
  m_file = "/home/jmcelwee/T2K/ANALYSIS/basic/plots/" + filename + ".txt";
  m_savename = filename;
}

// ==================================================================


// ==================================================================

void Simulation::FillVectors(){
  std::ifstream fnorm(m_file.c_str());
  std::string line;
  getline(fnorm,line);
  
  
  while(getline(fnorm,line)){
    std::stringstream line_stream(line);
    std::string entry;
    std::vector<std::string> entries;
    char delim = '\t';
    
    while(getline(line_stream, entry, delim)){
      entries.push_back(entry);
    }
    
    if (std::stof(entries.at(3)) < 0.1){
      m_energy.push_back(std::stof(entries.at(0)));
      m_angle.push_back(std::stof(entries.at(1)));
      m_q3.push_back(std::stof(entries.at(2)));
      m_shift.push_back(std::stof(entries.at(3)));
      }
  }

  TGraphErrors *tempPlot = new TGraphErrors(m_shift.size(),&m_q3[0],&m_shift[0],0,0);
  m_q3Graph = (TGraphErrors*)tempPlot->Clone();
}

// ==================================================================


// ==================================================================

void Simulation::Fit(){
  m_q3Graph->Fit("pol1","","",0.1,0.95);
  m_fitGraph = (TF1*) m_q3Graph->GetFunction("pol1")->Clone();
  
  m_fitIntercept[0] = m_fitGraph->GetParameter(0);
  m_fitGrad[0] = m_fitGraph->GetParameter(1);
  m_fitIntercept[1] = m_fitGraph->GetParError(0);
  m_fitGrad[1] = m_fitGraph->GetParError(1);
}

// ==================================================================


// ==================================================================

void Simulation::FormatPlot(int style, float size, int colour){
  m_q3Graph->SetMarkerStyle(style);
  m_q3Graph->SetMarkerSize(size);
  m_q3Graph->SetMarkerColor(colour);
  m_q3Graph->GetFunction("pol1")->SetLineColor(colour);

}

// ==================================================================


// ==================================================================

void Simulation::Plot(std::string _directory){
  TCanvas paddy("paddy","");
  paddy.cd();
  gPad->SetLeftMargin(0.13);
  gPad->SetRightMargin(0.04);
  gPad->SetTopMargin(0.04);
  gPad->SetBottomMargin(0.09);
  
  m_q3Graph->SetMarkerStyle(20);
  m_q3Graph->SetMarkerSize(0.5);
  m_q3Graph->GetXaxis()->SetLimits(0,1);
  m_q3Graph->GetYaxis()->SetRangeUser(-0.045,0.025);
  m_q3Graph->Draw("AP");
  m_q3Graph->SetTitle(";q_{3} [GeV];#Delta E_{B} [GeV]");
  
  PrintInformation(0.3);
  
  paddy.SaveAs((_directory + m_savename + ".pdf").c_str());
}

// ==================================================================


// ==================================================================

void Simulation::PrintInformation(float height){
  
  char PrintC[40];
  sprintf(PrintC, "c = %0.4f \x00B1 %0.4f", m_fitIntercept[0],m_fitIntercept[1]);
  char PrintM[40];
  sprintf(PrintM, "m = %0.4f \x00B1 %0.4f", m_fitGrad[0],m_fitGrad[1]);
  
  TText *temp_int = new TText(0.65,height,PrintC);
  temp_int->SetNDC();
  temp_int->SetTextSize(20);
  temp_int->SetTextFont(43);
  m_intercept = temp_int;
  PrintIntercept();
  
  
  TText *temp_grad = new TText(0.65,height-0.035,PrintM);
  temp_grad->SetNDC();
  temp_grad->SetTextSize(20);
  temp_grad->SetTextFont(43);
  m_gradient = temp_grad;
  PrintGradient();
} 

// ==================================================================
