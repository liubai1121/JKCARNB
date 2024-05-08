#include <gtk/gtk.h>

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