/*****************************************************************************
    eqlib.dll: MacroQuest's extension DLL for EverQuest
    Copyright (C) 2002-2003 Plazmic

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
******************************************************************************/

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x510
#define DIRECTINPUT_VERSION 0x800

#if !defined(CINTERFACE)
#error /DCINTERFACE
#endif

#define DBG_SPEW

#include "MQ2Main.h"
namespace MQ2Globals
{
DWORD gGameState = 0;

DWORD ThreadID = 0;
BOOL g_Loaded = FALSE;

HMODULE ghModule = NULL;
HINSTANCE ghInstance = NULL;
PHOTKEY pHotkey = NULL;
BOOL gbUnload = FALSE;
DWORD gpHook = NULL;
PMACROBLOCK gMacroBlock = NULL;
PMACROSTACK gMacroStack = NULL;
PEVENTSTACK gEventStack = NULL;
PMACROBLOCK gEventFunc[NUM_EVENTS] = {NULL};
UCHAR gLastFind = 0;
DOUBLE gZFilter=10000.0f;
DOUBLE gFaceAngle=10000.0f;
DOUBLE gLookAngle=10000.0f;
PVARSTRINGS gMacroStr = NULL;
PVARARRAYS gArray = NULL;
CHAR gszEQPath[MAX_STRING] = {0};
CHAR gszMacroPath[MAX_STRING] = {0};
CHAR gszVersion[MAX_STRING] = {0};
CHAR gszLogPath[MAX_STRING] = {0};
CHAR gszINIPath[MAX_STRING] = {0};
CHAR gszINIFilename[MAX_STRING] = {0};
CHAR gszItemDB[MAX_STRING] = {0};
CHAR gszMacroName[MAX_STRING] = {0};
CHAR szLastCommand[MAX_STRING] = {0};
DWORD gEventChat = 0;
DWORD gRunning = 0;
BOOL gbMoving = FALSE;
DWORD gMaxTurbo = 0;
BOOL gInClick = FALSE;
BOOL gZoning = FALSE;
BOOL WereWeZoning = TRUE;
BOOL gbInDInput = FALSE;
BOOL gbInChat = FALSE;
BOOL gbInDState = FALSE;
BOOL gbInDAcquire = FALSE;
BOOL gFilterSkillsAll = FALSE;
BOOL gFilterSkillsIncrease = FALSE;
BOOL gFilterTarget = FALSE;
BOOL gFilterDebug = FALSE;
BOOL gFilterMoney = FALSE;
BOOL gFilterFood = FALSE;
DWORD gUseMQChatWnd = 1;     // default is on
BOOL gFilterMacro = FALSE;
BOOL gFilterEncumber = FALSE;
BOOL gFilterCustom = TRUE;
BOOL gSpewToFile = FALSE;
BOOL gbDoAutoRun = FALSE;
BOOL gMQPauseOnChat = FALSE;
BOOL gKeepKeys = FALSE;
SWHOFILTER gFilterSWho = {0};

DOUBLE DegToRad = 57.295779513082320876846364344191;
DOUBLE PI = 3.1415926535;

PKEYPRESS gKeyStack = NULL;
PTIMER gTimer = NULL;
LONG gDelay = 0;
LONG gDelayZoning = 0;
PALERTLIST gpAlertList = NULL;
BOOL gMacroPause = FALSE;
ACTORINFO EnviroActor = {0};
SPAWNINFO EnviroTarget = {0};
PGROUNDITEM pGroundTarget = NULL;
SPAWNINFO DoorEnviroTarget = {0};
PDOOR pDoorTarget = NULL;
PITEMDB gItemDB = NULL;
BOOL bRunNextCommand = FALSE;
BOOL gTurbo = FALSE;
PDEFINE pDefines = NULL;
PEVENTLIST pEventList = NULL;
CHAR gLastFindSlot[MAX_STRING]={0};
CHAR gLastError[MAX_STRING] = {0};
HWND ghWnd = NULL;
PFILTER gpFilters = NULL;
PSPELLFAVORITE EQADDR_SPELLFAVORITES = NULL;

BOOL g_bInDXMouse = FALSE;
PMOUSESPOOF gMouseData = NULL;
BOOL bDetMouse = TRUE;


// EQ Functions Initialization
fEQCommand        cmdHelp        =  NULL;
fEQCommand        cmdWho         =  NULL;
fEQCommand        cmdWhoTarget   =  NULL;
fEQCommand        cmdLocation    =  NULL;
fEQCommand        cmdFace        =  NULL;
fEQCommand        cmdTarget      =  NULL;
fEQCommand        cmdCharInfo    =  NULL;
fEQCommand        cmdFilter      =  NULL;
fEQCommand        cmdDoAbility   =  NULL;
fEQCommand        cmdCast        =  NULL;
fEQGetStringByID  GetRaceByID    =  NULL;
fEQGetStringByID  GetClassByID   =  NULL;
fEQGetStringByID  GetDeityByID   =  NULL;
fEQGetStringByID  GetBodyTypeByID=  NULL;
fEQScreenItem     ScreenItem     =  NULL;
fEQScreenSpawn    ScreenSpawn    =  NULL;
fEQNewUIINI       NewUIINI   =  NULL;
fEQMemSpell       cmdMemSpell    =  NULL;
fEQLoadSpells     cmdLoadSpells  =  NULL;
fEQSelectItem     cmdSelectItem  =  NULL;
fEQBuyItem        cmdBuyItem     =  NULL;
fEQSellItem       cmdSellItem    =  NULL;
fEQProcGameEvts   ProcessGameEvents = NULL;
fEQSendMessage    send_message = NULL;

// EQ Address Initialization
DWORD EQADDR_HWND=0;
DWORD EQADDR_COMMANDS=0;
DWORD EQADDR_MEMCHECK=0;
DWORD EQADDR_MEMCHECK2=0;
DWORD EQADDR_MEMCHECKADDR1=0;
DWORD EQADDR_MEMCHECKADDR2=0;
DWORD EQADDR_MEMCHECK3=0;
PCHAR EQADDR_SERVERHOST=0;
PCHAR EQADDR_SERVERNAME=0;
PCHAR *EQADDR_ACTIVEMERCHANT=0;
PCHAR *EQADDR_ACTIVECORPSE=0;
PPACKLOC EQADDR_PACKLOCS=0;
DWORD EQADDR_CONVERTITEMTAGS=0;
PCMDLIST EQADDR_CMDLIST=0;

PBYTE EQADDR_ATTACK=0;
PBYTE EQADDR_NOTINCHATMODE=0;

//DWORD *EQADDR_CLSMAINNEWUI=0;
//DWORD EQADDR_CLSITEMS=0;
//DWORD EQADDR_CLSSPAWNS=0;


//PZONELIST **EQADDR_ZONELIST=0;
//PSPAWNINFO *EQADDR_SPAWNLIST=0;
//PSPAWNINFO *EQADDR_SPAWNTAIL=0;
//PSPAWNINFO *EQADDR_CHAR=0;
//PCHARINFO *EQADDR_CHAR_INFO=0;
//PSPAWNINFO *EQADDR_TARGET=0;
PCHAR EQADDR_LASTTELL=0;
PGROUNDITEM *EQADDR_ITEMS=0;
_SPELLPOINTER** EQADDR_SPELLS=0;
//PSPAWNINFO *EQADDR_GROUP=0;
PBYTE EQADDR_GROUPCOUNT=0;
PVOID EQADDR_GWORLD=0;
PDOORTABLE *EQADDR_DOORS=0;
DWORD EQADDR_GUILDLIST=0;
PDWORD EQADDR_DOABILITYLIST=0;

PBYTE EQADDR_DOABILITYAVAILABLE=0;


PBYTE EQADDR_ENCRYPTPAD=0;
PBYTE EQADDR_ENCRYPTPAD2=0;
PBYTE EQADDR_ENCRYPTPAD3=0;

EQLIB_VAR DWORD *pScreenX=0;
EQLIB_VAR DWORD *pScreenY=0;

PMOUSEINFO EQADDR_MOUSE=0;
PMOUSECLICK EQADDR_MOUSECLICK=0;

DWORD EQADDR_DIMAIN=0;
IDirectInputDevice8A **EQADDR_DIKEYBOARD=0;
IDirectInputDevice8A **EQADDR_DIMOUSE=0;

// Motd and Pulse's mouse variables
BOOL gMouseLeftClickInProgress = FALSE;
BOOL gMouseRightClickInProgress = FALSE;
// End of mouse variables

// Arrays  (Note:  See also EQLib_Utilities.cpp)
DIKEYID gDiKeyID[] = {
#include "dikeys.h"
    {NULL,0}
};

DWORD *EQADDR_SLOTLIST = 0;
//PZONEINFO EQADDR_ZONEINFO = 0;



PCHAR szHeading[] = {
    "south",                //0
    "south by southeast",   //1
    "southeast",            //2
    "east by southeast",    //3
    "east",                 //4
    "east by northeast",    //5
    "northeast",            //6
    "north by northeast",   //7
    "north",                //8
    "north by northwest",   //9
    "northwest",            //10
    "west by northwest",    //11
    "west",                 //12
    "west by southwest",    //13
    "southwest",            //14
    "south by southwest"    //15
};

PCHAR szHeadingShort[] = {
    "S",    //0
    "SSE",  //1
    "SE",   //2
    "ESE",  //3
    "E",    //4
    "ENE",  //5
    "NE",   //6
    "NNE",  //7
    "N",    //8
    "NNW",  //9
    "NW",   //10
    "WNW",  //11
    "W",    //12
    "WSW",  //13
    "SW",   //14
    "SSW"   //15
};

PCHAR szSize[] = {
    "Tiny",
    "Small",
    "Normal",
    "Large",
    "Giant",
    "Huge", //?
    "Unknown" //?
};

PCHAR szSpawnType[] = {
    "player",
    "NPC",
    "corpse",
    "any",
	"pet",
    NULL // SuperWhoTarget
};

PCHAR szGuildStatus[] = {
	"member",
	"officer",
	"leader",
	NULL
};

PCHAR szGender[] = {
    "male",
    "female",
    "neuter",
    "unknown"
};

PCHAR szDeityTeam[] = {
    "none",     //0
    "good",     //1
    "neutral",  //2
    "evil"      //3
};

PCHAR szLights[] = {
    "NONE",    // 0  - No light
    "CDL", // 1  - Candle
    "TR",  // 2  - Torch
    "TGS", // 3  - Tiny Glowing Skull
    "SL",  // 4  - Small Lantern
    "SoM", // 5  - Stein of Moggok
    "LL",  // 6  - Large Lantern
    "FL",  // 7  - Flameless lantern, Halo of Light
    "GOS", // 8  - Globe of stars
    "LG",  // 9  - Light Globe
    "LS",  // 10 - Lightstone, Burnt-out lightstone, wispstone
    "GLS", // 11 - Greater lightstone
    "FBE", // 12 - Fire Beatle Eye, Firefly Globe
    "CL"  // 13 - Coldlight
};

BYTE LightBrightness[] = {
    0,      //0
    1,      //1
    2,      //2
    3,      //3
    6,      //4
    7,      //5
    8,      //6
    9,      //7
    10,     //8
    0,      //9
    0,      //10
    0,      //11
    4,      //12
    5       //13
};

PCHAR szSkills[] = {
    #include "skills.h"
    NULL
};


PCHAR szCombineTypes[] = {
    #include "combines.h"
    NULL
};

PCHAR szItemTypes[] = {
    #include "itemtypes.h"
    NULL
};

PCHAR szZoneExpansionName[] = {
    "Original EQ",              //0
    "Kunark",                   //1
    "Velious",                  //2
    "Luclin",                   //3
    "Planes of Power",          //4
    "Legacy of Ykesha",         //5
    "Lost Dungeons of Norrath"  //6
};

#include "grounds.h"
PCHAR szItemName[] = {
    #include "weapons.h"
    NULL
};


CEverQuest **ppEverQuest=(CEverQuest**)pinstCEverQuest;
CDisplay **ppDisplay=(CDisplay**)pinstCDisplay;
EQ_PC **ppPCData=(EQ_PC**)pinstPCData;
EQ_Character **ppCharData=(EQ_Character**)pinstCharData;
EQPlayer **ppCharSpawn=(EQPlayer**)pinstCharSpawn;
EQPlayer **ppActiveMerchant=(EQPlayer**)pinstActiveMerchant;
EQPlayer **ppSpawnList=(EQPlayer**)pinstSpawnList;
EQPlayer **ppSpawnListTail=(EQPlayer**)pinstSpawnListTail;
EQWorldData **ppWorldData=(EQWorldData**)pinstWorldData;
SpellManager **ppSpellMgr=(SpellManager**)pinstSpellManager;
CInvSlot **ppSelectedItem=(CInvSlot **)pinstSelectedItem;
EQPlayer **ppGroup=(EQPlayer**)pinstGroup;
EQPlayer **ppTarget=(EQPlayer**)pinstTarget;
EqSwitchManager **ppSwitchMgr=(EqSwitchManager**)pinstSwitchManager;
EQItemList **ppItemList=(EQItemList**)pinstEQItemList;
SPELLFAVORITE *pSpellSets=(SPELLFAVORITE *)pinstSpellSets;
EQZoneInfo *pZoneInfo=(EQZoneInfo*)instEQZoneInfo;

/* WINDOW INSTANCES */
CContextMenuManager **ppContextMenuManager=(CContextMenuManager**)pinstCContextMenuManager;
CCursorAttachment **ppCursorAttachment=(CCursorAttachment**)pinstCCursorAttachment;
CSocialEditWnd **ppSocialEditWnd=(CSocialEditWnd**)pinstCSocialEditWnd;
CInvSlotMgr **ppInvSlotMgr=(CInvSlotMgr**)pinstCInvSlotMgr;
CContainerMgr **ppContainerMgr=(CContainerMgr**)pinstCContainerMgr;
CChatManager **ppChatManager=(CChatManager**)pinstCChatManager;
CConfirmationDialog **ppConfirmationDialog=(CConfirmationDialog**)pinstCConfirmationDialog;
CFacePick **ppFacePick=(CFacePick**)pinstCFacePick;
//CItemDisplayMgr **ppItemDisplayMgr=(CItemDisplayMgr**)pinstCItemDisplayMgr;
//CSpellDisplayMgr **ppSpellDisplayMgr=(CSpellDisplayMgr**)pinstCSpellDisplayMgr;
CNoteWnd **ppNoteWnd=(CNoteWnd**)pinstCNoteWnd;
CHelpWnd **ppHelpWnd=(CHelpWnd**)pinstCHelpWnd;
CTipWnd **ppTipWndOFDAY=(CTipWnd**)pinstCTipWndOFDAY;
CTipWnd **ppTipWndCONTEXT=(CTipWnd**)pinstCTipWndCONTEXT;
CBookWnd **ppBookWnd=(CBookWnd**)pinstCBookWnd;
CFriendsWnd **ppFriendsWnd=(CFriendsWnd**)pinstCFriendsWnd;
CMusicPlayerWnd **ppMusicPlayerWnd=(CMusicPlayerWnd**)pinstCMusicPlayerWnd;
CAlarmWnd **ppAlarmWnd=(CAlarmWnd**)pinstCAlarmWnd;
CLoadskinWnd **ppLoadskinWnd=(CLoadskinWnd**)pinstCLoadskinWnd;
CPetInfoWnd **ppPetInfoWnd=(CPetInfoWnd**)pinstCPetInfoWnd;
CTrainWnd **ppTrainWnd=(CTrainWnd**)pinstCTrainWnd;
CSkillsWnd **ppSkillsWnd=(CSkillsWnd**)pinstCSkillsWnd;
CSkillsSelectWnd **ppSkillsSelectWnd=(CSkillsSelectWnd**)pinstCSkillsSelectWnd;
CAAWnd **ppAAWnd=(CAAWnd**)pinstCAAWnd;
CGroupWnd **ppGroupWnd=(CGroupWnd**)pinstCGroupWnd;
CJournalNPCWnd **ppJournalNPCWnd=(CJournalNPCWnd**)pinstCJournalNPCWnd;
CGroupSearchWnd **ppGroupSearchWnd=(CGroupSearchWnd**)pinstCGroupSearchWnd;
CGroupSearchFiltersWnd **ppGroupSearchFiltersWnd=(CGroupSearchFiltersWnd**)pinstCGroupSearchFiltersWnd;
CRaidWnd **ppRaidWnd=(CRaidWnd**)pinstCRaidWnd;
CRaidOptionsWnd **ppRaidOptionsWnd=(CRaidOptionsWnd**)pinstCRaidOptionsWnd;
CBreathWnd **ppBreathWnd=(CBreathWnd**)pinstCBreathWnd;
CMapToolbarWnd **ppMapToolbarWnd=(CMapToolbarWnd**)pinstCMapToolbarWnd;
CMapViewWnd **ppMapViewWnd=(CMapViewWnd**)pinstCMapViewWnd;
CEditLabelWnd **ppEditLabelWnd=(CEditLabelWnd**)pinstCEditLabelWnd;
COptionsWnd **ppOptionsWnd=(COptionsWnd**)pinstCOptionsWnd;
CBuffWindow **ppBuffWindowSHORT=(CBuffWindow**)pinstCBuffWindowSHORT;
CBuffWindow **ppBuffWindowNORMAL=(CBuffWindow**)pinstCBuffWindowNORMAL;
CTargetWnd **ppTargetWnd=(CTargetWnd**)pinstCTargetWnd;
CColorPickerWnd **ppColorPickerWnd=(CColorPickerWnd**)pinstCColorPickerWnd;
CHotButtonWnd **ppHotButtonWnd=(CHotButtonWnd**)pinstCHotButtonWnd;
CPlayerWnd **ppPlayerWnd=(CPlayerWnd**)pinstCPlayerWnd;
CCastingWnd **ppCastingWnd=(CCastingWnd**)pinstCCastingWnd;
CCastSpellWnd **ppCastSpellWnd=(CCastSpellWnd**)pinstCCastSpellWnd;
CSpellBookWnd **ppSpellBookWnd=(CSpellBookWnd**)pinstCSpellBookWnd;
CInventoryWnd **ppInventoryWnd=(CInventoryWnd**)pinstCInventoryWnd;
CBankWnd **ppBankWnd=(CBankWnd**)pinstCBankWnd;
CQuantityWnd **ppQuantityWnd=(CQuantityWnd**)pinstCQuantityWnd;
CTextEntryWnd **ppTextEntryWnd=(CTextEntryWnd**)pinstCTextEntryWnd;
CFileSelectionWnd **ppFileSelectionWnd=(CFileSelectionWnd**)pinstCFileSelectionWnd;
CLootWnd **ppLootWnd=(CLootWnd**)pinstCLootWnd;
CActionsWnd **ppActionsWnd=(CActionsWnd**)pinstCActionsWnd;
CMerchantWnd **ppMerchantWnd=(CMerchantWnd**)pinstCMerchantWnd;
CTradeWnd **ppTradeWnd=(CTradeWnd**)pinstCTradeWnd;
CBazaarWnd **ppBazaarWnd=(CBazaarWnd**)pinstCBazaarWnd;
CBazaarSearchWnd **ppBazaarSearchWnd=(CBazaarSearchWnd**)pinstCBazaarSearchWnd;
CGiveWnd **ppGiveWnd=(CGiveWnd**)pinstCGiveWnd;
CSelectorWnd **ppSelectorWnd=(CSelectorWnd**)pinstCSelectorWnd;
CTrackingWnd **ppTrackingWnd=(CTrackingWnd**)pinstCTrackingWnd;
CInspectWnd **ppInspectWnd=(CInspectWnd**)pinstCInspectWnd;
CFeedbackWnd **ppFeedbackWnd=(CFeedbackWnd**)pinstCFeedbackWnd;
CBugReportWnd **ppBugReportWnd=(CBugReportWnd**)pinstCBugReportWnd;
CVideoModesWnd **ppVideoModesWnd=(CVideoModesWnd**)pinstCVideoModesWnd;
CCompassWnd **ppCompassWnd=(CCompassWnd**)pinstCCompassWnd;
CPlayerNotesWnd **ppPlayerNotesWnd=(CPlayerNotesWnd**)pinstCPlayerNotesWnd;
CGemsGameWnd **ppGemsGameWnd=(CGemsGameWnd**)pinstCGemsGameWnd;
CStoryWnd **ppStoryWnd=(CStoryWnd**)pinstCStoryWnd;
//CFindLocationWnd **ppFindLocationWnd=(CFindLocationWnd**)pinstCFindLocationWnd;
//CAdventureRequestWnd **ppAdventureRequestWnd=(CAdventureRequestWnd**)pinstCAdventureRequestWnd;
//CAdventureStatsWnd **ppAdventureStatsWnd=(CAdventureStatsWnd**)pinstCAdventureStatsWnd;
//CAdventureLeaderboardWnd **ppAdventureLeaderboardWnd=(CAdventureLeaderboardWnd**)pinstCAdventureLeaderboardWnd;
CBodyTintWnd **ppBodyTintWnd=(CBodyTintWnd**)pinstCBodyTintWnd;
CGuildMgmtWnd **ppGuildMgmtWnd=(CGuildMgmtWnd**)pinstCGuildMgmtWnd;
CJournalTextWnd **ppJournalTextWnd=(CJournalTextWnd**)pinstCJournalTextWnd;
CJournalCatWnd **ppJournalCatWnd=(CJournalCatWnd**)pinstCJournalCatWnd;
CPetitionQWnd **ppPetitionQWnd=(CPetitionQWnd**)pinstCPetitionQWnd;
CSoulmarkWnd **ppSoulmarkWnd=(CSoulmarkWnd**)pinstCSoulmarkWnd;
CTimeLeftWnd **ppTimeLeftWnd=(CTimeLeftWnd**)pinstCTimeLeftWnd;

PMQPLUGIN pPlugins=0;
DWORD ManaGained=0;
DWORD HealthGained=0;
PALIAS pAliases=0;
PMQCOMMAND pCommands=0;
};