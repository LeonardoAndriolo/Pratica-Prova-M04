#include <WiFi.h>
// #include <HTTPClient.h>

// #define led_azul 9   // Pino led azul
#define led_verde 41    // Pino led verde
#define led_vermelho 40 // Pino led vermelho
#define led_amarelo 9   // Pino led amarelo

#define buttonPin 35     // Pino botão
bool buttonState = HIGH;   // Estado do botão
long lastDebounceTime = 0;


#define ldrPin 10        // Pino sensor LDR
int threshold = 600;     // Limiar do LDR

void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  // pinMode(led_azul,OUTPUT);
  pinMode(led_verde,OUTPUT);
  pinMode(led_vermelho,OUTPUT);
  pinMode(led_amarelo,OUTPUT);

  // Inicialização das entradas
  pinMode(buttonPin, INPUT_PULLDOWN);

  // digitalWrite(led_azul, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);
  digitalWrite(led_amarelo, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600

  // WiFi.begin("Wokwi-GUEST", ""); // Conexão à rede WiFi aberta com SSID Wokwi-GUEST

  // while (WiFi.status() != WL_CONNECT_FAILED) {
  //   delay(100);
  //   Serial.print(".");
  // }
  // Serial.println("Conectado ao WiFi com sucesso!"); // Considerando que saiu do loop acima, o ESP32 agora está conectado ao WiFi (outra opção é colocar este comando dentro do if abaixo)

  // Verifica estado do botão
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }

  // if(WiFi.status() == WL_CONNECTED){ // Se o ESP32 estiver conectado à Internet
  //   HTTPClient http;

  //   String serverPath = "http://www.google.com.br/"; // Endpoint da requisição HTTP

  //   http.begin(serverPath.c_str());

  //   int httpResponseCode = http.GET(); // Código do Resultado da Requisição HTTP

  //   if (httpResponseCode>0) {
  //     Serial.print("Resposta HTTP: ");
  //     Serial.println(httpResponseCode);
  //     String payload = http.getString();
  //     Serial.println(payload);
  //     }
  //   else {
  //     Serial.print("Código de erro: ");
  //     Serial.println(httpResponseCode);
  //     }
  //     http.end();
  //   }

  // else {
  //   Serial.println("WiFi Desconectado");
  // }
}

void loop() {
  int ldrstatus = analogRead(ldrPin);

  // Verifica estado do botão
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("Botão pressionado!");
  } else {
    Serial.println("Botão não pressionado!");
  }

  // Modo Noturno
  if(ldrstatus >= threshold){
    Serial.print("Escuro. Ligar LED.");
    Serial.println(ldrstatus);
    digitalWrite(led_amarelo, HIGH);
    delay(2000);
    digitalWrite(led_amarelo, LOW);
    delay(2000);

  // Modo Normal
  }else{
    Serial.print("Claro. Desligar LED.");
    Serial.println(ldrstatus);
    digitalWrite(led_verde, HIGH);
    delay(3000);
    digitalWrite(led_verde, LOW);
    digitalWrite(led_amarelo, HIGH);
    delay(2000);
    digitalWrite(led_amarelo, LOW);
    digitalWrite(led_vermelho, HIGH);
    delay(5000);
    digitalWrite(led_vermelho, LOW);

    // Debounce do botão
    if ( (millis() - lastDebounceTime) > 50) {
      if ( (buttonState == HIGH) && (led_vermelho == HIGH) ) {
        delay(1000);
        digitalWrite(led_vermelho, LOW);
        digitalWrite(led_verde, HIGH);
        delay(3000);
        digitalWrite(led_verde, LOW);
        lastDebounceTime = millis();
      }
      else {
        lastDebounceTime = millis();
      }
    }
  }
  // delay(1000);
} 
