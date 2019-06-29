
/*
	TMC2130.cpp - Support for TMC2130 Stepper Drivers SPI Mode
  Part of Grbl_ESP32  

  Copyright (c) 2019 Barton Dring for Buildlog.net LLC   	

  GrblESP32 is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "grbl.h"

#ifdef X_CS_PIN
	#ifdef X_DRIVER_TYPE_TMC2130
		TMC2130Stepper driver_X(X_CS_PIN);
	#endif
	#ifdef X_DRIVER_TYPE_TMC5160
		TMC5160Stepper driver_X(X_CS_PIN);
	#endif
#endif

#ifdef Y_CS_PIN
	#ifdef Y_DRIVER_TYPE_TMC2130
		TMC2130Stepper driver_Y(Y_CS_PIN);
	#endif
#endif

#ifdef Z_CS_PIN
	#ifdef Z_DRIVER_TYPE_TMC2130
		TMC2130Stepper driver_Z(Z_CS_PIN);
	#endif
#endif

void Trinamic_Init()
{
	SPI.begin();                    // SPI drivers
	#ifdef X_CS_PIN			
		grbl_send(CLIENT_SERIAL, "[MSG: Init Trinamic X]\r\n");
		driver_X.begin(); // Initiate pins and registries				
		driver_X.microsteps(X_MICROSTEPS); 
		driver_X.rms_current(X_RMS_CURRENT);
	#endif	
		
	#ifdef Y_CS_PIN
		grbl_send(CLIENT_SERIAL, "[MSG: Init Trinamic Y]\r\n");
		driver_Y.begin(); // Initiate pins and registries
		driver_Y.toff(5);
		driver_Y.microsteps(X_MICROSTEPS);
		driver_Y.rms_current(X_RMS_CURRENT);
		driver_Y.pwm_autoscale(true);     // Needed for stealthChopg
	#endif
		
	#ifdef Z_CS_PIN
		grbl_send(CLIENT_SERIAL, "[MSG: Init Trinamic Z]\r\n");
		driver_Z.begin(); // Initiate pins and registries
		driver_Z.toff(5);
		driver_Z.microsteps(X_MICROSTEPS);
		driver_Z.rms_current(X_RMS_CURRENT);
		driver_Z.pwm_autoscale(true);     // Needed for stealthChop
	#endif
}
