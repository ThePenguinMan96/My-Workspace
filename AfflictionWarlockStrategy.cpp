/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it
 * and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "AfflictionWarlockStrategy.h"
#include "Playerbots.h"

// ===== Action Node Factory =====
class AfflictionWarlockStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    AfflictionWarlockStrategyActionNodeFactory()
    {
        creators["corruption"] = &corruption;
        creators["unstable affliction"] = &unstable_affliction;
        creators["haunt"] = &haunt;
        creators["curse of agony"] = &curse_of_agony;
        creators["drain soul"] = &drain_soul;
        creators["shadow bolt"] = &shadow_bolt;
        creators["seed of corruption"] = &seed_of_corruption;
        creators["seed of corruption on attacker"] = &seed_of_corruption_on_attacker;
        creators["corruption on attacker"] = &corruption_on_attacker;
        creators["unstable affliction on attacker"] = &unstable_affliction_on_attacker;
        creators["curse of agony on attacker"] = &curse_of_agony_on_attacker;
        creators["life tap"] = &life_tap;
    }
private:
    static ActionNode* corruption(PlayerbotAI*) { return new ActionNode("corruption", nullptr, nullptr, nullptr); }
    static ActionNode* unstable_affliction(PlayerbotAI*) { return new ActionNode("unstable affliction", nullptr, nullptr, nullptr); }
    static ActionNode* haunt(PlayerbotAI*) { return new ActionNode("haunt", nullptr, nullptr, nullptr); }
    static ActionNode* curse_of_agony(PlayerbotAI*) { return new ActionNode("curse of agony", nullptr, nullptr, nullptr); }
    static ActionNode* drain_soul(PlayerbotAI*) { return new ActionNode("drain soul", nullptr, nullptr, nullptr); }
    static ActionNode* shadow_bolt(PlayerbotAI*) { return new ActionNode("shadow bolt", nullptr, nullptr, nullptr); }
    static ActionNode* seed_of_corruption(PlayerbotAI*) { return new ActionNode("seed of corruption", nullptr, nullptr, nullptr); }
    static ActionNode* seed_of_corruption_on_attacker(PlayerbotAI*) { return new ActionNode("seed of corruption on attacker", nullptr, nullptr, nullptr); }
    static ActionNode* corruption_on_attacker(PlayerbotAI*) { return new ActionNode("corruption on attacker", nullptr, nullptr, nullptr); }
    static ActionNode* unstable_affliction_on_attacker(PlayerbotAI*) { return new ActionNode("unstable affliction on attacker", nullptr, nullptr, nullptr); }
    static ActionNode* curse_of_agony_on_attacker(PlayerbotAI*) { return new ActionNode("curse of agony on attacker", nullptr, nullptr, nullptr); }
    static ActionNode* life_tap(PlayerbotAI*) { return new ActionNode("life tap", nullptr, nullptr, nullptr); }
};

// ===== Single Target Strategy =====
AfflictionWarlockStrategy::AfflictionWarlockStrategy(PlayerbotAI* botAI) : GenericWarlockStrategy(botAI)
{
    actionNodeFactories.Add(new AfflictionWarlockStrategyActionNodeFactory());
}

NextAction** AfflictionWarlockStrategy::getDefaultActions()
{
    return NextAction::array( 0,
       new NextAction("haunt", 5.6f),
       new NextAction("unstable affliction", 5.5f),
       new NextAction("corruption", 5.4f),
       new NextAction("curse of agony", 5.3f),
       new NextAction("shadow bolt", 5.2f),
       new NextAction("shoot", 5.0f), nullptr);
}

// ===== Trigger Initialization ===
void AfflictionWarlockStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    GenericWarlockStrategy::InitTriggers(triggers);

    // Main DoT triggers for high uptime
    triggers.push_back(new TriggerNode("haunt", NextAction::array(0, new NextAction("haunt", 20.0f), nullptr)));
    triggers.push_back(new TriggerNode("unstable affliction", NextAction::array(0, new NextAction("unstable affliction", 19.5f), nullptr)));
    triggers.push_back(new TriggerNode("corruption", NextAction::array(0, new NextAction("corruption", 19.0f), nullptr)));
    triggers.push_back(new TriggerNode("curse of agony", NextAction::array(0, new NextAction("curse of agony", 18.5f), nullptr)));

     // Drain Soul as execute if target is low HP // Shadow Trance for free casts
    triggers.push_back(new TriggerNode("shadow trance", NextAction::array(0, new NextAction("shadow bolt", 18.0f), nullptr)));
    triggers.push_back(new TriggerNode("target critical health", NextAction::array(0, new NextAction("drain soul", 17.5f), nullptr)));
    

    // Cast during movement or to activate glyph buff
    triggers.push_back(new TriggerNode("high mana", NextAction::array(0, new NextAction("life tap", 5.1f), nullptr)));
    triggers.push_back(new TriggerNode("life tap glyph buff", NextAction::array(0, new NextAction("life tap", 28.0f), nullptr)));
}

// ===== AoE Strategy =====
AfflictionWarlockAoeStrategy::AfflictionWarlockAoeStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) {}

void AfflictionWarlockAoeStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("medium aoe", NextAction::array(0,
                       new NextAction("shadowflame", 22.5f),
                       new NextAction("seed of corruption", 22.0f),
                       new NextAction("seed of corruption on attacker", 21.5f),
                       new NextAction("rain of fire", 21.0f), nullptr)));
}
