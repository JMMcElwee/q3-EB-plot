#ifndef SIMULATION_H
#define SIMULATION_H

#include <sys/stat.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "TGraphErrors.h"
#include "TF1.h"
#include "TText.h"
#include "TCanvas.h"
#include "TPad.h"



class Simulation
{

  // --- File Names -----
  std::string m_file {};
  std::string m_savename {};

  // --- Variable Names -----
  std::vector<float> m_energy {};
  std::vector<float> m_angle {};
  std::vector<float> m_q3 {};
  std::vector<float> m_shift {};

  // --- Graphs -----
  TGraphErrors *m_q3Graph {};
  TF1 *m_fitGraph {};

  // --- Fit parameters ----- 
  double m_fitGrad[2] {};
  double m_fitIntercept[2] {};
  TText *m_intercept {};
  TText *m_gradient {};
  


public:

  // --- Get Variables -----
  std::vector<float> GetEnergy(){
    return m_energy;
  }
  std::vector<float> GetAngle(){
    return m_angle;
  }
  std::vector<float> GetQ3(){
    return m_q3;
  }
  std::vector<float> GetEBShift(){
    return m_shift;
  }

  // --- Get Graphs -----
  TGraphErrors *GetQ3EB(){
    return m_q3Graph;
  }
  TF1 *GetFit(){
    return m_fitGraph;
  }

  // --- Get Fit Parameters -----
  double *GetGrad(){
    return m_fitGrad;
  }
  double *GetIntercept(){
    return m_fitIntercept;
  }
  void PrintIntercept(){
    m_intercept->Draw();
  }
  void PrintGradient(){
    m_gradient->Draw();
  }

  // --- Forward Declarations ----- 
  void FillVectors();
  void SetFile(std::string filename);
  void Fit();
  void FormatPlot(int style, float size, int colour);
  void Plot(std::string _directory);
  void PrintInformation(float height);

};


#endif
