#include <LiquidCrystal.h>
const int ledA = 1;
const int ledV = 2;
const int ledR = 3;
const int ledAlert = 4;
const int ledListo = 5;
const int boton = A1;
const int salP = A0;
int botonEst = 1;
int parpadeoEs = 0;
int voltageInp;
int contador = 0;
int limpieza = 0;
int tiempo = 0;
//LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
void setup() {
  lcd.begin(2, 16);
  pinMode(ledA, OUTPUT);
  pinMode(ledV, OUTPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledAlert, OUTPUT);
  pinMode(ledListo, OUTPUT);
  pinMode(boton, INPUT);
  pinMode(botonEst, INPUT);
}
void loop() {
  botonEst = digitalRead(boton);
  if (botonEst == 1) {
    if (limpieza == 0) {
      lcd.clear();
      limpieza = 1;
    }
    if (contador >= 10) {
      lcd.setCursor(0, 0);
      lcd.print("QUESO LISTO :)");
      lcd.setCursor(0, 1);
      lcd.print("Duracion:");
      lcd.setCursor(9, 1);
      lcd.print(String(contador)+"s");
      digitalWrite(ledAlert, LOW);
      digitalWrite(ledListo, HIGH);
      delay(9000);
    }
    else {
      lcd.setCursor(0, 0);
      lcd.print("ECHANDO SAL :)");
      lcd.setCursor(0, 1);
      lcd.print("Tiempo:");
      lcd.setCursor(7, 1);
      lcd.print(contador);
      parpadeo();
    }
  } else {
    lcd.setCursor(0, 0);
    lcd.print("ESTADO :)");
    //voltageInp = analogRead(salP);
    voltageInp = 55;
    salinidad();
  }
}
void salinidad() {
  lcd.setCursor(0, 1);
  //lcd.clear();
  if (voltageInp <= 51) { //11 24 50
    //Serial.print("led amarillo -> ");
    lcd.print("BAJO :| ..");
    digitalWrite(ledA, HIGH);
    digitalWrite(ledV, 0);
    digitalWrite(ledR, 0);
  } else {
    if (voltageInp >= 52 && voltageInp <= 56) {//12:13 55:45
      //Serial.print("led verde -> ");
      lcd.print("ADECUADO :) ..");
      digitalWrite(ledA, 0);
      digitalWrite(ledV, HIGH);
      digitalWrite(ledR, 0);
    } else {
      //Serial.print("led rojo -> ");
      lcd.print("ALTO :( ..");
      digitalWrite(ledA, 0);
      digitalWrite(ledV, 0);
      digitalWrite(ledR, HIGH);
    }
  }
}
void parpadeo() {
  if (parpadeoEs == 0) {
    digitalWrite(ledAlert, LOW);
    parpadeoEs = 1;
  } else {
    digitalWrite(ledAlert, HIGH);
    parpadeoEs = 0;
  }
  delay(250);
  tiempo++;
  if (tiempo == 4) {
    tiempo = 0;
    contador++;
  }
}


