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
// Short Description: Write one or multiple text messages. 
void disp_message (HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem, 
    HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_GenParamName, hv_GenParamValue;

  //This procedure displays text in a graphics window.
  //
  //Input parameters:
  //WindowHandle: The WindowHandle of the graphics window, where
  //   the message should be displayed.
  //String: A tuple of strings containing the text messages to be displayed.
  //CoordSystem: If set to 'window', the text position is given
  //   with respect to the window coordinate system.
  //   If set to 'image', image coordinates are used.
  //   (This may be useful in zoomed images.)
  //Row: The row coordinate of the desired text position.
  //   You can pass a single value or a tuple of values.
  //   See the explanation below.
  //   Default: 12.
  //Column: The column coordinate of the desired text position.
  //   You can pass a single value or a tuple of values.
  //   See the explanation below.
  //   Default: 12.
  //Color: defines the color of the text as string.
  //   If set to [] or '' the currently set color is used.
  //   If a tuple of strings is passed, the colors are used cyclically
  //   for every text position defined by Row and Column,
  //   or every new text line in case of |Row| == |Column| == 1.
  //Box: A tuple controlling a possible box surrounding the text.
  //   Its entries:
  //   - Box[0]: Controls the box and its color. Possible values:
  //     -- 'true' (Default): An orange box is displayed.
  //     -- 'false': No box is displayed.
  //     -- color string: A box is displayed in the given color, e.g., 'white', '#FF00CC'.
  //   - Box[1] (Optional): Controls the shadow of the box. Possible values:
  //     -- 'true' (Default): A shadow is displayed in
  //               darker orange if Box[0] is not a color and in 'white' otherwise.
  //     -- 'false': No shadow is displayed.
  //     -- color string: A shadow is displayed in the given color, e.g., 'white', '#FF00CC'.
  //
  //It is possible to display multiple text strings in a single call.
  //In this case, some restrictions apply on the
  //parameters String, Row, and Column:
  //They can only have either 1 entry or n entries.
  //Behavior in the different cases:
  //   - Multiple text positions are specified, i.e.,
  //       - |Row| == n, |Column| == n
  //       - |Row| == n, |Column| == 1
  //       - |Row| == 1, |Column| == n
  //     In this case we distinguish:
  //       - |String| == n: Each element of String is displayed
  //                        at the corresponding position.
  //       - |String| == 1: String is displayed n times
  //                        at the corresponding positions.
  //   - Exactly one text position is specified,
  //      i.e., |Row| == |Column| == 1:
  //      Each element of String is display in a new textline.
  //
  //
  //Convert the parameters for disp_text.
  if (0 != (HTuple(int(hv_Row==HTuple())).TupleOr(int(hv_Column==HTuple()))))
  {
    return;
  }
  if (0 != (int(hv_Row==-1)))
  {
    hv_Row = 12;
  }
  if (0 != (int(hv_Column==-1)))
  {
    hv_Column = 12;
  }
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
  //Restore default CoordSystem behavior.
  if (0 != (int(hv_CoordSystem!=HTuple("window"))))
  {
    hv_CoordSystem = "image";
  }
  //
  if (0 != (int(hv_Color==HTuple(""))))
  {
    //disp_text does not accept an empty string for Color.
    hv_Color = HTuple();
  }
  //
  DispText(hv_WindowHandle, hv_String, hv_CoordSystem, hv_Row, hv_Column, hv_Color, 
      hv_GenParamName, hv_GenParamValue);
  return;
}
