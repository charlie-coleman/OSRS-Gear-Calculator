#include "SearchableComboBox.h"

#include <iostream>

#include "Equipment.h"
#include "Weapon.h"
#include "Monster.h"

template <class T>
SearchableComboBox<T>::SearchableComboBox(std::vector<T> i_db)
  : Glib::ObjectBase("searchablecombobox"),
    Gtk::ComboBox()
{
  static_assert(std::is_base_of<Thing, T>::value, "T is not of base class Thing");
  m_db = i_db;

  m_refTreeModel = Gtk::TreeStore::create(m_columns);
  set_model(m_refTreeModel);

  PopulateComboBox();

  pack_start(m_columns.m_colName);

  signal_changed().connect(sigc::mem_fun(*this, &SearchableComboBox<T>::on_combo_changed));
}

template <class T>
SearchableComboBox<T>::~SearchableComboBox()
{
}

template <class T>
const T& SearchableComboBox<T>::Selected() const
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
      set_active(row);
      m_selectedItem = m_db[0];
    }
  }
}

template <class T>
void SearchableComboBox<T>::on_combo_changed()
{
  Gtk::TreeModel::iterator it = get_active();

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
}

template class SearchableComboBox<Equipment>;
template class SearchableComboBox<Weapon>;
template class SearchableComboBox<Monster>;