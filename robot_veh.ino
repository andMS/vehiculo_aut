#include <Servo.h> 
#define pecho 3
#define ptrig 2

// motores
 
int IN1 = 7;
int IN2 = 8;
int IN3 = 9;
int IN4 = 10;







long duracion, distancia;

Servo servo1;

void setup () {
  
//establecer entradas y salidas

  
 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4 , OUTPUT);

  pinMode(pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(ptrig, OUTPUT);    // define el pin 7 como salida  (triger)
  Serial.begin(9600);
  digitalWrite(ptrig, LOW);//Inicializamos el pin con 0

  servo1.attach(12, 600, 1500);

}


void loop() {


// se busca si hay obstáculos 

    digitalWrite(ptrig, HIGH);   
    delay(10);
    digitalWrite(ptrig, LOW);

    duracion = pulseIn(pecho, HIGH);        
    distancia = (duracion / 2) / 29;          
    delay(100);

/*detecta si hay un obstáculo a menos de 15 cm 
 * y más de 1 cm (para que no maarque errores)
 */
    if (distancia <= 20 && distancia >= 1 )  {

//apaga los motores 
      digitalWrite(IN1, 0);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 0);
      delay (1000);

// el sensor gira a la derecha para verificar que no haya objetos

      servo1.write(0);
      delay (1000);

      digitalWrite(ptrig, HIGH);   
      delay(10);
      digitalWrite(ptrig, LOW);

      duracion = pulseIn(pecho, HIGH);         
      distancia = (duracion / 2) / 29;          
      delay(100);

      if (distancia > 20) {  //si no hay objetos a menos de 15 cm

//reversa
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        delay (300);

//giro a la derecha
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
        digitalWrite(IN4, HIGH);
        digitalWrite(IN3, LOW);
        delay (250);

//sensor en posición inicial

        servo1.write(0);
        delay (300);
        

      } else { // si hay un objeto a la derecha

        digitalWrite(IN1, 0);
        digitalWrite(IN2, 0);
        digitalWrite(IN3, 0);
        digitalWrite(IN4, 0);
        delay (1000);

//giro de sensor a la izq para verificar que no haya objetos

        servo1.write(180);
        delay (700);

        digitalWrite(ptrig, HIGH);   
        delay(10);
        digitalWrite(ptrig, LOW);

        duracion = pulseIn(pecho, HIGH);         
        distancia = (duracion / 2) / 29;         
        delay(100);


        if (distancia > 20) { // si no detecta objetos a la izq, giro a la izquierda
          
          digitalWrite(IN2, HIGH);
          digitalWrite(IN3, HIGH);
          delay (300);


          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          delay (550);
        }

      }


    } else  {

      //si no hay obstáculos, sensor mirando al frente y motores encendidos
      
      servo1.write(90);
    

      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN4, HIGH);
      digitalWrite(IN3, LOW);

    }


}
