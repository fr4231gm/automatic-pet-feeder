//Librerias necesarias
#include <LiquidCrystal.h>
#include <Servo.h>
#include <Wire.h>
#include <Stepper.h>
#include <RTClib.h>

//Pasos del pap
const int PPR = 200;
// RTC_DS1307 rtc;
RTC_DS3231 rtc;
//Pantalla LCD (configuracion de pines)
LiquidCrystal lcd(12, 11, 5, 8, 7, 6);
//Configurando PAP
Stepper mypap(PPR, 2, 3, 9, 10);


  // Valores por defecto de las variables
int numeroDeComidas = 1;  //Numero de veces que el sistema concede comida al animal
int cantidadDeComida = 5; //Vueltas del PAP, luego intentaré ver cuantos gramos da una vuelta  
int horaComida1 = 22;
int minutoComida1 = 30;
int horaComida2 = 22;
int minutoComida2 = 30;
const int boton1 = 13;
const int boton2 = 4;


void setup() {
  
  
lcd.begin(16,2);
lcd.setCursor(17,0);
lcd.print("Iniciando...");
pinMode(boton1, INPUT);
pinMode(boton2, INPUT);
mypap.setSpeed(60);
  //Verificamos que el sistema RTC está en buenas condiciones
   if (!rtc.begin()) {
      lcd.clear();
      lcd.print(("Error en el RTC"));
      while (1);
   }

delay(1000);
lcd.clear();

}

void printearDatos(DateTime date)
{
   lcd.setCursor(17,0);
   lcd.print(date.hour(), DEC);
   lcd.print(':');
   lcd.print(date.minute(), DEC);
   lcd.print(':');
   lcd.print(date.second(), DEC);
   lcd.setCursor(8,0);
   lcd.print("Cant:");
   lcd.setCursor(3,0);
   lcd.print(cantidadDeComida);
   if(numeroDeComidas == 1){
    lcd.noAutoscroll();
    lcd.setCursor(17,1);
    lcd.print("Hora: ");
    lcd.setCursor(10,1);
    lcd.print(horaComida1);
    lcd.setCursor(8,1);
    lcd.print(":");
    lcd.setCursor(7,1);
    lcd.print(minutoComida1);
   }else if(numeroDeComidas ==2){
    lcd.autoscroll();
    lcd.setCursor(17,1);
    lcd.print("Hora 1: ");
    lcd.setCursor(10,1);
    lcd.print(horaComida1);
    lcd.setCursor(8,1);
    lcd.print(":");
    lcd.setCursor(7,1);
    lcd.print(minutoComida1);
    lcd.print("Hora 2: ");
    lcd.setCursor(10,1);
    lcd.print(horaComida2);
    lcd.setCursor(8,1);
    lcd.print(":");
    lcd.setCursor(7,1);
    lcd.print(minutoComida2);
    
   }
}

void loop() {
  // Bucle principal del programa
  DateTime fecha = rtc.now();
 printearDatos(fecha);
  
if(numeroDeComidas == 1){
  if(fecha.hour() == horaComida1 && fecha.minute() == minutoComida1){
    lcd.clear();
    lcd.setCursor(17,0);
    lcd.print("Dando de comer");
    mypap.step(cantidadDeComida*200);
    delay(500);
  }
  
}else if(numeroDeComidas == 2){
  if(fecha.hour() == horaComida1 && fecha.minute() == minutoComida1){
    lcd.clear();
    lcd.setCursor(17,0);
    lcd.print("Dando de comer");
    mypap.step(cantidadDeComida*200);
    delay(500);
  }
  if(fecha.hour() == horaComida2 && fecha.minute() == minutoComida2){
    lcd.clear();
    lcd.setCursor(17,0);
    lcd.print("Dando de comer");
    mypap.step(cantidadDeComida*200);
    delay(500);
  }
}
  
  

  if(digitalRead(boton1) == HIGH){
    lcd.clear();
    lcd.setCursor(17,0);
    lcd.print("Iniciando");
    lcd.setCursor(17,1);
    lcd.print("Configuracion");
    delay(1000);

    //Configurar paso a paso las propiedades
    lcd.clear();
    lcd.setCursor(17,0);
    lcd.print("Numero de comidas");
    lcd.setCursor(17,1);
    while(digitalRead(boton1) != HIGH){
      lcd.print(numeroDeComidas);
      if(digitalRead(boton2) == HIGH){
        if(numeroDeComidas == 2){
          numeroDeComidas = 1;
        } else{
          numeroDeComidas = 2;
        }
        delay(1000);
      }
    }
    lcd.clear();
    lcd.setCursor(17,0);
    if(numeroDeComidas == 2){
      lcd.print("Horas de comidas");
      lcd.setCursor(17,1);
      lcd.print("Hora 1");
      lcd.setCursor(10,1);
      while(digitalRead(boton1) != HIGH){
         lcd.print(horaComida1);
        if(digitalRead(boton2) == HIGH){
         if(horaComida1 <= 23){
          horaComida1++;
         }else{
          horaComida1 = 00;
         }
        }
      }
      delay(500);
      lcd.setCursor(17,1);
      lcd.print("Minuto 1");
      lcd.print(8,1);
      while(digitalRead(boton1) != HIGH){
         lcd.print(minutoComida1);
        if(digitalRead(boton2) == HIGH){
         if(minutoComida1 <= 59){
          minutoComida1++;
         }else{
          minutoComida1 = 00;
         }
        }
      }
      delay(500);
      lcd.setCursor(17,1);
      lcd.print("Hora 2");
      lcd.setCursor(10,1);
      while(digitalRead(boton1) != HIGH){
         lcd.print(horaComida2);
        if(digitalRead(boton2) == HIGH){
         if(horaComida2 <= 23){
          horaComida2++;
         }else{
          horaComida2 = 00;
         }
        }
      }
      
      delay(500);
      lcd.setCursor(17,1);
      lcd.print("Minuto 2");
      lcd.print(8,1);
      while(digitalRead(boton1) != HIGH){
         lcd.print(minutoComida2);
        if(digitalRead(boton2) == HIGH){
         if(minutoComida2 <= 59){
          minutoComida2++;
         }else{
          minutoComida2 = 00;
         }
        }
      }
      delay(500);
    }else {

    lcd.print("Horas de comidas");
      lcd.setCursor(17,1);
      lcd.print("Hora 1");
      lcd.setCursor(10,1);
      while(digitalRead(boton1) != HIGH){
         lcd.print(horaComida1);
        if(digitalRead(boton2) == HIGH){
         if(horaComida1 <= 23){
          horaComida1++;
         }else{
          horaComida1 = 00;
         }
        }
      }
      delay(500);
      lcd.setCursor(17,1);
      lcd.print("Minuto 1");
      lcd.print(8,1);
      while(digitalRead(boton1) != HIGH){
         lcd.print(minutoComida1);
        if(digitalRead(boton2) == HIGH){
         if(minutoComida1 <= 59){
          minutoComida1++;
         }else{
          minutoComida1 = 00;
         }
        }
      }
      delay(500);
    
  }
  
 }

 
 
 }
