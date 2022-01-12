/**
 * Throttle Meter for ThrustMaster TMX PRO Pedals
 * As the title says, this is a throttle meter for the Thrustmaster TMX PRO Pedals.
 * By using the analog pin on an arduino, the voltage can be read in from the chip the racing pedals use.
 * Using these voltage values, can help determine how much a user is pressing on the gas pedal. Thus, a 
 * throttle meter indicator can be made from this.
 * Author: Chuyee Vue
 * 
 * Author's Note: This is not a finished product. I (Chuyee Vue), would like to do more than just light up LEDs.
 * I would like to actually record my throttle values and plot them on a graph. So whenever I'm racing in 
 * Assetto Corsa for example, I can use this data to help determine whether to step on the gas more or let go of the throttle
 * in certain parts of the race to improve my lap times.
 */


//Global Variables
const int MAX_PINS = 12;
const float MAX_VOLTAGE = 2.8;
const float BASE_VOLTAGE = 0.70;

//This is a doubly linked list.
class ThrottleMeter
{
private:
  struct Node
  {
    float thresholdValue;
    byte pinNumber;
    Node* next;
    Node* prev;
  };
  Node* head;
  Node* tail;
  Node* currentNode;
  
public:
  ThrottleMeter()
  {
    head = NULL;
    tail = NULL;
  }

  ~ThrottleMeter()
  {
    Node* iterator = head;
    //While the iterator is not null.
    while(iterator)
    {
      Node* temp = iterator;
      iterator = iterator->next;
      delete temp;
    }
  }

  /**
   * insertNode() will take in a thresholdValue and pinValue of type byte to create the node and insert it
   * at the end of the doubly linked list.
   */
  void insertNode(float thresholdValue, byte pinNumber)
  {
    Node* tempNode = new Node();
    //If the doubly linked list is NULL.
    if(head == NULL && tail == NULL)
    {
      tempNode->thresholdValue = thresholdValue;
      tempNode->pinNumber = pinNumber;
      head = tempNode;
      tail = tempNode;
      currentNode = head;
    }
    else
    {
      //Assign new node values.
      tempNode->thresholdValue = thresholdValue;
      tempNode->pinNumber = pinNumber;
      tempNode->prev = tail;
      //Set the current pin as an output.
      pinMode(tempNode->pinNumber, OUTPUT);
      //Have the tail node's next pointer, point towards the new node (tempNode).
      tail->next = tempNode;
      //Set the tail pointer to the tempNode.
      tail = tempNode;
    }
  }

  /**
  * turnOn will utilize the current node's pinNumber to turn the LED on.
  */
  void turnOn()
  {
    digitalWrite(currentNode->pinNumber, HIGH);
  }
  /**
   * turnOff will utilize the current node's pinNumber to turn the LED off.
   */
  void turnOff()
  {
    digitalWrite(currentNode->pinNumber, LOW);
  }

  /**
   * run() will take in a voltage value of type float and determine whether 
   * it should turn the LED on or off.
   */
  void run(float voltage)
  {
    //Flicker the last LED to indicate max throttle.
    if(currentNode->next == NULL)
    {
      turnOn();
      delay(80);
      turnOff();
      delay(80);
      turnOn();
    }
    if(currentNode->next != NULL && currentNode->thresholdValue < voltage)
    {
      turnOn();
      currentNode = currentNode->next;
      turnOn();
    }
    else
    {
      turnOff();
      if(currentNode != head)
        currentNode = currentNode->prev;
    }
  }
};

ThrottleMeter throttleMeter;

void setup()
{
  Serial.begin(9600);
  for(int i = 0; i < MAX_PINS; i++)
  {
    int pinNumber = 2 + i;
    float thresholdValue = (MAX_VOLTAGE - BASE_VOLTAGE) / MAX_PINS;
    if(i == 0)
    {
      throttleMeter.insertNode(BASE_VOLTAGE, pinNumber);
    }
    else
    {
      throttleMeter.insertNode((i * thresholdValue) + BASE_VOLTAGE , pinNumber);
    }
    
  }
}

void loop()
{
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0/1023.0);
  Serial.println(voltage);
  throttleMeter.run(voltage);
}
