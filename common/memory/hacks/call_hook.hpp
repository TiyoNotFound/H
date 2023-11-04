/*
    This is a SampVoice project file
    Developer: CyberMor <cyber.mor.2020@gmail.com>

    See more here https://github.com/CyberMor/sampvoice

    Copyright (c) Daniel (CyberMor) 2020 All rights reserved
*/

#pragma once

#include <cassert>

#include <system/types.hpp>

#include "patch.hpp"

struct CallHook {

    CallHook() noexcept = default;
    ~CallHook() noexcept = default;
    CallHook(const CallHook&) = delete;
    CallHook(CallHook&&) noexcept = default;
    CallHook& operator=(const CallHook&) = delete;
    CallHook& operator=(CallHook&&) noexcept = default;

private:

#pragma pack(push, 1)

    struct CallInstruction {

        CallInstruction() = delete;
        ~CallInstruction() noexcept = default;
        CallInstruction(const CallInstruction&) noexcept = default;
        CallInstruction(CallInstruction&&) noexcept = default;
        CallInstruction& operator=(const CallInstruction&) noexcept = default;
        CallInstruction& operator=(CallInstruction&&) noexcept = default;

    public:

        CallInstruction(const sptrint_t offset) noexcept
            : _offset { offset }
        {}

    public:

        sptrint_t Offset() const noexcept
        {
            return _offset;
        }

    private:

          ubyte_t _opcode = 0xE8;
        sptrint_t _offset;

    };

#pragma pack(pop)

public:

    CallHook(const ptr_t inject, const cptr_t hook, const bool enabled = true) noexcept
    {
        assert(inject != nullptr);
        assert(hook   != nullptr);

        _target = reinterpret_cast<ptr_t>((reinterpret_cast<sptrint_t>(inject) +
            static_cast<sptrint_t>(sizeof(CallInstruction))) + static_cast<const CallInstruction*>(inject)->Offset());

        if (_target != nullptr && !_patch.Initialize(inject, &CallInstruction(reinterpret_cast<sptrint_t>(hook) -
            (reinterpret_cast<sptrint_t>(inject) + static_cast<sptrint_t>(sizeof(CallInstruction)))), enabled))
            _target = nullptr;
    }

public:

    bool Valid() const noexcept
    {
        return _target != nullptr && _patch.Valid();
    }

    bool Invalid() const noexcept
    {
        return _target == nullptr || _patch.Invalid();
    }

public:

    bool Initialize(const ptr_t inject, const cptr_t hook, const bool enabled = true) noexcept
    {
        assert(inject != nullptr);
        assert(hook   != nullptr);

        _target = reinterpret_cast<ptr_t>((reinterpret_cast<sptrint_t>(inject) +
            static_cast<sptrint_t>(sizeof(CallInstruction))) + static_cast<const CallInstruction*>(inject)->Offset());

        if (_target != nullptr && !_patch.Initialize(inject, &CallInstruction(reinterpret_cast<sptrint_t>(hook) -
            (reinterpret_cast<sptrint_t>(inject) + static_cast<sptrint_t>(sizeof(CallInstruction)))), enabled))
            _target = nullptr;

        return _target != nullptr && _patch.Valid();
    }

    void Deinitialize() noexcept
    {
        _patch.Deinitialize();

        _target = nullptr;
    }

public:

    bool Enable() noexcept
    {
        return _patch.Enable();
    }

    bool Disable() noexcept
    {
        return _patch.Disable();
    }

public:

    ptr_t Target() const noexcept
    {
        return _target;
    }

public:

    ptr_t Address() const noexcept
    {
        return _patch.Address();
    }

    static constexpr size_t Length() noexcept
    {
        return sizeof(CallInstruction);
    }

private:

    ptr_t _target = nullptr;

private:

    Patch<sizeof(CallInstruction)> _patch;

};
