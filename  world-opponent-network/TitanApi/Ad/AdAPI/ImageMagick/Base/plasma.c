/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%                 PPPP   L       AAA   SSSSS  M   M   AAA                     %
%                 P   P  L      A   A  SS     MM MM  A   A                    %
%                 PPPP   L      AAAAA   SSS   M M M  AAAAA                    %
%                 P      L      A   A     SS  M   M  A   A                    %
%                 P      LLLLL  A   A  SSSSS  M   M  A   A                    %
%                                                                             %
%                                                                             %
%                    Read/Write ImageMagick Image Format.                     %
%                                                                             %
%                                                                             %
%                              Software Design                                %
%                                John Cristy                                  %
%                                 July 1992                                   %
%                                                                             %
%                                                                             %
%  Copyright (C) 2000 ImageMagick Studio, a non-profit organization dedicated %
%  to making software imaging solutions freely available.                     %
%                                                                             %
%  Permission is hereby granted, free of charge, to any person obtaining a    %
%  copy of this software and associated documentation files ("ImageMagick"),  %
%  to deal in ImageMagick without restriction, including without limitation   %
%  the rights to use, copy, modify, merge, publish, distribute, sublicense,   %
%  and/or sell copies of ImageMagick, and to permit persons to whom the       %
%  ImageMagick is furnished to do so, subject to the following conditions:    %
%                                                                             %
%  The above copyright notice and this permission notice shall be included in %
%  all copies or substantial portions of ImageMagick.                         %
%                                                                             %
%  The software is provided "as is", without warranty of any kind, express or %
%  implied, including but not limited to the warranties of merchantability,   %
%  fitness for a particular purpose and noninfringement.  In no event shall   %
%  ImageMagick Studio be liable for any claim, damages or other liability,    %
%  whether in an action of contract, tort or otherwise, arising from, out of  %
%  or in connection with ImageMagick or the use or other dealings in          %
%  ImageMagick.                                                               %
%                                                                             %
%  Except as contained in this notice, the name of the ImageMagick Studio     %
%  shall not be used in advertising or otherwise to promote the sale, use or  %
%  other dealings in ImageMagick without prior written authorization from the %
%  ImageMagick Studio.                                                        %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
*/

/*
  Include declarations.
*/
#include "magick.h"
#include "defines.h"

/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                             %
%                                                                             %
%                                                                             %
%   R e a d P L A S M A I m a g e                                             %
%                                                                             %
%                                                                             %
%                                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%  Method ReadPLASMAImage creates a plasma fractal image.  The image is
%  initialized to to the X server color as specified by the filename.
%
%  The format of the ReadPLASMAImage method is:
%
%      Image *ReadPLASMAImage(const ImageInfo *image_info)
%
%  A description of each parameter follows:
%
%    o image:  Method ReadPLASMAImage returns a pointer to the image after
%      creating it. A null image is returned if there is a memory shortage
%      or if the image cannot be read.
%
%    o image_info: Specifies a pointer to an ImageInfo structure.
%
%
*/
Export Image *ReadPLASMAImage(const ImageInfo *image_info)
{
#define PlasmaImageText  "  Applying image plasma...  "
#define PlasmaPixel(x,y) \
{ \
  q=GetPixelCache(image,(int) x,(int) y,1,1); \
  if (q != (PixelPacket *) NULL) \
    { \
      q->red=(Quantum) (rand() % (MaxRGB+1)); \
      q->green=(Quantum) (rand() % (MaxRGB+1)); \
      q->blue=(Quantum) (rand() % (MaxRGB+1)); \
     (void) SyncPixelCache(image); \
    } \
}

  Image
    *image;

  int
    y;

  register int
    i,
    x;

  register PixelPacket
    *q;

  SegmentInfo
    segment_info;

  unsigned int
    depth,
    max_depth;

  /*
    Recursively apply plasma to the image.
  */
  image=ReadGRADATIONImage(image_info);
  if (image == (Image *) NULL)
    return(image);
  image->class=DirectClass;
  for (y=0; y < (int) image->rows; y++)
  {
    q=GetPixelCache(image,0,y,image->columns,1);
    if (q == (PixelPacket *) NULL)
      break;
    for (x=0; x < (int) image->columns; x++)
    {
      q->opacity=(Opaque-Transparent) >> 1;
      q++;
    }
    if (!SyncPixelCache(image))
      break;
  }
  segment_info.x1=0;
  segment_info.y1=0;
  segment_info.x2=image->columns-1;
  segment_info.y2=image->rows-1;
  srand(time(0));
  if (Latin1Compare(image_info->filename,"fractal") == 0)
    {
      /*
        Seed pixels before recursion.
      */
      PlasmaPixel(segment_info.x1,segment_info.y1);
      PlasmaPixel(segment_info.x1,(segment_info.y1+segment_info.y2)/2);
      PlasmaPixel(segment_info.x1,segment_info.y2);
      PlasmaPixel((segment_info.x1+segment_info.x2)/2,segment_info.y1);
      PlasmaPixel((segment_info.x1+segment_info.x2)/2,
        (segment_info.y1+segment_info.y2)/2);
      PlasmaPixel((segment_info.x1+segment_info.x2)/2,segment_info.y2);
      PlasmaPixel(segment_info.x2,segment_info.y1);
      PlasmaPixel(segment_info.x2,(segment_info.y1+segment_info.y2)/2);
      PlasmaPixel(segment_info.x2,segment_info.y2);
    }
  i=Max(image->columns,image->rows) >> 1;
  for (max_depth=0; i != 0; max_depth++)
    i>>=1;
  for (depth=1; ; depth++)
  {
    ProgressMonitor(PlasmaImageText,depth,max_depth);
    if (PlasmaImage(image,&segment_info,0,depth))
      break;
  }
  return(image);
}
