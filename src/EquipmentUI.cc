#include "EquipmentUI.h"

#include <string>

EquipmentUI::EquipmentUI(std::string i_title, Database *i_db, Setup *i_setup)
  : m_titleLabel{i_title},
    m_db(i_db),
    m_setup(i_setup)
{
  InitializeComboBoxes();
  PopulateSetup();

  Pango::AttrList attrList;
  Pango::AttrInt attr = Pango::Attribute::create_attr_size(20 * 1024);
  attrList.insert(attr);

  m_titleLabel.set_attributes(attrList);
  m_titleLabel.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);

  set_border_width(15);
  set_orientation(Gtk::ORIENTATION_VERTICAL);

  add(m_titleLabel);
  add(m_grid);
}

EquipmentUI::~EquipmentUI()
{
}

void EquipmentUI::InitializeComboBoxes()
{
  m_weaponCombo = new SearchableComboBox<Weapon>(&m_grid, 0, "Weapon: ", m_db->Weapons());
  m_weaponCombo->signal_selected_change().connect(sigc::mem_fun(*this, &EquipmentUI::on_weapon_change));

  m_stanceCombo = new StanceComboBox(&m_grid, 1, "Stance: ", m_weaponCombo->Selected());
  m_stanceCombo->signal_stance_changed().connect(sigc::mem_fun(*this, &EquipmentUI::on_stance_change));

  m_ammoCombo   = new SearchableComboBox<Equipment>(&m_grid, 2, "Ammunition: ", m_db->Ammunition());
  m_ammoCombo->signal_selected_change().connect(sigc::bind<DB_TYPE_E::Type>( sigc::mem_fun(*this, &EquipmentUI::on_equipment_change), DB_TYPE_E::AMMO ));

  m_headCombo   = new SearchableComboBox<Equipment>(&m_grid, 3, "Head: ", m_db->Head());
  m_headCombo->signal_selected_change().connect(sigc::bind<DB_TYPE_E::Type>( sigc::mem_fun(*this, &EquipmentUI::on_equipment_change), DB_TYPE_E::HEAD ));

  m_capeCombo   = new SearchableComboBox<Equipment>(&m_grid, 4, "Cape: ", m_db->Cape());
  m_capeCombo->signal_selected_change().connect(sigc::bind<DB_TYPE_E::Type>( sigc::mem_fun(*this, &EquipmentUI::on_equipment_change), DB_TYPE_E::CAPE ));

  m_neckCombo   = new SearchableComboBox<Equipment>(&m_grid, 5, "Neck: ", m_db->Neck());
  m_neckCombo->signal_selected_change().connect(sigc::bind<DB_TYPE_E::Type>( sigc::mem_fun(*this, &EquipmentUI::on_equipment_change), DB_TYPE_E::NECK ));

  m_bodyCombo   = new SearchableComboBox<Equipment>(&m_grid, 6, "Body: ", m_db->Body());
  m_bodyCombo->signal_selected_change().connect(sigc::bind<DB_TYPE_E::Type>( sigc::mem_fun(*this, &EquipmentUI::on_equipment_change), DB_TYPE_E::BODY ));

  m_legsCombo   = new SearchableComboBox<Equipment>(&m_grid, 7, "Legs: ", m_db->Legs());
  m_legsCombo->signal_selected_change().connect(sigc::bind<DB_TYPE_E::Type>( sigc::mem_fun(*this, &EquipmentUI::on_equipment_change), DB_TYPE_E::LEGS ));

  m_shieldCombo = new SearchableComboBox<Equipment>(&m_grid, 8, "Shield: ", m_db->Shield());
  m_shieldCombo->signal_selected_change().connect(sigc::bind<DB_TYPE_E::Type>( sigc::mem_fun(*this, &EquipmentUI::on_equipment_change), DB_TYPE_E::SHIELD ));

  m_handCombo   = new SearchableComboBox<Equipment>(&m_grid, 9, "Hand: ", m_db->Hand());
  m_handCombo->signal_selected_change().connect(sigc::bind<DB_TYPE_E::Type>( sigc::mem_fun(*this, &EquipmentUI::on_equipment_change), DB_TYPE_E::HAND ));

  m_feetCombo   = new SearchableComboBox<Equipment>(&m_grid, 10, "Feet: ", m_db->Feet());
  m_feetCombo->signal_selected_change().connect(sigc::bind<DB_TYPE_E::Type>( sigc::mem_fun(*this, &EquipmentUI::on_equipment_change), DB_TYPE_E::FEET ));

  m_ringCombo   = new SearchableComboBox<Equipment>(&m_grid, 11, "Ring: ", m_db->Ring());
  m_ringCombo->signal_selected_change().connect(sigc::bind<DB_TYPE_E::Type>( sigc::mem_fun(*this, &EquipmentUI::on_equipment_change), DB_TYPE_E::RING ));
}

void EquipmentUI::PopulateSetup()
{
  m_setup->SetWeapon(m_weaponCombo->Selected());
  m_setup->SetStance(m_stanceCombo->StanceIndex());
  m_setup->SetAmmunition(m_ammoCombo->Selected());
  m_setup->SetBody(m_bodyCombo->Selected());
  m_setup->SetCape(m_capeCombo->Selected());
  m_setup->SetFeet(m_feetCombo->Selected());
  m_setup->SetHand(m_handCombo->Selected());
  m_setup->SetHead(m_headCombo->Selected());
  m_setup->SetNeck(m_neckCombo->Selected());
  m_setup->SetLegs(m_legsCombo->Selected());
  m_setup->SetRing(m_ringCombo->Selected());
  m_setup->SetShield(m_shieldCombo->Selected());

  m_signal_setup_update.emit();
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

void EquipmentUI::on_equipment_change(DB_TYPE_E::Type i_type)
{
  switch (i_type)
  {
  case DB_TYPE_E::AMMO:
    m_setup->SetAmmunition(m_ammoCombo->Selected());
    break;
  case DB_TYPE_E::BODY:
    m_setup->SetBody(m_bodyCombo->Selected());
    break;
  case DB_TYPE_E::CAPE:
    m_setup->SetCape(m_capeCombo->Selected());
    break;
  case DB_TYPE_E::FEET:
    m_setup->SetFeet(m_feetCombo->Selected());
    break;
  case DB_TYPE_E::HAND:
    m_setup->SetHand(m_handCombo->Selected());
    break;
  case DB_TYPE_E::HEAD:
    m_setup->SetHead(m_headCombo->Selected());
    break;
  case DB_TYPE_E::NECK:
    m_setup->SetNeck(m_neckCombo->Selected());
    break;
  case DB_TYPE_E::LEGS:
    m_setup->SetLegs(m_legsCombo->Selected());
    break;
  case DB_TYPE_E::RING:
    m_setup->SetRing(m_ringCombo->Selected());
    break;
  case DB_TYPE_E::SHIELD:
    m_setup->SetShield(m_shieldCombo->Selected());
    break;
  default:
    break;
  }

  m_signal_setup_update.emit();
}

void EquipmentUI::on_weapon_change()
{
  Weapon i_weap = m_weaponCombo->Selected();

  m_stanceCombo->SetWeapon(i_weap);
  m_setup->SetWeapon(i_weap);

  m_signal_setup_update.emit();
}

void EquipmentUI::on_stance_change(int i_stanceIndex)
{
  m_setup->SetStance(i_stanceIndex);

  m_signal_setup_update.emit();
}

sigc::signal<void> EquipmentUI::signal_setup_update()
{
  return m_signal_setup_update;
}