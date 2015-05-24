#ifndef ALIMCCONF_H
#define ALIMCCONF_H

#include <TObject.h>
#include <TString.h>
#include <stdio.h>

class AliMCConf : public TObject 
{
 public:
  enum collsyst_t {kPP,kPA,kAP,kAA};
  enum {kOffsStep=2}; // offset step in spaces
  AliMCConf();

  void         WriteConfigDet();

  void         SetDetConfName(const char* nm=0);
  const  char* GetDetConfName()                   const {return fDetConfName.Data();}
  //
 protected:
  void OpenFile(const char* name);
  void CloseFile();
  void ToFile(const char* cmd, int offsInc=0);
  void IncOffs()                                              {fOffs += kOffsStep;}
  void DecOffs()                                              {fOffs -= kOffsStep;}
  //
  void DoAliBody();
  void DoBody();
  void DoMagnet();
  void DoAbsorber(); 
  void DoDipole(); 
  void DoHall(); 
  void DoFrame(); 
  void DoShield(); 
  void DoPipe(); 
  void DoITS(); 
  void DoTPC(); 
  void DoTOF();
  void DoHMPID();
  void DoZDC();
  void DoTRD();
  void DoFMD();
  void DoMUON();
  void DoPHOS();
  void DoPMD();
  void DoT0();
  void DoEMCAL();
  void DoACORDE();
  void DoVZERO();
  void DoAD();
  //
 protected:
  Int_t fYear;
  collsyst_t fCollSystem;                    // collision system
  Float_t fBeamEnergy;                       // beam energy (per charge)
  //
  FILE* fFlOut;                              // current output file
  Int_t fOffs;                               // current offset in spaces
  TString     fDetConfName;                  // name for detector config macro
  //

  static const char* fgkDetConfName;         // default name for detector config file
  //
  ClassDef(AliMCConf,0);
};


#endif
