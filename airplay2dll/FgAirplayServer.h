#pragma once
#include "airplay.h"
#include "raop.h"


class FgAirplayServer
{
public:
	FgAirplayServer();
	virtual ~FgAirplayServer();
	int start(const char serverName, unsigned int raopPort, unsigned int airplayPort);
	void stop();

protected:
	static void connected(void* cls, const char* remoteName, const char* remoteDeviceId);
	static void disconnected(void* cls, const char* remoteName, const char* remoteDeviceId);
	static void audio_set_volume(void* cls, void* session, float volume, const char* remoteName, const char* remoteDeviceId);
	static void audio_set_metadata(void* cls, void* session, const void* buffer, int buflen, const char* remoteName, const char* remoteDeviceId);
	static void audio_set_coverart(void* cls, void* session, const void* buffer, int buflen, const char* remoteName, const char* remoteDeviceId);
	static void audio_process(void* cls, pcm_data_struct* data, const char* remoteName, const char* remoteDeviceId);
	static void audio_flush(void* cls, void* session, const char* remoteName, const char* remoteDeviceId);
	static void audio_destroy(void* cls, void* session, const char* remoteName, const char* remoteDeviceId);
	static void video_process(void* cls, h264_decode_struct* data, const char* remoteName, const char* remoteDeviceId);
	static void log_callback(void* cls, int level, const char* msg);
	static void ap_video_play(void* cls, char* url, double volume, double start_pos);
	static void ap_video_get_play_info(void* cls, double* duration, double* position, double* rate);
protected:

	airplay_t* m_pAirplay;
	raop_t* m_pRaop;
	airplay_callbacks_t		m_stAirplayCB;
	raop_callbacks_t		m_stRaopCB;
};

