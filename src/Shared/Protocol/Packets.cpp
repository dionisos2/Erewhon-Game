// Copyright (C) 2018 Jérôme Leclercq
// This file is part of the "Erewhon Shared" project
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Shared/Protocol/Packets.hpp>
#include <Nazara/Core/Algorithm.hpp>
#include <Nazara/Math/Vector3.hpp>
#include <Shared/Utils.hpp>

namespace ewn
{
	namespace Packets
	{
		void Serialize(PacketSerializer& serializer, ArenaList& data)
		{
			CompressedUnsigned<Nz::UInt32> arenaCount;
			if (serializer.IsWriting())
				arenaCount = Nz::UInt32(data.arenas.size());

			serializer &= arenaCount;
			if (!serializer.IsWriting())
				data.arenas.resize(arenaCount);

			for (auto& arenaData : data.arenas)
				serializer &= arenaData.arenaName;
		}

		void Serialize(PacketSerializer& serializer, ArenaPrefabs& data)
		{
			serializer &= data.startId;

			CompressedUnsigned<Nz::UInt32> prefabCount;
			if (serializer.IsWriting())
				prefabCount = Nz::UInt32(data.prefabs.size());

			serializer &= prefabCount;
			if (!serializer.IsWriting())
				data.prefabs.resize(prefabCount);

			for (auto& prefabs : data.prefabs)
			{
				CompressedUnsigned<Nz::UInt32> modelCount;
				CompressedUnsigned<Nz::UInt32> soundCount;
				CompressedUnsigned<Nz::UInt32> visualEffectCount;

				if (serializer.IsWriting())
				{
					modelCount = Nz::UInt32(prefabs.models.size());
					soundCount = Nz::UInt32(prefabs.sounds.size());
					visualEffectCount = Nz::UInt32(prefabs.visualEffects.size());
				}

				serializer &= modelCount;
				serializer &= soundCount;
				serializer &= visualEffectCount;

				if (!serializer.IsWriting())
				{
					prefabs.models.resize(modelCount);
					prefabs.sounds.resize(soundCount);
					prefabs.visualEffects.resize(visualEffectCount);
				}

				for (auto& model : prefabs.models)
				{
					serializer &= model.modelId;
					serializer &= model.rotation;
					serializer &= model.position;
					serializer &= model.scale;
				}

				for (auto& sound : prefabs.sounds)
				{
					serializer &= sound.soundId;
					serializer &= sound.position;
				}

				for (auto& effect : prefabs.visualEffects)
				{
					serializer &= effect.effectNameId;
					serializer &= effect.rotation;
					serializer &= effect.position;
					serializer &= effect.scale;
				}
			}
		}

		void Serialize(PacketSerializer& serializer, ArenaParticleSystems& data)
		{
			serializer &= data.startId;

			CompressedUnsigned<Nz::UInt32> particleSystemCount;
			if (serializer.IsWriting())
				particleSystemCount = Nz::UInt32(data.particleSystems.size());

			serializer &= particleSystemCount;
			if (!serializer.IsWriting())
				data.particleSystems.resize(particleSystemCount);

			for (auto& particleSystem : data.particleSystems)
			{
				CompressedUnsigned<Nz::UInt32> particleGroupCount;
				if (serializer.IsWriting())
					particleGroupCount = Nz::UInt32(particleSystem.particleGroups.size());

				serializer &= particleGroupCount;
				if (!serializer.IsWriting())
					particleSystem.particleGroups.resize(particleGroupCount);

				for (auto& particleGroup : particleSystem.particleGroups)
					serializer &= particleGroup.particleGroupNameId;
			}
		}

		void Serialize(PacketSerializer& serializer, ArenaSounds& data)
		{
			serializer &= data.startId;

			CompressedUnsigned<Nz::UInt32> soundCount;
			if (serializer.IsWriting())
				soundCount = Nz::UInt32(data.sounds.size());

			serializer &= soundCount;
			if (!serializer.IsWriting())
				data.sounds.resize(soundCount);

			for (auto& sound : data.sounds)
				serializer &= sound.filePath;
		}

		void Serialize(PacketSerializer& serializer, ArenaState& data)
		{
			serializer &= data.stateId;
			serializer &= data.serverTime;
			serializer &= data.lastProcessedInputTime;

			CompressedUnsigned<Nz::UInt32> entityCount;
			if (serializer.IsWriting())
				entityCount = Nz::UInt32(data.entities.size());

			serializer &= entityCount;
			if (!serializer.IsWriting())
				data.entities.resize(entityCount);

			for (auto& entity : data.entities)
			{
				serializer &= entity.id;
				serializer &= entity.position;
				serializer &= entity.rotation;
				serializer &= entity.angularVelocity;
				serializer &= entity.linearVelocity;
			}
		}

		void Serialize(PacketSerializer& serializer, BotMessage& data)
		{
			serializer.Serialize<Nz::UInt8>(data.messageType);
			serializer &= data.errorMessage;
		}

		void Serialize(PacketSerializer& serializer, ChatMessage& data)
		{
			serializer &= data.message;
		}

		void Serialize(PacketSerializer& serializer, ControlEntity& data)
		{
			serializer &= data.id;
		}

		void Serialize(PacketSerializer& serializer, CreateEntity& data)
		{
			serializer &= data.angularVelocity;
			serializer &= data.entityId;
			serializer &= data.linearVelocity;
			serializer &= data.position;
			serializer &= data.prefabId;
			serializer &= data.rotation;
			serializer &= data.visualName;
		}

		void Serialize(PacketSerializer& serializer, CreateSpaceship& data)
		{
			serializer &= data.hullId;
			serializer &= data.spaceshipName;
			serializer &= data.spaceshipCode;

			CompressedUnsigned<Nz::UInt32> moduleCount;
			if (serializer.IsWriting())
				moduleCount = Nz::UInt32(data.modules.size());

			serializer &= moduleCount;
			if (!serializer.IsWriting())
				data.modules.resize(moduleCount);

			for (auto& moduleInfo : data.modules)
			{
				serializer.Serialize<Nz::UInt8>(moduleInfo.type);
				serializer &= moduleInfo.moduleId;
			}
		}

		void Serialize(PacketSerializer& serializer, CreateSpaceshipFailure& data)
		{
			serializer.Serialize<Nz::UInt8>(data.reason);
		}

		void Serialize(PacketSerializer& serializer, CreateSpaceshipSuccess& data)
		{
		}

		void Serialize(PacketSerializer& serializer, DeleteEntity& data)
		{
			serializer &= data.id;
		}

		void Serialize(PacketSerializer& serializer, DeleteSpaceship& data)
		{
			serializer &= data.spaceshipName;
		}

		void Serialize(PacketSerializer& serializer, DeleteSpaceshipFailure& data)
		{
			serializer.Serialize<Nz::UInt8>(data.reason);
		}

		void Serialize(PacketSerializer& serializer, DeleteSpaceshipSuccess& data)
		{
		}

		void Serialize(PacketSerializer& serializer, HullList& data)
		{
			CompressedUnsigned<Nz::UInt32> hullCount;
			if (serializer.IsWriting())
				hullCount = Nz::UInt32(data.hulls.size());

			serializer &= hullCount;
			if (!serializer.IsWriting())
				data.hulls.resize(hullCount);

			for (auto& hullInfo : data.hulls)
			{
				serializer &= hullInfo.hullId;
				serializer &= hullInfo.hullModelPathId;
				serializer &= hullInfo.name;
				serializer &= hullInfo.description;

				CompressedUnsigned<Nz::UInt32> slotCount;
				if (serializer.IsWriting())
					slotCount = Nz::UInt32(hullInfo.slots.size());

				serializer &= slotCount;
				if (!serializer.IsWriting())
					hullInfo.slots.resize(slotCount);

				for (auto& slotInfo : hullInfo.slots)
					serializer.Serialize<Nz::UInt8>(slotInfo.type);
			}
		}

		void Serialize(PacketSerializer& serializer, InstantiateParticleSystem& data)
		{
			serializer &= data.particleSystemId;
			serializer &= data.rotation;
			serializer &= data.position;
			serializer &= data.scale;
		}

		void Serialize(PacketSerializer& serializer, IntegrityUpdate& data)
		{
			serializer &= data.integrityValue;
		}

		void Serialize(PacketSerializer & serializer, LeaveArena& data)
		{
		}

		void Serialize(PacketSerializer& serializer, JoinArena& data)
		{
			serializer &= data.arenaIndex;
		}

		void Serialize(PacketSerializer& serializer, Login& data)
		{
			serializer &= data.login;
			serializer &= data.passwordHash;

			serializer.Serialize<Nz::UInt8>(data.generateConnectionToken);
		}

		void Serialize(PacketSerializer& serializer, LoginByToken& data)
		{
			CompressedUnsigned<Nz::UInt32> tokenLength;
			if (serializer.IsWriting())
				tokenLength = Nz::UInt32(data.connectionToken.size());

			serializer &= tokenLength;
			if (!serializer.IsWriting())
				data.connectionToken.resize(tokenLength);

			for (auto& data : data.connectionToken)
				serializer &= data;

			serializer.Serialize<Nz::UInt8>(data.generateConnectionToken);
		}

		void Serialize(PacketSerializer& serializer, LoginFailure& data)
		{
			serializer.Serialize<Nz::UInt8>(data.reason);
		}

		void Serialize(PacketSerializer& serializer, LoginSuccess& data)
		{
			CompressedUnsigned<Nz::UInt32> tokenLength;
			if (serializer.IsWriting())
				tokenLength = Nz::UInt32(data.connectionToken.size());

			serializer &= tokenLength;
			if (!serializer.IsWriting())
				data.connectionToken.resize(tokenLength);

			for (auto& data : data.connectionToken)
				serializer &= data;
		}

		void Serialize(PacketSerializer& serializer, ModuleList& data)
		{
			// Modules
			CompressedUnsigned<Nz::UInt32> moduleCount;
			if (serializer.IsWriting())
				moduleCount = Nz::UInt32(data.modules.size());

			serializer &= moduleCount;
			if (!serializer.IsWriting())
				data.modules.resize(moduleCount);

			for (auto& moduleTypeInfo : data.modules)
			{
				serializer.Serialize<Nz::UInt8>(moduleTypeInfo.type);

				// Available modules
				CompressedUnsigned<Nz::UInt32> availableModuleCount;
				if (serializer.IsWriting())
					availableModuleCount = Nz::UInt32(moduleTypeInfo.availableModules.size());

				serializer &= availableModuleCount;
				if (!serializer.IsWriting())
					moduleTypeInfo.availableModules.resize(availableModuleCount);

				for (auto& moduleInfo : moduleTypeInfo.availableModules)
				{
					serializer &= moduleInfo.moduleId;
					serializer &= moduleInfo.moduleName;
				}
			}
		}

		void Serialize(PacketSerializer& serializer, NetworkStrings& data)
		{
			serializer &= data.startId;

			CompressedUnsigned<Nz::UInt32> stringCount;
			if (serializer.IsWriting())
				stringCount = Nz::UInt32(data.strings.size());

			serializer &= stringCount;
			if (!serializer.IsWriting())
				data.strings.resize(stringCount);

			for (auto& string : data.strings)
				serializer &= string;
		}

		void Serialize(PacketSerializer& serializer, PlayerChat& data)
		{
			serializer &= data.text;
		}

		void Serialize(PacketSerializer& serializer, PlayerMovement& data)
		{
			serializer &= data.inputTime;
			serializer &= data.direction;
			serializer &= data.rotation;
		}

		void Serialize(PacketSerializer& serializer, PlayerShoot& data)
		{
		}

		void Serialize(PacketSerializer& serializer, PlaySound& data)
		{
			serializer &= data.soundId;
			serializer &= data.position;
		}

		void Serialize(PacketSerializer& serializer, QueryArenaList& data)
		{
		}

		void Serialize(PacketSerializer& serializer, QueryHullList& data)
		{
		}

		void Serialize(PacketSerializer& serializer, QueryModuleList& data)
		{
		}

		void Serialize(PacketSerializer& serializer, QuerySpaceshipInfo& data)
		{
			serializer &= data.spaceshipName;
		}

		void Serialize(PacketSerializer& serializer, QuerySpaceshipList& data)
		{
		}

		void Serialize(PacketSerializer& serializer, Register& data)
		{
			serializer &= data.login;
			serializer &= data.email;
			serializer &= data.passwordHash;
		}

		void Serialize(PacketSerializer& serializer, RegisterFailure& data)
		{
			serializer.Serialize<Nz::UInt8>(data.reason);
		}

		void Serialize(PacketSerializer& serializer, RegisterSuccess& data)
		{
		}

		void Serialize(PacketSerializer& serializer, SpaceshipInfo& data)
		{
			serializer &= data.hullId;
			serializer &= data.hullModelPath;

			// Modules
			CompressedUnsigned<Nz::UInt32> moduleCount;
			if (serializer.IsWriting())
				moduleCount = Nz::UInt32(data.modules.size());

			serializer &= moduleCount;
			if (!serializer.IsWriting())
				data.modules.resize(moduleCount);

			for (auto& moduleInfo : data.modules)
			{
				serializer &= moduleInfo.currentModule;
				serializer.Serialize<Nz::UInt8>(moduleInfo.type);
			}
		}

		void Serialize(PacketSerializer& serializer, SpaceshipList& data)
		{
			CompressedUnsigned<Nz::UInt32> spaceshipCount;
			if (serializer.IsWriting())
				spaceshipCount = Nz::UInt32(data.spaceships.size());

			serializer &= spaceshipCount;
			if (!serializer.IsWriting())
				data.spaceships.resize(spaceshipCount);

			for (auto& spaceship : data.spaceships)
				serializer &= spaceship.name;

		}

		void Serialize(PacketSerializer& serializer, TimeSyncRequest& data)
		{
			serializer &= data.requestId;
		}

		void Serialize(PacketSerializer& serializer, TimeSyncResponse& data)
		{
			serializer &= data.requestId;
			serializer &= data.serverTime;
		}

		void Serialize(PacketSerializer& serializer, UpdateSpaceship& data)
		{
			serializer &= data.spaceshipName;
			serializer &= data.newSpaceshipName;
			serializer &= data.newSpaceshipCode;

			CompressedUnsigned<Nz::UInt32> modifiedModuleCount;
			if (serializer.IsWriting())
				modifiedModuleCount = Nz::UInt32(data.modifiedModules.size());

			serializer &= modifiedModuleCount;
			if (!serializer.IsWriting())
				data.modifiedModules.resize(modifiedModuleCount);

			for (auto& moduleInfo : data.modifiedModules)
			{
				serializer &= moduleInfo.moduleName;
				serializer &= moduleInfo.oldModuleName;
				serializer.Serialize<Nz::UInt8>(moduleInfo.type);
			}
		}

		void Serialize(PacketSerializer& serializer, UpdateSpaceshipFailure& data)
		{
			serializer.Serialize<Nz::UInt8>(data.reason);
		}

		void Serialize(PacketSerializer& serializer, UpdateSpaceshipSuccess& data)
		{
		}
	}
}
