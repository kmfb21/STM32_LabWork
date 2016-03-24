/* main.c ---
 *
 * Filename: main.c
 * Description:lab9
 * Author:gaoyu and bofang
 * Created: 3/23/2016
 * Date Last Modified: 3/24/2016
 /* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_nunchuk.h>
#include <stdio.h>
#include <math.h>

#define TIMER 20000



int main(void) {
  f3d_uart_init();
  f3d_gyro_init();
  f3d_lcd_init();
  f3d_lcd_fillScreen(WHITE); //set background  
  f3d_led_init();
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  f3d_nunchuk_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  float pitch, roll, pitchN, rollN, magy2, magx2, heading;
  int toggle = 0; //for switching between representations
  int pos, i;
  char tempPitch[10];
  char tempRoll[10];
  char tempHeading[10];
  char tempPitchN[10];
  char tempRollN[10];

  nunchuk_t n;  

  float accel_data[3];
  float mag_data[3];
  double accel_pitch, accel_pitch_deg;
  double accel_roll, accel_roll_deg;
  double mag_heading, mag_heading_deg;
  float val[3];
  
while(1) {

    f3d_nunchuk_read(&n);
    
    if (n.jx > 180 || n.c == 1) {
      f3d_lcd_fillScreen(WHITE); //reset screen each time
      delay(100);
      if (toggle < 3) {
        toggle++;
      }
      else toggle = 0;
    }
    else if (n.jx < 60 || n.z == 1) {
      f3d_lcd_fillScreen(WHITE); //reset screen each time
      delay(100);
      if (toggle == 0) {
	toggle = 3;
      }
      else toggle--;
    }

    if (toggle == 0) {

      f3d_lcd_drawString(20, 10, "stm32_pitch&roll", GREEN, WHITE);
      char pitch[20], roll[20];
      f3d_accel_read(accel_data);

      accel_pitch = atan2( accel_data[0], sqrt(pow(accel_data[1], 2) + pow(accel_data[2], 2)));
      accel_pitch_deg = (180/M_PI) * accel_pitch;
      accel_roll = atan2( accel_data[1], sqrt(pow(accel_data[0], 2) + pow(accel_data[2], 2)));
      accel_roll_deg = (180/M_PI) * accel_roll;
       
      snprintf(pitch, 20, "Pitch: %f", accel_pitch_deg);
      snprintf(roll, 20, "Roll: %f", accel_roll_deg);
     
      f3d_lcd_drawString(0, 40, pitch, BLACK, WHITE);
      f3d_lcd_drawString(0, 50, roll, BLACK, WHITE);

      int X,Y,oldX,oldY;
      X=50+accel_roll_deg;
      Y=100+accel_pitch_deg;
      f3d_lcd_drawString(oldX,oldY,"O",WHITE,WHITE);
      f3d_lcd_drawString(50,100, "o", BLACK, WHITE);
      f3d_lcd_drawString(X,Y,"O",BLACK,WHITE);
      oldX=X,oldY=Y;
    }
    if (toggle == 1) {
	f3d_lcd_drawString(20, 10, "Compass", GREEN, WHITE);
      char heading[20];
      f3d_mag_read(mag_data);

      mag_heading = atan2(mag_data[1], mag_data[0]);
      mag_heading_deg = (180/M_PI) * mag_heading;

      //calibrate compass heading
      mag_heading_deg -= 160; 
      if (mag_heading_deg < 0) {
	mag_heading_deg = -mag_heading_deg;
	mag_heading_deg = 360 - mag_heading_deg;
      }

      snprintf(heading, 20, "Heading: %f\n", mag_heading_deg);       
      f3d_lcd_drawString(0, 20, heading, BLACK, WHITE);
	
      int X,Y,oldX,oldY;
      X=50+200*mag_data[1];
      Y=100+200*mag_data[0];
      f3d_lcd_drawString(oldX,oldY,"N",WHITE,WHITE);
      f3d_lcd_drawString(50,100, "o", BLACK, WHITE);
      f3d_lcd_drawString(X,Y,"N",BLACK,WHITE);
      oldX=X,oldY=Y;
    }
    if (toggle == 2) {
	f3d_lcd_drawString(20, 10, "Gyro", GREEN, WHITE);
      f3d_gyro_getdata(val);
    
    //Strings for text values printed on lcd
    char xaxis[20];
    sprintf(xaxis, "X-Axis: %f", val[0]);
    char yaxis[20];
    sprintf(yaxis, "Y-Axis: %f", val[1]);
    char zaxis[20];
    sprintf(zaxis, "Z-Axis: %f", val[2]);
    
    
    //draw string for x-axis
    f3d_lcd_drawString(10, 20, xaxis, BLACK, WHITE);
    //clear any previous rectangle with white rectangle
    f3d_lcd_drawRectangle(WHITE, 10, 35, 125, 45);
    //based on x-axis value, create a green rectangle for a positive value
    //and a red rectangle for negative values
     if(val[0] > 300){
      f3d_lcd_drawRectangle(GREEN, 10, 35, 125, 45);
    } else if (val[0] > 200) {
      f3d_lcd_drawRectangle(GREEN, 10, 35, 100, 45);
    } else if (val[0] > 100) {
      f3d_lcd_drawRectangle(GREEN, 10, 35, 75, 45);
    } else if (val[0] > 5) {
      f3d_lcd_drawRectangle(GREEN, 10, 35, 50, 45);
    } else if (val[0] < -300) {
      f3d_lcd_drawRectangle(RED, 10, 35, 125, 45);
    }  else if (val[0] < -200) {
      f3d_lcd_drawRectangle(RED, 10, 35, 100, 45);
    } else if (val[0] < -100) {
      f3d_lcd_drawRectangle(RED, 10, 35, 75, 45);
    }  else if (val[0] < -5) {
      f3d_lcd_drawRectangle(RED, 10, 35, 50, 45);
     }

     //same process as the x-axis for y-axis
     f3d_lcd_drawString(10, 50, yaxis, BLACK, WHITE);
     f3d_lcd_drawRectangle(WHITE, 10, 65, 125, 75);
     if(val[1] > 300){
      f3d_lcd_drawRectangle(GREEN, 10, 65, 125, 75);
    } else if (val[1] > 200) {
      f3d_lcd_drawRectangle(GREEN, 10, 65, 100, 75);
    } else if (val[1] > 100) {
      f3d_lcd_drawRectangle(GREEN, 10, 65, 75, 75);
    } else if (val[1] > 5) {
      f3d_lcd_drawRectangle(GREEN, 10, 65, 50, 75);
    } else if (val[1] < -300) {
      f3d_lcd_drawRectangle(RED, 10, 65, 125, 75);
    }  else if (val[1] < -200) {
      f3d_lcd_drawRectangle(RED, 10, 65, 100, 75);
    } else if (val[1] < -100) {
      f3d_lcd_drawRectangle(RED, 10, 65, 75, 75);
    }  else if (val[1] < -5) {
      f3d_lcd_drawRectangle(RED, 10, 65, 50, 75);
     }
    
     //same process as x and y-axis for z-axis
     f3d_lcd_drawString(10, 80, zaxis, BLACK, WHITE);
     f3d_lcd_drawRectangle(WHITE, 10, 95, 125, 105);
     if(val[2] > 300){
      f3d_lcd_drawRectangle(GREEN, 10, 95, 125, 105);
    } else if (val[2] > 200) {
      f3d_lcd_drawRectangle(GREEN, 10, 95, 100, 105);
    } else if (val[2] > 100) {
      f3d_lcd_drawRectangle(GREEN, 10, 95, 75, 105);
    } else if (val[2] > 5) {
      f3d_lcd_drawRectangle(GREEN, 10, 95, 50, 105);
    } else if (val[2] < -300) {
      f3d_lcd_drawRectangle(RED, 10, 95, 125, 105);
    }  else if (val[2] < -200) {
      f3d_lcd_drawRectangle(RED, 10, 95, 100, 105);
    } else if (val[2] < -100) {
      f3d_lcd_drawRectangle(RED, 10, 95, 75, 105);
    }  else if (val[2] < -5) {
      f3d_lcd_drawRectangle(RED, 10, 95, 50, 105);
     }
  }
    
    if (toggle == 3) {
f3d_lcd_drawString(20, 10, "Nunchuk_pith&roll", GREEN, WHITE);
      char pitch[20], roll[20];

      accel_data[0]= atan2(n.ax, sqrt((pow(n.ay, 2) + (pow(n.ay, 2)))));
      accel_data[1] = atan2(n.ay, sqrt((pow(n.ax, 2) + (pow(n.az, 2)))));

      accel_pitch = atan2( accel_data[0], sqrt(pow(accel_data[1], 2) + pow(accel_data[2], 2)));
      accel_pitch_deg = (180/M_PI) * accel_pitch;
      accel_roll = atan2( accel_data[1], sqrt(pow(accel_data[0], 2) + pow(accel_data[2], 2)));
      accel_roll_deg = (180/M_PI) * accel_roll;
       
      snprintf(pitch, 20, "Pitch: %f", accel_pitch_deg);
      snprintf(roll, 20, "Roll: %f", accel_roll_deg);
     
      f3d_lcd_drawString(0, 40, pitch, BLACK, WHITE);
      f3d_lcd_drawString(0, 50, roll, BLACK, WHITE);

      int X,Y,oldX,oldY;
      X=50+accel_roll_deg;
      Y=100+accel_pitch_deg;
      f3d_lcd_drawString(oldX,oldY,"O",WHITE,WHITE);
      f3d_lcd_drawString(50,100, "o", BLACK, WHITE);
      f3d_lcd_drawString(X,Y,"O",BLACK,WHITE);
      oldX=X,oldY=Y;
    }
  }




}



#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
