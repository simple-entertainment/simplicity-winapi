/*
* Copyright © 2014 Simple Entertainment Limited
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
#include <simplicity/Simplicity.h>

#include "../input/WinAPIInputEvents.h"
#include "WinApiEngine.h"

using namespace std;

namespace simplicity
{
	namespace winapi
	{
		LRESULT CALLBACK handleEvent(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
		{
			if (message == WM_DESTROY)
			{
				Simplicity::stop();
				return 0;
			}
			else if (message == WM_KEYDOWN)
			{
				fireKeyboardButtonDownEvent(wParam);
			}
			else if (message == WM_KEYUP)
			{
				fireKeyboardButtonUpEvent(wParam);
			}
			else if (message == WM_LBUTTONDOWN)
			{
				fireMouseButtonEvent(Mouse::Button::LEFT, Button::State::DOWN, lParam);
			}
			else if (message == WM_LBUTTONUP)
			{
				fireMouseButtonEvent(Mouse::Button::LEFT, Button::State::UP, lParam);
			}
			else if (message == WM_MOUSEMOVE)
			{
				fireMouseMoveEvent(lParam);
			}
			else if (message == WM_RBUTTONDOWN)
			{
				fireMouseButtonEvent(Mouse::Button::RIGHT, Button::State::DOWN, lParam);
			}
			else if (message == WM_RBUTTONUP)
			{
				fireMouseButtonEvent(Mouse::Button::RIGHT, Button::State::UP, lParam);
			}

			return DefWindowProc(window, message, wParam, lParam);
		}

		WinAPIEngine::WinAPIEngine(const string& title, HINSTANCE instance, int commandShow) :
			commandShow(commandShow),
			height(768),
			instance(instance),
			title(title),
			width(1024),
			window()
		{
		}

		void WinAPIEngine::advance()
		{
			MSG message;
			while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}

		void WinAPIEngine::createWindow()
		{
			registerWindowClass();

			RECT adjustedRectangle = getAdjustedRectangle();
			int adjustedWidth = adjustedRectangle.right - adjustedRectangle.left;
			int adjustedHeight = adjustedRectangle.bottom - adjustedRectangle.top;

			window = CreateWindowEx(0, "WindowClass", title.c_str(), WS_OVERLAPPEDWINDOW, 0, 0, adjustedWidth,
				adjustedHeight, nullptr, nullptr, instance, nullptr);
		}

		RECT WinAPIEngine::getAdjustedRectangle() const
		{
			RECT windowRectangle;
			windowRectangle.bottom = height;
			windowRectangle.left = 0;
			windowRectangle.right = width;
			windowRectangle.top = 0;

			AdjustWindowRect(&windowRectangle, WS_OVERLAPPEDWINDOW, false);

			return windowRectangle;
		}

		int WinAPIEngine::getHeight() const
		{
			return height;
		}

		int WinAPIEngine::getWidth() const
		{
			return width;
		}

		HWND WinAPIEngine::getWindow() const
		{
			return window;
		}

		bool WinAPIEngine::isFullscreen() const
		{
			return false;
		}

		void WinAPIEngine::onPlay()
		{
			createWindow();
			ShowWindow(window, commandShow);
		}

		void WinAPIEngine::registerWindowClass()
		{
			WNDCLASSEX windowClass;
			ZeroMemory(&windowClass, sizeof(WNDCLASSEX));

			windowClass.cbSize = sizeof(WNDCLASSEX);
			windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
			windowClass.hInstance = instance;
			windowClass.lpfnWndProc = handleEvent;
			windowClass.lpszClassName = "WindowClass";
			windowClass.style = CS_HREDRAW | CS_VREDRAW;

			RegisterClassEx(&windowClass);
		}

		void WinAPIEngine::setFullscreen(bool /* fullscreen */)
		{
		}

		void WinAPIEngine::setHeight(int height)
		{
			this->height = height;
		}

		void WinAPIEngine::setWidth(int width)
		{
			this->width = width;
		}
	}
}
