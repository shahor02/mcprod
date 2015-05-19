#ifndef ALIMCCONF_H
#define ALIMCCONF_H

#include <TObject.h>
#include <TString.h>
#include <stdio.h>

class AliMCConf : public TObject 
{
 public:
  enum {kOffsStep=2}; // offset step in spaces
  AliMCConf();

  void         WriteConfigDet();

  void         SetDetConfName(const char* nm=0);
  const  char* GetDetConfName()                   const {return fDetConfName.Data();}
  //
 protected:
  void ToFile(FILE* fl,const char* cmd, int offsInc=0);
  void IncOffs()                                              {fOffs += kOffsStep;}
  void DecOffs()                                              {fOffs -= kOffsStep;}

 protected:
  Int_t fYear;

  Int_t fOffs;                               // current offset in spaces
  TString     fDetConfName;                  // name for detector config macro
  //

  static const char* fgkDetConfName;         // default name for detector config file
  //
  ClassDef(AliMCConf,0);
};


#endif
