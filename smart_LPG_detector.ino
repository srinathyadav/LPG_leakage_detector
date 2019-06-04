/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP8266     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <ESP8266WiFi.h>
#include <Servo.h> 
WiFiClient client;
int relayInput =2;
Servo servo_1;
String MakerIFTTT_Key ;
String MakerIFTTT_Event;
char *append_str(char *here, String s) {  int i=0; while (*here++ = s[i]){i++;};return here-1;}
char *append_ul(char *here, unsigned long u) { char buf[20]; return append_str(here, ultoa(u, buf, 10));}
char post_rqst[256];char *p;char *content_length_here;char *json_start;int compi;

int Gas_pin = D2; 



void setup()
{
  
  Serial.begin(115200);
  WiFi.disconnect();
  delay(3000);
  Serial.println("Start");
   WiFi.begin("Adarsh","adarsh68");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);

  }
  pinMode(Gas_pin,INPUT);
   servo_1.attach(0);
  pinMode(relayInput,OUTPUT);

  Serial.println(".................");
  Serial.println("connected");
  
}


void loop()
{
 int Gas_state = digitalRead(Gas_pin);
 
   if (Gas_state == LOW)
   {
    digitalWrite(relayInput,HIGH);
  servo_1.write (0);
    if (client.connect("maker.ifttt.com",80)) {
    MakerIFTTT_Key ="n0dSYG0PQfIXJYgUGDtyibavpD6GKULg-tfHj1yoTks";
    MakerIFTTT_Event ="sms"
    ;
    p = post_rqst;
    p = append_str(p, "POST /trigger/");
    p = append_str(p, MakerIFTTT_Event);
    p = append_str(p, "/with/key/");
    p = append_str(p, MakerIFTTT_Key);
    p = append_str(p, " HTTP/1.1\r\n");
    p = append_str(p, "Host: maker.ifttt.com\r\n");
    p = append_str(p, "Content-Type: application/json\r\n");
    p = append_str(p, "Content-Length: ");
    content_length_here = p;
    p = append_str(p, "NN\r\n");
    p = append_str(p, "\r\n");
    json_start = p;
    p = append_str(p, "{\"value1\":\"");
    p = append_str(p, "Nodemcu");
    p = append_str(p, "\",\"value2\":\"");
    p = append_str(p, "Hi Adarsh...Emergency!!!");
    p = append_str(p, "\",\"value3\":\"");
    p = append_str(p, " https://maps.app.goo.gl/HFycXnYwbZAwcURAA");
    p = append_str(p, "\"}");

    compi= strlen(json_start);
    content_length_here[0] = '0' + (compi/10);
    content_length_here[1] = '0' + (compi%10);
    client.print(post_rqst);

  }
  delay(2000);
  Serial.println("Alert Adarsh Emergency");
  Serial.println("Gas leakage is detected");
  
  
  delay(1000);
  }

   else 
   {
    Serial.println("No gas");
    digitalWrite(relayInput, LOW);
    servo_1.write (180);  
   }
}
