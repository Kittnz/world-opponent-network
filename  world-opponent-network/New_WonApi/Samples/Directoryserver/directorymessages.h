#include <msg/BadMsgException.h>
#include <msg/TMessage.h>
#include <msg/MServiceTypes.h>
#include <msg/SServiceTypes.h>
#include <msg/TServiceTypes.h>
#include <msg/ServerStatus.h>
#include <msg/Comm/MMsgTypesComm.h>
#include <msg/dir/DirACLs.h> //all dirmsg headers \m
#include <msg/dir/DirEntity.h>
#include <msg/dir/DirG2Flags.h>
#include <msg/dir/DirServerEntry.h>
#include <msg/dir/DirServerSKMasks.h>
#include <msg/dir/SMsgDirG2AddDirectory.h>
#include <msg/dir/SMsgDirG2AddService.h>
#include <msg/dir/SMsgDirG2ClearDataObjects.h>
#include <msg/dir/SMsgDirG2DumpTree.h>
#include <msg/dir/SMsgDirG2EntityBase.h>
#include <msg/dir\SMsgDirG2EntityListBase.h>
#include <msg/dir/SMsgDirG2ExplicitSetDOs.h>
#include <msg/dir/SMsgDirG2FindDirectory.h>
#include <msg/dir/SMsgDirG2FindService.h>
#include <msg/dir/SMsgDirG2GetDirContents.h>
#include <msg/dir/SMsgDirG2GetEntity.h>
#include <msg/dir/SMsgDirG2GetNumEntities.h>
#include <msg/dir/SMsgDirG2KeyedBase.h>
#include <msg/dir/SMsgDirG2LoadFromSrc.h>
#include <msg/dir/SMsgDirG2ModifyDataObjects.h>
#include <msg/dir/SMsgDirG2ModifyDirectory.h>
#include <msg/dir/SMsgDirG2ModifyService.h>
#include <msg/dir/SMsgDirG2MultiEntityReply.h>
#include <msg/dir/SMsgDirG2NameEntity.h>
#include <msg/dir/SMsgDirG2PeerAttach.h>
#include <msg/dir/SMsgDirG2PeerConnect.h>
#include <msg/dir/SMsgDirG2PeerDataBase.h>
#include <msg/dir/SMsgDirG2PeerSynch.h>
#include <msg/dir/SMsgDirG2QueryBase.h>
#include <msg/dir/SMsgDirG2QueryExtendBase.h>
#include <msg/dir/SMsgDirG2QueryFindBase.h>
#include <msg/dir/SMsgDirG2QueryGetBase.h>
#include <msg/dir/SMsgDirG2RemoveEntity.h>
#include <msg/dir/SMsgDirG2RenewEntity.h>
#include <msg/dir/SMsgDirG2SetACLs.h>
#include <msg/dir/SMsgDirG2SetDataObjects.h>
#include <msg/dir/SMsgDirG2SingleEntityReply.h>
#include <msg/dir/SMsgDirG2StatusReply.h>
#include <msg/dir/SMsgDirG2SynchTree.h>
#include <msg/dir/SMsgDirG2UpdateBase.h>
#include <msg/dir/SMsgDirG2UpdateExtendBase.h>
#include <msg/dir/SMsgTypesDir.h>
#include <msg/dir/TMsgDirAddDirectory.h>
#include <msg/dir/TMsgDirAddService.h>
#include <msg/dir/TMsgDirChangeDirectory.h>
#include <msg/dir/TMsgDirChangeService.h>
#include <msg/dir/TMsgDirDirectoryBase.h>
#include <msg/dir/TMsgDirDumpTree.h>
#include <msg/dir/TMsgDirFindService.h>
#include <msg/dir/TMsgDirGetDirContents.h>
#include <msg/dir/TMsgDirGetNumDirEntries.h>
#include <msg/dir/TMsgDirLoadFromSource.h>
#include <msg/dir/TMsgDirPeerConnect.h>
#include <msg/dir/TMsgDirPeerDataBase.h>
#include <msg/dir/TMsgDirPeerSynch.h>
#include <msg/dir/TMsgDirRemoveDirectory.h>
#include <msg/dir/TMsgDirRemoveService.h>
#include <msg/dir/TMsgDirRenewDirectory.h>
#include <msg/dir/TMsgDirRenewService.h>
#include <msg/dir/TMsgDirServiceBase.h>
#include <msg/dir/TMsgDirStatusReply.h>
#include <msg/dir/TMsgDirSynchDirTree.h>
#include <msg/dir/TMsgTypesDir.h>
