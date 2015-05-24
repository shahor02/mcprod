#include "AliMCConf.h"
#include "AliLog.h"

ClassImp(AliMCConf)

const char* AliMCConf::fgkDetConfName = "ConfigDet";

/*
	Int_t   iABSO   = 1;
	Int_t   iDIPO   = 1;
	Int_t   iFMD    = 1;
	Int_t   iFRAME  = 1;
	Int_t   iHALL   = 1;
	Int_t   iITS    = 1;
	Int_t   iMAG    = 1;
	Int_t   iMUON   = 1;
	Int_t   iPHOS   = 1;
	Int_t   iPIPE   = 1;
	Int_t   iPMD    = 1;
	Int_t   iHMPID  = 1;
	Int_t   iSHIL   = 1;
	Int_t   iT0     = 1;
	Int_t   iTOF    = 1;
	Int_t   iTPC    = 1;
	Int_t   iTRD    = 1;
	Int_t   iZDC    = 1;
	Int_t   iEMCAL  = 1;
	Int_t   iVZERO  = 1;
	Int_t   iACORDE = 1;
	Int_t   iAD = 1;
*/

//______________________________________________
AliMCConf::AliMCConf() 
  :fYear(0)
  ,fCollSystem(kPP)
  ,fBeamEnergy(0)
  ,fFlOut(0)
  ,fOffs(0)
  ,fDetConfName(fgkDetConfName)
{
  
}


//______________________________________________
void AliMCConf::WriteConfigDet()
{
  // write detector configuration
  //
  OpenFile(Form("%s.C",fDetConfName.Data()));
  ToFile(Form("void %s()",fDetConfName));
  ToFile("{");
  IncOffs();
  //
  DoBody(); //OK
  DoMagnet(); //OK
  DoAbsorber(); //OK
  DoDipole(); //OK
  DoHall(); //OK
  DoFrame(); //OK
  DoShield(); //OK
  DoPipe(); //OK
  DoITS(); //OK
  DoTPC(); //OK
  DoTOF(); //OK
  DoHMPID(); //OK
  DoZDC(); //TODOOOOOOOOOOOOOOOOOOOOOO
  DoTRD(); //OK 
  DoFMD(); //OK
  DoMUON(); //OK
  DoPHOS(); //OK
  DoPMD(); //OK
  DoT0(); //OK
  DoEMCAL(); //OK
  DoACORDE(); //OK
  DoVZERO(); //OK
  DoAD(); //OK
  //
  DecOffs();
  ToFile("}");
  CloseFile();
}

//______________________________________________
void AliMCConf::SetDetConfName(const char* nm)
{
  // set detector conf. name
  fDetConfName = nm;
  if (fDetConfName.IsNull()) fDetConfName = fgkDetConfName;
  if (fDetConfName.EndsWith(".C")) fDetConfName.Remove(fDetConfName.Length()-strlen(".C"));
  //
}

//______________________________________________
void AliMCConf::ToFile(const char* cmd, int offsInc)
{
  // write string to file with, prepending by offset
  int offs = fOffs;
  if (offsInc) offs += offsInc*kOffsStep;
  fprintf(fFlOut,Form("%%%ds%%s\n",offs),"",cmd);
}

//______________________________________________
void AliMCConf::OpenFile(const char* name)
{
  // creare output file
  if (fFlOut) fclose(fFlOut);
  fFlOut = fopen(Form("%s.C",fDetConfName.Data()),"w");
  if (!flout) AliFatalF("Failed to create file %s",fDetConfName.Data());
  fOffs = 0;
}

//______________________________________________
void AliMCConf::CloseFile()
{
  // close output file
  fclose(fFlOut);
}

//=====================================================================

//______________________________________________
void AliMCConf::DoBody()
{
  // body
  ToFile("//===============  ALICE BODY PARAMETERS  ===============");
  ToFile("AliBODY *BODY = new AliBODY(\"BODY\", \"Alice envelop\");");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoMagnet()
{
  // L3 magnet
  ToFile("//===============  MAGNET     PARAMETERS  ===============");
  ToFile("if (iMAG) {");
  ToFile("AliMAG *MAG = new AliMAG(\"MAG\", \"Magnet\");",1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoAbsorber() 
{
  // absorber
  ToFile("//===============  ABSORBER   PARAMETERS  ===============");
  ToFile("if (iABSO) {");
  ToFile("AliABSO *ABSO = new AliABSOv3(\"ABSO\", \"Muon Absorber\");",1);
  ToFile("}");
  ToFile("");
  //
}
  
//______________________________________________
void AliMCConf::DoDipole() 
{
  // dipole
  ToFile("//===============  DIPOLE     PARAMETERS  ===============");
  ToFile("if (iDIPO) {");
  ToFile("AliDIPO *DIPO = new AliDIPOv3(\"DIPO\", \"Dipole version 3\");",1);
  ToFile("");
  //  
}

//______________________________________________
void AliMCConf::DoHall() 
{
  // alice hall
  ToFile("//===============  HALL       PARAMETERS  ===============");
  ToFile("if (iHALL) AliHALL *HALL = new AliHALLv3(\"HALL\", \"Alice Hall\");");
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoFrame() 
{
  // alice frame
  ToFile("//===============  FRAME      PARAMETERS  ===============");
  ToFile("if (iFRAME) {");
  ToFile("AliFRAMEv3 *FRAME = new AliFRAMEv3(\"FRAME\", \"Space Frame\");",1);
  ToFile("FRAME->SetHoles(1);",1); 
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoShield() 
{
  // shield
  ToFile("//===============  SHIELD     PARAMETERS  ===============");
  ToFile("if (iSHIL) {");
  ToFile("AliSHIL *SHIL = new AliSHILv3(\"SHIL\", \"Shielding Version 3\");",1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoPipe() 
{
  // beam pipe
  ToFile("//===============  PIPE       PARAMETERS  ===============");
  ToFile("if (iPIPE) {");
  ToFile("AliPIPE *PIPE = new AliPIPEv3(\"PIPE\", \"Beam Pipe\");",1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoITS() 
{
  // ITS
  ToFile("//===============  ITS        PARAMETERS  ===============");
  ToFile("if (iITS) {");
  ToFile("AliITS *ITS = new AliITSv11(\"ITS\",\"ITS v11\");",1);
  ToFile("}");
  ToFile("");
  //  
}

//______________________________________________
void AliMCConf::DoTPC() 
{
  // TPC
  ToFile("//===============  TPC        PARAMETERS  ===============");
  ToFile("if (iTPC) {");
  ToFile("AliTPC *TPC = new AliTPCv2(\"TPC\", \"Default\");",1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoTOF()
{
  // TOF
  ToFile("//===============  TOF        PARAMETERS  ===============");
  ToFile("if (iTOF) {");
  ToFile("AliTOF *TOF = new AliTOFv6T0(\"TOF\", \"normal TOF\");",1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoHMPID()
{
  // HMPID
  ToFile("//===============  HMPID      PARAMETERS  ===============");
  ToFile("if (iHMPID) {");
  ToFile("AliHMPID *HMPID = new AliHMPIDv3(\"HMPID\", \"normal HMPID\");",1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoTRD()
{
  // TRD
  ToFile("//===============  TRD        PARAMETERS  ===============");
  ToFile("if (iTRD) {");  
  IncOffs();
  ToFile("AliTRD *TRD = new AliTRDv1(\"TRD\", \"TRD slow simulator\");");
  ToFile("AliTRDgeometry *geoTRD = TRD->GetGeometry();");
  if (fYear<2011) {
    ToFile("geoTRD->SetSMstatus(11,0);");
    ToFile("geoTRD->SetSMstatus(15,0);");
    ToFile("geoTRD->SetSMstatus(16,0);");
  }
  if (fYear<2012) {
    ToFile("geoTRD->SetSMstatus(2,0);");
    ToFile("geoTRD->SetSMstatus(3,0);");
    ToFile("geoTRD->SetSMstatus(6,0);");
  }
  if (fYear<2015) {
    ToFile("geoTRD->SetSMstatus(4,0);");
    ToFile("geoTRD->SetSMstatus(5,0);");
    ToFile("geoTRD->SetSMstatus(12,0);");
    ToFile("geoTRD->SetSMstatus(13,0);");
    ToFile("geoTRD->SetSMstatus(14,0);"); 
  }
  //
  DecOffs();
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoFMD()
{
  // FMD
  ToFile("//===============  FMD        PARAMETERS  ===============");
  ToFile("if (iFMD) {");
  ToFile("AliFMD *FMD = new AliFMDv1(\"FMD\", \"normal FMD\");",1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoMUON()
{
  // MUON
  ToFile("//===============  MUON       PARAMETERS  ===============");
  ToFile("if (iMUON) {");
  ToFile("AliMUON *MUON = new AliMUONv1(\"MUON\", \"default\");",1);
  ToFile("MUON->SetTriggerResponseV1(2);",1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoPHOS()
{
  // PHOS
  ToFile("//===============  PHOS       PARAMETERS  ===============");
  ToFile("if (iPHOS) {");
  if (fYear>2014) 
    ToFile("AliPHOS *PHOS = new AliPHOSv1(\"PHOS\", \"Run2\");",1);
  else 
    ToFile("AliPHOS *PHOS = new AliPHOSv1(\"PHOS\", \"noCPV_Modules123\");",1);
  //
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoPMD()
{
  // HPD
  ToFile("//===============  PMD        PARAMETERS  ===============");
  ToFile("if (iPMD) {");
  ToFile("AliPMD *PMD = new AliPMDv1(\"PMD\", \"normal PMD\");",1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoT0()
{
  // T0
  ToFile("//===============  T0         PARAMETERS  ===============");
  ToFile("if (iT0) {");
  ToFile("AliT0 *T0 = new AliT0v1(\"T0\", \"T0 Detector\");",1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoEMCAL()
{
  // EMCAL
  TString version;
  if      (fYear<=2010) version = "EMCAL_FIRSTYEARV1";
  else if (fYear==2011) version = "EMCAL_COMPLETEV1";
  else if (fYear<=2014) version = "EMCAL_COMPLETE12SMV1";
  else                  version = "EMCAL_COMPLETE12SMV1_DCAL_8SM";
  //
  ToFile("//===============  EMCAL      PARAMETERS  ===============");
  ToFile("if (iEMCAL) {");
  ToFile(Form("AliEMCAL *EMCAL = new AliEMCALv2(\"EMCAL\", \"%s\", kFALSE);",version.Data()),1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoACORDE()
{
  // ACORDE
  ToFile("//===============  ACORDE     PARAMETERS  ===============");
  ToFile("if (iACORDE) {");
  ToFile("AliACORDE *ACORDE = new AliACORDEv1(\"ACORDE\", \"normal ACORDE\");",1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoVZERO()
{
  // V0
  ToFile("//===============  VZERO      PARAMETERS  ===============");
  ToFile("if (iVZERO) {");
  ToFile("AliVZERO *VZERO = new AliVZEROv7(\"VZERO\", \"normal VZERO\");",1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoAD()
{
  // AD
  if (fYear<2015) return;
  ToFile("//===============  AD         PARAMETERS  ===============");
  ToFile("if (iAD) {");
  ToFile("AliAD *AD = new AliADv1(\"AD\", \"normal AD\");",1);
  ToFile("}");
  ToFile("");
  //
}

//______________________________________________
void AliMCConf::DoZDC()
{
  // ZDC
  if (fCollSystem == kPP) return;
  //
  TString zdcV = "AliZDCv3";
  TString zdcOpt;
  if (fYear>=2013) zdcV = "AliZDCv4";

  ToFile("//===============  ZDC        PARAMETERS  ===============");
  ToFile("if (iZDC) {");
  IncOffs();
  ToFile(Form("AliZDC *ZDC = new %s(\"ZDC\", \"normal ZDC\");",zdcV.Data()));
  //
  ToFile("ZDC->SetLumiLenght(0.);");
  if (fCollSystem==kPA || fCollSystem=kAP) {
    ToFile("ZDC->SetpASystem();");
    ToFile(Form("ZDC->SetBeamEnergy(82.*%f/208.);",fBeamEnergy));
  }
  
  ToFile("ZDC->SetSpectatorsTrack();");

  if (fPeriod==kLHC11h && TMath::Abs(fCrossAngle)>0) {
    ToFile("ZDC->SetVCollSideAAperture(2.8);");
    ToFile("ZDC->SetVCollSideAApertureNeg(2.8);");
    ToFile("ZDC->SetVCollSideCAperture(2.8);");
    ToFile("ZDC->SetVCollSideCApertureNeg(2.8);");
    ToFile("ZDC->SetTDIAperturePos(5.5);");
    ToFile("ZDC->SetTDIApertureNeg(5.5);");
    ToFile("ZDC->SetTCDDAperturePos(2.);");
    ToFile("ZDC->SetTCDDApertureNeg(2.2);");
  }
  DecOffs();
  ToFile("}");
  ToFile("");
  //
}
