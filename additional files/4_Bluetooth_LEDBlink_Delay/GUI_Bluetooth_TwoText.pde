import controlP5.*;
import processing.serial.*;

Serial myPort; // Create a Serial object to communicate with the Arduino
ControlP5 cp5; // Create a ControlP5 object for the GUI
String numBlinks_s = "0"; // Variable to store the number of blinks
String delayTime_s = "1000"; // Variable to store the delay time

void setup() {
  size(450, 500);
  //background(0); // Set background color to black
  background(237, 240, 241);
  myPort = new Serial(this, "COM7", 9600); // Use the same baud rate as in the Arduino code

  cp5 = new ControlP5(this); // Initialize ControlP5

  // Create a title label
  PFont titleFont = createFont("Verdana", 20);
  int titleWidth = (int) textWidth("GUI to control the LED blinking and delay");
  int titleX = (width - titleWidth) / 2;
  cp5.addTextlabel("titleLabel")
     .setText("GUI to control the LED blinking\n\n and delay")
     .setPosition(titleX, height / 8)
     .setFont(titleFont)
     .setColor(color(70));
 
 // Create a label for the "Enter a number of blinks" heading
  PFont blinkFont = createFont("Arial", 15);
  int headingWidth = (int) textWidth("Enter a number of blinks");
  int headingX = (width - headingWidth - 50) / 2;
  cp5.addTextlabel("headingLabel")
     .setText("Enter a number of blinks")
     .setPosition(headingX, height / 2 - 110)
     .setFont(blinkFont)
     .setColor(color(40)); // Set the heading text color to red (255, 0, 0)

  // Create a text input field for "Enter a number of blinks"
  cp5.addTextfield("numBlinksInput")
     .setPosition(width / 2 - 80, height / 2 - 80)
     .setSize(160, 30)
     .setAutoClear(true)
     .setColor(color(70))
     .setColorBackground(color(240))
     .setColorForeground(color(0));
     
  // Create a label for the "Enter Delay" heading
  PFont delaykFont = createFont("Arial", 15);
  int delayheadingWidth = (int) textWidth("Enter a Delay");
  int delayheadingX = (width - delayheadingWidth - 50) / 2;
  cp5.addTextlabel("delayheadingLabel")
     .setText("Enter a Delay")
     .setPosition(delayheadingX, height / 2 - 10)
     .setFont(delaykFont)
     .setColor(color(40)); // Set the heading text color to red (255, 0, 0)


  // Create a text input field for "Enter a Delay"
  cp5.addTextfield("delayInput")
     .setPosition(width / 2 - 80, height / 2 + 20)
     .setSize(160, 30)
     .setAutoClear(true)
     .setColor(color(70))
     .setColorBackground(color(240))
     .setColorForeground(color(0));
}

void draw() {
  // No need to draw anything here since the background is set to black
}

void keyPressed() {
  // Check if the key pressed is Enter
  if (key == ENTER) {
    numBlinks_s = cp5.get(Textfield.class, "numBlinksInput").getText(); // Get the entered value from the "Enter a number of blinks" field
    delayTime_s = cp5.get(Textfield.class, "delayInput").getText(); // Get the entered value from the "Enter a Delay" field
    int numBlinks = int(numBlinks_s);
    int delayTime = int(delayTime_s);
    print(numBlinks);
    print(delayTime);
    // Send the numeric values to Arduino over Bluetooth
    myPort.write(numBlinks_s);
    myPort.write(',');
    myPort.write(delayTime_s); // Send the high byte of the delay time
    myPort.write('\n');
 
  }
}
