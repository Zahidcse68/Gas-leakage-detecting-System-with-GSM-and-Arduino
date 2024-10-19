#include<SoftwareSerial.h> //software serial library for serial communication between Arduino & sim900 GSM

SoftwareSerial mySerial(3, 4);//connect Tx pin of GSM to pin 8 of Arduino && Rx pin of GSM to pin no 9

int REY = 6; // relay output

String message;

String lampState = "HIGH";// Create a variable to store Lamp state

void setup() {

mySerial.begin(9600); // Setting the baud rate of GSM Module

delay(20000);

mySerial.println("AT+CMGF=1"); // set text mode

delay(1000);

mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS

pinMode(REY, OUTPUT);

digitalWrite(REY, HIGH);

delay(100);

}

void loop() {

if (mySerial.available() > 0) {

message = mySerial.readString(); }

if (message.indexOf("ON") > -1) {

digitalWrite(REY,LOW);

lampState = "on"; }

if (message.indexOf("OFF") > -1) {

digitalWrite(REY, HIGH);

lampState = "off"; }

if (message.indexOf("STATE") > -1) {

mySerial.println("AT+CMGS=\"+917006561141\"\r"); // replace XXX.. with your number with country code delay(1000);

mySerial.println("Relay is "+ lampState);// Message content

delay(1000);

mySerial.println((char)26);// ASCII code of CTRL+Z

delay(100); }

}
