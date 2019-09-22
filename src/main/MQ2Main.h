/*
 * MacroQuest2: The extension platform for EverQuest
 * Copyright (C) 2002-2019 MacroQuest Authors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#pragma once

#if !defined(NOMINMAX)
#define NOMINMAX
#endif
#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

// targeting Windows 7+
#if defined(_WIN32_WINNT)
#undef _WIN32_WINNT
#endif
#define  _WIN32_WINNT          0x0601
#if defined(WINVER)
#undef WINVER
#endif
#define WINVER                 0x0601

#define DIRECTINPUT_VERSION    0x800

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <winsock.h>
#include <math.h>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <string_view>
#include <algorithm>

// warning C4530 : C++ exception handler used, but unwind semantics are not enabled.Specify / EHsc
#pragma warning(disable:4530)

// disable the noexcept warning there isnt really anything we can do about it as far as i know or is there? let me know if u know how to fix it - eqmule
#pragma warning(disable:4577)

// Windows Header Files:
#include <windows.h>

#include "dxsdk90\include\dinput.h"
#include "detours\inc\detours.h"

// MQ2
#include "blech\Blech.h"

//#define MQ2_PROFILING

// uncomment this line to turn off the single-line benchmark macro
// #define DISABLE_BENCHMARKS

#define VersionString          __ExpectedVersionDate
#define TimeString             __ExpectedVersionTime
#define DebugHeader            "[MQ2]"
#define LoadedString           "MQ2 Loaded."
#define ToUnloadString         "MQ2 Unloading..."
#define UnloadedString         "MQ2 Unloaded."

//
// EQ Version selection
//

// If this is a test branch, define TEST so that certain differences are enabled
//#define TEST
#define LIVE

#ifdef EQLIB_EXPORTS
#define EQLIB_API extern "C" __declspec(dllexport)
#define EQLIB_VAR extern "C" __declspec(dllexport)
#define EQLIB_OBJECT __declspec(dllexport)
#else
#define EQLIB_API extern "C" __declspec(dllimport)
#define EQLIB_VAR extern "C" __declspec(dllimport)
#define EQLIB_OBJECT __declspec(dllimport)
#endif

#ifdef MQ2PLUGIN
#define FromPlugin true
#else
#define FromPlugin false
#endif

#define EzDetour(offset, detour, trampoline) AddDetourf((DWORD)offset, detour, trampoline)
#define EzDetourwName(offset, detour, trampoline, name) AddDetourf((DWORD)offset, detour, trampoline, name)

#ifndef THIS_
#define THIS_                   INTERFACE FAR* This,
#endif

#ifdef DEBUG_TRY
#define DebugTry(x) DebugSpew("Trying %s",#x);x;DebugSpew("%s complete",#x)
#else
#define DebugTry(x) x
#endif

#define MAX_VARNAME           64
#define MAX_STRING            2048

#define IsNaN(x) (x != x)

#define LODWORD(_qw)          ((uint32_t)(_qw))
#define HIDWORD(_qw)          ((uint32_t)(((_qw) >> 32) & 0xffffffff))

#include "../eqlib/EQLib.h"

#include "MQ2Prototypes.h"
#include "MQ2Internal.h"
#include "MQ2Globals.h"

/* THREADING */
EQLIB_API DWORD GetMainThreadId();
EQLIB_API bool IsMainThread();

// Queue a function to be called on the main thread on the next pulse
EQLIB_OBJECT void PostToMainThread(std::function<void()>&& callback);

/* BENCHMARKING */
#ifdef DISABLE_BENCHMARKS
#define Benchmark(BMHandle, code) code
#else
#define Benchmark(BMHandle, code) { EnterMQ2Benchmark(BMHandle); code; ExitMQ2Benchmark(BMHandle); }
#endif
EQLIB_API void ShutdownMQ2Benchmarks();
EQLIB_API void InitializeMQ2Benchmarks();
EQLIB_API bool GetMQ2Benchmark(uint32_t BMHandle, MQBenchmark& Dest);
EQLIB_API void ExitMQ2Benchmark(uint32_t BMHandle);
EQLIB_API void EnterMQ2Benchmark(uint32_t BMHandle);
EQLIB_API void RemoveMQ2Benchmark(uint32_t BMHandle);
EQLIB_API uint32_t AddMQ2Benchmark(const char* Name);

/* SPAWN HANDLING */
EQLIB_API void InitializeMQ2Spawns();
EQLIB_API void ShutdownMQ2Spawns();
EQLIB_API void ProcessPendingGroundItems();
EQLIB_API void UpdateMQ2SpawnSort();
EQLIB_API bool SetNameSpriteState(SPAWNINFO* pSpawn, bool Show);
EQLIB_API bool IsTargetable(SPAWNINFO* pSpawn);

/* WINDOWS */
EQLIB_API HWND GetEQWindowHandle();
EQLIB_API void InitializeMQ2Windows();
EQLIB_API void ShutdownMQ2Windows();
EQLIB_API void RemoveXMLFile(const char* filename);
EQLIB_API void AddXMLFile(const char* filename);
EQLIB_API bool IsXMLFilePresent(const char* filename);
EQLIB_API bool SendWndClick(const char* WindowName, const char* ScreenID, const char* ClickNotification);
EQLIB_API bool SendWndNotification(const char* WindowName, const char* ScreenID, int Notification, void* Data = 0);
EQLIB_API void AddWindow(char *WindowName, CXWnd **ppWindow);
EQLIB_API void RemoveWindow(char* WindowName);
EQLIB_API CXWnd* FindMQ2Window(const char* Name);
EQLIB_API CXWnd* GetParentWnd(CXWnd* pWnd);

EQLIB_API bool SendComboSelect(const char* WindowName, const char* ScreenID, int Value);
EQLIB_API bool SendListSelect(const char* WindowName, const char* ScreenID, int Value);
EQLIB_API bool SendListSelect2(CXWnd* pList, int ListIndex);
EQLIB_API bool SendWndClick2(CXWnd* pWnd, const char* ClickNotification);

EQLIB_API void CreateMQ2NewsWindow();
EQLIB_API void DeleteMQ2NewsWindow();

/* CHAT HOOK */
EQLIB_API void InitializeChatHook();
EQLIB_API void ShutdownChatHook();
EQLIB_API void dsp_chat_no_events(const char* Text, int Color, bool EqLog = true, bool dopercentsubst = true);

/* DETOURING API */
EQLIB_API void InitializeMQ2Detours();
EQLIB_API void ShutdownMQ2Detours();

EQLIB_API bool AddDetour(DWORD address, BYTE* pfDetour = 0, BYTE* pfTrampoline = 0, DWORD Count = 20, char* Name = 0);
EQLIB_API void AddDetourf(DWORD address, ...);
EQLIB_API void RemoveDetour(DWORD address);
EQLIB_API void DeleteDetour(DWORD address);

EQLIB_API void WriteChatColor(const char* Line, int Color = USERCOLOR_DEFAULT, int Filter = 0);
EQLIB_API void WriteChatf(const char* Format, ...);
EQLIB_API [[deprecated("Use WriteChatf instead")]] void WriteChatfSafe(const char* szFormat, ...);
EQLIB_API void WriteChatColorf(const char* szFormat, int color, ...);

/* PLUGIN HANDLING */
EQLIB_API void InitializeMQ2Plugins();
EQLIB_API int LoadMQ2Plugin(const char* pszFilename, bool bCustom = false);
EQLIB_API bool UnloadMQ2Plugin(const char* pszFilename);
EQLIB_API void UnloadMQ2Plugins();
EQLIB_API void ShutdownMQ2Plugins();
EQLIB_API void SaveMQ2PluginLoadStatus(const char* Name, bool bLoad);
EQLIB_API void PulsePlugins();
EQLIB_API void PluginsZoned();
EQLIB_API bool PluginsIncomingChat(const char* Line, DWORD Color);
EQLIB_API void PluginsCleanUI();
EQLIB_API void PluginsReloadUI();
EQLIB_API void PluginsSetGameState(DWORD GameState);
EQLIB_API void PluginsDrawHUD();
EQLIB_API void PluginsAddSpawn(SPAWNINFO* pNewSpawn);
EQLIB_API void PluginsRemoveSpawn(SPAWNINFO* pSpawn);
EQLIB_API void PluginsAddGroundItem(GROUNDITEM* pNewGroundItem);
EQLIB_API void PluginsRemoveGroundItem(GROUNDITEM* pGroundItem);
EQLIB_API void PluginsBeginZone();
EQLIB_API void PluginsEndZone();
EQLIB_API bool IsPluginsInitialized();
EQLIB_API void* GetPluginProc(const char* plugin, const char* proc);

/* DIRECT INPUT */
EQLIB_API void InitializeMQ2DInput();
EQLIB_API void ShutdownMQ2DInput();

/* CLEAN UI */
EQLIB_API void InitializeDisplayHook();
EQLIB_API void ShutdownDisplayHook();
EQLIB_API void DrawHUD();

/* COMMAND HANDLING */
EQLIB_API void InitializeMQ2Commands();
EQLIB_API void ShutdownMQ2Commands();
EQLIB_API void AddCommand(const char* Command, fEQCommand Function, bool EQ = false, bool Parse = true, bool InGame = false);
EQLIB_API void AddAlias(const char* ShortCommand, const char* LongCommand);
EQLIB_API bool RemoveAlias(const char* ShortCommand);
EQLIB_API void AddSubstitute(const char* Original, const char* Substitution);
EQLIB_API bool RemoveSubstitute(const char* Original);
EQLIB_API bool RemoveCommand(const char* Command);
EQLIB_API void PulseCommands();
EQLIB_API void TimedCommand(const char* Command, int msDelay);
EQLIB_API bool IsCommand(const char* command);
EQLIB_API bool IsAlias(const char* alias);

/* MACRO COMMANDS */
EQLIB_API void DumpStack(SPAWNINFO*, char*);
EQLIB_API void EndMacro(SPAWNINFO*, char*);
EQLIB_API void Echo(SPAWNINFO*, char*);

/* MACRO PARSING */
void CALLBACK EventBlechCallback(unsigned int ID, void* pData, PBLECHVALUE pValues);

EQLIB_API char* ParseMacroParameter(SPAWNINFO* pChar, char* szOriginal, size_t BufferSize);

template <unsigned int _Size>
inline char* ParseMacroParameter(SPAWNINFO* pChar, char(&szOriginal)[_Size])
{
	return ParseMacroParameter(pChar, szOriginal, _Size);
}

EQLIB_API void FailIf(SPAWNINFO* pChar, const char* szCommand, int pStartLine, bool All = false);
EQLIB_API void InitializeParser();
EQLIB_API void ShutdownParser();

EQLIB_API void InitializeMQ2DataTypes();
EQLIB_API void ShutdownMQ2DataTypes();
EQLIB_API void InitializeMQ2Data();
EQLIB_API void ShutdownMQ2Data();
EQLIB_API bool ParseMacroData(char* szOriginal, size_t BufferSize);
EQLIB_API bool AddMQ2Data(const char* szName, fMQData Function);
EQLIB_API bool RemoveMQ2Data(const char* szName);
EQLIB_API MQ2Type* FindMQ2DataType(const char* szName);
EQLIB_API MQDataItem* FindMQ2Data(const char* szName);
EQLIB_API MQDataVar* FindMQ2DataVariable(const char* szName);
EQLIB_API bool AddMQ2Type(MQ2Type& type);
EQLIB_API bool RemoveMQ2Type(MQ2Type& type);
EQLIB_API bool ParseMQ2DataPortion(char* szOriginal, MQTypeVar &Result);
EQLIB_API bool AddMQ2TypeExtension(const char* typeName, MQ2Type* extension);
EQLIB_API bool RemoveMQ2TypeExtension(const char* typeName, MQ2Type* extension);

// Compatibility shims
inline [[deprecated("The data function's signature must be updated to bool functionName(const char* szIndex, MQTypeVar& ret)")]]
bool AddMQ2Data(const char* szName, fMQDataOld Function)
{
	return AddMQ2Data(szName, (fMQData)Function);
}

/* MOUSE */
EQLIB_API bool IsMouseWaiting();
EQLIB_API bool IsMouseWaitingForButton();
EQLIB_API void MQ2MouseHooks(bool bFlag);
EQLIB_API bool MoveMouse(int x, int y, bool bClick = false);
EQLIB_API bool MouseToPlayer(PlayerClient* pPlayer, DWORD position, bool bClick = false);

/* KEY BINDS */
EQLIB_API void InitializeMQ2KeyBinds();
EQLIB_API void ShutdownMQ2KeyBinds();
EQLIB_API bool PressMQ2KeyBind(const char* name, bool Hold);
EQLIB_API bool SetMQ2KeyBind(const char* name, bool Alternate, KeyCombo& Combo);
EQLIB_API bool AddMQ2KeyBind(const char* name, fMQExecuteCmd Function);
EQLIB_API bool RemoveMQ2KeyBind(const char* name);
EQLIB_API bool GetMQ2KeyBind(const char* name, bool Alt, KeyCombo& Combo);
EQLIB_API bool DumpBinds(const char* Filename);
EQLIB_API bool MQ2HandleKeyDown(const KeyCombo& Combo);
EQLIB_API bool MQ2HandleKeyUp(const KeyCombo& Combo);
EQLIB_API int FindMappableCommand(const char* name);

/* PULSING */
EQLIB_API void InitializeMQ2Pulse();
EQLIB_API void ShutdownMQ2Pulse();

/* UTILITIES */
EQLIB_API void ConvertCR(char* Text, size_t LineLen);
EQLIB_API void DrawHUDText(const char* Text, int X, int Y, unsigned int Argb, int Font);

// Logging utilities
EQLIB_API void DebugSpew(const char* szFormat, ...);
EQLIB_API void DebugSpewAlways(const char* szFormat, ...);
EQLIB_API void DebugSpewAlwaysFile(const char* szFormat, ...);
EQLIB_API void DebugSpewNoFile(const char* szFormat, ...);

EQLIB_API char* GetNextArg(char* szLine, int dwNumber = 1, bool CSV = false, char Separator = 0);
EQLIB_API char* GetArg(char* szDest, char* szSrc, int dwNumber, bool LeaveQuotes = false, bool ToParen = false, bool CSV = false, char Separator = 0, bool AnyNonAlphaNum = false);
EQLIB_API float DistanceToSpawn(SPAWNINFO* pChar, SPAWNINFO* pSpawn);
EQLIB_API char* GetEQPath(char* szBuffer, size_t len);

// Command Execution
EQLIB_API void HideDoCommand(SPAWNINFO* pChar, const char* szLine, bool delayed);
EQLIB_API void DoCommandf(const char* szFormat, ...);
inline void DoCommand(PSPAWNINFO pSpawnInfo, const char* szCommand)
{
	HideDoCommand(pSpawnInfo, szCommand, FromPlugin);
}
inline void EzCommand(const char* szCommand) { DoCommand((SPAWNINFO*)pLocalPlayer, szCommand); }

EQLIB_API DWORD MQToSTML(const char* in, char* out, size_t maxlen = MAX_STRING, uint32_t ColorOverride = 0xFFFFFF);
EQLIB_API void StripMQChat(const char* in, char* out);
EQLIB_API void STMLToPlainText(char* in, char* out);
EQLIB_API char* GetSubFromLine(int Line, char* szSub, size_t Sublen);
EQLIB_API const char* GetFilenameFromFullPath(const char* Filename);
EQLIB_API bool CompareTimes(char* RealTime, char* ExpectedTime);
EQLIB_API void AddFilter(const char* szFilter, int Length, bool& pEnabled);
EQLIB_API void DefaultFilters();
EQLIB_API char* ConvertHotkeyNameToKeyName(char* szName);
EQLIB_API void CheckChatForEvent(const char* szMsg);
EQLIB_API void ConvertItemTags(CXStr& cxstr, bool Tag = true);
EQLIB_API bool ParseKeyCombo(const char* text, KeyCombo& Dest);
EQLIB_API char* DescribeKeyCombo(KeyCombo& Combo, char* szDest, size_t BufferSize);
EQLIB_API int FindInvSlotForContents(CONTENTS* pContents);
EQLIB_API int FindInvSlot(const char* Name, bool Exact);
EQLIB_API int FindNextInvSlot(const char* Name, bool Exact);

EQLIB_API int GetLanguageIDByName(const char* szName);
EQLIB_API int GetCurrencyIDByName(char* szName);
EQLIB_API const char* GetSpellNameByID(int dwSpellID);
EQLIB_API SPELL* GetSpellByName(const char* szName);
EQLIB_API SPELL* GetSpellByAAName(const char* szName);
EQLIB_API ALTABILITY* GetAAByIdWrapper(int nAbilityId, int playerLevel = -1);
EQLIB_API int GetSpellRankByName(const char* SpellName);
EQLIB_API void TruncateSpellRankName(char* SpellName);
EQLIB_API void RemoveBuff(SPAWNINFO* pChar, char* szLine);
EQLIB_API void RemovePetBuff(SPAWNINFO* pChar, char* szLine);
EQLIB_API bool StripQuotes(char* str);
EQLIB_API void MakeMeVisible(SPAWNINFO* pChar, char* szLine);
EQLIB_API void RemoveAura(SPAWNINFO* pChar, char* szLine);
EQLIB_API bool GetAllMercDesc(std::map<int, MercDesc>& minfo);
EQLIB_API int GetKeyRingIndex(KeyRingType KeyRing, const char* szItemName, bool bExact = true, bool usecmd = false);
EQLIB_API int GetMountCount();
EQLIB_API int GetIllusionCount();
EQLIB_API int GetFamiliarCount();
EQLIB_API void RefreshKeyRings(void* kr);
EQLIB_API void InitKeyRings();
EQLIB_API bool IsActiveAA(const char* pSpellName);
EQLIB_API CXWnd* GetAdvLootPersonalListItem(DWORD ListIndex, DWORD type);
EQLIB_API CXWnd* GetAdvLootSharedListItem(DWORD ListIndex, DWORD type);
EQLIB_API bool LootInProgress(CAdvancedLootWnd* pAdvLoot, CListWnd* pPersonalList, CListWnd* pSharedList);
EQLIB_API void WeDidStuff();
EQLIB_API int GetFreeInventory(int nSize);
EQLIB_API int RangeRandom(int min, int max);

EQLIB_API int GetCharMaxBuffSlots();
EQLIB_API int GetBodyType(SPAWNINFO* pSpawn);
EQLIB_API eSpawnType GetSpawnType(SPAWNINFO* pSpawn);

EQLIB_OBJECT bool IsRaidMember(const char* SpawnName);
EQLIB_OBJECT bool IsRaidMember(SPAWNINFO* pSpawn);
EQLIB_OBJECT int GetRaidMemberIndex(const char* SpawnName);
EQLIB_OBJECT int GetRaidMemberIndex(SPAWNINFO* pSpawn);
EQLIB_OBJECT bool IsGroupMember(const char* SpawnName);
EQLIB_OBJECT bool IsGroupMember(SPAWNINFO* pSpawn);
EQLIB_API bool IsFellowshipMember(const char* SpawnName);
EQLIB_API bool IsGuildMember(const char* SpawnName);
EQLIB_API int GetGroupMercenaryCount(uint32_t ClassMASK);
EQLIB_API SPAWNINFO* GetRaidMember(int index);
EQLIB_API SPAWNINFO* GetGroupMember(int index);
EQLIB_API uint32_t GetGroupMainAssistTargetID();
EQLIB_API uint32_t GetRaidMainAssistTargetID(int index);
EQLIB_API bool IsAssistNPC(SPAWNINFO* pSpawn);

EQLIB_API CMQ2Alerts CAlerts;

struct RefreshKeyRingsThreadData
{
	char ItemName[256];
	CSidlScreenWnd *phWnd;
	bool bExact;
	bool bUseCmd;
};

EQLIB_API ITEMINFO* GetItemFromContents(CONTENTS* c);
EQLIB_API EQGroundItemListManager* GetItemList();

#include "MQ2Inlines.h"
#include "MQ2DataTypes.h"

EQLIB_API bool AddMacroLine(const char* FileName, char* szLine, size_t Linelen, int* LineNumber, int localLine);

EQLIB_API const char* GetLightForSpawn(SPAWNINFO* pSpawn);
EQLIB_API int GetSpellDuration(SPELL* pSpell, SPAWNINFO* pSpawn);
EQLIB_API int GetDeityTeamByID(int DeityID);
EQLIB_API int ConColor(SPAWNINFO* pSpawn);

EQLIB_API const char* GetGuildByID(int64_t GuildID);
EQLIB_API int64_t GetGuildIDByName(char* szGuild);

EQLIB_API CONTENTS* GetEnviroContainer();
EQLIB_API CContainerWnd* FindContainerForContents(CONTENTS* pContents);
EQLIB_API float FindSpeed(SPAWNINFO* pSpawn);
EQLIB_API bool IsNamed(SPAWNINFO* pSpawn);
EQLIB_API void GetItemLinkHash(CONTENTS* Item, char* Buffer, size_t BufferSize);

template <unsigned int _Size>
inline void GetItemLinkHash(CONTENTS* Item, char(&Buffer)[_Size])
{
	return GetItemLinkHash(Item, Buffer, _Size);
}

EQLIB_API bool GetItemLink(CONTENTS* Item, char* Buffer, size_t BufferSize, bool Clickable = true);

template <unsigned int _Size>
inline bool GetItemLink(CONTENTS* Item, char(&Buffer)[_Size], bool Clickable = true)
{
	return GetItemLink(Item, Buffer, _Size, Clickable);
}

EQLIB_API const char* GetLoginName();
EQLIB_API float DistanceToPoint(SPAWNINFO* pSpawn, float xLoc, float yLoc);
EQLIB_API float Distance3DToPoint(SPAWNINFO* pSpawn, float xLoc, float yLoc, float zLoc);
EQLIB_API char* ShowSpellSlotInfo(SPELL* pSpell, char* szBuffer, size_t BufferSize);
EQLIB_API char* ParseSpellEffect(SPELL* pSpell, int i, char* szBuffer, size_t BufferSize, int level = 100);

EQLIB_API int GetSpellAttrib(SPELL* pSpell, int index);
EQLIB_API int GetSpellBase(SPELL* pSpell, int index);
EQLIB_API int GetSpellBase2(SPELL* pSpell, int index);
EQLIB_API int GetSpellMax(SPELL* pSpell, int index);
EQLIB_API int GetSpellCalc(SPELL* pSpell, int index);

EQLIB_API void SlotValueCalculate(char* szBuff, SPELL* pSpell, int i, double mp = 1.0);
EQLIB_API int CalcValue(int calc, int base, int max, int tick, int minlevel = MAX_PC_LEVEL, int level = MAX_PC_LEVEL);
EQLIB_API char* GetSpellEffectName(int EffectID, char* szBuffer, size_t BufferSize);
EQLIB_API void GetGameDate(int* Month, int* Day, int* Year);
EQLIB_API void GetGameTime(int* Hour, int* Minute, int* Night);
EQLIB_API void SyntaxError(const char* szFormat, ...);
EQLIB_API void MacroError(const char* szFormat, ...);
EQLIB_API void FatalError(const char* szFormat, ...);
EQLIB_API char* GetSpellRestrictions(SPELL* pSpell, unsigned int nIndex, char* szBuffer, size_t BufferSize);
EQLIB_API void MQ2DataError(char* szFormat, ...);
EQLIB_API void DisplayOverlayText(const char* szText, int dwColor, uint32_t dwTransparency, uint32_t msFadeIn, uint32_t msFadeOut, uint32_t msHold);
EQLIB_API void CustomPopup(char* szPopText, bool bPopOutput);

EQLIB_API bool IsBardSong(SPELL* pSpell);
EQLIB_API bool IsSPAEffect(SPELL* pSpell, int EffectID);
EQLIB_API bool GetShortBuffID(SPELLBUFF* pBuff, int& nID);
EQLIB_API bool GetBuffID(SPELLBUFF* pBuff, int& nID);
EQLIB_API const char* GetLDoNTheme(int LDTheme);
EQLIB_API bool TriggeringEffectSpell(SPELL* aSpell, int i);
EQLIB_API bool BuffStackTest(SPELL* aSpell, SPELL* bSpell, bool bIgnoreTriggeringEffects = false, bool bTriggeredEffectCheck = false);
EQLIB_API uint32_t GetItemTimer(CONTENTS* pItem);
EQLIB_API CONTENTS* GetItemContentsBySlotID(int dwSlotID);
EQLIB_API CONTENTS* GetItemContentsByName(const char* ItemName);
EQLIB_API DWORD GetAvailableSlots(CONTENTS* pContainer, CONTENTS* pItem, int *firstavailableslot);
EQLIB_API bool LoH_HT_Ready();

/* MQ2DATAVARS */
EQLIB_API char* GetFuncParam(const char* szMacroLine, int ParamNum, char* szParamName, size_t ParamNameLen, char* szParamType, size_t ParamTypeLen);
EQLIB_API MQDataVar* FindMQ2DataVariable(const char* Name);
EQLIB_API bool AddMQ2DataVariable(const char* Name, const char* Index, MQ2Type* pType, MQDataVar** ppHead, const char* Default);
EQLIB_API bool AddMQ2DataVariableFromData(const char* Name, const char* Index, MQ2Type* pType, MQDataVar** ppHead, MQTypeVar Default);
EQLIB_API MQDataVar** FindVariableScope(const char* Name);
EQLIB_API bool DeleteMQ2DataVariable(const char* Name);
EQLIB_API void ClearMQ2DataVariables(MQDataVar** ppHead);
EQLIB_API void NewDeclareVar(SPAWNINFO* pChar, char* szLine);
EQLIB_API void NewDeleteVarCmd(SPAWNINFO* pChar, char* szLine);
EQLIB_API void NewVarset(SPAWNINFO* pChar, char* szLine);
EQLIB_API void NewVarcalc(SPAWNINFO* pChar, char* szLine);
EQLIB_API void NewVardata(SPAWNINFO* pChar, char* szLine);
EQLIB_API void DropTimers();

/*                 */

EQLIB_API bool LoadCfgFile(const char* Filename, bool Delayed = FromPlugin);
EQLIB_API char* GetFriendlyNameForGroundItem(PGROUNDITEM pItem, char* szName, size_t BufferSize);
EQLIB_API void ClearSearchSpawn(MQSpawnSearch* pSearchSpawn);
EQLIB_API SPAWNINFO* NthNearestSpawn(MQSpawnSearch* pSearchSpawn, int Nth, SPAWNINFO* pOrigin, bool IncludeOrigin = false);
EQLIB_API int CountMatchingSpawns(MQSpawnSearch* pSearchSpawn, SPAWNINFO* pOrigin, bool IncludeOrigin = false);
EQLIB_API SPAWNINFO* SearchThroughSpawns(MQSpawnSearch* pSearchSpawn, SPAWNINFO* pChar);
EQLIB_API bool SpawnMatchesSearch(MQSpawnSearch* pSearchSpawn, SPAWNINFO* pChar, SPAWNINFO* pSpawn);
EQLIB_API bool SearchSpawnMatchesSearchSpawn(MQSpawnSearch* pSearchSpawn1, MQSpawnSearch* pSearchSpawn2);
EQLIB_API char* ParseSearchSpawnArgs(char* szArg, char* szRest, MQSpawnSearch* pSearchSpawn);
EQLIB_API void ParseSearchSpawn(const char* Buffer, MQSpawnSearch* pSearchSpawn);
EQLIB_API char* FormatSearchSpawn(char* Buffer, size_t BufferSize, MQSpawnSearch* pSearchSpawn);
EQLIB_API bool IsPCNear(SPAWNINFO* pSpawn, float Radius);
EQLIB_API bool IsInGroup(SPAWNINFO* pSpawn, bool bCorpse = false);
EQLIB_API bool IsInFellowship(SPAWNINFO* pSpawn, bool bCorpse = false);
EQLIB_API bool IsInRaid(SPAWNINFO* pSpawn, bool bCorpse = false);
EQLIB_API bool IsAlert(SPAWNINFO* pChar, SPAWNINFO* pSpawn, uint32_t id);
EQLIB_API bool GetClosestAlert(SPAWNINFO* pSpawn, uint32_t id);
EQLIB_API bool IsAlert(SPAWNINFO* pChar, SPAWNINFO* pSpawn, uint32_t List);
EQLIB_API bool CheckAlertForRecursion(MQSpawnSearch* pSearchSpawn, uint32_t id);
EQLIB_API void WriteFilterNames();
EQLIB_API void RewriteSubstitutions();
EQLIB_API void RewriteAliases();
EQLIB_API void WriteAliasToIni(const char* Name, const char* Command);
EQLIB_API int FindSpellListByName(const char* szName);
EQLIB_API float StateHeightMultiplier(DWORD StandState);
extern void SuperWhoDisplay(SPAWNINFO* pChar, MQSpawnSearch* pSearchSpawn, DWORD Color);
extern void SuperWhoDisplay(SPAWNINFO* pSpawn, DWORD Color);

EQLIB_API bool        Include(const char* szFile, int* LineNumber);
EQLIB_API const char* GetFullZone(int ZoneID);
EQLIB_API int         GetZoneID(const char* ZoneShortName);
EQLIB_API const char* GetShortZone(int ZoneID);
EQLIB_API float       DistanceToSpawn3D(SPAWNINFO* pChar, SPAWNINFO* pSpawn);
EQLIB_API float       EstimatedDistanceToSpawn(SPAWNINFO* pChar, SPAWNINFO* pSpawn);
EQLIB_API bool        PlayerHasAAAbility(int AAIndex);
EQLIB_API const char* GetAANameByIndex(int AAIndex);
EQLIB_API int         GetAAIndexByName(const char* AAName);
EQLIB_API int         GetAAIndexByID(int ID);
EQLIB_API int         GetSkillIDFromName(const char* name);
EQLIB_API bool        InHoverState();
EQLIB_API int         GetGameState();
EQLIB_API int         GetWorldState();
EQLIB_API float       GetMeleeRange(PlayerClient*, PlayerClient*);
EQLIB_API uint32_t    GetSpellGemTimer(int nGem);
EQLIB_API uint32_t    GetSpellBuffTimer(int SpellID);
EQLIB_API bool        HasExpansion(int nExpansion);
EQLIB_API void        ListMercAltAbilities();
EQLIB_API CONTENTS*   FindItemBySlot(short InvSlot, short BagSlot = -1, ItemContainerInstance location = eItemContainerPossessions);
EQLIB_API CONTENTS*   FindItemBySlot2(const ItemGlobalIndex& idx);
EQLIB_API CONTENTS*   FindItemByName(const char* pName, bool bExact = false);
EQLIB_API CONTENTS*   FindItemByID(int ItemID);
EQLIB_API int         FindItemCountByName(const char* pName, bool bExact = false);
EQLIB_API int         FindItemCountByID(int ItemID);
EQLIB_API CONTENTS*   FindBankItemByName(const char* pName, bool bExact);
EQLIB_API CONTENTS*   FindBankItemByID(int ItemID);
EQLIB_API int         FindBankItemCountByName(const char* pName, bool bExact);
EQLIB_API int         FindBankItemCountByID(int ItemID);
EQLIB_API CInvSlot*   GetInvSlot(DWORD type, short Invslot, short Bagslot = -1);
EQLIB_API CInvSlot*   GetInvSlot2(const ItemGlobalIndex& idx);
EQLIB_API bool        IsItemInsideContainer(CONTENTS* pItem);
EQLIB_API bool        PickupItem(ItemContainerInstance type, CONTENTS* pItem);
EQLIB_API bool        DropItem(ItemContainerInstance type, short InvSlot, short Bagslot);
EQLIB_API bool        DropItem2(const ItemGlobalIndex& index);
EQLIB_API bool        ItemOnCursor();
EQLIB_API bool        OpenContainer(CONTENTS* pItem, bool hidden, bool flag = false);
EQLIB_API bool        CloseContainer(CONTENTS* pItem);
EQLIB_API int         GetTargetBuffByCategory(int category, unsigned int classmask = 0, int startslot = 0);
EQLIB_API int         GetTargetBuffBySubCat(const char* subcat, unsigned int classmask = 0, int startslot = 0);
EQLIB_API int         GetTargetBuffBySPA(int spa, bool bIncrease, int startslot = 0);
EQLIB_API bool        HasCachedTargetBuffSubCat(const char* subcat, SPAWNINFO* pSpawn, TargetBuff* pcTargetBuff, unsigned int classmask = 0);
EQLIB_API bool        HasCachedTargetBuffSPA(int spa, bool bIncrease, SPAWNINFO* pSpawn, TargetBuff* pcTargetBuff);
EQLIB_API int         GetSelfBuffByCategory(int category, unsigned int classmask = 0, int startslot = 0);
EQLIB_API int         GetSelfBuffBySubCat(const char* subcat, unsigned int classmask = 0, int startslot = 0);
EQLIB_API int         GetSelfBuffBySPA(int spa, bool bIncrease, int startslot = 0);
EQLIB_API int         GetSelfShortBuffBySPA(int spa, bool bIncrease, int startslot = 0);
EQLIB_API bool        IsSpellUsableForClass(SPELL* pSpell, unsigned int classmask = 0);
EQLIB_API bool        IsAegoSpell(SPELL* pSpell);
EQLIB_API int         GetSpellCategory(SPELL* pSpell);
EQLIB_API int         GetSpellSubcategory(SPELL* pSpell);
EQLIB_API SPELL*      GetSpellParent(int id);
EQLIB_API HMODULE GetCurrentModule();
EQLIB_API DWORD CALLBACK MQ2End(void* lpParameter);
EQLIB_API DWORD CALLBACK GetlocalPlayerOffset();
EQLIB_API void MQ2Shutdown();
EQLIB_API HANDLE hUnloadComplete;
EQLIB_API HANDLE hLoadComplete;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Functions that were built into commands and people used DoCommand to execute                  //

EQLIB_API void AttackRanged(PlayerClient* pRangedTarget = pTarget);
EQLIB_API void UseAbility(const char* sAbility);
EQLIB_OBJECT MQMacroBlockPtr GetNextMacroBlock();
EQLIB_OBJECT MQMacroBlockPtr GetCurrentMacroBlock();
EQLIB_API int GetMacroBlockCount();
EQLIB_API void EndAllMacros();
//                                                                                               //
///////////////////////////////////////////////////////////////////////////////////////////////////

// Parse Operations
std::string HandleParseParam(std::string_view strOriginal, bool bParseOnce = false);

enum class ModifyMacroMode { Default, Wrap, WrapNoDoubles };

std::string ModifyMacroString(std::string_view strOriginal, bool bParseOnce = false,
	ModifyMacroMode iOperation = ModifyMacroMode::Default);

EQLIB_API bool Calculate(const char* szFormula, double& Dest);

#include "MQ2TopLevelObjects.h"
#include "MQ2Commands.h"

constexpr int LIGHT_COUNT = 13;
//#define MAX_COMBINES		61
//#define MAX_ITEMTYPES		71
//#define MAX_SPELLEFFECTS	487

#define GAMESTATE_CHARSELECT    1
#define GAMESTATE_CHARCREATE    2
#define GAMESTATE_SOMETHING     4
#define GAMESTATE_INGAME        5
#define GAMESTATE_PRECHARSELECT -1
#define GAMESTATE_POSTFRONTLOAD 500
#define GAMESTATE_LOGGINGIN     253
#define GAMESTATE_UNLOADING     255

#define XKF_SHIFT               1
#define XKF_CTRL                2
#define XKF_LALT                4
#define XKF_RALT                8

#define CHATMENU_NEW			42
#define CHATMENU_ALWAYS_CHAT_HERE	43
#define CHATMENU_RENAME			44
#define CHATMENU_SCROLLBAR		45

// DO NOT CHANGE these user message id's.
// They must be identical between MQ2 and the
// injector process (macroquest2.exe).
//#define WM_USER_REGISTER_HK		(WM_USER + 1000)
//#define WM_USER_UNREGISTER_HK	(WM_USER + 1001)
//#define WM_USER_RESETLOADED		(WM_USER + 1002)
//#define WM_USER_SETLOADED		(WM_USER + 1003)

EQLIB_API void memchecks_tramp(char*, DWORD, void*, DWORD, bool);
EQLIB_API void memchecks(char*, DWORD, void*, DWORD, bool);
EQLIB_API void InitializeLoginPulse();
EQLIB_API void RemoveAutoBankMenu();
EQLIB_API bool WillFitInBank(CONTENTS* pContent);
EQLIB_API bool WillFitInInventory(CONTENTS* pContent);
EQLIB_API void AddAutoBankMenu();
EQLIB_API void AutoBankPulse();
EQLIB_API KeypressHandler* GetKeyPresshandler();
EQLIB_API AggroMeterManagerClient* GetAggroInfo();
EQLIB_API ClientSOIManager* GetAuraMgr();
EQLIB_API CBroadcast* GetTextOverlay();
EQLIB_API MercenaryAlternateAdvancementManagerClient* GetMercAltAbilities();
EQLIB_API bool Anonymize(char* name, int maxlen, int LootFlag = 0);
EQLIB_API bool Anonymize2(CXStr& name, int LootFlag = 0);
EQLIB_API void UpdatedMasterLooterLabel();
//EQLIB_API EQGroundItemListManager* GetItemList();

EQLIB_API int MQ2ExceptionFilter(unsigned int code, struct _EXCEPTION_POINTERS* ex, const char * description, ...);

// These are replaced with our own wrappers
#undef GetPrivateProfileInt
#undef GetPrivateProfileString
#undef WritePrivateProfileSection
#undef WritePrivateProfileString
inline int GetPrivateProfileInt(std::string Section, std::string Key, int DefaultValue, std::string iniFileName)
{
	return GetPrivateProfileIntA(Section.data(), Key.data(), DefaultValue, iniFileName.data());
}

inline int GetPrivateProfileInt(char* Section, char* Key, int DefaultValue, char* iniFileName)
{
	return GetPrivateProfileIntA(Section, Key, DefaultValue, iniFileName);
}

inline int GetPrivateProfileString(std::string Section, std::string Key, std::string DefaultValue, char* Return, size_t Size, std::string iniFileName)
{
	return GetPrivateProfileStringA(Section.data(), Key.data(), DefaultValue.data(), Return, Size, iniFileName.data());
}

inline int GetPrivateProfileString(char* Section, char* Key, char* DefaultValue, char* Return, size_t Size, char* iniFileName)
{
	return GetPrivateProfileStringA(Section, Key, DefaultValue, Return, Size, iniFileName);
}

inline bool WritePrivateProfileSection(std::string Section, std::string KeysAndValues, std::string iniFileName)
{
	return WritePrivateProfileSectionA(Section.data(), KeysAndValues.data(), iniFileName.data());	
}

inline bool WritePrivateProfileSection(char* Section, char* KeysAndValues, char* iniFileName)
{
	return WritePrivateProfileSectionA(Section, KeysAndValues, iniFileName);
}

inline bool WritePrivateProfileString(std::string Section, std::string Key, std::string Value, std::string iniFileName)
{
	return WritePrivateProfileStringA(Section.data(), Key.data(), Value.data(), iniFileName.data());
}

inline bool WritePrivateProfileString(char* Section, char* Key, char* Value, char* iniFileName)
{
	return WritePrivateProfileStringA(Section, Key, Value, iniFileName);
}