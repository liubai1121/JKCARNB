#define TAX_REBATE_AMOUNT_FACTOR 0.115
#define PURCHASE_TAX_FACTOR 11.3

struct VEHICLE_PRICE {
    double new_car_guide_price;
    double full_payment_discount;
    double naked_car_invoice_price;
    double on_the_cards;
    double compulsory_traffic_insurance;
    double domestic_shipping;
    double customs_clearance;
    double purchase_tax;
    double tax_refund_amount;
};

double calculate_tax_refund_amount(double naked_car_invoice_price);
double calculate_purchase_tax(double naked_car_invoice_price);
double calculate_quote(struct VEHICLE_PRICE *vehiche_price);


