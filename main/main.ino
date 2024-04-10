#include <Wire.h>
#include <RTClib.h>
#define BLYNK_PRINT Serial
#include <Simpletimer.h>
#include <Blynk.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "RTClib.h"
#include <SD.h>
#include <SPI.h>
#include "FS.h"

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "my07LK43cr97y9MoXPNs48WEfiNAayhx";
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Sat";
char pass[] = "agus9876";

// sensors 
const int vs1 = 34; // vibration sensor
const int vs2 = 35;
const int vs3 = 32;
const int vs4 = 33;
const int vs5 = 36;
const int vs6 = 39; 

int sdata1;
int sdata2; 
int sdata3;
int sdata4;
int sdata5;
int sdata6; // sensor data will be3 stored in this variable.
String vdata1, vdata2, vdata3, vdata4, vdata5, vdata6, tanggal= ""; 
float hasil1, hasil2, hasil3, hasil4, hasil5, hasil6;
//DS3231 Clock;
// Inisialisasi RTC & SD Card
RTC_DS1307 rtc;
char namaHari[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};
File myFile;
const int CS = 5;
String hasilSD;
char cHasilSD[500];
void setup()
{
  // Debug console
  Serial.begin(115200);
   Wire.begin();
  SD.begin(CS);
  pinMode(CS, OUTPUT);
  pinMode(vs1 ,INPUT); 
  pinMode(vs2 ,INPUT); 
  pinMode(vs3 ,INPUT); 
  pinMode(vs4 ,INPUT); 
  pinMode(vs5 ,INPUT); 
  pinMode(vs6 ,INPUT); 
  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
//  timer.setInterval(10L,sensorvalue); // 1000L
//  setSyncProvider(RTC.get);
  if (!SD.begin(CS)) {
  Serial.println("Gagal Memuat Kartu SD");
  return;
  }
  uint8_t cardType = SD.cardType();
  if (cardType == CARD_NONE) {
  Serial.println("Tidak Ada Kartu SD");
  return;
  }
  Serial.println("Menginisialisasi kartu SD...");
  
  //RTC
  if (! rtc.begin()) {
    Serial.println("RTC TIDAK TERBACA");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//update rtc dari waktu komputer
  }
//    writeFile(SD, "/vibrationMonitoring.txt", " test "); //membuat file
}

void loop()
{
  Blynk.run();
Serial.println("");
  Blynk.virtualWrite(V2, "                                           "); 
   DateTime now = rtc.now();
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(" ");
  Serial.print(namaHari[now.dayOfTheWeek()]);
  Serial.print(',');
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.println();

  tanggal = tanggal + now.hour() + ":" +  now.minute()+ ":" + now.second()+ " " + namaHari[now.dayOfTheWeek()] + "," +  now.day()+ "/" + now.month()+ "/" + now.year();
  Blynk.virtualWrite(V2, tanggal);
  tanggal = ""; 
  delay(50);
  
//float konversi;
//konversi = 2;
  Serial.println("Vibrasi Motor");
  Serial.println("Inboard");
  Blynk.virtualWrite(V2,"Vibrasi Motor" );
  Blynk.virtualWrite(V2,"Inboard" );

  

 sdata1=analogRead(vs1);
 long piezo1 = map(sdata1, 0, 4095, 0, 65536);
 if(piezo1==0){ 
  hasil1=0;
 }else {
 hasil1= ((piezo1*0.000037)+0.65);
 }
  Serial.print("Vertikal: ");Serial.print(hasil1);Serial.println(" mm/s");
 // Blynk.virtualWrite(V3, piezo1);
vdata1 = vdata1 + "Vertikal: " + hasil1+ " mm/s";  
  Blynk.virtualWrite(V2, vdata1);
vdata1 = ""; 


 sdata2=analogRead(vs2);
long piezo2 = map(sdata2, 0, 4095, 0, 65536);
if(piezo2==0){
  hasil2=0;
}else{
hasil2= ((piezo2*0.000037)+0.65);
}

  Serial.print("Horizontal: ");Serial.print(hasil2);Serial.println(" mm/s");//65536
 // Blynk.virtualWrite(V3, piezo2);
vdata2 = vdata2 + "Horizontal: " + hasil2 + " mm/s";  
  Blynk.virtualWrite(V2, vdata2);
vdata2 = ""; 


sdata3=analogRead(vs3);
long piezo3 = map(sdata3, 0, 4095, 0, 65536);
if(piezo3==0){
   hasil3=0; 
}else{
 hasil3= ((piezo3*0.000037)+0.65);
}
  Serial.print("Aksial: ");Serial.print(hasil3);Serial.println(" mm/s");
 // Blynk.virtualWrite(V3, piezo3);
vdata3 = vdata3 + "Aksial: " + hasil3 + " mm/s";  
  Blynk.virtualWrite(V2, vdata3);
vdata3 = "";


Blynk.virtualWrite(V2,"Outboard" );
Serial.println("Outboard");

sdata4=analogRead(vs4);
 long piezo4 = map(sdata4, 0, 4095, 0, 65536);
 if(piezo4==0){
hasil4=0;
 }else{
 hasil4= ((piezo4*0.000037)+0.65);
 }
  Serial.print("Vertikal: ");Serial.print(hasil4);Serial.println(" mm/s");
  //Blynk.virtualWrite(V3, piezo4);
vdata4 = vdata4 + "Vertikal: " + hasil4 + " mm/s";  
  Blynk.virtualWrite(V2, vdata4);
vdata4 = ""; 


sdata5=analogRead(vs5);
long piezo5 = map(sdata5, 0, 4095, 0, 65536);
if(piezo5==0){
hasil5=0;
}else{
 hasil5= ((piezo5*0.000037)+0.65);
}
  Serial.print("Horizontal: ");Serial.print(hasil5);Serial.println(" mm/s");
  //Blynk.virtualWrite(V3, piezo5);
vdata5 = vdata5 + "Horizontal: " + hasil5 + " mm/s";  
  Blynk.virtualWrite(V2, vdata5);
vdata5 = ""; 

sdata6=analogRead(vs6);
long piezo6 = map(sdata6, 0, 4095, 0, 65536);
  if(piezo6==0){
 hasil6=0;
  }else{
hasil6= ((piezo6*0.000037)+0.65);
}
  Serial.print("Aksial: ");Serial.print(hasil6);Serial.println(" mm/s");
 // Blynk.virtualWrite(V3, piezo6);
vdata6 = vdata6 + "Aksial: " + hasil6 + " mm/s";  
  Blynk.virtualWrite(V2, vdata6);
vdata6 = ""; 

 
 hasilSD = hasilSD  +  now.hour() + ":" + now.minute() + ":" + now.second() + "  " + namaHari[now.dayOfTheWeek()] + "," + now.day() + "/" + now.month() + "/" + now.year() + "\n" + "Vibrasi Motor" + "\n" + "Inboard" + "\n" + "Vertikal: " + hasil1 + " mm/s" + "\n" + "Horizontal: " + hasil2 + " mm/s" + "\n" + "Aksial: " + hasil3 + " mm/s" + "\n" + "Outboard" + "\n" +  "Vertikal: " + hasil4 + " mm/s" + "\n" + "Horizontal: " + hasil5 + " mm/s" + "\n" + "Aksial: " + hasil6 + " mm/s" + "\n" + "\n"; 
  hasilSD.toCharArray(cHasilSD, 500);     //menjadikan hasilSD menjadi char array
  appendFile(SD, "/vibrationMonitoring.txt", cHasilSD);   //menambahkan data ke file
  hasilSD = ""; 
  delay(10000);
}
void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}
