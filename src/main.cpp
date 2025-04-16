#include <Arduino.h>
#include "LedCube.h"
#include <SdFat.h>

Led8x8x8 Cube(4, 5, 6);
SdFat SD;

File Data;
unsigned long int imageCount;
unsigned long repeatCount = 1;
byte image[64];
unsigned int num = 0;
byte _loop;

void setup()
{
    Serial.begin(9600);
    Cube.init();
    if (SD.begin(2))
    {
        Serial.println("SD mounted");
    }
    else
    {
        Serial.println("Failed to mount SD card.");
        while (1)
            ;
    }
    Data = SD.open("Cube.cbin", FILE_READ);
    if (!Data)
    {
        Serial.println("Failed to open file.");
        while (1)
            ;
        return;
    }
    Data.readBytes((char *)&imageCount, 4);
    Data.readBytes((char*)&repeatCount, 1);
    Data.readBytes((char *)&_loop, 1);
    Serial.println("Image count: ");
    Serial.println(imageCount);
    Serial.println("Repeat count: ");
    Serial.println(repeatCount);
    Serial.println("Loop Around: ");
    Serial.println(_loop ? "true" : "false");
}

void loop()
{
    Data.readBytes((char *)image, 64);
    num++;
    if (imageCount == 1)
    {
        Serial.println("one image only.");
        while (1)
        {
            Cube.print(image);
        }
    }
    else
    {
        for (unsigned int i = 0; i < (repeatCount + 1) * 2; i++)
        {
            Cube.print(image);
        }
    }
    if (num >= imageCount)
    {
        if (_loop)
        {
            num = 0;
            Data.seek(6);
            return;
        }
        Serial.println("End!");
        while (1)
        {
        }
    }
}