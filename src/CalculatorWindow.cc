#include "CalculatorWindow.h"

#include <iostream>

CalculatorWindow::CalculatorWindow()
{
  set_title("Old School Runescape DPS Calculator");
  
  set_default_size(600, 600);
  set_border_width(10);

  m_db.ReadFilesToJson();
  m_db.ConvertJsonToDatabases();

  m_playerUI = new PlayerUI("Player Stats", &m_db, m_setup, SETUP_COUNT);
  
  for (int i = 0; i < SETUP_COUNT; ++i)
  {
    char name[32];
    sprintf(name, "Setup %d", (i+1));
    std::string nameStr(name);

    m_setup[i] = new Setup();
    m_equipmentUI[i] = new EquipmentUI(nameStr, &m_db, m_setup[i]);
  }

  InitializeSetup();

  m_container.set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);
  
  m_outputContainer.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
  m_playerContainer.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
  m_setupContainer.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);

  m_playerUI->signal_all_setups_changed().connect(sigc::mem_fun(*this, &CalculatorWindow::on_all_setups_changed));

  m_playerContainer.add(*m_playerUI);
  
  for (int i = 0; i < SETUP_COUNT; ++i)
  {
    m_equipmentUI[i]->signal_setup_update().connect(sigc::bind( sigc::mem_fun(*this, &CalculatorWindow::on_setup_update), i));

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
    m_setup[i]->SetPlayer(m_playerUI->GetPlayer());
    m_setup[i]->SetMonster(m_playerUI->GetMonster());

    char name[32];
    sprintf(name, "Setup %d Output", (i+1));
    std::string nameStr(name);
    
    m_setupOutput[i] = new SetupOutput(nameStr, m_setup[i]);
    m_setupOutput[i]->Update();
  }
}

void CalculatorWindow::on_all_setups_changed()
{
  for(int i = 0; i < SETUP_COUNT; ++i)
  {
    m_setupOutput[i]->Update();
  }
}

void CalculatorWindow::on_setup_update(int i_setupIndex)
{
  m_setupOutput[i_setupIndex]->Update();
}