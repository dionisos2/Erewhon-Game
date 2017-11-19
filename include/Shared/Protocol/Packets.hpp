// Copyright (C) 2017 Jérôme Leclercq
// This file is part of the "Erewhon Shared" project
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef EREWHON_SHARED_NETWORK_PACKETS_HPP
#define EREWHON_SHARED_NETWORK_PACKETS_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Core/String.hpp>
#include <Nazara/Math/Quaternion.hpp>
#include <Nazara/Math/Vector3.hpp>
#include <Nazara/Network/NetPacket.hpp>
#include <array>
#include <variant>
#include <vector>

namespace ewn
{
	enum class PacketType
	{
		ArenaState,
		ControlSpaceship,
		CreateSpaceship,
		DeleteSpaceship,
		JoinArena,
		Login,
		LoginFailure,
		LoginSuccess,
		PlayerMovement
	};

	template<PacketType PT> struct PacketTag
	{
		static constexpr PacketType Type = PT;
	};

	namespace Packets
	{
#define DeclarePacket(Type) struct Type : PacketTag<PacketType:: Type >

		DeclarePacket(ArenaState)
		{
			struct Spaceship
			{
				Nz::UInt32 id;
				Nz::Vector3f position;
				Nz::Quaternionf rotation;
			};

			std::vector<Spaceship> spaceships;
		};

		DeclarePacket(ControlSpaceship)
		{
			Nz::UInt32 id;
		};

		DeclarePacket(CreateSpaceship)
		{
			Nz::UInt32 id;
			Nz::Vector3f position;
			Nz::Quaternionf rotation;
			Nz::String name;
		};

		DeclarePacket(DeleteSpaceship)
		{
			Nz::UInt32 id;
		};

		DeclarePacket(JoinArena)
		{
		};

		DeclarePacket(Login)
		{
			std::string login;
			std::string passwordHash;
		};

		DeclarePacket(LoginFailure)
		{
			Nz::UInt8 reason;
		};

		DeclarePacket(LoginSuccess)
		{
		};

		DeclarePacket(PlayerMovement)
		{
			Nz::Vector3f direction;
			Nz::Vector3f rotation;
		};

#undef DeclarePacket

		void Serialize(Nz::NetPacket& packet, const ArenaState& data);
		void Serialize(Nz::NetPacket& packet, const ControlSpaceship& data);
		void Serialize(Nz::NetPacket& packet, const CreateSpaceship& data);
		void Serialize(Nz::NetPacket& packet, const DeleteSpaceship& data);
		void Serialize(Nz::NetPacket& packet, const JoinArena& data);
		void Serialize(Nz::NetPacket& packet, const Login& data);
		void Serialize(Nz::NetPacket& packet, const LoginFailure& data);
		void Serialize(Nz::NetPacket& packet, const LoginSuccess& data);
		void Serialize(Nz::NetPacket& packet, const PlayerMovement& data);
		void Unserialize(Nz::NetPacket& packet, ArenaState& data);
		void Unserialize(Nz::NetPacket& packet, ControlSpaceship& data);
		void Unserialize(Nz::NetPacket& packet, CreateSpaceship& data);
		void Unserialize(Nz::NetPacket& packet, DeleteSpaceship& data);
		void Unserialize(Nz::NetPacket& packet, JoinArena& data);
		void Unserialize(Nz::NetPacket& packet, Login& data);
		void Unserialize(Nz::NetPacket& packet, LoginFailure& data);
		void Unserialize(Nz::NetPacket& packet, LoginSuccess& data);
		void Unserialize(Nz::NetPacket& packet, PlayerMovement& data);
	}
}

#include <Shared/Protocol/Packets.inl>

#endif // EREWHON_SHARED_NETWORK_PACKETS_HPP
