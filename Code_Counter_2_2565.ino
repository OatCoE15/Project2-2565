#include <EEPROM.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

const int Baht1 = D6;
const int Baht2 = D5;
const int Baht5 = D3;
const int Baht10 = D0; 

const int Reset = D4;

int CntDelayCoin = 0; //ดีเลย์การนับของเหรียญ
boolean FlagCoin = false;

int Coin_1 = 0;
int Coin_2 = 0;
int Coin_5 = 0;
int Coin_10 = 0;

int BuffCoin = 0;

byte customChar1[] = {
  B00100,
  B11110,
  B10101,
  B11110,
  B10101,
  B11110,
  B00100,
  B00000
};

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   lcd.begin();
   lcd.backlight();
   
   lcd.clear();
   
   pinMode(Baht1,INPUT);
   pinMode(Baht2,INPUT_PULLUP);
   pinMode(Baht5,INPUT_PULLUP);
   pinMode(Baht10,INPUT_PULLUP);
   
   pinMode(Reset,INPUT_PULLUP);
   
   Coin_1 = EEPROM.read(0);
   Coin_2 = EEPROM.read(1);
   Coin_5 = EEPROM.read(2);
   Coin_10 = EEPROM.read(3); 

   lcd.createChar(0, customChar1);
}

void loop() {
  // put your main code here, to run repeatedly:
  ///////////////// Reset /////////////////////
  if(digitalRead(Reset)==LOW)
  {
    Coin_1 = 0;
    Coin_2 = 0;
    Coin_5 = 0;
    Coin_10 = 0;
    
   lcd.clear();
//    EEPROM.write(0,0);
//    EEPROM.write(1,0);
//    EEPROM.write(2,0);
//    EEPROM.write(3,0);
    CntDelayCoin=38;
    BuffCoin = 0;
  }
  ///////////////// Insert coin ///////////////
  if(digitalRead(Baht1)==LOW)
  {
    if(FlagCoin == false)
    {
       FlagCoin = true;
       CntDelayCoin = 0;
       
       BuffCoin = 1;
    }
  }
  else if(digitalRead(Baht2)==LOW)
  {
    if(FlagCoin == false)
    {
       FlagCoin = true;
       CntDelayCoin = 0;
       
       BuffCoin = 2;
    }
  }
  else if(digitalRead(Baht5)==LOW)
  {
    if(FlagCoin == false)
    {
       FlagCoin = true;
       CntDelayCoin = 0;
       
       BuffCoin = 5;
    }
  }
  else if(digitalRead(Baht10)==LOW)
  {
    if(FlagCoin == false)
    {
       FlagCoin = true;
       CntDelayCoin = 0;
       
       BuffCoin = 10;
    }
  }
  else
  {
    FlagCoin = false;
  }
  
  ////////////// Count Coin //////////////
  if(CntDelayCoin<40)
  {
    CntDelayCoin++;
  }
  
  
  if(CntDelayCoin==39)
  {
    if(BuffCoin==1)          // Type 1Baht
    {
      Coin_1++; 
//      EEPROM.write(0,Coin_1);
    }
    else if(BuffCoin==2)     // Type 2Baht
    {
      Coin_2++;
//      EEPROM.write(1,Coin_2);
    }
    else if(BuffCoin==5) // Type 5Baht
    {
      Coin_5++;
//      EEPROM.write(2,Coin_5);
    }
    else if(BuffCoin==10) // Type 10Baht
    {
      Coin_10++; 
//      EEPROM.write(3,Coin_10);
    }
    BuffCoin = 0;
    
    /////////////// Show Lcd /////////////////
    lcd.setCursor(0,0);
    lcd.print("[1]");
    lcd.print(Coin_1);
    lcd.print("  ");
  
    lcd.print("[2]");
    lcd.print(Coin_2);
    lcd.print(" ");
    
    lcd.print("[5]");
    lcd.print(Coin_5);
    lcd.print(" ");
    
    lcd.setCursor(0,1);
    lcd.print("[10]");
    lcd.print(Coin_10);
    lcd.print(" ");
    
    int ToTalBaht = (Coin_1+(Coin_2*2)+(Coin_5*5)+(Coin_10*10));
    
    lcd.print("T=");
    lcd.print(ToTalBaht);
    lcd.print("Baht");
    ///////////////////////////////////////////
    
    Serial.print("1Baht: ");
    Serial.println(Coin_1);
    Serial.print("2Baht: ");
    Serial.println(Coin_2);
    Serial.print("5Baht: ");
    Serial.println(Coin_5);
    Serial.print("10Baht: ");
    Serial.println(Coin_10);   
    
  }
  
 
  delay(10);
}
