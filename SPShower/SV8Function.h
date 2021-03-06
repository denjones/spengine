#pragma once
#include "SUIEffect.h"
#include "SUIPictureList.h"

using namespace SPEngine;

class SV8Function
{
	//static void Import(const FunctionCallbackInfo<Value>& args);
	//static void Include(const FunctionCallbackInfo<Value>& args);

private:
	SV8Function(void);
	~SV8Function(void);

public:

	//
	// Global Function
	//

	static void CreateScreen(const FunctionCallbackInfo<Value>& args);
	static void CreateTrack(const FunctionCallbackInfo<Value>& args);
	static void CreateVideo(const FunctionCallbackInfo<Value>& args);
	static void CreateParticleSystem(const FunctionCallbackInfo<Value>& args);
	static void RegisterFont(const FunctionCallbackInfo<Value>& args);
	static void AddCommand(const FunctionCallbackInfo<Value>& args);
	static void AddTag(const FunctionCallbackInfo<Value>& args);
	static void Goto(const FunctionCallbackInfo<Value>& args);
	static void SaveState(const FunctionCallbackInfo<Value>& args);
	static void LoadState(const FunctionCallbackInfo<Value>& args);
	static void GetTrackById(const FunctionCallbackInfo<Value>& args);
	static void GetScreenById(const FunctionCallbackInfo<Value>& args);
	static void GetVideoById(const FunctionCallbackInfo<Value>& args);
	static void GetParticleSystemById(const FunctionCallbackInfo<Value>& args);
	static void SaveSystemData(const FunctionCallbackInfo<Value>& args);
	static void LoadSystemData(const FunctionCallbackInfo<Value>& args);
	//static void SaveScreen(const FunctionCallbackInfo<Value>& args);

	//
	// SpeShow Command
	//

	
	
	//
	// Helper
	//

	static bool HasProperty(SPString propertyName, Handle<Object> obj);
	static Handle<Value> GetProperty(SPString propertyName, Handle<Object> obj);
	static SUIEffectPtr GetEffectFromObj(Handle<Object> obj, SUIEffectPtr original);
	static SPTexturePtr GetTextureFromObj(Handle<Object> obj);
	static Handle<Value> GetObjFromTexture(SPTexturePtr texture);
	static Handle<Value> GetObjFromEffect(SUIEffectPtr effect);
};

