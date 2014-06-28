/*
 * Copyright © 2012 Simple Entertainment Limited
 *
 * This file is part of The Simplicity Engine.
 *
 * The Simplicity Engine is free software: you can redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * The Simplicity Engine is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with The Simplicity Engine. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <simplicity/messaging/Messages.h>
#include <simplicity/messaging/Subject.h>

#include "WinAPIInputEvents.h"

using namespace std;

namespace simplicity
{
	namespace winapi
	{
		map<unsigned char, Keyboard::Button> winapiAsciiKeyboardButtonMap = createAsciiKeyboardButtonMap();

		int xOffset = 0;

		int yOffset = 0;

		void fireKeyboardButtonDownEvent(WPARAM key)
		{
			KeyboardButtonEvent keyboardButtonEvent = getKeyboardButtonEvent(key);
			keyboardButtonEvent.buttonState = Button::State::DOWN;
			
			Messages::send(Message(Subject::KEYBOARD_BUTTON, &keyboardButtonEvent));
		}

		void fireKeyboardButtonUpEvent(WPARAM key)
		{
			KeyboardButtonEvent event = getKeyboardButtonEvent(key);
			event.buttonState = Button::State::UP;

			Messages::send(Message(Subject::KEYBOARD_BUTTON, &event));
		}

		void fireMouseButtonEvent(Mouse::Button button, Button::State state, LPARAM position)
		{
			MouseButtonEvent mouseButtonEvent;
			mouseButtonEvent.button = button;
			mouseButtonEvent.buttonState = state;
			mouseButtonEvent.x = static_cast<int>(LOWORD(position));
			mouseButtonEvent.y = static_cast<int>(HIWORD(position));

			Messages::send(Message(Subject::MOUSE_BUTTON, &mouseButtonEvent));
		}

		void fireMouseMoveEvent(LPARAM position)
		{
			MouseMoveEvent mouseMoveEvent;
			mouseMoveEvent.x = static_cast<int>(LOWORD(position));
			mouseMoveEvent.y = static_cast<int>(HIWORD(position));

			Messages::send(Message(Subject::MOUSE_MOVE, &mouseMoveEvent));
		}

		KeyboardButtonEvent getKeyboardButtonEvent(WPARAM key)
		{
			KeyboardButtonEvent keyboardButtonEvent;

			if (key == VK_F1)
			{
				keyboardButtonEvent.button = Keyboard::Button::F1;
			}
			else if (key == VK_F2)
			{
				keyboardButtonEvent.button = Keyboard::Button::F2;
			}
			else if (key == VK_F3)
			{
				keyboardButtonEvent.button = Keyboard::Button::F3;
			}
			else if (key == VK_F4)
			{
				keyboardButtonEvent.button = Keyboard::Button::F4;
			}
			else if (key == VK_F5)
			{
				keyboardButtonEvent.button = Keyboard::Button::F5;
			}
			else if (key == VK_F6)
			{
				keyboardButtonEvent.button = Keyboard::Button::F6;
			}
			else if (key == VK_F7)
			{
				keyboardButtonEvent.button = Keyboard::Button::F7;
			}
			else if (key == VK_F8)
			{
				keyboardButtonEvent.button = Keyboard::Button::F8;
			}
			else if (key == VK_F9)
			{
				keyboardButtonEvent.button = Keyboard::Button::F9;
			}
			else if (key == VK_F10)
			{
				keyboardButtonEvent.button = Keyboard::Button::F10;
			}
			else if (key == VK_F11)
			{
				keyboardButtonEvent.button = Keyboard::Button::F11;
			}
			else if (key == VK_F12)
			{
				keyboardButtonEvent.button = Keyboard::Button::F12;
			}
			else if (key == VK_TAB)
			{
				keyboardButtonEvent.button = Keyboard::Button::TAB;
			}
			else if (winapiAsciiKeyboardButtonMap.find(static_cast<unsigned char>(key)) != winapiAsciiKeyboardButtonMap.end())
			{
				keyboardButtonEvent.button = winapiAsciiKeyboardButtonMap[static_cast<unsigned char>(key)];
				keyboardButtonEvent.character = static_cast<unsigned char>(key);
			}

			return keyboardButtonEvent;
		}

		void setMouseOffsets(int xOffset, int yOffset)
		{
			winapi::xOffset = xOffset;
			winapi::yOffset = yOffset;
		}
	}
}
