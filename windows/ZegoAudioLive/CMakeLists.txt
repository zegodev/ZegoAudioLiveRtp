cmake_minimum_required(VERSION 3.6)

#设置工程名称
project(ZegoAudioLive)

#set(CMAKE_SKIP_BUILD_RPATH TRUE)                 # 编译时加上RPATH  
#set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

if(WINDOWS_PLATFORM STREQUAL "x86")
    SET(CMAKE_PREFIX_PATH $ENV{QT_DIR})
elseif(WINDOWS_PLATFORM STREQUAL "x64")
    SET(CMAKE_PREFIX_PATH $ENV{QT_DIR_x64})
endif(WINDOWS_PLATFORM STREQUAL "x86")

#添加qt库
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

#编译时自动打开moc
set(CMAKE_AUTOMOC ON)
#设置工程包含当前目录，非必须                    
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#添加.ui文件，并将通过qt5_wrap_ui将.ui文件包裹成ui_*.h文件
FILE(GLOB_RECURSE FORMS "*.ui")
QT5_WRAP_UI(FORMS_UIC ${FORMS})

#添加资源文件.qrc
FILE(GLOB RES "*.qrc")
QT5_ADD_RESOURCES(RES_RCC ${RES})

file(GLOB_RECURSE All_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.mm 
                              ${CMAKE_CURRENT_LIST_DIR}/*.m 
                              ${CMAKE_CURRENT_LIST_DIR}/*.cpp 
                              ${CMAKE_CURRENT_LIST_DIR}/*.mm 
                              ${CMAKE_CURRENT_LIST_DIR}/*.c 
                              ${CMAKE_CURRENT_LIST_DIR}/*.cc 
                              ${CMAKE_CURRENT_LIST_DIR}/*.hh 
                              ${CMAKE_CURRENT_LIST_DIR}/*.h)
            
source_group_by_dir(All_SOURCES)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

if(WIN32)
    include_directories(${CMAKE_CURRENT_LIST_DIR}/../include/ZegoAudioRoom
    					${CMAKE_CURRENT_LIST_DIR}/UI
                        ${CMAKE_CURRENT_LIST_DIR})


elseif(APPLE)
    include_directories(${CMAKE_CURRENT_LIST_DIR}/../include/ZegoAudioRoom
                        ${CMAKE_CURRENT_LIST_DIR}
                        ${CMAKE_CURRENT_LIST_DIR}/UI)
endif(WIN32)

set(SCRIPT_PATH ${CMAKE_CURRENT_LIST_DIR}/../..)

if(WIN32)
	set(exe_property WIN32)
        set(ZegoAudioLive_RC ${CMAKE_CURRENT_LIST_DIR}/Resources/res.rc)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")

    if(WINDOWS_PLATFORM STREQUAL "x86")
	set(LINK_LIBRARY zegoaudioroom.lib)
	set(ZEGOAUDIOROOM_PATH ${CMAKE_CURRENT_LIST_DIR}/../libs/windows/x86_xp/$(Configuration)/zegoaudioroom.dll)
        set(MSVC_PATH ${CMAKE_CURRENT_LIST_DIR}/msvc/x86)
        add_definitions(-DUNICODE -D_UNICODE -D_SCL_SECURE_NO_WARNINGS -DWIN32 -DV_LOG -DCURL_STATICLIB)
	link_directories(${CMAKE_CURRENT_LIST_DIR}/../libs/windows/x86_xp)
    elseif(WINDOWS_PLATFORM STREQUAL "x64")
        set(LINK_LIBRARY zegoaudioroom.lib)
        set(ZEGOAUDIOROOM_PATH ${CMAKE_CURRENT_LIST_DIR}/../libs/windows/x64_xp/$(Configuration)/zegoaudioroom.dll)
        set(MSVC_PATH ${CMAKE_CURRENT_LIST_DIR}/msvc/x64)
        add_definitions(-DUNICODE -D_UNICODE -D_SCL_SECURE_NO_WARNINGS -DWIN32 -DV_LOG -DCURL_STATICLIB)
        link_directories(${CMAKE_CURRENT_LIST_DIR}/../libs/windows/x64_xp)
    endif(WINDOWS_PLATFORM STREQUAL "x86")

elseif(APPLE)
    SET(BUILD_WITH_INSTALL_RPATH TRUE)
    set(exe_property MACOSX_BUNDLE)
    set(MACOSX_BUNDLE_ICON_FILE ${CMAKE_CURRENT_LIST_DIR}/Resources/ZegoLiveDemo.icns)
    #set(ZegoLiveDemo_RC ${CMAKE_CURRENT_LIST_DIR}/Info.plist)
    set (CMAKE_CXX_FLAGS "--std=gnu++11 ${CMAKE_CXX_FLAGS}")
    set(LINK_LIBRARY libZegoLiveRoomOSX.dylib)				
    link_directories(${CMAKE_CURRENT_LIST_DIR}/../libs/mac)
endif(WIN32)

#构建可执行文件
set(NAME ZegoAudioLive)
add_executable(${NAME} ${exe_property} ${All_SOURCES} ${ZegoAudioLive_RC} ${FORMS_UIC} ${RES_RCC} ${MACOSX_BUNDLE_ICON_FILE} ${LangSrcs})



if(WIN32)
    #add_custom_command(TARGET ZegoAudioLive PRE_BUILD COMMAND python ${SCRIPT_PATH}/setup-newest-zegoliveroom.py --config $(Configuration) --platform ${WINDOWS_PLATFORM})

    add_custom_command(TARGET ZegoAudioLive POST_BUILD COMMAND if exist ${ZEGOAUDIOROOM_PATH} cmake -E copy ${ZEGOAUDIOROOM_PATH} ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))

    add_custom_command(TARGET ZegoAudioLive POST_BUILD COMMAND if exist ${MSVC_PATH}/msvcp120.dll cmake -E copy ${MSVC_PATH}/msvcp120.dll ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))

    add_custom_command(TARGET ZegoAudioLive POST_BUILD COMMAND if exist ${MSVC_PATH}/msvcr120.dll cmake -E copy ${MSVC_PATH}/msvcr120.dll ${CMAKE_CURRENT_BINARY_DIR}/$(Configuration))  

elseif(APPLE)
    set_source_files_properties(${CMAKE_CURRENT_LIST_DIR}/Resources/ZegoAudioLive.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
    set_target_properties(${NAME} PROPERTIES MACOSX_BUNDLE_ICON_FILE ZegoAudioLive.icns)
    
    #add_custom_command(TARGET ZegoAudioLive PRE_BUILD COMMAND python ${SCRIPT_PATH}/setup-newest-zegoliveroom.py)
    
    ADD_FRAMEWORK(Foundation ZegoAudioLive)
    ADD_FRAMEWORK(AVFoundation ZegoAudioLive)
    ADD_FRAMEWORK(cocoa ZegoAudioLive)
    ADD_FRAMEWORK(CoreMedia ZegoAudioLive)
    ADD_FRAMEWORK(CoreVideo ZegoAudioLive)

    #set(CMAKE_XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT dwarf-with-dsym)
    set_target_properties(ZegoAudioLive PROPERTIES XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym")
    set_target_properties(ZegoAudioLive PROPERTIES XCODE_ATTRIBUTE_GCC_GENERATE_DEBUGGING_SYMBOLS "YES")

    set_target_properties(ZegoAudioLive PROPERTIES XCODE_ATTRIBUTE_SEPARATE_STRIP "YES")
    set_target_properties(ZegoAudioLive PROPERTIES XCODE_ATTRIBUTE_STRIP_STYLE "Non-Global Symbols")

endif(WIN32)

qt5_use_modules(${NAME} Core)
qt5_use_modules(${NAME} Gui)
qt5_use_modules(${NAME} Widgets)
qt5_use_modules(${NAME} Network)

target_link_libraries(${NAME} ${LINK_LIBRARY})



