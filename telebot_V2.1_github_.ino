
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266TelegramBOT.h>
#define PIN_TRIG 5
#define PIN_ECHO 4
#define PIN_RELAY 2

int t;

long duration, cm;


// Подключаем пин данных DS18B20 к GPIO 15 на ESP8266

WiFiClientSecure client;
// Initialize Wifi connection to the router
char ssid[] = "*********";        // Имя точки доступа
char password[] = "**********";  // Пароль от точки доступа
int status = 0;


// Initialize Telegram BOT

#define BOTtoken "****************************"  //Токен бота полученного от @BotFather
#define BOTname "Mouse" // Имя бота
#define BOTusername "Mouse135_bot" // Логин бота
TelegramBOT bot(BOTtoken, BOTname, BOTusername);

int Bot_mtbs = 1000; //среднее время между сканированием сообщений
long Bot_lasttime;   //

bool Start = false;



/**************************************************
 * Функция обработки команд ботом от пользователя *
 **************************************************/
void Bot_EchoMessages() {
  for (int i = 1; i < bot.message[0][0].toInt() + 1; i++)      {
    bot.sendMessage(bot.message[i][4], bot.message[i][5], "");
    bot.message[i][5]=bot.message[i][5].substring(1,bot.message[i][5].length());
       
    if (bot.message[i][5] == "start") {
      String wellcome = "Wellcome from FlashLedBot, your personal Bot on ESP8266 board";
      bot.sendMessage(bot.message[i][4], wellcome, "");
      Start = true;
    }
  }
  bot.message[0][0] = "";   // All messages have been replied - reset new messages
}

void setup() {
  
  Serial.begin (9600);
  //delay(3000);

  byte test();
 pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, HIGH);
  
 client.setInsecure();
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
 
  // Подключаемся к Wifi:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  bot.begin();      // Включаем бота
  
}





byte test() {
   

}





void loop() {
// Сначала генерируем короткий импульс длительностью 2-5 микросекунд.
label:

  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);

  // Выставив высокий уровень сигнала, ждем около 10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц.
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  //  Время задержки акустического сигнала на эхолокаторе.
  duration = pulseIn(PIN_ECHO, HIGH);

  // Теперь осталось преобразовать время в расстояние
  cm = (duration / 2) / 29.1;



  delay(50);
int t = (cm);

if ( t > 6) 
{ goto label;  }





if ( t <= 6){
  Bot_lasttime = 0;
       digitalWrite(2, LOW);
      Serial.print("Есть движение ");
      Serial.print(cm);
      Serial.println(" см.");
     

delay(1000);// Время для работы электрошокера
digitalWrite(2, HIGH); 
   }   
delay(50);  
  




if (millis() > Bot_lasttime + Bot_mtbs)  {
    bot.getUpdates(bot.message[0][1]);   // Включаем API и получаем новые сообщения    
    if (t < 10){
   
    bot.sendMessage("881742452", "Возможно поймалась мышь", ""); // Здесь вписываем ID чата с ботом
  }    
    Bot_EchoMessages();   // reply to message with Echo
    Bot_lasttime = millis();
    delay(28800000);// Пауза в коде 8 часов, так как если мертвая мышь будет находится ближе расстояния сработки модуля, он будет постоянно включаться..   
  }



}


  
