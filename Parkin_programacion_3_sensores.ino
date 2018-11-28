
//Declaramos los pines
const int led1 = 8;
const int led2= 9;
const int led3 = 10;
const int trig = 2;
const int echo = 3;
const int trig2 = 4;
const int echo2 = 5;
const int trig3 = 6;
const int echo3 = 7;

long tiempo;             //Declaramos algunas variables
long distancia;

void setup() {
  pinMode(led1, OUTPUT);  //Definimos los leds como salidas
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(trig, OUTPUT); //Activación del pin trig como salida: para el pulso ultrasónico
  pinMode(echo, INPUT);  //Activación del pin echo como entrada: tiempo del rebote del ultrasonido
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);

  // Setting up the serial port
  Serial.begin(9600);
  
}

void loop(){

  //Funcionamiento del sensor numero 1
  digitalWrite(trig, LOW);
  delayMicroseconds(5);                // Por cuestión de estabilización del sensor
  digitalWrite(trig, HIGH);            // Enviamos el pulso ultrasónico
  delayMicroseconds(10);
  tiempo = pulseIn(3, HIGH);
  //distancia = int(0.017*tiempo);       //Formula para calcular la distancia obtenida en cm

  // Si el sensor mide una distancia más pequeña o igual a 30cm, apagar el LED1
  if(CalculateDistance(tiempo) <= 30){
    // turn off led
    digitalWrite(led1, LOW); 

    // send sensor status occupied
    SendDataToSerialPort(1, 1);          
  }
  else{
    // turn on led
    digitalWrite(led1, HIGH);

    // send sensor status free
    SendDataToSerialPort(1, 0);
  }

  // Funcionamiento del sensor numero 2
  digitalWrite(trig2, LOW);
  delayMicroseconds(5);                // Por cuestión de estabilización del sensor
  digitalWrite(trig2, HIGH);           //Enviamos el pulso ultrasónico
  delayMicroseconds(10);
  tiempo = pulseIn(5, HIGH);
  //distancia = int(0.017*tiempo);       //Formula para calcular la distancia obtenida en cm

  // Si el sensor mide una distancia más pequeña o igual a 30cm, apagar el LED2
  if(CalculateDistance(tiempo) <= 30){
    // turn off led
    digitalWrite(led2, LOW);      

    // send sensor status occupied
    SendDataToSerialPort(2, 1);     
  }
  else{
    // turn on led
    digitalWrite(led2, HIGH);

    // send sensor status free
    SendDataToSerialPort(2, 0);
  }
  
  // Funcionamiento del sensor numero 3
  digitalWrite(trig3, LOW);
  delayMicroseconds(5);                // Por cuestión de estabilización del sensor
  digitalWrite(trig3, HIGH);           //Enviamos el pulso ultrasónico
  delayMicroseconds(10);
  tiempo = pulseIn(7, HIGH);
  //distancia = int(0.017*tiempo);       //Formula para calcular la distancia obtenida en cm

  // Si el sensor mide una distancia más pequeña o igual a 30cm, apagar el LED3
  if(CalculateDistance(tiempo) <= 30){
    // turn off led
    digitalWrite(led3, LOW);
    
    // send sensor status occupied
    SendDataToSerialPort(3, 1);           
  }
  else{
    // turn on led
    digitalWrite(led3, HIGH);

    // send sensor status free
    SendDataToSerialPort(3, 0);
  }

} 

int CalculateDistance(unsigned long time)
{
  return int(0.017 * time);  
}

// Send data to serial port
// sensorId sensor id number , ex 1 or 2 or 3
// status, if parking spot occupied 1, otherwise 0 (free parking spot)
void SendDataToSerialPort(byte sensorId, byte status)
{
  // setting up the buffer data to send
  byte buffer[2] = { sensorId, status };

  // sending data
  Serial.write(buffer, 2);
}
