//---- DEFINICIONES ----
#define BAUDIOS 9600

//---- VARIABLES ----
float base;
int exponente;
float resultadoFinal;

//---- FUNCIONES ----
float resultadoCuenta (float baseRecibida, int exponente);

void setup()
{
  Serial.begin(BAUDIOS);
}

void loop()
{
  while (Serial.available() == 0);
  base=Serial.parseFloat();
  
  while (Serial.available() == 0);
  exponente=Serial.parseInt();
  
  resultadoFinal = resultadoCuenta( base , exponente);
  
  Serial.print("El resultado es ");
  Serial.println(resultadoFinal);
  
}

float resultadoCuenta (float baseRecibida, int exponenteRecibido)
{
  float resultado = 1;

  for (int indice = 0; indice < exponenteRecibido; indice = indice + 1)
  {
    resultado = resultado * baseRecibida;
  }
  return resultado;
}
