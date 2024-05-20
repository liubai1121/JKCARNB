#include <gtk/gtk.h>
#include "timeutil.h"

double get_entry_value(GtkWidget *entry);

double get_grid_entry_value(GtkWidget *fuel_vehicle_grid, int cloumn, int row);

GtkWidget *get_years_months_box(int year_range);

void get_selected_year_and_month_from_box(GtkWidget *years_months_box, char year[MAX_YEAR_STR_LENGTH], char month[MAX_MONTH_STR_LENGTH]);

GtkWidget *get_settlement_currency_drop_down();