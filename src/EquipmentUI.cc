#include "EquipmentUI.h"

EquipmentUI::EquipmentUI(Database *i_db)
{
  m_db = i_db;

  InitializeComboBoxes();
}

EquipmentUI::~EquipmentUI()
{
}

void EquipmentUI::InitializeComboBoxes()
{
  m_ammoCombo   = new SearchableComboBox<Equipment>((Gtk::Grid*)this, 0, "Ammunition: ", m_db->Ammunition(), DB_TYPE_E::AMMO);
  m_ammoCombo->signal_selected_change().connect(sigc::mem_fun(*this, &EquipmentUI::on_equipment_change));

  m_bodyCombo   = new SearchableComboBox<Equipment>((Gtk::Grid*)this, 1, "Body: ", m_db->Body(), DB_TYPE_E::BODY);
  m_bodyCombo->signal_selected_change().connect(sigc::mem_fun(*this, &EquipmentUI::on_equipment_change));

  m_capeCombo   = new SearchableComboBox<Equipment>((Gtk::Grid*)this, 2, "Cape: ", m_db->Cape(), DB_TYPE_E::CAPE);
  m_capeCombo->signal_selected_change().connect(sigc::mem_fun(*this, &EquipmentUI::on_equipment_change));

  m_feetCombo   = new SearchableComboBox<Equipment>((Gtk::Grid*)this, 3, "Feet: ", m_db->Feet(), DB_TYPE_E::FEET);
  m_feetCombo->signal_selected_change().connect(sigc::mem_fun(*this, &EquipmentUI::on_equipment_change));

  m_handCombo   = new SearchableComboBox<Equipment>((Gtk::Grid*)this, 4, "Hand: ", m_db->Hand(), DB_TYPE_E::HAND);
  m_handCombo->signal_selected_change().connect(sigc::mem_fun(*this, &EquipmentUI::on_equipment_change));

  m_headCombo   = new SearchableComboBox<Equipment>((Gtk::Grid*)this, 5, "Head: ", m_db->Head(), DB_TYPE_E::HEAD);
  m_headCombo->signal_selected_change().connect(sigc::mem_fun(*this, &EquipmentUI::on_equipment_change));

  m_legsCombo   = new SearchableComboBox<Equipment>((Gtk::Grid*)this, 6, "Legs: ", m_db->Legs(), DB_TYPE_E::LEGS);
  m_legsCombo->signal_selected_change().connect(sigc::mem_fun(*this, &EquipmentUI::on_equipment_change));

  m_neckCombo   = new SearchableComboBox<Equipment>((Gtk::Grid*)this, 7, "Neck: ", m_db->Neck(), DB_TYPE_E::NECK);
  m_neckCombo->signal_selected_change().connect(sigc::mem_fun(*this, &EquipmentUI::on_equipment_change));

  m_ringCombo   = new SearchableComboBox<Equipment>((Gtk::Grid*)this, 8, "Ring: ", m_db->Ring(), DB_TYPE_E::RING);
  m_ringCombo->signal_selected_change().connect(sigc::mem_fun(*this, &EquipmentUI::on_equipment_change));

  m_shieldCombo = new SearchableComboBox<Equipment>((Gtk::Grid*)this, 9, "Shield: ", m_db->Shield(), DB_TYPE_E::SHIELD);
  m_shieldCombo->signal_selected_change().connect(sigc::mem_fun(*this, &EquipmentUI::on_equipment_change));

  m_weaponCombo = new SearchableComboBox<Weapon>((Gtk::Grid*)this, 10, "Weapon: ", m_db->Weapons(), DB_TYPE_E::WEAPON);
  m_weaponCombo->signal_selected_change().connect(sigc::mem_fun(*this, &EquipmentUI::on_equipment_change));

  m_monsterCombo = new SearchableComboBox<Monster>((Gtk::Grid*)this, 12, "Monster: ", m_db->Monsters(), DB_TYPE_E::MONSTER);
  m_monsterCombo->signal_selected_change().connect(sigc::mem_fun(*this, &EquipmentUI::on_equipment_change));
}


Equipment EquipmentUI::Ammunition() const
{
  return m_ammoCombo->Selected();
}
Equipment EquipmentUI::Body() const
{
  return m_bodyCombo->Selected();
}
Equipment EquipmentUI::Cape() const
{
  return m_capeCombo->Selected();
}
Equipment EquipmentUI::Feet() const
{
  return m_feetCombo->Selected();
}
Equipment EquipmentUI::Hand() const
{
  return m_handCombo->Selected();
}
Equipment EquipmentUI::Head() const
{
  return m_headCombo->Selected();
}
Equipment EquipmentUI::Legs() const
{
  return m_legsCombo->Selected();
}
Equipment EquipmentUI::Neck() const
{
  return m_neckCombo->Selected();
}
Equipment EquipmentUI::Ring() const
{
  return m_ringCombo->Selected();
}
Equipment EquipmentUI::Shield() const
{
  return m_shieldCombo->Selected();
}

Weapon EquipmentUI::GetWeapon() const
{
  return m_weaponCombo->Selected();
}
Monster EquipmentUI::GetMonster() const
{
  return m_monsterCombo->Selected();
}

sigc::signal<void, DB_TYPE_E::Type> EquipmentUI::signal_equipment_change()
{
  return m_equipment_changed;
}

void EquipmentUI::on_equipment_change(DB_TYPE_E::Type i_type)
{
  m_equipment_changed.emit(i_type);
}