#include <SoftwareSerial.h>

SoftwareSerial gsm(3, 4);  // RX, TX (Change pins based on your setup)

const int gasSensorPin = A0;  // Gas sensor connected to A0
const int buzzerPin = 9;      // Buzzer connected to digital pin 9
int gasThreshold = 350;       // Gas threshold value for alert
String phoneNumber = "+917006561141";  // Enter recipient's mobile number here

void setup() {
  Serial.begin(9600);
  gsm.begin(9600);

  pinMode(gasSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  initializeGSM();
}

void loop() {
  int gasValue = analogRead(gasSensorPin);
  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  if (gasValue > gasThreshold) {
    digitalWrite(buzzerPin, HIGH);  // Activate the buzzer
    sendSMS();                       // Send SMS alert
    delay(1000);                     // Beep duration
  } else {
    digitalWrite(buzzerPin, LOW);    // Turn off the buzzer
  }

  delay(2000); // Delay for stability
}

// Function to initialize GSM module
void initializeGSM() {
  gsm.println("AT");
  delay(1000);
  gsm.println("AT+CMGF=1");  // Set SMS to Text Mode
  delay(1000);
  gsm.println("AT+CSMP=17,167,0,0");  // Configure message settings
  delay(1000);
  gsm.println("AT+CNMI=2,1,0,0,0");   // Configure SMS message to be displayed
  delay(1000);
  Serial.println("GSM module initialized");
}

// Function to send SMS
void sendSMS() {
  gsm.print("AT+CMGS=\"");
  gsm.print(phoneNumber);
  gsm.println("\"");
  delay(1000);
  gsm.println("Gas Level High! Take immediate action."); // Your alert message
  delay(1000);
  gsm.write(26);  // CTRL+Z to send SMS
  delay(1000);
  Serial.println("SMS sent");
}
