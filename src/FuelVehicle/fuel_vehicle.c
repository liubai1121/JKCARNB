#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "gtkutil.h"
#include "stringformatutil.h"
#include "calculatecarpriceutil.h"

void on_calculate_tax_refund_amount_for_fuel_vehicle(GtkWidget *tax_refund_amount_entry, GtkEntryIconPosition icon_pos, GtkWidget *naked_car_invoice_price_entry)
{
  double naked_car_invoice_price = get_entry_value(naked_car_invoice_price_entry);
  double tax_refund_amount_d = calculate_tax_refund_amount(naked_car_invoice_price);

  char tax_refund_amount_s[20];
  to_str(tax_refund_amount_s, tax_refund_amount_d);

  GtkEntryBuffer *buffer = gtk_entry_buffer_new(tax_refund_amount_s, -1);
  gtk_entry_set_buffer(GTK_ENTRY(tax_refund_amount_entry), buffer);
}

void on_calculate_purchase_tax_for_fuel_vehicle(GtkWidget *purchase_tax_entry, GtkEntryIconPosition icon_pos, GtkWidget *naked_car_invoice_price_entry)
{
  double naked_car_invoice_price = get_entry_value(naked_car_invoice_price_entry);
  double purchase_tax_d = calculate_purchase_tax(naked_car_invoice_price);

  char purchase_tax_s[20];
  sprintf(purchase_tax_s, "%.2f", purchase_tax_d);

  const char *c_purchase_tax_s = purchase_tax_s;
  GtkEntryBuffer *buffer = gtk_entry_buffer_new(c_purchase_tax_s, -1);
  gtk_entry_set_buffer(GTK_ENTRY(purchase_tax_entry), buffer);
}

void on_calculate_quote_for_fuel_vehicle(GtkWidget *button, GtkWidget *fuel_vehicle_grid)
{
  GtkWidget *naked_car_invoice_price_entry;
  GtkWidget *purchase_tax_entry;
  GtkWidget *tax_refund_amount_entry;

  double new_car_guide_price = get_grid_entry_value(fuel_vehicle_grid, 1, 0);   // "新车指导价
  double full_payment_discount = get_grid_entry_value(fuel_vehicle_grid, 1, 1); // 全款优惠
  naked_car_invoice_price_entry = gtk_grid_get_child_at(GTK_GRID(fuel_vehicle_grid), 1, 2);
  double naked_car_invoice_price = get_entry_value(naked_car_invoice_price_entry);     // 裸车发票价
  double on_the_cards = get_grid_entry_value(fuel_vehicle_grid, 1, 3);                 // 上牌
  double compulsory_traffic_insurance = get_grid_entry_value(fuel_vehicle_grid, 1, 4); // 交强险
  double domestic_shipping = get_grid_entry_value(fuel_vehicle_grid, 1, 5);            // 国内运费
  double customs_clearance = get_grid_entry_value(fuel_vehicle_grid, 1, 6);            // 报关

  purchase_tax_entry = gtk_grid_get_child_at(GTK_GRID(fuel_vehicle_grid), 1, 7);
  on_calculate_purchase_tax_for_fuel_vehicle(purchase_tax_entry, GTK_ENTRY_ICON_SECONDARY, naked_car_invoice_price_entry);
  double purchase_tax = get_entry_value(purchase_tax_entry); // 购置税

  tax_refund_amount_entry = gtk_grid_get_child_at(GTK_GRID(fuel_vehicle_grid), 1, 8);
  on_calculate_tax_refund_amount_for_fuel_vehicle(tax_refund_amount_entry, GTK_ENTRY_ICON_SECONDARY, naked_car_invoice_price_entry);
  double tax_refund_amount = get_entry_value(tax_refund_amount_entry); // 退税金额

  struct VEHICLE_PRICE vehicle_price = {
      new_car_guide_price,
      full_payment_discount,
      naked_car_invoice_price,
      on_the_cards,
      compulsory_traffic_insurance,
      domestic_shipping,
      customs_clearance,
      purchase_tax,
      tax_refund_amount,
  };

  double quote_d = calculate_quote(&vehicle_price);

  char quote_s[20];
  to_rmb(quote_s, quote_d);

  GtkEntryBuffer *buffer = gtk_entry_buffer_new(quote_s, -1);
  GtkWidget *quote_entry = gtk_grid_get_child_at(GTK_GRID(fuel_vehicle_grid), 1, 10);
  gtk_entry_set_buffer(GTK_ENTRY(quote_entry), buffer);
}

GtkWidget *get_fuel_vehicle_page()
{

  GtkWidget *box;
  GtkWidget *grid;

  box = gtk_center_box_new();

  grid = gtk_grid_new();
  gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 10);

  // gtk_widget_set_hexpand(grid, TRUE);

  // "新车指导价
  GtkWidget *new_car_guide_price_label = gtk_label_new("新车指导价 *：");
  gtk_widget_set_halign(new_car_guide_price_label, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), new_car_guide_price_label, 0, 0, 1, 1);

  GtkWidget *new_car_guide_price_entry = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), new_car_guide_price_entry, 1, 0, 1, 1);

  // 全款优惠
  GtkWidget *full_payment_discount_label = gtk_label_new("全款优惠 *：");
  gtk_widget_set_halign(full_payment_discount_label, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), full_payment_discount_label, 0, 1, 1, 1);

  GtkWidget *full_payment_discount_entry = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), full_payment_discount_entry, 1, 1, 1, 1);

  // 裸车发票价
  GtkWidget *naked_car_invoice_price_label = gtk_label_new("裸车发票价：");
  gtk_widget_set_halign(naked_car_invoice_price_label, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), naked_car_invoice_price_label, 0, 2, 1, 1);

  GtkWidget *naked_car_invoice_price_entry = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), naked_car_invoice_price_entry, 1, 2, 1, 1);

  // 上牌
  GtkWidget *on_the_cards_label = gtk_label_new("上牌与转让待出口：");
  gtk_widget_set_halign(on_the_cards_label, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), on_the_cards_label, 0, 3, 1, 1);

  GtkWidget *on_the_cards_entry = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), on_the_cards_entry, 1, 3, 1, 1);

  // 交强险
  GtkWidget *compulsory_traffic_insurance_label = gtk_label_new("交强险：");
  gtk_widget_set_halign(compulsory_traffic_insurance_label, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), compulsory_traffic_insurance_label, 0, 4, 1, 1);

  GtkWidget *compulsory_traffic_insurance_entry = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), compulsory_traffic_insurance_entry, 1, 4, 1, 1);

  // 国内运费
  GtkWidget *domestic_shipping_label = gtk_label_new("国内运费：");
  gtk_widget_set_halign(domestic_shipping_label, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), domestic_shipping_label, 0, 5, 1, 1);

  GtkWidget *domestic_shipping_entry = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), domestic_shipping_entry, 1, 5, 1, 1);

  // 报关
  GtkWidget *customs_clearance_label = gtk_label_new("报关：");
  gtk_widget_set_halign(customs_clearance_label, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), customs_clearance_label, 0, 6, 1, 1);

  GtkWidget *customs_clearance_entry = gtk_entry_new();
  gtk_grid_attach(GTK_GRID(grid), customs_clearance_entry, 1, 6, 1, 1);

  // 购置税
  GtkWidget *purchase_tax_label = gtk_label_new("购置税：");
  gtk_widget_set_halign(purchase_tax_label, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), purchase_tax_label, 0, 7, 1, 1);

  GtkWidget *purchase_tax_entry = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(purchase_tax_entry), FALSE);
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(purchase_tax_entry), GTK_ENTRY_ICON_SECONDARY, "media-playback-start");
  gtk_entry_set_placeholder_text(GTK_ENTRY(purchase_tax_entry), "输入裸车发票价后点击按钮生成");
  g_signal_connect(purchase_tax_entry, "icon_press", G_CALLBACK(on_calculate_purchase_tax_for_fuel_vehicle), naked_car_invoice_price_entry);
  gtk_grid_attach(GTK_GRID(grid), purchase_tax_entry, 1, 7, 1, 1);

  // 退税金额
  GtkWidget *tax_refund_amount_label = gtk_label_new("退税金额：");
  gtk_widget_set_halign(tax_refund_amount_label, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), tax_refund_amount_label, 0, 8, 1, 1);

  GtkWidget *tax_refund_amount_entry = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(tax_refund_amount_entry), FALSE);
  gtk_entry_set_icon_from_icon_name(GTK_ENTRY(tax_refund_amount_entry), GTK_ENTRY_ICON_SECONDARY, "media-playback-start");
  gtk_entry_set_placeholder_text(GTK_ENTRY(tax_refund_amount_entry), "输入裸车发票价后点击按钮生成");
  g_signal_connect(tax_refund_amount_entry, "icon_press", G_CALLBACK(on_calculate_tax_refund_amount_for_fuel_vehicle), naked_car_invoice_price_entry);
  gtk_grid_attach(GTK_GRID(grid), tax_refund_amount_entry, 1, 8, 1, 1);

  // 计算按钮
  GtkWidget *calculate_button = gtk_button_new_with_label("计算");
  gtk_grid_attach(GTK_GRID(grid), calculate_button, 0, 9, 2, 1);

  g_signal_connect(calculate_button, "clicked", G_CALLBACK(on_calculate_quote_for_fuel_vehicle), grid);

  // 报价
  GtkWidget *quote_label = gtk_label_new("报价：");
  gtk_widget_set_halign(quote_label, GTK_ALIGN_END);
  gtk_grid_attach(GTK_GRID(grid), quote_label, 0, 10, 1, 1);

  GtkWidget *quote_entry = gtk_entry_new();
  gtk_editable_set_editable(GTK_EDITABLE(quote_entry), FALSE);
  // gtk_widget_set_can_focus(quote_entry, FALSE);
  gtk_grid_attach(GTK_GRID(grid), quote_entry, 1, 10, 1, 1);

  gtk_widget_set_size_request(gtk_grid_get_child_at(GTK_GRID(grid), 0, 0), 80, -1);
  gtk_widget_set_size_request(gtk_grid_get_child_at(GTK_GRID(grid), 1, 0), 300, -1);

  gtk_center_box_set_center_widget(GTK_CENTER_BOX(box), grid);

  return box;
}