#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"

class Player
{
  public:
    Player();
    Player(PLAYER_STATS_T i_stats);
    Player(PLAYER_STATS_T i_stats, POTIONS_T i_potions, PRAYER_T i_prayer);
    Player(int i_attack, int i_strength, int i_defense, int i_ranged, int i_magic, int i_prayer, int i_hitpoints);
    Player(int i_attack, int i_strength, int i_defense, int i_ranged, int i_magic, int i_prayer, int i_hitpoints,
           POTIONS_E::Type i_attackPotion, POTIONS_E::Type i_strengthPotion, POTIONS_E::Type i_defensePotion, POTIONS_E::Type i_rangedPotion, MAGIC_POTIONS_E::Type i_magicPotion,
           ATTACK_PRAYER_E::Type i_attackPrayer, STRENGTH_PRAYER_E::Type i_strengthPrayer, DEFENSE_PRAYER_E::Type i_defensePrayer, RANGED_PRAYER_E::Type i_rangedPrayer, MAGIC_PRAYER_E::Type i_magicPrayer);

    ~Player();

    void SetStats(PLAYER_STATS_T i_stats);
    void SetStats(int i_attack, int i_strength, int i_defense, int i_ranged, int i_magic, int i_prayer, int i_hitpoints);

    void SetPotions(POTIONS_T i_potions);
    void SetPotions(POTIONS_E::Type i_attackPotion, POTIONS_E::Type i_strengthPotion, POTIONS_E::Type i_defensePotion, POTIONS_E::Type i_rangedPotion, MAGIC_POTIONS_E::Type i_magicPotion);

    void SetPrayer(PRAYER_T i_prayer);
    void SetPrayer(ATTACK_PRAYER_E::Type i_attackPrayer, STRENGTH_PRAYER_E::Type i_strengthPrayer, DEFENSE_PRAYER_E::Type i_defensePrayer, RANGED_PRAYER_E::Type i_rangedPrayer, MAGIC_PRAYER_E::Type i_magicPrayer);

    void SetCurrentHitpoints(int i_hitpoints);

    const PLAYER_STATS_T& Stats() const;
    const PLAYER_STATS_T& EffectiveStats() const;

  private:
    PLAYER_STATS_T m_stats;
    PLAYER_STATS_T m_effectiveStats;
    POTIONS_T m_potions;
    PRAYER_T m_prayer;

    int m_currentHitpoints;

    void CalculateEffectiveStats();

    int CalculateEffectiveAttackLevel();
    int CalculateEffectiveStrengthLevel();
    int CalculateEffectiveDefenseLevel();
    int CalculateEffectiveRangedLevel();
    int CalculateEffectiveRangedStrength();
    int CalculateEffectiveMagicLevel();
};

#endif