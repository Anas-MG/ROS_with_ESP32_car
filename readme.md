## ROS with ESP32 Car
##### This is an ESP32 robot car project that is designed to move by ROS. 

<img 
src="https://user-images.githubusercontent.com/49666154/140733000-94906f91-95a6-4caf-8942-75631905dc4c.jpg" width="700px"  > 

## How can ROS move the car remotly?
- #### Understanding ESP32.
- ##### ESP32 is a low-power Microcontroller with an integrated Wi-Fi and Bluetooth, This board is used with 2.4 GHz dual-mode Wi-Fi. The reason I used it is Due  to the need of the Wi-Fi in order to communicate with ROS.
 #
- #### The projects program
 - ##### The program will connect The ESP32 to the Wifi and a ROS serial server machine IP address, then it'll subscribe to a specific ROS topic in that machine so whenever when press keyboard to move towards any side it will understand and move the ESP32 accordingly.

## ROS Operations:
- #### Launch rosserial socket node so that the ESP32 connects to the machine:
> roslaunch rosserial_server socket.launch
- #### Launch Keybord node to control the robot: 
> rosrun teleop_twist_keyboard teleop_twist_keyboard.py




# Required components :
##### 1-ESP32
##### 2-L298N H-bridge
##### 3-Four DC motors 3-6 volts with wheels
##### 4-10k mAh Power supply 
##### 5-9V battery

## L298N H-bridge motor driver  
<img src="https://user-images.githubusercontent.com/49666154/128776326-36a2416f-9356-49f9-842e-ab9bff2704f0.jpeg" width="300px" > <img src="https://user-images.githubusercontent.com/49666154/128803887-7bc041e8-9c74-42aa-8f75-aa2c68efa30d.png" width="400px" >
##### L298N is a dual H-Bridge motor driver which allows speed and direction control of two DC motors at the same time. you could possibly connect two in parallel to each output, like this project. It's recommended to power it with 7-12 volts.
- ##### Out1-OUT2  and Out3-Out4 pins are for Dc motors
- ##### IN1-IN2 and IN3-IN4 pins controles direction 
- ##### ENA & ENB pins are puls width modulation pins that controls the speed
 
# Connection :
- ##### D26 connected to ENA
- ##### D27 connected to INA1
- ##### D14 connected to INA2
- ##### D32 connected to INB3
- ##### D33 connected to INB4
- ##### D25 connected to ENB
- ##### GND connected to L298N GND
- ##### Each side of the motors is connected to OUTx pin L298N 
#### Power sources:
##### - 9V Battery connected to L298N for DC motors 
##### - 10k mAh power supply connected to ESP32
###### The power sources seperated so L298N can properly handle four DC motors.

 After plugging the power sources and running ROS operations the robot car should be connected to rosserial server and subscribe to  topic .
 Note: the blue led indicates wither ROS connected or not, Off means its connected.

