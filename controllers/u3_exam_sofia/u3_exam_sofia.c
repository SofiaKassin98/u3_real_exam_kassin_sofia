/*
 * File:          exsm_sofia
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/differential_wheels.h>, etc.
 */
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/position_sensor.h>
#include <webots/keyboard.h>

#include <stdio.h>

/*
 * You may want to add macros here.
 */
#define TIME_STEP 64
#define PI 3.1416

double b=0;
double b1=0;

void goRobot(WbDeviceTag wheel_left,WbDeviceTag wheel_left2,
             WbDeviceTag wheel_right,WbDeviceTag wheel_right2) {
  wb_motor_set_position(wheel_right, INFINITY);
  wb_motor_set_velocity(wheel_right, -2);
  wb_motor_set_position(wheel_left, INFINITY);
  wb_motor_set_velocity(wheel_left, -2);
  wb_motor_set_position(wheel_right2, INFINITY);
  wb_motor_set_velocity(wheel_right2, -2);
  wb_motor_set_position(wheel_left2, INFINITY);
  wb_motor_set_velocity(wheel_left2, -2);
}

void stopRobot(WbDeviceTag wheel_left,WbDeviceTag wheel_left2,
               WbDeviceTag wheel_right,WbDeviceTag wheel_right2) {
  wb_motor_set_velocity(wheel_right, 0);
  wb_motor_set_velocity(wheel_left, 0);
  wb_motor_set_velocity(wheel_right2, 0);
  wb_motor_set_velocity(wheel_left2, 0);
}

void turnLeft(WbDeviceTag wheel_left,WbDeviceTag wheel_left2,
               WbDeviceTag wheel_right,WbDeviceTag wheel_right2) {
  wb_motor_set_position(wheel_right, INFINITY);
  wb_motor_set_velocity(wheel_right,-2);
  wb_motor_set_position(wheel_left, INFINITY);
  wb_motor_set_velocity(wheel_left, 4);
  wb_motor_set_position(wheel_right2, INFINITY);
  wb_motor_set_velocity(wheel_right2, -2);
  wb_motor_set_position(wheel_left2, INFINITY);
  wb_motor_set_velocity(wheel_left2, 4);
}

int main(int argc, char **argv)
{
  wb_robot_init();

   WbDeviceTag wheel_right = wb_robot_get_device("motor_right");
   WbDeviceTag wheel_left = wb_robot_get_device("motor_left");
   WbDeviceTag wheel_right2 = wb_robot_get_device("motor_right2");
   WbDeviceTag wheel_left2 = wb_robot_get_device("motor_left2");
   WbDeviceTag  radar_motor = wb_robot_get_device("rotational_motor");
   WbDeviceTag gun_motor = wb_robot_get_device("rotational_gun");


   /////////position sensor//////////
   WbDeviceTag ps_left = wb_robot_get_device("position_left");
   WbDeviceTag ps_right = wb_robot_get_device("position_right");
   wb_position_sensor_enable(ps_left, TIME_STEP);
   wb_position_sensor_enable(ps_right, TIME_STEP);

   ///////////distance sensor/////////
   WbDeviceTag ds_r = wb_robot_get_device("distance_sensor");
   wb_distance_sensor_enable(ds_r, TIME_STEP);

   ////////activacion del teclado//
   wb_keyboard_enable(TIME_STEP);

  /////////variables para el encoder///
  //double pos_final, pos_final1;
  double  a1;

  while (wb_robot_step(TIME_STEP) != -1) {

  a1 = ((wb_distance_sensor_get_value(ds_r)*0.4)/255);
  goRobot(wheel_left,wheel_left2,wheel_right,wheel_right2);



    if (a1<=0.3) {
      turnLeft(wheel_left,wheel_left2,wheel_right,wheel_right2);
    }


     printf("Left velocity: %f RPM\n",a1);

  };

  wb_robot_cleanup();

  return 0;
}
