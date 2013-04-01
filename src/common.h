#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include "types.h"
#include "Mat2.h"

// has an additional column at the end with random data
inline
Mat2<float3> diffX(Mat2<float3> input)
{
    const uint W = input.width;
    const uint H = input.height;

    Mat2<float3> output(W,H);

    for (uint i=0; i<H; i++)
    {
        for (uint j=0; j<W-1; j++)
        {
            uint idx = i*W + j;
            output.data[idx].r = input.data[idx+1].r - input.data[idx].r;
            output.data[idx].g = input.data[idx+1].g - input.data[idx].g;
            output.data[idx].b = input.data[idx+1].b - input.data[idx].b;
        }
    }

    return output;
}

// has an additional column at the end with random data
inline
Mat2<float3> diffY(Mat2<float3> input)
{
    const uint W = input.width;
    const uint H = input.height;

    Mat2<float3> output(W,H);

    for (uint i=0; i<H-1; i++)
    {
        for (uint j=0; j<W; j++)
        {
            uint idx = i*W + j;
            output.data[idx].r = input.data[idx+W].r - input.data[idx].r;
            output.data[idx].g = input.data[idx+W].g - input.data[idx].g;
            output.data[idx].b = input.data[idx+W].b - input.data[idx].b;
        }
    }

    return output;
}

/** In place cumulative sum along width/X/rows **/
inline
void cumsumX(Mat2<float> img)
{
    uint H = img.height;
    uint W = img.width;
    for (uint i=0; i<H; i++)
    {
        float sum = 0;
        for (uint j=0; j<W; j++)
        {
            uint idx = i*W + j;
            sum += img.data[idx];
            img.data[idx] = sum;
        }
    }
}

/** In place cumulative sum along height/Y/cols **/
inline
void cumsumY(Mat2<float> img)
{
    uint H = img.height;
    uint W = img.width;
    for (uint j=0; j<W; j++)
    {
        float sum = 0;
        for (uint i=0; i<H; i++)
        {
            uint idx = i*W + j;
            sum += img.data[idx];
            img.data[idx] = sum;
        }
    }
}

inline
Mat2<float> transposed(Mat2<float> in)
{
    Mat2<float> out(in.width,in.height);
    uint H = in.height;
    uint W = in.width;
    for (uint i=0; i<in.height; i++)
    {
        for (uint j=0; j<in.width; j++)
        {
            uint idx = i*W + j;
            uint idxT = j*W + i;
            out.data[idxT] = in.data[idx];
        }
    }
    return out;
}

// please recheck this function
inline
void transpose(Mat2<float3> in)
{
    uint H = in.height;
    uint W = in.width;
    for (uint i=1; i<in.height; i++) // start with index 1
    {
        for (uint j=i; j<in.width; j++)
        {
            uint idx = i*W + j;
            uint idxT = j*W + i;
            float3 tmp = in.data[idx];
            in.data[idx] = in.data[idxT];
            in.data[idxT] = tmp;
        }
    }
    in.height = W;
    in.width = H;
}

inline
void transpose(Mat2<float> in)
{
    uint H = in.height;
    uint W = in.width;
    for (uint i=1; i<in.height; i++) // start with index 1
    {
        for (uint j=i; j<in.width; j++)
        {
            uint idx = i*W + j;
            uint idxT = j*W + i;
            float tmp = in.data[idx];
            in.data[idx] = in.data[idxT];
            in.data[idxT] = tmp;
        }
    }
    in.height = W;
    in.width = H;
}

inline
Mat2<float3> transposed(Mat2<float3> in)
{
    Mat2<float3> out(in.width,in.height);
    uint H = in.height;
    uint W = in.width;
    for (uint i=0; i<in.height; i++)
    {
        for (uint j=0; j<in.width; j++)
        {
            uint idx = i*W + j;
            uint idxT = j*W + i;
            out.data[idxT].r = in.data[idx].r;
            out.data[idxT].g = in.data[idx].g;
            out.data[idxT].b = in.data[idx].b;
        }
    }
    return out;
}



#endif // COMMON_H
