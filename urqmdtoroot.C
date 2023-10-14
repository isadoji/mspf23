#include "Riostream.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TRandom.h"
#include "TTree.h"
#include "TMath.h"
void urqmdtoroot()
{
     ifstream pFile("datasets/test.f14");

    Float_t  time,X,Y,Z,E,Px,Py,Pz,m,id,isoespin,charge,lastcoll,numbercoll,history,frezetime,frezeX,frezeY,frezeZ,frezeE,frezePx,frezePy,frezePz;
    Int_t nlines = 0;

    TFile hfile("output/pid.root","RECREATE","Demo ROOT file with histograms & trees");


    struct particula_t
    {
      Float_t time,X,Y,Z,E,Px,Py,Pz,Pt,P,Eta,m,id,isoespin,charge,lastcoll,numbercoll,history,frezetime,frezeX,frezeY,frezeZ,frezeE,frezePx,frezePy,frezePz,frezePt,frezeP,frezeEta,b,bmin,bmax,sigma;

    } PARTICLE;

    particula_t  particle;


    struct evento_t {Int_t nparticles,nevent;}  EVENT;
    evento_t event;

    TTree *tree = new TTree("T","An example of ROOT tree with a few branches");
    tree->Branch("particle",&particle,"time:X:Y:Z:E:Px:Py:Pz:Pt:P:Eta:m:id:isoespin:charge:lastcoll:numbercoll:history:frezetime:frezeX:frezeY:frezeZ:frezeE:frezePx:frezePy:frezePz:frezePt:frezeP:frezeEta:b:bmin:bmax:sigma");
    tree->Branch("event",&event,"ntrack/I:nevent/I");

    char header;
    float myarray[23];
    Int_t EventNumber= 0;
    Int_t endofevent=0;
    Int_t particlesperevent=0;
    Int_t chargedparticles=0;

    if(pFile.is_open())
      {
	while(!pFile.eof())
	  {
	    std::string str;
	    std::getline(pFile,str);
	    if(str[0] == 'U')
	      {
		if(EventNumber==0)
		  {
		    //particlespervent=0;
		    chargedparticles=0;
		  }
		else
		  {
		    event.nparticles=particlesperevent;
		    event.nevent = EventNumber;
		    //             particlesperevent= 0 ;
		    printf("\n * Event  %d   Number of particles  %d ************************* \n ",EventNumber,event.nparticles);

		  }
		++EventNumber;
		//if(EventNumber>20) break;
		printf("\n ************************** Converting event %d ************************* \n ",EventNumber);
		continue;
	      }
	    if(str[0] == 'p' || str[0] == 't')continue;
	    Float_t b=-999.00, bmin=-999.00, bmax=-999.00, sigma=-999.00;
	    if(str[0] == 'i'){
	      cout<<"b="<<str.substr(37,5)<<"\n";
	      cout<<"bmin="<<str.substr(43,5)<<"\n";
	      cout<<"bmax="<<str.substr(49,5)<<"\n";
	      cout<<"sigma="<<str.substr(87,7)<<"\n";
	      std::stringstream sb(str.substr(37,5));
	      std::stringstream sbmin(str.substr(43,5));
	      std::stringstream sbmax(str.substr(49,5));
	      std::stringstream ssigma(str.substr(87,7));

	      sb>>b;
	      sbmin>>bmin;
	      sbmax>>bmax;
	      ssigma>>sigma;


	      particle.b = b;
	      particle.bmin = bmin;
	      particle.bmax = bmax;
	      particle.sigma = sigma;


	    }
	    if(str[0] == 'e' || str[0] == 'o') continue;
	    std::stringstream ss(str);
	    Int_t position = 0 ;
	    while(ss>>myarray[position])
	      {
		//printf("\n position %d =  %f \n ", position, myarray[position]);
		position++;
	      }

	    //if(myarray[0]==200.00)
	    //{
	    ++particlesperevent;
	    time = myarray[0];
	    X = myarray[1];
	    Y = myarray[2];
	    Z = myarray[3];
	    E = myarray[4];
	    Px = myarray[5];
	    Py = myarray[6];
	    Pz = myarray[7];
	    m = myarray[8];
	    id = myarray[9];
	    isoespin = myarray[10];
	    charge = myarray[11];
	    if(charge>0 || charge <0)++chargedparticles;
	    lastcoll = myarray[12];
	    numbercoll = myarray[13];
	    history = myarray[14];
	    frezetime = myarray[15];
	    frezeX = myarray[16];
	    frezeY = myarray[17];
	    frezeZ = myarray[18];
	    frezeE = myarray[19];
	    frezePx = myarray[20];
	    frezePy = myarray[21];
	    frezePz = myarray[22];
	    //}

	    //Calculate  Eta, Pt, and P
	    Float_t  Eta=-999.00,Pt= -999.0 ,P= -999.0 ,FEta= -999.0 ,FPt= -999.0,FP= -999.0;

	    Pt = TMath::Sqrt(Px*Px+ Py*Py);
	    P = TMath::Sqrt(Px*Px+Py*Py+Pz*Pz);

	    if(TMath::Abs(P- Pz)>0.0000000001)
	      {
		Eta = 0.5*TMath::Log((P+Pz)/(P-Pz));

		if(nlines<5) printf("Eta =  %f \n",Eta);
	      }
	    else continue;

	    FPt = TMath::Sqrt(frezePx*frezePx+ frezePy*frezePy);
	    FP = TMath::Sqrt(frezePx*frezePx+frezePy*frezePy+frezePz*frezePz);


	    if(TMath::Abs(FP-frezePz )>0.000000001)
	      {
		FEta =  0.5*TMath::Log((FP+frezePz )/(FP-frezePz));
	      }

	    particle.time = time;
	    particle.X = X;
	    particle.Y = Y;
	    particle.Z = Z;
	    particle.E = E;
	    particle.Px = Px;
	    particle.Py = Py;
	    particle.Pz = Pz;
	    particle.Pt = Pt;
	    particle.P= P;
	    particle.Eta = Eta;
	    particle.m = m;
	    particle.id = id;
	    particle.isoespin = isoespin ;
	    particle.charge = charge;
	    particle.lastcoll = lastcoll ;
	    particle.numbercoll = numbercoll;
	    particle.history = history;
	    particle.frezetime = frezetime;
	    particle.frezeX = frezeX ;
	    particle.frezeY = frezeY ;
	    particle.frezeZ = frezeZ;
	    particle.frezeE = frezeE;
	    particle.frezePx = frezePx;
	    particle.frezePy = frezePy;
	    particle.frezePz = frezePz;
	    particle.frezePt = FPt;
	    particle.frezeP= FP;
	    particle.frezeEta= FEta;
	    nlines++;
	    //event.nparticles = nlines
	    tree->Fill();
	    if(event.nparticles>0)
	      {
		Int_t minusone=-1;
		event.nparticles=minusone;
	      }

	  }
	//event.nparticles = nlines;
	//tree->Fill();

      }

    else
      {
	printf("Unable to open file");
      }




    printf(" found %d points\n",nlines);

    pFile.close();

    hfile.Write();
    hfile.Close();


}
