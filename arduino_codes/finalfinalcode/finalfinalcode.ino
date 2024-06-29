#include <WiFi.h>
#include <WebServer.h>
#include <string>

using namespace std;

const char* ssid = "ESP32-Access-Point"; // Name of the ESP32 AP
const char* password = "password123";    // Password for the ESP32 AP
// Declare values of dropdown globally
int dropdown1Value , dropdown2Value , dropdown3Value, point ;

WebServer server(80);

// Function prototype for findMostProbableDisease
string findMostProbableDisease(int inputSymptoms[]);

// Function prototype for processArray
int* processArray(int dropdown1Value, int dropdown2Value, int dropdown3Value);

int motorPin1_1 =12;
int motorPin2_1 =14;
int enablePin_1 =13;

int motorPin1_2 =26;
int motorPin2_2 =25;
int enablePin_2 =27;

// int motorPin1_4 =32;
// int motorPin2_4 =35;
// int enablePin_4 =33;

int motorPin1_3 =19;
int motorPin2_3 =21;
int enablePin_3 =18;

void row1(){
  Serial.println("called for first motor");
  // digitalWrite(enablePin_1, HIGH);
  // digitalWrite(motorPin2_1 , LOW);
  // digitalWrite(motorPin1_1 , HIGH);
  // delay(4000);
  // digitalWrite(enablePin_1,LOW);
  // digitalWrite(motorPin2_1 , LOW);
  // digitalWrite(motorPin1_1 , LOW);
  // digitalWrite(enablePin_4,HIGH);
  // digitalWrite(motorPin1_4 , LOW);
  // digitalWrite(motorPin2_4 , HIGH);
  // delay(4000);
  digitalWrite(enablePin_1,HIGH);
  digitalWrite(motorPin2_1 , LOW);
  digitalWrite(motorPin1_1 , HIGH);
  delay(2500);
  digitalWrite(motorPin2_1 , LOW);
  digitalWrite(motorPin1_1 , LOW);
  delay(200);  
  digitalWrite(enablePin_1, LOW);
}

void row2(){
  Serial.println("called for second motor");
  // digitalWrite(enablePin_2, HIGH);
  // digitalWrite(motorPin2_2 , LOW);
  // digitalWrite(motorPin1_2 , HIGH);
  // delay(4000);
  // digitalWrite(enablePin_2,LOW);
  // digitalWrite(motorPin2_2 , LOW);
  // digitalWrite(motorPin1_2 , LOW);
  // digitalWrite(enablePin_4,HIGH);
  // digitalWrite(motorPin1_4 , LOW);
  // digitalWrite(motorPin2_4 , HIGH);
  // delay(3000);
  digitalWrite(enablePin_2,HIGH);
  digitalWrite(motorPin2_2 , LOW);
  digitalWrite(motorPin1_2 , HIGH);
  delay(2500);
  digitalWrite(motorPin2_2 , LOW);
  digitalWrite(motorPin1_2 , LOW);
  delay(200);  
  digitalWrite(enablePin_2, LOW);
}

void row3(){
  Serial.println("called for third motor");
  // digitalWrite(enablePin_3, HIGH);
  // digitalWrite(motorPin2_3 , LOW);
  // digitalWrite(motorPin1_3 , HIGH);
  // delay(4000);
  // digitalWrite(enablePin_3,LOW);
  // digitalWrite(motorPin2_3 , LOW);
  // digitalWrite(motorPin1_3 , LOW);
  // digitalWrite(enablePin_4,HIGH);
  // digitalWrite(motorPin1_4 , LOW);
  // digitalWrite(motorPin2_4 , HIGH);
  // delay(2000);
  digitalWrite(enablePin_3,HIGH);
  digitalWrite(motorPin2_3 , LOW);
  digitalWrite(motorPin1_3 , HIGH);
  delay(2500);
  digitalWrite(motorPin2_3 , LOW);
  digitalWrite(motorPin1_3 , LOW);
  delay(200);  
  digitalWrite(enablePin_3, LOW);
}


void setup() {
  Serial.begin(115200);
  delay(1000);

  // Start access point
  Serial.println();
  Serial.println("Starting access point...");
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Start the server
  server.on("/", HTTP_GET, handleRoot);
  server.on("/submit", HTTP_POST, handleSubmit);
  server.begin();
  Serial.println("Server started");

  //row 1
  pinMode(motorPin1_1, OUTPUT);
  pinMode(motorPin2_1, OUTPUT);
  pinMode(enablePin_1, OUTPUT);
  digitalWrite(enablePin_1,LOW);
//row 2
  pinMode(motorPin1_2, OUTPUT);
  pinMode(motorPin2_2, OUTPUT);
  pinMode(enablePin_2, OUTPUT);
  digitalWrite(enablePin_2,LOW);
//row 3
  pinMode(motorPin1_3, OUTPUT);
  pinMode(motorPin2_3, OUTPUT);
  pinMode(enablePin_3, OUTPUT);
  digitalWrite(enablePin_3,LOW);
//
  // pinMode(motorPin1_4, OUTPUT);
  // pinMode(motorPin2_4, OUTPUT);
  // pinMode(enablePin_4, OUTPUT);
  // digitalWrite(enablePin_4,LOW);
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String dropdown1 = "<select name='dropdown1'><option value='0'>Fever</option><option value='1'>Cough</option><option value='2'>Headache</option><option value='3'>Fatigue</option><option value='4'>Sore Throat</option></select><br/>";
  String dropdown2 = "<select name='dropdown2'><option value='-1'>None</option><option value='0'>Fever</option><option value='1'>Cough</option><option value='2'>Headache</option><option value='3'>Fatigue</option><option value='4'>Sore Throat</option></select><br/>";
  String dropdown3 = "<select name='dropdown3'><option value='-1'>None</option><option value='0'>Fever</option><option value='1'>Cough</option><option value='2'>Headache</option><option value='3'>Fatigue</option><option value='4'>Sore Throat</option></select><br/>";
  String submitButton = "<input type='submit' value='Submit'></form>";
  String html = "<form action='/submit' method='post'>" + dropdown1 + dropdown2 + dropdown3 + submitButton;
  server.send(200, "text/html", html);
}

void handleSubmit() {
  if (server.hasArg("dropdown1") && server.hasArg("dropdown2") && server.hasArg("dropdown3")) {
    dropdown1Value = server.arg("dropdown1").toInt();
    dropdown2Value = server.arg("dropdown2").toInt();
    dropdown3Value = server.arg("dropdown3").toInt();
    
    // Call findMostProbableDisease function
    int* symptomsArray = processArray(dropdown1Value, dropdown2Value, dropdown3Value);
    string disease = findMostProbableDisease(symptomsArray);
    
    // Send response with the disease found
    server.send(200, "text/plain", String("Most probable disease: ") + disease.c_str());
    //select row for motor
    giveMedicine();
    // Free the allocated memory
    delete[] symptomsArray;
  } else {
    server.send(400, "text/plain", "Missing parameters");
  }
}

void giveMedicine(){
  switch (point) {
    case 0:
        row1();
        break;
    case 1:
        row2();
        break;
    case 2:
        row3();
        break;
    // More cases can be added as needed
    default:
        Serial.println("row not available");
        break;
}

}

// Function that returns an integer array and takes dropdown values as parameters
int* processArray(int dropdown1Value, int dropdown2Value, int dropdown3Value) {
    // Dynamically allocate memory for the output array
    int* outputArray = new int[5]{0};

    // Set values based on dropdown selections
    outputArray[dropdown1Value] = 1;
    
    if (dropdown2Value >-1) {
        outputArray[dropdown2Value] = 1;
    }
    if (dropdown3Value >-1) {
        outputArray[dropdown3Value] = 1;
    }
    
    // Return the output array
    return outputArray;
}

// Define findMostProbableDisease function
string findMostProbableDisease(int inputSymptoms[]) {
    // Define diseases and symptoms
    string diseases[3] = {"Pneumonia", "Asthma", "Gastroenteritis"};
    int matrix[3][5] = {
        {1, 1, 0, 1, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0}
    };

    int maxMatches = 0;
    string mostProbableDisease;

    // Iterate over diseases
    for (int i = 0; i < 3; ++i) {
        int matches = 0;
        // Iterate over symptoms
        for (int j = 0; j < 5; ++j) {
            // Check if the symptom is present both in input and matrix
            if (inputSymptoms[j] == matrix[i][j]) {
                matches++;
            }
        }
        // Update the most probable disease if matches are higher
        if (matches > maxMatches) {
            maxMatches = matches;
            mostProbableDisease = diseases[i];
            point = i;
        }
    }

    // Return the most probable disease
    return mostProbableDisease;
}
