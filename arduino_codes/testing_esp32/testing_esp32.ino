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

    // Free the allocated memory
    delete[] symptomsArray;
  } else {
    server.send(400, "text/plain", "Missing parameters");
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
