// Copyright (C) 2018 Jérôme Leclercq
// This file is part of the "Erewhon Server" project
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Server/ServerCommandStore.hpp>
#include <Server/ServerApplication.hpp>

namespace ewn
{
	ServerCommandStore::ServerCommandStore(ServerApplication* app)
	{
		using namespace std::placeholders;

#define IncomingCommand(Type) RegisterIncomingCommand<Packets::Type>(#Type, [app](std::size_t peerId, const Packets::Type& packet) \
{ \
	app->Handle##Type(peerId, packet); \
})
#define OutgoingCommand(Type, Flags, Channel) RegisterOutgoingCommand<Packets::Type>(#Type, Flags, Channel)

		// Incoming commands
		IncomingCommand(CreateSpaceship);
		IncomingCommand(DeleteSpaceship);
		IncomingCommand(JoinArena);
		IncomingCommand(LeaveArena);
		IncomingCommand(Login);
		IncomingCommand(LoginByToken);
		IncomingCommand(PlayerChat);
		IncomingCommand(PlayerMovement);
		IncomingCommand(PlayerShoot);
		IncomingCommand(QueryArenaList);
		IncomingCommand(QueryHullList);
		IncomingCommand(QueryModuleList);
		IncomingCommand(QuerySpaceshipInfo);
		IncomingCommand(QuerySpaceshipList);
		IncomingCommand(Register);
		IncomingCommand(TimeSyncRequest);
		IncomingCommand(UpdateSpaceship);

		// Outgoing commands
		OutgoingCommand(ArenaList,                 Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(ArenaPrefabs,              Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(ArenaParticleSystems,      Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(ArenaSounds,               Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(ArenaState,                0,                           0);
		OutgoingCommand(BotMessage,                Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(ChatMessage,               Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(ControlEntity,             Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(CreateEntity,              Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(CreateSpaceshipFailure,    Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(CreateSpaceshipSuccess,    Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(DeleteEntity,              Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(DeleteSpaceshipFailure,    Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(DeleteSpaceshipSuccess,    Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(HullList,                  Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(InstantiateParticleSystem, Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(IntegrityUpdate,           Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(LoginFailure,              Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(LoginSuccess,              Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(ModuleList,                Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(NetworkStrings,            Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(PlaySound,                 Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(RegisterFailure,           Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(RegisterSuccess,           Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(SpaceshipInfo,             Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(SpaceshipList,             Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(TimeSyncResponse,          0,                           0);
		OutgoingCommand(UpdateSpaceshipFailure,    Nz::ENetPacketFlag_Reliable, 0);
		OutgoingCommand(UpdateSpaceshipSuccess,    Nz::ENetPacketFlag_Reliable, 0);

#undef IncomingCommand
#undef OutgoingCommand
	}
}
