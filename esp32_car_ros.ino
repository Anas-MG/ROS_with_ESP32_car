

#include <math.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <analogWrite.h>
#define LED_BUILTIN 2 // Remapping the built-in LED .
#define LED_BUILTIN_RED 16 // If using a NodeMcu v1.
#define PWM_MIN 70
#define PWMRANGE 255

// Declare functions
void setupPins();
void setupSerial();
void setupWiFi();
bool rosConnected();
void onTwist(const geometry_msgs::Twist &msg);
float mapPwm(float x, float out_min, float out_max);

// Pins
const uint8_t R_PWM = 26;
const uint8_t R_BACK = 14;
const uint8_t R_FORW = 27;
const uint8_t L_BACK = 32;
const uint8_t L_FORW = 33;
const uint8_t L_PWM = 25;

// Wifi
// If access point is defined, a Wifi network with this name will be created.
// Remove if you want to connect to an existing network.
//#define ACCESS_POINT_SSID "SMARTCAR"

#ifndef ACCESS_POINT_SSID
WiFiMulti wifi;
#endif

// ROS serial server
IPAddress server(192, 168, 100, 181);
ros::NodeHandle node;
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", &onTwist);

bool _connected = false;

void setup()
{
  setupPins();
  setupSerial();
  setupWiFi();

  // Connect to rosserial socket server and init node. (Using default port of 11411)
  Serial.printf("Connecting to ROS serial server at %s\n", server.toString().c_str());
  node.getHardware()->setConnection(server);
  node.initNode();
  node.subscribe(sub);
}

void setupPins()
{
  // Status LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(L_PWM, OUTPUT);
  pinMode(L_FORW, OUTPUT);
  pinMode(L_BACK, OUTPUT);
  pinMode(R_PWM, OUTPUT);
  pinMode(R_FORW, OUTPUT);
  pinMode(R_BACK, OUTPUT);
  stop();
}

void setupSerial()
{
  Serial.begin(115200);
  Serial.println();
}

void setupWiFi()
{
#ifdef ACCESS_POINT_SSID

  WiFi.disconnect();
  Serial.println("Creating Wifi network");
  if (WiFi.softAP(ACCESS_POINT_SSID))
  {
    Serial.println("Wifi network created");
    Serial.print("SSID: ");
    Serial.println(WiFi.softAPSSID());
    Serial.print("IP:   ");
    Serial.println(WiFi.softAPIP());
  }

#else

  WiFi.softAPdisconnect();
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  wifi.addAP("MadScientisto", "anosi12345");
  wifi.addAP("--wifi_2--", "--password_2--");
  wifi.addAP("--wifi_3--", "--password_3--");

  Serial.println("Connecting to Wifi");
  while (wifi.run() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("IP:   ");
  Serial.println(WiFi.localIP());

#endif
}

void stop()
{
  digitalWrite(L_FORW, 0);
  digitalWrite(L_BACK, 0);
  digitalWrite(R_FORW, 0);
  digitalWrite(R_BACK, 0);
  analogWrite(L_PWM, 0);
  analogWrite(R_PWM, 0);
}

void onTwist(const geometry_msgs::Twist &msg)
{
  if (!_connected)
  {
    stop();
    return;
  }

  // Cap values at [-1 .. 1]
  float x = max(min(msg.linear.x, 1.0f), -1.0f);
  float z = max(min(msg.angular.z, 1.0f), -1.0f);

  // Calculate the intensity of left and right wheels. Simple version.
  float l = (msg.linear.x - msg.angular.z) / 2;
  float r = (msg.linear.x + msg.angular.z) / 2;

  // Then map those values to PWM intensities. PWMRANGE = full speed, while PWM_MIN = the minimal amount of power at which the motors begin moving.
  uint16_t lPwm = mapPwm(fabs(l), PWM_MIN, PWMRANGE);
  uint16_t rPwm = mapPwm(fabs(r), PWM_MIN, PWMRANGE);

  // Set direction pins and PWM
  digitalWrite(L_FORW, l > 0);
  digitalWrite(L_BACK, l < 0);
  digitalWrite(R_FORW, r > 0);
  digitalWrite(R_BACK, r < 0);
  analogWrite(L_PWM, lPwm);
  analogWrite(R_PWM, rPwm);
}

void loop()
{
  if (!rosConnected())
    stop();
  node.spinOnce();
}

bool rosConnected()
{
  // If value changes, notify via LED and console.
  bool connected = node.connected();
  if (_connected != connected)
  {
    _connected = connected;
    digitalWrite(LED_BUILTIN, !connected); // false -> on, true -> off
    Serial.println(connected ? "ROS connected" : "ROS disconnected");
  }
  return connected;
}

// Map x value from [0 .. 1] to [out_min .. out_max]
float mapPwm(float x, float out_min, float out_max)
{
  return x * (out_max - out_min) + out_min;
}
