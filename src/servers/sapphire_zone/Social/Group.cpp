#include <cassert>
#include <boost/shared_ptr.hpp>
#include <Logging/Logger.h>

#include <sapphire_zone/Session.h>
#include <Network/PacketDef/Ipcs.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <sapphire_zone/Actor/Actor.h>
#include <sapphire_zone/Actor/Player.h>
#include <sapphire_zone/ServerZone.h>
#include <sapphire_zone/Zone/Zone.h>
#include <Network/GamePacketNew.h>

#include "Group.h"
#include "Framework.h"
#include "Forwards.h"

#include <set>

extern Core::Framework g_fw;

using namespace Core::Social;
using namespace Core::Network;


int32_t Group::findNextAvailableIndex() const
{
   // todo: perhaps throw an exception instead of returning -1 if not available?
   auto const it = std::find( std::begin( m_members ), std::end( m_members ), 0 );

   if( it == m_members.end() )
   {
      return -1;
   }

   return std::distance( m_members.begin(), it );
}

// todo: invite map in g_serverZone.getGroupMgr(GroupType) and look up

uint32_t Group::addMember( uint64_t contentId )
{
   assert( contentId != 0 );

   uint32_t logMessage = 0;

   m_members.push_back( contentId );

   return logMessage;
}

bool Group::hasMember( uint64_t contentId ) const
{
   return std::find( m_members.begin(), m_members.end(), contentId ) != m_members.end();
}

Core::Network::Packets::GamePacketPtr Group::processInvite( uint64_t recipientId, uint64_t senderId )
{
   constexpr uint32_t logMessages[] = {
      0, // 
      1
   };
   assert( senderId != 0 );

   using namespace Core::Network::Packets;

   uint64_t recipientContentId = 0;

   auto packet = GamePacketNew< Server::FFXIVIpcSocialRequestResponse, ServerZoneIpcType >( recipientId, senderId );
   packet.data().contentId = recipientContentId;
   packet.data().category = Common::SocialCategory::Friends;
   packet.data().response = Common::SocialRequestResponse::Accept;
   //packet.data().

   if ( m_members.size() < m_maxCapacity )
   {
      // todo: broadcast join message

      //m_groupInvites.erase( recipientId );

      m_members.push_back( recipientId );
   }
   else
   {
   }

   return packet;
}

Core::Network::Packets::GamePacketPtr Group::addMember2( Core::Entity::PlayerPtr pSender, Core::Entity::PlayerPtr pRecipient, uint64_t senderId, uint64_t recipientId )
{
   constexpr uint32_t logMessages[] = {
      0, // 
      1
   };
   assert( pSender != nullptr || senderId != 0 );

   using namespace Core::Network::Packets;

   uint64_t recipientContentId = 0;

   if( pSender )
   {
      senderId = pSender->getId();
   }

   if( pRecipient )
   {
      recipientId = pRecipient->getId();
      recipientContentId = pRecipient->getContentId();
   }

   auto packet = GamePacketNew< Server::FFXIVIpcSocialRequestResponse, ServerZoneIpcType >( recipientId, senderId );
   packet.data().contentId = recipientContentId;
   packet.data().category = Common::SocialCategory::Friends;
   /*
   if( m_members.size() < m_maxCapacity )
   {
      // todo: broadcast join message

      m_invites.erase( m_invites.find( recipientId ), m_invites.end() );
      GroupMember member;
      //member.inviterId = senderId;
      member.role = 0;
      //member.contentId = recipientId;
      //member.name = pSender->getName();
      m_members.emplace( recipientId, member );
   }
   else
   {
   }
   */
   return packet;
}

Packets::GamePacketPtr Group::inviteMember2( Core::Entity::PlayerPtr pSender, Core::Entity::PlayerPtr pRecipient, uint64_t senderId, uint64_t recipientId )
{
   assert( pSender != nullptr || senderId != 0 );


   auto packet = Packets::GamePacketNew< Packets::Server::FFXIVIpcSocialRequestResponse, Packets::ServerZoneIpcType >( recipientId, senderId );
   packet.data().contentId = recipientId;
   packet.data().category = Common::SocialCategory::Friends;
/*
   if( m_invites.size() < m_maxCapacity )
   {
      GroupMember member;
      //member.inviterId = senderId;
      member.role = 0;
      //member.contentId = recipientId;
      //member.name = pSender->getName();

      m_invites.emplace( recipientId, member );
   }
   */
   return packet;
}

// todo: fix
Core::Network::Packets::GamePacketPtr Group::removeMember2( Core::Entity::PlayerPtr pSender, Core::Entity::PlayerPtr pRecipient, uint64_t senderId, uint64_t recipientId )
{
   assert( pSender != nullptr || senderId != 0 );

   auto packet = Packets::GamePacketNew< Packets::Server::FFXIVIpcSocialRequestResponse, Packets::ServerZoneIpcType >( recipientId, senderId );
   packet.data().contentId = recipientId;
   packet.data().category = Common::SocialCategory::Friends;

   return packet;
}

void Group::sendPacketToMembers( Core::Network::Packets::GamePacketPtr pPacket, bool invitesToo )
{
   assert( pPacket );
   for( const auto& member : m_members )
   {
      auto pSession = g_fw.get< ServerZone >()->getSession( member );
      if( pSession )
      {
         pSession->getPlayer()->queuePacket( pPacket );
      }
   }
}



std::vector< uint64_t >& Group::getMembers()
{
   return m_members;
}


uint32_t Group::getCapacity() const
{
   return m_maxCapacity;
}

uint32_t Group::getTotalSize() const
{
   return m_members.size();
}

bool Group::isParty() const
{
   return m_type == GroupType::Party;
}

bool Group::isFriendList() const
{
   return m_type == GroupType::FriendList;
}

bool Group::isFreeCompany() const
{
   return m_type == GroupType::FreeCompany;
}

bool Group::isLinkshell() const
{
   return m_type == GroupType::Linkshell;
}

bool Group::isFreeCompanyPetition() const
{
   return m_type == GroupType::FreeCompanyPetition;
}

bool Group::isBlacklist() const
{
   return m_type == GroupType::Blacklist;
}

bool Group::isContentGroup() const
{
   return m_type == GroupType::ContentGroup;
}