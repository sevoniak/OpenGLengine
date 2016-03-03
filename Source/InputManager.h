#pragma once

const short INPUTOFFSET = 300;

const short ascii_1 = 49;		//0x21
const short ascii_2 = 50;
const short ascii_3 = 51;
const short ascii_4 = 52;
const short ascii_5 = 53;
const short ascii_6 = 54;
const short ascii_A = 65;		//0x41
const short ascii_B = 66;
const short ascii_C = 67;
const short ascii_D = 68;
const short ascii_E = 69;
const short ascii_F = 70;
const short ascii_I = 73;
const short ascii_J = 74;
const short ascii_K = 75;
const short ascii_L = 76;
const short ascii_P = 80;
const short ascii_R = 82;
const short ascii_S = 83;
const short ascii_W = 87;
const short ascii_X = 88;
const short ascii_Y = 89;
const short ascii_Z = 90;


class InputManager
{
private:
	bool m_keys[256];
	bool m_spec[256];

public:
	InputManager();
	~InputManager();

	void resetInput();

	void keyDown(short);
	void keyUp(short);
	bool isKeyDown(short);
};

