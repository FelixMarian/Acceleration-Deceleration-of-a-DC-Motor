#include <LiquidCrystal.h>

//Declaration of LCD pins
const int RS = 8;
const int Enable = 9;
const int DB4=10;
const int DB5=11;
const int DB6=12;
const int DB7=13;
unsigned long startTime; //Variable used to check when the button is pressed
bool timerStarted; //Variable to check if the timer already started or not
bool isOn=true; //Variable to check if the motor is ON or OFF, by default is ON

LiquidCrystal lcd_l(RS, Enable, DB4,DB5,DB6,DB7);

int i = 0, state=1;

void setup()
{
  DDRD=B00100000; //Only Digital pin 5 is for output, rest of them are for input
  DDRB=B00111111; //Digital pins 8-13 are for output
  lcd_l.begin(16,2);
  dutyCycleWrite(i); //LCD shows current duty cycle which is 0
  Serial.begin(9600); // Serial debugging
}

void loop()
{
  //We check if the button is pressed and the timer hasn't started yet (the moment we press it)
  if(PIND&(1<<6) && !timerStarted){
    startTime=millis(); //Memorize the moment button is pressed
  	timerStarted=true; //Set that the timer started
  }
  else if(PIND&(1<<6)){ //Check if the button is pressed (this works only after timer has started)
    if(state){ //Check if we are in the acceleration cycle     
      if((millis()-startTime)>=2000){ //Check if the button is pressed for more than 2 seconds
        //If the motor is on, change the state to 0 (shutting it down) and we stop the output voltage
        if(isOn){
        changeState(0); 
        delay(20);
        PORTD=B00000000;
        isOn = false; //Update the ON/OFF state
        }   
        //If the motor is off, change the state to 1 (starting it) and set output on digital pin 5
        else if(!isOn){
        changeState(1);
        delay(20);
        PORTD=B00100000;
        isOn = true; //Update the ON/OFF state
        }
      }
      //We increment the duty-cycle with another 10%
      i+=100;
      delay(200);
      dutyCycleWrite(i);
      delay(200);
      if(i==1000)//If the duty cycle is maximum (100%), set the cycleState to 0 (enter the deceleration cycle)
        state=cycleState(0);
    }
    else if(!state){ //Check if we are in the deceleration cycle 
      if((millis()-startTime)>=2000){ //Check if the button is pressed for more than 2 seconds
        //If the motor is on, change the state to 0 (shutting it down) and we stop the output voltage
        if(isOn){ 
        changeState(0);
        delay(20);
        PORTD=B00000000;
        isOn = false; //Update the ON/OFF state
        }     
        //If the motor is off, change the state to 1 (starting it) and set output on digital pin 5
        else if(!isOn){
        changeState(1);
        delay(20);
        PORTD=B00100000;
        isOn = true; //Update the ON/OFF state
        }
      }
      //We decrement the duty-cycle with another 10%
      i-=100;
      delay(200);
      dutyCycleWrite(i);
      delay(200);
      if(i==0) //If the duty cycle is minimum (0%), set the cycleState to 1 (enter the acceleration cycle)
        state=cycleState(1);
    }
  }
  else {
  startTime=millis(); //If the button is not pressed, we constantly reset the start time
  }
  if(isOn){ //If the engine's state is ON, we start it with a PWM signal of i% duty-cycle
    PORTD=B00100000;
    delayMicroseconds(i);
    PORTD=B00000000;
    delayMicroseconds(1000-i);
  }
}
//Function used to print on the LCD the current duty-cycle
//We print i/10 because i=100 => 10% duty-cycle, i=200 => 20% duty-cycle and so on...
void dutyCycleWrite(int i){ 
    lcd_l.clear();
    lcd_l.setCursor(0, 0);
  	lcd_l.print("Duty-Cycle");
    lcd_l.setCursor(3, 1);
    lcd_l.print(i/10);
    lcd_l.setCursor(6, 1);
    lcd_l.print("%");
}

//Function used to modify the cycle state (acceleration cycle or deceleration state)
int cycleState(int nr){
	if(nr==1)
      return 1;
 	else if(nr==0)
      return 0;
}

//Function used to print an shutting down / starting up prompt with timer
void changeState(int state){
	lcd_l.clear();
    lcd_l.setCursor(0, 0);
  	if(state==0)
      lcd_l.print("Shutdown in");
    else
      lcd_l.print("Starting in");
  	for(int i=3;i>0;i--){
    	lcd_l.setCursor(5, 1);
        lcd_l.print(i);
      	delay(500);
    }
}
      