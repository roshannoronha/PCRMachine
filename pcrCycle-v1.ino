/*This code is just a template and is incomplete. DO NOT USE*/
/*
Author: Roshan Noronha
Date: January 30th, 2015
Purpose: This sketch will run a user defined number of heating and cooling cycles for a user defined amount of time.
         Temperature of the sample is monitored via a thermocouple
         Heating and cooling of the samples is controled via thermoelectric plates based on the temperature of the samples
*/

//import libraries
#include "Timer.h"

//////////user defined parameters

//number of cycles (30);
int cycles = 30;
//temp of the polymerase in degrees C
//user defined
int polyTemp = ;

//temp of primer 1 and 2 in degrees C
//both are user defined
const int tempPrimerOne = ;
const int tempPrimerTwo = ;

//temp in degrees and time in seconds for denaturation
const int denatTemp = 98;
const int timeDenatTemp = 25;

//temp in degrees and time in seconds for annealing
//annealTemp is average primer temp - 3 degrees
const int annealTemp = ((tempPrimerOne + tempPrimerTwo) / 2) - 3;
const int timeAnnealTemp = 30;

//temp in degrees and time in seconds for elongation
//elogation is polymerase dependant (assume taq polymerase)
//time is blank as it depends on length of fragment in addition to the type of polymerase
const int elongTemp = 72;
const int timeElongTemp = ;

//temp in degrees and time in seconds for final elongation
//final step done for 10 mins/600s
const int finalElongTemp = 72;
const int timeFinalElong = 600;

//holding temp in degrees and time in seconds for short term storage of the sample
//max 30 min storage time
const int tempHold = 4;
const int timeTempHold = 1800;

//////////end user defined parameters

//get temps for each sample from thermocouple
int sampleOneTemp = ;
int sampleTwoTemp = ;

//////////start cycles

while (cycles >= 0) {
  
  if (cycles == 0) {
   
   hold(); 
  }
  
  if (cycles == 1) {
    
    denaturation();
    annealing();
    elongation();
    extention();
  }
  
  else {
    
    denaturation();
    annealing();
    elongation();
  }
  
  cycles--;
}

//////////end cycles

void denaturation() {
  
  //heats samples to denaturation step
  heatSamples(denatTemp);
  
  //initilize a timer "t" to 0 seconds
  while (t <= timeDenatTemp) {
    
    if ((sampleOneTemp < (denatTemp - 5)) || (sampleOneTemp < (denatTemp - 5))) {
      
      heatSamples(denatTemp);
    }
  }
}

void annealing() {
  
  //heat samples to annealing temp
  heatSamples(annealTemp);
  
  //initilaize a timer "t" to 0 seconds
  while (t <= timeAnnealTemp) {
    
    if ((sampleOneTemp < (annealTemp - 1)) || (sampleOneTemp < (annealTemp - 1))) {
      
      heatSamples(annealTemp);
    }
  }
}

void elongation() {
  
  //heat samples to elongation temp
  heatSamples(elongTemp);
  
  //initilaize a timer "t" to 0 seconds
  while (t <= timeElongTemp) {
    
    if ((sampleOneTemp < (elongTemp - 1)) || (sampleOneTemp < (elongTemp - 1))) {
      
      heatSamples(elongTemp);
    }
  }
}

void heatSamples(int tempParam) {
  
  //heat samples if sample temps are too low
  if (sampleOneTemp < tempParam) && (sampleTwoTemp < tempParam) {
           
  }
  
  //cool samples if samples temps are too high
  //switches the direction of the current to have the plate cool down
  if ((sampleOneTemp > tempParam) && (sampleTwoTemp > tempParam)) {
    
  }
}

void hold() {

  //cools samples to holding temp
  heatSamples(tempHold);
  
  //initialize timer "t" to 0 seconds
  while (t < timeTempHold) {
    
    if ((sampleOneTemp < (tempHold - 2)) || (sampleOneTemp < (tempHold - 2))) {
      
      heatSamples(elongTemp);
    }
  }
}

    
  
  
  
 
  

  
    







