/*
 * Copyright (C) 2007 Giacomo Spigler
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

extern "C" {

  __global__ void FragmentProgram(int w, int h, unsigned char *in, unsigned char *out) {
    int i=0;

    for(i=threadIdx.x+blockIdx.x*blockDim.x; i<w*h; i+=blockDim.x*gridDim.x) {
      if(in[i*3]>=200) {
        //out[i*3]=255;
        //out[i*3+1]=255;
        //out[i*3+2]=255;
      } else {
        out[i*3]=0;
        out[i*3+1]=0;
        out[i*3+2]=0;
      }
    }
  }

}


