#include <Wire.h>
#define Led 13
#define DS3231_I2C_ADDRESS 0x68

//**************************** SAAT TANIMLANIYOR  *************************

byte second, minute, hour,dayOfTheWeek, dayOfMonth, month, year; 
byte decToBcd(byte val){
  return ( (val / 10 * 16) + (val % 10) );
}
byte bcdToDec(byte val){
  return ( (val / 16 * 10) + (val % 16) );
}


void setup (){
  Serial.begin    (9600);
  Wire.begin          ();
  pinMode  (Led, OUTPUT);   
  digitalWrite(Led, LOW);  
}

void loop (){
   displayTime();
   if ( hour == 15 && minute == 04 ) {        // Saat 00.00sa
   digitalWrite(Led, HIGH);                   // Saat Ve Dakika Doğru İse Ledi Yak
    }                                           
  
   if ( hour == 15 && minute == 05 ) {        // Saat 00.00sa
   digitalWrite(Led, LOW);                    // Saat Ve Dakika Doğru İse Ledi Söndür
    }
  }  
  
//***************** DS3231 REAL TİME CLOCK  *************************

  void save() {                               // Saati Ayarlamak İstiyorsanız İşlem Sonunda "save" Etmeniz Gerekmektedir...
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);                   
  Wire.write(decToBcd(second));     // set seconds
  Wire.write(decToBcd(minute));     // set minutes
  Wire.write(decToBcd(hour));       // set hours
  Wire.write(decToBcd(dayOfTheWeek));  // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month));      // set month
  Wire.write(decToBcd(year));       // set year (0 to 99)
  Wire.endTransmission();
}
//*******************************************************************

  void readDS3231time(  // DS3231'den Saat Okunuyor
  byte *second,
  byte *minute,
  byte *hour,
  byte *dayOfTheWeek,
  byte *dayOfMonth,
  byte *month,
  byte *year)
  
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  *second       = bcdToDec(Wire.read() & 0x7f);
  *minute       = bcdToDec(Wire.read());
  *hour         = bcdToDec(Wire.read() & 0x3f);
  *dayOfTheWeek = bcdToDec(Wire.read());
  *dayOfMonth   = bcdToDec(Wire.read());
  *month        = bcdToDec(Wire.read());
  *year         = bcdToDec(Wire.read());
 
    
    Serial.print("Tarih: ");
    Serial.print(*dayOfMonth  );
    Serial.print('/');
    Serial.print(*month);
    Serial.print('/');
    Serial.print(*year);
    Serial.println("\t");
    //Serial.println(*dayOfTheWeek);
    Serial.print("Saat:  ");
    Serial.print(*hour);
    Serial.print(':');
    Serial.print(*minute);
    Serial.print(':');
    Serial.print(*second);
    Serial.println();
    Serial.println("-----------------------");
    
    delay(1000);
}

//********************* SAAT OKU ************************************

  void displayTime() {
  readDS3231time(&second, &minute, &hour, &dayOfTheWeek, &dayOfMonth, &month,
                 &year);
}
