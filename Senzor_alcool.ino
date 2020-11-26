#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //Setting MAC Address

LiquidCrystal_I2C lcd(0x27, 16, 2);

char server[] = "192.168.2.183";
IPAddress ip(192,168,0,177); 
EthernetClient client; 

const int btnPin = 2;
const int AOUT = A0;
int btnNew, btnOld, state;
float ethVal, sensorValOld, sensorValNew, voltage;
float avgVal = 0;
int dt = 100;
int dt2 = 500;
int dt3 = 300;
int dt4 = 2000;

void setup() {
  // put your setup code here, to run once:
  pinMode(AOUT, INPUT);
  pinMode(btnPin, INPUT);
  digitalWrite(btnPin, HIGH);
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }
}

void sendToDB()   //CONNECTING WITH MYSQL
{
   if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    Serial.print("GET /mq3/mq3.php?value=");
    client.print("GET /mq3/mq3.php?value=");     //YOUR URL
    Serial.println(avgVal);
    client.print(avgVal);
    client.print(" ");      //SPACE BEFORE HTTP/1.1
    client.print("HTTP/1.1");
    client.println();
    client.println("Host: 192.168.2.183");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  btnOld = btnNew;
  btnNew = digitalRead(btnPin);
  if (btnOld == 1 && btnNew == 0) /// ON/OFF button for readings
  {
    if (state == 1)
    {
      /// the sensor is reading
      state = 0;
      lcd.clear();
    }
    else
    {
      state = 1;
    }
  }
  if (state == 1) /// Button ON => sensor reads values
  {
    lcd.setCursor(0,0);
    lcd.print("Sensor voltage:");
    avgVal = 0;
    for (int i = 1; i <= 100; i++) /// increased no. of readings for increased accuracy
    {
      sensorValNew = analogRead(AOUT);
      voltage = (float)sensorValNew/1024*5.0;
      avgVal += voltage;
    }
    avgVal /= 100;
    //Serial.print("The sensor input voltage is: ");
    //Serial.print(avgVal);
    //Serial.println(" V");
    lcd.setCursor(0,1);
    lcd.print(avgVal);
    lcd.print(" V");
    sendToDB();
    delay(dt4);  
  }
    delay(dt);
}
