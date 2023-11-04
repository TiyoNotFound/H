/*
    This is a SampVoice project file
    Developer: CyberMor <cyber.mor.2020@gmail.com>

    See more here https://github.com/CyberMor/sampvoice

    Copyright (c) Daniel (CyberMor) 2020 All rights reserved
*/

#pragma once

#include <system/types.hpp>
#include <other/version.hpp>

constexpr Version kCurrentVersion = MakeVersion(4, 1, 0);

constexpr size_t kMaxPlayers = 1024;
constexpr size_t kMaxStreams = 4096;
constexpr size_t kMaxEffects = 256;

constexpr size_t kFrequency = 48000; // Sound Frequency
constexpr size_t kInterval  = 100;   // Interval beetwen Voice Packets (or Voice Packet duration)

constexpr size_t kFrameSamples = kFrequency / 1000 * kInterval;
constexpr size_t kFrameBytes   = kFrameSamples * sizeof(float);
