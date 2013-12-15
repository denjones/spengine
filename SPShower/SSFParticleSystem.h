#pragma once
#include "SScriptFunction.h"
#include "SUIManager.h"
#include "SUIParticleSystemManager.h"

#pragma warning (disable:4244)

using namespace KScript;
class SSFParticleSystem : public SScriptFunction
{
public:

	bool Function(VariableMap args, bool isRead)
	{
		if (IsSet(L"name", args))
		{
			SPParticleSystem3DPtr particleSystem;

			SPString name = args[L"name"].value;

			SUIParticleSystemManager::GetSingleton().SetParticleSystemProperties(name, args);

			particleSystem = SPParticleSystemManager::GetSingleton().GetParticleSystem(name);

			if (!particleSystem)
			{
				particleSystem = new SPParticleSystem3D();
				SPParticleSystemManager::GetSingleton().AddParticleSystem(name, particleSystem);
				particleSystem->LoadWith2D();
				particleSystem->SetSystemAge(-1);
			}

			if (IsSet(L"width", args) && IsSet(L"height", args))
			{
				int width = SPStringHelper::StringToInt(args[L"width"].value);
				int height = SPStringHelper::StringToInt(args[L"height"].value);
				SPTextureManager::GetSingleton().CreateParticleSystemTexture(name,width,height);

				args.erase(L"width");
				args.erase(L"height");
			}

			if (IsSet(L"tex_src", args))
			{
				SPTexturePtr particleTexture = SPTextureManager::GetSingleton().GetTexture(args[L"tex_src"].value);

				if (particleTexture)
				{
					particleSystem->SetTexture(particleTexture);
				}				

				args.erase(L"tex_src");
			}			

			if (IsSet(L"born_x_min", args))
			{
				int bornMinX = SPStringHelper::StringToInt(args[L"born_x_min"].value);

				particleSystem->SetBornBoxMinX(bornMinX);			

				args.erase(L"born_x_min");
			}

			if (IsSet(L"born_y_min", args))
			{
				int bornMinY = SPStringHelper::StringToInt(args[L"born_y_min"].value);

				particleSystem->SetBornBoxMinY(bornMinY);			

				args.erase(L"born_y_min");
			}

			if (IsSet(L"born_x_max", args))
			{
				int bornMaxX = SPStringHelper::StringToInt(args[L"born_x_max"].value);

				particleSystem->SetBornBoxMaxX(bornMaxX);			

				args.erase(L"born_x_max");
			}

			if (IsSet(L"born_y_max", args))
			{
				int bornMaxY = SPStringHelper::StringToInt(args[L"born_y_max"].value);

				particleSystem->SetBornBoxMaxY(bornMaxY);			

				args.erase(L"born_y_max");
			}

			if (IsSet(L"live_x_min", args))
			{
				int liveMinX = SPStringHelper::StringToInt(args[L"live_x_min"].value);

				particleSystem->SetLiveBoxMinX(liveMinX);			

				args.erase(L"live_x_min");
			}

			if (IsSet(L"live_y_min", args))
			{
				int liveMinY = SPStringHelper::StringToInt(args[L"live_y_min"].value);

				particleSystem->SetLiveBoxMinY(liveMinY);			

				args.erase(L"live_y_min");
			}

			if (IsSet(L"live_x_max", args))
			{
				int liveMaxX = SPStringHelper::StringToInt(args[L"live_x_max"].value);

				particleSystem->SetLiveBoxMaxX(liveMaxX);			

				args.erase(L"live_x_max");
			}

			if (IsSet(L"live_y_max", args))
			{
				int liveMaxY = SPStringHelper::StringToInt(args[L"live_y_max"].value);

				particleSystem->SetLiveBoxMaxY(liveMaxY);			

				args.erase(L"live_y_max");
			}

			if (IsSet(L"live_time", args))
			{
				float liveTimeS = SPStringHelper::StringToFloat(args[L"live_time"].value);

				particleSystem->SetParticleAge(liveTimeS);			

				args.erase(L"live_time");
			}

			if (IsSet(L"color", args))
			{
				D3DCOLOR color = SPStringHelper::StringToInt(args[L"color"].value);

				particleSystem->SetColor(color);			

				args.erase(L"color");
			}

			if (IsSet(L"shoot_velocity_min", args))
			{
				float shootMin = SPStringHelper::StringToFloat(args[L"shoot_velocity_min"].value);

				particleSystem->SetTheParticleVelocityMin(shootMin);

				args.erase(L"shoot_velocity_min");
			}

			if (IsSet(L"shoot_velocity_max", args))
			{
				float shootMax = SPStringHelper::StringToFloat(args[L"shoot_velocity_max"].value);

				particleSystem->SetTheParticleVelocityMax(shootMax);			

				args.erase(L"shoot_velocity_max");
			}

			if (IsSet(L"shoot_rate", args))
			{
				float bornRate = SPStringHelper::StringToFloat(args[L"shoot_rate"].value);

				particleSystem->SetBornRate(bornRate);			

				args.erase(L"shoot_rate");
			}

			if (IsSet(L"num_max", args))
			{
				int numMax = SPStringHelper::StringToInt(args[L"num_max"].value);

				particleSystem->SetMaxNumOfParticle(numMax);			

				args.erase(L"num_max");
			}

			if (IsSet(L"acceleration_x", args) && IsSet(L"acceleration_y", args))
			{
				float accelerationX = SPStringHelper::StringToFloat(args[L"acceleration_x"].value);
				float accelerationY = SPStringHelper::StringToFloat(args[L"acceleration_y"].value);

				particleSystem->SetTheParticleAcceleration(D3DXVECTOR3(accelerationX, 0, accelerationY));			

				args.erase(L"acceleration_x");
				args.erase(L"acceleration_y");
			}

			if (IsSet(L"rotate_max", args))
			{
				float rotateMax = SPStringHelper::StringToFloat(args[L"rotate_max"].value);

				particleSystem->SetBeginRotateMaxAngle(rotateMax);			

				args.erase(L"rotate_max");
			}

			if (IsSet(L"rotate_min", args))
			{
				float rotateMin = SPStringHelper::StringToFloat(args[L"rotate_min"].value);

				particleSystem->SetBeginRotateMinAngle(rotateMin);			

				args.erase(L"rotate_min");
			}

			if (IsSet(L"rotate_rate_min", args))
			{
				float rotateRateMin = SPStringHelper::StringToFloat(args[L"rotate_rate_min"].value);

				particleSystem->SetRotateSpeedMin(rotateRateMin);			

				args.erase(L"rotate_rate_min");
			}

			if (IsSet(L"rotate_rate_max", args))
			{
				float rotateRateMax = SPStringHelper::StringToFloat(args[L"rotate_rate_max"].value);

				particleSystem->SetRotateSpeedMax(rotateRateMax);			

				args.erase(L"rotate_rate_max");
			}

			if (IsSet(L"scale_max", args))
			{
				float scaleMax = SPStringHelper::StringToFloat(args[L"scale_max"].value);

				particleSystem->SetParticleMaxScale(scaleMax);			

				args.erase(L"scale_max");
			}

			if (IsSet(L"scale_min", args))
			{
				float scaleMin = SPStringHelper::StringToFloat(args[L"scale_min"].value);

				particleSystem->SetParticleMinScale(scaleMin);			

				args.erase(L"scale_min");
			}

			if (IsSet(L"scale_rate_min", args) && IsSet(L"scale_rate_max", args))
			{
				float scaleRateMin = SPStringHelper::StringToFloat(args[L"scale_rate_min"].value);
				float scaleRateMax = SPStringHelper::StringToFloat(args[L"scale_rate_max"].value);

				particleSystem->SetParticleScaleDelta(scaleRateMin, scaleRateMax);			

				args.erase(L"scale_rate_min");
				args.erase(L"scale_rate_max");
			}

			if (IsSet(L"fade_time", args))
			{
				float fadeTime = SPStringHelper::StringToFloat(args[L"fade_time"].value);

				particleSystem->SetFadeOutTime(fadeTime);			

				args.erase(L"fade_time");
			}

			if (IsSet(L"special_rotation", args))
			{
				bool isOn = SPStringHelper::StringToInt(args[L"special_rotation"].value) != 0;

				particleSystem->SetSpecialRotation(isOn);			

				args.erase(L"special_rotation");
			}

			if (IsSet(L"shoot_angle_max", args))
			{
				float angle = SPStringHelper::StringToFloat(args[L"shoot_angle_max"].value);

				particleSystem->SetParticleMoveAngleMax(angle);			

				args.erase(L"shoot_angle_max");
			}

			if (IsSet(L"shoot_angle_min", args))
			{
				float angle = SPStringHelper::StringToFloat(args[L"shoot_angle_min"].value);

				particleSystem->SetParticleMoveAngleMin(angle);			

				args.erase(L"shoot_angle_min");
			}

			if (IsSet(L"background_color", args))
			{
				particleSystem->SetBackgroundColor(SPStringHelper::StringToInt(args[L"background_color"].value));

				args.erase(L"background_color");
			}

			if (IsSet(L"control", args))
			{
				SPString state = args[L"control"].value;

				if (state == L"Play")
				{
					particleSystem->Play();
				}

				if (state == L"Stop")
				{
					particleSystem->Stop();
				}

				if (state == L"Pause")
				{
					particleSystem->Pause();
				}

				args.erase(L"control");
			}

			args.erase(L"name");
		}

		OutLogUnusedProperties(args);

		return true;
	}
};

