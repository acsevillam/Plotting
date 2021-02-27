// ROOT Headers
#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"

#include <map>
#include <iostream>
#include <string>

using namespace std;

void plot_05(){

	gStyle->SetOptStat(0);

	// Draw histos filled by Geant4 simulation
	//
	map<TString,TFile*> FileCollection;
	map<TString,TFile*>::iterator FileCollectionIt;

	FileCollection["Au"] 		= new TFile("Au/20nm.root");
	FileCollection["Gd"]		= new TFile("Gd/20nm.root");

	map<TString,Int_t> ColorCollection;

	ColorCollection["Au"] 		= kBlue;
	ColorCollection["Gd"] 		= kRed;

	map<Int_t,TString> VariableNameCollection;

	VariableNameCollection[1]	="SecondariesTrackLength";
	VariableNameCollection[2]	="SecondariesRange";

	TCanvas* c1 = new TCanvas("c1", "c1", 800, 600);
	c1->Divide(2,1);

	map<TString,TH1D*> h;
	TString HistogramName("histograms/");

	Double_t MaximunBinContent, Integral, nEntries;

	// --- SecondariesTrackLength ---

	c1->cd(1);
	c1->cd(1)->SetLeftMargin(0.15);
	c1->cd(1)->SetLogy(true);
	c1->cd(1)->SetGrid(true,true);
	c1->cd(1)->SetTicks(true,true);

	TString HistogramName1 = HistogramName+VariableNameCollection[1];

	MaximunBinContent = 0;

	TLegend* l1 = new TLegend(0.55, 0.45, 0.85, 0.85) ;

	for (FileCollectionIt = FileCollection.begin() ; FileCollectionIt != FileCollection.end(); ++FileCollectionIt){

		h[FileCollectionIt->first] = static_cast<TH1D*>(FileCollectionIt->second->Get(HistogramName1.Data()));
		h[FileCollectionIt->first]->Rebin(10);
		h[FileCollectionIt->first]->SetLineColor(ColorCollection[FileCollectionIt->first]);

		Integral = h[FileCollectionIt->first]->Integral();
		h[FileCollectionIt->first]->Scale(1./Integral);

		h[FileCollectionIt->first]->Draw("HIST same");

		if(h[FileCollectionIt->first]->GetBinContent(h[FileCollectionIt->first]->GetMaximumBin())>MaximunBinContent)
			MaximunBinContent = h[FileCollectionIt->first]->GetBinContent(h[FileCollectionIt->first]->GetMaximumBin());

		nEntries = h[FileCollectionIt->first]->GetEntries();

		TString legend_entry("");
		legend_entry+=FileCollectionIt->first.Data();
		//legend_entry+=" (";
		//legend_entry+=to_string(Int_t(nEntries));
		//legend_entry+=")";

		l1->AddEntry(h[FileCollectionIt->first], legend_entry.Data(), "L") ;
		l1->Draw() ;

	}

	for (FileCollectionIt = FileCollection.begin() ; FileCollectionIt != FileCollection.end(); ++FileCollectionIt){
		h[FileCollectionIt->first]->SetAxisRange(0,10,"X");
		h[FileCollectionIt->first]->SetAxisRange(1E-4,MaximunBinContent*2,"Y");
		h[FileCollectionIt->first]->GetXaxis()->SetTitleOffset(1.2);
		h[FileCollectionIt->first]->GetYaxis()->SetTitleOffset(1.8);
		h[FileCollectionIt->first]->SetTitle("");
		h[FileCollectionIt->first]->SetXTitle("Secondary e- track lengh [um]");
		h[FileCollectionIt->first]->SetYTitle("Relative counts [%]");
		h[FileCollectionIt->first]->SetLineWidth(2.0);
	}

	// --- End SecondariesTrackLength ---

	// --- SecondariesRange ---

	c1->cd(2);
	c1->cd(2)->SetLeftMargin(0.15);
	c1->cd(2)->SetLogy(true);
	c1->cd(2)->SetGrid(true,true);
	c1->cd(2)->SetTicks(true,true);

	TString HistogramName2=HistogramName+VariableNameCollection[2];

	MaximunBinContent = 0;

	TLegend* l2 = new TLegend(0.55, 0.45, 0.85, 0.85) ;

	for (FileCollectionIt = FileCollection.begin() ; FileCollectionIt != FileCollection.end(); ++FileCollectionIt){

		h[FileCollectionIt->first] = static_cast<TH1D*>(FileCollectionIt->second->Get(HistogramName2.Data()));
		h[FileCollectionIt->first]->Rebin(10);
		h[FileCollectionIt->first]->SetLineColor(ColorCollection[FileCollectionIt->first]);

		Integral = h[FileCollectionIt->first]->Integral();
		h[FileCollectionIt->first]->Scale(1./Integral);

		h[FileCollectionIt->first]->Draw("HIST same");

		if(h[FileCollectionIt->first]->GetBinContent(h[FileCollectionIt->first]->GetMaximumBin())>MaximunBinContent)
			MaximunBinContent = h[FileCollectionIt->first]->GetBinContent(h[FileCollectionIt->first]->GetMaximumBin());

		nEntries = h[FileCollectionIt->first]->GetEntries();

		TString legend_entry("");
		legend_entry+=FileCollectionIt->first.Data();
		//legend_entry+=" (";
		//legend_entry+=to_string(Int_t(nEntries));
		//legend_entry+=")";

		l2->AddEntry(h[FileCollectionIt->first], legend_entry.Data(), "L") ;
		l2->Draw() ;

	}

	for (FileCollectionIt = FileCollection.begin() ; FileCollectionIt != FileCollection.end(); ++FileCollectionIt){
		h[FileCollectionIt->first]->SetAxisRange(0,10,"X");
		h[FileCollectionIt->first]->SetAxisRange(1E-4,MaximunBinContent*2,"Y");
		h[FileCollectionIt->first]->GetXaxis()->SetTitleOffset(1.2);
		h[FileCollectionIt->first]->GetYaxis()->SetTitleOffset(2.0);
		h[FileCollectionIt->first]->SetTitle("");
		h[FileCollectionIt->first]->SetXTitle("Secondary e- range [um]");
		h[FileCollectionIt->first]->SetYTitle("Relative counts [%]");
		h[FileCollectionIt->first]->SetLineWidth(2.0);
	}

	// --- End SecondariesRange ---

	c1->Print("plot_05.png");

}  
