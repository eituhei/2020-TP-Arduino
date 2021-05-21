//---- Definicion de entradas ----
#define PIN_BOTON 3

//---- Definicion de salidas ----
#define PIN_LED   4

//---- Constantes de tiempo ----
#define TIEMPO_ON 5000

//---- Estado del boton ----
#define BOTON_PRESIONADO  0

//---- Variables ----
boolean estadoBoton;


void setup()
{
  pinMode(PIN_BOTON, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
}

void loop()
{
  estadoBoton = digitalRead(PIN_BOTON);
  if (estadoBoton == BOTON_PRESIONADO)
  {
    digitalWrite(PIN_LED, HIGH);
    delay(TIEMPO_ON);
    digitalWrite(PIN_LED, LOW);
  }
}
