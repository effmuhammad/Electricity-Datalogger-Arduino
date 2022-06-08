#include <PZEM004T.h>
#include <Wire.h>
#include <DS3231.h>
#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x3F,20,4);
PZEM004T pzem (11, 12); // Perangkat Lunak Serial pin 11 (RX) & 12 (TX) 
DS3231  rtc(SDA, SCL);
File myFile;

//int CH[0] = 34 //(pin sensor arus ch1)
//int CH[1] = 35 //(pin sensor arus ch1)
//int CH[2] = 32 //(pin sensor arus ch1)
//#define CH[2] (pin sensor arus ch3)

LiquidCrystal_I2C  lcd(0x3F,20,4);
DS3231  rtc(SDA, SCL);

void setup(){
  rtc.begin();
  lcd.begin();
  Serial.begin(115200);
  delay(3000);
  tampilan_awal();
}

void loop(){
  //read_pzem();
}

void tampilan_awal(){
  Serial.println("Trial Data Logger Arduino");
  Serial.println("nyebarilmu.com");
}

void menu(){
  
}

float read_pzem(){
   float tegangan = pzem.voltage();
   if (tegangan! == NAN) {
     Serial.print("Voltase:");
     Serial.print(voltase);
     Serial.println("V");
   } lain {
     Serial.println("Kesalahan pembacaan voltase");
   }

   float arus = pzem.current();
   if(current != NAN){
     Serial.print("Current: ");
     Serial.print(current);
     Serial.println("A");
   } else {
     Serial.println("Error reading current");
   }

   float daya = pzem.power();
   if(current != NAN){
     Serial.print("Power: ");
     Serial.print(power);
     Serial.println("W");
   } else {
     Serial.println("Error reading power");
   }

   float energi = pzem.energy();
   if(current != NAN){
     Serial.print("Energy: ");
     Serial.print(energy,3);
     Serial.println("kWh");
   } else {
     Serial.println("Error reading energy");
   }

   float frekuensi = pzem.frequency();
   if(current != NAN){
     Serial.print("Frequency: ");
     Serial.print(frequency, 1);
     Serial.println("Hz");
   } else {
     Serial.println("Error reading frequency");
   }

   float pf = pzem.pf();
   if(current != NAN){
     Serial.print("PF: ");
     Serial.println(pf);
   } else {
     Serial.println("Error reading power factor");
   }

   Serial.println();
   value = [tegangan, arus, daya, energi, frekuensi, pf]
   return value
}

float read_sensor(){
  int sensitivitas = 100; //100mV/A 
  int teganganoffset = 2500; //nilai pembacaan offset saat tidak ada arus yang lewat
  double tegangan = 00;
  double nilaiarus = 00;
  ch[0] = analogRead(CH1); 
  ch[1] = analogRead(CH2);
  ch[2] = analogRead(CH3);

  for(i=0,i<3;i++){
    ch[i] = analogRead(CH[i]);
    tegangan = (ch[i] / 4095.0) * 3300;
    nilaiarus = ((tegangan - teganganoffset) / sensitivitas);
  }  
}

void save_file(){
  myFile = SD.open("datalogger.txt", FILE_WRITE); //Membuka File datalogger.txt
  if (myFile){
    Serial.print(rtc.getDOWStr(1));
    Serial.print(",");
    myFile.print(rtc.getDOWStr(1));
    myFile.print(",");
    
    Serial.print(rtc.getDateStr());
    Serial.print(" -- ");
    myFile.print(rtc.getDateStr());
    myFile.print(" -- ");
    
    Serial.println(rtc.getTimeStr());
    Serial.print(" -- ");
    myFile.println(rtc.getTimeStr());
    myFile.print(" -- ");
    
    Serial.print(" suhu:");  
    Serial.println(rtc.getTemp());
    myFile.print(" suhu:");  
    myFile.println(rtc.getTemp());
    myFile.close();
  }
  else{
    Serial.println("Failed open datalogger.txt"); // jika gagal print error
  }
  delay(2000); //total jeda yaitu 5 detik karena proses penulisan data kurang lebih 3 detik
}
