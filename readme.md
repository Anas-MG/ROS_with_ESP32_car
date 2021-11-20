## ROS with ESP32 Car
<img 
src="https://user-images.githubusercontent.com/49666154/140733000-94906f91-95a6-4caf-8942-75631905dc4c.jpg" width="700px"  > 

##### This is an Arduino based robot that is programmed to move by ROS. 

# Required components :
##### 1-ESP32
##### 2-L298N H-bridge
##### 3-Four DC motors 3-6 volts, wheels
##### 4-10k mAh Power supply 
##### 5-9V battery

# Connection:
- D26 connected to ENA
- D27 connected to INA1
- D14 connected to INA2
- D32 connected to INB3
- D33 connected to INB4
- D25 connected to ENB
- GND connected to L298N GND
- Each side of the motors is connected to one side of L298N 

#### Power sources:
##### - 9V Battery connected to L298N for DC motors 
##### - 10k mAh power supply connected to ESP32
###### The power sources seperated so L298N can properly handle four DC motors.

## How can ROS move the car remotly?
#### To understand this idea we firstly need to understand ESP32.
- ##### 1-ESP32 is a low-power Microcontroller with an integrated Wi-Fi and Bluetooth, This board is used with 2.4 GHz dual-mode Wi-Fi. The reason I used it is Due to that I need to the need of the Wi-Fi in order to communicate with ROS.
- ##### 2-ESP32 is programmed to connect to the Wifi and a specific IP address(ROS serial server) to recieve and translate the position data from ROS  (subscriping and publishing) in the network layer .

## Understanding L298N H-bridge motor driver  
<img src="https://user-images.githubusercontent.com/49666154/128776326-36a2416f-9356-49f9-842e-ab9bff2704f0.jpeg" width="300px" > <img src="https://user-images.githubusercontent.com/49666154/128803887-7bc041e8-9c74-42aa-8f75-aa2c68efa30d.png" width="400px" >

##### The L298N is a dual H-Bridge motor driver which allows speed and direction control of two DC motors at the same time. it won't allow the independent control of four motors, but you could possibly connect two in parallel to each output, like this project. It's recommended to power it with 7-12 volts.

- ##### Outx pins are used for the dc motors
- ##### IN1-IN2 and IN3-IN4 pins controles direction 
- ##### ENA & ENB pins are puls width modulation pins that controls the speed
 
# ROS Operations:
- #### launch rosserial socket node:
> roslaunch rosserial_server socket.launch
- #### Launch Keybord node to control the robot: 
> rosrun teleop_twist_keyboard teleop_twist_keyboard.py

 After plugging the power sources and running ROS operations the robot car should be connected to rosserial server and subscribe to cmd_vel topic .
 Note: the blue led indicates wither ROS connected or not, Off means its connected.


