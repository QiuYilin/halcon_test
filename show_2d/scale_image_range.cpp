///////////////////////////////////////////////////////////////////////////////
// File generated by HDevelop for HALCON/C++ Version 23.05.0.0
// Non-ASCII strings in this file are encoded in local-8-bit encoding (cp936).
// Ensure that the interface encoding is set to locale encoding by calling
// SetHcppInterfaceStringEncodingIsUtf8(false) at the beginning of the program.
// 
// Please note that non-ASCII characters in string constants are exported
// as octal codes in order to guarantee that the strings are correctly
// created on all systems, independent on any compiler settings.
// 
// Source files with different encoding should not be mixed in one project.
///////////////////////////////////////////////////////////////////////////////

#include "HalconCpp.h"
#include "HDevThread.h"



using namespace HalconCpp;


// Chapter: Filters / Arithmetic
// Short Description: Scale the gray values of an image from the interval [Min,Max] to [0,255] 
void scale_image_range (HObject ho_Image, HObject *ho_ImageScaled, HTuple hv_Min, 
    HTuple hv_Max)
{

  // Local iconic variables
  HObject  ho_ImageSelected, ho_SelectedChannel;
  HObject  ho_LowerRegion, ho_UpperRegion, ho_ImageSelectedScaled;

  // Local control variables
  HTuple  hv_LowerLimit, hv_UpperLimit, hv_Mult;
  HTuple  hv_Add, hv_NumImages, hv_ImageIndex, hv_Channels;
  HTuple  hv_ChannelIndex, hv_MinGray, hv_MaxGray, hv_Range;

  //Convenience procedure to scale the gray values of the
  //input image Image from the interval [Min,Max]
  //to the interval [0,255] (default).
  //Gray values < 0 or > 255 (after scaling) are clipped.
  //
  //If the image shall be scaled to an interval different from [0,255],
  //this can be achieved by passing tuples with 2 values [From, To]
  //as Min and Max.
  //Example:
  //scale_image_range(Image:ImageScaled:[100,50],[200,250])
  //maps the gray values of Image from the interval [100,200] to [50,250].
  //All other gray values will be clipped.
  //
  //input parameters:
  //Image: the input image
  //Min: the minimum gray value which will be mapped to 0
  //     If a tuple with two values is given, the first value will
  //     be mapped to the second value.
  //Max: The maximum gray value which will be mapped to 255
  //     If a tuple with two values is given, the first value will
  //     be mapped to the second value.
  //
  //Output parameter:
  //ImageScale: the resulting scaled image.
  //
  if (0 != (int((hv_Min.TupleLength())==2)))
  {
    hv_LowerLimit = ((const HTuple&)hv_Min)[1];
    hv_Min = ((const HTuple&)hv_Min)[0];
  }
  else
  {
    hv_LowerLimit = 0.0;
  }
  if (0 != (int((hv_Max.TupleLength())==2)))
  {
    hv_UpperLimit = ((const HTuple&)hv_Max)[1];
    hv_Max = ((const HTuple&)hv_Max)[0];
  }
  else
  {
    hv_UpperLimit = 255.0;
  }
  //
  //Calculate scaling parameters.
  //Only scale if the scaling range is not zero.
  if (0 != (HTuple(int(((hv_Max-hv_Min).TupleAbs())<1.0E-6)).TupleNot()))
  {
    hv_Mult = ((hv_UpperLimit-hv_LowerLimit).TupleReal())/(hv_Max-hv_Min);
    hv_Add = ((-hv_Mult)*hv_Min)+hv_LowerLimit;
    //Scale image.
    ScaleImage(ho_Image, &ho_Image, hv_Mult, hv_Add);
  }
  //
  //Clip gray values if necessary.
  //This must be done for each image and channel separately.
  GenEmptyObj(&(*ho_ImageScaled));
  CountObj(ho_Image, &hv_NumImages);
  {
  HTuple end_val51 = hv_NumImages;
  HTuple step_val51 = 1;
  for (hv_ImageIndex=1; hv_ImageIndex.Continue(end_val51, step_val51); hv_ImageIndex += step_val51)
  {
    SelectObj(ho_Image, &ho_ImageSelected, hv_ImageIndex);
    CountChannels(ho_ImageSelected, &hv_Channels);
    {
    HTuple end_val54 = hv_Channels;
    HTuple step_val54 = 1;
    for (hv_ChannelIndex=1; hv_ChannelIndex.Continue(end_val54, step_val54); hv_ChannelIndex += step_val54)
    {
      AccessChannel(ho_ImageSelected, &ho_SelectedChannel, hv_ChannelIndex);
      MinMaxGray(ho_SelectedChannel, ho_SelectedChannel, 0, &hv_MinGray, &hv_MaxGray, 
          &hv_Range);
      Threshold(ho_SelectedChannel, &ho_LowerRegion, (hv_MinGray.TupleConcat(hv_LowerLimit)).TupleMin(), 
          hv_LowerLimit);
      Threshold(ho_SelectedChannel, &ho_UpperRegion, hv_UpperLimit, (hv_UpperLimit.TupleConcat(hv_MaxGray)).TupleMax());
      PaintRegion(ho_LowerRegion, ho_SelectedChannel, &ho_SelectedChannel, hv_LowerLimit, 
          "fill");
      PaintRegion(ho_UpperRegion, ho_SelectedChannel, &ho_SelectedChannel, hv_UpperLimit, 
          "fill");
      if (0 != (int(hv_ChannelIndex==1)))
      {
        CopyObj(ho_SelectedChannel, &ho_ImageSelectedScaled, 1, 1);
      }
      else
      {
        AppendChannel(ho_ImageSelectedScaled, ho_SelectedChannel, &ho_ImageSelectedScaled
            );
      }
    }
    }
    ConcatObj((*ho_ImageScaled), ho_ImageSelectedScaled, &(*ho_ImageScaled));
  }
  }
  return;
}
