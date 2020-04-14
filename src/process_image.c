#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "image.h"

float get_pixel(image im, int x, int y, int c)
{
    // TODO Fill this in
    int col = ((0 > x) ? 0 : ((im.w <= x) ? im.w-1 : x));
    int row = ((0 > y) ? 0 : ((im.h <= y) ? im.h-1 : y));
    int chn = ((0 > c) ? 0 : ((im.c <= c) ? im.c-1 : c));  
    return im.data[col+(row*im.w)+(chn*im.h*im.w)];
}

void set_pixel(image im, int x, int y, int c, float v)
{
    if( 0<=x && x<im.w && 0<=y && y<im.h && 0<=c && c<im.c){
        im.data[x+(y*im.w)+(c*im.w*im.h)]=v;
    }
    // TODO Fill this in
}

image copy_image(image im)
{
    image copy = make_image(im.w, im.h, im.c);
    // TODO Fill this in
    for(int it = 0; it<im.w*im.h*im.c; it++){
        copy.data[it] = im.data[it];
    }
    return copy;
}

image rgb_to_grayscale(image im)
{
    assert(im.c == 3);
    image gray = make_image(im.w, im.h, 1);
    for(int it = 0; it<im.w*im.h; it++){
        // luma calculations https://en.wikipedia.org/wiki/Luma_(video)
        gray.data[it] = 0.299*im.data[it] +0.587*im.data[it+(im.w*im.h)] + 0.114*im.data[it+(2*im.w*im.h)];
    }
    // TODO Fill this in
    return gray;
}

void shift_image(image im, int c, float v)
{
    if(0<=c && c<im.c){
        for(int it = 0; it<im.w*im.h; it++){
            im.data[it+(c*im.w*im.h)] +=v;
        }
    }
    // TODO Fill this in
}

void clamp_image(image im)
{
    for(int it = 0; it<im.w*im.h*im.c; it++){
            im.data[it] = 0 > im.data[it] ? 0 :(im.data[it] <= 1 ? im.data[it] : 1);
    }
    // TODO Fill this in
}


// These might be handy
float three_way_max(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? a : c) : ( (b > c) ? b : c) ;
}

float three_way_max_chn(float a, float b, float c)
{
    return (a > b) ? ( (a > c) ? 0 : 2) : ( (b > c) ? 1 : 2) ;
}


float three_way_min(float a, float b, float c)
{
    return (a < b) ? ( (a < c) ? a : c) : ( (b < c) ? b : c) ;
}

void rgb_to_hsv(image im)
{
    // TODO Fill this in
    for(int it = 0 ; it < im.h*im.w ; it++){
        int value_chn = three_way_max_chn(im.data[it],im.data[it+(im.h*im.w)],im.data[it+(im.h*im.w*2)]);
        float V = im.data[it+(value_chn*im.h*im.w)];
        float min = three_way_min(im.data[it],im.data[it+(im.h*im.w)],im.data[it+(im.h*im.w*2)]);
        float C = (V - min);
        float S = C/V;

        float Hprime =  0;
        float H =  0;

        // if C != 0 then check blue (value channel 2) if not then check other channels
        if(C == 0) H = 0;
        else if(value_chn == 2) Hprime = ((im.data[it+(value_chn*im.h*im.w)] - im.data[it+(0*im.h*im.w)])/C) + value_chn*2; 
        else Hprime = ((im.data[it+(value_chn*im.h*im.w)] - im.data[it+(value_chn+1*im.h*im.w)])/C) + value_chn*2; 

        if(Hprime<0) H=(Hprime/6) +1;
        else  H=(Hprime/6);

        // if(H<0)H=1;
        // if(H>1)H=0;
        // replacing RGB with HSV
        im.data[it] = H;
        im.data[it+(im.h*im.w)] = S;
        im.data[it+(im.h*im.w*2)] = V;
    }
}

void hsv_to_rgb(image im)
{
    // TODO Fill this in
}
