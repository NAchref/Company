#include <SPI.h>
#include <Adafruit_GFX.h>
#include <TFT_ILI9163C.h>

#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid     = "TOPNET2F8EEEAE";
const char *password = "0335E957EB";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String formattedDate;
String dayStamp;
String timeStamp;

// Definition of COLORS
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0

/*Connections to NodeMCU

LED to 3V3
SCK to D5
SDA to D7
A0/DC to D1
RST to D2
CS to D4
GND to GND
VCC to 3V3
*/

#define CS D4
#define DC D2
#define RST D1

// Declare an instance of the ILI9163
TFT_ILI9163C tft = TFT_ILI9163C(CS, RST, DC);

void setup() {
tft.begin();
tft.fillScreen();
Serial.begin(9600);

WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
  timeClient.setTimeOffset(3600);
}

void loop(){
  timeClient.update();
  
  tft.setCursor(10, 20);
tft.setTextColor(BLUE);
tft.setTextSize(1);

formattedDate = timeClient.getFormattedDate();
 int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
 /* Serial.print("DATE: ");
  Serial.println(dayStamp);*/
  // Extract time
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
 /* Serial.print("HOUR: ");
  Serial.println(timeStamp);*/

tft.println(dayStamp);

tft.setCursor(10, 40);
tft.println(timeStamp);



  if(Serial.available()>0)
{
  tft.setCursor(10, 60);
tft.setTextColor(BLUE);
tft.setTextSize(1);
tft.println(Serial.readString());
  
}




}

unsigned long testText() {

tft.setCursor(10, 40);
tft.setTextColor(BLUE);
tft.setTextSize(1);
tft.println("NodeMCU DOIT");
tft.setCursor(10, 63);
//tft.println(“1.44 TFT LCD”);
}
