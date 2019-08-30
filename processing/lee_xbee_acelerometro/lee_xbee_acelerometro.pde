// usar con archivo arduino/leer_aceler_metro_adxl335.ino

import processing.serial.*;

int bgcolor;           // Background color
int fgcolor;           // Fill color
int xpos, ypos, zpos;  
Serial myPort;                       // The serial port
int[] serialInArray = new int[3]; 
int serialCount = 0; 
int hPos = 0;
int val_max = 0;

void setup() {
  size(600, 255);  // Stage size
  noStroke();      // No border on the next thing drawn

  printArray(Serial.list());

  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  //background(210);
  //fill(125);
  dibuja(xpos+50, ypos, zpos-80);

}

void dibuja(int valor1, int valor2, int valor3){
  stroke(0,255,0,80);
  line(hPos, height, hPos, height - valor1);
  stroke(50,50,0,80);
  line(hPos, height, hPos, height - valor2);
  stroke(200,100,0,80);
  line(hPos, height, hPos, height - valor3);
  if(hPos >= width){
    hPos = 0;
    background(255);
  }else{
    hPos++;    
  }
  for (int i = 0; i < width; i = i+50) {
    //line(30, i, 80, i);
    stroke(230,220,220);
    line(i, height , i, 0 );
  }
}

void periodo(int pos) {
  if (pos > val_max){   
    //line(hPos, height, hPos, 0);
    stroke(0,0,0);
    line(hPos, height , hPos, height - 20 );
    val_max = pos; 
  } 
}

void serialEvent(Serial myPort) {
  // read a byte from the serial port:
  int inByte = myPort.read();
 
  serialInArray[serialCount] = inByte;
  serialCount++;


    // If we have 3 bytes:
  if (serialCount > 2 ) {
    xpos = serialInArray[0];
    ypos = serialInArray[1];
    zpos = serialInArray[2];
    //println(xpos + "\t" + ypos + "\t" + zpos + "\t");
    serialCount = 0;  
  }
 
}