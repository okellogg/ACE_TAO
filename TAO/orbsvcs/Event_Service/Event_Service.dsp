# Microsoft Developer Studio Project File - Name="Event_Service" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Event_Service - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE run the tool that generated this project file and specify the
!MESSAGE nmake output type.  You can then use the following command:
!MESSAGE
!MESSAGE NMAKE /f "Event_Service.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "Event_Service.mak" CFG="Event_Service - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "Event_Service - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Event_Service - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Event_Service - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release\Event_Service"
# PROP Target_Dir ""
# ADD CPP /nologo /O2 /W3 /GX /MD /GR /I "..\..\orbsvcs" /I "..\.." /I "..\..\tao" /I "..\..\.." /D NDEBUG /D WIN32 /D _CONSOLE /FD /c
# SUBTRACT CPP /YX
# ADD RSC /l 0x409 /d NDEBUG /i "..\..\orbsvcs" /i "..\.." /i "..\..\tao" /i "..\..\.."
BSC32=bscmake.exe
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD LINK32 advapi32.lib user32.lib /INCREMENTAL:NO TAO_BiDirGIOP.lib TAO_RTSchedEvent.lib TAO_RTOLDEvent.lib TAO_RTSched.lib TAO_RTEvent.lib TAO_CosEvent.lib TAO_Messaging.lib TAO_CosNaming.lib TAO_Svc_Utils.lib TAO_PortableServer.lib TAO_IORInterceptor.lib TAO_Valuetype.lib TAO_ObjRefTemplate.lib TAO_IORTable.lib TAO.lib ACE.lib /libpath:"..\..\..\lib" /nologo /version:1.3.1 /subsystem:console /pdb:"Release\Event_Service.pdb"  /machine:I386 /out:"Release\Event_Service.exe"

!ELSEIF  "$(CFG)" == "Event_Service - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "."
# PROP Intermediate_Dir "Debug\Event_Service"
# PROP Target_Dir ""
# ADD CPP /nologo /Ob0 /W3 /Gm /GX /Zi /MDd /GR /Gy /I "..\..\orbsvcs" /I "..\.." /I "..\..\tao" /I "..\..\.." /D _DEBUG /D WIN32 /D _CONSOLE /FD /c
# SUBTRACT CPP /YX
# ADD RSC /l 0x409 /d _DEBUG /i "..\..\orbsvcs" /i "..\.." /i "..\..\tao" /i "..\..\.."
BSC32=bscmake.exe
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD LINK32 advapi32.lib user32.lib /INCREMENTAL:NO TAO_BiDirGIOPd.lib TAO_RTSchedEventd.lib TAO_RTOLDEventd.lib TAO_RTSchedd.lib TAO_RTEventd.lib TAO_CosEventd.lib TAO_Messagingd.lib TAO_CosNamingd.lib TAO_Svc_Utilsd.lib TAO_PortableServerd.lib TAO_IORInterceptord.lib TAO_Valuetyped.lib TAO_ObjRefTemplated.lib TAO_IORTabled.lib TAOd.lib ACEd.lib /libpath:"..\..\..\lib" /nologo /version:1.3.1 /subsystem:console /pdb:".\Event_Service.pdb" /debug /machine:I386 /out:".\Event_Service.exe"

!ENDIF

# Begin Target

# Name "Event_Service - Win32 Release"
# Name "Event_Service - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;cxx;c"
# Begin Source File

SOURCE=".\Event_Service.cpp"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hh"
# Begin Source File

SOURCE=".\Event_Service.h"
# End Source File
# End Group
# End Target
# End Project
