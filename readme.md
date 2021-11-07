## ROS with ESP32 Car

##### This Robot is an Arduino based robot that is programmed to recieve a position data from ROS topic 

## Components required To build:
##### 1-ESP32
##### 2-L298N H-bridge
##### 4-Four DC motors 3-6 volts, wheels
##### 5-Power supply and 9V battery 

## How the Robot moves remotly with Ros ?
#### To understand how the robot moves by ros we need to understand ESP32.
- ##### 1-ESP32 is a low-power Microcontroller with an integrated Wi-Fi and Bluetooth, This board is used with 2.4 GHz dual-mode Wi-Fi. The reason I used it is Due to that I need to connect to the Wi-Fi.
- ##### 2-ESP32 is programmed to connect to the Wifi and a specific IP address(ROS serial server) to recieve and translate the position data from ROS in the network layer using UDP proocol, which is a communications protocol that facilitates the exchange of messages between computing devices in a network

## Understanding L298N H-bridge motor driver  
<img src="https://user-images.githubusercontent.com/49666154/128776326-36a2416f-9356-49f9-842e-ab9bff2704f0.jpeg" width="300px" > <img src="https://user-images.githubusercontent.com/49666154/128803887-7bc041e8-9c74-42aa-8f75-aa2c68efa30d.png" width="400px" >

##### The L298N is a dual H-Bridge motor driver which allows speed and direction control of two DC motors at the same time. it won't allow the independent control of four motors, but you could possibly connect two in parallel to each output, like this project. It's recommended to power it with 7-12 volts.

- ##### Outx pins for the dc motors
- ##### IN1-IN2 and IN2-IN4 pins controles direction 
- ##### ENA & ENB pins are puls width modulation pins that controls the speed
 

## Circuit Diagram 
> ##### The project circuit is simple as it's only a ESP32 based car connected to L298N motor driver. most of the work is done in the programming
<img src="https://user-images.githubusercontent.com/49666154/128810985-fdf2664e-83c6-4a8d-a168-b4ce82bab137.png" width="700px" >

#### The power sources is seperated so L298N can properly handle four DC motors.

## Obstacles Avoiding Robot in field
https://user-images.githubusercontent.com/49666154/128778157-4c76af22-ae89-4151-b63f-5991b3715af8.mp4

