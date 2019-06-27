
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
		#ifdef X_CS_PIN			
			grbl_send(CLIENT_SERIAL, "[MSG: Init Trinamic X]\r\n");
			driver_X.begin(); // Initiate pins and registries
			driver_X.microsteps(X_MICROSTEPS);
			driver_X.rms_current(X_RMS_CURRENT);
			driver_X.en_pwm_mode(1); // Enable extremely quiet stepping			
		#endif	
		
		#ifdef Y_CS_PIN
			grbl_send(CLIENT_SERIAL, "[MSG: Init Trinamic Y]\r\n");
			driver_Y.begin(); // Initiate pins and registries
			driver_Y.microsteps(Y_MICROSTEPS);
			driver_Y.rms_current(Y_RMS_CURRENT);
			driver_Y.en_pwm_mode(1); // Enable extremely quiet stepping
		#endif
		
		#ifdef Z_CS_PIN
			grbl_send(CLIENT_SERIAL, "[MSG: Init Trinamic Z]\r\n");
			driver_Z.begin(); // Initiate pins and registries
			driver_Z.microsteps(Z_MICROSTEPS);
			driver_Z.rms_current(Z_RMS_CURRENT);
			driver_Z.stealthChop(1); // Enable extremely quiet stepping
		#endif
}