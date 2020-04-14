#include "CalculatorWindow.h"

#include <iostream>

CalculatorWindow::CalculatorWindow()
{
  set_title("Old School Runescape DPS Calculator");
  
  set_default_size(600, 600);
  set_border_width(10);

  m_db.ReadFilesToJson();
  m_db.ConvertJsonToDatabases();

  m_playerUI = new PlayerUI("Player Stats");
  m_equipmentUI = new EquipmentUI(&m_db);

  InitializeSetup();

  m_container.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
  
  m_setupContainer.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
  m_playerContainer.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);

  m_playerUI->signal_player_changed().connect(sigc::mem_fun(*this, &CalculatorWindow::on_player_changed));
  m_equipmentUI->signal_equipment_change().connect(sigc::mem_fun(*this, &CalculatorWindow::on_equipment_changed));

  m_setupContainer.add(*m_equipmentUI);
  m_playerContainer.add(*m_playerUI);

  m_setupContainer.set_border_width(10);
  m_playerContainer.set_border_width(10);

  m_container.add(m_playerContainer);
  m_container.add(m_setupContainer);
  
  add(m_container);

  show_all_children();
}

CalculatorWindow::~CalculatorWindow()
{
}

void CalculatorWindow::InitializeSetup()
{
  m_setup = new Setup(m_playerUI->GetPlayer(), m_equipmentUI->GetMonster(), m_equipmentUI->Ammunition(), m_equipmentUI->Body(),   m_equipmentUI->Cape(),
                                               m_equipmentUI->Feet(),       m_equipmentUI->Hand(),       m_equipmentUI->Head(),   m_equipmentUI->Legs(),
                                               m_equipmentUI->Neck(),       m_equipmentUI->Ring(),       m_equipmentUI->Shield(), m_equipmentUI->GetWeapon());
}

void CalculatorWindow::on_player_changed()
{
  m_setup->SetPlayer(m_playerUI->GetPlayer());

  m_setup->Recalculate();
  std::cout << "Max hit: " << m_setup->MaxDamage() << std::endl;
  std::cout << "Accuracy: " << m_setup->Accuracy() << std::endl;
  std::cout << "DPS: " << m_setup->DPS() << std::endl;
}

void CalculatorWindow::on_equipment_changed(DB_TYPE_E::Type i_type)
{
  switch (i_type)
  {
  case DB_TYPE_E::AMMO:
    m_setup->SetAmmunition(m_equipmentUI->Ammunition());
    break;
  case DB_TYPE_E::BODY:
    m_setup->SetBody(m_equipmentUI->Body());
    break;
  case DB_TYPE_E::CAPE:
    m_setup->SetCape(m_equipmentUI->Cape());
    break;
  case DB_TYPE_E::FEET:
    m_setup->SetFeet(m_equipmentUI->Feet());
    break;
  case DB_TYPE_E::HAND:
    m_setup->SetHand(m_equipmentUI->Hand());
    break;
  case DB_TYPE_E::HEAD:
    m_setup->SetHead(m_equipmentUI->Head());
    break;
  case DB_TYPE_E::NECK:
    m_setup->SetNeck(m_equipmentUI->Neck());
    break;
  case DB_TYPE_E::LEGS:
    m_setup->SetLegs(m_equipmentUI->Legs());
    break;
  case DB_TYPE_E::RING:
    m_setup->SetRing(m_equipmentUI->Ring());
    break;
  case DB_TYPE_E::SHIELD:
    m_setup->SetShield(m_equipmentUI->Shield());
    break;
  case DB_TYPE_E::WEAPON:
    m_setup->SetWeapon(m_equipmentUI->GetWeapon());
    break;
  case DB_TYPE_E::MONSTER:
    m_setup->SetMonster(m_equipmentUI->GetMonster());
    break;
  default:
    break;
  }

  m_setup->Recalculate();
  std::cout << "Max hit: " << m_setup->MaxDamage() << std::endl;
  std::cout << "Accuracy: " << m_setup->Accuracy() << std::endl;
  std::cout << "DPS: " << m_setup->DPS() << std::endl;
}