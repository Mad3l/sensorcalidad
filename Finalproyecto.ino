int pinlec_salida=A2;//aforo salida
int pinlec_entrada=A3;//aforo entrada
int aforo=0;
int ventilacion1=10;//pin ventilación1
int ventilacion2=9;//pin ventilación2
int stemp=A1;//estado de temp


void setup() {
  Serial.begin(9600);
  pinMode(stemp,INPUT);
  pinMode(ventilacion1,OUTPUT);
  pinMode(ventilacion2,OUTPUT);
  
}

void loop() {
  //calidad de aire
  int sen_air=analogRead(A2);
  float voltaje = sen_air*(5.0/1023.0);
  float RS = 1000*(5-voltaje)/voltaje;
  float rsr0=RS/1.44;//valor de 
  float CO2= 5.1496*pow(rsr0,-0.346);//y=5.1496x<--0.346
  Serial.print("\nCalidad del aire:");
  Serial.println(CO2);
  
  //temperatura
  float lecturatemp = analogRead(stemp);
  float temp=((5.0*lecturatemp*100.0)/1024.0);
  Serial.print("Temperatura:");
  Serial.print(temp);
  Serial.println(" C°");

  //trigger 01 de ventilacion por calidad de aire
  if(sen_air>=700){
    digitalWrite(ventilacion1,HIGH);
    digitalWrite(ventilacion2,HIGH);
    while(sen_air>=500){
      sen_air=analogRead(A2);
      Serial.println(sen_air);
      }
    }
  if(sen_air<500){
      digitalWrite(ventilacion1,LOW);
      digitalWrite(ventilacion2,LOW);
      }
  //fin triger 01

  //trigger 02 ventiladores con temperatura
  if(temp>=28){
    digitalWrite(ventilacion1,HIGH);
    digitalWrite(ventilacion2,HIGH);
    while(temp>=25){
      float temp=((5.0*lecturatemp*100.0)/1024.0);
    }
    if(temp<25){
      digitalWrite(ventilacion1,LOW);
      digitalWrite(ventilacion2,LOW);
      }
    }
    //fin triger 02

    //contador de aforo
    float lecturaIN=analogRead(A3); //entrada
    float lecturaOUT=analogRead(A4); //entrada

    if(lecturaIN>=1002){
      Serial.println("entró");
      aforo++;
      while(lecturaIN>=1004){
        lecturaIN=analogRead(A3); //entrada
      }
      

    if(lecturaOUT>=1005){
      Serial.println("salió");
      aforo--;
      while(lecturaOUT>=1004){
        lecturaOUT=analogRead(A4); //entrada
      }
      
    }

    //trigger 03 ventilación por aforo
    int aforoi=100;
    float aforop=aforoi*0.4;
    float aforopor=(aforo*100)/aforoi;
    if(aforopor>=35){
      digitalWrite(ventilacion1,HIGH);
      digitalWrite(ventilacion2,HIGH);
    }
    if(aforopor<35){
        digitalWrite(ventilacion1,LOW);
        digitalWrite(ventilacion2,LOW);
        }
        //end trigger 03
        
      Serial.print("Porcetaje de aforo: ");
      Serial.print(aforopor);
      Serial.println("%");
      Serial.print("Aforo: ");
      Serial.println(aforo);
      Serial.println("Estado: Moderado");
      delay(1000);
    }   
}
