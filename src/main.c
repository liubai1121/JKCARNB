#include <gtk/gtk.h>
#include <libadwaita-1/adwaita.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpfr.h>
#include "fuel_vehicle.h"
#include "new_energy_vehicles.h"

static void
activate(GtkApplication *app,
         gpointer user_data)
{
  // 下面两行注释掉就可以使用adwaita的皮肤了
  GtkSettings *settings = gtk_settings_get_default();
  g_object_set(settings, "gtk-theme-name", "Adwaita", NULL);

  GtkWidget *window;
  GtkWidget *stack_switcher;
  GtkWidget *stack;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "车价计算器");
  gtk_window_set_default_size(GTK_WINDOW(window), 540, 800);

  stack = gtk_stack_new();

  GtkWidget *fuel_vehicle_page = get_fuel_vehicle_page();
  GtkWidget *new_energy_vehicles_page = get_new_energy_vehicles_page();

  gtk_stack_add_titled(GTK_STACK(stack), fuel_vehicle_page, "燃油车", "燃油车");
  gtk_stack_add_titled(GTK_STACK(stack), new_energy_vehicles_page, "新能源车", "新能源车");

  stack_switcher = gtk_stack_switcher_new();
  gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(stack_switcher), GTK_STACK(stack));

  // // 创建一个垂直布局的盒子，用于容纳切换器和堆栈容器
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  gtk_box_append(GTK_BOX(box), stack_switcher);
  gtk_box_append(GTK_BOX(box), stack);

  gtk_window_set_child(GTK_WINDOW(window), box);

  gtk_widget_set_visible(window, true);

  gtk_window_present(GTK_WINDOW(window));
}

int main(int argc,
         char **argv)
{
  g_autoptr(AdwApplication) app = NULL;
  int status;

  app = adw_application_new("org.example.Hello", G_APPLICATION_DEFAULT_FLAGS);

  // // 获取默认的GtkSettings对象
  // GtkSettings *settings = gtk_settings_get_default();

  // // 设置主题为Adwaita
  // g_object_set(settings, "gtk-theme-name", "Adwaita", NULL);

  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
