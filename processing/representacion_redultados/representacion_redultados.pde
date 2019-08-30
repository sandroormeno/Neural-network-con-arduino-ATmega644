import processing.serial.*;
Serial myPort;                       // The serial port
int[] serialInArray = new int[3];


int numFrames = 8;  // The number of frames in the animation
int currentFrame = 0;
int currentFrametrote = 0;
int numFramestrote = 4;
PImage[] piernas = new PImage[numFrames];
PImage[] gluteos = new PImage[numFrames];
PImage[] trote = new PImage[numFramestrote];

int serialCount = 0; 

int ejercicio = 0;

void setup() {
  size(220, 250);
  frameRate(6);
  printArray(Serial.list());

  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);

  for (int i = 0; i < numFrames; i++) {
    String imageName = "piernas" + nf(i+1, 2) + ".png";
    piernas[i] = loadImage(imageName);
  }
  for (int i = 0; i < numFrames; i++) {
    String imageName = "gluteos" + nf(i+1, 2) + ".png";
    gluteos[i] = loadImage(imageName);
  }
 for (int i = 0; i < numFramestrote; i++) {
    String imageName = "trote" + nf(i+1, 2) + ".png";
    trote[i] = loadImage(imageName);
  }
} 
 
void draw() { 
  background(255);
  
  int offset = 0;
  currentFrame = (currentFrame+1) % numFrames;  
  currentFrametrote = (currentFrametrote+1) % numFramestrote; 

  if (ejercicio == 0){
    image(trote[(currentFrame+offset) % numFramestrote], 50, 40);
  }else if (ejercicio == 1){
    image(gluteos[(currentFrame+offset) % numFrames], 40, 40);
  }else{
    image(piernas[(currentFrame+offset) % numFrames], -10, 30);
  }
  while (myPort.available() > 0) {
    int inByte = myPort.read();
    ejercicio = inByte;
    //println(inByte);
  }
}