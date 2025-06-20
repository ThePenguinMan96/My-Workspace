/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it
 * and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#ifndef _PLAYERBOT_WARLOCKTRIGGERS_H
#define _PLAYERBOT_WARLOCKTRIGGERS_H

#include "GenericTriggers.h"
#include "PlayerbotAI.h"

class PlayerbotAI;

class DemonArmorTrigger : public BuffTrigger
{
public:
    DemonArmorTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "demon armor") {}

    bool IsActive() override;
};

class FirestoneTrigger : public BuffTrigger
{
public:
    FirestoneTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "firestone") {}

    bool IsActive() override;
};

class SpellstoneTrigger : public BuffTrigger
{
public:
    SpellstoneTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "spellstone") {}

    bool IsActive() override;
};

class HasSoulstoneTrigger : public Trigger
{
public:
    HasSoulstoneTrigger(PlayerbotAI* botAI) : Trigger(botAI, "no soulstone") {}
    bool IsActive() override { return AI_VALUE2(uint32, "item count", "soulstone") == 0; }
};

class SoulstoneTrigger : public Trigger
{
public:
    SoulstoneTrigger(PlayerbotAI* botAI) : Trigger(botAI, "soulstone") {}
    bool IsActive() override
    {
        Player* master = botAI->GetMaster();
        if (!master)
            return false;

        static const std::vector<uint32> soulstoneAuraIds = {20707, 20762, 20763, 20764, 20765, 27239, 47883};
        for (uint32 spellId : soulstoneAuraIds)
            if (master->HasAura(spellId))
                return false;

        return AI_VALUE2(uint32, "item count", "soulstone") > 0;
    }
};

class CurseOfAgonyTrigger : public DebuffTrigger
{
public:
    CurseOfAgonyTrigger(PlayerbotAI* botAI) : DebuffTrigger(botAI, "curse of agony", 1, true, 20.0f) {}
};

class CorruptionTrigger : public DebuffTrigger
{
public:
    CorruptionTrigger(PlayerbotAI* botAI) : DebuffTrigger(botAI, "corruption", 1, true) {}
    bool IsActive() override
    {
        return DebuffTrigger::IsActive() && !botAI->HasAura("seed of corruption", GetTarget(), false, true);
    }
};

class CorruptionOnAttackerTrigger : public DebuffOnAttackerTrigger
{
public:
    CorruptionOnAttackerTrigger(PlayerbotAI* botAI) : DebuffOnAttackerTrigger(botAI, "corruption", true) {}
    bool IsActive() override
    {
        return DebuffOnAttackerTrigger::IsActive() && !botAI->HasAura("seed of corruption", GetTarget(), false, true);
    }
};

class CastCurseOfAgonyOnAttackerTrigger : public DebuffOnAttackerTrigger
{
public:
    CastCurseOfAgonyOnAttackerTrigger(PlayerbotAI* botAI)
        : DebuffOnAttackerTrigger(botAI, "curse of agony", true, 20.0f)
    {
    }
};

class SiphonLifeOnAttackerTrigger : public DebuffOnAttackerTrigger
{
public:
    SiphonLifeOnAttackerTrigger(PlayerbotAI* botAI) : DebuffOnAttackerTrigger(botAI, "siphon life") {}
};

DEBUFF_CHECKISOWNER_TRIGGER(ImmolateTrigger, "immolate");

class ImmolateOnAttackerTrigger : public DebuffOnAttackerTrigger
{
public:
    ImmolateOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "immolate") {}
    bool IsActive() override;
};

class ShadowTranceTrigger : public HasAuraTrigger
{
public:
    ShadowTranceTrigger(PlayerbotAI* botAI) : HasAuraTrigger(botAI, "shadow trance") {}
};

class BacklashTrigger : public HasAuraTrigger
{
public:
    BacklashTrigger(PlayerbotAI* botAI) : HasAuraTrigger(botAI, "backlash") {}
};

class BanishTrigger : public HasCcTargetTrigger
{
public:
    BanishTrigger(PlayerbotAI* botAI) : HasCcTargetTrigger(botAI, "banish") {}
};

class WarlockConjuredItemTrigger : public ItemCountTrigger
{
public:
    WarlockConjuredItemTrigger(PlayerbotAI* botAI, std::string const item) : ItemCountTrigger(botAI, item, 1) {}

    bool IsActive() override;
};

class HasSpellstoneTrigger : public WarlockConjuredItemTrigger
{
public:
    HasSpellstoneTrigger(PlayerbotAI* botAI) : WarlockConjuredItemTrigger(botAI, "spellstone") {}
};

class HasFirestoneTrigger : public WarlockConjuredItemTrigger
{
public:
    HasFirestoneTrigger(PlayerbotAI* botAI) : WarlockConjuredItemTrigger(botAI, "firestone") {}
};

class HasHealthstoneTrigger : public WarlockConjuredItemTrigger
{
public:
    HasHealthstoneTrigger(PlayerbotAI* botAI) : WarlockConjuredItemTrigger(botAI, "healthstone") {}
};

class FearTrigger : public HasCcTargetTrigger
{
public:
    FearTrigger(PlayerbotAI* botAI) : HasCcTargetTrigger(botAI, "fear") {}
};

class AmplifyCurseTrigger : public BuffTrigger
{
public:
    AmplifyCurseTrigger(PlayerbotAI* botAI) : BuffTrigger(botAI, "amplify curse") {}
};

class UnstableAfflictionTrigger : public DebuffTrigger
{
public:
    UnstableAfflictionTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "unstable affliction", 1, true) {}
    bool IsActive() override;
};

class UnstableAfflictionOnAttackerTrigger : public DebuffOnAttackerTrigger
{
public:
    UnstableAfflictionOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "unstable affliction", true) {}
    bool IsActive() override;
};

class HauntTrigger : public DebuffTrigger
{
public:
    HauntTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "haunt", 1, true, 0) {}
};

class DecimationTrigger : public HasAuraTrigger
{
public:
    DecimationTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "decimation") {}
    bool IsActive() override;
};

class LifeTapGlyphBuffTrigger : public BuffTrigger
{
public:
    LifeTapGlyphBuffTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "life tap") {}
    bool IsActive() override;
};

class MoltenCoreTrigger : public HasAuraTrigger
{
public:
    MoltenCoreTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "molten core") {}
};

class MetamorphosisTrigger : public BoostTrigger
{
public:
    MetamorphosisTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "metamorphosis") {}
};

class ImmolationAuraActiveTrigger : public HasAuraTrigger
{
public:
    ImmolationAuraActiveTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "immolation aura") {}
};

#endif
