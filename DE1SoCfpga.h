//@file DE1SoCfpga.h
//@Author Eleni Polichronakis
//@date October 2020
//@brief This is the header file for the DE1SoC class

#ifndef DE1SoCfpga_H
#define DE1SoCfpga_H

//function prototypes & class definition 
class DE1SoCfpga{
public:
  int fd;
  char *pBase;
  DE1SoCfpga();
  ~DE1SoCfpga();
  void RegisterWrite(unsigned int offset, int value);
  int RegisterRead(unsigned int offset);
  };//end of class 
  #endif

