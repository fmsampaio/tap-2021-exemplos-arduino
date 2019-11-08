#include <Ultrasonic.h>
Ultrasonic ultrassom(8,7); 
//e onde esta ligado o trig(8) e o echo(7) respectivamente
long distancia;

void setup() {
Serial.begin(9600); //Habilita Comunicação Serial a uma taxa de 9600 bauds.
}
// Função que se repete infinitamente quando a placa é ligada
void loop()
{
  distancia = ultrassom.Ranging(CM);// ultrassom.Ranging(CM) retorna a distancia em
                                    // centímetros(CM) ou polegadas(INC)
  Serial.print(distancia); //imprime o valor da variável distancia
  Serial.println("cm");
  delay(100);
}

