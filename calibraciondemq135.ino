void setup() {
  Serial.begin(9600);

}
//medir el aire limpio en donde estamos
void loop() {
  float sensor_voltaje;
  float RS_aire; //Valor de RS en aire limpio
  float R0;
  float sensorValor=0.0;

  //Promedio del valor
  for(int i = 0 ; i < 100 ; i++){
    sensorValor = sensorValor + analogRead(A0);
    delay(10);
  }
  sensorValor = sensorValor/100.0;

  sensor_voltaje =  sensorValor/1024*5.0;
  RS_aire = (5.0-sensor_voltaje)/sensor_voltaje;
  R0 = RS_aire/9.8;

  Serial.print("Voltaje del sensor: ");
  Serial.print(sensor_voltaje);
  Serial.println("V");

  Serial.print("R0: ");
  Serial.println(R0);
  delay(1000);
  //R0=1.41
}
