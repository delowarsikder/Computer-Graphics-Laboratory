## How To install open GL in Windows-10 32 bit or 64 bit system

> You should follow two step one by one

>## 1. Download and setup 


1.Download and install ` codeblocks-17.12mingw-setup.exe ` From 
**[Here](https://sourceforge.net/projects/codeblocks/files/Binaries/17.12/Windows/codeblocks-17.12mingw-setup.exe/download)**
.Unless Codeblocks not install in your computer.

2.Download ` glut-3.7.6-bin.zip` from **[Here](https://sourceforge.net/projects/colladaloader/files/colladaloader/colladaloader%201.1/glut-3.7.6-bin.zip/download)** and Unzip this file.There, your will get at least 3 files.`glut.h, glut32.dll, glut32.lib `

3.Copy `glut.h` file and  Go to `C:\Program Files (x86)\CodeBlocks\MinGW\include\GL `this Location in your computer and **paste** `glut.h` 


4.Copy `glut32.lib` file and  Go to `C:\Program Files (x86)\CodeBlocks\MinGW\lib` this Location in your computer and **paste** `glut32.lib` 

5.Copy `glut32.dll` file and Go to `C:\Windows\SysWOW64` this Location in your computer and **paste** `glut32.dll`
 
*	**Note:** If your Operating System is 32 bit, folder name might be `C:\Windows\System32`

```sh
N.B: When you go to noted path and paste the file.

you will insure that don't modify ,replace or delete file.just you paste your desire file.
```

>## 2.Linker settings for codeblocks 

1.Open `Codebocks` and then go `settings ->  compiler -> linker settings`.

2.Click `add` button and go to `C:\Program Files (x86)\CodeBlocks\MinGW\lib` and add this file (`glut32.lib, libglu32.a, libopengl32.a`) one by one 

3.Press ok

>>### Test the settings

1.Open `Codeblocks` go to `File->New -> Project -> GLUT Project -> Go -> Next `

2.Provide the ***project name*** and Choose the path where you want to save your project. 

3.When you create new project.you will already get a ready made project default.

4.Add `#include<windows.h>` Line in your project .

5.Press `F9` or go to `Built` -> `Run` to run your project.

```
if you follow above instruction properly . you will successfully run the programe
```
>### Happy Computer Graphics

-------
>># My project 
# Computer Graphics Laboratory 
* computer graphics assignment file contain the MVC to VCS and VCS to NDCS conversion .

## 1. Boat Racing folder contain the project that is developed in computer graphics laboratory
## 2. Lighting and class room desing repo contain the lab works
>* This lab works are  designed and developed an attractive class room using c++ ,openGl glu,glut library 