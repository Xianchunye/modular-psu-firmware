/*
 * EEZ Modular Firmware
 * Copyright (C) 2015-present, Envox d.o.o.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <eez/gui/document.h>

using namespace eez::gui;

namespace eez {
namespace home {

bool isTouchCalibrated();
void enterTouchCalibration(int yesNoPageId = PAGE_ID_TOUCH_CALIBRATION_YES_NO_CANCEL,
                           int nextPageId = -1);
void onTouchCalibrationPageTouch(const WidgetCursor &foundWidget, Event &touchEvent);
bool isTouchPointActivated();

} // namespace home
} // namespace eez
