//---- DEFINES ----
#define TAMANO_VECTOR 12
#define BAUDIOS 9600

//---- VECTORES ----
int datos [TAMANO_VECTOR];

//---- VARIABLES DE LECTURA ----
int datoLeido;
int posicion;

//---- VARIABLES PARA INFORMACION FINAL ----
int mesMayor;
int mesMenor;
int promedio;
int totalMeses;
int ingresoMayor;
int ingresoMenor;

//---- FUNCIONES ----
int posicionMayor(int vector[], int elementos);
int posicionMenor(int vector[], int elementos);
int promedioIngreso(int vector[], int elementos);
int ingresoTotal(int vector[], int elementos);
void listado(int vector[], int elementos);

void setup()
{
  Serial.begin(BAUDIOS);
  Serial.println("Ingrese las ganancias de cada mes en orden");

  for (posicion = 0 ; posicion < TAMANO_VECTOR ; posicion = posicion + 1)
  {
    while (Serial.available() == 0);
    datoLeido = Serial.parseInt();
    Serial.println(datoLeido);
    datos[posicion] = datoLeido;
  }

  listado(datos, TAMANO_VECTOR);
  mesMayor = posicionMayor(datos, TAMANO_VECTOR );
  mesMenor = posicionMenor(datos, TAMANO_VECTOR);
  promedio = promedioIngreso(datos, TAMANO_VECTOR);
  totalMeses = ingresoTotal(datos, TAMANO_VECTOR);

  ingresoMayor = datos[mesMayor];
  ingresoMenor = datos[mesMenor];

  Serial.print(" El mes con mayor ganancia fue el: ");
  Serial.println(mesMayor + 1);
  Serial.print(" Con una ganancia de: $");
  Serial.println(ingresoMayor);
  Serial.print(" El mes con menor ganancia fue el: ");
  Serial.println(mesMenor + 1);
  Serial.print(" Con una ganancia de: $");
  Serial.println(ingresoMenor);
  Serial.print(" El ingreso promedio fue de: $");
  Serial.println(promedio);
  Serial.print(" El ingreso total de todo el año fue de: $");
  Serial.println(totalMeses);
}

void loop()
{

}

int posicionMayor(int vector[], int elementos)
{
  int mesGananciaMayor = 0;
  int mayorIngreso = vector[0];

  for (int lugar = 0 ; lugar  < elementos ; lugar = lugar + 1)
  {

    if (mayorIngreso < vector[lugar])
    {
      mayorIngreso = vector[lugar];
      mesGananciaMayor = lugar;
    }
  }
  return mesGananciaMayor;
}

int posicionMenor(int vector[], int elementos)
{
  int mesGananciaMenor = 0;
  int menorIngreso = vector[0];

  for (int lugar = 0 ; lugar  < elementos ; lugar = lugar + 1)
  {

    if (menorIngreso > vector[lugar])
    {
      menorIngreso = vector[lugar];
      mesGananciaMenor = lugar;
    }
  }
  return mesGananciaMenor;
}

int promedioIngreso(int vector[], int elementos)
{
  int promedioTotal = 0;

  for (int lugar = 0 ; lugar  < elementos ; lugar = lugar + 1)
  {
    promedioTotal = promedioTotal + vector[lugar];
  }
  promedioTotal = promedioTotal / elementos;
  return promedioTotal;
}

int ingresoTotal(int vector[], int elementos)
{
  int ingresoTotal = 0;

  for (int lugar = 0 ; lugar  < elementos ; lugar = lugar + 1)
  {
    ingresoTotal = ingresoTotal + vector[lugar];
  }

  return ingresoTotal;
}

void listado(int vector[], int elementos)
{
  for (int lugar = 0 ; lugar < elementos ; lugar = lugar + 1)
  {
    Serial.print(lugar + 1);
    Serial.print(": $");
    Serial.println(vector[lugar]);
  }
}
