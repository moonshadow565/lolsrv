#pragma once
#include <array>
#include <io.hpp>
#include <optional>
#include <r3d.hpp>
#include <string>
#include <variant>
#include <vector>

enum Channel : uint32_t {
    CHANNEL_DEFAULT = 0x0,
    CHANNEL_GENERIC_APP_TO_SERVER = 0x1,
    CHANNEL_SYNCHCLOCK = 0x2,
    CHANNEL_GENERIC_APP_BROADCAST = 0x3,
    CHANNEL_GENERIC_APP_BROADCAST_UNRELIABLE = 0x4,
    CHANNEL_MIDDLE_TIER_CHAT = 0x5,
    CHANNEL_MIDDLE_TIER_ROSTER = 0x6,
    CHANNEL_NUM_TOTAL = 0x7,
};

enum class PKT_ID : uint16_t {};

enum class EGP_ID : uint16_t {};

struct DefaultPayload {};

struct EGP_RequestJoinTeam : DefaultPayload {
    int32_t Id_Player = {};
    uint32_t team = {};
};

struct EGP_RequestRename : DefaultPayload {
    int64_t Id_Player = {};
    int32_t skinID = {};
    std::string buffer = {};
};

struct EGP_RequestReskin : DefaultPayload {
    int64_t Id_Player = {};
    int32_t skinID = {};
    std::string buffer = {};
};

struct EGP_TeamRosterUpdate : DefaultPayload {
    uint32_t teamsize_order = {};
    uint32_t teamsize_chaos = {};
    std::array<int64_t, 24> orderMembers = {};
    std::array<int64_t, 24> chaosMembers = {};
    uint32_t current_teamsize_order = {};
    uint32_t current_teamsize_chaos = {};
};

struct EGP_Chat : DefaultPayload {
    int32_t clientID = {};
    uint32_t chatType = {};
    std::string message = {};
};

struct CommonBasicAttack {
    uint32_t targetNetId = {};
    float extraTime = {};
    uint32_t missileNextID = {};
    uint8_t attackSlot = {};
};

struct ConnectionInfo {
    int32_t mClientID = {};
    int64_t mPlayerID = {};
    float mPercentage = {};
    float mETA = {};
    int16_t mCount = {};
    uint16_t mPing = {};
    uint8_t mPad = {};
    uint8_t mReady = {};
    std::string mState = {};
};

struct PlayerLiteInfo {
    int64_t ID = {};
    uint16_t summonorLevel = {};
    uint32_t summonorSpell1 = {};
    uint32_t summonorSpell2 = {};
    bool isBot = {};
    uint32_t teamId = {};
    std::string botName = {};
    std::string skinName = {};
    uint32_t botDifficulty = {};
    uint32_t profileIconId = {};
};

struct ItemData {
    uint32_t itemID = {};
    uint8_t slot = {};
    uint8_t itemsInSlot = {};
    uint8_t spellCharges = {};
};

struct DefaultPacket {};

struct WithSyncID {};

struct PKT_Basic_Attack {
    uint32_t fromID = {};
    CommonBasicAttack data = {};
};

struct PKT_Basic_Attack_Pos {
    uint32_t fromID = {};
    CommonBasicAttack data = {};
    r3dPoint2D pos = {};
};

struct PKT_BuyItemAns : DefaultPacket {
    uint32_t fromID = {};
    uint8_t slot = {};
    uint32_t itemID = {};
    uint8_t itemsInSlot = {};
    bool useOnBought = {};
};

struct PKT_BuyItemReq : DefaultPacket {
    uint32_t fromID = {};
    uint32_t itemID = {};
};

struct PKT_C2S_CharSelected : DefaultPacket {
    uint32_t fromID = {};
};

struct PKT_C2S_ClientReady : DefaultPacket {
    uint32_t fromID = {};
};

struct PKT_C2S_MapPing : DefaultPacket {
    uint32_t fromID = {};
    r3dPoint3D pos = {};
    uint32_t target = {};
    uint8_t pingCategory = {};
};

struct PKT_C2S_Ping_Load_Info : DefaultPacket {
    uint32_t fromID = {};
    ConnectionInfo mConnectionInfo = {};
};

struct PKT_C2S_PlayEmote : DefaultPacket {
    uint32_t fromID = {};
    uint32_t mEmoteId = {};
};

struct PKT_C2S_QueryStatusReq : DefaultPacket {
    uint32_t fromID = {};
};

struct PKT_C2S_Reconnect : DefaultPacket {
    uint32_t fromID = {};
    bool isFullReconnect = {};
};

struct PKT_NPC_Die : DefaultPacket {
    uint32_t fromID = {};
    uint32_t killerNetID = {};
    uint8_t damageType = {};
    uint8_t mSpellSourceType = {};
    float DeathDuration = {};
    bool becomeZombie = {};
};

struct PKT_NPC_IssueOrderReq : DefaultPacket {
    uint32_t fromID = {};
    uint8_t order = {};
    r3dPoint3D pos = {};
    uint32_t targetNetID = {};
};

struct PKT_NPC_LevelUp : DefaultPacket {
    uint32_t fromID = {};
    uint8_t mLevel = {};
    uint8_t mPoints = {};
};

struct PKT_NPC_UpgradeSpellAns : DefaultPacket {
    uint32_t fromID = {};
    uint8_t slot = {};
    uint8_t spellLevel = {};
    uint8_t spellTrainingPoints = {};
};

struct PKT_NPC_UpgradeSpellReq : DefaultPacket {
    uint32_t fromID = {};
    uint8_t slot = {};
};

struct PKT_OnEnterVisiblityClient : DefaultPacket, WithSyncID {
    uint32_t fromID = {};
    std::vector<ItemData> items = {};
    std::optional<r3dPoint3D> lookat = {};
    std::optional<r3dPoint2D> position = {};
    uint32_t syncID = {};
};

struct PKT_RemoveItemAns : DefaultPacket {
    uint32_t fromID = {};
    uint8_t slot = {};
    uint8_t itemsInSlot = {};
};

struct PKT_RemoveItemReq : DefaultPacket {
    uint32_t fromID = {};
    uint8_t slot = {};
    bool bSell = {};
};

struct PKT_S2C_ChangeCharacterData : DefaultPacket {
    uint32_t fromID = {};
    uint32_t id = {};
    bool useSpells = true;
    std::string skinName = {};
};

struct PKT_S2C_CreateHero : DefaultPacket {
    uint32_t fromID = {};
    uint32_t netObjID = {};
    int32_t playerUID = {};
    uint8_t netNodeID = {};
    uint8_t skillLevel = {};
    bool teamIsOrder = {};
    bool isBot = {};
    uint8_t botRank = {};
    uint8_t spawnPosIndex = {};
    int32_t skinID = {};
    std::string Name = {};
    std::string Skin = {};
};

struct PKT_S2C_CreateTurret : DefaultPacket {
    uint32_t fromID = {};
    uint32_t netObjID = {};
    uint8_t netNodeID = {};
    std::string Name = {};
};

struct PKT_S2C_FaceDirection : DefaultPacket {
    uint32_t fromID = {};
    r3dPoint3D direction = {};
};

struct PKT_S2C_EndSpawn : DefaultPacket {
    uint32_t fromID = {};
};

struct PKT_S2C_MapPing : DefaultPacket {
    uint32_t fromID = {};
    r3dPoint3D pos = {};
    uint32_t target = {};
    uint32_t src = {};
    uint8_t pingCategory = {};
    bool bPlayAudio = {};
    bool bShowChat = {};
    bool bPingThrottled = {};
};

struct PKT_S2C_Ping_Load_Info : DefaultPacket {
    uint32_t fromID = {};
    ConnectionInfo mConnectionInfo = {};
};

struct PKT_S2C_PlayAnimation : DefaultPacket {
    uint32_t fromID = {};
    uint32_t flags = {};
    float scaleTime = {};
    std::string animationName = {};
};

struct PKT_S2C_PlayEmote : DefaultPacket {
    uint32_t fromID = {};
    uint32_t mEmoteId = {};
};

struct PKT_S2C_QueryStatusAns : DefaultPacket {
    uint32_t fromID = {};
    bool ok = {};
};

struct PKT_S2C_Reconnect : DefaultPacket {
    uint32_t fromID = {};
    int32_t cid = {};
};

struct PKT_S2C_StartGame : DefaultPacket {
    uint32_t fromID = {};
    uint8_t tournamentEnabled = {};
};

struct PKT_S2C_StartSpawn : DefaultPacket {
    uint32_t fromID = {};
    uint8_t numBotsOrder = {};
    uint8_t numBotsChaos = {};
};

struct PKT_S2C_ToggleFoW : DefaultPacket {
    uint32_t fromID = {};
};

struct PKT_SpawnMinionS2C : DefaultPacket {
    uint32_t fromID = {};
    uint32_t netObjID = {};
    uint8_t netNodeID = {};
    r3dPoint3D Pos = {};
    int32_t skinID = {};
    uint32_t CloneID = {};
    uint32_t TeamID = {};
    float visibilitySize = {};
    bool IgnoreCollision = {};
    bool IsWard = {};
    bool useBehaviorTreeAI = {};
    std::string Name = {};
    std::string SkinName = {};
};

struct PKT_SwapItemAns : DefaultPacket {
    uint32_t fromID = {};
    uint8_t source = {};
    uint8_t dest = {};
};

struct PKT_SwapItemReq : DefaultPacket {
    uint32_t fromID = {};
    uint8_t source = {};
    uint8_t dest = {};
};

struct PKT_SynchVersionC2S : DefaultPacket {
    uint32_t fromID = {};
    float mTime_LastClient = {};
    uint32_t mClientNetID = {};
    std::string mVersionString = {};
};

struct PKT_SynchVersionS2C : DefaultPacket {
    uint32_t fromID = {};
    bool mIsVersionOk = {};
    int mMapToLoad = {};
    std::array<PlayerLiteInfo, 12> playerInfo = {};
    std::string mVersionString = {};
    std::string mMapMode = {};
};

struct PKT_WaypointList : DefaultPacket, WithSyncID {
    uint32_t fromID = {};
    uint32_t syncID = {};
    std::vector<r3dPoint2D> list = {};
};

struct PKT_World_LockCamera_Server : DefaultPacket {
    uint32_t fromID = {};
    bool lockCamera = {};
    int32_t clientID = {};
};

struct PKT_World_SendCamera_Server : DefaultPacket {
    uint32_t fromID = {};
    r3dPoint3D cameraPos = {};
    r3dPoint3D cameraDir = {};
    int32_t clientID = {};
    int8_t syncID = {};
};

struct PKT_World_SendCamera_Server_Acknologment : DefaultPacket {
    uint32_t fromID = {};
    int8_t syncID = {};
};

using PKT_C2S = std::variant<EGP_RequestJoinTeam,
                             EGP_Chat,
                             PKT_BuyItemReq,
                             PKT_C2S_CharSelected,
                             PKT_C2S_ClientReady,
                             PKT_C2S_MapPing,
                             PKT_C2S_Ping_Load_Info,
                             PKT_C2S_PlayEmote,
                             PKT_C2S_QueryStatusReq,
                             PKT_C2S_Reconnect,
                             PKT_NPC_IssueOrderReq,
                             PKT_NPC_UpgradeSpellReq,
                             PKT_RemoveItemReq,
                             PKT_SwapItemReq,
                             PKT_SynchVersionC2S,
                             PKT_World_LockCamera_Server,
                             PKT_World_SendCamera_Server>;

using PKT_S2C = std::variant<EGP_RequestRename,
                             EGP_RequestReskin,
                             EGP_TeamRosterUpdate,
                             EGP_Chat,
                             PKT_Basic_Attack,
                             PKT_Basic_Attack_Pos,
                             PKT_BuyItemAns,
                             PKT_NPC_Die,
                             PKT_NPC_LevelUp,
                             PKT_NPC_UpgradeSpellAns,
                             PKT_OnEnterVisiblityClient,
                             PKT_RemoveItemAns,
                             PKT_S2C_ChangeCharacterData,
                             PKT_S2C_CreateHero,
                             PKT_S2C_CreateTurret,
                             PKT_S2C_FaceDirection,
                             PKT_S2C_EndSpawn,
                             PKT_S2C_MapPing,
                             PKT_S2C_Ping_Load_Info,
                             PKT_S2C_PlayAnimation,
                             PKT_S2C_PlayEmote,
                             PKT_S2C_QueryStatusAns,
                             PKT_S2C_Reconnect,
                             PKT_S2C_StartGame,
                             PKT_S2C_StartSpawn,
                             PKT_S2C_ToggleFoW,
                             PKT_SpawnMinionS2C,
                             PKT_SynchVersionS2C,
                             PKT_SwapItemAns,
                             PKT_WaypointList,
                             PKT_World_SendCamera_Server_Acknologment>;

template <typename T>
inline constexpr std::string_view type_name() {
    std::string_view name, prefix, suffix;
#ifdef __clang__
    name = __PRETTY_FUNCTION__;
    prefix = "std::string_view type_name() [T = ";
    suffix = "]";
#elif defined(__GNUC__)
    name = __PRETTY_FUNCTION__;
    prefix = "constexpr std::string_view type_name() [with T = ";
    suffix = "; std::string_view = std::basic_string_view<char>]";
#elif defined(_MSC_VER)
    name = __FUNCSIG__;
    prefix = "class std::basic_string_view<char,struct std::char_traits<char> > __cdecl type_name<struct ";
    suffix = ">(void)";
#endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());
    return name;
}
