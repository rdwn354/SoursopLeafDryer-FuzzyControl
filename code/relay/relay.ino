// Define the pin connected to the relay
const int relay1 = 2; // Change this to match your setup
const int relay2 = 3;


void setup() {
  // Initialize the relay pin as an output
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop() {
  // Turn on the relay (activate the connected device) for 1 second
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  delay(1000);
  
  // Turn off the relay (deactivate the connected device) for 1 second
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  delay(1000);
}
