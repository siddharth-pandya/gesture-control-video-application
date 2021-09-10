#include <LiquidCrystal.h>  
int Contrast=20;
 LiquidCrystal lcd(12, 11, 5, 4, 3, 2);   
const int trigger1 = 7; //Trigger pin of 1st Sesnor
const int echo1 = 8; //Echo pin of 1st Sesnor
const int trigger2 = 10; //Trigger pin of 2nd Sesnor
const int echo2 = 13;//Echo pin of 2nd Sesnor

long time_taken;
int dist,distL,distR;

 

void setup() {
Serial.begin(9600); 
  
pinMode(trigger1, OUTPUT); 
pinMode(echo1, INPUT);     
pinMode(trigger2, OUTPUT); 
pinMode(echo2, INPUT); 

analogWrite(6,Contrast);
    lcd.begin(16, 2);
}

/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo)
{
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);

time_taken = pulseIn(echo, HIGH);
dist= time_taken*0.034/2;
if (dist>50)
dist = 50;
}

void loop() { //infinite loopy
calculate_distance(trigger1,echo1);
distL =dist; //get distance of left sensor

calculate_distance(trigger2,echo2);
distR =dist; //get distance of right sensor

//Uncomment for debudding
Serial.print("L=");
Serial.println(distL);
Serial.print("R=");
Serial.println(distR);


//Pause Modes -Hold
if ((distL >40 && distR>40) && (distL <50 && distR<50)) //Detect both hands
{Serial.println("Play/Pause"); delay (500);

lcd.setCursor(0, 0);
lcd.print("PLAY/PAUSE");}
calculate_distance(trigger1,echo1);
distL =dist;

calculate_distance(trigger2,echo2);
distR =dist;

 
//full screen -Hold
if ((distL >5 && distR>5) && (distL <10 && distR<10)) //Detect both hands
{Serial.println("FullScreen"); delay (500);
lcd.setCursor(0, 0);
lcd.print("FULLSCREEN");}
calculate_distance(trigger1,echo1);
distL =dist;

calculate_distance(trigger2,echo2);
distR =dist;
//Control Modes
//Lock Left - Control Mode
if (distL>=13 && distL<=17)
{
  delay(100); //Hand Hold Time
  calculate_distance(trigger1,echo1);
  distL =dist;
  if (distL>=13 && distL<=17)
  {
    Serial.println("Left Locked");
    while(distL<=40)
    {
      calculate_distance(trigger1,echo1);
      distL =dist;
      if (distL<10) //Hand pushed in 
      {Serial.println ("Vup"); delay (300);
      lcd.setCursor(0, 0);
      lcd.print("VUP");}
      if (distL>20) //Hand pulled out
      {Serial.println ("Vdown"); delay (300);
      lcd.setCursor(0, 0);
      lcd.print("VDOWN");}
    }
  }
}

//Lock Right - Control Mode
if (distR>=13 && distR<=17)
{
  delay(100); //Hand Hold Time
  calculate_distance(trigger2,echo2);
  distR =dist;
  if (distR>=13 && distR<=17)
  {
    Serial.println("Right Locked");
    while(distR<=40)
    {
      calculate_distance(trigger2,echo2);
      distR =dist;
      if (distR<10) //Right hand pushed in
      {Serial.println ("Rewind"); delay (300);
      lcd.setCursor(0, 0);
      lcd.print("REWIND");}
      if (distR>20) //Right hand pulled out
      {Serial.println ("Forward"); delay (300);
      lcd.setCursor(0, 0);
      lcd.print("FORWARD");}
  }
}
}

delay(200);
} 
