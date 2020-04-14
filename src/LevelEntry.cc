#include "LevelEntry.h"

#include <iostream>

LevelEntry::LevelEntry(Gtk::Grid *i_grid, int i_row, std::string i_labelStr, std::vector<std::string> i_potionNames, std::vector<std::string> i_prayerNames)
  : m_label{i_labelStr},
    m_level(99),
    m_potionCombo(),
    m_prayerCombo()
{
  m_label.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);

  m_levelEntry.configure((Glib::RefPtr<Gtk::Adjustment>)nullptr, 1.0, 2);

  m_levelEntry.set_numeric(true);
  m_levelEntry.set_range(1, 99);
  m_levelEntry.set_digits(0);
  m_levelEntry.set_increments(1, 5);
  m_levelEntry.set_value(99);

  m_levelEntry.signal_value_changed().connect(sigc::mem_fun(*this, &LevelEntry::on_level_changed));

  i_grid->attach(m_label, 0, i_row);
  i_grid->attach(m_levelEntry, 1, i_row);

  if (i_potionNames.size() > 0)
  {
    m_potionNames = i_potionNames;
    InitializePotions();
    i_grid->attach(m_potionCombo, 2, i_row);
  }

  if (i_prayerNames.size() > 0)
  {
    m_prayerNames = i_prayerNames;
    InitializePrayers();
    i_grid->attach(m_prayerCombo, 3, i_row);
  }
}

LevelEntry::~LevelEntry()
{
}

void LevelEntry::on_level_changed()
{
  m_level = m_levelEntry.get_value_as_int();

  m_signal_level_changed.emit(m_level);
}

void LevelEntry::on_potion_changed()
{
  Gtk::TreeStore::iterator it = m_potionCombo.get_active();

  if (it)
  {
    Gtk::TreeModel::Row row = *it;

    if (row)
    {
      m_potionIndex = row[m_columns.m_colIndex];
    }
  }
  else
  {
    std::cerr << "Error: on potion changed received bad active value" << std::endl;
  }

  m_signal_potion_changed.emit(m_potionIndex);
}

void LevelEntry::on_prayer_changed()
{
  Gtk::TreeStore::iterator it = m_prayerCombo.get_active();

  if (it)
  {
    Gtk::TreeModel::Row row = *it;

    if (row)
    {
      m_prayerIndex = row[m_columns.m_colIndex];
    }
  }

  m_signal_prayer_changed.emit(m_prayerIndex);
}

void LevelEntry::InitializePotions()
{
  m_potionTreeModel = Gtk::TreeStore::create(m_columns);
  m_potionCombo.set_model(m_potionTreeModel);

  for (int i = 0; i < m_potionNames.size(); ++i)
  {
    Gtk::TreeModel::Row row = *(m_potionTreeModel->append());

    row[m_columns.m_colIndex] = i;
    row[m_columns.m_colName] = m_potionNames[i];

    if (i == 0)
    {
      m_potionCombo.set_active(row);
      m_potionIndex = i;
    }
  }

  m_potionCombo.pack_start(m_columns.m_colName);
  m_potionCombo.signal_changed().connect(sigc::mem_fun(*this, &LevelEntry::on_potion_changed));
}

void LevelEntry::InitializePrayers()
{
  m_prayerTreeModel = Gtk::TreeStore::create(m_columns);
  m_prayerCombo.set_model(m_prayerTreeModel);

  for (int i = 0; i < m_prayerNames.size(); ++i)
  {
    Gtk::TreeModel::Row row = *(m_prayerTreeModel->append());

    row[m_columns.m_colIndex] = i;
    row[m_columns.m_colName] = m_prayerNames[i];

    if (i == 0)
    {
      m_prayerCombo.set_active(row);
      m_prayerIndex = i;
    }
  }

  m_prayerCombo.pack_start(m_columns.m_colName);
  m_prayerCombo.signal_changed().connect(sigc::mem_fun(*this, &LevelEntry::on_prayer_changed));
}

int LevelEntry::Level() const
{
  return m_level;
}

sigc::signal<void, int> LevelEntry::signal_level_changed()
{
  return m_signal_level_changed;
}

sigc::signal<void, int> LevelEntry::signal_potion_changed()
{
  return m_signal_potion_changed;
}

sigc::signal<void, int> LevelEntry::signal_prayer_changed()
{
  return m_signal_prayer_changed;
}