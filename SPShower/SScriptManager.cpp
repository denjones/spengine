#include "StdAfx.h"
#include "SScriptManager.h"
#include "SSFScreen.h"
#include "SSFPicture.h"
#include "SSFPictureBox.h"
#include "SSFComponent.h"
#include "SSFMixPicture.h"
#include "SSFWaitClick.h"
#include "SSFSwitchPicture.h"
#include "SSFTextBox.h"
#include "SSFFont.h"
#include "SSFAddText.h"
#include "SSFClearText.h"
#include "SSFAnimation.h"
#include "SSFSwitchScreen.h"
#include "SSFWaitTime.h"
#include "SSFEffect.h"
#include "SSFRegisterFont.h"
#include "SSFExit.h"
#include "SSFScript.h"
#include "SSFTag.h"
#include "SSFGoTo.h"
#include "SSFVideo.h"
#include "SSFSound.h"
#include "SSFList.h"
#include "SSFTrack.h"
#include "SSFDialogBox.h"
#include "SSFNext.h"
#include "SSFWaitDialog.h"
#include "SSFSaveGameData.h"
#include "SSFSavePicture.h"
#include "SSFLoadGameData.h"
#include "SScriptHelper.h"
#include "SSFVar.h"
#include "SSFWindowText.h"
#include "SSFDisplay.h"
#include "SSFWait.h"
#include "SSFFirst.h"
#include "SSFCursor.h"
#include "SSFFps.h"
#include "SSFExecute.h"
#include "SSFSkip.h"
#include "SSFParticleSystem.h"

using namespace KScript;

SScriptManager::SScriptManager(void): SPScriptManager()
{
	innerScript = new Script(this);
	currentPosition = commands.begin();
	firstName = L"first.ks";
	currentOrder = 0;
	autoWaitTimeS = 0;
	isSkipModeOn = false;
	isImmediateModeOn = false;
	skipMode = SkipAuto;
}


SScriptManager::~SScriptManager(void)
{
}

bool SScriptManager::Update( float timeDelta )
{
	if (immediateCommands.size() > 0)
	{
		while(immediateCommands.size() > 0)
		{
			// Accept Function.
			SScriptCommand command = immediateCommands.front();
			SScriptFunctionPtr function;

			// No such function.
			if (!functions.IsSet(command.commandName))
			{
				immediateCommands.pop_front();
				continue;
			}

			// Use function.
			function = functions[command.commandName];
			function->Function(command.args, IsCommandRead(command));

			// If the function is not finished.
			if (function->IsWaiting())
			{
				break;
			}

			// If the function is finished and need to refresh screen.
			if (function->IsNeedToRefresh())
			{
				immediateCommands.pop_front();
				break;
			}

			immediateCommands.pop_front();
		}
	}
	else
	{
		while(commands.size() > 0)
		{
			// Accept Function.
			SScriptCommand command = commands.front();
			SScriptFunctionPtr function;

			// No such function.
			if (!functions.IsSet(command.commandName))
			{
				commands.pop_front();
				SetInsertPosBack();
				continue;
			}

			// Use function.
			function = functions[command.commandName];
			function->Function(command.args, IsCommandRead(command));

			// If the function is not finished.
			if (function->IsWaiting())
			{
				break;
			}

			// If the function is finished and need to refresh screen.
			if (function->IsNeedToRefresh())
			{
				commands.pop_front();
				if (commands.size() > 0 && commands.front().order != command.order)
				{
					SetCommandRead(command);
				}
				SetInsertPosBack();
				break;
			}

			commands.pop_front();
			if (commands.size() > 0 && commands.front().order != command.order)
			{
				SetCommandRead(command);
			}
		}
	}

	return true;
}

bool SScriptManager::AddCommand(SScriptCommand newCommand, KScript::Script* currentScript)
{
	//
	// If immediate mode is on, just add command to immediate list.
	//

	if (isImmediateModeOn)
	{
		immediateCommands.push_back(newCommand);
		return true;
	}

	//currentOrder++;
	if (!currentScript)
	{
		newCommand.order = script->functionOrder;
	}
	else
	{
		newCommand.order = currentScript->functionOrder;
	}
	
	currentPosition = commands.insert(currentPosition, newCommand);
	currentPosition++;

	return true;
}

bool SScriptManager::AddFunction( SPString name, SScriptFunctionPtr function )
{
	if (!function)
	{
		return false;
	}
	AddExtension(name, new AddCommandToCommandList(name));
	function->SetName(name);
	functions.Set(name, function);

	return true;
}

bool SScriptManager::Initialize()
{
	AddFunction(L"screen",		new SSFScreen());
	AddFunction(L"picture",		new SSFPicture());
	AddFunction(L"pictureBox",	new SSFPictureBox());
	AddFunction(L"component",	new SSFComponent());
	AddFunction(L"mixPicture",	new SSFMixPicture());
	AddFunction(L"waitClick",	new SSFWaitClick());
	AddFunction(L"switchPicture",new SSFSwitchPicture());
	AddFunction(L"textBox",		new SSFTextBox());
	AddFunction(L"font",		new SSFFont());
	AddFunction(L"addText",		new SSFAddText());
	AddFunction(L"clearText",	new SSFClearText());
	AddFunction(L"animation",	new SSFAnimation());
	AddFunction(L"switchScreen",new SSFSwitchScreen());
	AddFunction(L"waitTime",	new SSFWaitTime());
	AddFunction(L"effect",		new SSFEffect());
	AddFunction(L"registerFont",new SSFRegisterFont());
	AddFunction(L"exit",		new SSFExit());
	AddFunction(L"script",		new SSFScript());
	AddFunction(L"tag",			new SSFTag());
	AddFunction(L"goTo",		new SSFGoTo());
	AddFunction(L"video",		new SSFVideo());
	AddFunction(L"sound",		new SSFSound());
	AddFunction(L"list",		new SSFList());
	AddFunction(L"track",		new SSFTrack());
	AddFunction(L"dialogBox",	new SSFDialogBox());
	//AddFunction(L"next",		new SSFNext());
	AddFunction(L"waitDialog",	new SSFWaitDialog());
	AddFunction(L"saveGameData",new SSFSaveGameData());
	AddFunction(L"savePicture",	new SSFSavePicture());
	AddFunction(L"loadGameData",new SSFLoadGameData());
	AddFunction(L"var",			new SSFVar());
	AddFunction(L"windowText",	new SSFWindowText());
	AddFunction(L"display",		new SSFDisplay());
	AddFunction(L"wait",		new SSFWait());
	AddFunction(L"first",		new SSFFirst());
	AddFunction(L"cursor",		new SSFCursor());
	AddFunction(L"fps",			new SSFFps());
	AddFunction(L"execute",		new SSFExecute());
	AddFunction(L"skip",		new SSFSkip());
	AddFunction(L"particleSystem", new SSFParticleSystem());
	AddExtension(L"include",	new IncludeMapArgsFunc(this));
	AddExtension(L"next",		new SSFNext());
	

	return true;
}

bool SScriptManager::ExecuteInnerScript( SPString stringScript )
{
	innerScript->LoadStringScript(stringScript);
	innerScript->SetVariableMap(systemVariables);
	innerScript->SetVariableMap(script->GetVariableMap());
	innerScript->fileName = script->fileName;
	innerScript->Execute();
	script->UpdateVariableMap(innerScript->GetVariableMap());
	UpdateSystemVariables(innerScript->GetVariableMap());
	
	return true;
}

bool SScriptManager::ExecuteInnerScript( KScript::ScriptPtr newScript )
{
	newScript->ClearVariableMap();
	newScript->runner = this;
	newScript->SetVariableMap(systemVariables);
	newScript->SetVariableMap(script->GetVariableMap());
	newScript->fileName = script->fileName;
	newScript->Execute();
	script->SetVariableMap(newScript->GetVariableMap());
	UpdateSystemVariables(newScript->GetVariableMap());

	return true;
}

bool SScriptManager::SetInsertPosFront(int offset)
{
	currentPosition = commands.begin();

	while(offset-- > 0 && currentPosition != commands.end())
	{
		currentPosition++;
	}

	return true;
}

bool SScriptManager::SetInsertPosBack()
{
	currentPosition = commands.end();

	return true;
}

bool SScriptManager::ReplaceCommandsFromFile( KString path )
{
	commands.clear();
	immediateCommands.clear();
	SPScriptManager::Load(path);
	Execute();
	return true;
}

bool SScriptManager::ClearCommands()
{
	commands.clear();
	immediateCommands.clear();
	return true;
}

bool SScriptManager::LocateCommands( SScriptCommand target)
{
	CommandIterator iter = commands.begin();

	while(iter != commands.end())
	{
		// If match command name, check if the variable maps match.
		if (iter->commandName == target.commandName)
		{
			VariableMap::iterator valueIter = target.args.begin();

			bool match = true;

			// Loop through value to check if match.
			while (valueIter != target.args.end())
			{
				VariableMap v = iter->args;

				// One value mismatch, means totally mismatch.
				if(v[valueIter->first].value != valueIter->second.value)
				{
					match = false;
					break;
				}

				valueIter++;
			}

			// If match, end locating.
			if (match)
			{
				break;
			}
		}

		// Mismatch, pop.
		iter = commands.erase(iter);
	}

	return true;
}

bool SScriptManager::ReloadCommands()
{
	commands.clear();
	Execute();

	return true;
}

bool SScriptManager::LoadFromString( SPString stringStream )
{
	SPString commandsString = SPStringHelper::XMLExcludeFrom(stringStream, L"Commands");

	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"Commands");

	commands.clear();

	//while(commandsString.size() > 0)
	//{
	//	SPString commandString = SPStringHelper::XMLExcludeFrom(commandsString, L"SSC");
	//	commandsString = SPStringHelper::XMLRemoveFirst(commandsString, L"SSC");

	//	SPString commandName = SPStringHelper::XMLExcludeFrom(commandString, L"CN");
	//	SPString commandArgs = SPStringHelper::XMLExcludeFrom(commandString, L"Properties");
	//	SPString commandFile = SPStringHelper::XMLExcludeFrom(commandString, L"FN");
	//	int commandOrder = SPStringHelper::StringToInt(SPStringHelper::XMLExcludeFrom(commandString, L"OD"));

	//	SScriptCommand command(commandName, SScriptHelper::StringToVariables(commandArgs), commandFile, commandOrder);

	//	commands.push_back(command);
	//}

	SPString commandName = SPStringHelper::XMLExcludeFrom(commandsString, L"CN");
	commandsString = SPStringHelper::XMLRemoveFirst(commandsString, L"CN");
	SPString commandFile = SPStringHelper::XMLExcludeFrom(commandsString, L"SF");
	commandsString = SPStringHelper::XMLRemoveFirst(commandsString, L"SF");
	int commandOrder = SPStringHelper::StringToInt(SPStringHelper::XMLExcludeFrom(commandsString, L"CO"));
	commandsString = SPStringHelper::XMLRemoveFirst(commandsString, L"CO");

	SPScriptManager::Load(commandFile);

	Execute();

	while(commands.size() > 0)
	{
		if (commands.front().commandName == commandName  
			&& commands.front().order == commandOrder)
		{
			break;
		}

		commands.pop_front();
	}

	SPString innerVariablesString = SPStringHelper::XMLExcludeFrom(stringStream, L"InnerVariables");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"InnerVariables");
	innerScript->SetVariableMap(SScriptHelper::StringToVariables(innerVariablesString));

	SPString outerVariablesString = SPStringHelper::XMLExcludeFrom(stringStream, L"OuterVariables");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"OuterVariables");
	script->SetVariableMap(SScriptHelper::StringToVariables(innerVariablesString));

	SPString functionsString = SPStringHelper::XMLExcludeFrom(stringStream, L"Functions");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"Functions");
	while(functionsString.size() > 0)
	{
		SPString functionString = SPStringHelper::XMLExcludeFrom(functionsString, L"F");
		functionsString = SPStringHelper::XMLRemoveFirst(functionsString, L"F");

		SPString functionName = SPStringHelper::XMLExcludeFrom(functionString, L"N");
		SPString functionScript = SPStringHelper::XMLExcludeFrom(functionString, L"S");

		AddUserDefinedFunction(functionName, new ScriptStringFunction(this, functionScript));
	}

	return true;
}

SPString SScriptManager::SaveAsString()
{
	SPString result;

	result += L"<Commands>";

	//if (commands.size() > 1)
	//{
	//	CommandIterator iter = commands.begin();

	//	iter++;

	//	while(iter != commands.end())
	//	{
	//		result += iter->SaveAsString();

	//		iter++;
	//	}
	//}	

	while (commands.size() > 0)
	{
		if (commands.front().order > 0)
		{
			break;
		}

		commands.pop_front();
	}

	SScriptCommand currentCommand = commands.front();

	result += L"<CN>" + currentCommand.commandName + L"</CN>";

	result += L"<SF>" + currentCommand.fileName + L"</SF>";

	result += L"<CO>" + SPStringHelper::ToWString(currentCommand.order) + L"</CO>";

	result += L"</Commands>";

	result += SPStringHelper::XMLSurroundWith(SScriptHelper::VariablesToString(innerScript->GetVariableMap()), L"InnerVariables");

	result += SPStringHelper::XMLSurroundWith(SScriptHelper::VariablesToString(script->GetVariableMap()), L"OuterVariables");

	result += L"<Functions>";

	ScriptStringFunctionMap::iterator fIter = userDefinedScriptStringFunctions.begin();

	while(fIter != userDefinedScriptStringFunctions.end())
	{
		result += L"<F>";

		result += L"<N>";
		result += fIter->first;
		result += L"</N>";

		result += L"<S>";
		result += fIter->second->scriptString;
		result += L"</S>";

		result += L"</F>";

		fIter++;
	}

	result += L"</Functions>";

	result = SPStringHelper::XMLSurroundWith(result, L"SScriptManager");

	return result;
}

bool SScriptManager::UpdateSystemVariables( VariableMap setVars )
{
	for(VariableMap::iterator iter = setVars.begin();
		iter != setVars.end(); iter++)
	{
		if (systemVariables.find(iter->first) == systemVariables.end())
		{
			continue;
		}

		systemVariables[iter->first] = iter->second;
	}

	return true;
}

bool SScriptManager::SetSystemVariables( VariableMap setVars )
{
	for(VariableMap::iterator iter = setVars.begin();
		iter != setVars.end(); iter++)
	{
		systemVariables[iter->first] = iter->second;
	}

	return true;
}

KScript::VariableMap SScriptManager::GetSystemVariables()
{
	return systemVariables;
}

bool SScriptManager::InitializeSystemVariables( VariableMap setVars )
{
	for(VariableMap::iterator iter = setVars.begin();
		iter != setVars.end(); iter++)
	{
		if (systemVariables.find(iter->first) == systemVariables.end())
		{
			systemVariables[iter->first] = iter->second;
		}
	}

	return true;
}

bool SScriptManager::Load()
{
	SPScriptManager::Load(L"pre.ks");

	Execute();

	while(commands.size() > 0)
	{
		// Accept Function.
		SScriptCommand command = commands.front();
		SScriptFunctionPtr function;

		// No such function.
		if (!functions.IsSet(command.commandName))
		{
			commands.pop_front();
			SetInsertPosBack();
			continue;
		}

		// Use function.
		function = functions[command.commandName];
		function->Function(command.args, false);

		commands.pop_front();
	}

	SPScriptManager::Load(firstName);

	Execute();

	return true;
}

bool SScriptManager::SetFirst( SPString setPath )
{
	firstName = setPath;

	return true;
}

KScript::Value SScriptManager::Execute()
{
	currentOrder = 0;
	script->SetVariableMap(systemVariables);
	Value result = script->Execute();
	currentOrder = 0;

	return result;
}

bool SScriptManager::IsCommandRead( SScriptCommand command )
{
	if (command.fileName == L"")
	{
		return false;
	}

	if (!readCommands.IsSet(command.fileName))
	{
		return false;
	}

	RegionListPtr readOrderList = readCommands.Get(command.fileName);

	RegionListIterator iter = readOrderList->begin();

	while(iter != readOrderList->end())
	{
		if ((*iter)->first <= command.order && command.order <= (*iter)->second)
		{
			return true;
		}

		iter++;
	}

	return false;
}

bool SScriptManager::SetCommandRead( SScriptCommand command )
{
	if (!readCommands.IsSet(command.fileName))
	{
		readCommands.Set(command.fileName, new RegionList());
	}

	RegionListPtr readOrderList = readCommands.Get(command.fileName);

	RegionListIterator iter = readOrderList->begin();

	if (iter == readOrderList->end())
	{
		readOrderList->push_back(new Region(command.order, command.order));
		return true;
	}

	RegionListIterator iterNext = iter;
	iterNext++;

	while(iterNext != readOrderList->end())
	{
		if(command.order > (*iter)->second && command.order < (*iterNext)->first)
		{
			break;
		}

		iter++;
		iterNext++;
	}

	// Less than head
	if (command.order < (*iter)->first)
	{
		if (command.order == (*iter)->first - 1)
		{
			(*iter)->first = command.order;
		}
		else
		{
			readOrderList->push_front(new Region(command.order, command.order));
		}
	}
	// Iter is tail
	else if (command.order > (*iter)->second && iterNext == readOrderList->end())
	{		
		if (command.order == (*iter)->second + 1)
		{
			// Add to tail.
			(*iter)->second = command.order;
		}
		else
		{
			// New region
			readOrderList->push_back(new Region(command.order, command.order));
		}
	}
	// Not reach list tail
	else if (command.order > (*iter)->second && iterNext != readOrderList->end())
	{
		if (command.order == (*iter)->second + 1)
		{
			// Add to tail.
			(*iter)->second = command.order;

			// Merge region.
			if (command.order == (*iterNext)->first - 1)
			{
				(*iter)->second = (*iterNext)->second;
				iterNext = readOrderList->erase(iterNext);
			}
		}
		else if (command.order == (*iterNext)->first - 1)
		{
			// Add to head of next region.
			(*iterNext)->first = command.order;
		}
		else
		{
			// New Region
			readOrderList->insert(iterNext, new Region(command.order, command.order));
		}		
	}

	return true;
}

SPString SScriptManager::ReadCommandsToString()
{
	SPWStringMapIterator<RegionListPtr> iter(&readCommands);

	SPString result = L"";

	for (iter.First(); !iter.IsDone(); iter.Next())
	{
		if (iter.CurrentIndex() == L"")
		{
			continue;
		}

		SPString fileNameString = SPStringHelper::XMLSurroundWith(iter.CurrentIndex(), L"FN");
		SPString regionListString = L"";

		RegionListIterator innerIter = iter.CurrentItem()->begin();

		if (iter.CurrentItem()->size() == 0)
		{
			continue;
		}

		while(innerIter != iter.CurrentItem()->end())
		{
			SPString regionString = L"";

			regionString += SPStringHelper::XMLSurroundWith(SPStringHelper::ToWString((*innerIter)->first), L"B");
			regionString += SPStringHelper::XMLSurroundWith(SPStringHelper::ToWString((*innerIter)->second), L"E");
			regionString = SPStringHelper::XMLSurroundWith(regionString, L"R");

			regionListString += regionString;

			innerIter++;
		}

		regionListString = SPStringHelper::XMLSurroundWith(regionListString, L"RL");

		result += SPStringHelper::XMLSurroundWith(fileNameString + regionListString, L"FR");

	}

	result = SPStringHelper::XMLSurroundWith(result, L"RC");

	return result;
}

bool SScriptManager::ReadCommandsFromString( SPString stringStream )
{
	readCommands.Clear();

	SPString readRommandsString = SPStringHelper::XMLExcludeFrom(stringStream, L"RC");
	stringStream = SPStringHelper::XMLRemoveFirst(stringStream, L"RC");

	while(readRommandsString.size() > 0)
	{
		SPString commandString = SPStringHelper::XMLExcludeFrom(readRommandsString, L"FR");
		readRommandsString = SPStringHelper::XMLRemoveFirst(readRommandsString, L"FR");

		SPString commandFileName = SPStringHelper::XMLExcludeFrom(commandString, L"FN");
		SPString commandReadRegionsString = SPStringHelper::XMLExcludeFrom(commandString, L"RL");

		if (commandFileName == L"")
		{
			continue;
		}

		RegionListPtr regionList = new RegionList();

		while(commandReadRegionsString.size() > 0)
		{
			SPString regionString = SPStringHelper::XMLExcludeFrom(commandReadRegionsString, L"R");
			commandReadRegionsString = SPStringHelper::XMLRemoveFirst(commandReadRegionsString, L"R");

			int beginOrder = SPStringHelper::StringToInt(SPStringHelper::XMLExcludeFrom(regionString, L"B"));
			int endOrder = SPStringHelper::StringToInt(SPStringHelper::XMLExcludeFrom(regionString, L"E"));

			regionList->push_back(new Region(beginOrder,endOrder));
		}
		
		readCommands.Set(commandFileName, regionList);
	}

	return true;
}

bool SScriptManager::ImmediateModeOn()
{
	isImmediateModeOn = true;
	return true;
}

bool SScriptManager::ImmediateModeOff()
{
	isImmediateModeOn = false;
	return true;
}

bool SScriptManager::Reload()
{
	return true;
}
