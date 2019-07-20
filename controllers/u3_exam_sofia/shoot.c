#include <webots/robot.h>
#include <stdio.h>
#include "shoot.h"

float gun(float a) {
  if (a<2 && a>1.5) {
    printf("tha\n");
  }
  if (a<1.4 && a>0.8) {
    printf("tha tha tha\n");
  }
  if (a<0.7 && a>0.01) {
    printf("tha tha tha tha tha tha\n");
  }

  return a;
}
