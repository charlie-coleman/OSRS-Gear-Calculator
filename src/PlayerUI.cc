#include "PlayerUI.h"

#include "enums.h"
#include <pangomm.h>

#include <iostream>

PlayerUI::PlayerUI(std::string i_title, Database *i_db, Setup **i_setups, int i_setupCount)
  : m_playerTitle{i_title},
    m_monsterTitle{"Monster"},
    m_levelHeader{"Level"},
    m_potionHeader{"Potion"},
    m_prayerHeader{"Prayer"},
    m_player(99, 99, 99, 99, 99, 99, 99, 99,
             POTIONS_E::NONE,       POTIONS_E::NONE,         POTIONS_E::NONE,        POTIONS_E::NONE,       MAGIC_POTIONS_E::NONE,
             ATTACK_PRAYER_E::NONE, STRENGTH_PRAYER_E::NONE, DEFENCE_PRAYER_E::NONE, RANGED_PRAYER_E::NONE, MAGIC_PRAYER_E::NONE),
    m_db(i_db),
    m_setups(i_setups),
    m_setupCount(i_setupCount)
{
  InitializeEntries();
  InitializeExtras();

  m_playerGrid.attach(m_levelHeader, 1, 0);
  m_playerGrid.attach(m_potionHeader, 2, 0);
  m_playerGrid.attach(m_prayerHeader, 3, 0);

  set_orientation(Gtk::ORIENTATION_VERTICAL);

  Pango::AttrList attrList;
  Pango::AttrInt attr = Pango::Attribute::create_attr_size(20 * 1024);
  attrList.insert(attr);

  m_playerTitle.set_attributes(attrList);
  m_playerTitle.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);

  m_monsterTitle.set_attributes(attrList);
  m_monsterTitle.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);

  m_playerGrid.set_property("margin_bottom", 15);

  add(m_playerTitle);
  add(m_playerGrid);

  add(m_monsterTitle);
  add(m_monsterGrid);
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::InitializeEntries()
{
  m_attackEntry = new LevelEntry(&m_playerGrid, 1, "Attack: ", POTIONS_E::Names, ATTACK_PRAYER_E::Names);
  m_attackEntry->signal_level_changed().connect(sigc::mem_fun(*this, &PlayerUI::on_attack_changed));
  m_attackEntry->signal_potion_changed().connect(sigc::mem_fun(*this, &PlayerUI::attack_potion_changed));
  m_attackEntry->signal_prayer_changed().connect(sigc::mem_fun(*this, &PlayerUI::attack_prayer_changed));

  m_strengthEntry = new LevelEntry(&m_playerGrid, 2, "Strength: ", POTIONS_E::Names, STRENGTH_PRAYER_E::Names);
  m_strengthEntry->signal_level_changed().connect(sigc::mem_fun(*this, &PlayerUI::on_strength_changed));
  m_strengthEntry->signal_potion_changed().connect(sigc::mem_fun(*this, &PlayerUI::strength_potion_changed));
  m_strengthEntry->signal_prayer_changed().connect(sigc::mem_fun(*this, &PlayerUI::strength_prayer_changed));

  m_defenceEntry = new LevelEntry(&m_playerGrid, 3, "Defence: ", POTIONS_E::Names, DEFENCE_PRAYER_E::Names);
  m_defenceEntry->signal_level_changed().connect(sigc::mem_fun(*this, &PlayerUI::on_defence_changed));
  m_defenceEntry->signal_potion_changed().connect(sigc::mem_fun(*this, &PlayerUI::defence_potion_changed));
  m_defenceEntry->signal_prayer_changed().connect(sigc::mem_fun(*this, &PlayerUI::defence_prayer_changed));

  m_rangedEntry = new LevelEntry(&m_playerGrid, 4, "Ranged: ", POTIONS_E::Names, RANGED_PRAYER_E::Names);
  m_rangedEntry->signal_level_changed().connect(sigc::mem_fun(*this, &PlayerUI::on_ranged_changed));
  m_rangedEntry->signal_potion_changed().connect(sigc::mem_fun(*this, &PlayerUI::ranged_potion_changed));
  m_rangedEntry->signal_prayer_changed().connect(sigc::mem_fun(*this, &PlayerUI::ranged_prayer_changed));

  m_magicEntry = new LevelEntry(&m_playerGrid, 5, "Magic: ", MAGIC_POTIONS_E::Names, MAGIC_PRAYER_E::Names);
  m_magicEntry->signal_level_changed().connect(sigc::mem_fun(*this, &PlayerUI::on_magic_changed));
  m_magicEntry->signal_potion_changed().connect(sigc::mem_fun(*this, &PlayerUI::magic_potion_changed));
  m_magicEntry->signal_prayer_changed().connect(sigc::mem_fun(*this, &PlayerUI::magic_prayer_changed));

  m_prayerEntry = new LevelEntry(&m_playerGrid, 6, "Prayer: ", {}, {});
  m_prayerEntry->signal_level_changed().connect(sigc::mem_fun(*this, &PlayerUI::on_prayer_changed));

  m_hitpointsEntry = new LevelEntry(&m_playerGrid, 7, "Hitpoints: ", {}, {});
  m_hitpointsEntry->signal_level_changed().connect(sigc::mem_fun(*this, &PlayerUI::on_hitpoints_changed));
  
  m_currentHitpointsEntry = new LevelEntry(&m_playerGrid, 8, "Current Hitpoints: ", {}, {});
  m_currentHitpointsEntry->signal_level_changed().connect(sigc::mem_fun(*this, &PlayerUI::on_current_hp_changed));
}

void PlayerUI::InitializeExtras()
{
  m_monsterCombo = new SearchableComboBox<Monster>(&m_monsterGrid, 0, "", m_db->Monsters());
  m_monsterCombo->signal_selected_change().connect(sigc::mem_fun(*this, &PlayerUI::on_monster_changed));
}

/**
 * 
 * SIGNAL HANDLERS
 * 
 */
void PlayerUI::on_attack_changed(int i_level)
{
  m_player.SetAttack(i_level);
  UpdateSetupPlayer();
}
void PlayerUI::on_strength_changed(int i_level)
{
  m_player.SetStrength(i_level);
  UpdateSetupPlayer();
}
void PlayerUI::on_defence_changed(int i_level)
{
  m_player.SetDefence(i_level);
  UpdateSetupPlayer();
}
void PlayerUI::on_ranged_changed(int i_level)
{
  m_player.SetRanged(i_level);
  UpdateSetupPlayer();
}
void PlayerUI::on_magic_changed(int i_level)
{
  m_player.SetMagic(i_level);
  UpdateSetupPlayer();
}
void PlayerUI::on_prayer_changed(int i_level)
{
  m_player.SetPrayer(i_level);
  UpdateSetupPlayer();
}
void PlayerUI::on_hitpoints_changed(int i_level)
{
  m_player.SetHitpoints(i_level);
  UpdateSetupPlayer();
}
void PlayerUI::on_current_hp_changed(int i_level)
{
  m_player.SetCurrentHitpoints(i_level);
  UpdateSetupPlayer();
}
void PlayerUI::attack_potion_changed(int i_potion)
{
  m_player.SetAttackPotion((POTIONS_E::Type)i_potion);
  UpdateSetupPlayer();
}
void PlayerUI::strength_potion_changed(int i_potion)
{
  m_player.SetStrengthPotion((POTIONS_E::Type)i_potion);
  UpdateSetupPlayer();
}
void PlayerUI::defence_potion_changed(int i_potion)
{
  m_player.SetDefencePotion((POTIONS_E::Type)i_potion);
  UpdateSetupPlayer();
}
void PlayerUI::ranged_potion_changed(int i_potion)
{
  m_player.SetRangedPotion((POTIONS_E::Type)i_potion);
  UpdateSetupPlayer();
}
void PlayerUI::magic_potion_changed(int i_potion)
{
  m_player.SetMagicPotion((MAGIC_POTIONS_E::Type)i_potion);
  UpdateSetupPlayer();
}
void PlayerUI::attack_prayer_changed(int i_prayer)
{
  m_player.SetAttackPrayer((ATTACK_PRAYER_E::Type)i_prayer);
  UpdateSetupPlayer();
}
void PlayerUI::strength_prayer_changed(int i_prayer)
{
  m_player.SetStrengthPrayer((STRENGTH_PRAYER_E::Type)i_prayer);
  UpdateSetupPlayer();
}
void PlayerUI::defence_prayer_changed(int i_prayer)
{
  m_player.SetDefencePrayer((DEFENCE_PRAYER_E::Type)i_prayer);
  UpdateSetupPlayer();
}
void PlayerUI::ranged_prayer_changed(int i_prayer)
{
  m_player.SetRangedPrayer((RANGED_PRAYER_E::Type)i_prayer);
  UpdateSetupPlayer();
}
void PlayerUI::magic_prayer_changed(int i_prayer)
{
  m_player.SetMagicPrayer((MAGIC_PRAYER_E::Type)i_prayer);
  UpdateSetupPlayer();
}

void PlayerUI::on_monster_changed()
{
  for (int i = 0; i < m_setupCount; ++i)
  {
    m_setups[i]->SetMonster(m_monsterCombo->Selected());
  }

  m_signal_all_setups_changed.emit();
}

void PlayerUI::UpdateSetupPlayer()
{
  for (int i = 0; i < m_setupCount; ++i)
  {
    m_setups[i]->SetPlayer(m_player);
  }

  m_signal_all_setups_changed.emit();
}

sigc::signal<void> PlayerUI::signal_all_setups_changed()
{
  return m_signal_all_setups_changed;
}

Player PlayerUI::GetPlayer() const
{
  return m_player;
}

Monster PlayerUI::GetMonster() const
{
  return m_monsterCombo->Selected();
}