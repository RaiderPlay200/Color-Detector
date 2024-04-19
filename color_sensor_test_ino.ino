#include "SD.h"
#define SD_ChipSelectPin 2
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;
 
#define s0 4        //Module pins wiring
#define s1 5
#define s2 6
#define s3 7
#define out 8 

int red=0, blue=0, green=0;  //RGB values 

void setup() 
{
  tmrpcm.speakerPin=9;
   pinMode(s0,OUTPUT);    //pin modes
   pinMode(s1,OUTPUT);
   pinMode(s2,OUTPUT);
   pinMode(s3,OUTPUT);
   pinMode(out,INPUT);

   Serial.begin(9600);   //intialize the serial monitor baud rate
   if(!SD.begin(SD_ChipSelectPin))
{
  Serial.println("SD fail");
  return;
}
tmrpcm.setVolume(6);
   
   digitalWrite(s0,HIGH); //Putting S0/S1 on HIGH/HIGH levels means the output frequency scalling is at 100% (recommended)
   digitalWrite(s1,HIGH); //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is  2%
}

void GetColors()  
{    
  digitalWrite(s2, LOW);                                           //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for red LOW/HIGH is for blue and HIGH/HIGH is for green 
  digitalWrite(s3, LOW);                                           
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);       //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again, if you have trouble with this expression check the bottom of the code
  digitalWrite(s3, HIGH);                                         //Here we select the other color (set of photodiodes) and measure the other colors value using the same techinque
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s2, HIGH);  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
}

void loop(){
 
  GetColors();                                     //Execute the GetColors function to get the value of each RGB color
                                                   //Depending of the RGB values given by the sensor we can define the color and displays it on the monitor

  Serial.print("R =")
 ; Serial.print(red, DEC);
  Serial.print(" G = ");
   Serial.print(green, DEC);
  Serial.print(" B = ");
  Serial.print(blue,   DEC);
  Serial.print("\	");

  if (red < blue && red < green && red   < 25)
  {
    if (red<=11 && red>=7 && green<=22 && green>=17&& blue<=15 && blue>=11)
    {
  Serial.println(" - (Red Color)");
    tmrpcm.play("re.wav");
     }

   else if (red<=6 && red>=2 && green<=9 && green>=5&& blue<=14 && blue>=8)
     {
 Serial.println(" - (Yellow Color)");
     tmrpcm.play("ye.wav");
     }
    
    else if (red<=7 && red>=5 && green<=12 && green>=9&& blue<=11 && blue>=8)
    {
Serial.println(" - (Pink Color)");
      tmrpcm.play("pi.wav");
     }
    
    else if (red<=7 && red>=5 && green<=16 && green>=11&& blue<=17 && blue>=13)
    {
Serial.println(" - (Orange Color)");
      tmrpcm.play("or.wav");
     }

  }

  else if (red<=12 && red>=9 && green<=9 && green>=7&& blue<=12 && blue>=9)
   {
     Serial.println(" - (Green Color)");
tmrpcm.play("gr.wav");     
  }

  else if (red<=16 && red>=12 && green<=9 && green>=6&& blue<=7 && blue>=4)
  {

    Serial.println(" - (Blue Color)");
    tmrpcm.play("bl.wav");
   }

  else if (red >= 20 && blue>=20 && green>=20)
  {
     Serial.println(" - (Black Color)");
     tmrpcm.play("bla.wav");
  }
  else if (red<=12 && red>=9 && green<=12 && green>=9&& blue<=9 && blue>=7)
  {
     Serial.println(" - (Gray Color)");
     tmrpcm.play("gra.wav");
  }
  else if (red <= 7 && blue<=7 && green<=7)
  {

    if (red <= 7 && blue<=7 && green<=7)
    {
       Serial.println(" - (White Color)");
       tmrpcm.play("wh.wav");
    }
  }
  Serial.println();
   delay(3000);
}