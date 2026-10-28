#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char* ssid = "NOMBRE_WIFI";
const char* password = "CONTRASEÑA";
WebServer server(80);

//==============================
// Pantalla LCD 16x2 I2C
//==============================
LiquidCrystal_I2C lcd(0x27, 16, 2);

//==============================
// Sensor DS18B20
//==============================
#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

//==============================
// Definición de pines
//==============================
#define REED_PIN    18
#define BUZZER_PIN  19

//==============================
// Variables
//==============================
float temperatura = 0.0;

bool puertaAbierta = false;
bool alarmaPuerta = false;
bool alarmaTemperatura = false;

unsigned long tiempoPuerta = 0;
bool contandoTiempo = false;
// Variables del buzzer
bool estadoBuzzer = false;
unsigned long tiempoBuzzer = 0;
const unsigned long INTERVALO_BUZZER = 500;

// Temperatura máxima permitida
const float TEMP_MAXIMA = 8.0;

// Tiempo de puerta abierta (1 minuto)
const unsigned long TIEMPO_ALARMA = 60000;

//==============================
// SETUP
//==============================
void setup()
{
  Serial.begin(115200);
  lcd.init();
lcd.backlight();
    //==============================
  // Conexión Wi-Fi
  //==============================

  WiFi.begin(ssid, password);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectando WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);

    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi conectado");

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi: Conectado");

  delay(2000);
  
  // Inicializar sensor
  sensors.begin();

  // Configurar pines
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(BUZZER_PIN, OUTPUT);

  // Apagar buzzer
  digitalWrite(BUZZER_PIN, LOW);

  // Pantalla de inicio
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("FRIGORIFICO");

  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");

  delay(3000);

  lcd.clear();
  //==============================
// Página de prueba para la App
//==============================

server.on("/datos", []()
{
  String datos = "";

  datos += "TEMP=";
  datos += String(temperatura, 1);
  datos += ";";

  datos += "PUERTA=";

  if (puertaAbierta)
    datos += "ABIERTA";
  else
    datos += "CERRADA";

  datos += ";";

  datos += "ALARMA=";

  if (temperatura > TEMP_MAXIMA)
    datos += "TEMPERATURA";
  else if (contandoTiempo && millis() - tiempoPuerta >= TIEMPO_ALARMA)
    datos += "PUERTA";
  else
    datos += "NINGUNA";

  server.send(200, "text/plain", datos);
});
server.begin();

Serial.println("Servidor iniciado");
}

//==============================
// LOOP PRINCIPAL
//==============================
void loop()
{
  server.handleClient();
  // Leer temperatura
  sensors.requestTemperatures();
  temperatura = sensors.getTempCByIndex(0);

  // Leer estado de la puerta
  puertaAbierta = digitalRead(REED_PIN);
  //==============================
// Temporizador de puerta abierta
//==============================

if (puertaAbierta)
{
  if (!contandoTiempo)
  {
    tiempoPuerta = millis();
    contandoTiempo = true;
  }
}
else
{
  contandoTiempo = false;
  tiempoPuerta = 0;
}
  // Mostrar temperatura
 lcd.setCursor(0,0);
lcd.print("TEMP: ");
lcd.print(temperatura,1);
lcd.print((char)223);
lcd.print("C   ");
  // Mostrar estado de la puerta
  lcd.setCursor(0, 1);

  if (puertaAbierta)
  {
    lcd.print("Puerta:Abierta ");
  }
  else
  {
    lcd.print("Puerta:Cerrada");
  }
//-------------------------
 //==============================
// Alarma por temperatura
//==============================

if (temperatura > TEMP_MAXIMA || (contandoTiempo && millis() - tiempoPuerta >= TIEMPO_ALARMA))
{
  if (millis() - tiempoBuzzer >= INTERVALO_BUZZER)
{
  tiempoBuzzer = millis();

  estadoBuzzer = !estadoBuzzer;

  digitalWrite(BUZZER_PIN, estadoBuzzer);
}

 lcd.setCursor(0,1);

if (temperatura > TEMP_MAXIMA)
{
  lcd.print("TEMP > 8C      ");
}
else
{
  lcd.print("PUERTA >1 MIN  ");
}
}
else
{
  digitalWrite(BUZZER_PIN, LOW);
estadoBuzzer = false;

  if (puertaAbierta)
    lcd.print("Puerta:Abierta ");
  else
    lcd.print("Puerta:Cerrada ");
}

//==============================
// Monitor Serie
//==============================

Serial.print("Temperatura: ");
Serial.print(temperatura);
Serial.print(" C  ");

Serial.print("Puerta: ");

if (puertaAbierta)
  Serial.print("Abierta");
else
  Serial.print("Cerrada");

if (temperatura > TEMP_MAXIMA)
  Serial.print("  | ALARMA: TEMP ALTA");

Serial.println();

delay(1000);
}