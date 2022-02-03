#include "pch.h"
#include "FgAirplayServer.h"
#include <thread>

#ifdef WIN32
#include   "iphlpapi.h"  
#pragma   comment(lib,   "iphlpapi.lib   ")  
#endif

FgAirplayServer::FgAirplayServer() :
	 m_pAirplay(NULL)
	, m_pRaop(NULL)
{
	memset(&m_stAirplayCB, 0, sizeof(airplay_callbacks_t));
	memset(&m_stRaopCB, 0, sizeof(raop_callbacks_t));
	m_stAirplayCB.cls = this;
	m_stRaopCB.cls = this;

	m_stAirplayCB.video_play = ap_video_play;
	m_stAirplayCB.video_get_play_info = ap_video_get_play_info;

	m_stRaopCB.connected = connected;
	m_stRaopCB.disconnected = disconnected;
	m_stRaopCB.audio_set_volume = audio_set_volume;
	m_stRaopCB.audio_set_metadata = audio_set_metadata;
	m_stRaopCB.audio_set_coverart = audio_set_coverart;
	m_stRaopCB.audio_process = audio_process;
	m_stRaopCB.audio_flush = audio_flush;
	m_stRaopCB.video_process = video_process;
}

FgAirplayServer::~FgAirplayServer()
{
}

int FgAirplayServer::start(const char serverName,  unsigned int raopPort, unsigned int airplayPort )
{
	unsigned short raop_port = raopPort;
	unsigned short airplay_port = airplayPort;
	unsigned char hwaddr[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
	char* pemstr = NULL;

	int ret = 0;
	do {
		m_pAirplay = airplay_init(10, &m_stAirplayCB, pemstr, &ret);
		if (m_pAirplay == NULL) {
			ret = -1;
			break;
		}
		ret = airplay_start(m_pAirplay, &airplay_port, hwaddr, sizeof(hwaddr), NULL);
		if (ret < 0) {
			break;
		}
		airplay_set_log_level(m_pAirplay, RAOP_LOG_DEBUG);
		airplay_set_log_callback(m_pAirplay, &log_callback, this);

		m_pRaop = raop_init(10, &m_stRaopCB);
		if (m_pRaop == NULL) {
			ret = -1;
			break;
		}

		raop_set_log_level(m_pRaop, RAOP_LOG_DEBUG);
		raop_set_log_callback(m_pRaop, &log_callback, this);
		ret = raop_start(m_pRaop, &raop_port);
		if (ret < 0) {
			break;
		}
		raop_set_port(m_pRaop, raop_port);

		raop_log_info(m_pRaop, "Startup complete... Kill with Ctrl+C\n");
	} while (false);

	if (ret != 0) {
		stop();
	}

	return 0;
}

void FgAirplayServer::stop()
{
	if (m_pRaop) {
		raop_destroy(m_pRaop);
		m_pRaop = NULL;
	}

	if (m_pAirplay) {
		airplay_destroy(m_pAirplay);
		m_pAirplay = NULL;
	}
}


void FgAirplayServer::connected(void* cls, const char* remoteName, const char* remoteDeviceId)
{
	
}

void FgAirplayServer::disconnected(void* cls, const char* remoteName, const char* remoteDeviceId)
{
	
}


void FgAirplayServer::audio_set_volume(void* cls, void* session, float volume, const char* remoteName, const char* remoteDeviceId)
{
}

void FgAirplayServer::audio_set_metadata(void* cls, void* session, const void* buffer, int buflen, const char* remoteName, const char* remoteDeviceId)
{
}

void FgAirplayServer::audio_set_coverart(void* cls, void* session, const void* buffer, int buflen, const char* remoteName, const char* remoteDeviceId)
{
}

void FgAirplayServer::audio_process(void* cls, pcm_data_struct* data, const char* remoteName, const char* remoteDeviceId)
{
	
}

void FgAirplayServer::audio_flush(void* cls, void* session, const char* remoteName, const char* remoteDeviceId)
{
}

void FgAirplayServer::audio_destroy(void* cls, void* session, const char* remoteName, const char* remoteDeviceId)
{
}

void FgAirplayServer::video_process(void* cls, h264_decode_struct* h264data, const char* remoteName, const char* remoteDeviceId)
{
	
}

void FgAirplayServer::ap_video_play(void* cls, char* url, double volume, double start_pos)
{
	
}

void FgAirplayServer::ap_video_get_play_info(void* cls, double* duration, double* position, double* rate)
{
	
}

void FgAirplayServer::log_callback(void* cls, int level, const char* msg)
{
	
}

