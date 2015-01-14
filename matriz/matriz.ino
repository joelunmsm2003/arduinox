int pinLatch = 10;    //Pin para el latch de los 74CH495
int pinDatos = 11;    //Pin para Datos serie del 74CH495
int pinReloj = 12;    //Pin para reloj del 74CH495
int letra = 0;         //Variable para cada letra
int ciclo = 0;         //Variable para los ciclos de cada letra en cada posicion
int desplaza = 0;      //Variable para generar desplazamiento en las filas
//Definimos los numeros decimales que hacen falta para dibujar cada caracter
#define SP {1, 1, 1, 1, 1}    


//Escribimos la frase separando cada letra por comas
//En el primer numero lo adaptaremos la longitud de la frase (caracteres)
//byte frase[32][6]={B,I,E,N,V,E,N,I,D,O,S,SP,A,SP,A,R,D,U,I,N,O,SP,A,C,A,D,E,M,Y,SP,SP,SP};
  byte frase[32][9]={XA,XA,B,I,E,N,V,E,N,I,D,O,S,SP,A,SP,X,I,E,N,C,I,A,S,XA,XA,SP};
//Almacenamos los pines de las filas que van conectadas a los catodos
int gnd[13]={0,0,0,0,0,2,3,4,5,6,7,8,9};
//Configuramos la placa
void setup()
{
  //Ponemos del pin 2 al 12 como salidas
  for (int i=2;i<=12; i++)
    {
      pinMode(i, OUTPUT);
    }  
  //Ponemos a nivel alto todas las lineas de los catodos de la matriz
  for (int g=2; g<=9; g++)
    {
      digitalWrite(g, HIGH);
    }
} 
void loop()
{
//Pequeño contador para que salga una letra de cada color
for (int count = 0 ; count <= 1; count ++)
  {
    if (count < 1 )
      {
        for (desplaza = 8; desplaza>=0; desplaza--)
          {
            for (ciclo=0; ciclo<=1; ciclo++)
              {
                imprimeRojo();
              }
          }
      }
    else {
        for (desplaza = 8; desplaza>=0; desplaza--)
          {
            for (ciclo=0; ciclo<=1; ciclo++)
              {
                imprimeRojo();
              }
          }
        }
  //Una vez ha mostrado una letra, sumamos uno para que salga la siguiente
  letra++;
  }
//Cuando ha llegado al final de la frase, lo pone a cero para que vuelva a salir
//Si cambiamos la longitud de la frase, este valor hay que cambiarlo
if(letra == 32)
  {
    letra = 0;
  }
}
//Funcion que imprime en color rojo
void imprimeRojo()
{
 //Un contador del tamaño de las letras (5 lineas de ancho)
 for (int z=0; z<=5; z++)
       {
          int fila = z + desplaza;                                  //Le decimos en que linea empieza a dibujar
          digitalWrite(gnd[fila], LOW);                             //La ponemos a cero
          digitalWrite(pinLatch, LOW);                              //Le decimos a los registros que empiecen a escuchar los datos
          shiftOut(pinDatos, pinReloj, MSBFIRST, 0);                //Le decimos que en el ultimo registro no encienda nada
          shiftOut(pinDatos, pinReloj, MSBFIRST, frase[letra][z]);  //Le decimos que imprima la línea z de la letra en el primer registro (rojo)
          digitalWrite(pinLatch, HIGH);                             //Guarda y graba las salidas en los registros al poner a 1 el latch
          digitalWrite(gnd[fila], HIGH);                            //Apagamos esa fila poniendola en alto
        }
}
//Funcion que imprime en color verde
void imprimeVerde()
{
 //Un contador del tamaño de las letras (5 lineas de ancho)
 for (int z=0; z<=5; z++)
       {
          int fila = z + desplaza;                                  //Le decimos en que linea empieza a dibujar
          digitalWrite(gnd[fila], LOW);                          //La ponemos a cero
          digitalWrite(pinLatch, LOW);                     //Le decimos a los registros que empiecen a escuchar los datos
          shiftOut(pinDatos, pinReloj, MSBFIRST, frase[letra][z]);  //Le decimos que imprima la linea z de la letra en el segundo registro (verde)
          shiftOut(pinDatos, pinReloj, MSBFIRST, 0);       //Le decimos que en el primer registro no encienda nada
          digitalWrite(pinLatch, HIGH);                    //Guarda y graba las salidas en los registros al poner a 1 el latch
          digitalWrite(gnd[fila], HIGH);                         //Apagamos esa fila poniendola en alto
        }
}
