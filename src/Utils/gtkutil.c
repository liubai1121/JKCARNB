#include <gtk/gtk.h>
#include "timeutil.h"

double get_entry_value(GtkWidget *entry)
{
  GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entry));
  const char *value_s = gtk_entry_buffer_get_text(buffer);
  return atof(value_s);
}

double get_grid_entry_value(GtkWidget *fuel_vehicle_grid, int cloumn, int row)
{
  GtkWidget *entry = gtk_grid_get_child_at(GTK_GRID(fuel_vehicle_grid), cloumn, row);
  return get_entry_value(entry);
}

void get_selected_value(GtkWidget *drop_down, char *value)
{
  guint position = gtk_drop_down_get_selected(GTK_DROP_DOWN(drop_down));
  GListModel *model = gtk_drop_down_get_model(GTK_DROP_DOWN(drop_down));
  const char *seleted = gtk_string_list_get_string(GTK_STRING_LIST(model), position);
  strcpy(value, seleted);
}

GtkWidget *get_years_months_box(int year_range)
{
  char years[year_range][MAX_YEAR_STR_LENGTH];
  initLastYears(years, year_range);

  const char *year_items[year_range + 2];
  for (int i = 0; i < year_range; i++)
  {
    year_items[i + 1] = years[i];
  }
  year_items[0] = "";
  year_items[year_range] = NULL;

  GtkWidget *actual_vehicle_age_years = gtk_drop_down_new_from_strings(year_items);
  gtk_widget_set_size_request(actual_vehicle_age_years, 100, -1);
  char months[MAX_MONTH_LENGTH][MAX_MONTH_STR_LENGTH];
  initMonths(months);

  const char *month_items[MAX_MONTH_LENGTH + 2];
  for (int i = 0; i < MAX_MONTH_LENGTH; i++)
  {
    month_items[i + 1] = months[i];
  }
  month_items[0] = "";
  month_items[MAX_MONTH_LENGTH + 1] = NULL;

  GtkWidget *actual_vehicle_age_months = gtk_drop_down_new_from_strings(month_items);
  gtk_widget_set_size_request(actual_vehicle_age_months, 60, -1);

  GtkWidget *actual_vehicle_age_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
  gtk_box_append(GTK_BOX(actual_vehicle_age_box), actual_vehicle_age_years);
  gtk_box_append(GTK_BOX(actual_vehicle_age_box), actual_vehicle_age_months);
  return actual_vehicle_age_box;
}

GtkWidget *get_settlement_currency_drop_down()
{
  const char *settlement_currency_items[] = {"美金", "人民币", "卢布", NULL};
  GtkWidget *settlement_currency = gtk_drop_down_new_from_strings(settlement_currency_items);
  gtk_widget_set_size_request(settlement_currency, 180, -1);
  return settlement_currency;
}

void get_selected_year_and_month_from_box(GtkWidget *years_months_box, char year[MAX_YEAR_STR_LENGTH], char month[MAX_MONTH_STR_LENGTH])
{
  GtkWidget *years_drop_down = gtk_widget_get_first_child(years_months_box);
  GtkWidget *months_drop_down = gtk_widget_get_next_sibling(years_drop_down);

  get_selected_value(years_drop_down, year);
  get_selected_value(months_drop_down, month);
}
