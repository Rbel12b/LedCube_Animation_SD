#include "LedCube.h"

Led8x8x8::Led8x8x8()
{
	_setup(2, 3, 4, false, false);
}

Led8x8x8::Led8x8x8(bool Hmirror, bool Vmirror)
{
	_setup(2, 3, 4, Hmirror, Vmirror);
}

Led8x8x8::Led8x8x8(int dataPin, int clockPin, int registerPin)
{
	_setup(dataPin, clockPin, registerPin, false, false);
}

Led8x8x8::Led8x8x8(int dataPin, int clockPin, int registerPin, bool Hmirror, bool Vmirror)
{
	_setup(dataPin, clockPin, registerPin, Hmirror, Vmirror);
}

void Led8x8x8::_setup(int dataPin, int clockPin, int registerPin, bool Hmirror, bool Vmirror)
{
	_Vmirror = Vmirror;
	_Hmirror = Hmirror;
	dataP = dataPin;
	clockP = clockPin;
	registerP = registerPin;
	pinMode(dataP, OUTPUT);
	pinMode(clockP, OUTPUT);
	pinMode(registerP, OUTPUT);
	digitalWrite(registerP, LOW);
}

const uint8_t PROGMEM _LED8x8x8Font[101] = {
		0x00, 0x00,							// 0:Space
		0x7D,								// 2:  !
		0x60, 0x0, 0x60,					// 3:  "
		0x12, 0x3f, 0x12, 0x12, 0x3f, 0x12, // 6:  #
		0x30, 0x49, 0xff, 0x49, 0x6,		// 12: $
		0x11, 0x2a, 0x14, 0xa, 0x15, 0x22,	// 17: %
		0x66, 0x99, 0x89, 0x86, 0x62, 0x5,	// 23: &
		0xc0,								// 29: '
		0x3e, 0x41,							// 30: (
		0x41, 0x3e,							// 32: )
		0x88, 0x50, 0xf8, 0x50, 0x88,		// 34: +
		0x8, 0x8, 0x3e, 0x8, 0x8,			// 39: *
		0x3,								// 44: ,
		0x8, 0x8, 0x8, 0x8, 0x8,			// 45: -
		0x1,								// 50: .
		0x3, 0xc, 0x30,						// 51: /
		0x3e, 0x41, 0x41, 0x41, 0x3e,		// 54: 0
		0x10, 0x20, 0x7f,					// 59: 1
		0x21, 0x43, 0x45, 0x49, 0x31,		// 62: 2
		0x22, 0x49, 0x49, 0x49, 0x36,		// 67: 3
		0xc, 0x14, 0x24, 0x7f, 0x4,			// 72: 4
		0x7a, 0x49, 0x49, 0x49, 0x46,		// 77: 5
		0x3e, 0x49, 0x49, 0x49, 0x6,		// 82: 6
		0x40, 0x43, 0x4c, 0x50, 0x60,		// 86: 7
		0x36, 0x49, 0x49, 0x36,				// 91: 8
		0x32, 0x49, 0x49, 0x49, 0x3e,		// 95: 9 - 100
											/*{0x00, 0x18, 0x24, 0x24, 0x3C, 0x42, 0x42, 0x42, 6}, // A 1
											{0x00, 0x70, 0x48, 0x48, 0x70, 0x48, 0x48, 0x70, 4}, // B 2
											{0x00, 0x38, 0x40, 0x40, 0x40, 0x40, 0x40, 0x38, 4}, // C 3
											{0x00, 0x70, 0x48, 0x48, 0x48, 0x48, 0x48, 0x70, 4}, // D 4
											{0x00, 0x78, 0x40, 0x40, 0x78, 0x40, 0x40, 0x78, 4}, // E 5
											{0x00, 0x78, 0x40, 0x40, 0x78, 0x40, 0x40, 0x40, 4}, // F 6
											{0x00, 0x00, 0x38, 0x40, 0x40, 0x4C, 0x44, 0x38, 5}, // G 7
											{0x00, 0x44, 0x44, 0x44, 0x7C, 0x44, 0x44, 0x44, 5}, // H 8
											{0x00, 0x38, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38, 3}, // I 9
											{0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x48, 0x30, 4}, // J 10
											{0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x78, 4}, // K 11
											{0x00, 0x80, 0x80, 0x8A, 0x84, 0x84, 0x84, 0xF4, 0}, // L 12
											{0x00, 0x00, 0x44, 0x6C, 0x54, 0x44, 0x44, 0x44, 5}, // M 13
											{0x00, 0x44, 0x44, 0x64, 0x54, 0x4C, 0x44, 0x44, 5}, // N 14
											{0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 6}, // O 15
											{0x00, 0x70, 0x48, 0x48, 0x70, 0x40, 0x40, 0x40, 4}, // P 16
											{0x00, 0x3C, 0x42, 0x42, 0x42, 0x46, 0x3E, 0x01, 7}, // Q 17
											{0x00, 0x70, 0x48, 0x48, 0x70, 0x50, 0x48, 0x44, 5}, // R 18
											{0x00, 0x30, 0x40, 0x40, 0x30, 0x08, 0x08, 0x30, 4}, // S 19
											{0x00, 0x00, 0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 5}, // T 20
											{0x00, 0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38, 5}, // U 21
											{0x00, 0x82, 0x82, 0x44, 0x44, 0x28, 0x28, 0x10, 7}, // V 22
											{0x00, 0x00, 0x82, 0x82, 0x54, 0x54, 0x28, 0x28, 7}, // W 23
											{0x00, 0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 5}, // X 24
											{0x00, 0x00, 0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 5}, // Y 25
											{0x00, 0xFC, 0x04, 0x08, 0x10, 0x20, 0x40, 0xFC, 6}, // Z 26
											{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 4}, // SPACE 27
											{0x00, 0x00, 0x40, 0x80, 0x80, 0x80, 0x80, 0x40, 2}, //( 28
											{0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 2}, //) 29
											{0x01, 0x19, 0x24, 0x24, 0x3C, 0x42, 0x42, 0x42, 7}, // Á 30
											//{0x00, 0x70, 0x80, 0x86, 0x88, 0x86, 0x81, 0x76, 0},  //Cs
											//{0x00, 0x00, 0xE0, 0x97, 0x91, 0x92, 0x94, 0xE7, 0},  //Dz
											{0x02, 0x7A, 0x40, 0x40, 0x78, 0x40, 0x40, 0x78, 6}, // É 31
											//{0x00, 0x00, 0x70, 0x85, 0x82, 0x9A, 0x8A, 0x72, 0},  //GY
											{0x10, 0x10, 0x00, 0x38, 0x10, 0x10, 0x10, 0x38, 3}, // Í 32
											//{0x00, 0x44, 0x48, 0x50, 0x60, 0x50, 0x48, 0x44, 5},  //LY
											//{0x00, 0x88, 0x88, 0xCD, 0xAA, 0x9A, 0x8A, 0x8A, 0},  //NY
											{0x08, 0x08, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x3C, 6}, // Ó 33
											{0x24, 0x00, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x3C, 6}, // Ö 34
											{0x24, 0x24, 0x00, 0x3C, 0x42, 0x42, 0x42, 0x3C, 6}, // Ő 35
											//{0x00, 0x60, 0x80, 0x87, 0x61, 0x12, 0x14, 0x67, 0},  //SZ
											//{0x00, 0x00, 0xF8, 0x25, 0x22, 0x22, 0x22, 0x22, 0},  //TY
											{0x10, 0x10, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38, 5}, // Ú 36
											{0x28, 0x00, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38, 5}, // Ü 37
											{0x28, 0x28, 0x44, 0x44, 0x44, 0x44, 0x44, 0x38, 5}, // Ű 38
											//{0x00, 0x00, 0x00, 0xF3, 0x14, 0x23, 0x41, 0xF6, 0},  //ZS*/
};
const uint8_t PROGMEM _charmap[95] = {
	0,	 // Space
	2,	 // !
	3,	 // "
	6,	 // #
	12,	 // $
	17,	 // %
	23,	 // &
	29,	 // '
	30,	 // (
	32,	 // )
	34,	 // *
	39,	 // +
	44,	 // ,
	45,	 // -
	50,	 // .
	51,	 // /
	54,	 // 0
	59,	 // 1
	62,	 // 2
	67,	 // 3
	72,	 // 4
	77,	 // 5
	82,	 // 6
	86,	 // 7
	91,	 // 8
	95,	 // 9
	100, // :
	0,	 // ;
	0,	 // <
	0,	 // =
	0,	 // >
	0,	 // ?
	0,	 // @
	0,	 // A
	0,	 // B
	0,	 // C
	0,	 // D
	0,	 // E
	0,	 // F
	0,	 // G
	0,	 // H
	0,	 // I
	0,	 // J
	0,	 // K
	0,	 // L
	0,	 // M
	0,	 // N
	0,	 // O
	0,	 // P
	0,	 // Q
	0,	 // R
	0,	 // S
	0,	 // T
	0,	 // U
	0,	 // V
	0,	 // W
	0,	 // X
	0,	 // Y
	0,	 // Z
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0,	 //
	0	 //
};

void Led8x8x8::renderCube(void)
{
	for (int a = 0; a < 8; a++)
	{
		for (int b = 0; b < 8; b++)
		{
			_shiftHMirror((int)cube[b][a], 1);
		}
		_shiftVMirror(0x01 << a, 1);
		_latch();
	}
	// added just for delay, because it thakes around the same time to render a layer
	// so the last layer will not look brighter.
	for (int b = 0; b < 8; b++)
	{
		_shiftHMirror(0, 1);
	}
	_shiftVMirror(0, 1);
	_latch();
	return;
}

void Led8x8x8::_setCharLine(const byte c[])
{
	log(c[8]);
	log("\n");
	for (int i = 0; i < c[8]; i++)
	{
		_charLine[_jelzo + i] = c[i];
	}
	_jelzo += (c[8] + 1);
	if(_jelzo > 16){
		_jelzo = 0;
	}
}

void Led8x8x8::print(byte *Data)
{
	for (int a = 0; a < 8; a++)
	{
		for (int b = 0; b < 8; b++)
		{
			_shiftHMirror(Data[8 * b + a], 1);
		}
		_shiftVMirror(0x01 << a, 1);
		_latch();
	}
	// added just for delay, because it thakes around the same time to render a layer
	// so the last layer will not look brighter.
	for (int b = 0; b < 8; b++)
	{
		_shiftHMirror(0, 1);
	}
	_shiftVMirror(0, 1);
	_latch();
	return;
}

void Led8x8x8::_printText(int timing, uint8_t charLenght)
{
	log(_jelzo);
	log("\n");

	int begintime = 0;
	byte rows[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	if(_jelzo != 0){
		return;
	}
	for (int counter = 0; counter < 8;)
	{
		begintime = millis();
		for (int i = 0; i < 8; i++)
		{
			rows[i] = 0;
			for (int x = counter; x < counter + 8; x++)
			{
				if (_charLine[x] & (0x80 >> i))
				{
					rows[i] = rows[i] + (0x80 >> (x - counter));
				}
			}
		}
	_PRINT:
		for (int b = 0; b < 8; b++)
		{
			_shiftHMirror(rows[b], 0);
			clear(6);
			_shiftVMirror(0x01 << b, 1);
			_latch();
		}
		if ((unsigned long)(millis() - begintime) >= (unsigned long)timing)
		{
			counter++;
		}
		else
		{
			goto _PRINT;
		}
	}
}

void Led8x8x8::printChar(byte Data[])
{
	for (int b = 0; b < 8; b++)
	{
		_shiftHMirror(Data[b], 0);
		clear(6);
		_shiftVMirror(0x01 << b, 1);
		_latch();
	}
}

void Led8x8x8::_println(byte c[], byte e[], int rv, int level)
{
	int total[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	int data1[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	for (int a = 0; a < 8; a++)
	{
		for (int b = 0; b < 8; b++)
		{
			bool d = c[8 * a + b];
			if (d)
			{
				total[a] = total[a] + (0x01 << b);
			}
		}
	}
	for (int a = 0; a < 8; a++)
	{
		for (int b = 0; b < 8; b++)
		{
			bool d = e[8 * a + b];
			if (d)
			{
				data1[a] = data1[a] + (0x01 << b);
			}
		}
	}
	for (int b = 0; b < 8; b++)
	{
		_shiftHMirror(total[b], 1);
	}
	_shiftVMirror(0x01, 1);
	_latch();
	for (int a = 1; a < 7; a++)
	{
		for (int b = 0; b < 8; b++)
		{
			if (rv / 8 != b)
			{
				_shiftHMirror(0x00, 0);
			}
			else if (level == a)
			{
				_shiftHMirror(0x01 << rv % 8, 1);
			}
			else
			{
				_shiftHMirror(0x00, 0);
			}
		}
		_shiftVMirror(0x01 << a, 1);
		_latch();
	}
	for (int b = 0; b < 8; b++)
	{
		_shiftHMirror(data1[b], 1);
	}
	_shiftVMirror(0x80, 1);
	_latch();
}

void Led8x8x8::_latch(void)
{
	digitalWrite(registerP, HIGH);
	digitalWrite(registerP, LOW);
}

void Led8x8x8::_shiftHMirror(int data, byte bitorder)
{
	if ((bitorder && !_Hmirror) || (!bitorder && _Hmirror))
	{
		shiftOut(dataP, clockP, MSBFIRST, data);
	}
	else
	{
		shiftOut(dataP, clockP, LSBFIRST, data);
	}
}

void Led8x8x8::_shiftVMirror(int data, byte bitorder)
{
	if ((bitorder && !_Vmirror) || (!bitorder && _Vmirror))
	{
		shiftOut(dataP, clockP, MSBFIRST, data);
	}
	else
	{
		shiftOut(dataP, clockP, LSBFIRST, data);
	}
}

void Led8x8x8::fall(void)
{
	_reset();
	_setRandomPath();
	for (int i = 0; i < 64; i++)
	{
		_search();
		for (int i = 1; i < 7; i++)
		{
			for (int k = 0; k < 4; k++)
			{
				_println(ledf, ledl, ID, i);
			}
		}
		ledl[ID] = 1;
		_println(ledf, ledl, ID, i);
	}
	for (int i = 0; i < 100; i++)
	{
		_println(ledf, ledl, ID, 8);
	}
}

void Led8x8x8::init(void)
{
	_reset();
	for (int i = 0; i < 32; i++)
	{
		_charLine[i] = 0;
	}
	_jelzo = 0;
}

void Led8x8x8::_reset(void)
{
	for (int i = 0; i < 64; i++)
	{
		ledf[i] = 1;
	}
	for (int i = 0; i < 64; i++)
	{
		ledl[i] = 0;
	}
	resetEffect();
}

void Led8x8x8::resetEffect(void)
{
	loading = true;
	timer = millis();
}

void Led8x8x8::_search(void)
{
	ID = randomPath[NextVal++];
	ledf[ID] = 0;
	return;
}

void Led8x8x8::_setRandomPath(void)
{
	for (int i = 0; i < 64; i++)
	{
	Generate_Random:
		randomPath[i] = random(0, 64);
		for (int n = 0; n < i; n++)
		{
			if (randomPath[n] == randomPath[i])
			{
				goto Generate_Random;
			}
		}
	}
	NextVal = 0;
	return;
}

void Led8x8x8::clear(int n)
{
	for (int i = 0; i <= n; i++)
	{
		_shiftVMirror(0x00, 0);
	}
}

void Led8x8x8::clear(void)
{
	_shiftVMirror(0x00, 0);
	_latch();
	clearCube();
}

void Led8x8x8::fill(int n)
{
	for (int i = 0; i <= n; i++)
	{
		_shiftVMirror(0xff, 0);
		_latch();
	}
}

void Led8x8x8::scrollText(String text)
{
	scrollText(text, 150);
}

void Led8x8x8::scrollText(const char *text)
{
	String _text = text;
	scrollText(_text, 150);
}

void Led8x8x8::scrollText(const char *text, int timing)
{
	String _text = text;
	scrollText(_text, timing);
}

void Led8x8x8::scrollText(String text, int timing)
{
	
}

void Led8x8x8::rain(void)
{
	if (loading)
	{
		clearCube();
		loading = false;
	}

	if (millis() - timer > RAIN_TIME)
	{
		timer = millis();
		shift(NEG_Y);
		uint8_t numDrops = random(0, 5);
		for (uint8_t i = 0; i < numDrops; i++)
		{
			setVoxel(random(0, 8), 7, random(0, 8));
		}
	}
	renderCube();
}

void Led8x8x8::planeBoing(void)
{
	if (loading)
	{
		clearCube();
		uint8_t axis = random(0, 3);
		planePosition = random(0, 2) * 7;
		setPlane(axis, planePosition);
		if (axis == XAXIS)
		{
			if (planePosition == 0)
			{
				planeDirection = POS_X;
			}
			else
			{
				planeDirection = NEG_X;
			}
		}
		else if (axis == YAXIS)
		{
			if (planePosition == 0)
			{
				planeDirection = POS_Y;
			}
			else
			{
				planeDirection = NEG_Y;
			}
		}
		else if (axis == ZAXIS)
		{
			if (planePosition == 0)
			{
				planeDirection = POS_Z;
			}
			else
			{
				planeDirection = NEG_Z;
			}
		}
		timer = millis();
		looped = false;
		loading = false;
	}

	if (millis() - timer > PLANE_BOING_TIME)
	{
		timer = millis();
		shift(planeDirection);
		if (planeDirection % 2 == 0)
		{
			planePosition++;
			if (planePosition == 7)
			{
				if (looped)
				{
					loading = true;
				}
				else
				{
					planeDirection++;
					looped = true;
				}
			}
		}
		else
		{
			planePosition--;
			if (planePosition == 0)
			{
				if (looped)
				{
					loading = true;
				}
				else
				{
					planeDirection--;
					looped = true;
				}
			}
		}
	}
	renderCube();
}

void Led8x8x8::sendVoxels(void)
{
	if (loading)
	{
		clearCube();
		for (uint8_t x = 0; x < 8; x++)
		{
			for (uint8_t z = 0; z < 8; z++)
			{
				setVoxel(x, random(0, 2) * 7, z);
			}
		}
		loading = false;
	}

	if (millis() - timer > SEND_VOXELS_TIME)
	{
		timer = millis();
		if (!sending)
		{
			selX = random(0, 8);
			selZ = random(0, 8);
			if (getVoxel(selX, 0, selZ))
			{
				selY = 0;
				sendDirection = POS_Y;
			}
			else if (getVoxel(selX, 7, selZ))
			{
				selY = 7;
				sendDirection = NEG_Y;
			}
			sending = true;
		}
		else
		{
			if (sendDirection == POS_Y)
			{
				selY++;
				setVoxel(selX, selY, selZ);
				clearVoxel(selX, selY - 1, selZ);
				if (selY == 7)
				{
					sending = false;
				}
			}
			else
			{
				selY--;
				setVoxel(selX, selY, selZ);
				clearVoxel(selX, selY + 1, selZ);
				if (selY == 0)
				{
					sending = false;
				}
			}
		}
	}
	renderCube();
}

void Led8x8x8::woopWoop(void)
{
	if (loading)
	{
		clearCube();
		cubeSize = 2;
		cubeExpanding = true;
		loading = false;
	}

	if (millis() - timer > WOOP_WOOP_TIME)
	{
		timer = millis();
		if (cubeExpanding)
		{
			cubeSize += 2;
			if (cubeSize == 8)
			{
				cubeExpanding = false;
			}
		}
		else
		{
			cubeSize -= 2;
			if (cubeSize == 2)
			{
				cubeExpanding = true;
			}
		}
		clearCube();
	}
	drawCube(4 - cubeSize / 2, 4 - cubeSize / 2, 4 - cubeSize / 2, cubeSize);
}

void Led8x8x8::cubeJump(void)
{
	if (loading)
	{
		clearCube();
		xPos = random(0, 2) * 7;
		yPos = random(0, 2) * 7;
		zPos = random(0, 2) * 7;
		cubeSize = 8;
		cubeExpanding = false;
		loading = false;
	}

	if (millis() - timer > CUBE_JUMP_TIME)
	{
		timer = millis();
		clearCube();
		if (xPos == 0 && yPos == 0 && zPos == 0)
		{
			drawCube(xPos, yPos, zPos, cubeSize);
		}
		else if (xPos == 7 && yPos == 7 && zPos == 7)
		{
			drawCube(xPos + 1 - cubeSize, yPos + 1 - cubeSize, zPos + 1 - cubeSize, cubeSize);
		}
		else if (xPos == 7 && yPos == 0 && zPos == 0)
		{
			drawCube(xPos + 1 - cubeSize, yPos, zPos, cubeSize);
		}
		else if (xPos == 0 && yPos == 7 && zPos == 0)
		{
			drawCube(xPos, yPos + 1 - cubeSize, zPos, cubeSize);
		}
		else if (xPos == 0 && yPos == 0 && zPos == 7)
		{
			drawCube(xPos, yPos, zPos + 1 - cubeSize, cubeSize);
		}
		else if (xPos == 7 && yPos == 7 && zPos == 0)
		{
			drawCube(xPos + 1 - cubeSize, yPos + 1 - cubeSize, zPos, cubeSize);
		}
		else if (xPos == 0 && yPos == 7 && zPos == 7)
		{
			drawCube(xPos, yPos + 1 - cubeSize, zPos + 1 - cubeSize, cubeSize);
		}
		else if (xPos == 7 && yPos == 0 && zPos == 7)
		{
			drawCube(xPos + 1 - cubeSize, yPos, zPos + 1 - cubeSize, cubeSize);
		}
		if (cubeExpanding)
		{
			cubeSize++;
			if (cubeSize == 8)
			{
				cubeExpanding = false;
				xPos = random(0, 2) * 7;
				yPos = random(0, 2) * 7;
				zPos = random(0, 2) * 7;
			}
		}
		else
		{
			cubeSize--;
			if (cubeSize == 1)
			{
				cubeExpanding = true;
			}
		}
	}
	renderCube();
}

void Led8x8x8::glow(void)
{
	if (loading)
	{
		clearCube();
		glowCount = 0;
		glowing = true;
		loading = false;
	}

	if (millis() - timer > GLOW_TIME)
	{
		timer = millis();
		if (glowing)
		{
			if (glowCount < 448)
			{
				do
				{
					selX = random(0, 8);
					selY = random(0, 8);
					selZ = random(0, 8);
				} while (getVoxel(selX, selY, selZ));
				setVoxel(selX, selY, selZ);
				glowCount++;
			}
			else if (glowCount < 512)
			{
				lightCube();
				glowCount++;
			}
			else
			{
				glowing = false;
				glowCount = 0;
			}
		}
		else
		{
			if (glowCount < 448)
			{
				do
				{
					selX = random(0, 8);
					selY = random(0, 8);
					selZ = random(0, 8);
				} while (!getVoxel(selX, selY, selZ));
				clearVoxel(selX, selY, selZ);
				glowCount++;
			}
			else
			{
				clearCube();
				glowing = true;
				glowCount = 0;
			}
		}
	}
	renderCube();
}

void Led8x8x8::text(char string[], uint8_t len)
{
	if (loading)
	{
		clearCube();
		charPosition = -1;
		charCounter = 0;
		loading = false;
	}

	if (millis() - timer > TEXT_TIME)
	{
		timer = millis();

		shift(NEG_Z);
		charPosition++;

		if (charPosition == 7)
		{
			charCounter++;
			if (charCounter > len - 1)
			{
				charCounter = 0;
			}
			charPosition = 0;
		}

		if (charPosition == 0)
		{
			for (uint8_t i = 0; i < 8; i++)
			{
				// cube[i][0] = _characters[string[charCounter] - ' '][i];
			}
		}
	}
	renderCube();
}

void Led8x8x8::lit(void)
{
	if (loading)
	{
		clearCube();
		for (uint8_t i = 0; i < 8; i++)
		{
			for (uint8_t j = 0; j < 8; j++)
			{
				cube[i][j] = 0xFF;
			}
		}
		loading = false;
	}
	renderCube();
}

void Led8x8x8::setVoxel(uint8_t x, uint8_t y, uint8_t z)
{
	cube[7 - y][7 - z] |= (0x01 << x);
}

void Led8x8x8::clearVoxel(uint8_t x, uint8_t y, uint8_t z)
{
	cube[7 - y][7 - z] ^= (0x01 << x);
}

bool Led8x8x8::getVoxel(uint8_t x, uint8_t y, uint8_t z)
{
	return (cube[7 - y][7 - z] & (0x01 << x)) == (0x01 << x);
}

void Led8x8x8::setPlane(uint8_t axis, uint8_t i)
{
	for (uint8_t j = 0; j < 8; j++)
	{
		for (uint8_t k = 0; k < 8; k++)
		{
			if (axis == XAXIS)
			{
				setVoxel(i, j, k);
			}
			else if (axis == YAXIS)
			{
				setVoxel(j, i, k);
			}
			else if (axis == ZAXIS)
			{
				setVoxel(j, k, i);
			}
		}
	}
}

void Led8x8x8::shift(uint8_t dir)
{

	if (dir == POS_X)
	{
		for (uint8_t y = 0; y < 8; y++)
		{
			for (uint8_t z = 0; z < 8; z++)
			{
				cube[y][z] = cube[y][z] << 1;
			}
		}
	}
	else if (dir == NEG_X)
	{
		for (uint8_t y = 0; y < 8; y++)
		{
			for (uint8_t z = 0; z < 8; z++)
			{
				cube[y][z] = cube[y][z] >> 1;
			}
		}
	}
	else if (dir == POS_Y)
	{
		for (uint8_t y = 1; y < 8; y++)
		{
			for (uint8_t z = 0; z < 8; z++)
			{
				cube[y - 1][z] = cube[y][z];
			}
		}
		for (uint8_t i = 0; i < 8; i++)
		{
			cube[7][i] = 0;
		}
	}
	else if (dir == NEG_Y)
	{
		for (uint8_t y = 7; y > 0; y--)
		{
			for (uint8_t z = 0; z < 8; z++)
			{
				cube[y][z] = cube[y - 1][z];
			}
		}
		for (uint8_t i = 0; i < 8; i++)
		{
			cube[0][i] = 0;
		}
	}
	else if (dir == POS_Z)
	{
		for (uint8_t y = 0; y < 8; y++)
		{
			for (uint8_t z = 1; z < 8; z++)
			{
				cube[y][z - 1] = cube[y][z];
			}
		}
		for (uint8_t i = 0; i < 8; i++)
		{
			cube[i][7] = 0;
		}
	}
	else if (dir == NEG_Z)
	{
		for (uint8_t y = 0; y < 8; y++)
		{
			for (uint8_t z = 7; z > 0; z--)
			{
				cube[y][z] = cube[y][z - 1];
			}
		}
		for (uint8_t i = 0; i < 8; i++)
		{
			cube[i][0] = 0;
		}
	}
}

void Led8x8x8::drawCube(uint8_t x, uint8_t y, uint8_t z, uint8_t s)
{
	for (uint8_t i = 0; i < s; i++)
	{
		setVoxel(x, y + i, z);
		setVoxel(x + i, y, z);
		setVoxel(x, y, z + i);
		setVoxel(x + s - 1, y + i, z + s - 1);
		setVoxel(x + i, y + s - 1, z + s - 1);
		setVoxel(x + s - 1, y + s - 1, z + i);
		setVoxel(x + s - 1, y + i, z);
		setVoxel(x, y + i, z + s - 1);
		setVoxel(x + i, y + s - 1, z);
		setVoxel(x + i, y, z + s - 1);
		setVoxel(x + s - 1, y, z + i);
		setVoxel(x, y + s - 1, z + i);
	}
	renderCube();
}

void Led8x8x8::lightCube(void)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		for (uint8_t j = 0; j < 8; j++)
		{
			cube[i][j] = 0xFF;
		}
	}
	renderCube();
}

void Led8x8x8::clearCube(void)
{
	for (uint8_t i = 0; i < 8; i++)
	{
		for (uint8_t j = 0; j < 8; j++)
		{
			cube[i][j] = 0;
		}
	}
	renderCube();
}