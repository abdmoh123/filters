﻿# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\Abdul\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8214.51\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\Abdul\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8214.51\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\Digital_filterer.dir\depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles\Digital_filterer.dir\compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles\Digital_filterer.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Digital_filterer.dir\flags.make

CMakeFiles\Digital_filterer.dir\main.cpp.obj: CMakeFiles\Digital_filterer.dir\flags.make
CMakeFiles\Digital_filterer.dir\main.cpp.obj: "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\main.cpp"
CMakeFiles\Digital_filterer.dir\main.cpp.obj: CMakeFiles\Digital_filterer.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Digital_filterer.dir/main.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\Digital_filterer.dir\main.cpp.obj.d --working-dir="C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug" --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\Digital_filterer.dir\main.cpp.obj /FdCMakeFiles\Digital_filterer.dir\ /FS -c "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\main.cpp"
<<

CMakeFiles\Digital_filterer.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Digital_filterer.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe > CMakeFiles\Digital_filterer.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\main.cpp"
<<

CMakeFiles\Digital_filterer.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Digital_filterer.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Digital_filterer.dir\main.cpp.s /c "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\main.cpp"
<<

CMakeFiles\Digital_filterer.dir\data_handler.cpp.obj: CMakeFiles\Digital_filterer.dir\flags.make
CMakeFiles\Digital_filterer.dir\data_handler.cpp.obj: "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\data_handler.cpp"
CMakeFiles\Digital_filterer.dir\data_handler.cpp.obj: CMakeFiles\Digital_filterer.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Digital_filterer.dir/data_handler.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\Digital_filterer.dir\data_handler.cpp.obj.d --working-dir="C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug" --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\Digital_filterer.dir\data_handler.cpp.obj /FdCMakeFiles\Digital_filterer.dir\ /FS -c "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\data_handler.cpp"
<<

CMakeFiles\Digital_filterer.dir\data_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Digital_filterer.dir/data_handler.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe > CMakeFiles\Digital_filterer.dir\data_handler.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\data_handler.cpp"
<<

CMakeFiles\Digital_filterer.dir\data_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Digital_filterer.dir/data_handler.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Digital_filterer.dir\data_handler.cpp.s /c "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\data_handler.cpp"
<<

CMakeFiles\Digital_filterer.dir\classes\FiniteImpulseResponseFilter.cpp.obj: CMakeFiles\Digital_filterer.dir\flags.make
CMakeFiles\Digital_filterer.dir\classes\FiniteImpulseResponseFilter.cpp.obj: "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\classes\FiniteImpulseResponseFilter.cpp"
CMakeFiles\Digital_filterer.dir\classes\FiniteImpulseResponseFilter.cpp.obj: CMakeFiles\Digital_filterer.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Digital_filterer.dir/classes/FiniteImpulseResponseFilter.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\Digital_filterer.dir\classes\FiniteImpulseResponseFilter.cpp.obj.d --working-dir="C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug" --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\Digital_filterer.dir\classes\FiniteImpulseResponseFilter.cpp.obj /FdCMakeFiles\Digital_filterer.dir\ /FS -c "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\classes\FiniteImpulseResponseFilter.cpp"
<<

CMakeFiles\Digital_filterer.dir\classes\FiniteImpulseResponseFilter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Digital_filterer.dir/classes/FiniteImpulseResponseFilter.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe > CMakeFiles\Digital_filterer.dir\classes\FiniteImpulseResponseFilter.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\classes\FiniteImpulseResponseFilter.cpp"
<<

CMakeFiles\Digital_filterer.dir\classes\FiniteImpulseResponseFilter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Digital_filterer.dir/classes/FiniteImpulseResponseFilter.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Digital_filterer.dir\classes\FiniteImpulseResponseFilter.cpp.s /c "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\classes\FiniteImpulseResponseFilter.cpp"
<<

CMakeFiles\Digital_filterer.dir\classes\InfiniteImpulseResponseFilter.cpp.obj: CMakeFiles\Digital_filterer.dir\flags.make
CMakeFiles\Digital_filterer.dir\classes\InfiniteImpulseResponseFilter.cpp.obj: "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\classes\InfiniteImpulseResponseFilter.cpp"
CMakeFiles\Digital_filterer.dir\classes\InfiniteImpulseResponseFilter.cpp.obj: CMakeFiles\Digital_filterer.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Digital_filterer.dir/classes/InfiniteImpulseResponseFilter.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\Digital_filterer.dir\classes\InfiniteImpulseResponseFilter.cpp.obj.d --working-dir="C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug" --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\Digital_filterer.dir\classes\InfiniteImpulseResponseFilter.cpp.obj /FdCMakeFiles\Digital_filterer.dir\ /FS -c "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\classes\InfiniteImpulseResponseFilter.cpp"
<<

CMakeFiles\Digital_filterer.dir\classes\InfiniteImpulseResponseFilter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Digital_filterer.dir/classes/InfiniteImpulseResponseFilter.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe > CMakeFiles\Digital_filterer.dir\classes\InfiniteImpulseResponseFilter.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\classes\InfiniteImpulseResponseFilter.cpp"
<<

CMakeFiles\Digital_filterer.dir\classes\InfiniteImpulseResponseFilter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Digital_filterer.dir/classes/InfiniteImpulseResponseFilter.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Digital_filterer.dir\classes\InfiniteImpulseResponseFilter.cpp.s /c "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\classes\InfiniteImpulseResponseFilter.cpp"
<<

CMakeFiles\Digital_filterer.dir\wav_handler.cpp.obj: CMakeFiles\Digital_filterer.dir\flags.make
CMakeFiles\Digital_filterer.dir\wav_handler.cpp.obj: "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\wav_handler.cpp"
CMakeFiles\Digital_filterer.dir\wav_handler.cpp.obj: CMakeFiles\Digital_filterer.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Digital_filterer.dir/wav_handler.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\Digital_filterer.dir\wav_handler.cpp.obj.d --working-dir="C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug" --filter-prefix="Note: including file: " -- C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\Digital_filterer.dir\wav_handler.cpp.obj /FdCMakeFiles\Digital_filterer.dir\ /FS -c "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\wav_handler.cpp"
<<

CMakeFiles\Digital_filterer.dir\wav_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Digital_filterer.dir/wav_handler.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe > CMakeFiles\Digital_filterer.dir\wav_handler.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\wav_handler.cpp"
<<

CMakeFiles\Digital_filterer.dir\wav_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Digital_filterer.dir/wav_handler.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Digital_filterer.dir\wav_handler.cpp.s /c "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\wav_handler.cpp"
<<

# Object files for target Digital_filterer
Digital_filterer_OBJECTS = \
"CMakeFiles\Digital_filterer.dir\main.cpp.obj" \
"CMakeFiles\Digital_filterer.dir\data_handler.cpp.obj" \
"CMakeFiles\Digital_filterer.dir\classes\FiniteImpulseResponseFilter.cpp.obj" \
"CMakeFiles\Digital_filterer.dir\classes\InfiniteImpulseResponseFilter.cpp.obj" \
"CMakeFiles\Digital_filterer.dir\wav_handler.cpp.obj"

# External object files for target Digital_filterer
Digital_filterer_EXTERNAL_OBJECTS =

Digital_filterer.exe: CMakeFiles\Digital_filterer.dir\main.cpp.obj
Digital_filterer.exe: CMakeFiles\Digital_filterer.dir\data_handler.cpp.obj
Digital_filterer.exe: CMakeFiles\Digital_filterer.dir\classes\FiniteImpulseResponseFilter.cpp.obj
Digital_filterer.exe: CMakeFiles\Digital_filterer.dir\classes\InfiniteImpulseResponseFilter.cpp.obj
Digital_filterer.exe: CMakeFiles\Digital_filterer.dir\wav_handler.cpp.obj
Digital_filterer.exe: CMakeFiles\Digital_filterer.dir\build.make
Digital_filterer.exe: CMakeFiles\Digital_filterer.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable Digital_filterer.exe"
	C:\Users\Abdul\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\223.8214.51\bin\cmake\win\bin\cmake.exe -E vs_link_exe --intdir=CMakeFiles\Digital_filterer.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1428~1.299\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Digital_filterer.dir\objects1.rsp @<<
 /out:Digital_filterer.exe /implib:Digital_filterer.lib /pdb:"C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug\Digital_filterer.pdb" /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Digital_filterer.dir\build: Digital_filterer.exe
.PHONY : CMakeFiles\Digital_filterer.dir\build

CMakeFiles\Digital_filterer.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Digital_filterer.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Digital_filterer.dir\clean

CMakeFiles\Digital_filterer.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files" "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files" "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug" "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug" "C:\Users\Abdul\OneDrive - Newcastle University\Stage 4\E3004.1 ECAD Project\Project files\cmake-build-debug\CMakeFiles\Digital_filterer.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\Digital_filterer.dir\depend
