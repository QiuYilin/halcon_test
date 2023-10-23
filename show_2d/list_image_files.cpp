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


// Chapter: File / Misc
// Short Description: Get all image files under the given path 
void list_image_files (HTuple hv_ImageDirectory, HTuple hv_Extensions, HTuple hv_Options, 
    HTuple *hv_ImageFiles)
{

  // Local iconic variables

  // Local control variables
  HTuple  hv_ImageDirectoryIndex, hv_ImageFilesTmp;
  HTuple  hv_CurrentImageDirectory, hv_HalconImages, hv_OS;
  HTuple  hv_Directories, hv_Index, hv_Length, hv_NetworkDrive;
  HTuple  hv_Substring, hv_FileExists, hv_AllFiles, hv_i;
  HTuple  hv_Selection;

  //This procedure returns all files in a given directory
  //with one of the suffixes specified in Extensions.
  //
  //Input parameters:
  //ImageDirectory: Directory or a tuple of directories with images.
  //   If a directory is not found locally, the respective directory
  //   is searched under %HALCONIMAGES%/ImageDirectory.
  //   See the Installation Guide for further information
  //   in case %HALCONIMAGES% is not set.
  //Extensions: A string tuple containing the extensions to be found
  //   e.g. ['png','tif',jpg'] or others
  //If Extensions is set to 'default' or the empty string '',
  //   all image suffixes supported by HALCON are used.
  //Options: as in the operator list_files, except that the 'files'
  //   option is always used. Note that the 'directories' option
  //   has no effect but increases runtime, because only files are
  //   returned.
  //
  //Output parameter:
  //ImageFiles: A tuple of all found image file names
  //
  if (0 != (HTuple(HTuple(int(hv_Extensions==HTuple())).TupleOr(int(hv_Extensions==HTuple("")))).TupleOr(int(hv_Extensions==HTuple("default")))))
  {
    hv_Extensions.Clear();
    hv_Extensions[0] = "ima";
    hv_Extensions[1] = "tif";
    hv_Extensions[2] = "tiff";
    hv_Extensions[3] = "gif";
    hv_Extensions[4] = "bmp";
    hv_Extensions[5] = "jpg";
    hv_Extensions[6] = "jpeg";
    hv_Extensions[7] = "jp2";
    hv_Extensions[8] = "jxr";
    hv_Extensions[9] = "png";
    hv_Extensions[10] = "pcx";
    hv_Extensions[11] = "ras";
    hv_Extensions[12] = "xwd";
    hv_Extensions[13] = "pbm";
    hv_Extensions[14] = "pnm";
    hv_Extensions[15] = "pgm";
    hv_Extensions[16] = "ppm";
    //
  }
  (*hv_ImageFiles) = HTuple();
  //Loop through all given image directories.
  {
  HTuple end_val27 = (hv_ImageDirectory.TupleLength())-1;
  HTuple step_val27 = 1;
  for (hv_ImageDirectoryIndex=0; hv_ImageDirectoryIndex.Continue(end_val27, step_val27); hv_ImageDirectoryIndex += step_val27)
  {
    hv_ImageFilesTmp = HTuple();
    hv_CurrentImageDirectory = HTuple(hv_ImageDirectory[hv_ImageDirectoryIndex]);
    if (0 != (int(hv_CurrentImageDirectory==HTuple(""))))
    {
      hv_CurrentImageDirectory = ".";
    }
    GetSystem("image_dir", &hv_HalconImages);
    GetSystem("operating_system", &hv_OS);
    if (0 != (int((hv_OS.TupleSubstr(0,2))==HTuple("Win"))))
    {
      hv_HalconImages = hv_HalconImages.TupleSplit(";");
    }
    else
    {
      hv_HalconImages = hv_HalconImages.TupleSplit(":");
    }
    hv_Directories = hv_CurrentImageDirectory;
    {
    HTuple end_val41 = (hv_HalconImages.TupleLength())-1;
    HTuple step_val41 = 1;
    for (hv_Index=0; hv_Index.Continue(end_val41, step_val41); hv_Index += step_val41)
    {
      hv_Directories = hv_Directories.TupleConcat((HTuple(hv_HalconImages[hv_Index])+"/")+hv_CurrentImageDirectory);
    }
    }
    TupleStrlen(hv_Directories, &hv_Length);
    TupleGenConst(hv_Length.TupleLength(), 0, &hv_NetworkDrive);
    if (0 != (int((hv_OS.TupleSubstr(0,2))==HTuple("Win"))))
    {
      {
      HTuple end_val47 = (hv_Length.TupleLength())-1;
      HTuple step_val47 = 1;
      for (hv_Index=0; hv_Index.Continue(end_val47, step_val47); hv_Index += step_val47)
      {
        if (0 != (int((HTuple(hv_Directories[hv_Index]).TupleStrlen())>1)))
        {
          TupleStrFirstN(HTuple(hv_Directories[hv_Index]), 1, &hv_Substring);
          if (0 != (HTuple(int(hv_Substring==HTuple("//"))).TupleOr(int(hv_Substring==HTuple("\\\\")))))
          {
            hv_NetworkDrive[hv_Index] = 1;
          }
        }
      }
      }
    }
    hv_ImageFilesTmp = HTuple();
    {
    HTuple end_val57 = (hv_Directories.TupleLength())-1;
    HTuple step_val57 = 1;
    for (hv_Index=0; hv_Index.Continue(end_val57, step_val57); hv_Index += step_val57)
    {
      FileExists(HTuple(hv_Directories[hv_Index]), &hv_FileExists);
      if (0 != hv_FileExists)
      {
        ListFiles(HTuple(hv_Directories[hv_Index]), HTuple("files").TupleConcat(hv_Options), 
            &hv_AllFiles);
        hv_ImageFilesTmp = HTuple();
        {
        HTuple end_val62 = (hv_Extensions.TupleLength())-1;
        HTuple step_val62 = 1;
        for (hv_i=0; hv_i.Continue(end_val62, step_val62); hv_i += step_val62)
        {
          TupleRegexpSelect(hv_AllFiles, ((".*"+HTuple(hv_Extensions[hv_i]))+"$").TupleConcat("ignore_case"), 
              &hv_Selection);
          hv_ImageFilesTmp = hv_ImageFilesTmp.TupleConcat(hv_Selection);
        }
        }
        TupleRegexpReplace(hv_ImageFilesTmp, (HTuple("\\\\").Append("replace_all")), 
            "/", &hv_ImageFilesTmp);
        if (0 != (HTuple(hv_NetworkDrive[hv_Index])))
        {
          TupleRegexpReplace(hv_ImageFilesTmp, (HTuple("//").Append("replace_all")), 
              "/", &hv_ImageFilesTmp);
          hv_ImageFilesTmp = "/"+hv_ImageFilesTmp;
        }
        else
        {
          TupleRegexpReplace(hv_ImageFilesTmp, (HTuple("//").Append("replace_all")), 
              "/", &hv_ImageFilesTmp);
        }
        break;
      }
    }
    }
    //Concatenate the output image paths.
    (*hv_ImageFiles) = (*hv_ImageFiles).TupleConcat(hv_ImageFilesTmp);
  }
  }
  return;
}