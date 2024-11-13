/*************************************************************************************************
  ESP32 Web Server
  Ejemplo de creación de Web server 
  Basándose en los ejemplos de: 
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://electropeak.com/learn
**************************************************************************************************/
//************************************************************************************************
// Librerías
//************************************************************************************************
#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>
//************************************************************************************************
// Variables globales
//************************************************************************************************
// SSID & Password
/*const char* ssid = "iPhone122";  // Enter your SSID here usar internet de mi casa :(
const char* password = "qwerty123";  //Enter your Password here*/

const char* ssid = "hola";  
const char* password = "juanitoxx";  

/*const char* ssid = "CLARO1_9FBF95";  
const char* password = "L70FXWTOBQ"; */ 

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

#define I2C_ADDRESS 0x08
#define PIN 4
#define NUMPIXELS 36

String c = "";
//Cada variable representa el estado de un sensor 
bool S1 = LOW; 
bool S2 = LOW;
bool S3 = LOW; 
bool S4 = LOW; 
bool S5 = LOW; 
bool S6 = LOW;  
bool S7 = LOW; 
bool S8 = LOW; 

// Variables para almacenar el estado anterior de los sensores
bool prevS1 = LOW;
bool prevS2 = LOW;
bool prevS3 = LOW;
bool prevS4 = LOW;
bool prevS5 = LOW;
bool prevS6 = LOW;
bool prevS7 = LOW;
bool prevS8 = LOW;


Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB +NEO_KHZ400);
//************************************************************************************************
// Configuración
//************************************************************************************************
void setup() {
  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);


  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_OnConnect); // Directamente desde e.g. 192.168.0.8

  
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);

  Wire.setClock(100000);
  Wire.begin(I2C_ADDRESS);  // Inicia el I2C en modo esclavo con la dirección especificada
  Wire.onReceive(receiveEvent);  // Asigna la función de recepción de datos

//Neopixles

  pixels.begin();
  pixels.clear(); 
  pixels.setBrightness(255);
  pixels.setPixelColor(0, pixels.Color(0,255,0)); 
  pixels.show();  
  pixels.setBrightness(255);
  pixels.setPixelColor(3, pixels.Color(0,255,0)); 
  pixels.show(); 
  pixels.setBrightness(255);
  pixels.setPixelColor(6, pixels.Color(0,255,0)); 
  
  pixels.setBrightness(255);
  pixels.setPixelColor(9, pixels.Color(0,255,0)); 
  pixels.show();  
  pixels.setBrightness(255);
  pixels.setPixelColor(27, pixels.Color(0,255,0)); 
  pixels.show(); 
  pixels.setBrightness(255);
  pixels.setPixelColor(30, pixels.Color(0,255,0)); 
  
  pixels.setBrightness(255);
  pixels.setPixelColor(33, pixels.Color(0,255,0)); 
  pixels.show();  
  pixels.setBrightness(255);
  pixels.setPixelColor(36, pixels.Color(0,255,0)); 
  pixels.show(); 

}
//************************************************************************************************
// loop principal
//************************************************************************************************
void loop() {
  server.handleClient();
  
  // Variable que indica si hubo un cambio
  bool cambio = false;

  // Verificación de cambios en los estados de los sensores
  // Verifica si S1 ha cambiado respecto a su valor anterior
  if (S1 != prevS1) {
    prevS1 = S1; // Actualiza prevS1 con el nuevo valor de S1
    cambio = true; // Indica que hubo un cambio
    if(S1 == true){
      pixels.show(); 
      pixels.setBrightness(255);
      pixels.setPixelColor(0, pixels.Color(255,0,0)); //Rojo
    }else if(S1 == false){
      pixels.setBrightness(255);
      pixels.setPixelColor(0, pixels.Color(0,255,0)); //Verde
      pixels.show(); 
    }
  }

  // Verifica si S2 ha cambiado respecto a su valor anterior
  if (S2 != prevS2) { 
      prevS2 = S2; // Actualiza prevS2 con el nuevo valor de S2
      cambio = true; // Indica que hubo un cambio
      if(S2 == true){
        pixels.show(); 
        pixels.setBrightness(255);
        pixels.setPixelColor(3, pixels.Color(255,0,0)); //Rojo
      }else if(S2 == false){
        pixels.setBrightness(255);
        pixels.setPixelColor(3, pixels.Color(0,255,0)); //Verde
        pixels.show(); 
      }
  }
  
  // Verifica si S3 ha cambiado respecto a su valor anterior
  if (S3 != prevS3) { 
      prevS3 = S3; // Actualiza prevS3 con el nuevo valor de S3
      cambio = true; // Indica que hubo un cambio
      if(S3 == true){
        pixels.show(); 
        pixels.setBrightness(255);
        pixels.setPixelColor(6, pixels.Color(255,0,0)); //Rojo
      }else if(S3 == false){
        pixels.setBrightness(255);
        pixels.setPixelColor(6, pixels.Color(0,255,0)); //Verde
        pixels.show(); 
      }
  }
  
  // Verifica si S4 ha cambiado respecto a su valor anterior
  if (S4 != prevS4) { 
      prevS4 = S4; // Actualiza prevS4 con el nuevo valor de S4
      cambio = true; // Indica que hubo un cambio
      if(S4 == true){
        pixels.show(); 
        pixels.setBrightness(255);
        pixels.setPixelColor(9, pixels.Color(255,0,0)); //Rojo
      }else if(S4 == false){
        pixels.setBrightness(255);
        pixels.setPixelColor(9, pixels.Color(0,255,0)); //Verde
        pixels.show(); 
      }
  }
  
  // Verifica si S5 ha cambiado respecto a su valor anterior
  if (S5 != prevS5) { 
      prevS5 = S5; // Actualiza prevS5 con el nuevo valor de S5
      cambio = true; // Indica que hubo un cambio
      if(S5 == true){
        pixels.show(); 
        pixels.setBrightness(255);
        pixels.setPixelColor(27, pixels.Color(255,0,0)); //Rojo
      }else if(S5 == false){
        pixels.setBrightness(255);
        pixels.setPixelColor(27, pixels.Color(0,255,0)); //Verde
        pixels.show(); 
      }
  }
  
  // Verifica si S6 ha cambiado respecto a su valor anterior
  if (S6 != prevS6) { 
      prevS6 = S6; // Actualiza prevS6 con el nuevo valor de S6
      cambio = true; // Indica que hubo un cambio
      if(S6 == true){
        pixels.show(); 
        pixels.setBrightness(255);
        pixels.setPixelColor(30, pixels.Color(255,0,0)); //Rojo
      }else if(S6 == false){
        pixels.setBrightness(255);
        pixels.setPixelColor(30, pixels.Color(0,255,0)); //Verde
        pixels.show(); 
      }
  }
  
  // Verifica si S7 ha cambiado respecto a su valor anterior
  if (S7 != prevS7) { 
      prevS7 = S7; // Actualiza prevS7 con el nuevo valor de S7
      cambio = true; // Indica que hubo un cambio
      if(S7 == true){
        pixels.show(); 
        pixels.setBrightness(255);
        pixels.setPixelColor(33, pixels.Color(255,0,0)); //Rojo
      }else if(S7 == false){
        pixels.setBrightness(255);
        pixels.setPixelColor(33, pixels.Color(0,255,0)); //Verde
        pixels.show(); 
      }
  }
  
  // Verifica si S8 ha cambiado respecto a su valor anterior
  if (S8 != prevS8) { 
      prevS8 = S8; // Actualiza prevS8 con el nuevo valor de S8
      cambio = true; // Indica que hubo un cambio
      if(S8 == true){
        pixels.show(); 
        pixels.setBrightness(255);
        pixels.setPixelColor(36, pixels.Color(255,0,0)); //Rojo
      }else if(S8 == false){
        pixels.setBrightness(255);
        pixels.setPixelColor(36, pixels.Color(0,255,0)); //Verde
        pixels.show(); 
      }
  }


  // Si hubo algún cambio, envía los datos al servidor
  if (cambio) {
    server.send(200, "text/html", SendHTML(S1, S2, S3, S4, S5, S6, S7, S8));
  }

}
//************************************************************************************************
// Handler de Inicio página
//************************************************************************************************
void handle_OnConnect() {

  server.send(200, "text/html", SendHTML(S1,S2,S3,S4,S5,S6,S7,S8));
}

//************************************************************************************************
// Procesador de HTML
//************************************************************************************************
String SendHTML(uint8_t stateS1,uint8_t stateS2, uint8_t stateS3, uint8_t stateS4, uint8_t stateS5, uint8_t stateS6, uint8_t stateS7, uint8_t stateS8){ //S1, S2, S3, S4, S5, S6, S7, S8
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head>\n";
  ptr +="<meta name=viewport content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<link rel=stylesheet href=https://stackpath.bootstrapcdn.com/bootstrap/4.5.0/css/bootstrap.min.css integrity=sha384-9aIt2nRpC12Uk9gS9baDl411NQApFmC26EwAOH8WgZl5MYYxFfc+NcPb1dKGj7Sk crossorigin=anonymous>\n";
  ptr +="<link href=\"https://fonts.googleapis.com/css2?family=Lobster&display=swap\" rel=stylesheet>\n";
  ptr +="<style>html{font-family:Helvetica;display:inline-block;margin:0 auto;text-align:center}h1{font-family:'Poppins',sans-serif;display:block;font-size:2em;margin-top:.67em;margin-bottom:.67em;margin-left:0;margin-right:0;font-weight:bold}h2{font-family:'Lobster',cursive;color:#111010;margin-bottom:50px}body{background-color:#ffa600a0;margin-top:50px;font-family:Arial,sans-serif}.parqueo-container{display:flex;flex-wrap:wrap;gap:20px;justify-content:center;margin-top:20px}.parqueo{width:100px;height:100px;display:flex;align-items:center;justify-content:center;font-weight:bold;color:white;font-size:1.2em;border-radius:10px}.disponible{background:linear-gradient(to bottom right,#34eb77,#0fa52d)}.no-disponible{background:linear-gradient(to bottom right,#eb3434,#a50f0f)}</style>\n";
  ptr +="<meta charset=UTF-8>\n";
  ptr +="<meta name=viewport content=\"width=device-width, initial-scale=1.0\">\n";
  ptr +="<title>Document</title>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<img class=imagen-garaje src=https://i.imgur.com/TqFhB7U.jpeg alt=\"Garaje vacío\"width=1600 height=auto>\n";
  ptr +="<h1 style=text-align:center>SmartPark</h1>\n";
  ptr +="<h2>Disponibilidad</h2>\n";
  ptr +="<div class=parqueo-container>\n";


  
  if(stateS1)
  {ptr +="<div class=\"parqueo no-disponible\">No Disponible</div>\n";}
  else
  {ptr +="<div class=\"parqueo disponible\"> Disponible</div>\n";}
  if(stateS2)
  {ptr +="<div class=\"parqueo no-disponible\">No Disponible</div>\n";}
  else 
  {ptr +="<div class=\"parqueo disponible\">Disponible</div>\n";}
  if(stateS3)
  {ptr +="<div class=\"parqueo no-disponible\">No Disponible</div>\n";}
  else 
  {ptr +="<div class=\"parqueo disponible\">Disponible</div>\n";}
  if(stateS4)
  {ptr +="<div class=\"parqueo no-disponible\">No Disponible</div>\n";}
  else 
  {ptr +="<div class=\"parqueo disponible\">Disponible</div>\n";}
  if(stateS5)
  {ptr +="<div class=\"parqueo no-disponible\">No Disponible</div>\n";}
  else 
  {ptr +="<div class=\"parqueo disponible\">Disponible</div>\n";}
  if(stateS6)
  {ptr +="<div class=\"parqueo no-disponible\">No Disponible</div>\n";}
  else 
  {ptr +="<div class=\"parqueo disponible\">Disponible</div>\n";}
  if(stateS7)
  {ptr +="<div class=\"parqueo no-disponible\">No Disponible</div>\n";}
  else 
  {ptr +="<div class=\"parqueo disponible\">Disponible</div>\n";}
  if(stateS8)
  {ptr +="<div class=\"parqueo no-disponible\">No Disponible</div>\n";}
  else 
  {ptr +="<div class=\"parqueo disponible\">Disponible</div>\n";}

  // Cantidad total de parqueos
  const uint8_t totalParqueos = 8;

  // Cálculo de parqueos no disponibles y disponibles
  uint8_t noDisponible = stateS1 + stateS2 + stateS3 + stateS4 + stateS5 + stateS6 + stateS7 + stateS8;
  uint8_t disponible = totalParqueos - noDisponible;
  
  ptr +="</div>\n";
  ptr +="<script src=https://cdn.jsdelivr.net/npm/chart.js></script>\n";
  ptr +="<canvas id=parqueosChart width=300 height=300></canvas>\n";
  //ptr +="<script>const ctx=document.getElementById(\"parqueosChart\").getContext(\"2d\");const parqueosChart=new Chart(ctx,{type:\"doughnut\",data:{labels:[\"Disponible\",\"No Disponible\"],datasets:[{label:\"Disponibilidad de Parqueos\",data:[5,3],backgroundColor:[\"#34eb77\",\"#eb3434\"],borderWidth:1}]},options:{responsive:true,plugins:{legend:{position:\"top\"},tooltip:{callbacks:{label:function(a){return a.label+\": \"+a.raw}}}}}});</script>\n";
  ptr += "<script>const ctx=document.getElementById(\"parqueosChart\").getContext(\"2d\");const parqueosChart=new Chart(ctx,{type:\"doughnut\",data:{labels:[\"Disponible\",\"No Disponible\"],datasets:[{label:\"Disponibilidad de Parqueos\",data:[" + String(disponible) + "," + String(noDisponible) + "],backgroundColor:[\"#34eb77\",\"#eb3434\"],borderWidth:1}]},options:{responsive:true,plugins:{legend:{position:\"top\"},tooltip:{callbacks:{label:function(a){return a.label+\": \"+a.raw}}}}}});</script>\n";

  
  ptr +="<script type=text/javascript>setTimeout(function(){location.reload()},5000);</script>\n";
  ptr +="</body>\n";
  ptr +="</html>"; 
  return ptr; 
}
//************************************************************************************************
// Handler de not found
//************************************************************************************************
void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}


//************************************************************************************************
// Rutina Esp32
//************************************************************************************************
void receiveEvent(int numBytes) {
  /*Serial.print("Datos recibidos: ");
  while (Wire.available()) {
    c = Wire.read();  // Lee un byte de datos y lo guarda en la variable 'c'
    Serial.print(c);  // Muestra el carácter recibido
    Serial.println();*/
    c = "";  // Limpia el contenido previo de c

    for (int i = 0; i < numBytes; i++) {
      char receivedChar = Wire.read();  // Lee un byte de datos
      c += receivedChar;  // Agrega el carácter a la cadena c
    }

    /*Serial.print("Datos recibidos: ");
    Serial.println(c);*/

    // Comprueba si el carácter es 'A' y asigna el valor correspondiente a S1
    if (c == "A") {
      S1 = true;
      //pixels.show(); 
      //pixels.setBrightness(255);
      //pixels.setPixelColor(0, pixels.Color(255,0,0)); //Rojo
    } else if (c == "a"){
      S1 = false;
      //pixels.setBrightness(255);
      //pixels.setPixelColor(0, pixels.Color(0,255,0)); //Verde
      //pixels.show(); 
    }
    if (c == "B") {
      S2 = true;
      //pixels.show(); 
      //pixels.setBrightness(255);
      //pixels.setPixelColor(3, pixels.Color(255,0,0)); //Rojo
    } else if (c == "b"){
      S2 = false;
     // pixels.setBrightness(255);
      //pixels.setPixelColor(3, pixels.Color(0,255,0)); //Verde
      //pixels.show(); 
    }
    if (c == "C") {
      S3 = true;
      //pixels.show(); 
      //pixels.setBrightness(255);
      //pixels.setPixelColor(6, pixels.Color(255,0,0)); //Rojo
      
    } else if (c == "c"){
      S3 = false;
      //pixels.setBrightness(255);
      //pixels.setPixelColor(6, pixels.Color(0,255,0)); //Verde
      //pixels.show();
    }
    if (c == "D") {
      S4 = true;
      //pixels.show(); 
      //pixels.setBrightness(255);
      //pixels.setPixelColor(9, pixels.Color(255,0,0)); //Rojo
    } else if (c == "d"){
      S4 = false;
      //pixels.setBrightness(255);
      //pixels.setPixelColor(9, pixels.Color(0,255,0)); //Verde
      //pixels.show();
    }
    if (c == "E") {
      S5 = true;
      //pixels.show(); 
      //pixels.setBrightness(255);
      //pixels.setPixelColor(27, pixels.Color(255,0,0)); //Rojo 
    } else if (c == "e"){
      S5 = false;
      //pixels.setBrightness(255);
      //pixels.setPixelColor(27, pixels.Color(0,255,0)); //Verde
      //pixels.show();
    }
    if (c == "F") {
      S6 = true;
      //pixels.show(); 
      //pixels.setBrightness(255);
      //pixels.setPixelColor(30, pixels.Color(255,0,0)); //Rojo
    } else if (c == "f"){
      S6 = false;
      //pixels.setBrightness(255);
      //pixels.setPixelColor(30, pixels.Color(0,255,0)); //Verde
      //pixels.show();
    }
    if (c == "G") {
      S7 = true;
      //pixels.show(); 
      //pixels.setBrightness(255);
      //pixels.setPixelColor(33, pixels.Color(255,0,0)); //Rojo
    } else if (c == "g"){
      S7 = false; 
      //pixels.setBrightness(255);
      //pixels.setPixelColor(33, pixels.Color(0,255,0)); //Verde
      //pixels.show(); 
    }
    if (c == "H") {
      S8 = true;
      //pixels.setPixelColor(36, pixels.Color(255,0,0)); //Rojo
    } else if (c == "h"){
      S8 = false;
      //pixels.setPixelColor(36, pixels.Color(0,255,0)); //Verde
    }
    


    delay(100); 

  
}
