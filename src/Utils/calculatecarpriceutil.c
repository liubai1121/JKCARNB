#include <mpfr.h>
#include "calculatecarpriceutil.h"

double calculate_purchase_tax(double naked_car_invoice_price)
{
    mpfr_t purchase_tax;
    mpfr_init(purchase_tax);
    mpfr_set_d(purchase_tax, naked_car_invoice_price, MPFR_RNDU);
    mpfr_div_d(purchase_tax, purchase_tax, PURCHASE_TAX_FACTOR, MPFR_RNDU);

    double purchase_tax_d = mpfr_get_d(purchase_tax, MPFR_RNDU);
    mpfr_clear(purchase_tax);
    return purchase_tax_d;
}

double calculate_tax_refund_amount(double naked_car_invoice_price)
{
    mpfr_t tax_refund_amount;
    mpfr_init(tax_refund_amount);
    mpfr_set_d(tax_refund_amount, naked_car_invoice_price, MPFR_RNDU);
    mpfr_mul_d(tax_refund_amount, tax_refund_amount, TAX_REBATE_AMOUNT_FACTOR, MPFR_RNDU);

    double tax_refund_amount_d = mpfr_get_d(tax_refund_amount, MPFR_RNDU);
    mpfr_clear(tax_refund_amount);
    return tax_refund_amount_d;
}

double calculate_quote(struct VEHICLE_PRICE *vehiche_price)
{
    mpfr_t quote;
    mpfr_init(quote);
    mpfr_set_d(quote, 0.00, MPFR_RNDU);
    mpfr_add_d(quote, quote, vehiche_price->new_car_guide_price, MPFR_RNDU);
    mpfr_add_d(quote, quote, vehiche_price->full_payment_discount, MPFR_RNDU);
    mpfr_add_d(quote, quote, vehiche_price->naked_car_invoice_price, MPFR_RNDU);
    mpfr_add_d(quote, quote, vehiche_price->on_the_cards, MPFR_RNDU);
    mpfr_add_d(quote, quote, vehiche_price->compulsory_traffic_insurance, MPFR_RNDU);
    mpfr_add_d(quote, quote, vehiche_price->domestic_shipping, MPFR_RNDU);
    mpfr_add_d(quote, quote, vehiche_price->customs_clearance, MPFR_RNDU);
    mpfr_add_d(quote, quote, vehiche_price->purchase_tax, MPFR_RNDU);
    mpfr_add_d(quote, quote, vehiche_price->tax_refund_amount, MPFR_RNDU);
    double quote_d = mpfr_get_d(quote, MPFR_RNDU);

    mpfr_clear(quote);
    return quote_d;
}