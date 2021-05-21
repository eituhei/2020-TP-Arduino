#define PIN_BOCINA                     8

void setup() {
  pinMode(PIN_BOCINA, OUTPUT);
}

void loop () {

}
void sonidoAlarma ()
{
  int duracion = 250;
  int frecmin = 2000;
  int frecmax = 4000;
  int i;
  for (i = frecmin; i <= frecmax; i++) {
    tone(PIN_BOCINA, i, duracion);
  }
  for (i = frecmax; i >= frecmin; i--) {
    tone(PIN_BOCINA, i, duracion);
  }
}
