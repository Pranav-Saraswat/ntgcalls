//
// Created by Laky64 on 29/08/2023.
//

#pragma once

#if defined _WIN32 || defined __CYGWIN__
#ifdef NTG_EXPORTS
#define NTG_C_EXPORT __declspec(dllexport) // building the library
#else
#define NTG_C_EXPORT __declspec(dllimport) // using the library
#endif
#else // not WIN32
#define NTG_C_EXPORT
#endif

#include <stdint.h>
#include <stdbool.h>

// EXCEPTIONS CODES
#define NTG_UNKNOWN_EXCEPTION -1
#define NTG_INVALID_UID -2
#define NTG_CONNECTION_ALREADY_EXISTS -3
#define NTG_FILE_NOT_FOUND -4
#define NTG_ENCODER_NOT_FOUND -5
#define NTG_FFMPEG_NOT_FOUND -6
#define NTG_RTMP_NEEDED -7
#define NTG_INVALID_TRANSPORT -8
#define NTG_CONNECTION_FAILED -9
#define NTG_CONNECTION_NOT_FOUND -10
#define NTG_SHELL_ERROR -11
#define NTG_ERR_TOO_SMALL -12

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NTG_FILE,
    NTG_SHELL,
    NTG_FFMPEG
} ntg_input_mode_enum;

typedef enum {
    NTG_STREAM_AUDIO,
    NTG_STREAM_VIDEO
} ntg_stream_type_enum;

typedef enum {
    NTG_PLAYING,
    NTG_PAUSED,
    NTG_IDLING
} ntg_stream_status_enum;

typedef struct {
    ntg_input_mode_enum inputMode;
    char* input;
    uint16_t sampleRate;
    uint8_t bitsPerSample, channelCount;
} ntg_audio_description_struct;

typedef struct {
    ntg_input_mode_enum inputMode;
    char* input;
    uint16_t width, height;
    uint8_t fps;
} ntg_video_description_struct;

typedef struct {
    ntg_audio_description_struct* audio;
    ntg_video_description_struct* video;
} ntg_media_description_struct;

typedef struct {
    int64_t chatId;
    ntg_stream_status_enum status;
} ntg_group_call_struct;

typedef struct {
    bool muted;
    bool videoPaused;
    bool videoStopped;
} ntg_media_state_struct;

typedef void (*ntg_stream_callback)(uint32_t, int64_t, ntg_stream_type_enum);

typedef void (*ntg_upgrade_callback)(uint32_t, int64_t, ntg_media_state_struct);

NTG_C_EXPORT uint32_t ntg_init();

NTG_C_EXPORT int ntg_destroy(uint32_t uid);

NTG_C_EXPORT int ntg_get_params(uint32_t uid, int64_t chatID, ntg_media_description_struct rep, char* buffer, int size);

NTG_C_EXPORT int ntg_connect(uint32_t uid, int64_t chatID, char* params);

NTG_C_EXPORT int ntg_change_stream(uint32_t uid, int64_t chatID, ntg_media_description_struct desc);

NTG_C_EXPORT bool ntg_pause(uint32_t uid, int64_t chatID);

NTG_C_EXPORT bool ntg_resume(uint32_t uid, int64_t chatID);

NTG_C_EXPORT bool ntg_mute(uint32_t uid, int64_t chatID);

NTG_C_EXPORT bool ntg_unmute(uint32_t uid, int64_t chatID);

NTG_C_EXPORT int ntg_stop(uint32_t uid, int64_t chatID);

NTG_C_EXPORT uint64_t ntg_time(uint32_t uid, int64_t chatID);

NTG_C_EXPORT int ntg_calls(uint32_t uid, ntg_group_call_struct *buffer, int size);

NTG_C_EXPORT int ntg_calls_count(uint32_t uid);

NTG_C_EXPORT int ntg_on_stream_end(uint32_t uid, ntg_stream_callback callback);

NTG_C_EXPORT int ntg_on_upgrade(uint32_t uid, ntg_upgrade_callback callback);

#ifdef __cplusplus
}
#endif
