#include "pins.h"

enum led_states{
  state_0 = 0,  // normal state, all LEDs are OFF
  state_1,  // blink blue LED for 5 seconds
  state_2   // wait for state_1 to finish and blink green LEDs for 5 seconds
};

// function prototypes
void runState_0(void);
void runState_1(void);
void runState_2(void);

typedef void(*stateFunction)(void);

constexpr stateFunction stateFunctions[]= { // array of function pointers
  runState_0,
  runState_1,
  runState_2,
  nullptr
};

led_states state = led_states::state_0; // starting state
bool state_change_flag = true;
const long interval = 3000;  // change state after every 3 seconds
unsigned long current_time, previous_time = 0;

// button variables
bool current_button_state; // current reading from the button pin
int last_button_state = LOW;  // previous reading from the input pin
unsigned long last_debounce_time = 0;
unsigned long debounce_delay = 100; // debounce time

void setUpPins(){
  pinMode(blue_led, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(button_pin, INPUT);
}

void setup() {
  setUpPins();  // set up pins as inputs or outputs
  Serial.begin(9600);

  // default 
//    digitalWrite(blue_led, HIGH);
//    digitalWrite(green_led, HIGH);
}

// state functions
void runState_0(void){
  Serial.println("State 0");

  state = led_states::state_1;  // update next state

  // run code because interval has elapsed
  digitalWrite(blue_led, HIGH);
  delay(500);
}

void runState_1(void){
  Serial.println("State 1");
  current_time = millis();

  state = led_states::state_2;
    
  digitalWrite(blue_led, LOW);
  delay(500);

}

void runState_2(void){
  Serial.println("State 2");
  
  state = led_states::state_0;  // go back to the original state
  
  digitalWrite(blue_led, HIGH);
  delay(500);
}

void test_function(){
    digitalWrite(green_led, HIGH);
    delay(1000);
    digitalWrite(green_led, LOW);
    delay(500);
}

void loop() {
  // poll for button press
  int reading = digitalRead(button_pin);

  if(reading != last_button_state){
    // reset the debouncing timer
    last_debounce_time = millis();
  }

  if(millis() - last_debounce_time > debounce_delay){
    current_button_state = reading;

    // if the new button state is HIGH, perfom state transition
    if(current_button_state == HIGH){
      Serial.println("Button pressed");
      state_change_flag = true;
      
      Serial.println("Calling state");  
      stateFunctions[(int)state](); // call the relevant function
    }
  }
  
  last_button_state = reading; // update reading for next iteration
  
  
}
