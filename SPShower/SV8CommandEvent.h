#pragma once

using namespace SPEngine;

class SV8CommandEvent
{
public:
	bool refresh;
	bool repeat;
	bool read;
	SPPointer<Persistent<Object>> v8Obj;

public:
	SV8CommandEvent(void);
	~SV8CommandEvent(void);

	Handle<Object> GetV8Obj();
};

typedef SV8CommandEvent* SUICommandEventHandle;
typedef SPPointer<SV8CommandEvent> SV8CommandEventPtr;