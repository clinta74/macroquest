	int         AugFlag;
	UINT        NewArmorID;
	int         ArmorType;
	int64_t     MerchantSlot;
	ArrayClass_RO RealEstateArray;
	int         RealEstateID;
	int64_t     DontKnow;
	int         StackCount;
	int         ConvertItemID;
	LONG        LastEquipped;
	bool        bRankDisabled;
	ITEMINFO*   Item1;
	int         ScriptIndex;
	int         Power;
	ItemBaseContainer2 Contents;                     // Size is 0x1c
	EqItemGuid  ItemGUID;
	CXStr       ConvertItemName;
	int         EvolvingMaxLevel;
	bool        bItemNeedsUpdate;
	bool        bCopied;
	int         Open;
	bool        bCollected;
	bool        IsEvolvingItem;
	int         Charges;
	UINT        Tint;
	int         Luck;
	ItemGlobalIndex2 GlobalIndex;                    // Size is 0xa (0xc)
	int         NoDropFlag;
	UINT        LastCastTime;
	int         ItemColor;
	int         OrnamentationIcon;
	int         ID;
	UINT        RespawnTime;
	int         GroupID;
	CHAR        ActorTag2[0x1e];
	UINT        ItemHash;
	int         EvolvingCurrentLevel;
	CXStr       SaveString;
	int64_t     Price;
	bool        bConvertable;
	CHAR        ActorTag1[0x1e];
	int         MerchantQuantity;
	DOUBLE      EvolvingExpPct;
	int         NoteStatus;
	bool        bDisableAugTexture;
	bool        bRealEstateItemPlaceable;
