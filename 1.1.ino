#include <LiquidCrystal.h>
#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"

LiquidCrystal lcd(8,9,4,5,6,7);

void A2D_init()
{
  ADMUX= _BV(REFS0)|_BV(ADLAR);//Set to reference voltage, left adjust
  ADCSRA= _BV(ADEN)|_BV(ADSC)|7;//Set to 128 prescaler, free running mode
}
int A2D_read()
{
  unsigned int temp;
  temp=((ADCH*19.5)); //reads adc value
  return temp;
}
void RFSetup()
{
  Mirf.csnPin = 2;
  Mirf.cePin = 3;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setTADDR ((byte *) "EGR226");
  Mirf.payload=16;
  Mirf.channel = 50;
  Mirf.config ();
}

void setup() 
{
  Serial.begin (9600);
  Serial.println ("Ready to decode");
  
  A2D_init();
  RFSetup();
  lcd.begin (16,2);
  lcd.setCursor (0,0);
}

void loop() 
{
  char v = 'A';
  uint8_t btnVal;
  btnVal = A2D_read();
  
  //btnVal=analogRead (A0);
  
  Serial.println (btnVal);
  
  if (btnVal<100)
  {//left
    v='G';
    Serial.println ("G");
    lcd.print ("G");
    //Mirf.send ((byte *)&v);
  }
  else if (btnVal>100&&btnVal<200)
  {//up
    v='V';
    Serial.println ("V");
    lcd.print ("G");
    //Mirf.send ((byte *)&v);
  }
  else if (btnVal>200&&btnVal<300)
  {//right
    v='S';
    Serial.println ("S");
    lcd.print ("G");
   // Mirf.send ((byte *)&v);
  }
  else if ((btnVal>300&&btnVal<400))
  {//down
    v='U';
    Serial.println ("U");
    lcd.print ("G");
    //Mirf.send ((byte *)&v);
  }

  
  delay(200);
}
