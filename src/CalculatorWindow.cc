#include "CalculatorWindow.h"

CalculatorWindow::CalculatorWindow()
{
  set_title("Old School Runescape DPS Calculator");
  
  set_default_size(600, 600);
  set_border_width(10);

  m_db.ReadFilesToJson();
  m_db.ConvertJsonToDatabases();

  InitializeLabels();
  InitializeComboBoxes();

  m_container.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
  m_playerBox.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
  m_gearBox.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);

  m_playerBox.add(m_attackLabel);
  m_playerBox.add(m_attackEntry);
  m_playerBox.add(m_strengthLabel);
  m_playerBox.add(m_strengthEntry);
  m_playerBox.add(m_defenceLabel);
  m_playerBox.add(m_defenceEntry);
  m_playerBox.add(m_rangedLabel);
  m_playerBox.add(m_rangedEntry);
  m_playerBox.add(m_magicLabel);
  m_playerBox.add(m_magicEntry);
  m_playerBox.add(m_prayerLabel);
  m_playerBox.add(m_prayerEntry);
  m_playerBox.add(m_hitpointsLabel);
  m_playerBox.add(m_hitpointsEntry);

  m_container.add(m_playerBox);
  m_container.add(m_gearBox);
  
  add(m_container);

  show_all_children();
}

CalculatorWindow::~CalculatorWindow()
{
}

void CalculatorWindow::InitializeLabels()
{
  m_attackLabel.set_text("Attack Level: ");
  m_strengthLabel.set_text("Strength Level: ");
  m_defenceLabel.set_text("Defence Level: ");
  m_rangedLabel.set_text("Ranged Level: ");
  m_magicLabel.set_text("Magic Level: ");
  m_prayerLabel.set_text("Prayer Level: ");
  m_hitpointsLabel.set_text("Hitpoints Level: ");
}

void CalculatorWindow::InitializeComboBoxes()
{
  m_ammoCombo   = new SearchableComboBox<Equipment>(m_db.Ammunition());
  m_bodyCombo   = new SearchableComboBox<Equipment>(m_db.Body());
  m_capeCombo   = new SearchableComboBox<Equipment>(m_db.Cape());
  m_feetCombo   = new SearchableComboBox<Equipment>(m_db.Feet());
  m_handCombo   = new SearchableComboBox<Equipment>(m_db.Hand());
  m_headCombo   = new SearchableComboBox<Equipment>(m_db.Head());
  m_legsCombo   = new SearchableComboBox<Equipment>(m_db.Legs());
  m_neckCombo   = new SearchableComboBox<Equipment>(m_db.Neck());
  m_ringCombo   = new SearchableComboBox<Equipment>(m_db.Ring());
  m_shieldCombo = new SearchableComboBox<Equipment>(m_db.Shield());

  m_weaponCombo = new SearchableComboBox<Weapon>(m_db.Weapons());

  m_monsterCombo = new SearchableComboBox<Monster>(m_db.Monsters());

  m_gearBox.add(*m_ammoCombo);
  m_gearBox.add(*m_bodyCombo);
  m_gearBox.add(*m_capeCombo);   
  m_gearBox.add(*m_feetCombo);
  m_gearBox.add(*m_handCombo);
  m_gearBox.add(*m_headCombo);
  m_gearBox.add(*m_legsCombo);
  m_gearBox.add(*m_neckCombo);
  m_gearBox.add(*m_ringCombo);
  m_gearBox.add(*m_shieldCombo);

  m_gearBox.add(*m_weaponCombo);

  m_gearBox.add(*m_monsterCombo);
}

void CalculatorWindow::InitializeSetup()
{
  Player player(99, 99, 99, 99, 99, 99, 99, 
                POTIONS_E::SUPER_POTION, POTIONS_E::SUPER_POTION, POTIONS_E::SUPER_POTION, POTIONS_E::REGULAR_POTION, MAGIC_POTIONS_E::NONE,
                ATTACK_PRAYER_E::PIETY, STRENGTH_PRAYER_E::PIETY, DEFENCE_PRAYER_E::PIETY, RANGED_PRAYER_E::RIGOUR, MAGIC_PRAYER_E::AUGURY);

  Setup t(player, m_monsterCombo->Selected(), m_ammoCombo->Selected(), m_bodyCombo->Selected(),   m_capeCombo->Selected(),
                  m_feetCombo->Selected(),    m_handCombo->Selected(), m_headCombo->Selected(),   m_legsCombo->Selected(),
                  m_neckCombo->Selected(),    m_ringCombo->Selected(), m_shieldCombo->Selected(), m_weaponCombo->Selected());
}