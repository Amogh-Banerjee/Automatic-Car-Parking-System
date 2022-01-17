// AUTOMATIC CAR PARKING SYSTEM

#include <Wire.h> 
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

Servo myservo1;
Servo myservo2;
int IR1 = 2; // IR Sensor at entrance is connected to D2
int IR2 = 12; // IR Sensor at exit is connected to D12
int slots = 8; // Total number of available parking slots

// Initially, both the gates are closed
bool gate1open = false; // Entry gate
bool gate2open = false; // Exit gate

void setup() {
  
  // Initialise the LCD
  lcd.begin();
  lcd.backlight();
  
  // Pins D2 and D4 are configured as inputs
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  
  myservo1.attach(6); // Servo at entrance is attached to D6
  myservo2.attach(9); // Servo at exit is attached to D9

  // Close both the gates
  myservo1.write(90);
  myservo2.write(90);

  // Displaying name of the project on LCD and clearing the screen
  lcd.setCursor (0,0);
  lcd.print(" AUTOMATIC CAR  ");
  lcd.setCursor (0,1);
  lcd.print(" PARKING SYSTEM ");
  delay (4000);
  lcd.clear();  
}

void loop() {

  // When a car wants to exit the parking lot
  while(digitalRead(IR2) == LOW && slots >= 0 && slots < 8){ 

    // Slowly open the exit gate
    if(gate2open == false){
      for(int i = 90; i >= 0;i--){
        myservo2.write(i);
        delay(30);
      }
      gate2open = true;
      slots++; // Increase the number of parking slots by 1
    }
 
  }

  // If the exit gate is open, close it
  if(gate2open == true){
      delay(2000);
      for(int i = 0; i <= 90; i++){
        myservo2.write(i);
        delay(30);
      }
      gate2open = false;
    }

  // When a car wants to enter the parking lot and parking slots are available
  while(digitalRead(IR1) == LOW && slots > 0 && slots <= 8){ 

    // Slowly open the entry gate
    if(gate1open == false){
      for(int i = 90; i <= 180; i++){
        myservo1.write(i);
        delay(30);
      }
      gate1open = true;
      slots--; // Decrease the number of parking slots by 1
    }
    
  }
  
    // If the entry gate is open, close it
    if(gate1open == true){
      delay(2000);
      for(int i = 180; i >= 90; i--){
        myservo1.write(i);
        delay(30);
      }
      gate1open = false;
    }

    // Display the number of available parking slots on the LCD Screen 
    if(slots > 0){
      lcd.setCursor (0,0);
      lcd.print("    WELCOME!    ");
      lcd.setCursor (0,1);
      lcd.print("Slots Left: ");
      lcd.print(slots);    
    }

    // If there is no space available, show a message that the parking is full
    else{
      lcd.setCursor (0,0);
      lcd.print("    SORRY :(    ");  
      lcd.setCursor (0,1);
      lcd.print("  Parking Full  "); 
      delay (3000);
      lcd.clear(); 
    }
      
}
