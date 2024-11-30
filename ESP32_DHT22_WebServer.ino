#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// Définition des broches et du type de capteur DHT
#define DHTPIN 4 // GPIO utilisé pour connecter le DHT22
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Configuration du point d'accès
const char *ssid = "ESP32_DHT22";  // Nom du réseau Wi-Fi
const char *password = "12345678"; // Mot de passe du réseau Wi-Fi

WebServer server(80); // Serveur web sur le port 80

void setup()
{
    Serial.begin(115200);
    dht.begin();

    // Création du point d'accès Wi-Fi
    WiFi.softAP(ssid, password);
    Serial.println("Point d'accès Wi-Fi créé !");
    Serial.print("Nom du réseau : ");
    Serial.println(ssid);
    Serial.print("Mot de passe : ");
    Serial.println(password);
    Serial.print("Adresse IP : ");
    Serial.println(WiFi.softAPIP());

    // Route pour la page principale
    server.on("/", handleRoot);

    // Route pour les données JSON
    server.on("/data", handleData);

    // Démarrage du serveur
    server.begin();
    Serial.println("Serveur HTTP démarré");
}

void loop()
{
    server.handleClient(); // Gérer les requêtes clients
}

// Fonction pour la page HTML principale
void handleRoot()
{
    String html = generateHTML();
    server.send(200, "text/html", html);
}

// Fonction pour envoyer les données JSON
void handleData()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    float f = dht.readTemperature(true);
    float hic = dht.computeHeatIndex(t, h, false);
    float hif = dht.computeHeatIndex(f, h);

    String json = "{";
    json += "\"temperature\":" + String(t) + ",";
    json += "\"temperatureF\":" + String(f) + ",";
    json += "\"humidity\":" + String(h) + ",";
    json += "\"heatIndex\":" + String(hic) + ",";
    json += "\"heatIndexF\":" + String(hif);
    json += "}";

    server.send(200, "application/json", json);
}

// Fonction pour générer le HTML
String generateHTML()
{
    String html = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>ESP32 DHT22 Monitor</title>
  <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@300;400&display=swap" rel="stylesheet">
  <style>
    body {
      font-family: 'Roboto', sans-serif;
      text-align: center;
      background-color: #f0f8ff;
      color: #333;
      margin: 0;
      padding: 0;
      display: flex;
      justify-content: center;
      align-items: center;
      height: 100vh;
    }
    .container {
      width: 80%;
      max-width: 600px;
      margin: 0 auto;
      padding: 20px;
      background-color: #ffffff;
      border-radius: 15px;
      box-shadow: 0px 6px 15px rgba(0, 0, 0, 0.1);
    }
    h1 {
      color: #2c3e50;
      margin: 20px 0;
    }
    .data {
      font-size: 1.5em;
      margin: 15px 0;
      padding: 15px;
      border-radius: 8px;
      background-color: #e8f5e9;
      color: #2e7d32;
    }
  </style>
  <script>
    function getData() {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/data", true);
      xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
          var json = JSON.parse(xhr.responseText);
          document.getElementById("temperature").innerHTML = json.temperature + "°C / " + json.temperatureF + "°F";
          document.getElementById("humidity").innerHTML = json.humidity + " %";
          document.getElementById("heatIndex").innerHTML = json.heatIndex + "°C / " + json.heatIndexF + "°F";
        }
      };
      xhr.send();
    }
    setInterval(getData, 5000); // Rafraîchissement toutes les 5 secondes
  </script>
</head>
<body onload="getData()">
  <div class="container">
    <h1>Moniteur de Température & Humidité</h1>
    <div class="data">
      🌡️ Température : <span id="temperature">--</span>
    </div>
    <div class="data">
      💧 Humidité : <span id="humidity">--</span>
    </div>
    <div class="data">
      🔥 Indice de Chaleur : <span id="heatIndex">--</span>
    </div>
  </div>
</body>
</html>
)rawliteral";
    return html;
}
