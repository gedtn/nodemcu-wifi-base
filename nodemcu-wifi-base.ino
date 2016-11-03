/*
 *  nodemcu-wifi-base
 *  
 *  This sketch provides a skeleton to use for writing sketches that need to ability to use wifi 
 *  on a known subset of networks. This allows devices based on this code to be able to switch 
 *  between wifi networks without needing to be reconfigured. Simply populate the 2 arrays
 *  (SSIDs and SSID_PWs) as needed
 *  
 *  This sketch is based on a some of the example sketches from ESP8266 Arduino IDE librarries
 */
 
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

String SSIDs[] = {"ssid-1"
                ,"ssid-2"
                };

String SSID_PWs[] = {"pw-1"
                    ,"pw-2"
                    };

String credentials;
char ssid[50];
char password[50];

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup done");

  connectWifi();  

  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
}

void loop () {


  
}

void connectWifi() {

  boolean connected = false;
  int connects;

  while (!connected) {
    connects = 0;
    Serial.println("scan start");
  
    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0)
      Serial.println("no networks found");
    else
    {
      Serial.print(n);
      Serial.println(" networks found");
      for (int i = 0; i < n; ++i)
      {
        // Look for known network
        if (getCredentials(WiFi.SSID(i))) {
          // Connect to WiFi network
          WiFi.SSID(i).toCharArray(ssid,WiFi.SSID(i).length()+1);
          credentials.toCharArray(password, credentials.length()+1);
          WiFi.begin(ssid,password);
          Serial.print("\n\r \n\rWorking to connect ");
          Serial.print(ssid);
          Serial.print(",");
          Serial.print(password);
        
          // Wait for connection
          while (WiFi.status() != WL_CONNECTED) {
            delay(1000);
            Serial.print(".");
            connects++;

            // We will try a few times before failing
            if (connects > 10) {
              Serial.println("Failed 10 attempts. Scanning again");
              break;
            }
          }

          if (WiFi.status() == WL_CONNECTED) {
            connected = true;
          }

        }
      }
    }
    Serial.println("");
  
    // Wait a bit before scanning again
    if (!connected) {
      delay(5000);
    }  
  }
}

boolean getCredentials(String SSID) {

  for (int i = 0; i<(sizeof(SSIDs)/4)-1; i++) {
    if (SSID == SSIDs[i]) {
      credentials = SSID_PWs[i];
      Serial.print("Match!!");      
      Serial.println(credentials);
      return true;
    }
  }
  return false;
}

