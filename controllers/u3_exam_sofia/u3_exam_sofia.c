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

#define TIME_STEP 64
#define PI 3.1416

enum {
  GO,
  ENEMY,
  FREEWAY,
  OBSTACLE
};

int h;
float b, c;
short int robot_state;

int checkForObstacles(WbDeviceTag distance_sensor) {
  double distance = wb_distance_sensor_get_value(distance_sensor);

  if (distance > 0.2)
    return FREEWAY;
  else
    return OBSTACLE;
}

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
  wb_motor_set_velocity(wheel_right,4);
  wb_motor_set_velocity(wheel_left, -2);
  wb_motor_set_velocity(wheel_right2, 4);
  wb_motor_set_velocity(wheel_left2, -2);
}

void radarOn(WbDeviceTag radar_motor) {
  wb_motor_set_position(radar_motor, INFINITY);
  wb_motor_set_velocity(radar_motor,0.4);
}

void stopRadar(WbDeviceTag radar_motor) {
  wb_motor_set_position(radar_motor, INFINITY);
  wb_motor_set_velocity(radar_motor,0);
}

void gunOn(WbDeviceTag gun_motor, float b) {
  wb_motor_set_position(gun_motor, b);
  wb_motor_set_velocity(gun_motor,0.3);
}

void shoot(float a) {
  if (a<2 && a>1.5) {
    printf("tha\n");
  }
  if (a<1.4 && a>0.8) {
    printf("tha tha tha\n");
  }
  if (a<0.7 && a>0.01) {
    printf("tha tha tha tha tha tha\n");
  }
}

int main(int argc, char **argv)
{
  wb_robot_init();

   WbDeviceTag wheel_right = wb_robot_get_device("motor_right");
   WbDeviceTag wheel_left = wb_robot_get_device("motor_left");
   WbDeviceTag wheel_right2 = wb_robot_get_device("motor_right2");
   WbDeviceTag wheel_left2 = wb_robot_get_device("motor_left2");
   WbDeviceTag radar_motor = wb_robot_get_device("rotational_motor");
   WbDeviceTag gun_motor = wb_robot_get_device("rotational_gun");


   /////////position sensor//////////
   WbDeviceTag ps_left = wb_robot_get_device("position_left");
   WbDeviceTag ps_right = wb_robot_get_device("position_right");
   WbDeviceTag radar_pos = wb_robot_get_device("position_sensor");
   wb_position_sensor_enable(ps_left, TIME_STEP);
   wb_position_sensor_enable(ps_right, TIME_STEP);
   wb_position_sensor_enable(radar_pos, TIME_STEP);

   ///////////distance sensor/////////
   WbDeviceTag ds_r = wb_robot_get_device("distance_sensor");
   wb_distance_sensor_enable(ds_r, TIME_STEP);
   WbDeviceTag radar_sen = wb_robot_get_device("distance_sensor2");
   wb_distance_sensor_enable(radar_sen, TIME_STEP);
   WbDeviceTag gun_sen = wb_robot_get_device("gun_sensor");
   wb_distance_sensor_enable(gun_sen, TIME_STEP);


  /////////variables para el encoder///
  //double pos_final, pos_final1;
  double  a,a1;

  while (wb_robot_step(TIME_STEP) != -1) {

  goRobot(wheel_left,wheel_left2,wheel_right,wheel_right2);
  radarOn(radar_motor);

  a1 = ((wb_distance_sensor_get_value(ds_r)*0.4)/255);
  if (a1<=0.35 ||  (h<=50&&h>=1)) {
    h++;
    turnLeft(wheel_left,wheel_left2,wheel_right,wheel_right2);
    printf("L: %f RPM\n",a1);
  }
  else {
    h=0;
  }

  a = ((wb_distance_sensor_get_value(radar_sen)*2)/1023);
  if (a<2 || robot_state==ENEMY) {
    robot_state=ENEMY;
    stopRobot(wheel_left,wheel_left2,wheel_right,wheel_right2);
    stopRadar(radar_motor);
    b=wb_position_sensor_get_value(radar_pos);
  }

  c = ((wb_distance_sensor_get_value(gun_sen)*0.4)/255);
  if (robot_state==ENEMY) {
    gunOn(gun_motor,b);
    shoot(gun_sen);
  }


  };

  wb_robot_cleanup();

  return 0;
}
