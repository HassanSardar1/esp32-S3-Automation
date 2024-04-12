#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Hassan";
const char* password = "marwat0000";

IPAddress staticIP(192, 168, 10, 100);  // Set your desired static IP address
IPAddress gateway(192, 168, 10, 1);
IPAddress subnet(255, 255, 255, 0);
    
WebServer server(80);

int lcd1Pin = 4;   // GPIO pin connected to LCD 1
int lcd2Pin = 5;   // GPIO pin connected to LCD 2
int lcd3Pin = 6;   // GPIO pin connected to LCD 3
int ampPin = 7;    // GPIO pin connected to Amplifier
int chargerPin = 15;// GPIO pin connected to Laptop Charger
int cordPin = 16;   // GPIO pin connected to Extension Cord
int extraPin = 17;  // GPIO pin connected to Extra

void setup() {

    pinMode(lcd1Pin, OUTPUT);
  pinMode(lcd2Pin, OUTPUT);
  pinMode(lcd3Pin, OUTPUT);
    pinMode(ampPin, OUTPUT);
  pinMode(chargerPin, OUTPUT);
  pinMode(cordPin, OUTPUT);
    pinMode(extraPin, OUTPUT);
  Serial.begin(115200);

  // Connect to WiFi with static IP configuration
  WiFi.config(staticIP, gateway, subnet);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");

  // Start web server
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);

  server.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<!DOCTYPE html><html><head>";
  html += "<style>";
  html += "@import url(\"https://fonts.googleapis.com/css2?family=Nunito:wght@200;400;500;700&display=swap\");*,*::after,*::before{box-sizing:border-box;padding:0;margin:0;font-family:\"Nunito\",sans-serif}body{background:#c9cfd4}.mobile{width:320px;height:95vh;background:#1a1a1a;position:absolute;top:2.5%;left:calc((100% - 320px) / 2);border-radius:15px;box-shadow:2px 2px 9px 1px rgba(0,0,0,0.22)}.flex{display:flex;align-items:center;justify-content:space-between}.flex-c{flex-direction:column}.input{display:none}.emoji::after {content:\"\\1F44B\";font-size:1.2em;}.app{width:100%;height:90%;position:relative}.app .page{width:100%;height:100%;position:absolute;top:0;left:0;padding:25px 15px;transition:0.5s linear}p{color:#f1f1f1}.page-1{color:#fff}.profile{height:10%;width:100%;font-size:12px;font-weight:400}.heading{font-size:20px;font-weight:400}.sub-heading{font-size:10px;font-weight:200}.name{width:85%;height:100%}.avatar{width:15%;height:100%;cursor:pointer}.avatar img{width:100%;border-radius:50%}.icon{width:35px;height:35px;background:#2c2c2c;border-radius:50%;justify-content:center;font-size:22px;color:#fff;transition:0.3s linear;cursor:pointer}.icon:hover{color:#e2d606}.rooms h3{font-size:15px;font-weight:200;color:#c9cfd4}.control-pannel{width:100%;height:20rem;display:flex;flex-wrap:wrap;justify-content:space-between}.devices{background:#2c2c2c;width:48%;height:40%;border-radius:8px;padding:15px 10px;text-align:center;margin-bottom:10px}.control-pannel .icon{background:inherit;border-radius:none}.switch{width:100%}.toggle-switch{margin-left:3rem;width:40px;height:20px;border-radius:15px;border:1px solid #c9cfd4;position:relative;transition:0.3s linear}.toggle-switch span{width:15px;height:15px;background:#c9cfd4;position:absolute;border-radius:50%;top:1.5px;left:2px;cursor:pointer}.toggle-input:checked~label .toggle-switch{border-color:#e2d606}.toggle-input:checked~label .toggle-switch span{right:2px;left:unset;background:#fff;transition:0.3s linear}.control-pannel h3{font-size:18px;font-weight:400}.control-pannel h2{font-size:22px;color:#e2d606;font-weight:400}.control-pannel p{font-size:12px;color:#c9cfd4;font-weight:200;margin-top:5px}";
  html += "</style>";
  html += "<script>"
          "function toggleDevice(device) {"
          "  var xhr = new XMLHttpRequest();"
          "  xhr.onreadystatechange = function() {"
          "    if (xhr.readyState === XMLHttpRequest.DONE) {"
          "      if (xhr.status === 200) {"
          "        document.getElementById(device + '-status').innerText = xhr.responseText;"
          "      }"
          "    }"
          "  };"
          "  xhr.open('GET', '/toggle?device=' + device, true);"
          "  xhr.send();"
          "}"
          "</script>";
  html += "</head><body>";
  html += "<div class='mobile'>";
  html += "<div class='app'>";
  html += "<div class='page page-1'>";
  html += "<div class='profile flex'>";
  html += "<div class='name'>";
  html += "<h2 class='emoji heading'>Hey, Hassan </h2>";
  html += "<p class='sub-heading'>Manage your system here!</p>";
  html += "</div>";
  html += "<div class='avatar flex flex-c'>";
  html += "<img src='https://scontent.fisb5-2.fna.fbcdn.net/v/t1.6435-1/122641776_1280253595662382_7262440743655975793_n.jpg?stp=cp0_dst-jpg_p40x40&amp;_nc_cat=109&amp;ccb=1-7&amp;_nc_sid=5f2048&amp;_nc_ohc=6piSvJbiaqcAb4ydsNk&amp;_nc_ht=scontent.fisb5-2.fna&amp;oh=00_AfDbDKHBgWKL7GnyHXeCfEizwyhwmnzdW5lJy8069gYcuQ&amp;oe=663F40AE' style='height: 40px; width: 40px;' alt='avatar'>";
  html += "</div>";
  html += "</div>";
  html += "<div class='controls flex-c'>";
  html += "<div class='control-pannel flex'>";

  // Generate device controls dynamically
  html += generateDeviceControl("LCD Left", lcd1Pin, "desktop");
  html += generateDeviceControl("LCD Middle", lcd2Pin, "desktop");
  html += generateDeviceControl("LCD Right", lcd3Pin, "desktop");
  html += generateDeviceControl("Amplifier", ampPin, "desktop");
  html += generateDeviceControl("Laptop Charger", chargerPin, "desktop");
  html += generateDeviceControl("Extension Cord", cordPin, "desktop");
  html += generateDeviceControl("Extra", extraPin, "desktop");

  html += "</div>"; // End control-pannel
  html += "</div>"; // End controls
  html += "</div>"; // End page-1
  html += "</div>"; // End app
  html += "</div>"; // End mobile
  html += "<script type=\"module\" src=\"https://cdn.jsdelivr.net/npm/@ionic/core/dist/ionic/ionic.esm.js\"></script><script nomodule src=\"https://cdn.jsdelivr.net/npm/@ionic/core/dist/ionic/ionic.js\"></script>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

String generateDeviceControl(const char* deviceName, int pin, const char* icon) {
  String html = "<div class='devices flex'>";
  html += "<div class='control-box flex flex-c'>";
  html += "<div class='switch flex'>";
  html += "<div class='icon flex'>";
  html += "<ion-icon name='"+ String(icon) +"-outline'></ion-icon>";
  html += "</div>";
  html += "<input type='checkbox' class='input toggle-input' id='" + String(deviceName) + "-toggle' onchange='toggleDevice(\"" + String(deviceName) + "\");'";
  html += (digitalRead(pin) ? " checked" : "");
  html += " />";
  html += "<label for='" + String(deviceName) + "-toggle'>";
  html += "<div class='toggle-switch'>";
  html += "<span></span>";
  html += "</div>";
  html += "</label>";
  html += "</div>";
  html += "<div class='container'>";
  html += "<h3>" + String(deviceName) + "</h3>";
  html += "<p id='" + String(deviceName) + "-status'>";
  html += (digitalRead(pin) ? "Active" : "Inactive");
  html += "</p>";
  html += "</div>";
  html += "</div>";
  html += "</div>";
  return html;
}

void handleToggle() {
  if (server.hasArg("device")) {
    String device = server.arg("device");
    if (device == "LCD Left") {
      digitalWrite(lcd1Pin, !digitalRead(lcd1Pin));
      server.send(200, "text/plain", (digitalRead(lcd1Pin) ? "Active" : "Inactive"));
    } else if (device == "LCD Middle") {
      digitalWrite(lcd2Pin, !digitalRead(lcd2Pin));
      server.send(200, "text/plain", (digitalRead(lcd2Pin) ? "Active" : "Inactive"));
    } else if (device == "LCD Right") {
      digitalWrite(lcd3Pin, !digitalRead(lcd3Pin));
      server.send(200, "text/plain", (digitalRead(lcd3Pin) ? "Active" : "Inactive"));
    } else if (device == "Amplifier") {
      digitalWrite(ampPin, !digitalRead(ampPin));
      server.send(200, "text/plain", (digitalRead(ampPin) ? "Active" : "Inactive"));
    } else if (device == "Laptop Charger") {
      digitalWrite(chargerPin, !digitalRead(chargerPin));
      server.send(200, "text/plain", (digitalRead(chargerPin) ? "Active" : "Inactive"));
    } else if (device == "Extension Cord") {
      digitalWrite(cordPin, !digitalRead(cordPin));
      server.send(200, "text/plain", (digitalRead(cordPin) ? "Active" : "Inactive"));
    } else if (device == "Extra") {
      digitalWrite(extraPin, !digitalRead(extraPin));
      server.send(200, "text/plain", (digitalRead(extraPin) ? "Active" : "Inactive"));
    }
  }
}
