# PSDParser
c++ library for parsing Photoshop File (.PSD and PSB) and return JSON format datas include "Image Hight", "Image Width", "DPI", "ICC Profile", "Layers" and "Fonrs"

This code is based on Adobe Photoshop File Formats Specification(https://www.adobe.com/devnet-apps/photoshop/fileformatashtml/) and Internation Color Consortium(http://www.color.org/index.xalter)

This code is required to link icu4c, C/C++ libraries for Unicode and globalization.
You can download the library from Homebrew.

Here is sample JSON.
```json
{
  "height":1080,
  "width":1920,
  "DPI":72,
  "ICC Profile": "Display P3",
  "layers": 
     {"name": "root",
      "children":
        [
          {"name" : "Layer 1",
           "children" : []
          },
          {"name" : "Background",
           "children" : []
          }
        ]
      }
}
```
