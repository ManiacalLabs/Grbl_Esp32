
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

#ifdef USE_TRINAMIC
	#ifdef USE_SPI_DAISY_CHAIN
		#ifdef DRIVER_TYPE_TMC2130
			TMC2130Stepper driver(CS_STEPPER);
		#endif
		#ifdef DRIVER_TYPE_TMC5160
			TMC5160Stepper driver(CS_STEPPER);			
		#endif
	#else
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
			#ifdef Y_DRIVER_TYPE_TMC5160
				TMC5160Stepper driver_Y(Y_CS_PIN);
			#endif
		#endif

		#ifdef Z_CS_PIN
			#ifdef Z_DRIVER_TYPE_TMC2130
				TMC2130Stepper driver_Z(Z_CS_PIN);
			#endif
			#ifdef Z_DRIVER_TYPE_TMC5160
				TMC5160Stepper driver_Z(Z_CS_PIN);
			#endif
		#endif
	#endif
#endif


void Trinamic_Init()
{
	grbl_send(CLIENT_SERIAL, "[MSG: Trinamic Init]\r\n");
	SPI.begin();                    // SPI drivers
	
	#ifdef USE_SPI_DAISY_CHAIN
		grbl_send(CLIENT_SERIAL, "[MSG: CS Daisy Chain]\r\n");
		driver.set_axis_count(4);		
		
		#ifdef X_STEP_PIN
			driver.set_axis(X_AXIS);
			driver.begin();
			driver.microsteps(X_MICROSTEPS);
			//driver.rms_current(X_RMS_CURRENT);	
			driver.irun(24);
			if (settings.stepper_idle_lock_time == 255) {
				driver.ihold(5);	
				driver.iholddelay(6);
				driver.TPOWERDOWN(10);
			}
			else {
				driver.ihold(0);
			}			
		#endif
		
		#ifdef Y_STEP_PIN
			driver.set_axis(Y_AXIS);
			driver.begin();
			driver.microsteps(Y_MICROSTEPS);
			driver.rms_current(Y_RMS_CURRENT);
		#endif
		
		#ifdef Z_STEP_PIN
			driver.set_axis(Z_AXIS);
			driver.begin();
			driver.microsteps(Z_MICROSTEPS);
			driver.rms_current(Z_RMS_CURRENT);
		#endif
		
		#ifdef A_STEP_PIN
			driver.set_axis(A_AXIS);
			driver.begin();
			driver.microsteps(A_MICROSTEPS);
			driver.rms_current(A_RMS_CURRENT);
		#endif		
		
	#else	
		grbl_send(CLIENT_SERIAL, "[MSG: CS Multiple]\r\n");		
		driver_X.begin(); // Initiate pins and registries				
		driver_X.microsteps(X_MICROSTEPS);
		driver_X.rms_current(X_RMS_CURRENT);		
	#endif	
	
	/*
		
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
	
	*/
}
