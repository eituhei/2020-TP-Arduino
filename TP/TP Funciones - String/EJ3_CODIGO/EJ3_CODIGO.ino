//---- DEFINICIONES ----
#define BAUDIOS 9600
#define ESTADO_ALTO "Ahora el estado de la salida es alto"
#define ESTADO_BAJO "Ahora el estado de la salida es bajo"
#define PIN_SALIDA 3

//---- FUNCIONES ----
void digitalToggle(int pin);

void setup()
{
  Serial.begin(BAUDIOS);
  pinMode(PIN_SALIDA, OUTPUT);
}

void loop()
{
  digitalToggle(PIN_SALIDA);
}

void digitalToggle(int pin)
{
  if (digitalRead(pin) == LOW)
  {
    digitalWrite(pin, HIGH);
  }

  else
  {
    digitalWrite(pin, LOW);
  }
}
