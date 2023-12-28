#include <TinyGPS++.h>
// #include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

// シリアル通信に使用するpinを指定。
int RXPin = 2;  // D4
int TXPin = 16; // D0

int GPSBaud = 9600;

// TinyGPS++オブジェクトを作成する
TinyGPSPlus gps;

// 「gpsSerial」というソフトウェアシリアルポートを作成します
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup()
{
  // シリアルポートを9600で起動します
  Serial.begin(9600);

  // Wait for Serial is ready
  while ( !Serial ) {
  }

  gpsSerial.begin(GPSBaud);
}

void loop()
{

  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();

  // 5000ミリ秒が経過し、文字が入力されていない場合「No GPS detected」とエラーを表示します。
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
  }
  else
  {
    Serial.println("Location: Not Available");
  }
  
  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
  }
  else
  {
    Serial.println("Not Available");
  }

  Serial.println();
  Serial.println();
  delay(1000);
}