/*
Author: Roshan Noronha
Date: July 29, 2017
Purpose: This sketch will run a user defined number of heating and cooling cycles for a user defined amount of time.
         Temperature of the sample is monitored via a thermocouple
         Heating and cooling of the samples is controled via thermoelectric plates based on the temperature of the samples
*/


//////////import libraries//////////////
///#include "Timer.h"
//////////end import libraries//////////
//////////user defined parameters//////////

//number of cycles (30);
int cycles = 2;
//temp of the polymerase in degrees C
//user defined
int polyTemp = 72;

//temp of primer 1 and 2 in degrees C
//both are user defined
const int tempPrimerOne = 61;
const int tempPrimerTwo = 66;

//temp in degrees and time in milliseconds for denaturation
const int denatTemp = 95;
const int initialTimeDenat = 5000;
const int timeDenat = 5000;

//temp in degrees and time in milliseconds for annealing
//annealTemp largest primer temp + 2 degrees
const int annealTemp = max(tempPrimerOne, tempPrimerTwo) + 2;
const int timeAnneal = 5000;

//temp in degrees and time in milliseconds for elongation
//elogation is polymerase dependant (assume taq polymerase)
//time is blank as it depends on length of fragment in addition to the type of polymerase
const int elongTemp = 72;
const int timeElong = 5000;

//temp in degrees and time in milliseconds for final elongation
//final step done for 10 mins/600s
const int finalElongTemp = 72;
const int timeFinalElong = 5000;

//holding temp in degrees and time in seconds for short term storage of the sample
//max 30 min storage time
const int tempHold = 3;
const int timeTempHold = 5000;

//////////end user defined parameters/////////////

////////Pins Setup///////////////

int tempPin = 0;
int input1 = 10;
int input2 = 9;
///////End Pin Setup/////////////////

void setup() {
  
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  
  digitalWrite(input1, LOW);
  digitalWrite(input2, LOW);
  
  //initial denaturation
  denaturation(denatTemp, initialTimeDenat, "Initial Denaturation");
}

//////////start cycles///////////

//rest of pcr cycle
void loop() {
  
  if (cycles == 0) {
    
    hold(tempHold, timeTempHold);
    Serial.println();
  	Serial.println();
  	Serial.println("PCR COMPLETE");
  	exitPCR();
  }
  
  else if (cycles == 1) {
    
    Serial.println();
    Serial.println();
    Serial.println("denaturation ");
 	Serial.println(cycles);
  	Serial.println();
    denaturation(denatTemp, timeDenat, "Denaturation");
    
    Serial.println();
    Serial.println();
    Serial.println("annealing ");
 	Serial.println(cycles);
  	Serial.println();
    annealing(annealTemp, timeAnneal);
    
    Serial.println();
    Serial.println();
    Serial.println("elongation ");
 	Serial.println(cycles);
  	Serial.println();
    elongation(elongTemp, timeElong, "Elongation");
    
    Serial.println();
    Serial.println();
    Serial.println("final elongation ");
 	Serial.println(cycles);
  	Serial.println();
    elongation(finalElongTemp, timeFinalElong, "Final Elongation");
  }
  
  else {
    
    Serial.println();
    Serial.println();
    Serial.println("denaturation ");
 	Serial.println(cycles);
  	Serial.println();
    denaturation(denatTemp, timeDenat, "Denaturation");
    
    Serial.println();
    Serial.println();
    Serial.println("annealing ");
 	Serial.println(cycles);
  	Serial.println();
    annealing(annealTemp, timeAnneal);
    
    Serial.println();
    Serial.println();
    Serial.println("elongation ");
 	Serial.println(cycles);
  	Serial.println();
    elongation(elongTemp, timeElong, "Elongation");
    
  }
  
  cycles--;
}
 
//////////end cycles///////////

void denaturation(int temp, int time, String step) {
  
  //gets samples to denaturation temp
  getToTemp(temp, step);
  
  //wait for the nessecary time
  Serial.print(step);
  Serial.print(" complete in: ");
  Serial.print(time);
  Serial.println(" s");
  delay(time);
  Serial.print(step);
  Serial.println(" complete ");
}

void annealing(int temp, int time) {
  
  //heats samples to denaturation temp
  getToTemp(temp, "Annealing");
  
  //wait for the nessecary time
  Serial.print("Annealing");
  Serial.print(" complete in: ");
  Serial.print(time);
  Serial.println(" s");
  delay(time);
  Serial.print("Annealing");
  Serial.println(" complete ");
}

void elongation(int temp, int time, String step) {
  
  //heats samples to denaturation temp
  getToTemp(temp, step);
  
  //wait for the nessecary time
  Serial.print(step);
  Serial.print(" complete in: ");
  Serial.print(time);
  Serial.println(" s");
  delay(time);
  Serial.print(step);
  Serial.println(" complete ");
}

void hold(int temp, int time) {

  //heats samples to denaturation temp
  getToTemp(temp, "hold");
  
  //wait for the nessecary time
  Serial.print("Hold");
  Serial.print(" complete in: ");
  Serial.print(time);
  Serial.println(" s");
  delay(time);
}

void getToTemp(int tempParam, String step) {
  
  //read in sample temp
  int sampleTemp = getSampleTemp();
  
  //if sample temp is less than the needed temperature then heat the sample
  //otherwise reverse the current to cool down the sample
  while (sampleTemp != tempParam) {
    
    if (sampleTemp < tempParam) { 
      digitalWrite(input1, HIGH);
      digitalWrite(input2, LOW);
    }
    
    else {
      digitalWrite(input1, LOW);
      digitalWrite(input2, HIGH);
    }
    
    Serial.print("Sample Temp: ");
    Serial.print(sampleTemp);
    Serial.println(" C");
    Serial.print(step);
    Serial.print(" Temp: ");
    Serial.print(tempParam);
    Serial.println(" C");
    
    //update sample temp
    sampleTemp = getSampleTemp();
    delay(2000);
  }
  
  //turns off the plate
  digitalWrite(input1, LOW);
  digitalWrite(input2, LOW);
}

int getSampleTemp() {
  
  float pinRead = analogRead(tempPin);
  float voltage = pinRead * 5.0;
  voltage /= 1024.0;
  int temperatureC = (voltage - 0.5) * 100;
  
  return temperatureC;  
}

void exitPCR() {
  
  delay(10000);
  exit(0);
}

