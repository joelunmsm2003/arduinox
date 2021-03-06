int pinLatch = 10;    //Pin para el latch de los 74CH495
int pinDatos = 11;    //Pin para Datos serie del 74CH495
int pinReloj = 12;    //Pin para reloj del 74CH495

int letra = 0;         //Variable para cada letra
int ciclo = 0;         //Variable para los ciclos de cada letra en cada posicion
int desplaza = 0;      //Variable para generar desplazamiento en las filas


////////////
 int ledPin = 13;
 int joyPin1 = 0;                 // slider variable connecetd to analog pin 0
 int joyPin2 = 1;                 // slider variable connecetd to analog pin 1
 int value1 = 0;                  // variable to read the value from the analog pin 0
 int value2 = 0;                  // variable to read the value from the analog pin 1


 ///////////////////

//Definimos los numeros decimales que hacen falta para dibujar cada caracter

#define SP {0, 0, 0, 0, 0}               //Espacio
#define EX {0, 125, 0, 0, 0}             //Exclamacion !
#define A {31, 36, 68, 36, 31}
#define B {127, 73, 73, 73, 54,}
#define C {62, 65, 65, 65, 34}
#define D {127, 65, 65, 34, 28}
#define E {127, 73, 73, 65, 65}
#define F {127, 72, 72, 72, 64}
#define G {62, 65, 65, 69, 38}
#define H {127, 8, 8, 8, 127}
#define I {0, 65, 127, 65, 0}
#define J {2, 1, 1, 1, 126}
#define K {127, 8, 20, 34, 65}
#define L {127, 1, 1, 1, 1}
#define M {127, 32, 16, 32, 127}
#define N {127, 32, 16, 8, 127}
#define O {62, 65, 65, 65, 62}
#define P {127, 72, 72, 72, 48}
#define Q {62, 65, 69, 66, 61}
#define R {127, 72, 76, 74, 49}
#define S {50, 73, 73, 73, 38}
#define T {64, 64, 127, 64, 64}
#define U {126, 1, 1, 1, 126}
#define V {124, 2, 1, 2, 124}
#define W {126, 1, 6, 1, 126}
#define X {99, 20, 8, 20, 99}
#define XA {36, 00, 255, 66, 60}
#define XB {36, 00, 60, 66, 255}
#define Y {96, 16, 15, 16, 96}
#define Z {67, 69, 73, 81, 97}
//#define FD {00, 28, 28, 127, 62, 28, 8, 00}
//#define FI {00, 8, 28, 62, 127, 28, 28, 00}
#define FX {255, 255, 255, 255, 255, 255, 255, 255}
#define FY {255, 255, 255, 231, 231, 255, 255, 255}
#define FZ {255, 129, 189, 165, 165, 189, 129, 255}
#define CA {116,86, 117, 5, 5, 117, 86, 116}
//Escribimos la frase separando cada letra por comas
//En el primer numero lo adaptaremos la longitud de la frase (caracteres)
//byte frase[32][6]={B,I,E,N,V,E,N,I,D,O,S,SP,A,SP,A,R,D,U,I,N,O,SP,A,C,A,D,E,M,Y,SP,SP,SP};

  byte frase[32][9]={XA,XA,B,I,E,N,V,E,N,I,D,O,S,SP,A,SP,X,I,E,N,C,I,A,S,XA,XA,SP};

//Almacenamos los pines de las filas que van conectadas a los catodos
int gnd[13]={0,0,0,0,0,2,3,4,5,6,7,8,9};

//Configuramos la placa
void setup()

{
  
      Serial.begin(9600);
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

  value1 = analogRead(joyPin1);   
  // this small pause is needed between reading
  // analog pins, otherwise we get the same value twice
           
  // reads the value of the variable resistor 
  value2 = analogRead(joyPin2); 
  Serial.println(value1);  
  Serial.println(value2); 
  
  

for (int count = 0 ; count <= 1; count ++)
  {
    if (count < 1 )
      {
        for (desplaza = 8; desplaza>=0; desplaza--)
          {
            for (ciclo=0; ciclo<=35; ciclo++)
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
 for (int z=5; z<=0; z--)
       {
          int fila = z - desplaza;                                  //Le decimos en que linea empieza a dibujar
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
