#include "StdAfx.h"
#include "SoundManager.h"

using namespace SPEngine;

SoundManager::SoundManager( SPGame* game )
{
	xAudio = NULL;
	masterVoice = NULL;
	Register(game);
	sounds.clear();
}


SoundManager::SoundManager(void)
{
	xAudio = NULL;
	masterVoice = NULL;
	sounds.clear();
}


SoundManager::~SoundManager(void)
{
}

bool SPEngine::SoundManager::Initialize()
{
	return true;
}

bool SPEngine::SoundManager::Load()
{
	if (FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED)))
	{
		MessageBoxA(NULL, "Failed to initialize XAudio2!", NULL, NULL);
		return false;
	}	

	if ( FAILED(XAudio2Create( &xAudio, 0, XAUDIO2_DEFAULT_PROCESSOR ) ) )
	{
		MessageBoxA(NULL, "Failed to initialize XAudio2!", NULL, NULL);
		return false;
	}

	// Enumerate and select devices
	UINT32 deviceCount;
	xAudio->GetDeviceCount(&deviceCount);

	XAUDIO2_DEVICE_DETAILS deviceDetails;
	int preferredDevice = 0;
	for (unsigned int i = 0; i < deviceCount; i++)
	{
		xAudio->GetDeviceDetails(i,&deviceDetails);
		if (deviceDetails.OutputFormat.Format.nChannels > 2)
		{
			preferredDevice = i;
			break;
		}
	}

	// Create mastering voice device
	if ( FAILED(xAudio->CreateMasteringVoice( &masterVoice, XAUDIO2_DEFAULT_CHANNELS,
		XAUDIO2_DEFAULT_SAMPLERATE, 0, preferredDevice, NULL ) ) )
	{
		MessageBoxA(NULL, "Failed to create mastering voice!", NULL, NULL);
		return false;
	}

	return true;
}

bool SPEngine::SoundManager::Unload()
{
	foreach(Sound*, sound, vector<Sound*>, sounds )
	{
		//Because of mutiUnload
		//if (sound)
		//{
		//	sound->Stop();
		//	sound->Shutdown();
		//}
	}

	sounds.clear();
	
	//Unload the Master Voice
	if(masterVoice != NULL)
		masterVoice->DestroyVoice();
	masterVoice = 0;

	//Unload the xAudio2
	if(xAudio != NULL)
		xAudio->Release();
	xAudio = 0;

	return true;
}

bool SPEngine::SoundManager::Update( float timeElapsed )
{
	foreach(Sound*, sound, vector<Sound*>, sounds)
	{
		if(sound)
			sound->Update(timeElapsed);
	}
	return true;
}

//bool SPEngine::SoundManager::AddSound( string soundfile, int numRepeats, int *id )
//{
//	sounds.push_back(&Sound(this, soundfile, numRepeats));
//	return true;
//}

bool SPEngine::SoundManager::AddSound(Sound *sound)
{
	sounds.push_back(sound);
	return true;
}

void SPEngine::SoundManager::Play( int id )
{
	if(id >= (int)sounds.size()) return;

	sounds[id]->Play();
}

void SPEngine::SoundManager::Stop( int id )
{
	if(id >= (int)sounds.size()) return;

	sounds[id]->Stop();
}

void SPEngine::SoundManager::Pause( int id )
{
	if( id >= (int)sounds.size() ) return;
	sounds[id]->Pause();
}

void SPEngine::SoundManager::UpdateSoundPosition( int id, float x, float y, float z )
{
	if(id >= (int)sounds.size()) return;

	sounds[id]->UpdateSoundPosition(x, y, z);
}

IXAudio2* SPEngine::SoundManager::XAudio()
{
	return xAudio;
}

bool SoundManager::Draw( float timeElapsed )
{
	return true;
}

void SoundManager::GetVolume(float &volume)
{
	masterVoice->GetVolume(&volume);
}

void SoundManager::SetVolume(float volume)
{
	masterVoice->SetVolume(volume);
}
