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
   
  ,fOffs(0)
  ,fDetConfName(fgkDetConfName)
{
  
}


//______________________________________________
void AliMCConf::WriteConfigDet()
{
  // write detector configuration
  FILE* flout = fopen(Form("%s.C",fDetConfName.Data()),"w");
  if (!flout) AliFatalF("Failed to create file %s",fDetConfName.Data());
  fOffs = 0;
  //
  ToFile(flout,Form("void %s()",macroname));
  ToFile(flout,"{");
  IncOffs();
  //
  ToFile(flout,"//===============  ALICE BODY PARAMETERS  ===============");
  ToFile(flout,"AliBODY *BODY = new AliBODY(\"BODY\", \"Alice envelop\");");
  ToFile(flout,"");
  //
  ToFile(flout,"//===============  MAGNET     PARAMETERS  ===============");
  ToFile(flout,"if (iMAG) {");
  ToFile(flout,"AliMAG *MAG = new AliMAG(\"MAG\", \"Magnet\");",1);
  ToFile(flout,"}");
  ToFile(flout,"");
  //
  ToFile(flout,"//===============  ABSORBER   PARAMETERS  ===============");
  ToFile(flout,"if (iABSO) {");
  ToFile(flout,"AliABSO *ABSO = new AliABSOv3(\"ABSO\", \"Muon Absorber\");",1);
  ToFile(flout,"}");
  ToFile(flout,"");
  //  
  ToFile(flout,"//===============  DIPOLE     PARAMETERS  ===============");
  ToFile(flout,"if (iDIPO) {");
  ToFile(flout,"AliDIPO *DIPO = new AliDIPOv3(\"DIPO\", \"Dipole version 3\");",1);
  ToFile(flout,"");
  //  
  ToFile(flout,"//===============  HALL       PARAMETERS  ===============");
  ToFile(flout,"if (iHALL) AliHALL *HALL = new AliHALLv3(\"HALL\", \"Alice Hall\");");
  ToFile(flout,"}");
  ToFile(flout,"");
  //
  ToFile(flout,"//===============  FRAME      PARAMETERS  ===============");
  ToFile(flout,"if (iFRAME) {");
  ToFile(flout,"AliFRAMEv3 *FRAME = new AliFRAMEv3(\"FRAME\", \"Space Frame\");",1);
  ToFile(flout,"FRAME->SetHoles(1);",1); 
  ToFile(flout,"}");
  ToFile(flout,"");
  //
  ToFile(flout,"//===============  SHIELD     PARAMETERS  ===============");
  ToFile(flout,"if (iSHIL) {");
  ToFile(flout,"AliSHIL *SHIL = new AliSHILv3(\"SHIL\", \"Shielding Version 3\");",1);
  ToFile(flout,"}");
  ToFile(flout,"");
  //
  ToFile(flout,"//===============  PIPE       PARAMETERS  ===============");
  ToFile(flout,"if (iPIPE) {");
  ToFile(flout,"AliPIPE *PIPE = new AliPIPEv3(\"PIPE\", \"Beam Pipe\");",1);
  ToFile(flout,"}");
  ToFile(flout,"");
  //
  ToFile(flout,"//===============  ITS        PARAMETERS  ===============");
  ToFile(flout,"if (iITS) {");
  ToFile(flout,"AliITS *ITS = new AliITSv11(\"ITS\",\"ITS v11\");",1);
  ToFile(flout,"}");
  ToFile(flout,"");
  //  
  ToFile(flout,"//===============  TPC        PARAMETERS  ===============");
  ToFile(flout,"if (iTPC) {");
  ToFile(flout,"AliTPC *TPC = new AliTPCv2(\"TPC\", \"Default\");",1);
  ToFile(flout,"}");
  ToFile(flout,"");
  //  



  DecOffs();
  ToFile(flout,"}");
  /*



	if (iTOF) {
		//=================== TOF parameters ============================
		AliTOF *TOF = new AliTOFv6T0("TOF", "normal TOF");
	}


	if (iHMPID){
		//=================== HMPID parameters ===========================
		AliHMPID *HMPID = new AliHMPIDv3("HMPID", "normal HMPID");
	}


	if (iZDC)	{
		//=================== ZDC parameters ============================
		AliZDC *ZDC = new AliZDCv4("ZDC", "normal ZDC");
	}

	if (iTRD){
		//=================== TRD parameters ============================
		AliTRD *TRD = new AliTRDv1("TRD", "TRD slow simulator");
		AliTRDgeometry *geoTRD = TRD->GetGeometry();
		// // Partial geometry: modules at 0,1,2,3,6,7,8,9,10,11,15,16,17
		// // starting at 3h in positive direction
		// geoTRD->SetSMstatus(4,0);
		// geoTRD->SetSMstatus(5,0);
		// geoTRD->SetSMstatus(12,0);
		// geoTRD->SetSMstatus(13,0);
		// geoTRD->SetSMstatus(14,0);
	}

	if (iFMD){
		//=================== FMD parameters ============================
		AliFMD *FMD = new AliFMDv1("FMD", "normal FMD");
	}

	if (iMUON){
		//=================== MUON parameters ===========================
		// New MUONv1 version (geometry defined via builders)
		AliMUON *MUON = new AliMUONv1("MUON", "default");
    MUON->SetTriggerResponseV1(2);
	}
	//=================== PHOS parameters ===========================

	if (iPHOS){
	  //see	  https://alice.its.cern.ch/jira/browse/ALIROOT-5623?focusedCommentId=147957&page=com.atlassian.jira.plugin.system.issuetabpanels:comment-tabpanel#comment-147957
	  AliPHOS *PHOS = new AliPHOSv1("PHOS", "Run2"); 
	  //
	  // AliPHOS *PHOS = new AliPHOSv1("PHOS", "noCPV_Modules1234");
	  // AliPHOS *PHOS = new AliPHOSv1("PHOS", "noCPV_Modules123");
	}


	if (iPMD){
		//=================== PMD parameters ============================
		AliPMD *PMD = new AliPMDv1("PMD", "normal PMD");
	}

	if (iT0){
		//=================== T0 parameters ============================
		AliT0 *T0 = new AliT0v1("T0", "T0 Detector");
	}

	if (iEMCAL){
		//=================== EMCAL parameters ============================
  	     // AliEMCAL *EMCAL = new AliEMCALv2("EMCAL", "EMCAL_COMPLETE12SMV1");
		AliEMCAL *EMCAL = new AliEMCALv2("EMCAL", "EMCAL_COMPLETE12SMV1_DCAL_8SM", kFALSE);
	}

	if (iACORDE){
		//=================== ACORDE parameters ============================
		AliACORDE *ACORDE = new AliACORDEv1("ACORDE", "normal ACORDE");
	}

	if (iVZERO){
		//=================== VZERO parameters ============================
		AliVZERO *VZERO = new AliVZEROv7("VZERO", "normal VZERO");
	}
	
	if (iAD){
		//=================== AD parameters ============================
		AliAD *AD = new AliADv1("AD", "normal AD");
	}  

  */
  
  fclose(flout);
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
void AliMCConf::ToFile(FILE* fl,const char* cmd, int offsInc)
{
  // write string to file with, prepending by offset
  int offs = fOffs;
  if (offsInc) offs += offsInc*kOffsStep;
  fprintf(fl,Form("%%%ds%%s\n",offs),"",cmd);
}
