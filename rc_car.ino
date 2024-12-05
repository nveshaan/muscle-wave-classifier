#include <ESP8266WiFi.h>

// Define motor pins
#define IN1 D1  // Rear motor control 1
#define IN2 D2  // Rear motor control 2
#define IN3 D3  // Front motor control 1
#define IN4 D4  // Front motor control 2
#define ENA D5  // Rear motor enable
#define ENB D6  // Front motor enable

// Wi-Fi credentials
const char* ssid = ""; // fill in your Wi-Fi name
const char* password = ""; // fill in your Wi-Fi password

// Server configuration
WiFiServer server(8888);  // Use port 8888 for socket communication

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Motor pin configurations
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Set ENA and ENB to HIGH to enable motors
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");

  // Print the IP address of the ESP8266
  Serial.print("ESP8266 IP address: ");
  Serial.println(WiFi.localIP());

  // Start the socket server
  server.begin();
}

void loop() {
  // Check for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connected");
    while (client.connected()) {
      if (client.available()) {
        String fistState = client.readStringUntil('\n');
        Serial.println("Fist state received: " + fistState);

        // Process the fist state
        if (fistState.indexOf("forward") >= 0) {
          moveForward();
        } else if (fistState.indexOf("stop") >= 0) {
          stopCar();
        } else if (fistState.indexOf("left") >= 0) {
          rotateLeft();
        } else if (fistState.indexOf("right") >= 0) {
          rotateRight();
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}

// Function to move the car forward
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Car moving forward");
}

// Function to stop the car
void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Car stopped");
}

// Function to rotate the car to the left
void rotateLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Car rotating left");
}

// Function to rotate the car to the right
void rotateRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Car rotating right");
}
