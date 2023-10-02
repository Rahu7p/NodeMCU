// Definición de pines de entrada
const int pinA = D1;    //D1
const int pinB = D2;    //D2
const int pinC = D5;    //D5
const int pinD = D6;    //D6

// Definición de pin de salida para el LED
const int pinLED = D0;  //D0

void setup() {
  // Configuración de pines de entrada
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(pinC, INPUT);
  pinMode(pinD, INPUT);

  // Configuración de pin de salida para el LED
  pinMode(pinLED, OUTPUT);
}

void loop() {
  // Lectura de entradas
  int A = digitalRead(pinA);
  int B = digitalRead(pinB);
  int C = digitalRead(pinC);
  int D = digitalRead(pinD);
  
  // Evaluación de la expresión booleana
  int resultado = evaluarExpresion(A, B, C, D);

  // Encender o apagar el LED basado en el resultado de la expresión
  if( !resultado )
    digitalWrite(pinLED, HIGH);
  else
    digitalWrite(pinLED, LOW);
}

// Función para evaluar la expresión booleana
int evaluarExpresion(int A, int B, int C, int D) {
  // Expresión booleana simplificada: A'B' + B'D' + B'C'
  return (( A && !B ) || ( !B && !D ) || ( !B & !C ));
}
