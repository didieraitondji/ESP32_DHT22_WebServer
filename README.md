# **ESP32 DHT22 Web Server 🌡️💧**  

Surveillez en temps réel la température, l'humidité et l'indice de chaleur avec un ESP32 et un capteur DHT22. Ce projet permet à l'ESP32 de créer un point d'accès Wi-Fi, auquel les utilisateurs peuvent se connecter pour consulter les données via une interface web.

---

## **🖥️ Démonstration**  
![](demo-image.png)  
*Capture d'écran de l'interface web affichant la température, l'humidité et l'indice de chaleur.* (Ajoutez une capture d'écran ici.)

---

## **🚀 Fonctionnalités**  
- Création d'un point d'accès Wi-Fi avec l'ESP32.  
- Serveur web pour afficher la température, l'humidité et l'indice de chaleur en temps réel.  
- Interface utilisateur simple et responsive grâce au CSS intégré.  
- Actualisation automatique des données toutes les 10 secondes.

---

## **📋 Matériel Requis**  

| **Composant**           | **Quantité** | **Description** |
|-------------------------|--------------|-----------------|
| ESP32                    | 1            | Microcontrôleur principal |
| Capteur DHT22            | 1            | Capteur de température et d'humidité |
| Câbles Dupont            | 3            | Pour connecter le DHT22 à l'ESP32 |
| Alimentation USB         | 1            | Pour alimenter l'ESP32 |

---

## **🛠️ Schéma de Connexion**  

| **DHT22**  | **ESP32**  |
|------------|------------|
| VCC        | 3.3V       |
| GND        | GND        |
| DATA       | GPIO 4     |

---

## **📁 Dépendances**  

Assurez-vous d'avoir les bibliothèques suivantes installées dans l'IDE Arduino :  
1. **DHT Sensor Library**  
   - [Adafruit DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library)  
2. **ESPAsyncWebServer** (si nécessaire pour des améliorations futures)

---

## **🔧 Installation**  

### 1. **Préparation de l'environnement**  
- Téléchargez et installez l’IDE Arduino : [Arduino IDE](https://www.arduino.cc/en/software).  
- Installez les bibliothèques nécessaires via le gestionnaire de bibliothèques de l'IDE Arduino :
  - **DHT sensor library** (Adafruit)
  - **ESP32 Board Manager** via l’URL suivante :  
    `https://dl.espressif.com/dl/package_esp32_index.json`  

### 2. **Configuration du code**  
- Téléchargez ou clonez ce dépôt GitHub.  
- Ouvrez le fichier **`ESP32_DHT22_WebServer.ino`** dans l’IDE Arduino.  
- Vérifiez les paramètres Wi-Fi :  

```cpp
const char* ssid = "DIDOS_ESP32";  // Nom du point d'accès
const char* password = "12345678"; // Mot de passe du point d'accès
#define DHTPIN 4                   // Broche de données du DHT22
