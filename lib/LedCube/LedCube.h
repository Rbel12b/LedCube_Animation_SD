#ifndef Led8x8x8_h
#define Led8x8x8_h
#include "Arduino.h"
#if DEBUG
#define log(x) Serial.print(x)
#define log_m(x, m) Serial.print(x, m)
#else
#define log(x) Serial.print(x)
#define log_m(x, m) Serial.print(x, m)
#endif

#define XAXIS 0
#define YAXIS 1
#define ZAXIS 2

#define POS_X 0
#define NEG_X 1
#define POS_Z 2
#define NEG_Z 3
#define POS_Y 4
#define NEG_Y 5

#define BUTTON_PIN 8
#define RED_LED 5
#define GREEN_LED 7

#define TOTAL_EFFECTS 8
#define RAIN 0
#define PLANE_BOING 1
#define SEND_VOXELS 2
#define WOOP_WOOP 3
#define CUBE_JUMP 4
#define GLOW 5
#define TEXT 6
#define LIT 7

#define RAIN_TIME 100
#define PLANE_BOING_TIME 90
#define SEND_VOXELS_TIME 50
#define WOOP_WOOP_TIME 80
#define CUBE_JUMP_TIME 80
#define GLOW_TIME 50
#define TEXT_TIME 150
class Led8x8x8
{
public:
	Led8x8x8();
	Led8x8x8(bool, bool);
	Led8x8x8(int, int, int);
	Led8x8x8(int, int, int, bool, bool);
	void print(byte *);
	void printChar(byte[]);
	void fall(void);
	void init(void);
	void resetEffect(void);
	void clear(void);
	void scrollText(String);
	void scrollText(const char *);
	void scrollText(const char *, int);
	void scrollText(String, int);
	void clearCube(void);
	void rain(void);
	void planeBoing(void);
	void sendVoxels(void);
	void woopWoop(void);
	void cubeJump(void);
	void glow(void);
	void text(char string[], uint8_t len);
	void lit(void);
	void setVoxel(uint8_t x, uint8_t y, uint8_t z);
	void clearVoxel(uint8_t x, uint8_t y, uint8_t z);
	bool getVoxel(uint8_t x, uint8_t y, uint8_t z);
	void setPlane(uint8_t axis, uint8_t i);
	void shift(uint8_t dir);
	void drawCube(uint8_t x, uint8_t y, uint8_t z, uint8_t s);
	void lightCube(void);
	void renderCube(void);

private:
	void _println(byte[], byte[], int, int);
	void _latch(void);
	void _shiftHMirror(int, byte);
	void _shiftVMirror(int, byte);
	void _reset(void);
	void _search(void);
	void _setCharLine(const byte[]);
	void _printText(int,uint8_t);
	void _setRandomPath(void);
	void clear(int n);
	void fill(int n);
	void _setup(int, int, int, bool, bool);

protected:
	byte _charLine[32];
	int dataP;
	int clockP;
	int registerP;
	int ID;
	int randomseed;
	int _jelzo = 0;
	byte ledf[64];
	byte ledl[64];
	byte randomPath[64];
	byte NextVal = 0;
	bool _Hmirror = false;
	bool _Vmirror = false;
	byte cube[8][8];
	unsigned long long timer;
	uint64_t randomTimer;
	bool loading;
	uint8_t planePosition = 0;
	uint8_t planeDirection = 0;
	bool looped = false;
	uint8_t selX = 0;
	uint8_t selY = 0;
	uint8_t selZ = 0;
	uint8_t sendDirection = 0;
	bool sending = false;
	uint8_t cubeSize = 0;
	bool cubeExpanding = true;
	uint8_t xPos;
	uint8_t yPos;
	uint8_t zPos;
	bool glowing;
	uint16_t glowCount = 0;
	uint8_t charCounter = 0;
	uint8_t charPosition = 0;
};
#endif