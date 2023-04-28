
#include <DHT11.h>

// -------------------------------------------------------------------------------
// Distribución de Pines Analógicos en los sensores
// -------------------------------------------------------------------------------
int sensorNivel = A0, sensorLluvia = A1, sensorLuz = A2, sensordht11 = A3, sensorSuelo = A4;
DHT11 dht11(sensordht11);

// -------------------------------------------------------------------------------
// Variables iniciales de los sensores
// -------------------------------------------------------------------------------
int error , nivelValor, lluviaValor, luzValor, luz, sueloValor;
float tempValor, humeValor;

// -------------------------------------------------------------------------------
// Distribución de Pines Digitales en los actuadores
// -------------------------------------------------------------------------------
int regarPin = 10, ledNivel = 9, ledLluvia = 8, ledLuz = 7, ledSuelo = 6;

void setup() {
  Serial.begin(9600);
  pinMode(regarPin, OUTPUT);
  pinMode(ledNivel, OUTPUT);
  pinMode(ledLluvia, OUTPUT);
  pinMode(ledLuz, OUTPUT);
  pinMode(ledSuelo, OUTPUT);
}

void loop() {
  nivelValor = analogRead(sensorNivel);
  lluviaValor = analogRead(sensorLluvia);
  luzValor = analogRead(sensorLuz);
  error = dht11.read(tempValor, humeValor); 
  sueloValor = analogRead(sensorSuelo);
  delay(3000);   
  Serial.println("--------------------------------------------------------------------------------");
  Serial.println("          IMPRESION DE LAS CONDICIONES AMBIENTALES         ");
  Serial.println("--------------------------------------------------------------------------------");  
  if(error == 0) { // Si devuelve 0 ha leído bien.
       Serial.print("Humedad: "); 
       Serial.print(humeValor);
       Serial.println("\n");
       Serial.print("Temperatura: "); 
       Serial.print(tempValor);
       Serial.println(" *C ");
       Serial.println("\n");
  } else {
       Serial.println();
       Serial.print("Error Num :");
       Serial.print(error);
       Serial.println();
  }
  luz = (100.0 * luzValor) / 1024;
       Serial.print("Luz: ");
       Serial.print(luz);
       Serial.println(" L");    
  Serial.println("--------------------------------------------------------------------------------");
  Serial.println("           IMPRESION DE LAS CONDICIONES DEL DISPOSITIVO          ");
  Serial.println("--------------------------------------------------------------------------------");       
       Serial.print("Nivel de Agua: "); 
       Serial.println(nivelValor);
       Serial.println("\n");
       Serial.print("Lluvia: "); 
       Serial.println(lluviaValor);
       Serial.println("\n");
       Serial.print("Humedad del suelo: "); 
       Serial.println(sueloValor);
       Serial.println("---------------------------------------------------------------------------------");
       Serial.println("---------------------------------------------------------------------------------");
       Serial.println("---------------------------------------------------------------------------------");
       Serial.println("---------------------------------------------------------------------------------");
       Serial.println("---------------------------------------------------------------------------------");
  // -------------------------------------------------------------------------------
  // Evaluación de riego
  // -------------------------------------------------------------------------------
  if(nivelValor == 0) {       
       Serial.println();
       Serial.print("Error : ");
       Serial.print(" Se detecta falta agua en el tanque ");
       Serial.println();
       digitalWrite(ledNivel, HIGH);
       digitalWrite(regarPin, LOW); 
  } else if(lluviaValor > 10) {
       Serial.println();
       Serial.print("Error :");
       Serial.print(" Se detecta lluvia ");
       Serial.println();
       digitalWrite(ledLluvia, HIGH);
       digitalWrite(regarPin, LOW);  
  } else if((tempValor <= 4)&&(luzValor < 50)) {
       Serial.println();
       Serial.print("Error :");
       Serial.print(" Se detecta riesgo de congelamiento ");
       Serial.println();
       digitalWrite(ledLuz, HIGH);
       digitalWrite(regarPin, LOW);
   } else if((tempValor >= 40)&&(luzValor > 50)) {
       Serial.println();
       Serial.print("Error :");
       Serial.print(" Se detecta riesgo de quemado ");
       Serial.println();
       digitalWrite(ledLuz, HIGH);
       digitalWrite(regarPin, LOW);
   } else if(sueloValor <= 100) {
       Serial.println();
       Serial.print("Error :");
       Serial.print(" Se detecta humedad suficiente ");
       Serial.println(); 
       digitalWrite(ledSuelo, HIGH);
       digitalWrite(regarPin, LOW);
   } else{
       Serial.println("ES CONVENIENTE REGAR");
       Serial.println("================================================================================");
       digitalWrite(ledNivel, LOW);
       digitalWrite(ledLluvia, LOW);
       digitalWrite(ledLuz, LOW);
       digitalWrite(ledSuelo, LOW);
       digitalWrite(regarPin, HIGH);
   }
}
