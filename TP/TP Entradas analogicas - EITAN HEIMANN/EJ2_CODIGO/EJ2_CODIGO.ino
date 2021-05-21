//---- Salida digital ---- 
#define PIN_LED 3

//---- Entradas Analogicas ----
#define PIN_TERMOMETRO A0

//---- Delays ----
#define DELAY_SEGURIDAD 2

//---- Variables ----
float sensorTermometro;
float valorTermometro;
float temperatura;

void setup()
{
  
  Serial.begin(9600);
  Serial.println("Bienvenidos");
    
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TERMOMETRO, INPUT_PULLUP);
  
}

void loop()
{

  sensorTermometro = analogRead(A0);
  valorTermometro = (sensorTermometro * 5) / 1023;
  temperatura = -10 + (valorTermometro * 12) ;

  delay(DELAY_SEGURIDAD);

  if (temperatura <= 10)
  {
    digitalWrite(PIN_LED, LOW);
    Serial.println("Temperatura baja");
  /*Serial.println(temperatura);*/ // Para testear
  }

  if (temperatura > 10 && temperatura <= 25) // Si es 10 es temperatura baja
  {
    digitalWrite(PIN_LED, LOW);
    Serial.println("Temperatura media");
  /*Serial.println(temperatura);*/ // Para testear    
  }

  if (temperatura > 25) // Si es 25 es temperatura media
  {
    digitalWrite(PIN_LED, HIGH);
    Serial.println("Temperatura alta");
  /*Serial.println(temperatura);*/ // Para testear
  }
}
