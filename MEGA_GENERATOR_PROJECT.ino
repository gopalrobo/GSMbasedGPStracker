

#include <TinyGPS.h>
TinyGPS gps;
String state;
int flag=0;
void setup(){


  Serial.begin(9600);
  Serial.println("Arduino serial initialized!");
  delay(10);

  Serial1.begin(9600);
  Serial.println("GSM initialized!");
  delay(10);
  Serial2.begin(9600);
  Serial.println("GPS serial initialized!");
  delay(10);
  pinMode(5,INPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
  
}

void loop(){
  
  char x;
  if(Serial.available())
  {
    x=Serial.read();
    switch(x)
    {
      case'a':  issueCommand("AT");
                break;
      case'z':  issueCommand("ATH");
                break;
      case'y':  issueCommand("ATA");
                break;
      case'b':  issueCommand("ATD7904542651;");
                break;
      case'c':  issueCommand("AT+CLIP=0");
                break;
      case'd':issueCommand("AT+CNMI=1,2,0,0,0");
              break;
      case'e':issueCommand("AT+CMGF=1");
              break;
      case'f':Serial1.print("AT+CMGL=");
             Serial1.print('"');
             Serial1.print("ALL");
             Serial1.println('"');
             delay(10);
              break;
      case'g':Serial1.print("AT+CMGS=\""); // send the SMS number
              Serial1.print("7904542651");
              Serial1.println("\"");
              delay(1000);
             Serial1.print("hai h r u");
             delay(1000);
             Serial1.write(0x1A);
             Serial1.write(0x0D);
             Serial1.write(0x0A);
             delay(10);
              break;
              
              
    }
  }
    if((digitalRead(5)==HIGH)&&(flag==0))
      {
            flag=1;
            state="ON";
            Serial.println("DIGITAL HIGH");
            Serial.println(get_lat());
            Serial.println(get_long());
            sms(get_lat(),get_long(),state);
            Serial.println();
      }

      if((digitalRead(5)==LOW)&&(flag==1))
      {
        flag=0;
        state="OFF";
        Serial.println("DIGITAL LOW");
        Serial.println(get_lat());
        Serial.println(get_long());
        sms(get_lat(),get_long(),state);
        Serial.println();
      } 
  //Serial.println(get_long());
  //Serial.println(get_lat()); 
  smartdelay(100);
  readSerial();
  delay(500);

}
String get_long()
    {
      float flat,flon;
      unsigned long age;
      gps.f_get_position(&flat, &flon, &age);
       if(flon==TinyGPS::GPS_INVALID_F_ANGLE)
       {
        return "SIGNAL NOT FOUND";
       }
       else
       {
        return(String(flon,6));
       }
    //gps.f_get_position(&flat, &flon, &age);
    }
 String get_lat()
  {
    float flat,flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
     if(flat==TinyGPS::GPS_INVALID_F_ANGLE)
     {
      return "SIGNAL NOT FOUND";
     }
     else
     {
      return(String(flat,6));
     }
  //gps.f_get_position(&flat, &flon, &age);
  }
static void smartdelay(unsigned long ms)
  {
    unsigned long start = millis();
    do 
    {
      while (Serial2.available())
        gps.encode(Serial2.read());
    } while (millis() - start < ms);
 }
void sms(String flat,String flon,String stat)
    {
          Serial.println("SMS");
          Serial1.print("AT+CMGS=\""); // send the SMS number
          Serial1.print("7010567337");
          Serial1.println("\"");
          delay(1000);
          Serial1.print("DEVICE SWITCHED ");
          Serial1.println(stat);
          
            if(flat=="SIGNAL NOT FOUND" || flon=="SIGNAL NOT FOUND")
            { 
              
            Serial1.print("POS:GPS SIGNAL NOT FOUND TRY WITH STATUS  COMMAND AFTER SOME TIME Sorry For The Inconvenience ");
            
              
            }
            else
            {
              Serial1.print("POS:https://maps.google.com/?q=");
              Serial1.print(flat);
              Serial1.print(",");
              Serial1.print(flon);
             
           }
              delay(1000);
              Serial1.write(0x1A);
              Serial1.write(0x0D);
              Serial1.write(0x0A);
              delay(10);

    
    } 


void issueCommand(char* msg){
  Serial1.println(msg);
  delay(10);
}

void readSerial(){

  String y,phone,command;
  while (Serial1.available()){
    y=Serial1.readString();
    Serial.println( y);
    Serial.println( y.substring(2,6));
    Serial.println( y.substring(9,22));
    Serial.println( y.substring(y.length()-8,y.length()-2));
    phone= y.substring(9,22);
    command= y.substring(y.length()-8,y.length()-2);
    if(y.substring(2,6)=="+CMT"&& phone=="+917010567337"&&command=="Status")
    {
        sms(get_lat(),get_long(),state);     
    }
}
}
