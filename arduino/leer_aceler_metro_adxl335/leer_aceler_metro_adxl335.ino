// Acelerómetro:
// setup para arduino uno o Nano
//const int xInput = A0;
//const int yInput = A1;
//const int zInput = A2;

// acelerómetro tiene una arreglo especial en el ATMega644  

const int xInput = A1; //A0 - PA0 
const int yInput = A0; //A1 - PA1
const int zInput = A7; //A2 - PA2

// initialize minimum and maximum Raw Ranges for each axis
int RawMin = 0;
int RawMax = 1023;

// Take multiple samples to reduce noise
const int sampleSize = 10;

void setup()
{
  analogReference(EXTERNAL);
  Serial.begin(9600);
}

void loop()
{
  //Read raw values
  int xRaw = ReadAxis(xInput);
  int yRaw = ReadAxis(yInput);
  int zRaw = ReadAxis(zInput);
  
  int xScaled = map(xRaw,  RawMin, RawMax, 0, 255);
  int yScaled = map(yRaw,  RawMin, RawMax, 0, 255);
  int zScaled = map(zRaw,  RawMin, RawMax, 0, 255);

  // re-scale to fractional Gs
  float xAccel = xScaled / 1000.0;
  float yAccel = yScaled / 1000.0;
  float zAccel = zScaled / 1000.0;

  //Serial.print("X, Y, Z  :: ");
  Serial.write(xScaled);
  //Serial.print("\t");
  Serial.write(yScaled);
  //Serial.print("\t");
  Serial.write(zScaled);
  //Serial.print("\n");

  delay(100);
}

// Take samples and return the average
int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(1);
  for (int i = 0; i < sampleSize; i++)
  {
    reading += analogRead(axisPin);
  }
  return reading / sampleSize;
}

