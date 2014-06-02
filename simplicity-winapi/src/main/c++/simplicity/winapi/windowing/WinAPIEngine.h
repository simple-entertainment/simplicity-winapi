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
#ifndef WINAPIENGINE_H_
#define WINAPIENGINE_H_

#include <string>

#include <windows.h>

#include <simplicity/windowing/WindowEngine.h>

namespace simplicity
{
	namespace winapi
	{
		class SIMPLE_API WinAPIEngine : public WindowEngine
		{
			public:
				/**
				 * @param title The window title.
				 * @param instance The WinAPI instance (an argument to WinMain).
				 * @param commandShow The WinAPI show command (an argument to WinMain).
				 */
				WinAPIEngine(const std::string& title, HINSTANCE instance, int commandShow);

				void advance();

				int getHeight() const;

				int getWidth() const;

				/**
				 * <p>
				 * Retrieves the WinAPI window.
				 * </p>
				 *
				 * @return The WinAPI window.
				 */
				HWND getWindow() const;

				bool isFullscreen() const;

				void onPlay();

				void setFullscreen(bool fullscreen);

				void setHeight(int height);

				void setWidth(int width);

			private:
				int commandShow;

				int height;

				HINSTANCE instance;

				std::string title;

				int width;

				HWND window;

				void createWindow();

				RECT getAdjustedRectangle() const;

				void registerWindowClass();
		};
	}
}

#endif /* WINAPIENGINE_H_ */
