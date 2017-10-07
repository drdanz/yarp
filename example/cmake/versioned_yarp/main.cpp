
/*
 * Copyright: (C) 2011 RobotCub Consortium
 * Author: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#include <stdio.h>
#include <yarp/os/all.h>

int main() {
  printf("Hello from YARP [dramatic pause]\n");
  yarp::os::Time::delay(5);
  printf("[/dramatic pause]\n");
  return 0;
}
