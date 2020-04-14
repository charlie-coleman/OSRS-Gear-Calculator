#include "SearchableComboBox.h"

#include <iostream>

#include "Equipment.h"
#include "Weapon.h"
#include "Monster.h"

template <class T>
SearchableComboBox<T>::SearchableComboBox(Gtk::Grid* i_grid, int i_row, std::string i_labelStr, std::vector<T> i_db, DB_TYPE_E::Type i_type)
  : m_label{i_labelStr},
    m_combo(),
    m_type(i_type)
{
  static_assert(std::is_base_of<Thing, T>::value, "T is not of base class Thing");
  m_db = i_db;

  m_refTreeModel = Gtk::TreeStore::create(m_columns);
  m_combo.set_model(m_refTreeModel);

  PopulateComboBox();

  m_label.set_alignment(Gtk::Align::ALIGN_START, Gtk::Align::ALIGN_CENTER);

  m_combo.pack_start(m_columns.m_colName);

  m_combo.signal_changed().connect(sigc::mem_fun(*this, &SearchableComboBox<T>::on_combo_changed));

  i_grid->attach(m_label, 0, i_row);
  i_grid->attach(m_combo, 1, i_row);
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

    row[m_columns.m_colIndex] = i;
    row[m_columns.m_colName] = m_db[i].Name();
    row[m_columns.m_colId] = m_db[i].Id();

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
  }
  else
  {
    std::cerr << "SearchableComboBox: invalid active item on change." << std::endl;
  }

  m_selected_change.emit(m_type);
}

template <class T>
sigc::signal<void, DB_TYPE_E::Type> SearchableComboBox<T>::signal_selected_change()
{
  return m_selected_change;
}

template class SearchableComboBox<Equipment>;
template class SearchableComboBox<Weapon>;
template class SearchableComboBox<Monster>;