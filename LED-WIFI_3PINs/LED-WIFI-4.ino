// (No copyright)  SLG Robotics V09/20

#include <WiFi.h>
const char* ssid = "WIFII-2";
const char* mot_de_passe = "3rpz9xnr";
String entete;

// PIN xx -
String etat_LED_BLANCHE = "eteint";
const int LED_BLANCHE = 14;
// - fin PIN xx

// PIN xx -
String etat_LED_rouge = "eteint";
const int LED_rouge = 2;
// - fin PIN xx


// PIN xx -
String etat_TESTPIN = "eteint";
const int TESTPIN = 15;
// - fin PIN xx


WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println("Tentative de rejoindre le réseau...");
  WiFi.begin(ssid, mot_de_passe);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("connexion au réseau réussie...!");
  Serial.println(WiFi.localIP());
  server.begin();

// PIN xx -
  pinMode(LED_BLANCHE, OUTPUT);
// - fin PIN xx

//PIN xx -
  pinMode(LED_rouge, OUTPUT);
// - fin PIN xx


//PIN TEST -
  pinMode(TESTPIN, OUTPUT);
// - fin PIN TEST


}

void loop() {

  WiFiClient client = server.available();
  if (client) {
    Serial.println("Nouveau client Web");
    String ligne = "";

    while (client.connected())
    { Serial.println("client connecté !");
      if (client.available())
      { char c = client.read();
        Serial.write(c); entete += c;
        if (c == '\n')
        { if (ligne.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

// PIN xx -
            if (entete.indexOf("GET /10/allume") >= 0) {
              Serial.println("LED_BLANCHE allumée"); etat_LED_BLANCHE = "allume";
              digitalWrite(LED_BLANCHE, HIGH);
            }
            if (entete.indexOf("GET /10/eteint") >= 0) {
              Serial.println("LED_BLANCHE éteinte"); etat_LED_BLANCHE = "eteint";
              digitalWrite(LED_BLANCHE, LOW);
            }
// - fin PIN xx

// PIN xx -
            if (entete.indexOf("GET /20/allume") >= 0) {
              Serial.println("LED rouge allumée"); etat_LED_rouge = "allume";
              digitalWrite(LED_rouge, HIGH);
            }

            if (entete.indexOf("GET /20/eteint") >= 0) {
              Serial.println("LED rouge éteinte"); etat_LED_rouge = "eteint";
              digitalWrite(LED_rouge, LOW);
            }
// - fin PIN xx


// PIN TEST -
            if (entete.indexOf("GET /30/allume") >= 0) {
              Serial.println("TESTPIN allumée"); etat_TESTPIN = "allume";
              digitalWrite(TESTPIN, HIGH);
            }

            if (entete.indexOf("GET /30/eteint") >= 0) {
              Serial.println("TESTPIN éteinte"); etat_TESTPIN = "eteint";
              digitalWrite(TESTPIN, LOW);
            }
// - fin PIN TEST



            client.println("<!DOCTYPE html><html>");
            client.print("<head><meta name=\"viewport\" content=\"width=device-width, ");
            client.println("initial-scale=1\">");

            client.println("<link rel=\"icon\" href=\"data:,\">");

            client.print("<style>html { font-family: Helvetica; display: inline-block; ");
            client.println("margin: 0px auto; text-align: center;}");

            client.print(".button { background-color: #299886; border: none; ");
            client.println("color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");

            client.print(".button20 { background-color: #d35845; border: none; color: white; ");
            client.println("padding: 16px 40px;");

            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button3 {background-color: #f2b2a8;}");
            client.println(".button35 {background-color: #aab1c1;}");
            client.println(".button30 {background-color: #1d69bf;}");
            client.println(".button10 {background-color: #82d9cb;}</style></head>");

            client.println("<body><h1>Server web ESP32 v3.2</h1>");


// PIN xx -
            client.println("<p>LED blanche - Etat " + etat_LED_BLANCHE + "</p>");
            if (etat_LED_BLANCHE == "eteint") {
              client.println("<p><a href=\"/10/allume\"><button class=\"button\">Allumer</button></a></p>");
            } else {
              client.print("<p><a href=\"/10/eteint\"><button class=\"button button10\">Eteindre");
              client.println("</button></a></p>");
            }
// - fin PIN xx

// PIN xx -
            client.println("<p>LED rouge - Etat " + etat_LED_rouge + "</p>");
            if (etat_LED_rouge == "eteint") {
              client.print("<p><a href=\"/20/allume\"><button class=\"button button20\">Allumer");
              client.println("</button></a></p>");
            } else {
              client.print("<p><a href=\"/20/eteint\"><button class=\"button button3\">Eteindre");
              client.println("</button></a></p>");
            }
// - fin PIN xx


// PIN TEST -
            client.println("<p>LED Bleu - Etat " + etat_TESTPIN + "</p>");
            if (etat_TESTPIN == "eteint") {
              client.print("<p><a href=\"/30/allume\"><button class=\"button button30\">Allumer");
              client.println("</button></a></p>");
            } else {
              client.print("<p><a href=\"/30/eteint\"><button class=\"button button35\">Eteindre");
              client.println("</button></a></p>");
            }
// - fin PIN TEST



            client.println("</body></html>");

            client.println(); break;
          } else {
            ligne = "";
          }
        }
        else if (c != '\r') {
          ligne += c;
        }
      }
    }


    entete = "";
    client.stop();
    Serial.println("Client Web déconnecté !");
    Serial.println("");
  }
}
