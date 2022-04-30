#include "defines.h"

#include "Display.h"

#include <NTPClient_Generic.h>
#include <WiFiNINA.h>

#include "TimeWidget.h"
#include "ScrollingText.h"

int16_t x = 0;
int16_t y = 0;

int16_t x_1 = 0;
int16_t y_1 = 0;

uint16_t t_w = 0;
uint16_t t_h = 0;

uint16_t color565(uint8_t red, uint8_t green, uint8_t blue) {
    return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
}

uint16_t colors[] = { color565(32, 0, 0), color565(0, 32, 0), color565(0, 0, 32) };
uint16_t color_white = color565(32, 32, 32);

int WiFiStatus = WL_IDLE_STATUS;

//char timeServer[] = "0.north-america.pool.ntp.org";
char timeServer[] = "0.ca.pool.ntp.org";
TimeChangeRule myEDT = {"EDT", Second, Sun, Mar, 2, -240};
TimeChangeRule myEST = {"EST", First, Sun, Nov, 2, -300};
Timezone *EDT;
TimeChangeRule utcRule = {"UTC", Last, Sun, Mar, 1, 0};
Timezone *UTC;


#define TIME_ZONE_OFFSET_HRS            (-4)
#define NTP_UPDATE_INTERVAL_MS          60000L
WiFiUDP ntpUDP;

Display *canvas = NULL;


NTPClient timeClient(ntpUDP, timeServer, (3600 * TIME_ZONE_OFFSET_HRS), NTP_UPDATE_INTERVAL_MS);

static bool gotCurrentTime = false;

void update_Time(void)
{
    // Just get the correct time once
    if (timeClient.updated())
    {
        Serial.println("********UPDATED********");

        // set the system time to UTC
        // warning: assumes that compileTime() returns US EDT
        // adjust the followinif ((current_millis > TimeDisplay_timeout) || (TimeDisplay_timeout == 0))

        setTime(timeClient.getUTCEpochTime());

        gotCurrentTime = true;
    }
}

void check_status(void)
{
    // Update first time after 5s
    static ulong checkstatus_timeout  = 5000L;
    static ulong TimeDisplay_timeout   = 0;

    static ulong current_millis;

    // Display every 10s
#define TIME_DISPLAY_INTERVAL       (10000L)

    // Update RTC every hour if got correct time from NTP
#define TIME_UPDATE_INTERVAL         (3600 * 1000L)

    // Retry updating RTC every 5s if haven't got correct time from NTP
#define TIME_RETRY_INTERVAL          (3 * 1000L)

    current_millis = millis();

    // Update Time every TIME_UPDATE_INTERVAL (3600) seconds.
    if ((current_millis > checkstatus_timeout))
    {
        update_Time();

        if (gotCurrentTime)
        {
            Serial.println("Time updated. Next update in seconds : " + String(TIME_UPDATE_INTERVAL / 1000, DEC));
            checkstatus_timeout = current_millis + TIME_UPDATE_INTERVAL;
        }
        else
        {
            Serial.println("Retry Time update in seconds : " + String(TIME_RETRY_INTERVAL / 1000, DEC));
            checkstatus_timeout = current_millis + TIME_RETRY_INTERVAL;
        }
    }
}

void wifiConnect() {
    while (WiFiStatus != WL_CONNECTED) {
        Serial.print("Attempting to connect to WPA SSID: ");
        Serial.println(ssid);
        WiFiStatus = WiFi.begin(ssid, pass);
        delay(1000);
    }
    Serial.print(F("You're connected to the network, IP = "));
    Serial.println(WiFi.localIP());
}


#define MATRIX_WIDTH  128
#define MATRIX_HEIGHT 64

// WiFiClient espClient;
// int wifiStatus = -1;





void setup(void) {
    Serial.begin(115200) ;
    while (!Serial && millis() < 5000);
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);

    canvas = new Display(128, 64);
    Serial.print(F("\nStart NINA_TZ_NTP_Clock on ")); Serial.print(BOARD_NAME);
    Serial.print(F(" with ")); Serial.print(SHIELD_TYPE); Serial.print("on a board type "); Serial.println(BOARD_TYPE);
    Serial.println(NTPCLIENT_GENERIC_VERSION);
    canvas->printText(0,0,"Wifi Connect...");

    wifiConnect();
    //canvas->printText(0,8,"Connected: "+WiFi.localIP());
    //delay(5000);

    Serial.print(F("\nStart NINA_TZ_NTP_Clock on ")); Serial.println(BOARD_NAME);

    EDT = new Timezone(myEDT, myEST);
    UTC   = new Timezone(utcRule);
    timeClient.begin();
    Serial.println("Pause to begin...");
    check_status();

    canvas->printText(0,16,"widget registration..");
    TimeWidget* temp = new TimeWidget(0, 0, 32, 64, EDT, color565(32, 0, 0));
    canvas->registerWidget(temp);
    temp = new TimeWidget(64, 0, 32, 64, UTC, color565(0, 0, 32));
    canvas->registerWidget(temp);
    ScrollingTextWidget* t = new ScrollingTextWidget(0, 24, 40, 128, "Hello there, Twitterverse!!", color_white, 4);
    canvas->registerWidget(t);

    canvas->clearBuffer();

    Serial.println("STARTING....");
    Serial.println("Write something?");

}
int count = 0;
void loop(void) {
    digitalWrite(13, count++ % 2);
    if (count % 10 == 0 || count == 0 ) {
        timeClient.update();
        check_status();
    }
    canvas->updateWidgets();
}
