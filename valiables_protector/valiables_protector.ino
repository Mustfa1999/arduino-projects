#include <TinyGPS++.h>                                  // Tiny GPS Plus Library
#include <SoftwareSerial.h>                             // Software Serial Library so we can use other Pins for communication with the GPS module
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial

unsigned int move_index = 1;                            // fixed location for now

TinyGPSPlus gps;                                        // Create an Instance of the TinyGPS++ object called gps
SoftwareSerial ss(D6, D7);  // Rx, Tx
WidgetMap myMap(V0);                                    // V0 for vitrual pin of Map Widget
BlynkTimer timer;


char auth[] = "yFdWT9jVulw56pvJebjs1YXRYfYJYdbf"; 
//char ssid[] = "Umniah-evo-Home-D8BC";
//char pass[] = "startpch";

char ssid[] = "Mustfa";
char pass[] = "12345678";

void setup()
{  
  Serial.begin(9600);
  pinMode(D5, INPUT);
  Blynk.begin(auth, ssid, pass);
  delay(1500);
  Serial.println("WiFi Connected!");
  delay(3000);                                         
  ss.begin(9600);                                   
  timer.setInterval(5000L, checkGPS);
}



void checkGPS(){
  if (gps.charsProcessed() < 10)
  { Serial.println(F("No GPS detected: check wiring.")); }
}


void displayInfo()
{if (gps.location.isValid() ) 
  { float latitude = (gps.location.lat());     //Storing the Lat. and Lon. 
    float longitude = (gps.location.lng()); 
    
    Serial.print("LAT:  ");
    Serial.println(latitude, 6);  // float to x decimal places
    Serial.print("LONG: ");
    Serial.println(longitude, 6);  
    
    myMap.location(move_index, latitude, longitude, "GPS_Location");                 
  }
 Serial.println();
}

void loop()
{  
  Blynk.run();
  timer.run();

  Serial.print("LAT: ");
  Serial.println(gps.location.lat(),5);
  Serial.print("LON: ");
  Serial.println(gps.location.lng(),5);
  Serial.println("\n");

  while(ss.available() > 0)
  {if (gps.encode(ss.read()))
      displayInfo();}
}
