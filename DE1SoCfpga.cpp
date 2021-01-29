//@file DE1SoCfpga.cpp
//@Author Eleni Polichronakis
//@date October 2020
//@brief This is the .cpp file for the DE1SoC class

#include "DE1SoCfpga.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
using namespace std;

// Physical base address of FPGA Devices 
const unsigned int LW_BRIDGE_BASE 	= 0xFF200000;  // Base offset 

// Length of memory-mapped IO window 
const unsigned int LW_BRIDGE_SPAN 	= 0x00DEC700;  // Address map size

// Cyclone V FPGA device addresses
const unsigned int LEDR_BASE 		= 0x00000000;  // Leds offset 
const unsigned int SW_BASE 			= 0x00000040;  // Switches offset
const unsigned int KEY_BASE 		= 0x00000050;  // Push buttons offset
const unsigned int HEX3_HEX0_BASE=0x00000020;  //HEX reg1 offset
const unsigned int HEX5_HEX4_BASE=0x00000030;  //HEX reg2 offset


DE1SoCfpga::DE1SoCfpga(){
  // Open /dev/mem to give access to physical addresses
	fd = open( "/dev/mem", (O_RDWR | O_SYNC));
	if (fd == -1)			//  check for errors in openning /dev/mem
	{
        cout << "ERROR: could not open /dev/mem..." << endl;
        exit(1);
	}
	
   // Get a mapping from physical addresses to virtual addresses
   char *virtual_base = (char *)mmap (NULL, LW_BRIDGE_SPAN, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, LW_BRIDGE_BASE);
   if (virtual_base == MAP_FAILED)		// check for errors
   {
      cout << "ERROR: mmap() failed..." << endl;
      close (fd);		// close memory before exiting
      exit(1);        // Returns 1 to the operating system;
   }
   pBase= virtual_base;
   
  }
DE1SoCfpga::~DE1SoCfpga(){
  if (munmap (pBase, LW_BRIDGE_SPAN) != 0)
	{
      cout << "ERROR: munmap() failed..." << endl;
      exit(1);
	}
   close (fd); 	// close memory
  }
  
  /** 
 * Write a 4-byte value at the specified general-purpose I/O location. 
 * 
 * @param pBase		Base address returned by 'mmap'. 
 * @parem offset	Offset where device is mapped. 
 * @param value	Value to be written. 
 */ 
void DE1SoCfpga::RegisterWrite(unsigned int offset, int value) 
{ 
  * (volatile unsigned int *)(pBase + offset) = value; 
} 
/** 
 * Read a 4-byte value from the specified general-purpose I/O location. 
 * 
 * @param pBase		Base address returned by 'mmap'. 
 * @param offset	Offset where device is mapped. 
 * @return		Value read. 
 */ 
int DE1SoCfpga::RegisterRead(unsigned int offset) 
{ 
	return * (volatile unsigned int *)(pBase + offset); 
} 

