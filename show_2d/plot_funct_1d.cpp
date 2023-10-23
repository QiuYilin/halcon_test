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

extern void plot_tuple (HTuple hv_WindowHandle, HTuple hv_XValues, HTuple hv_YValues, 
    HTuple hv_XLabel, HTuple hv_YLabel, HTuple hv_Color, HTuple hv_GenParamName, 
    HTuple hv_GenParamValue);


// Chapter: Graphics / Output
// Short Description: Plot tuples representing functions or curves in a coordinate system. 
void plot_funct_1d (HTuple hv_WindowHandle, HTuple hv_Function, HTuple hv_XLabel, 
    HTuple hv_YLabel, HTuple hv_Color, HTuple hv_GenParamName, HTuple hv_GenParamValue)
{

  // Local control variables
  HTuple  hv_XValues, hv_YValues;

  //This procedure plots a function in a coordinate system.
  //
  //Input parameters:
  //
  //Function: 1D function
  //
  //XLabel: X-axis label
  //
  //YLabel: Y-axis label
  //
  //Color: Color of the plotted function
  //       If [] is given, the currently set display color is used.
  //       If 'none is given, the function is not plotted, but only
  //       the coordinate axes as specified.
  //
  //GenParamName:  Generic parameters to control the presentation
  //               The parameters are evaluated from left to right.
  //
  //               Possible Values:
  //   'axes_color': coordinate system color
  //                 Default: 'white'
  //                 If 'none' is given, no coordinate system is shown.
  //   'style': Graph style
  //            Possible values: 'line' (default), 'cross', 'step', 'filled'
  //   'clip': Clip graph to coordinate system area
  //           Possible values: 'yes' (default), 'no'
  //   'ticks': Control display of ticks on the axes
  //            If 'min_max_origin' is given (default), ticks are shown
  //            at the minimum and maximum values of the axes and at the
  //            intercept point of x- and y-axis.
  //            If 'none' is given, no ticks are shown.
  //            If any number != 0 is given, it is interpreted as distance
  //            between the ticks.
  //   'ticks_x': Control display of ticks on x-axis only
  //   'ticks_y': Control display of ticks on y-axis only
  //   'format_x': Format of the values next to the ticks of the x-axis
  //               (see tuple_string for more details).
  //   'format_y': Format of the values next to the ticks of the y-axis
  //               (see tuple_string for more details).
  //   'grid': Control display of grid lines within the coordinate system
  //           If 'min_max_origin' is given (default), grid lines are shown
  //           at the minimum and maximum values of the axes.
  //           If 'none' is given, no grid lines are shown.
  //           If any number != 0 is given, it is interpreted as distance
  //           between the grid lines.
  //   'grid_x': Control display of grid lines for the x-axis only
  //   'grid_y': Control display of grid lines for the y-axis only
  //   'grid_color': Color of the grid (default: 'dim gray')
  //   'margin': The distance in pixels of the coordinate system area
  //             to all four window borders.
  //   'margin_left': The distance in pixels of the coordinate system area
  //                  to the left window border.
  //   'margin_right': The distance in pixels of the coordinate system area
  //                   to the right window border.
  //   'margin_top': The distance in pixels of the coordinate system area
  //                 to the upper window border.
  //   'margin_bottom': The distance in pixels of the coordinate system area
  //                    to the lower window border.
  //   'start_x': Lowest x value of the x-axis
  //              Default: min(XValues)
  //   'end_x': Highest x value of the x-axis
  //            Default: max(XValues)
  //   'start_y': Lowest y value of the y-axis
  //              Default: min(YValues)
  //   'end_y': Highest y value of the y-axis
  //            Default: max(YValues)
  //   'axis_location_x': Either 'bottom', 'origin', or 'top'
  //               to position the x-axis conveniently,
  //               or the Y coordinate of the intercept point of x- and y-axis.
  //               Default: 'bottom'
  //               (Used to be called 'origin_y')
  //   'axis_location_y': Either 'left', 'origin', or 'right'
  //               to position the y-axis conveniently,
  //               or the X coordinate of the intercept point of x- and y-axis.
  //               Default: 'left'
  //               (Used to be called 'origin_x')
  //
  //GenParamValue: Values of the generic parameters of GenericParamName
  //
  //
  Funct1dToPairs(hv_Function, &hv_XValues, &hv_YValues);
  plot_tuple(hv_WindowHandle, hv_XValues, hv_YValues, hv_XLabel, hv_YLabel, hv_Color, 
      hv_GenParamName, hv_GenParamValue);
  return;
}
