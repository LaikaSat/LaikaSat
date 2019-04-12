/*
 **********************************************************
 *
 *                   Codigo CANSAT 
 *                       v1.0
 * 
 * Este codigo lee cada sensor y copia los valores leidos
 * a la estructura tipo DATA que enviaremos a traves del
 * APC220 en cada ciclo. Tambien copia los datos en el
 * mismo formato a la tarjeta SD.
 *
 *
 * PINES:
 * -MOSI de la SD: MOSI
 * -MISO de la SD: MOSI
 * -SCK de la SD: SCK
 * -CS de la SD: digital 5
 * -SCL del BMP280: digital 3
 * -SDA del BMP280: digital2
 * -PIN central de DHT11: digital 6
 * -RX del APC220: TX del arduino.
 * -TX del APC220: RX del arduino.
 * -RX del GPS: digital 10
 * -TX del GPS: digital 11
 * 
 **********************************************************
 */
 
#include <TinyGPS++.h>
#include <Adafruit_BMP280.h>
#include <SoftwareSerial.h>
#include <dht.h>
#include <SD.h>

#define BPS 9600 // Bits por segundo del serial
#define CS_PIN  5 // Pin CS de la SD
#define PIN_DHT  6 // Pin central del DHT11
#define RETARDO 36 // Retardo entre cada iteracion (minimo 36)
#define NIVEL_DEL_MAR_PR 101325 // Presion al nivel del mar
#define LOG_FILE "logazo.txt" // Nombre del archivo en la SD

/* Paquete de datos */
typedef struct {
  int temp = 0;     // Temperatura (K)
  uint8_t hum = 0;      // Humedad  (%)
  int alt;      // Altura (m)
  uint32_t pr = 0;       // Presion (Pa)
  uint16_t coordX = 0;   // Latitud
  int coordX_coma = 0; // Coma latitud
  int coordY = 0;   // Longitud
  int coordY_coma = 0; // Coma longitud
  int vel = 0;      // Velocidad (m/s)
}Data;

Adafruit_BMP280 bmp; // Objeto BMP280
dht dht11; // Objeto DHT11
SoftwareSerial serial_connection(10, 11); //Iniciar conexion serial virtual en RX=pin 10, TX=pin 11
TinyGPSPlus gps; // Objeto GPS

Data data; //Paquete de datos
File file; //Archivo para guardar datos en la SD

static const String sp = " "; // String espacio necesario para la construccion de cadenas de texto.

void setup() {
  Serial1.begin(BPS); // Iniciar comunicacion serial a 9600 bps
  serial_connection.begin(9600);  // Esto abre la comunicacion con el GPS
  pinMode(CS_PIN, OUTPUT); //Pin CS de la SD en CS_PIN
  SD.begin(); //Iniciar SD
  bmp.begin(); //Iniciar BMP
}

void loop() {
  leerDHT(&data); //Leer DHT11 (temperatura y humedad)
  leerBMP(&data); //Leer BMP280 (presion)
  leerGPS(&data); //Leer GPS (coordenadas, altura y velocidad)
  transmitir(dataToString(data, 1)); //Transmitir datos por radio (APC220)
  escribirSD(dataToString(data, 0)); //Guardar datos en la SD
  delay(RETARDO);
}

/**
 * Transmite la String por el APC220.
 */
void transmitir(String s) {
  // Los datos se transmiten del siguiente formato:
  // "DATA (Temperatura) (Humedad) (Presion) (Altitud) (Coordenadas X) (Coordenadas Y) (Velocidad) FDATA" 
  Serial1.println(s); //APC220
  //Serial.println(s); //Terminal
}

/**
 * Lee temperatura y presion con el DHT11 y los guarda en el paquete datos.
 */
void leerDHT(Data* datos) {
  dht11.read11(PIN_DHT); // Leemos el sensor.
  if (dht11.temperature != -999 && dht11.humidity != -999) {  // Si los datos obtenidos son correctos, mete los valores leidos por el DHT a los datos
    datos->temp = dht11.temperature - 7 + 273; // -7 por ajuste (el sensor no es muy preciso) y + 273 para pasar a kelvin
    datos->hum = dht11.humidity;
  }
}

/**
 * Lee datos del GPS (coordenadas, altura y velocidad) y los guarda en el paquete datos.
 */
void leerGPS(Data* datos) {
  while(serial_connection.available()) {   // Mientras haya datos por recibir del GPS...
    gps.encode(serial_connection.read());  // Procesamos los datos en NMEA con la libreria del GPS
  }
  if(gps.location.isUpdated()) {           // Si se actualiza el valor...
    datos->coordX = (int)gps.location.lat();    // ... coordenadas x ...
    datos->coordX_coma = (gps.location.lat()*10000)-((uint32_t)gps.location.lat())*10000;
    datos->coordY = (int)gps.location.lng();    // ... coordenadas y ...
    datos->coordY_coma = (gps.location.lng()*-10000)+((int)gps.location.lng())*10000; //Aquí se hace una conversion solo valida para Los Arcos
    datos->vel = gps.speed.mps();          // ... velocidad ...
    datos->alt = gps.altitude.meters();    // ... altitud (media entre gps y bmp280)
  }
}

/**
 * Lee la presion mediante el BMP280 y la guarda en el paquete.
 */
void leerBMP(Data* datos) {
  datos->pr = bmp.readPressure();     // Almacena en variable el valor de presion en Pascales
}

/**
 * Escribe la String en la SD.
 */
void escribirSD(String s){
  file = SD.open(LOG_FILE, FILE_WRITE);
  if (file) file.println(s);
  if (file) file.close();
}

/**
 * Convierte un paquete de datos en un String para enviar (tipo = 1) o para guardar en la SD (tipo = 0).
 */
String dataToString(Data data, bool tipo){
  static const String sp = " ";
  if(tipo) //Para transmitir
    return String("DATA" + sp + data.temp + sp + data.hum + sp + data.pr + sp + data.alt + sp + data.coordX + "." + data.coordX_coma + sp + data.coordY + "." + data.coordY_coma + sp + data.vel + " FDATA");
  else //Para la SD
    return String(data.temp + sp + data.hum + sp + data.pr + sp + data.alt + sp + data.coordX + "." + data.coordX_coma + sp + data.coordY + "." + data.coordY_coma + sp + data.vel);
}
