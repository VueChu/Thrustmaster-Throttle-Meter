# Thrustmaster-Throttle-Meter
A 12 LED display that would represent the user's throttle values using an Arduino UNO, Thrustmaster TMX Pro Racing Pedals and the Arduino IDE.

# Author's Note:
I created this for the sole purpose of learning how to program on an Arduino, practicing object oriented programming, using a doubly linked list data structure, and utilize the analog pin to read in the voltage the pedals would output. In addition, currently a cruise control feature is in the works and there will be a library in its own seperate repository that can just be downloaded and then included into this source code. If you are only interested in the cruise control feature, there will also be repository for this.

If you see anything that can be improved or have any tips (including this readme file), I would greatly appreciate any sort of feedback.

### Summary:
This program's purpose is to display the user's throttle values through a 12 LED display using the Thrustmaster TMX Pro Racing Pedals using an Arduino UNO on the Arduino IDE.


### Materials needed:
- Arduino Uno or any board that can utilize Serial - 1 (Click [here](https://www.arduino.cc/reference/en/language/functions/communication/serial/) to check which type of Serial you would have to use for this program.)
- Breadboard - 1
- 150Ω resistors - 12 -- Note: You can use any resistor value that you want. I chose to go with 150 Ohms. 
- LED - 12
- Any USB that is compatible with your Arduino that can be connected to a computer.
- A computer.
- Thrustmaster TMX Pro Racing Pedals
### Diagram:
![here](https://github.com/VueChu/BrainMeter/blob/main/BrainMeter%20Diagram.png)
- Do take note that the resistors are not the same values in the picture below as mentioned above in the "Materials needed" section. I am limited on components and since these resistors aren't important but to protect my LEDs, that is all I need for functionality.
![here](https://github.com/VueChu/Thrustmaster-Throttle-Meter/blob/main/Meter%20Configuration.jpg)
![here](https://github.com/VueChu/Thrustmaster-Throttle-Meter/blob/main/Pedal%20Chip%20Config..jpg)
### ---ThrottleMeter Class---
- ### Struct Node
	- ```byte pinNumber```
      - pinNumber will store the specified pin for each node.

	- ```float thresholdValue```
		- thresholdValue will hold a threshold value for each node.

	- ```Node* next```
		- Will point to the memory address of the next node in the doubly linked list.
		
	- ```Node* prev```
		- Will point to the memory address of the previous node in the doubly linked list.
		
- ### Attributes
	- ```Node* head```
		- A pointer that keeps track of the first node in the doubly linked list.
		
	- ```Node* tail```
		- A pointer that keeps track of the last node in the doubly linked list.
		
	- ```Node* currentNode```
		- A pointer that keeps track of the current location of a node when traversing through the doubly linked list when given a voltage value of type float.
		
-	### CONSTRUCTOR
    - ```Throttlemeter()```
    
      - Default constructor that instantiates the Throttlemeter class.

- ### FUNCTIONS
  - ```void insertNode(float thresholdValue, byte pinNumber)```

    - Creates a node and inserts it to the tail of the doubly linked list. Each node will represent an LED on the breadboard.
	- Params: float thresholdValue, byte pinNumber
	
  - ```void turnOn()```
  
    - This function will utilize the current node's pinNumber that currentNode is pointing at to turn ON the LED.

  - ```void turnOff()```
  
    - This function will utilize the current node's pinNumber that currentNode is pointing at to turn OFF the LED.
  
  - ```void run(float voltage)```
  
    - This function will iterate until the voltage values are correctly displayed on the throttle meter by receiving a voltage reading from the analog pin.
	- Params: float voltage

### ---End of Throttlemeter Class---
### GLOBAL VARIABLES WORTH MENTIONING

- ```Throttlemeter throttleMeter```

  - throttleMeter is an object of type Throttlemeter that will allow the meter to function.

- ```float MAX_VOLTAGE ```

  - MAX_VOLTAGE is a constant variable of type float. It is important to limit the max voltage that the throttle pedal can  output. I have not tried to go higher as I am afraid I will break the components. 

- ```float BASE_VOLTAGE```

  - BASE_VOLTAGE is a constant variable of type float. This is the base voltage the throttle output pin will output at idle. It won't be until the throttle pedal is pressed, the meter will display through the LEDs.  
