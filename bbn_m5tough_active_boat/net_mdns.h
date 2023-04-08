#ifndef NET_MDNS_H
#define NET_MDNS_H

//   from command line you can discover services:
//   avahi-browse -ar

#ifdef __cplusplus
extern "C" {
#endif

#define SK_TCP_HOST_PREF "signalk_host"
#define SK_TCP_PORT_PREF "signalk_port"

#define PYP_TCP_HOST_PREF "pypilot_host"
#define PYP_TCP_PORT_PREF "pypilot_port"

#define NMEA0183_TCP_HOST_PREF "n0183_host"
#define NMEA0183_TCP_PORT_PREF "n0183_port"

#define MPD_TCP_HOST_PREF "mpd_host"
#define MPD_TCP_PORT_PREF "mpd_port"

  void mdns_begin() {
    if (!MDNS.begin("ESP32_Browser")) {
      M5.Lcd.println("Error setting up MDNS responder!");
    }
  }

  void mdns_end() {
    MDNS.end();
  }

  bool discover_n_config() {
    bool saved = false;

    String signalk_tcp_host = preferences.getString(SK_TCP_HOST_PREF);
    int signalk_tcp_port = preferences.getInt(SK_TCP_PORT_PREF);
    if (signalk_tcp_host.length() <= 0 || signalk_tcp_host == "0.0.0.0" || signalk_tcp_port <= 0) {
      int n = MDNS.queryService("signalk-tcp", "tcp");
      if (n > 0) {
        if (n == 1) {
          preferences.remove("SK_TCP_HOST_PREF");
          preferences.remove("SK_TCP_PORT_PREF");
          preferences.putString(SK_TCP_HOST_PREF, MDNS.IP(0).toString());
          preferences.putInt(SK_TCP_PORT_PREF, MDNS.port(0));
          saved = true;
          M5.Lcd.print(MDNS.IP(0).toString());
          M5.Lcd.print(":");
          M5.Lcd.printf("%d - signalk\n", MDNS.port(0));
        }
      }
    }

    String nmea0183_tcp_host = preferences.getString(NMEA0183_TCP_HOST_PREF);
    int nmea0183_tcp_port = preferences.getInt(NMEA0183_TCP_PORT_PREF);
    if (nmea0183_tcp_host.length() <= 0 || nmea0183_tcp_host == "0.0.0.0" || nmea0183_tcp_port <= 0) {
      int n = MDNS.queryService("nmea-0183", "tcp");
      if (n > 0) {
        if (n == 1) {
          preferences.remove("NMEA0183_TCP_HOST_PREF");
          preferences.remove("NMEA0183_TCP_PORT_PREF");
          preferences.putString(NMEA0183_TCP_HOST_PREF, MDNS.IP(0).toString());
          preferences.putInt(NMEA0183_TCP_PORT_PREF, MDNS.port(0));
          saved = true;
          M5.Lcd.print(MDNS.IP(0).toString());
          M5.Lcd.print(":");
          M5.Lcd.printf("%d - nmea0183\n", MDNS.port(0));
        } else {
          String found10110;
          for (int i = 0; i < n; ++i) {
            if (MDNS.port(i) == 10110) {
              found10110 = MDNS.IP(i).toString();
            }
            break;
          }
          if (found10110 != NULL && found10110.length() > 0) {
            preferences.remove("NMEA0183_TCP_HOST_PREF");
            preferences.remove("NMEA0183_TCP_PORT_PREF");
            preferences.putString(NMEA0183_TCP_HOST_PREF, found10110);
            preferences.putInt(NMEA0183_TCP_PORT_PREF, 10110);
            saved = true;
            M5.Lcd.print(found10110);
            M5.Lcd.print(":");
            M5.Lcd.printf("%d - nmea0183\n", 10110);
          } else {
            preferences.remove("NMEA0183_TCP_HOST_PREF");
            preferences.remove("NMEA0183_TCP_PORT_PREF");
            preferences.putString(NMEA0183_TCP_HOST_PREF, MDNS.IP(0).toString());
            preferences.putInt(NMEA0183_TCP_PORT_PREF, MDNS.port(0));
            saved = true;
            M5.Lcd.print(MDNS.IP(0).toString());
            M5.Lcd.print(":");
            M5.Lcd.printf("%d - nmea0183\n", MDNS.port(0));
          }
        }
      }
    }

    String pypilot_tcp_host = preferences.getString(PYP_TCP_HOST_PREF);
    int pypilot_tcp_port = preferences.getInt(PYP_TCP_PORT_PREF);
    if (pypilot_tcp_host.length() <= 0 || pypilot_tcp_host == "0.0.0.0" || pypilot_tcp_port <= 0) {
      int n = MDNS.queryService("pypilot", "tcp");
      if (n > 0) {
        if (n == 1) {
          preferences.remove("PYP_TCP_HOST_PREF");
          preferences.remove("PYP_TCP_HOST_PREF");
          preferences.putString(PYP_TCP_HOST_PREF, MDNS.IP(0).toString());
          preferences.putInt(PYP_TCP_PORT_PREF, MDNS.port(0));
          saved = true;
          M5.Lcd.print(MDNS.IP(0).toString());
          M5.Lcd.print(":");
          M5.Lcd.printf("%d - pypilot\n", MDNS.port(0));
        }
      }
    }

    String mpd_tcp_host = preferences.getString(MPD_TCP_HOST_PREF);
    int mpd_tcp_port = preferences.getInt(MPD_TCP_PORT_PREF);
    if (mpd_tcp_host.length() <= 0 || mpd_tcp_host == "0.0.0.0" || mpd_tcp_port <= 0) {
      int n = MDNS.queryService("mpd", "tcp");
      if (n > 0) {
        if (n == 1) {
          preferences.remove("MPD_TCP_HOST_PREF");
          preferences.remove("MPD_TCP_PORT_PREF");
          preferences.putString(MPD_TCP_HOST_PREF, MDNS.IP(0).toString());
          preferences.putInt(MPD_TCP_PORT_PREF, MDNS.port(0));
          saved = true;
          M5.Lcd.print(MDNS.IP(0).toString());
          M5.Lcd.print(":");
          M5.Lcd.printf("%d - mpd\n", MDNS.port(0));
        }
      }
    }
    return saved;
  }

  void browseServiceMDNS(const char* service, const char* proto) {
    M5.Lcd.printf("Scan _%s._%s.local. ... ", service, proto);
    int n = MDNS.queryService(service, proto);
    if (n == 0) {
      M5.Lcd.println("no found");
    } else {
      M5.Lcd.setTextColor(WHITE);
      M5.Lcd.print(n);
      M5.Lcd.println(" found");
      M5.Lcd.setTextColor(YELLOW);
      for (int i = 0; i < n; ++i) {
        // Print details for each service found
        M5.Lcd.print(" ");
        M5.Lcd.print(i + 1);
        M5.Lcd.print(": ");
        M5.Lcd.print(MDNS.hostname(i));
        M5.Lcd.print(" (");
        M5.Lcd.print(MDNS.IP(i));
        M5.Lcd.print(":");
        M5.Lcd.print(MDNS.port(i));
        M5.Lcd.println(")");
      }
    }
    M5.Lcd.println();
  }

  void discoverBasics() {
    browseServiceMDNS("http", "tcp");
    delay(100);
    browseServiceMDNS("nmea-0183", "tcp");
    delay(100);
    browseServiceMDNS("signalk-http", "tcp");
    delay(100);
    browseServiceMDNS("signalk-tcp", "tcp");
    delay(100);
    browseServiceMDNS("signalk-ws", "tcp");
    delay(100);
    browseServiceMDNS("pypilot", "tcp");
    delay(100);
    browseServiceMDNS("mpd", "tcp");
    delay(100);
    browseServiceMDNS("mopidy-http", "tcp");
    delay(100);
  }

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
