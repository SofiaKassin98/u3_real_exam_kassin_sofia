#include <webots/robot.h>
#include <stdio.h>
#include "shoot.h"

float gun(float shut) {
  if (shut<2 && shut>1.5) {
    printf("tha\n");
  }
  if (shut<1.4 && shut>0.8) {
    printf("tha tha tha\n");
  }
  if (shut<0.7 && shut>0.01) {
    printf("tha tha tha tha tha tha\n");
  }

  return shut;
}
