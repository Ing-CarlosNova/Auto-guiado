const int FSR_PIN = A0;
const float VCC = 5.0; // Voltaje de alimentación del Arduino
const float R_DIV = 10000.0; // Valor de la resistencia de 10kΩ en ohmios

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Leer el valor del FSR
  int fsrADC = analogRead(FSR_PIN);

  // Convertir el valor ADC a voltaje
  float fsrV = fsrADC * (VCC / 1023.0);

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
  Serial.print(fsrADC);
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
