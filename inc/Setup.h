#ifndef SETUP_H
#define SETUP_H

#include "Equipment.h"
#include "Weapon.h"
#include "Monster.h"
#include "Player.h"
 
class Setup
{
public:
  Setup();

  Setup(Player i_player,      Monster i_monster,
        Equipment i_ammoSlot, Equipment i_bodySlot,   Equipment i_capeSlot,   Equipment i_feetSlot,
        Equipment i_handSlot, Equipment i_headSlot,   Equipment i_legsSlot,   Equipment i_neckSlot,
        Equipment i_ringSlot, Equipment i_shieldSlot, Weapon i_oneHandedSlot);

  Setup(Player i_player,      Monster i_monster,
        Equipment i_ammoSlot, Equipment i_bodySlot,   Equipment i_capeSlot,   Equipment i_feetSlot,
        Equipment i_handSlot, Equipment i_headSlot,   Equipment i_legsSlot,   Equipment i_neckSlot,
        Equipment i_ringSlot, Weapon i_twoHandedSlot);

  ~Setup();

  void SetPlayer(Player i_player);
  void SetMonster(Monster i_monster);
  void SetAmmunition(Equipment i_ammo);
  void SetBody(Equipment i_body);
  void SetCape(Equipment i_cape);
  void SetFeet(Equipment i_feet);
  void SetHand(Equipment i_hand);
  void SetHead(Equipment i_head);
  void SetLegs(Equipment i_legs);
  void SetNeck(Equipment i_neck);
  void SetRing(Equipment i_ring);
  void SetShield(Equipment i_shield);
  void SetOneHanded(Weapon i_oneHanded);
  void SetTwoHanded(Weapon i_twoHanded);

  void SetCurrentHitpoints(int i_currentHitpoints);
  void SetOnTask(bool i_onSlayerTask);
  void SetStance(int i_stance);

  const Player& GetPlayer() const;
  const Monster& GetMonster() const;

  const Equipment& AmmoSlot() const;
  const Equipment& BodySlot() const;
  const Equipment& CapeSlot() const;
  const Equipment& FeetSlot() const;
  const Equipment& HandSlot() const;
  const Equipment& HeadSlot() const;
  const Equipment& LegsSlot() const;
  const Equipment& NeckSlot() const;
  const Equipment& RingSlot() const;
  const Equipment& ShieldSlot() const;

  const Weapon& OneHandedSlot() const;
  const Weapon& TwoHandedSlot() const;

  const int& CurrentHitpoints() const;
  const bool& IsOnTask() const;

  int GetMaxHit();

protected:
  int m_maxHit;
  float m_accuracy, m_dps;

  void CalculateMaxHit();

  int CalculateMeleeMaxHit();
  int CalculateRangedMaxHit();
  int CalculateMagicMaxHit();

  int CalculateEffectiveMeleeStrength();
  int CalculateEffectiveRangedStrength();

  Equipment m_ammoSlot,
            m_bodySlot,
            m_capeSlot,
            m_feetSlot,
            m_handSlot,
            m_headSlot,
            m_legsSlot,
            m_neckSlot,
            m_ringSlot,
            m_shieldSlot;

  Weapon m_oneHandedSlot,
         m_twoHandedSlot;

  int m_weaponStance;
  int m_effectiveMeleeStrength, m_effectiveRangedStrength;
  int m_baseMeleeDamage, m_baseRangedDamage;

  int m_currentHitpoints;
  bool m_onSlayerTask;

  bool m_isOneHanded;

  Monster m_monster;

  Player m_player;
};

#endif