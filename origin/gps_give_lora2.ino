#include <HardwareSerial.h>

#include <TinyGPSPlus.h>


HardwareSerial lora(1); //lora 통신방법 

HardwareSerial gps(2);


TinyGPSPlus Tiny; //gps libarry

static const uint32_t GPSBaud = 57600; //baud rate

// setup 은 실행시 한번 실행
void setup() {
  
  Serial.begin(57600);
  
  gps.begin(9600,SERIAL_8N1,26,27); //gps
  lora.begin(9600,SERIAL_8N1,16,17); //lora
  delay(100);
//
//
  gps.write("$PMTK251,57600*2C\r\n");   // gps baudrate 57600
//gps.write("$PMTK251,115200*1F\r\n");  // gps baudrate 115200
  delay(100); 
  
  gps.begin(57600,SERIAL_8N1,26,27);  //gps serial reset to 57600
//gps.begin(115200,SERIAL_8N1,26,27); //gps serial reset to 115200 
  delay(100);

  
  gps.write("$PMTK220,200*2C\r\n");      //  fix interval. 0.2s
//gps.write("$PMTK220,100*2F\r\n");      //  fix interval. 0.1s
  delay(100);
  
  Serial.println(F("ready"));

}

// loop 계속 반
void loop()
{
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 100;) // 100ms 마다 한번
  {
    while (gps.available())
    {
      if (Tiny.encode(gps.read()))
      {
        newData = true;
      }
    }
  }

  //If newData is true
  if(newData == true)
  {
    newData = false;
    gpsInfo();
  }
  else
  {
    lora.println("noData");
   
  }  

}

void gpsInfo() //gps information 지금은 따로 찔끔찔끔 보내는데 모아서 한뭉텅이로 보내야함.
{
  lora.print(F("Location: ")); //
  if (Tiny.location.isValid())
  {
    lora.print(Tiny.location.lat(), 6);
    lora.print(F(","));
    lora.print(Tiny.location.lng(), 6);
  }
  else
  {
    lora.print(F("INVALID"));
  }

  lora.print(F(" "));
  if (Tiny.time.isValid())
  {
    if (Tiny.time.hour() < 10) lora.print(F("0"));
    lora.print(Tiny.time.hour());
    lora.print(F(":"));
    if (Tiny.time.minute() < 10) lora.print(F("0"));
    lora.print(Tiny.time.minute());
    lora.print(F(":"));
    if (Tiny.time.second() < 10) lora.print(F("0"));
    lora.print(Tiny.time.second());
    lora.print(F("."));
    if (Tiny.time.centisecond() < 10) lora.print(F("0"));
    lora.print(Tiny.time.centisecond());
  }
  else
  {
    lora.print(F("INVALID"));
  }

  lora.println();

}
