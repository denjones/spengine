#include "StdAfx.h"
#include "SPVideoManager.h"
#include "SPStringHelper.h"

namespace SPEngine
{
	SPVideoManager::SPVideoManager(void)
	{
	}


	SPVideoManager::~SPVideoManager(void)
	{
	}

	void SPVideoManager::CreateVideo( SPString name )
	{
		videos.Set(name, new SPVideo(name));
	}

	SPVideoPtr SPVideoManager::GetVideo( SPString name )
	{
		if (!videos.IsSet(name))
		{
			CreateVideo(name);
		}
		
		return videos[name];
	}

	void SPVideoManager::ReleaseVideo( SPString name )
	{
		if (videos.IsSet(name))
		{
			videos.Remove(name);
		}
	}

	void SPVideoManager::Update( float timeDelta )
	{
		SPWStringMapIterator<SPVideoPtr> iter(&videos);

		for (iter.First(); !iter.IsDone(); iter.Next())
		{
			iter.CurrentItem()->UpdateFrame();
		}
	}

	void SPVideoManager::Unload()
	{

	}

	void SPVideoManager::Reload()
	{

	}

	void SPVideoManager::LoadFromString( SPString stringStream )
	{
		SPString videosString = SPStringHelper::XMLExcludeFrom(stringStream, L"Videos");
		stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"Videos");
		while(videosString.size() > 0)
		{
			SPString videoString = SPStringHelper::XMLExcludeFrom(videosString, L"V");
			videosString = SPStringHelper::XMLRemoveFirst(videosString, L"V");

			SPString videoName = SPStringHelper::XMLExcludeFrom(videoString, L"N");
			SPString videoPath = SPStringHelper::XMLExcludeFrom(videoString, L"P");
			SPString videoLoop = SPStringHelper::XMLExcludeFrom(videoString, L"L");
			SPString videoFilp = SPStringHelper::XMLExcludeFrom(videoString, L"F");
			SPString videoState = SPStringHelper::XMLExcludeFrom(videoString, L"PS");

			SPVideoPtr video = new SPVideo(videoPath);
			video->SetLoopTimes(SPStringHelper::StringToInt(videoLoop));
			video->SetFlipVertical(SPStringHelper::StringToInt(videoFilp) != 0);
			if (SPStringHelper::StringToInt(videoState))
			{
				video->Play();
			}

			videos[videoName] = video;
		}
	}

	SPString SPVideoManager::SaveAsString()
	{
		SPString result;

		result += L"<Videos>";

		SPWStringMapIterator<SPVideoPtr> iter(&videos);

		for(iter.First(); !iter.IsDone(); iter.Next())
		{
			result += L"<V>";

			result += L"<N>";
			result += iter.CurrentIndex();
			result += L"</N>";

			result += L"<P>";
			result += iter.CurrentItem()->GetPath();
			result += L"</P>";

			result += L"<L>";
			result += SPStringHelper::ToWString(iter.CurrentItem()->GetLeftTime());
			result += L"</L>";

			result += L"<F>";
			result += SPStringHelper::ToWString(iter.CurrentItem()->IsFilpVertical());
			result += L"</F>";

			result += L"<PS>";
			result += SPStringHelper::ToWString(iter.CurrentItem()->IsPlaying());
			result += L"</PS>";

			result += L"</V>";
		}

		result += L"</Videos>";

		result = SPStringHelper::XMLSurroundWith(result, L"SPVideoManager");

		return result;
	}

}

