{
Float_t x,y,z,e,p,px, py,pz,m,ch,pid,pt ,eta,cent;
TH1F *ptpiH = new TH1F("ptpi","",100,0,10);
TH1F *ptantipiH = new TH1F("ptantipi","",100,0,10);
TH1F *ptpH = new TH1F("ptp","",100,0,10);
TH1F *ptantipH = new TH1F("ptantip","",100,0,10);
TH1F *ptkH = new TH1F("ptk","",100,0,10);
TH1F *ptantikH = new TH1F("ptantik","",100,0,10);
TH1F *ptlH = new TH1F("ptl","",100,0,10);
TH1F *ptantilH = new TH1F("ptantil","",100,0,10);

gROOT->Reset();
TChain mychain("T");
TChain mychain2("particles");
mychain.Add("output/pid.root"); //archivo a leer 500*20

 Int_t nev=1000;
struct particula_t
{
Float_t time,X,Y,Z,E,Px,Py,Pz,Pt,P,Eta,m,id,isoespin,charge,lastcol\
l,numbercoll,history,frezetime,frezeX,frezeY,frezeZ,frezeE,frezePx;
    Float_t frezePy,frezePz,frezePt,frezeP,frezeEta,b,bmin,bmax,sigma;
  } PARTICLE;

particula_t  particle;

mychain.SetBranchAddress("particle",&particle);

Int_t nevent = mychain.GetEntries();
ofstream myfile;
    myfile.open ("output/pid.csv");
    myfile << "x,y,z,e,p,px,py,pz,m,ch,pid,pt,eta\n";


for (Int_t i=0;i<nevent;i++)
{
	mychain.GetEvent(i);
  if(particle.numbercoll==0)continue;//protones participantes
	myfile << x << "," << y << "," << z << "," << e << "," << p << "," << px << ","<< py << "," << pz << "," << m 
	<< "," << ch << "," << pid << "," << pt << "," << eta << "\n"; 
    
	p = particle.P;
	e = particle.E;
	x = particle.X;
	y = particle.Y;
	z = particle.Z;
	px = particle.Px;
	py = particle.Py;
	pz = particle.Pz;
	pt = particle.Pt;
    eta = particle.Eta;
	pid = particle.id;
	ch = particle.charge;
	cent = particle.b;
	m = particle.m;

	if(TMath::Abs(eta) >0.5)continue;
	if(TMath::Abs(pt) <0.5)continue;
	if(particle.id == 1) ptpH->Fill(pt,Float_t (1/pt));
	if(particle.id == -1) ptantipH->Fill(pt,Float_t (1/pt));
	if(particle.id == 101 && particle.charge ==1) ptpiH->Fill(pt,Float_t (1/pt));
	if(particle.id == 101 && particle.charge ==-1) ptantipiH->Fill(pt,Float_t (1/pt));
	if(particle.id == 106) ptkH->Fill(pt,Float_t (1/pt));
	if(particle.id == -106) ptantikH->Fill(pt,Float_t (1/pt));
	if(particle.id == 27 ) ptlH->Fill(pt,Float_t (1/pt));
	if(particle.id == -27 ) ptantilH->Fill(pt,Float_t (1/pt));

	}
myfile.close();

/*TCanvas* c1 = new TCanvas("c1","",800,800);
gStyle->SetOptStat(false);
c1->SetRightMargin(0.05);
c1->SetTopMargin(0.1);
c1->SetFillColor(0);
//c1->SetLogy();
c1->Divide(2,3);
c1->cd(1);
gPad->SetLogy();
ptpH->Scale(10/(Float_t(nev)));
ptpH->Draw();
ptpH->SetXTitle("p_{T} [GeV]");
ptpH->GetXaxis()->CenterTitle(true);
ptpH->GetXaxis()->SetTitleSize(0.04);
ptpH->GetXaxis()->SetLabelSize(0.03);
ptpH->GetXaxis()->SetTitleOffset(1.2);
ptpH->SetYTitle("1/N_{ev} dN/dp_{T}");
ptpH->GetYaxis()->CenterTitle(true);
ptpH->GetYaxis()->SetTitleSize(0.04);
ptpH->GetYaxis()->SetLabelSize(0.03);
ptpH->GetYaxis()->SetTitleOffset(1.2);
ptpH->GetYaxis()->SetRangeUser(0.00001,10000);
ptpH->GetXaxis()->SetRangeUser(0.5,5);
TLegend *leg = new TLegend(0.35,0.6,0.88,0.88);
leg->SetTextFont(62);
leg->SetTextSize(0.025);
leg->SetLineColor(0);
leg->SetLineStyle(0);
leg->SetLineWidth(1);
leg->SetFillColor(0);
leg->SetFillStyle(1001);
leg->AddEntry("","Proton","");
leg->AddEntry(ptpH,"UrQMD Au+Au #sqrt{s_{NN}}=7.7 GeV","l");
leg->Draw();

c1->cd(2);
gPad->SetLogy();
ptantipH->Scale(10/(Float_t(nev)));
ptantipH->Draw("");
ptantipH->SetXTitle("p_{T} [GeV]");
ptantipH->GetXaxis()->CenterTitle(true);
ptantipH->GetXaxis()->SetTitleSize(0.04);
ptantipH->GetXaxis()->SetLabelSize(0.03);
ptantipH->GetXaxis()->SetTitleOffset(1.2);
ptantipH->SetYTitle("1/N_{ev} dN/dp_{T}");
ptantipH->GetYaxis()->CenterTitle(true);
ptantipH->GetYaxis()->SetTitleSize(0.04);
ptantipH->GetYaxis()->SetLabelSize(0.03);
ptantipH->GetYaxis()->SetTitleOffset(1.2);
ptantipH->GetYaxis()->SetRangeUser(0.00001,10000);
ptantipH->GetXaxis()->SetRangeUser(0.5,5);
TLegend *leg1 = new TLegend(0.35,0.6,0.88,0.88);
leg1->SetTextFont(62);
leg1->SetTextSize(0.025);
leg1->SetLineColor(0);
leg1->SetLineStyle(0);
leg1->SetLineWidth(1);
leg1->SetFillColor(0);
leg1->SetFillStyle(1001);
leg1->AddEntry("","Anti Proton","");
leg1->AddEntry(ptantipH,"UrQMD Au+Au #sqrt{s_{NN}}=7.7 GeV","l");
leg1->Draw();

c1->cd(3);
gPad->SetLogy();
ptpiH->Scale(10/(Float_t(nev)));
ptpiH->Draw("");
ptpiH->SetXTitle("p_{T} [GeV]");
ptpiH->GetXaxis()->CenterTitle(true);
ptpiH->GetXaxis()->SetTitleSize(0.04);
ptpiH->GetXaxis()->SetLabelSize(0.03);
ptpiH->GetXaxis()->SetTitleOffset(1.2);
ptpiH->SetYTitle("1/N_{ev} dN/dp_{T}");
ptpiH->GetYaxis()->CenterTitle(true);
ptpiH->GetYaxis()->SetTitleSize(0.04);
ptpiH->GetYaxis()->SetLabelSize(0.03);
ptpiH->GetYaxis()->SetTitleOffset(1.2);
ptpiH->GetYaxis()->SetRangeUser(0.00001,10000);
ptpiH->GetXaxis()->SetRangeUser(0.5,5);
TLegend *leg2 = new TLegend(0.35,0.6,0.88,0.88);
leg2->SetTextFont(62);
leg2->SetTextSize(0.025);
leg2->SetLineColor(0);
leg2->SetLineStyle(0);
leg2->SetLineWidth(1);
leg2->SetFillColor(0);
leg2->SetFillStyle(1001);
leg2->AddEntry("","Pion","");
leg2->AddEntry(ptpiH,"UrQMD Au+Au #sqrt{s_{NN}}=7.7 GeV","l");
leg2->Draw();

c1->cd(4);
gPad->SetLogy();
ptantipiH->Scale(10/(Float_t(nev)));
ptantipiH->Draw("");
ptantipiH->SetXTitle("p_{T} [GeV]");
ptantipiH->GetXaxis()->CenterTitle(true);
ptantipiH->GetXaxis()->SetTitleSize(0.04);
ptantipiH->GetXaxis()->SetLabelSize(0.03);
ptantipiH->GetXaxis()->SetTitleOffset(1.2);
ptantipiH->SetYTitle("1/N_{ev} dN/dp_{T}");
ptantipiH->GetYaxis()->CenterTitle(true);
ptantipiH->GetYaxis()->SetTitleSize(0.04);
ptantipiH->GetYaxis()->SetLabelSize(0.03);
ptantipiH->GetYaxis()->SetTitleOffset(1.2);
ptantipiH->GetXaxis()->SetRangeUser(0.5,5);
ptantipiH->GetYaxis()->SetRangeUser(0.00001,10000);
TLegend *leg3 = new TLegend(0.35,0.6,0.88,0.88);
leg3->SetTextFont(62);
leg3->SetTextSize(0.022);
leg3->SetLineColor(0);
leg3->SetLineStyle(0);
leg3->SetLineWidth(1);
leg3->SetFillColor(0);
leg3->SetFillStyle(1001);
leg3->AddEntry("","Anti Pion","");
leg3->AddEntry(ptantipiH,"UrQMD Au+Au #sqrt{s_{NN}}=7.7 GeV","l");
leg3->Draw();

c1->cd(5);
gPad->SetLogy();
ptlH->Scale(10/(Float_t(nev)));
ptlH->Draw();
ptlH->SetXTitle("p_{T} [GeV]");
ptlH->GetXaxis()->CenterTitle(true);
ptlH->GetXaxis()->SetTitleSize(0.04);
ptlH->GetXaxis()->SetLabelSize(0.03);
ptlH->GetXaxis()->SetTitleOffset(1.2);
ptlH->SetYTitle("1/N_{ev} dN/dp_{T}");
ptlH->GetYaxis()->CenterTitle(true);
ptlH->GetYaxis()->SetTitleSize(0.04);
ptlH->GetYaxis()->SetLabelSize(0.03);
ptlH->GetYaxis()->SetTitleOffset(1.2);
ptlH->GetYaxis()->SetRangeUser(0.00001,1000);
ptlH->GetXaxis()->SetRangeUser(0.5,5);
TLegend *leg4 = new TLegend(0.35,0.6,0.88,0.88);
leg4->SetTextFont(62);
leg4->SetTextSize(0.022);
leg4->SetLineColor(0);
leg4->SetLineStyle(0);
leg4->SetLineWidth(1);
leg4->SetFillColor(0);
leg4->SetFillStyle(1001);
leg4->AddEntry("","Lambda","");
leg4->AddEntry(ptlH,"UrQMD Au+Au #sqrt{s_{NN}}=7.7 GeV","l");
leg4->Draw();

c1->cd(6);
gPad->SetLogy();
ptantilH->Scale(10/(Float_t(nev)));
ptantilH->Draw("");
ptantilH->SetXTitle("p_{T} [GeV]");
ptantilH->GetXaxis()->CenterTitle(true);
ptantilH->GetXaxis()->SetTitleSize(0.04);
ptantilH->GetXaxis()->SetLabelSize(0.03);
ptantilH->GetXaxis()->SetTitleOffset(1.2);
ptantilH->SetYTitle("1/N_{ev} dN/dp_{T}");
ptantilH->GetYaxis()->CenterTitle(true);
ptantilH->GetYaxis()->SetTitleSize(0.04);
ptantilH->GetYaxis()->SetLabelSize(0.03);
ptantilH->GetYaxis()->SetTitleOffset(1.2);
//ptantilH->GetYaxis()->SetRangeUser(0.00001,1000);
//ptantilH->GetXaxis()->SetRangeUser(0.5,5);
TLegend *leg5 = new TLegend(0.35,0.6,0.88,0.88);
leg5->SetTextFont(62);
leg5->SetTextSize(0.022);
leg5->SetLineColor(0);
leg5->SetLineStyle(0);
leg5->SetLineWidth(1);
leg5->SetFillColor(0);
leg5->SetFillStyle(1001);
leg5->AddEntry("","Anti Lambda","");
leg5->AddEntry(ptantilH,"UrQMD Au+Au #sqrt{s_{NN}}=7.7 GeV","l");
leg5->Draw();

c1->SaveAs("UrQMDpid.eps");
c1->SaveAs("UrQMDpid.pdf");
*/
}
