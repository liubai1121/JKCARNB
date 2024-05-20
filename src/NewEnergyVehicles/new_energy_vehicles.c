#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "gtkutil.h"
#include "stringformatutil.h"
#include "calculatecarpriceutil.h"

#define PURCHASE_TAX_EXEMPTION_AMOUNT 30000.00

#define NEW_CAR_GUIDE_PRICE_ROW 0          // "新车指导价
#define FULL_PAYMENT_DISCOUNT_ROW 1        // 全款优惠
#define NAKED_CAR_INVOICE_PRICE_ROW 2      // 裸车发票价
#define ON_THE_CARDS_ROW 3                 // 上牌与转让待出口
#define COMPULSORY_TRAFFIC_INSURANCE_ROW 4 // 交强险
#define DOMESTIC_SHIPPING_ROW 5            // 国内运费
#define CUSTOMS_CLEARANCE_ROW 6            // 报关
#define PURCHASE_TAX_ROW 7                 // 购置税
#define TAX_REFUND_AMOUNT_ROW 8            // 退税金额
#define ACTUAL_DELIVERY_TIME_ROW 9         // 实际交付时间
#define ACTUAL_VEHICLE_AGE_ROW 10          // 实际车龄
#define SETTLEMENT_CURRENCY_ROW 11         // 结算币种
#define CALCULATE_ROW 12                   // 计算按钮
#define QUOTE_ROW 13                       // 报价

void on_calculate_tax_refund_amount_for_new_energy_vehicles(GtkWidget *tax_refund_amount_entry, GtkEntryIconPosition icon_pos, GtkWidget *naked_car_invoice_price_entry)
{
    double naked_car_invoice_price = get_entry_value(naked_car_invoice_price_entry);
    double tax_refund_amount_d = calculate_tax_refund_amount(naked_car_invoice_price);

    char tax_refund_amount_s[20];
    to_str_double(tax_refund_amount_s, tax_refund_amount_d);

    GtkEntryBuffer *buffer = gtk_entry_buffer_new(tax_refund_amount_s, -1);
    gtk_entry_set_buffer(GTK_ENTRY(tax_refund_amount_entry), buffer);
}

void on_calculate_purchase_tax_for_new_energy_vehicles(GtkWidget *purchase_tax_entry, GtkEntryIconPosition icon_pos, GtkWidget *naked_car_invoice_price_entry)
{
    double naked_car_invoice_price = get_entry_value(naked_car_invoice_price_entry);
    double purchase_tax_d = calculate_purchase_tax(naked_car_invoice_price);

    if (purchase_tax_d <= PURCHASE_TAX_EXEMPTION_AMOUNT)
    {
        purchase_tax_d = 0.0;
    }

    char purchase_tax_s[20];
    sprintf(purchase_tax_s, "%.2f", purchase_tax_d);

    const char *c_purchase_tax_s = purchase_tax_s;
    GtkEntryBuffer *buffer = gtk_entry_buffer_new(c_purchase_tax_s, -1);
    gtk_entry_set_buffer(GTK_ENTRY(purchase_tax_entry), buffer);
}

void on_calculate_quote_for_new_energy_vehicles(GtkWidget *button, GtkWidget *fuel_vehicle_grid)
{

    GtkWidget *naked_car_invoice_price_entry;
    GtkWidget *purchase_tax_entry;
    GtkWidget *tax_refund_amount_entry;

    double new_car_guide_price = get_grid_entry_value(fuel_vehicle_grid, 1, NEW_CAR_GUIDE_PRICE_ROW);     // "新车指导价
    double full_payment_discount = get_grid_entry_value(fuel_vehicle_grid, 1, FULL_PAYMENT_DISCOUNT_ROW); // 全款优惠
    naked_car_invoice_price_entry = gtk_grid_get_child_at(GTK_GRID(fuel_vehicle_grid), 1, NAKED_CAR_INVOICE_PRICE_ROW);
    double naked_car_invoice_price = get_entry_value(naked_car_invoice_price_entry);                                    // 裸车发票价
    double on_the_cards = get_grid_entry_value(fuel_vehicle_grid, 1, ON_THE_CARDS_ROW);                                 // 上牌
    double compulsory_traffic_insurance = get_grid_entry_value(fuel_vehicle_grid, 1, COMPULSORY_TRAFFIC_INSURANCE_ROW); // 交强险
    double domestic_shipping = get_grid_entry_value(fuel_vehicle_grid, 1, DOMESTIC_SHIPPING_ROW);                       // 国内运费
    double customs_clearance = get_grid_entry_value(fuel_vehicle_grid, 1, CUSTOMS_CLEARANCE_ROW);                       // 报关

    purchase_tax_entry = gtk_grid_get_child_at(GTK_GRID(fuel_vehicle_grid), 1, PURCHASE_TAX_ROW);
    on_calculate_purchase_tax_for_new_energy_vehicles(purchase_tax_entry, GTK_ENTRY_ICON_SECONDARY, naked_car_invoice_price_entry);
    double purchase_tax = get_entry_value(purchase_tax_entry); // 购置税

    tax_refund_amount_entry = gtk_grid_get_child_at(GTK_GRID(fuel_vehicle_grid), 1, TAX_REFUND_AMOUNT_ROW);
    on_calculate_tax_refund_amount_for_new_energy_vehicles(tax_refund_amount_entry, GTK_ENTRY_ICON_SECONDARY, naked_car_invoice_price_entry);
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

    // const char *c_quote_s = quote_s;

    GtkEntryBuffer *buffer = gtk_entry_buffer_new(quote_s, -1);
    GtkWidget *quote_entry = gtk_grid_get_child_at(GTK_GRID(fuel_vehicle_grid), 1, QUOTE_ROW); // 报价
    gtk_entry_set_buffer(GTK_ENTRY(quote_entry), buffer);
}

GtkWidget *get_new_energy_vehicles_page()
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
    gtk_grid_attach(GTK_GRID(grid), new_car_guide_price_label, 0, NEW_CAR_GUIDE_PRICE_ROW, 1, 1);

    GtkWidget *new_car_guide_price_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), new_car_guide_price_entry, 1, NEW_CAR_GUIDE_PRICE_ROW, 1, 1);

    // 全款优惠
    GtkWidget *full_payment_discount_label = gtk_label_new("全款优惠 *：");
    gtk_widget_set_halign(full_payment_discount_label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), full_payment_discount_label, 0, FULL_PAYMENT_DISCOUNT_ROW, 1, 1);

    GtkWidget *full_payment_discount_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), full_payment_discount_entry, 1, FULL_PAYMENT_DISCOUNT_ROW, 1, 1);

    // 裸车发票价
    GtkWidget *naked_car_invoice_price_label = gtk_label_new("裸车发票价：");
    gtk_widget_set_halign(naked_car_invoice_price_label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), naked_car_invoice_price_label, 0, NAKED_CAR_INVOICE_PRICE_ROW, 1, 1);

    GtkWidget *naked_car_invoice_price_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), naked_car_invoice_price_entry, 1, NAKED_CAR_INVOICE_PRICE_ROW, 1, 1);

    // 上牌
    GtkWidget *on_the_cards_label = gtk_label_new("上牌与转让待出口：");
    gtk_widget_set_halign(on_the_cards_label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), on_the_cards_label, 0, ON_THE_CARDS_ROW, 1, 1);

    GtkWidget *on_the_cards_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), on_the_cards_entry, 1, ON_THE_CARDS_ROW, 1, 1);

    // 交强险
    GtkWidget *compulsory_traffic_insurance_label = gtk_label_new("交强险：");
    gtk_widget_set_halign(compulsory_traffic_insurance_label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), compulsory_traffic_insurance_label, 0, COMPULSORY_TRAFFIC_INSURANCE_ROW, 1, 1);

    GtkWidget *compulsory_traffic_insurance_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), compulsory_traffic_insurance_entry, 1, COMPULSORY_TRAFFIC_INSURANCE_ROW, 1, 1);

    // 国内运费
    GtkWidget *domestic_shipping_label = gtk_label_new("国内运费：");
    gtk_widget_set_halign(domestic_shipping_label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), domestic_shipping_label, 0, DOMESTIC_SHIPPING_ROW, 1, 1);

    GtkWidget *domestic_shipping_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), domestic_shipping_entry, 1, DOMESTIC_SHIPPING_ROW, 1, 1);

    // 报关
    GtkWidget *customs_clearance_label = gtk_label_new("报关：");
    gtk_widget_set_halign(customs_clearance_label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), customs_clearance_label, 0, CUSTOMS_CLEARANCE_ROW, 1, 1);

    GtkWidget *customs_clearance_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), customs_clearance_entry, 1, CUSTOMS_CLEARANCE_ROW, 1, 1);

    // 购置税
    GtkWidget *purchase_tax_label = gtk_label_new("购置税：");
    gtk_widget_set_halign(purchase_tax_label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), purchase_tax_label, 0, PURCHASE_TAX_ROW, 1, 1);

    GtkWidget *purchase_tax_entry = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(purchase_tax_entry), FALSE);
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(purchase_tax_entry), GTK_ENTRY_ICON_SECONDARY, "media-playback-start");
    gtk_entry_set_placeholder_text(GTK_ENTRY(purchase_tax_entry), "输入裸车发票价后点击按钮生成");
    g_signal_connect(purchase_tax_entry, "icon_press", G_CALLBACK(on_calculate_purchase_tax_for_new_energy_vehicles), naked_car_invoice_price_entry);
    gtk_grid_attach(GTK_GRID(grid), purchase_tax_entry, 1, PURCHASE_TAX_ROW, 1, 1);

    // 退税金额
    GtkWidget *tax_refund_amount_label = gtk_label_new("退税金额：");
    gtk_widget_set_halign(tax_refund_amount_label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), tax_refund_amount_label, 0, TAX_REFUND_AMOUNT_ROW, 1, 1);

    GtkWidget *tax_refund_amount_entry = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(tax_refund_amount_entry), FALSE);
    gtk_entry_set_icon_from_icon_name(GTK_ENTRY(tax_refund_amount_entry), GTK_ENTRY_ICON_SECONDARY, "media-playback-start");
    gtk_entry_set_placeholder_text(GTK_ENTRY(tax_refund_amount_entry), "输入裸车发票价后点击按钮生成");
    g_signal_connect(tax_refund_amount_entry, "icon_press", G_CALLBACK(on_calculate_tax_refund_amount_for_new_energy_vehicles), naked_car_invoice_price_entry);
    gtk_grid_attach(GTK_GRID(grid), tax_refund_amount_entry, 1, TAX_REFUND_AMOUNT_ROW, 1, 1);

    // 实际交付时间
    GtkWidget *actual_delivery_time_label = gtk_label_new("实际交付时间：");
    gtk_widget_set_halign(actual_delivery_time_label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), actual_delivery_time_label, 0, ACTUAL_DELIVERY_TIME_ROW, 1, 1);

    GtkWidget *actual_delivery_time_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), actual_delivery_time_entry, 1, ACTUAL_DELIVERY_TIME_ROW, 1, 1);

    // 实际车龄
    GtkWidget *actual_vehicle_age_label = gtk_label_new("实际车龄：");
    gtk_widget_set_halign(actual_vehicle_age_label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), actual_vehicle_age_label, 0, ACTUAL_VEHICLE_AGE_ROW, 1, 1);

    int year_range = 7;
    GtkWidget *actual_vehicle_age_box = get_years_months_box(year_range);
    gtk_grid_attach(GTK_GRID(grid), actual_vehicle_age_box, 1, ACTUAL_VEHICLE_AGE_ROW, 1, 1);

    // 结算币种
    GtkWidget *settlement_currency_label = gtk_label_new("结算币种：");
    gtk_widget_set_halign(settlement_currency_label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), settlement_currency_label, 0, SETTLEMENT_CURRENCY_ROW, 1, 1);

    GtkWidget *settlement_currency_drop_down = get_settlement_currency_drop_down();
    gtk_grid_attach(GTK_GRID(grid), settlement_currency_drop_down, 1, SETTLEMENT_CURRENCY_ROW, 1, 1);

    // 计算按钮
    GtkWidget *calculate_button = gtk_button_new_with_label("计算");
    gtk_grid_attach(GTK_GRID(grid), calculate_button, 0, CALCULATE_ROW, 2, 1);

    g_signal_connect(calculate_button, "clicked", G_CALLBACK(on_calculate_quote_for_new_energy_vehicles), grid);

    // 报价
    GtkWidget *quote_label = gtk_label_new("报价：");
    gtk_widget_set_halign(quote_label, GTK_ALIGN_END);
    gtk_grid_attach(GTK_GRID(grid), quote_label, 0, QUOTE_ROW, 1, 1);

    GtkWidget *quote_entry = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(quote_entry), FALSE);
    // gtk_widget_set_can_focus(quote_entry, FALSE);
    gtk_grid_attach(GTK_GRID(grid), quote_entry, 1, QUOTE_ROW, 1, 1);

    gtk_widget_set_size_request(gtk_grid_get_child_at(GTK_GRID(grid), 0, 0), 80, -1);
    gtk_widget_set_size_request(gtk_grid_get_child_at(GTK_GRID(grid), 1, 0), 300, -1);

    gtk_center_box_set_center_widget(GTK_CENTER_BOX(box), grid);

    return box;
}