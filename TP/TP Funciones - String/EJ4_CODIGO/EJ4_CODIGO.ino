//---- DEFINICIONES ----
#define PIN_LED_ROJO 3
#define PIN_LED_VERDE 4
#define PIN_LED_AZUL 5
#define RANGO_PWM 255
#define RANGO_PORCENTAJE 100
#define BAUDIOS 9600

//---- FUNCIONES ----
void actualizarValores ( int recibeRojo, int recibeVerde, int recibeAzul);

void setup()
{
  Serial.begin (BAUDIOS);
  
  pinMode(PIN_LED_ROJO, OUTPUT);
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_LED_AZUL, OUTPUT);
}

void loop()
{
  while (Serial.available () == 0);
  
  actualizarValores (PIN_LED_ROJO, PIN_LED_VERDE, PIN_LED_AZUL);
  
  while (Serial.available())
  {
    Serial.read();
  }
}
void actualizarValores ( int recibeRojo, int recibeVerde, int recibeAzul)
{
  int ledRojoPorcentaje;
  int ledVerdePorcentaje;
  int ledAzulPorcentaje;
  int ledRojoPWM;
  int ledVerdePWM;
  int ledAzulPWM;

  ledRojoPorcentaje = Serial.parseInt();
  ledVerdePorcentaje = Serial.parseInt();
  ledAzulPorcentaje = Serial.parseInt();

  ledRojoPWM = ledRojoPorcentaje * (RANGO_PWM / RANGO_PORCENTAJE);
  ledVerdePWM = ledVerdePorcentaje * (RANGO_PWM / RANGO_PORCENTAJE);
  ledAzulPWM = ledAzulPorcentaje * (RANGO_PWM / RANGO_PORCENTAJE);

  analogWrite(recibeRojo, ledRojoPWM);
  analogWrite(recibeVerde, ledVerdePWM);
  analogWrite(recibeAzul, ledAzulPWM);
}
