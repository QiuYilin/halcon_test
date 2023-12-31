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


// Chapter: Graphics / Text
// Short Description: Display 'End of program' in the lower right corner of the screen. 
void disp_end_of_program_message (HTuple hv_WindowHandle, HTuple hv_Color, HTuple hv_Box)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_GenParamName, hv_GenParamValue, hv_EndMessage;

  //This procedure displays 'End of program' in the
  //lower right corner of the screen.
  //It uses the procedure disp_message.
  //
  //Input parameters:
  //WindowHandle: The window, where the text shall be displayed
  //Color: defines the text color.
  //   If set to '' or 'auto', the currently set color is used.
  //Box: If set to 'true', the text is displayed in a box.
  //
  //Convert the parameter Box to generic parameters.
  hv_GenParamName = HTuple();
  hv_GenParamValue = HTuple();
  if (0 != (int((hv_Box.TupleLength())>0)))
  {
    if (0 != (int(HTuple(hv_Box[0])==HTuple("false"))))
    {
      //Display no box
      hv_GenParamName = hv_GenParamName.TupleConcat("box");
      hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
    }
    else if (0 != (int(HTuple(hv_Box[0])!=HTuple("true"))))
    {
      //Set a color other than the default.
      hv_GenParamName = hv_GenParamName.TupleConcat("box_color");
      hv_GenParamValue = hv_GenParamValue.TupleConcat(HTuple(hv_Box[0]));
    }
  }
  if (0 != (int((hv_Box.TupleLength())>1)))
  {
    if (0 != (int(HTuple(hv_Box[1])==HTuple("false"))))
    {
      //Display no shadow.
      hv_GenParamName = hv_GenParamName.TupleConcat("shadow");
      hv_GenParamValue = hv_GenParamValue.TupleConcat("false");
    }
    else if (0 != (int(HTuple(hv_Box[1])!=HTuple("true"))))
    {
      //Set a shadow color other than the default.
      hv_GenParamName = hv_GenParamName.TupleConcat("shadow_color");
      hv_GenParamValue = hv_GenParamValue.TupleConcat(HTuple(hv_Box[1]));
    }
  }
  //
  if (0 != (int(hv_Color==HTuple(""))))
  {
    //disp_text does not accept an empty string for Color.
    hv_Color = HTuple();
  }
  //
  //Display the message.
  hv_EndMessage = "      End of program      ";
  DispText(hv_WindowHandle, hv_EndMessage, "window", "bottom", "right", hv_Color, 
      hv_GenParamName, hv_GenParamValue);
  return;
}
