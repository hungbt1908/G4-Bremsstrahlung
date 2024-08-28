void analysis()
{
    gROOT->Reset();
	gROOT->SetStyle("Plain");

    // open ROOT file
    TFile* f = new TFile("output.root", "READ");
    f->ls(); // list all trees

    // open trees
    TTree* tree = (TTree*)f->Get("positron;1");
    tree->Print(); // print branches of the tree

    Char_t parName[30]; 
    Int_t eventID, trackID, stepNumber, parentID;
    Double_t xPos, yPos, zPos;
    Double_t brem_kinetic;

    // set branches
    tree->SetBranchAddress("xPos", &xPos);
	tree->SetBranchAddress("yPos", &yPos);
	tree->SetBranchAddress("zPos", &zPos);
    tree->SetBranchAddress("kinetic", &brem_kinetic);

    TH1D* brem_kinetic_hist = new TH1D("Bremsstrahlung Energy", "Bremsstrahlung Energy", 1000, 0., 1.1);

    int nEntries = tree->GetEntries();
	for(int i=0; i<nEntries; ++i)
	{
		tree->GetEntry(i);
		brem_kinetic_hist->Fill(brem_kinetic);
	}


    // create canvas
	TCanvas* c1 = new TCanvas("c1", "c1", 1200, 800);

    // draws
    c1->cd();
	//gPad->SetLogy();
	gPad->SetGrid();
	brem_kinetic_hist->SetTitle("Bremsstrahlung Kinetic Spectrum");
	brem_kinetic_hist->GetXaxis()->CenterTitle(true);
	brem_kinetic_hist->GetYaxis()->CenterTitle(true);
	brem_kinetic_hist->GetXaxis()->SetTitle("MeV");
	brem_kinetic_hist->GetYaxis()->SetTitle("Count");
	brem_kinetic_hist->SetLineColor(kRed);
	brem_kinetic_hist->SetLineWidth(1);
	brem_kinetic_hist->SetStats(kFALSE);
	brem_kinetic_hist->Draw("P");
	brem_kinetic_hist->SetMarkerStyle(6);
	brem_kinetic_hist->SetMarkerSize(1);
	brem_kinetic_hist->SetMarkerColor(4);

}