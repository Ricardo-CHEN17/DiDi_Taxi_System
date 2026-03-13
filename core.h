#pragma once
#ifndef CORE_H
#define CORE_H

#include "data.h"

// 乘客功能
Order create_order(int passenger_id, const char* start, const char* end);
int cancel_order(int order_id, int passenger_id);


// 司机功能
int accept_order(int order_id, int driver_id);
int complete_order(int order_id, int driver_id);

// 支付功能
int make_payment(int order_id);
int recharge_balance(int user_id, float amount);
float calculate_price(float distance, int car_type);

// 搜索功能
void show_user_orders(int user_id, int user_type);
#endif