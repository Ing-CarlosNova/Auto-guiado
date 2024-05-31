const int FSR_PIN = A0;
const float VCC = 5.0; // Voltaje de alimentación del Arduino
const float R_DIV = 10000.0; // Valor de la resistencia de 10kΩ en ohmios

const int numReadings = 10;
float readings[numReadings]; // Array to store readings
int readIndex = 0; // Index of the current reading
float total = 0; // Running total
float average = 0; // Average of the readings


void setup() {
  Serial.begin(9600);
  //realiza un llenado de vector con valores de o
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {

   total = total - readings[readIndex];
  // Read from the sensor:
  readings[readIndex] = analogRead(FSR_PIN);
  // Add the reading to the total:
  total = total + readings[readIndex];
  // guarda el valor del sensor en la posición del vector el 
  readIndex = readIndex + 1;

 if (readIndex >= numReadings) {
    readIndex = 0;
  }

  // Calculate un promedio de 10 datos leidos para el peso
  average = total / numReadings;


  // Leer el valor del FSR
  //int fsrADC = analogRead(FSR_PIN);

  // Convertir el valor ADC a voltaje
  float fsrV = average * (VCC / 1023.0);

  // Calcular la resistencia del FSR
  float fsrR = R_DIV * (VCC / fsrV - 1.0);

  // Calcular la fuerza en Newtons (esto depende del modelo específico del FSR)
  float force = 0;
  if (fsrR <= 600) {
    force = (fsrR - 600) / 6000; // Esto depende del modelo y debe ajustarse
  } else {
    force = (fsrR - 600) / 250; // Esto depende del modelo y debe ajustarse
  }

  // Convertir la fuerza de Newtons a kilogramos (1 Newton = 0.10197 kg)
  float weight = force * 0.10197;

  // Imprimir los resultados
  Serial.print("ADC Value: ");
  Serial.print(average);
  Serial.print("\tVoltage: ");
  Serial.print(fsrV);
  Serial.print(" V\tResistance: ");
  Serial.print(fsrR);
  Serial.print(" ohms\tForce: ");
  Serial.print(force);
  Serial.print(" N\tWeight: ");
  Serial.print(weight);
  Serial.println(" kg");

  delay(500);
}
