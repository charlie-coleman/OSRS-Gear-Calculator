#include "SearchableComboBox.h"

#include <string>
#include <iostream>
#include <algorithm>

#include "Equipment.h"
#include "Weapon.h"
#include "Monster.h"

template <class T>
SearchableComboBox<T>::SearchableComboBox(Gtk::Grid* i_grid, int i_row, std::string i_labelStr, std::vector<T> i_db)
  : m_label{i_labelStr},
    m_combo(true)
{
  static_assert(std::is_base_of<Thing, T>::value, "T is not of base class Thing");
  m_db = i_db;

  m_refTreeModel = Gtk::TreeStore::create(m_columns);
  m_refCompletionModel = Gtk::TreeStore::create(m_columns);

  m_combo.set_model(m_refTreeModel);
  m_comboEntry = m_combo.get_entry();

  m_refEntryCompletion = Gtk::EntryCompletion::create();
  m_refEntryCompletion->set_model(m_refCompletionModel);
  m_refEntryCompletion->set_text_column(m_columns.m_colName);
  m_refEntryCompletion->set_popup_completion(true);
  m_refEntryCompletion->set_minimum_key_length(2);
  m_refEntryCompletion->signal_match_selected().connect(sigc::mem_fun(*this, &SearchableComboBox<T>::on_completion_selection), false);
  
  m_comboEntry->set_completion(m_refEntryCompletion);

  m_combo.set_entry_text_column(m_columns.m_colName);
  m_combo.set_can_focus(false);
  m_combo.set_button_sensitivity(Gtk::SENSITIVITY_ON);

  PopulateComboBox();

  if (m_comboEntry)
  {
    m_comboEntry->add_events(Gdk::FOCUS_CHANGE_MASK);
    m_comboEntry->signal_activate().connect(sigc::mem_fun(*this, &SearchableComboBox<T>::on_entry_activate));
  }

  m_label.set_alignment(Gtk::Align::ALIGN_START, Gtk::Align::ALIGN_CENTER);

  m_combo.signal_changed().connect(sigc::mem_fun(*this, &SearchableComboBox<T>::on_combo_changed));

  if (i_labelStr.compare("") == 0)
  {
    i_grid->attach(m_combo, 0, i_row);
  }
  else
  {
    i_grid->attach(m_label, 0, i_row);
    i_grid->attach(m_combo, 1, i_row);
  }
}

template <class T>
SearchableComboBox<T>::~SearchableComboBox()
{
}

template <class T>
T SearchableComboBox<T>::Selected() const
{
  return m_selectedItem;
}

template <class T>
void SearchableComboBox<T>::PopulateComboBox()
{
  for (int i = 0; i < m_db.size(); ++i)
  {
    Gtk::TreeModel::Row row = *(m_refTreeModel->append());
    Gtk::TreeModel::Row row2 = *(m_refCompletionModel->append());

    row[m_columns.m_colIndex] = i;
    row[m_columns.m_colName] = m_db[i].Name();
    row[m_columns.m_colId] = m_db[i].Id();

    row2[m_columns.m_colIndex] = i;
    row2[m_columns.m_colName] = m_db[i].Name();
    row2[m_columns.m_colId] = m_db[i].Id();

    if (i == 0) 
    {
      m_combo.set_active(row);
      m_selectedItem = m_db[0];
    }
  }
}

template <class T>
void SearchableComboBox<T>::on_combo_changed()
{
  Gtk::TreeModel::iterator it = m_combo.get_active();

  if (it)
  {
    Gtk::TreeModel::Row row = *it;

    if (row)
    {
      int index = row[m_columns.m_colIndex];
      m_selectedItem = m_db[index];
    }

    m_selected_change.emit();
  }
}

template <class T>
void SearchableComboBox<T>::on_entry_activate()
{
  Glib::ustring entryVal = m_comboEntry->get_text();
  Glib::ustring lowerEntry = entryVal.lowercase();

  Gtk::TreeModel::iterator iter = m_combo.get_active();
  Gtk::TreeModel::Row row = *iter;

  if (row)
  {
    Glib::ustring comboName = row[m_columns.m_colName];
    std::string lowerCombo(comboName.lowercase());

    if (entryVal.compare(comboName) == 0)
    {
      return;
    }
  }

  Gtk::TreeModel::Children comboChildren = m_refTreeModel->children();

  bool foundBadMatch = false;
  Gtk::TreeModel::Row badMatch;
  for (auto it = comboChildren.begin(); it != comboChildren.end(); ++it)
  {
    Gtk::TreeModel::Row comboRow = *it;

    if (comboRow)
    {
      Glib::ustring rowName = comboRow[m_columns.m_colName];
      std::string lowerName(rowName.lowercase());

      if (rowName.compare(entryVal) == 0)
      {
        m_combo.set_active(comboRow);
        return;
      }
      else if (!foundBadMatch && lowerName.find(lowerEntry) != -1)
      {
        badMatch = comboRow;
        foundBadMatch = true;
      }
    }
  }

  if (foundBadMatch)
    m_combo.set_active(badMatch);
}

template <class T>
bool SearchableComboBox<T>::on_completion_selection(const Gtk::TreeModel::iterator& iter)
{
  Gtk::TreeModel::Row row = *iter;

  Gtk::TreeModel::Children comboChildren = m_refTreeModel->children();

  if (row)
  {
    int id = row[m_columns.m_colId];

    for(auto it = comboChildren.begin(); it != comboChildren.end(); ++it)
    {
      Gtk::TreeModel::Row comboRow = *it;
      
      if (row)
      {
        int comboId = comboRow[m_columns.m_colId];

        if (id == comboId)
        {
          m_combo.set_active(comboRow);
        }
      }
    }
  }
  return false;
}

template <class T>
std::string SearchableComboBox<T>::ToLower(std::string i_str)
{
  std::string temp = i_str;
  std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
  return temp;
}

template <class T>
sigc::signal<void> SearchableComboBox<T>::signal_selected_change()
{
  return m_selected_change;
}

template class SearchableComboBox<Equipment>;
template class SearchableComboBox<Weapon>;
template class SearchableComboBox<Monster>;