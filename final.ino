
#include <Servo.h> // add the libraies
Servo servo_test;
#define opin 6 // servo motor data pin
int button= 10; // button data  pin 
int val=0;
int aval=4;   // avalable for car
const int ldrPin =A0;                
int angle = 0; 
int red_led=2;
int green_led=3; 
int street_light=9;

 
void setup() {
  
  pinMode(opin,OUTPUT);
  pinMode(button,INPUT);
  pinMode(ldrPin,INPUT);
  pinMode(button,OUTPUT);
  pinMode(red_led,OUTPUT);
  pinMode(green_led,OUTPUT);
  pinMode(street_light,OUTPUT);

  
  servo_test.attach(opin); 
  Serial.begin(9600);

  
}

void loop() {

   open_gate();  // this function use to open the gate using pir sensor
   car_exit();   // this function return at time of car exit  using a button
   ldr_pin();     // to glow the street light at night using ldr sensor

   
   if(aval==0){
       digitalWrite(red_led,HIGH);  // if parking is full then red led indicate to parking full 
       digitalWrite(green_led,LOW);   
   }
   else{
     digitalWrite(green_led,HIGH);// if parking is availavle then green led indicate to availavle for parking 
     digitalWrite(red_led,LOW);
   }

 }

void open_gate()
{


  int pin = digitalRead(7); // pir sensor read pin
  Serial.println(pin);
 
  if( pin==HIGH && aval>0)

  {
     for(angle = 0; angle < 90; angle += 1)    // command to move from 0 degrees to 90 degrees 
      {                                  
         servo_test.write(angle);                 //command to rotate the servo to the specified angle
         delay(15);                       
      } 

  delay(4000);
  
  if(aval>0 && aval<10)
   {
       aval--;
  
      Serial.print("car count ");
      Serial.println(aval);
   }
      
   for(angle = 90; angle>=1; angle-=5)     // command to move from 90 degrees to 0 degrees 
  {                                
    servo_test.write(angle);              //command to rotate the servo to the specified angle
    delay(5);                       
  } 

  delay(5000);
   
   }

   else if(pin==LOW)
   {
     servo_test.write(0);
      Serial.println("else part");
   }

    delay(1000); 

}

void car_exit(){

     val=digitalRead(button);
     
      Serial.print("buuton value ");
      Serial.println(val);
  

  if(val==HIGH){
    
     val=digitalRead(button);
      Serial.print("buuton value ");
      Serial.println(val);
     if(val==HIGH)
     {
    
         delay(200);
         if(aval >=0 && aval<=9)
         {       
            aval++;                    // exit the car 
            Serial.print("car exit ");
             Serial.println(aval);
         }

    }
  }

}



void ldr_pin(){


  int ledStatus=analogRead(ldrPin);
  
  if(ledStatus>115)
  {
    Serial.print("It is Dark ");
    Serial.println(ledStatus);
     digitalWrite(street_light,HIGH);
  }
  else
  {
     Serial.print("Light ");
     Serial.println(ledStatus);
     digitalWrite(street_light,LOW);

  }


}
