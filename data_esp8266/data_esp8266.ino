#include <WiFiClient.h>
#include <ESP8266WiFi.h>
//#include <WiFi.h>

WiFiClient Sock_TCP_Client;
const char* SSID = "TP-Link_D5FC";

const char* PASS = "890995755";

const char* host = "54.192.22.61";

uint16_t port = 80;
char data_recv1[4096] = {0};

void setup()
{
  Serial.begin(115200);
  WiFi.begin(SSID, PASS);
  Serial.print("Connect esp \r\n");
  while (!WiFi.isConnected())

  {

    Serial.println("Wifi da ket noi");

    delay(1000);

  }

  Sock_TCP_Client.connect(host, port);

  Serial.printf("Connect to : %s\r\n", host);

  while (!Sock_TCP_Client.connected())

  {

    Serial.println(".");

    delay(1000);

  }
  Serial.println("TCP socket connected");

  // Sock_TCP_Client.println("This is message from ESP8266");
  Sock_TCP_Client.println( "GET /v1/bpi/currentprice.json HTTP/1.1\r\nHost: api.coindesk.com\r\n\r\n");
}
void loop()
{

  String data_recv;
  while (!Sock_TCP_Client.available()) ;

  data_recv = Sock_TCP_Client.readStringUntil(0x0d);
  Serial.println(data_recv);
  data_recv.toCharArray(data_recv1, sizeof(data_recv1));
  const char* Substr = "\"rate_float\":";
  char* Start_Pos = strstr(data_recv1, Substr);
  if (Start_Pos > 0)
  {
    Start_Pos += strlen(Substr);
    char Bitcoin_Gia[20] = { 0 };
    int index = 0;
    while (Start_Pos[index] != '}')
    {
      Bitcoin_Gia[index] = Start_Pos[index];
      index++;
    }
    Serial.printf("\nGia Bitcoin la: %s\r\n", Bitcoin_Gia);
  }


}
