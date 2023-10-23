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


// Chapter: Graphics / Window
// Short Description: Close all window handles contained in a dictionary. 
void dev_close_window_dict (HTuple hv_WindowHandleDict)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_WindowHandleDicts, hv_WindowDictIdx;
  HTuple  hv_WindowHandleKeys, hv_Index, hv_WindowHandles;
  HTuple  hv_Exception, hv_RemovedWindowIndices, hv_WindowHandleIndex;

  //
  //This procedure closes all window handles
  //that are contained in the dictionary WindowHandleDict.
  //
  hv_WindowHandleDicts = hv_WindowHandleDict;
  {
  HTuple end_val5 = (hv_WindowHandleDicts.TupleLength())-1;
  HTuple step_val5 = 1;
  for (hv_WindowDictIdx=0; hv_WindowDictIdx.Continue(end_val5, step_val5); hv_WindowDictIdx += step_val5)
  {
    hv_WindowHandleDict = HTuple(hv_WindowHandleDicts[hv_WindowDictIdx]);
    GetDictParam(hv_WindowHandleDict, "keys", HTuple(), &hv_WindowHandleKeys);
    {
    HTuple end_val8 = (hv_WindowHandleKeys.TupleLength())-1;
    HTuple step_val8 = 1;
    for (hv_Index=0; hv_Index.Continue(end_val8, step_val8); hv_Index += step_val8)
    {
      try
      {
        GetDictTuple(hv_WindowHandleDict, HTuple(hv_WindowHandleKeys[hv_Index]), 
            &hv_WindowHandles);
      }
      // catch (Exception) 
      catch (HException &HDevExpDefaultException)
      {
        HDevExpDefaultException.ToHTuple(&hv_Exception);
        continue;
      }
      hv_RemovedWindowIndices = HTuple();
      {
      HTuple end_val15 = (hv_WindowHandles.TupleLength())-1;
      HTuple step_val15 = 1;
      for (hv_WindowHandleIndex=0; hv_WindowHandleIndex.Continue(end_val15, step_val15); hv_WindowHandleIndex += step_val15)
      {
        //Not every entry has to be a window handle, therefore use try-catch.
        try
        {
          //Call set_window_param to check if the handle is a window handle.
          SetWindowParam(HTuple(hv_WindowHandles[hv_WindowHandleIndex]), "flush", 
              "true");
          HDevWindowStack::SetActive(HTuple(hv_WindowHandles[hv_WindowHandleIndex]));
          if (HDevWindowStack::IsOpen())
            CloseWindow(HDevWindowStack::Pop());
          hv_RemovedWindowIndices = hv_RemovedWindowIndices.TupleConcat(hv_WindowHandleIndex);
        }
        // catch (Exception) 
        catch (HException &HDevExpDefaultException)
        {
          HDevExpDefaultException.ToHTuple(&hv_Exception);
        }
      }
      }
      TupleRemove(hv_WindowHandles, hv_RemovedWindowIndices, &hv_WindowHandles);
      //If some entries remained, set reduced tuple. Otherwise, remove whole key entry.
      if (0 != (int((hv_WindowHandles.TupleLength())>0)))
      {
        SetDictTuple(hv_WindowHandleDict, HTuple(hv_WindowHandleKeys[hv_Index]), 
            hv_WindowHandles);
      }
      else
      {
        RemoveDictKey(hv_WindowHandleDict, HTuple(hv_WindowHandleKeys[hv_Index]));
      }
    }
    }
  }
  }
  //
  return;
}
