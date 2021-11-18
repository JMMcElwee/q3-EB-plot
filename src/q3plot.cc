#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <sys/stat.h>

#include "TGraph.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TText.h"
#include "TF1.h"

#include "simulation.h" 


int main(int argc, char *argv[]){

  // === COMMAND LINE FLAGS ==============================================

  // --- Default Files -----
  bool is2P2H = false;

  bool isALPHA = false;
  int alphaFile; 

  bool isRFG = false;

  bool isSF = true;
  int SF_thing = 1;

  bool isNuWro = false;
  int nuwroOP = 0;

  bool isCCQE = false;

  std::string _saving = "/home/jmcelwee/T2K/ANALYSIS/q3corr/plots/";

  // --- Read command line -----
  int argCount = 0;
  int opt;
  while ((opt = getopt(argc, argv, ":hqc:gRS:n:d:")) != -1){
    switch (opt)
      {
      case 'h':
	//	help();
	return 0;
      case 'g':
	is2P2H = true;
	break;
      case 'q':
	isCCQE = true;
	break;
      case 'c':
	isALPHA = true;
	alphaFile = std::stoi(optarg);
	break;
      case 'S':
	SF_thing = std::stoi(optarg);
	if (!SF_thing) isSF = false;
	break;
      case 'R':
	isRFG = true;
	break;
      case 'n':
	isNuWro = true;
	nuwroOP = std::stoi(optarg);
	break;
      case 'd':
	_saving = optarg;
	break;
      case ':':
	printf("\033[1;31m[ERROR]\033[0m -%c requires an argument.\n",optopt);
	return 0;
      case '?':
	printf("\033[1;33m[ERROR]\033[0m -%c is an unknown argument... just ignoring it.\n",optopt);
	break;
      }
  }
  
  // ===================================================================== 



  // === Fill Vectors ==================================================== 

  std::string addFile;
  Simulation sf, rfg, nuwro, nuwro_OP, sf_alpha, sf_2p2h, sf_2p2h_alpha, sf_CCQE;
  int simCount = 0;


  if (isSF && !isALPHA && !is2P2H && !isCCQE) {
    sf.SetFile("SF");
    sf.FillVectors();
    sf.Fit();
    simCount++;
  }

  if (isSF && !isALPHA && !is2P2H && isCCQE) {
    sf_CCQE.SetFile("SF_CCQE");
    sf_CCQE.FillVectors();
    sf_CCQE.Fit();
    simCount++;
  }

  if (isSF && isALPHA && !is2P2H && !isCCQE){
    sf_alpha.SetFile("SF_alpha");
    sf_alpha.FillVectors();
    sf_alpha.Fit();
    simCount++;
  }

  if (isRFG){
    rfg.SetFile("RFG");
    rfg.FillVectors();
    rfg.Fit();
    simCount++;
  } 

  if (isSF && !isALPHA && is2P2H){
    sf_2p2h.SetFile("SF_2p2h");
    sf_2p2h.FillVectors();
    sf_2p2h.Fit();
    simCount++;
  }

  if (isSF && isALPHA && is2P2H){
    sf_2p2h_alpha.SetFile("SF_2p2h_alpha");
    sf_2p2h_alpha.FillVectors();
    sf_2p2h_alpha.Fit();
    simCount++;
  }
  
  if (isNuWro && !nuwroOP){
    nuwro.SetFile("nuwro");
    nuwro.FillVectors();
    nuwro.Fit();
    simCount++;
  }

  if (isNuWro && nuwroOP){
    nuwro_OP.SetFile("SF_nuwro_OP");
    nuwro_OP.FillVectors();
    nuwro_OP.Fit();
    simCount++;
  }
  
  // ===================================================================== 


  // === Plotting ======================================================== 

  // --- Setup Canvas -----
  TCanvas c1("c1","",800,600);
  c1.cd();
  gPad->SetLeftMargin(0.13);
  gPad->SetRightMargin(0.04);
  gPad->SetTopMargin(0.04);
  gPad->SetBottomMargin(0.09);


  // --- Graph style -----
  float xAx[2] = {0,0.9};
  float yAx[2] = {-0.04,0.02};
  TGraph *blankCanv = new TGraph(2,xAx,yAx);
  blankCanv->SetMarkerColor(0);
  blankCanv->Draw("AP");
  blankCanv->SetTitle(";q_{3} [GeV];#Delta E_{B} [GeV]");
  float height = 0.35;

  // --- Run Plotting -----
  if (isSF && !isALPHA && !is2P2H && !isCCQE) {
    sf.GetQ3EB()->Draw("Psame");
    sf.Plot(_saving);
    sf.FormatPlot(20,0.5,2);
    sf.PrintInformation(height);
    height -= 0.1;
  }
  if (isSF && !isALPHA && !is2P2H && isCCQE) {
    sf_CCQE.GetQ3EB()->Draw("Psame");
    sf_CCQE.Plot(_saving);
    sf_CCQE.FormatPlot(20,0.5,2);
    sf_CCQE.PrintInformation(height);
    height -= 0.1;
  }
  if (isSF && isALPHA && !is2P2H){
    sf_alpha.GetQ3EB()->Draw("Psame");
    sf_alpha.Plot(_saving);
    sf_alpha.FormatPlot(22,0.5,4);
    sf_alpha.PrintInformation(height);
    height -= 0.1;
  }
  if (isRFG){
    rfg.GetQ3EB()->Draw("Psame");
    rfg.Plot(_saving);
    rfg.FormatPlot(21,0.5,9);
    rfg.PrintInformation(height);
    height -= 0.1;
  } 
  if (isSF && !isALPHA && is2P2H){
    sf_2p2h.GetQ3EB()->Draw("Psame");
    sf_2p2h.Plot(_saving);
    sf_2p2h.FormatPlot(23,0.5,6);
    sf_2p2h.PrintInformation(height);
    height -= 0.1;
  }
  if (isSF && isALPHA && is2P2H){
    sf_2p2h_alpha.GetQ3EB()->Draw("Psame");
    sf_2p2h_alpha.Plot(_saving);
    sf_2p2h_alpha.FormatPlot(22,0.5,4);
    sf_2p2h_alpha.PrintInformation(height);
    height -= 0.1;
  }
  if (isNuWro && !nuwroOP){
    nuwro.GetQ3EB()->Draw("Psame");
    nuwro.Plot(_saving);
    nuwro.FormatPlot(21,0.5,9);
    nuwro.PrintInformation(height);
    height -= 0.1;
  }
  if (isNuWro && nuwroOP){
    nuwro_OP.GetQ3EB()->Draw("Psame");
    nuwro_OP.Plot(_saving);
    nuwro_OP.FormatPlot(24,0.5,8);
    nuwro_OP.PrintInformation(height);
    height -= 0.1;
  }

  
  // --- Legend Formatting -----
  /*  TLegend *leg11 = new TLegend(0.2,0.77,0.34,0.9);
  leg11->AddEntry(q3Plot_norm, "SF","p");
  leg11->AddEntry(q3Plot_RFG, "RFG","p");
  leg11->Draw(); */



  // --- Save Multigraph -----
  if (isSF && !isRFG && !isNuWro && !isCCQE) _saving += "SF";
  else if (isSF && !isRFG && !isNuWro && isCCQE) _saving += "SF_CCQE";
  else if (!isSF && isRFG && !isNuWro) _saving += "RFG";
  else if (isSF && isRFG && !isNuWro) _saving += "SF_RFG";
  else if (!isSF && !isRFG && isNuWro) {
    if (nuwroOP) _saving += "nuwro_OP";
    else if (!nuwroOP) _saving += "nuwro";
  }
  else if (isSF && !isRFG && isNuWro) {
    if (nuwroOP) _saving += "SF_nuwro_OP";
    else if (!nuwroOP) _saving += "SF_nuwro";
  }
  else if (!isSF && isRFG && isNuWro) {
    if (nuwroOP) _saving += "RFG_nuwro_OP";
    else if (!nuwroOP) _saving += "RFG_nuwro";
  }
  else if (isSF && isRFG && isNuWro) {
    if (nuwroOP) _saving += "SF_RFG_nuwro_OP";
    else if (!nuwroOP) _saving += "SF_RFG_nuwro";
  }
  if (is2P2H) _saving += "_2p2h";
  if (isALPHA) _saving += "_alpha";


  
  c1.SaveAs((_saving+".pdf").c_str());
  
  // =====================================================================   

  return 0;

}


int exist(const std::string &name){
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}


  /*

  std::transform(shift_norm.begin(),shift_norm.end(),shift_RFG.begin(),std::back_inserter(difference),[](float shift_norm, float shift_RFG) {return shift_RFG - shift_norm;});

  TGraphErrors *diff_plot = new TGraphErrors(shift_RFG.size(), &q3_RFG[0], &difference[0],0,0);
  diff_plot->SetMarkerStyle(2);
  diff_plot->SetMarkerSize(1);

  

  TCanvas c3("c3","",80,30);
  //  TCanvas c3("c3","");
  c3.cd();
  gPad->SetLeftMargin(0.18);
  gPad->SetRightMargin(0.04);
  gPad->SetTopMargin(0.04);
  gPad->SetBottomMargin(0.15);

  //  diff_plot->Fit("pol1","","",0.1,0.97);
  diff_plot->GetXaxis()->SetLimits(0,1.0);
  //diff_plot->GetYaxis()->SetRangeUser(-0.040,0.020);
  diff_plot->SetTitle(";q_{3} [GeV];#Delta #Delta E_{B} [GeV]");
  diff_plot->Draw("AP");
  c3.SaveAs("SF_RFG_2p2h_abs.pdf");


  TCanvas paddy("paddy","",900,1100);
  //  paddy.Divide(1,2);
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.32, 1, 1.0);
  pad1->SetBottomMargin(0);
  pad1->SetLeftMargin(0.13);
  pad1->SetTopMargin(0.04);
  pad1->SetRightMargin(0.04);
  pad1->Draw();
  pad1->cd();

  gStyle->SetOptStat(0);
  q3Plot_norm->GetXaxis()->SetTitleFont(43);
  q3Plot_norm->GetYaxis()->SetTitleFont(43);
  q3Plot_norm->GetXaxis()->SetTitleSize(22);
  q3Plot_norm->GetYaxis()->SetTitleSize(22);
  q3Plot_norm->GetXaxis()->SetTitleOffset(3);
  q3Plot_norm->GetYaxis()->SetTitleOffset(2.5);
  q3Plot_norm->GetXaxis()->SetLabelFont(43);
  q3Plot_norm->GetYaxis()->SetLabelFont(43);
  q3Plot_norm->GetXaxis()->SetLabelSize(20);
  q3Plot_norm->GetYaxis()->SetLabelSize(20);

  q3Plot_norm->SetMarkerColor(2);
  q3Plot_RFG->SetMarkerColor(4);
  q3Plot_RFG->GetFunction("pol1")->SetLineColor(4);

  /*  q3Plot_RFG->GetXaxis()->SetTitleFont(43);
  q3Plot_RFG->GetYaxis()->SetTitleFont(43);
  q3Plot_RFG->GetXaxis()->SetTitleSize(6);
  q3Plot_RFG->GetYaxis()->SetTitleSize(6);
  q3Plot_RFG->GetXaxis()->SetLabelSize(4);
  q3Plot_RFG->GetYaxis()->SetLabelSize(4);
   

  q3Plot_norm->SetMarkerStyle(20);
  q3Plot_RFG->SetMarkerStyle(22);

  q3Plot_norm->GetYaxis()->SetRangeUser(-0.045,0.030);
  q3Plot_norm->Draw("AP");
  q3Plot_RFG->Draw("P same");

  TLegend *leg11 = new TLegend(0.2,0.77,0.34,0.9);
  leg11->AddEntry(q3Plot_norm, "SF","p");
  leg11->AddEntry(q3Plot_RFG, "RFG","p");
  leg11->Draw();

  char print_c_n2[40];
  sprintf(print_c_n2, "SF: c = %0.4f \x00B1 %0.4f", fit_c_norm,fit_cE_norm);
  char print_m_n2[40];
  sprintf(print_m_n2, "      m = %0.4f \x00B1 %0.4f", fit_m_norm,fit_mE_norm);
  char print_c_22[40];
  sprintf(print_c_22, "RFG: c = %0.4f \x00B1 %0.4f", fit_c_RFG,fit_cE_RFG);
  char print_m_22[40];
  sprintf(print_m_22, "         m = %0.4f \x00B1 %0.4f", fit_m_RFG,fit_mE_RFG);

  TText *t12 = new TText(0.67,0.3,print_c_n2);
  TText *t22 = new TText(0.67,0.26,print_m_n2);
  t12->SetNDC();
  t12->SetTextSize(22);
  t12->SetTextFont(43);
  t12->Draw();
  t22->SetNDC();
  t22->SetTextSize(22);
  t22->SetTextFont(43);
  t22->Draw();

  TText *t32 = new TText(0.65,0.2,print_c_22);
  TText *t42 = new TText(0.65,0.16,print_m_22);
  t32->SetNDC();
  t32->SetTextSize(22);
  t32->SetTextFont(43);
  t32->Draw();
  t42->SetNDC();
  t42->SetTextSize(22);
  t42->SetTextFont(43);
  t42->Draw();

  paddy.cd();


  TPad *pad2 = new TPad("pad1", "pad1", 0, 0, 1, 0.32);
  pad2->SetTopMargin(0);
  pad2->SetLeftMargin(0.13);
  pad2->SetRightMargin(0.04);
  pad2->SetBottomMargin(0.14);
  pad2->SetBorderMode(0);
  pad2->SetBorderSize(2);
  pad2->SetFrameBorderMode(0);
  pad2->Draw();
  pad2->cd();

  gStyle->SetOptStat(0);
  gStyle->SetPadBottomMargin(0.1);
  gROOT->ForceStyle();
  diff_plot->GetXaxis()->SetTitleFont(43);
  diff_plot->GetYaxis()->SetTitleFont(43);
  diff_plot->GetXaxis()->SetTitleSize(22);
  diff_plot->GetYaxis()->SetTitleSize(22);
  diff_plot->GetYaxis()->CenterTitle();
  diff_plot->GetXaxis()->SetTitleOffset(3);
  diff_plot->GetYaxis()->SetTitleOffset(2.5);
  diff_plot->GetXaxis()->SetLabelFont(43);
  diff_plot->GetYaxis()->SetLabelFont(43);
  diff_plot->GetXaxis()->SetLabelSize(20);
  diff_plot->GetYaxis()->SetLabelSize(20);

  diff_plot->GetYaxis()->SetRangeUser(-0.01,0.023);
  diff_plot->Draw("AP");

  //  paddy.SaveAs("thisISNTatest.pdf");


  /*  paddy.cd(1);
  gPad->SetBottomMargin(0.0001);
  gPad->SetRightMargin(0.04);
  gPad->SetTopMargin(0.04);  

  q3Plot_RFG->Fit("pol1","","",0.1,0.97);
  q3Plot_RFG->GetXaxis()->SetLimits(0,1.0);
  q3Plot_RFG->GetYaxis()->SetRangeUser(-0.040,0.020);
  q3Plot_RFG->SetTitle(";q_{3} [GeV];#Delta E_{B} [GeV]");
  q3Plot_RFG->Draw("AP");


  paddy.cd(2);
  gPad->SetTopMargin(0.0001);
  gPad->SetRightMargin(0.04);
  gPad->SetBottomMargin(0.15);

  diff_plot->GetXaxis()->SetLimits(0,1.0);
  diff_plot->SetTitle(";q_{3} [GeV];#Delta #Delta E_{B} [GeV]");
  diff_plot->Draw("AP");

  c1.Update();

  paddy.SaveAs("tester.pdf");*/



