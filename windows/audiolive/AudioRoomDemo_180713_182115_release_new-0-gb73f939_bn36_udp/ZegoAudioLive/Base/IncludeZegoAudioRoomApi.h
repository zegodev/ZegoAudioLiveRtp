//
//  IncludeZegoLiveRoomApi.h
//  ZegoLiveDemo
//
//  Created by Randy Qiu on 2017/11/22.
//

#ifndef IncludeZegoAudioRoomApi_h
#define IncludeZegoAudioRoomApi_h

#include <QDebug>

#if defined(Q_OS_WIN)

#include "AudioRoom.h"
#include "AudioRoom-Publisher.h"
#include "AudioRoom-Player.h"
#include "AudioRoomDefines.h"
#include "AudioRoom-Volume.h"
#include "RoomDefines.h"

extern ZEGOAVKIT_API void ZegoExternalLogWithNotice(const char* content);

inline void log_string_notice(const char* content) { ZegoExternalLogWithNotice(content); qDebug() << content; }

#define qtoc(content) content.toStdString().c_str()

#elif defined(Q_OS_MAC)

#include "LiveRoom.h"
#include "LiveRoom-IM.h"
#include "LiveRoom-Player.h"
#include "LiveRoom-Publisher.h"

#else
static_assert(false, "Unkown Platform");
#endif


#endif /* IncludeZegoAudioRoomApi_h */
