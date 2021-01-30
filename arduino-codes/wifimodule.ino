#include <SoftwareSerial.h>                                   //SoftwareSerial library
#include <dht11.h>                                            //DHT11 sensor library

String agAdi = "Demagorgon2.4gHz";                 //Wifi SSID   
String agSifresi = "753159Can";           //WIFI Password

int rxPin = 10;                                               //ESP8266 RX pini
int txPin = 11;                                               //ESP8266 TX pini
int dht11Pin = 2;

String ip = "184.106.153.149";                                //Thingspeak ip adress
float tempr, humid;

dht11 DHT11;

SoftwareSerial esp(rxPin, txPin);                             //Serial comm pin settings

void setup() {  
  
  Serial.begin(9600);                                         //Start comm with serial port
  Serial.println("Started");
  esp.begin(115200);                                          //ESP8266 start serial comm.
  esp.println("AT");                                          //Chipset controll with AT command
  Serial.println("AT is Sent");
  while(!esp.find("OK")){                                     //Waiting for OK command
    esp.println("AT");
    Serial.println("ESP8266 not found.");
  }
  Serial.println("OK Commend Recieved");
  esp.println("AT+CWMODE=1");                                 //ESP8266 module setted as client
  while(!esp.find("OK")){                                     //Wait for OK
    esp.println("AT+CWMODE=1");
    Serial.println("Setting Up....");
  }
  Serial.println("Set up as client");
  Serial.println("Connecting Network...");
  esp.println("AT+CWJAP=\""+agAdi+"\",\""+agSifresi+"\"");    //Connect network
  while(!esp.find("OK"));                                     //Wait for connecting OK
  Serial.println("Connected.");
  delay(1000);
}
void loop() {
  esp.println("AT+CIPSTART=\"TCP\",\""+ip+"\",80");           //Thingspeak connection
  if(esp.find("Error")){                                      //Checking errors.
    Serial.println("AT+CIPSTART Error");
  }
  DHT11.read(dht11Pin);
  tempr = (float)DHT11.temperature;
  humid = (float)DHT11.humidity;
  String veri = "GET https://api.thingspeak.com/update?api_key=OE6M5TZI4G6KSEHP";   //Thingspeak api url, key is project key.
  veri += "&field1=";
  veri += String(tempr);                                        //temperature value
  veri += "&field2=";
  veri += String(humid);                                        //humidity value
  veri += "\r\n\r\n"; 
  esp.print("AT+CIPSEND=");                                   //Data lenght to send with ESP
  esp.println(veri.length()+2);
  delay(2000);
  if(esp.find(">")){                                          //When ESP8266 is ready, 
    esp.print(veri);                                          //Data is sent.
    Serial.println(veri);
    Serial.println("Data is sent.");
    delay(1000);
  }
  Serial.println("Baglantı Kapatildi.");
  esp.println("AT+CIPCLOSE");                                //Closing Connection
  delay(1000);                                               //Delay for new data sending
}
