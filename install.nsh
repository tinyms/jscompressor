;Author: tinyms
;Date: 2011-06-22

!include "MUI.nsh"

!insertmacro MUI_PAGE_DIRECTORY

!insertmacro MUI_PAGE_INSTFILES

!insertmacro MUI_LANGUAGE "SimpChinese"

Section
	SetOutPath $INSTDIR\JsCompressor\bin
	CreateShortCut $DESKTOP\JsCompressor.lnk $INSTDIR\JsCompressor\bin\JsCompressor.exe
SectionEnd