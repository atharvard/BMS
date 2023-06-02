    #include<LiquidCrystal.h>
        LiquidCrystal lcd(2,3,4,5,6,7);
        
        #include "ACS712.h"
        #include <EEPROM.h>
        
        #include "DHT.h"
        #define DHTPIN A15 
        
        #define DHTTYPE DHT11
        
        #define A_1 A9
        #define A_2 A7
        #define A_3 A5
        #define A_4 A3
        #define A_5 A1
        #define A_6 A10
        
        float adc1 = 0.0;
        float in1 = 0.0;
        
        float adc2 = 0.0;
        float in2 = 0.0;
        
        float adc3 = 0.0;
        float in3 = 0.0;
        
        float adc4 = 0.0;
        float in4 = 0.0;
        
        float adc5 = 0.0;
        float in5 = 0.0;
        
        float adc6 = 0.0;
        float in6 = 0.0;
         
        float R1 = 30000.0;
        float R2 = 7500.0; 
         
        float ref_voltage = 5.0;
        int adc_v1 = 0;
        int adc_v2 = 0;
        int adc_v3 = 0;
        int adc_v4 = 0;
        int adc_v5 = 0;
        int adc_v6 = 0;
        
        float t = 0.0;
        float h = 0.0;
        
        int o = 0;
        
           float I1; 
           float I2;
           float I3; 
           float I4;
           float I5; 
        
        int SOC;  int soc1 = 0;int soc2 = 0;int soc3 = 0;int soc4 = 0;int soc5 = 0;
        int SOH;
        float time; // Time in seconds
        float remainingCapacity; // Remaining capacity of the battery in Ah
        float nominalCapacity; // Rated capacity of the battery in Ah
        
        int sw1 = 0;
        int sw = 0;
        int chr = 0;
        int s = 0; int m = 0; int h1 = 0;
        
        unsigned long startMillis;  
        unsigned long currentMillis;
        const int period = 1000; 
        float totalCoulumbs = 0.0;
        
        DHT dht(DHTPIN, DHTTYPE);
        
        void setup()
        {
           lcd.begin(20,4);
        Serial.begin(9600);
        Serial.println("CLEARDATA"); 
        Serial.println("LABEL,tIME,C1,C2,C3,C4,C5,I1,I2,I3,I4,I5,VOLTAGE,WATT,TEMPRETURE,HUMIDITY,SOC (%),SOH (%),SOC CELL 1,SOC CELL 2,SOC CELL 3,SOC CELL 4,SOC CELL 5"); 
        Serial.println("RESETTIMER");
        SOH = EEPROM.read(0);
        pinMode(8,INPUT_PULLUP);
        dht.begin();
        pinMode(12,OUTPUT);
        
        pinMode(53,OUTPUT);
        pinMode(51,OUTPUT);
        pinMode(49,OUTPUT);
        pinMode(47,OUTPUT);
        pinMode(45,OUTPUT);
        }
         
        void loop(){
            sw1 = digitalRead(8);
            
           adc_v1 = analogRead(A_1);
           adc1  = (adc_v1 * ref_voltage) / 1024.0; 
           in1 = adc1 / (R2/(R1+R2)) ; 
        
           adc_v2 = analogRead(A_2);
           adc2  = (adc_v2 * ref_voltage) / 1024.0; 
           in2 = adc2 / (R2/(R1+R2)) ;
        
           adc_v3 = analogRead(A_3);
           adc3  = (adc_v3 * ref_voltage) / 1024.0; 
           in3 = adc3 / (R2/(R1+R2)) ;
        
           adc_v4 = analogRead(A_4);
           adc4  = (adc_v4 * ref_voltage) / 1024.0; 
           in4 = adc4 / (R2/(R1+R2)) ;
        
           adc_v5 = analogRead(A_5);
           adc5  = (adc_v5 * ref_voltage) / 1024.0; 
           in5 = adc5 / (R2/(R1+R2)) ;
        
           adc_v6 = analogRead(A_6);
           adc6  = (adc_v6 * ref_voltage) / 1024.0; 
           in6 = adc6 / (R2/(R1+R2)) ;
        
           chr = analogRead(A10);
        
           h = dht.readHumidity();
           t = dht.readTemperature();
        
           soc1 = map((in1-in2) , 0 , 4.1 , 0 , 100);
           soc2 = map((in2-in3) , 0 , 4.1 , 0 , 100);
           soc3 = map((in3-in4) , 0 , 4.1 , 0 , 100);
           soc4 = map((in4-in5) , 0 , 4.1 , 0 , 100);
           soc5 = map(in5 , 0 , 4.1 , 0 , 100);
           SOC = map(in1 , 0 , 20.5 , 0 , 100);
        
         I1 = 0;I2 = 0;I3 = 0;I4 = 0;I5 = 0;
        for(int i = 0; i < 600; i++) {
             I1 = I1 + (.0264 * analogRead(A0) -13.51);
             I2 = I2 + (.0264 * analogRead(A2) -13.51);
             I3 = I3 + (.0264 * analogRead(A4) -13.51);
             I4 = I4 + (.0264 * analogRead(A6) -13.51);
             I5 = I5 + (.0264 * analogRead(A8) -13.51);
             digitalWrite(12,LOW);
           delay(1);
         }
        
        
          if((in1-in2) > 3.9){digitalWrite(53,HIGH);delay(100);digitalWrite(53,LOW);delay(100);}else{digitalWrite(53,LOW);}
          if((in2-in3) > 3.9){digitalWrite(51,HIGH);delay(100);digitalWrite(53,LOW);delay(100);}else{digitalWrite(51,LOW);}
          if((in3-in4) > 3.9){digitalWrite(49,HIGH);delay(100);digitalWrite(53,LOW);delay(100);}else{digitalWrite(49,LOW);}
          if((in4-in5) > 3.9){digitalWrite(47,HIGH);delay(100);digitalWrite(53,LOW);delay(100);}else{digitalWrite(47,LOW);}
          if(in5 > 3.9){digitalWrite(45,HIGH);delay(100);digitalWrite(53,LOW);delay(100);}else{digitalWrite(45,LOW);}
          
          if(in6 > 1.0)
          {
               lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("C1:");
          lcd.print(in1-in2, 2);lcd.print('V');
        
          lcd.setCursor(10,0);
          lcd.print("|C2:");
          lcd.print(in2-in3, 2);lcd.print('V');
        
          lcd.setCursor(0,1);
          lcd.print("C3:");
          lcd.print(in3-in4, 2);lcd.print('V');
          
          lcd.setCursor(10,1);
          lcd.print("|C4:");
          lcd.print(in4-in5, 2);lcd.print('V');
        
          lcd.setCursor(0,2);
          lcd.print("C5:");
          lcd.print(in5, 2);lcd.print('V');
        
        
        lcd.setCursor(10,2);
          lcd.print("|V :");
          lcd.print(in1, 2);lcd.print('V');
          
          lcd.setCursor(0,3);
          lcd.print("SOC:");
          lcd.print(SOC);lcd.print('%');
        
          if(chr == 0){
          lcd.setCursor(10,3);
          lcd.print("|CH: 00V");
          }
          else
          {
            lcd.setCursor(10,3);
          lcd.print("|CH: 24V");
          }
          if((in1-in2) > 4.1 && (in2-in3) > 4.1 &&(in3-in4) > 4.1 &&(in4-in5) > 4.1 && in5 > 4.1)
          {
            lcd.clear();
            lcd.setCursor(3,1);
            lcd.print("Warning !!!");
            lcd.setCursor(0,2);
            lcd.print("Battery Full Charged");
            delay(1000);
          }
          }
          else
          {
          if(sw1 == LOW){sw = 1; lcd.clear(); lcd.print("testing Starts");delay(1000);}
        
          if(sw == 0)
          {
           o++;
          if(o < 5)
          {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("C1:");
          lcd.print(in1-in2, 2);lcd.print('V');
        
          lcd.setCursor(10,0);
          lcd.print("|C2:");
          lcd.print(in2-in3, 2);lcd.print('V');
        
          lcd.setCursor(0,1);
          lcd.print("C3:");
          lcd.print(in3-in4, 2);lcd.print('V');
          
          lcd.setCursor(10,1);
          lcd.print("|C4:");
          lcd.print(in4-in5, 2);lcd.print('V');
        
          lcd.setCursor(0,2);
          lcd.print("C5:");
          lcd.print(in5, 2);lcd.print('V');
        
          lcd.setCursor(10,2);
          lcd.print("|T:");
          lcd.print(t);
        
          lcd.setCursor(0,3);
          lcd.print("V:");
          lcd.print(in1);lcd.print("V");
        
          lcd.setCursor(10,3);
          lcd.print("|SOC:");
          lcd.print(SOC);lcd.print('%');
          }
          else
          {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("I1:");
          lcd.print((I1/1000)/2);lcd.print('A');
        
          lcd.setCursor(10,0);
          lcd.print("|I2:");
          lcd.print((I2/1000)/2);lcd.print('A');
        
          lcd.setCursor(0,1);
          lcd.print("I3:");
          lcd.print((I3/1000)/2);lcd.print('A');
          
          lcd.setCursor(10,1);
          lcd.print("|I4:");
          lcd.print((I4/1000)/2);lcd.print('A');
        
          lcd.setCursor(0,2);
          lcd.print("I5:");
          lcd.print((I5/1000)/2);lcd.print('A');
        
          lcd.setCursor(10,2);
          lcd.print("|H:");
          lcd.print(h);
        
          lcd.setCursor(0,3);
          lcd.print("P :");
          lcd.print((in1*(((I1/1000)/2)*1000))/1000);lcd.print('W');
        
          lcd.setCursor(10,3);
          lcd.print("|SOH:");
          lcd.print(SOH);lcd.print('%');
          }
          if(o == 11){o = 0;}
          }
          else
          {
              s++; if(s == 60){s = 0; m++;} if(m == 60){h1++; m = 0;}
        
           time = millis() / 1000.0;
           remainingCapacity -= (((I1/1000)/2) * time) / 3600.0;
           nominalCapacity = 1.2;
           SOH  = (remainingCapacity / nominalCapacity) * 100.0;
           
              lcd.clear();
              lcd.print("TIME :- ");lcd.print(h1);lcd.print(':');lcd.print(m);lcd.print(':');lcd.print(s);
        
              lcd.setCursor(0,1);
              lcd.print("V :");lcd.print(in1);lcd.print('V');
              lcd.setCursor(10,1);
              lcd.print("|I :");lcd.print((I1/1000)/2);lcd.print('A');
              lcd.setCursor(0,2);
              lcd.print("P :");lcd.print(in1 * (I1/1000)/2);lcd.print('W');
              lcd.setCursor(10,2);
              lcd.print("|T :"); lcd.print(t);
              lcd.setCursor(0,3);
              lcd.print("SOC :"); lcd.print(SOC);lcd.print('%');
              lcd.setCursor(10,3);
              lcd.print("|SOH :"); lcd.print(SOH);lcd.print('%');
              
              if(s == 59)
              {
          Serial.print("DATA,TIME,");
          Serial.print(in1-in2);
          Serial.print(',');
          Serial.print(in2-in3);
          Serial.print(',');
          Serial.print(in3-in4);
          Serial.print(',');
          Serial.print(in4-in5);
          Serial.print(',');
          Serial.print(in5);
          Serial.print(',');
          if(I1 < 0.1){Serial.print("0.0");}else{Serial.print((I1/1000)/2);}
          Serial.print(',');
          if(I2 < 0.1){Serial.print("0.0");}else{Serial.print((I2/1000)/2);}
          Serial.print(',');
          if(I3 < 0.1){Serial.print("0.0");}else{Serial.print((I3/1000)/2);}
          Serial.print(',');
          if(I4 < 0.1){Serial.print("0.0");}else{Serial.print((I4/1000)/2);}
          Serial.print(',');
          if(I5 < 0.1){Serial.print("0.0");}else{Serial.print((I5/1000)/2);}
          Serial.print(',');
          Serial.print(in1);
          Serial.print(',');
          Serial.print((in1*(((I1/1000)/2)*1000))/1000);
          Serial.print(',');
          Serial.print(t);
          Serial.print(',');
