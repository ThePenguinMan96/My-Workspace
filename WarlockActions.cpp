/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it
 * and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "WarlockActions.h"
#include "ServerFacade.h"
#include "Event.h"
#include "Playerbots.h"
#include "Player.h"
#include "ObjectGuid.h"
#include "PlayerbotAI.h"
#include <vector>
#include <string>
#include "Item.h"
#include "Unit.h"

bool CastDrainSoulAction::isUseful() { return AI_VALUE2(uint32, "item count", "soul shard") < 32; }

Value<Unit*>* CastBanishAction::GetTargetValue() { return context->GetValue<Unit*>("cc target", "banish"); }

bool CastBanishAction::Execute(Event event) { return botAI->CastSpell("banish", GetTarget()); }

Value<Unit*>* CastFearOnCcAction::GetTargetValue() { return context->GetValue<Unit*>("cc target", "fear"); }

bool CastFearOnCcAction::Execute(Event event) { return botAI->CastSpell("fear", GetTarget()); }

bool CastFearOnCcAction::isPossible() { return true; }

bool CastFearOnCcAction::isUseful() { return true; }

bool CastLifeTapAction::isUseful() { return AI_VALUE2(uint8, "health", "self target") > sPlayerbotAIConfig->lowHealth; }

bool CastShadowflameAction::isUseful()
{
    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target)
        return false;
    bool facingTarget = AI_VALUE2(bool, "facing", "current target");
    bool targetClose = bot->IsWithinCombatRange(target, 7.0f);  // 7yd cone
    return facingTarget && targetClose;
}

bool CastRainOfFireAction::isUseful()
{
    Unit* target = GetTarget();
    // If no target, it's not useful to cast anything
    if (!target)
        return false;

    // If you CAN cast Seed of Corruption, Rain of Fire is strictly worse.
    // This checks to see if the bot knows Seed of Corruption, and returns false if it does.

    if (bot->HasSpell(27243) || bot->HasSpell(47835) || bot->HasSpell(47836))
        return false;

    // Otherwise, Rain of Fire is useful
    return true;
}

bool UseSoulstoneAction::Execute(Event event)
{
    std::string name = event.getParam();
    if (name.empty())
        name = getName();  // "soulstone"

    std::vector<Item*> items = AI_VALUE2(std::vector<Item*>, "inventory items", name);
    if (items.empty())
        return false;

    Unit* master = botAI->GetMaster();

    bot->SetSelection(master->GetGUID());

    // Use the soulstone on the master by passing master as unitTarget
    return UseItem(items[0], ObjectGuid::Empty, nullptr, master);
}

bool CastImmolationAuraAction::isUseful()
{
    // If the "meta melee aoe" strategy is enabled in combat, return true immediately
    if (botAI->HasStrategy("meta melee aoe", BOT_STATE_COMBAT))
        return true;

    // Otherwise, check the following conditions
    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target)
        return false;

    if (!bot->HasAura(47241))  // 47241 is Metamorphosis spell ID (WotLK)
        return false;

    return bot->IsWithinCombatRange(target, 7.0f);  // 7 yards is the range for Immolation Aura
}

bool CastSoulshatterAction::isUseful()
{
    // If the "warlock tank" strategy is enabled, return false
    if (botAI->HasStrategy("warlock tank", BOT_STATE_COMBAT))
        return false;
    return true;
}


