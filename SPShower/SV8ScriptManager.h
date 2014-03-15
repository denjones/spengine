#pragma once

using namespace SPEngine;

class SV8ScriptManager :
	public SPComponent,
	public SPSingleton<SV8ScriptManager>
{
public:
	enum SkipMode{
		SkipRead,
		SkipAll,
		SkipAuto,
	};

private:
	SPPointer<SPV8ScriptEngine> requireEngine;
	SPPointer<Persistent<ObjectTemplate>> screenTempl;
	SPPointer<Persistent<ObjectTemplate>> componentTempl;
	SPPointer<Persistent<ObjectTemplate>> windowTempl;
	SPPointer<Persistent<ObjectTemplate>> textBoxTempl;
	SPPointer<Persistent<ObjectTemplate>> dialogBoxTempl;
	SPPointer<Persistent<ObjectTemplate>> pictureBoxTempl;
	SPPointer<Persistent<ObjectTemplate>> scrollTempl;
	SPPointer<Persistent<ObjectTemplate>> eventTempl;

public:
	Handle<ObjectTemplate> GetScreenTemplate();
	Handle<ObjectTemplate> GetComponentTemplate();
	Handle<ObjectTemplate> GetWindowTemplate();
	Handle<ObjectTemplate> GetTextBoxTemplate();
	Handle<ObjectTemplate> GetDialogBoxTemplate();
	Handle<ObjectTemplate> GetPictureBoxTemplate();
	Handle<ObjectTemplate> GetScrollTemplate();
	Handle<ObjectTemplate> GetEventTemplate();

private:
	static bool HasProperty(SPString propertyName, Handle<Object> obj);
	static Handle<Value> GetProperty(SPString propertyName, Handle<Object> obj);

public:

	// Skip mode
	bool isSkipModeOn;
	bool isImmediateModeOn;
	SkipMode skipMode;
	float autoWaitTimeS;
	bool isScriptRunning;

public:
	SV8ScriptManager(void);
	virtual ~SV8ScriptManager(void);

	bool Initialize();
	bool Update(float timeDelta);
	bool Load();
	bool Reload();
	bool Unload();

	static void InitModule(Handle<Object> exports);
};

