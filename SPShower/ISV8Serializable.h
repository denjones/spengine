#pragma once
#include <v8.h>
using namespace v8;

class ISV8Serializable
{
public:
	virtual Handle<Object> SaveAsObj() = 0;
	virtual void LoadFromObj(Handle<Object> obj) = 0;
};

