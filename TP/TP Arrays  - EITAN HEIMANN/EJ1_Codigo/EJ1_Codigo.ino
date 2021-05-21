//---- DEFINES ----
#define TAMANO_VECTOR 12
#define BAUDIOS 9600

//---- VECTOR ----
int datos [TAMANO_VECTOR];

//---- VARIABLES DE LECTURA
int datoLeido;
int posicion;

//---- VARIABLES PARA INFO FINAL ----
int mesMayor;
int mesMenor;
int totalMeses;
int ingresoMayor;
int ingresoMenor;

void setup()
{
  Serial.begin(BAUDIOS);
  Serial.println("Ingrese las ganancias de cada mes en orden");

  for (posicion = 0 ; posicion < TAMANO_VECTOR ; posicion = posicion + 1)
  {
    while (Serial.available() == 0);

    datoLeido = Serial.parseInt();
    Serial.print(posicion + 1);
    Serial.print(": $");
    Serial.println(datoLeido);

    datos[posicion] = datoLeido;

  }
  ingresoMayor = datos[0];
  ingresoMenor = datos[0];
  totalMeses = 0;

  for ( posicion = 0 ; posicion  < TAMANO_VECTOR ; posicion = posicion + 1)
  {
    if (ingresoMayor < datos[posicion])
    {
      ingresoMayor = datos[posicion];
      mesMayor = posicion;
    }
    if (datos[posicion] < ingresoMenor)
    {
      ingresoMenor = datos[posicion];
      mesMenor = posicion;
    }
    totalMeses = totalMeses + datos[posicion];
  }
  Serial.print(" El mes con mayor ganancia fue el: ");
  Serial.println(mesMayor + 1);
  Serial.print(" Con una ganancia de: $");
  Serial.println(ingresoMayor);
  Serial.print(" El mes con menor ganancia fue el: ");
  Serial.println(mesMenor + 1);
  Serial.print(" Con una ganancia de: $");
  Serial.println(ingresoMenor);
  Serial.print(" El ingreso promedio fue de: $");
  Serial.println(totalMeses / TAMANO_VECTOR);
  Serial.print(" El ingreso total de todo el año fue de: $");
  Serial.println(totalMeses);
}

void loop()
{

}
