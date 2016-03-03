#include "InputManager.h"


InputManager::InputManager(void)
{
	resetInput();
}

InputManager::~InputManager(void)
{
}

void InputManager::resetInput()
{
	for (short i = 0; i < 256; i++)
	{
		m_keys[i] = false;
		m_spec[i] = false;
	}
}

void InputManager::keyDown(short input) 
{ 
	if (input < INPUTOFFSET)
		m_keys[input] = true; 
	else
		m_spec[input-INPUTOFFSET] = true;
}

void InputManager::keyUp(short input) 
{ 
	if (input < INPUTOFFSET)
		m_keys[input] = false; 
	else
		m_spec[input-INPUTOFFSET] = false;
}

bool InputManager::isKeyDown(short key) 
{ 
	if (key < INPUTOFFSET)
		return m_keys[key]; 
	else
		return m_spec[key-INPUTOFFSET];
}