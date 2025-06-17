/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license, you may redistribute it
 * and/or modify it under version 2 of the License, or (at your option), any later version.
 */

#include "DestructionWarlockStrategy.h"
#include "Playerbots.h"

// ===== Action Node Factory =====
class DestructionWarlockStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DestructionWarlockStrategyActionNodeFactory()
    {
        creators["curse of agony"] = &curse_of_agony;
        creators["immolate"] = &immolate;
        creators["conflagrate"] = &conflagrate;
        creators["chaos bolt"] = &chaos_bolt;
        creators["incinerate"] = &incinerate;
        creators["corruption"] = &corruption;
        creators["shadow bolt"] = &shadow_bolt;
        creators["shadowburn"] = &shadowburn;
        creators["life tap"] = &life_tap;
        creators["rain of fire"] = &rain_of_fire;
        creators["shadowfury"] = &shadowfury;
        creators["shadowflame"] = &shadowflame;
        creators["seed of corruption"] = &seed_of_corruption;
        creators["seed of corruption on attacker"] = &seed_of_corruption_on_attacker;
    }

private:
    static ActionNode* curse_of_agony(PlayerbotAI*) { return new ActionNode("curse of agony", nullptr, nullptr, nullptr); }
    static ActionNode* immolate(PlayerbotAI*) { return new ActionNode("immolate", nullptr, nullptr, nullptr); }
    static ActionNode* conflagrate(PlayerbotAI*) { return new ActionNode("conflagrate", nullptr, nullptr, nullptr); }
    static ActionNode* chaos_bolt(PlayerbotAI*) { return new ActionNode("chaos bolt", nullptr, nullptr, nullptr); }
    static ActionNode* incinerate(PlayerbotAI*) { return new ActionNode("incinerate", nullptr, nullptr, nullptr); }
    static ActionNode* corruption(PlayerbotAI*) { return new ActionNode("corruption", nullptr, nullptr, nullptr); }
    static ActionNode* shadow_bolt(PlayerbotAI*) { return new ActionNode("shadow bolt", nullptr, nullptr, nullptr); }
    static ActionNode* shadowburn(PlayerbotAI*) { return new ActionNode("shadowburn", nullptr, nullptr, nullptr); }
    static ActionNode* life_tap(PlayerbotAI*) { return new ActionNode("life tap", nullptr, nullptr, nullptr); }
    static ActionNode* rain_of_fire(PlayerbotAI*) { return new ActionNode("rain of fire", nullptr, nullptr, nullptr); }
    static ActionNode* shadowfury(PlayerbotAI*) { return new ActionNode("shadowfury", nullptr, nullptr, nullptr); }
    static ActionNode* shadowflame(PlayerbotAI*) { return new ActionNode("shadowflame", nullptr, nullptr, nullptr); }
    static ActionNode* seed_of_corruption(PlayerbotAI*) { return new ActionNode("seed of corruption", nullptr, nullptr, nullptr); }
    static ActionNode* seed_of_corruption_on_attacker(PlayerbotAI*) { return new ActionNode("seed of corruption on attacker", nullptr, nullptr, nullptr); }
};

// ===== Single Target Strategy =====
DestructionWarlockStrategy::DestructionWarlockStrategy(PlayerbotAI* botAI) : GenericWarlockStrategy(botAI)
{
    actionNodeFactories.Add(new DestructionWarlockStrategyActionNodeFactory());
}

NextAction** DestructionWarlockStrategy::getDefaultActions()
{
    return NextAction::array( 0,
       new NextAction("curse of agony", 5.8f),
       new NextAction("immolate", 5.7f),
       new NextAction("conflagrate", 5.6f),
       new NextAction("chaos bolt", 5.5f),
       new NextAction("incinerate", 5.4f),
       new NextAction("corruption", 5.3f),
       new NextAction("shadow bolt", 5.2f),
       new NextAction("shoot", 5.0f), nullptr);
}

// ===== Trigger Initialization ===
void DestructionWarlockStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    GenericWarlockStrategy::InitTriggers(triggers);

    // Main DoT triggers for high uptime + high priority cooldowns
    triggers.push_back(new TriggerNode("immolate", NextAction::array(0, new NextAction("immolate", 20.0f), nullptr)));
    triggers.push_back(new TriggerNode("conflagrate", NextAction::array(0, new NextAction("conflagrate", 19.5f), nullptr)));
    triggers.push_back(new TriggerNode("chaos bolt", NextAction::array(0, new NextAction("chaos bolt", 19.0f), nullptr)));
    triggers.push_back(new TriggerNode("curse of agony", NextAction::array(0, new NextAction("curse of agony", 18.5f), nullptr)));

    // Shadowburn as execute if target is low HP
    triggers.push_back(new TriggerNode("target critical health", NextAction::array(0, new NextAction("shadowburn", 18.0f), nullptr)));

    // Life Tap for efficiency/glyph
    triggers.push_back(new TriggerNode("high mana", NextAction::array(0, new NextAction("life tap", 5.1f), nullptr)));
    triggers.push_back(new TriggerNode("life tap glyph buff", NextAction::array(0, new NextAction("life tap", 28.0f), nullptr)));
}

// ===== AoE Strategy =====
DestructionWarlockAoeStrategy::DestructionWarlockAoeStrategy(PlayerbotAI* botAI) : CombatStrategy(botAI) {}

void DestructionWarlockAoeStrategy::InitTriggers(std::vector<TriggerNode*>& triggers)
{
    triggers.push_back(new TriggerNode("medium aoe", NextAction::array(0,
                       new NextAction("shadowfury", 23.0f),
                       new NextAction("shadowflame", 22.5f),
                       new NextAction("seed of corruption", 22.0f),
                       new NextAction("seed of corruption on attacker", 21.5f),
                       new NextAction("rain of fire", 21.0f), nullptr)));
}
