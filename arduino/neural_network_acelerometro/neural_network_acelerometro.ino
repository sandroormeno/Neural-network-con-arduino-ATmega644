#include <MatrixMath.h>
#include <Math.h>
#include "WeightBias.h"
#include "validacion.h"

// matrices temporales

mtx_type mult0[1][16]; 
mtx_type suma0[1][16]; 
mtx_type salida0[1][16]; 

mtx_type mult1[1][16]; 
mtx_type suma1[1][16]; 
mtx_type salida1[1][16]; 

mtx_type mult2[1][3]; 
mtx_type suma2[1][3]; 
mtx_type salida2[1][3];

// valores para testing

mtx_type test[1][15] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 

int mult_val = 100; // para hacer visibles las predicciones.

int vali_pos = 10;

// acelerómetro tiene una arreglo especial en el ATMega644  

const int xInput = A1; //A0 - PA0 
const int yInput = A0; //A1 - PA1
const int zInput = A7; //A2 - PA2

// initialize minimum and maximum Raw Ranges for each axis
int RawMin = 0;
int RawMax = 1023;

double xfloat;
double yfloat;
double zfloat;

// Take multiple samples to reduce noise
const int sampleSize = 10;

int contador =  0;

void setup(){  
  analogReference(EXTERNAL);
  Serial.begin(9600);

  /*
  for(int i=0; i<10;i++){
    print_val(i);
    NeuralNetwork();
  }
  */
}  

void loop(){ 

  int xRaw = ReadAxis(xInput);
  int yRaw = ReadAxis(yInput);
  int zRaw = ReadAxis(zInput); 

  int xScaled = map(xRaw,  RawMin, RawMax, 0, 255);
  int yScaled = map(yRaw,  RawMin, RawMax, 0, 255);
  int zScaled = map(zRaw,  RawMin, RawMax, 0, 255);
  
  xfloat = (float)xScaled/255.0;
  yfloat = (float)yScaled/255.0;
  zfloat = (float)zScaled/255.0;
  
  
  test[0][contador*3+0] = (double)xScaled/255.0;
  test[0][contador*3+1] = (double)yScaled/255.0;
  test[0][contador*3+2] = (double)zScaled/255.0;

  if (contador < 4){
    contador++;
  }else{
    contador = 0;
    NeuralNetwork();

  }
  delay(100);
  
  
  
  
}

float sigmoid(float x){
  return 1.0/(exp(-x)+1.0);
}

float relu(float x){
  if( x >= 0){
    return x;
  }
  else{
    return 0; 
  }
}


void print_val(int vali_pos){
  //Serial.print("|   ");
  //Serial.print(labels[0][0]);
  //Serial.print("  ");
  for(int i=0; i < 15; i++){
    test[0][i] = validation[vali_pos][i];
  }
}

float NeuralNetwork(){

  // cálculo de la capa de entrada , capa 0:

  // WL0[15][16]
  // test[1][15]
  // mult0[1][16];
  Matrix.Multiply((mtx_type*)test, (mtx_type*)WL0, 1, 15, 16, (mtx_type*)mult0);

  // suma0[1][16];
  // BL0[1][16];
  Matrix.Add((mtx_type*)mult0, (mtx_type*)BL0, 1 , 16, (mtx_type*) suma0);

  // función de activación:
  // salida0[1][16];
  for(int i=0; i<16;i++){
    salida0[0][i] = relu(suma0[0][i]);
  }

  // cálculo de la capa de entrada , capa 1:

  // salida0[1][16];
  // WL1[16][16]
  // mult1[1][16];
  Matrix.Multiply((mtx_type*)salida0, (mtx_type*)WL1, 1, 16, 16, (mtx_type*)mult1);

  // suma1[1][16];
  // BL1[1][16];
  Matrix.Add((mtx_type*)mult1, (mtx_type*)BL1, 1 , 16, (mtx_type*) suma1);

  // función de activación:
  for(int i=0; i<16;i++){
    salida1[0][i] = relu(suma1[0][i]);
  }

  // cálculo de la capa de entrada , capa 2:

  // salida1[1][16];
  // WL2[16][3]
  // mult2[1][3];
  Matrix.Multiply((mtx_type*)salida1, (mtx_type*)WL2, 1, 16, 3, (mtx_type*)mult2);

  // suma2[1][16];
  // BL2[1][16];
  Matrix.Add((mtx_type*)mult2, (mtx_type*)BL2, 1 , 3, (mtx_type*) suma2);

  // función de activación:
  for(int i=0; i<3;i++){
    salida2[0][i] = sigmoid(suma2[0][i]);
  }

  // imprimir resultado
  maxValue();
/*
  for(int i=0; i<3;i++){
    if (i == 2){
      Serial.println(mult_val*salida2[0][i]);
      //Serial.print("\n");
    }else{
      Serial.print(mult_val*salida2[0][i]);
      Serial.print("\t");
    } 
  }
  */
  
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


int maxValue(){
  int indtotal = 3; //para recorrer hasta dos indices
  int inteval = 0;
  for (int m = 1; m < indtotal; m++){
    if (salida2[0][inteval] < salida2[0][m]){
      inteval = m;
    }
  }
  Serial.write(inteval);
  //imprimo el resultado
  /*
  if (inteval ==0){
    Serial.println("1 0 0 : trote");
  }else if (inteval == 1){
    Serial.println("0 1 0 : ejercicio gluteos");
  }else if (inteval == 2){
    Serial.println("0 0 1 : ejercicio piernas");
  }
  */
 
}







