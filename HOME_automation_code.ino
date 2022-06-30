#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);

#define Relay4 D1
#define Relay2 D2
#define Relay1 D4

void setup() 
{
  //Setup code here, to run once:
  Serial.begin(9600);
  WiFi.softAP("Team24_Home_automation", "123456789");
  Serial.println();
  Serial.println("NodeMCU has started.....");
  Serial.println(WiFi.softAPIP());
  server.begin();
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay4, OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  client = server.available();  //Gets a client that is connected to the server and has data available for reading.                                                                   
  
  if (client == 1)
  {  
    String request =  client.readStringUntil('\n');
    Serial.println(request);
    request.trim();
    if(request == "GET /ledon HTTP/1.1")
    {
      digitalWrite(Relay1, HIGH);
    }
    if(request == "GET /ledoff HTTP/1.1")
    {
      digitalWrite(Relay1, LOW);
    }
    if(request == "GET /fanon HTTP/1.1")
    {
      digitalWrite(Relay2, HIGH);
    }
    if(request == "GET /fanoff HTTP/1.1")
    {
      digitalWrite(Relay2, LOW);
    }
    if(request == "GET /relayon HTTP/1.1")
    {
      digitalWrite(Relay4, HIGH);
    }
    if(request == "GET /relayoff HTTP/1.1")
    {
      digitalWrite(Relay4, LOW);
    }
  }
  client.println("HTTP/1.1 200 OK");//
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1>WELCOME     TO     YOUR   HOME AUTOMATION PAGE :)</h1>");
  client.println("");
  client.println("<h3> DEVICE CONTROLS :<h3>");
  client.println("<br>");
  client.println("<a href=\"/ledoff\"\"><button>LED ON</button></a>");
  client.println("<a href=\"/ledon\"\"><button>LED OFF</button></a><br/>");
  client.println("");
  client.println("<a href=\"/fanoff\"\"><button>FAN ON</button></a>");
  client.println("<a href=\"/fanon\"\"><button>FAN OFF</button></a><br/>");
  client.println("");
  client.println("<a href=\"/relayoff\"\"><button>BG ON</button></a>");
  client.println("<a href=\"/relayon\"\"><button>BG OFF</button></a><br/>");
  client.println("</html>");
}
