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
  
  for (int i = 0; i < SETUP_COUNT; ++i)
  {
    m_equipmentUI[i] = new EquipmentUI(&m_db);
  }

  InitializeSetup();

  m_container.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
  
  m_outputContainer.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
  m_playerContainer.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
  m_setupContainer.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);

  m_playerUI->signal_player_changed().connect(sigc::mem_fun(*this, &CalculatorWindow::on_player_changed));

  m_playerContainer.add(*m_playerUI);
  
  for (int i = 0; i < SETUP_COUNT; ++i)
  {
    m_equipmentUI[i]->signal_equipment_change().connect(sigc::bind<int>(sigc::mem_fun(*this, &CalculatorWindow::on_equipment_changed), i));
    m_equipmentUI[i]->signal_stance_change().connect(sigc::bind<int>(sigc::mem_fun(*this, &CalculatorWindow::on_stance_changed), i));

    m_setupContainer.add(*m_equipmentUI[i]);
    m_outputContainer.add(*m_setupOutput[i]);
  }

  m_setupContainer.set_border_width(10);
  m_playerContainer.set_border_width(10);
  m_outputContainer.set_border_width(10);

  m_container.add(m_outputContainer);
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
  for (int i = 0; i < SETUP_COUNT; ++i)
  {
    m_setup[i] = new Setup(m_playerUI->GetPlayer(), m_equipmentUI[i]->GetMonster(), m_equipmentUI[i]->Ammunition(), m_equipmentUI[i]->Body(),   m_equipmentUI[i]->Cape(),
                                                    m_equipmentUI[i]->Feet(),       m_equipmentUI[i]->Hand(),       m_equipmentUI[i]->Head(),   m_equipmentUI[i]->Legs(),
                                                    m_equipmentUI[i]->Neck(),       m_equipmentUI[i]->Ring(),       m_equipmentUI[i]->Shield(), m_equipmentUI[i]->GetWeapon());

    m_setupOutput[i] = new SetupOutput(m_setup[i]);
    m_setupOutput[i]->Update();
  }
}

void CalculatorWindow::on_player_changed()
{
  for (int i = 0; i < SETUP_COUNT; ++i)
  {
    m_setup[i]->SetPlayer(m_playerUI->GetPlayer());
    m_setupOutput[i]->Update();
  }
}

void CalculatorWindow::on_equipment_changed(DB_TYPE_E::Type i_type, int i_setupIndex)
{
  EquipmentUI *eq = m_equipmentUI[i_setupIndex];
  Setup *s = m_setup[i_setupIndex];
  SetupOutput *sOut = m_setupOutput[i_setupIndex];

  switch (i_type)
  {
  case DB_TYPE_E::AMMO:
    s->SetAmmunition(eq->Ammunition());
    break;
  case DB_TYPE_E::BODY:
    s->SetBody(eq->Body());
    break;
  case DB_TYPE_E::CAPE:
    s->SetCape(eq->Cape());
    break;
  case DB_TYPE_E::FEET:
    s->SetFeet(eq->Feet());
    break;
  case DB_TYPE_E::HAND:
    s->SetHand(eq->Hand());
    break;
  case DB_TYPE_E::HEAD:
    s->SetHead(eq->Head());
    break;
  case DB_TYPE_E::NECK:
    s->SetNeck(eq->Neck());
    break;
  case DB_TYPE_E::LEGS:
    s->SetLegs(eq->Legs());
    break;
  case DB_TYPE_E::RING:
    s->SetRing(eq->Ring());
    break;
  case DB_TYPE_E::SHIELD:
    s->SetShield(eq->Shield());
    break;
  case DB_TYPE_E::WEAPON:
    s->SetWeapon(eq->GetWeapon());
    break;
  case DB_TYPE_E::MONSTER:
    s->SetMonster(eq->GetMonster());
    break;
  default:
    break;
  }

  sOut->Update();
}

void CalculatorWindow::on_stance_changed(int i_stanceIndex, int i_setupIndex)
{
  m_setup[i_setupIndex]->SetStance(i_stanceIndex);
  m_setupOutput[i_setupIndex]->Update();
}