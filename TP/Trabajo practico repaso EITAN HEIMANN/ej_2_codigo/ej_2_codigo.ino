//---- Definicion de entradas ----
#define PIN_BOTON 3

//---- Definicion de salidas ----
#define PIN_LED   4

//---- Estado del boton ----
#define BOTON_PRESIONADO  0

//---- Constantes de tiempo ----
#define TIEMPO_ON 2000

//---- Informacion del contador ----
#define CANTIDAD_DESEADA_CONTADOR        3
#define INICIO_CONTADOR 0

//---- Varianles
boolean estadoBoton;
int contadorBoton = 0;



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
    while (estadoBoton = BOTON_PRESIONADO)
    {
      estadoBoton = digitalRead(PIN_BOTON);
    }
    contadorBoton = contadorBoton + 1;
  }
  if (contadorBoton == CANTIDAD_DESEADA_CONTADOR)
  {
    digitalWrite(PIN_LED, HIGH);
    delay(TIEMPO_ON);
    digitalWrite(PIN_LED, LOW);
    contadorBoton = INICIO_CONTADOR;
  }
}
