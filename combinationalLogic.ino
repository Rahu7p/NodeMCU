// Definición de pines de entrada
// DIP Switch -> D:5, C:6, B:7, A:8
const int pinA = D6;    
const int pinB = D5;    
const int pinC = D2;    
const int pinD = D1;    

// Definición de pin de salida para el LED
const int pinLED = D7;  

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
  if( resultado == 0 )
    digitalWrite(pinLED, LOW);
  else
    digitalWrite(pinLED, HIGH);
}

// Función para evaluar la expresión booleana
int evaluarExpresion(int A, int B, int C, int D) {
  // Reemplazar la expresión en minitérminos con la ecuación simplificada
  return ((!A && !B && !C && !D) || //m0
          (!A && !B && !C &&  D) || //m1
          (!A && !B &&  C && !D) || //m2
          ( A && !B && !C &&  D) || //m9
          ( A && !B &&  C &&  D));  //m11
}
