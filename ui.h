#pragma once
#ifndef UI_H
#define UI_H

// 主菜单(finish)
void show_main_menu();
void handle_main_menu_choice(int choice);

// 乘客菜单(finish)
void show_passenger_menu();
void handle_passenger_choice(int choice);

// 司机菜单
void show_driver_menu();
void handle_driver_choice(int choice);

// 注册菜单
void show_register_menu(); 

// 登录功能
void login_user();
void logout_user();

// 乘客功能界面
void show_call_taxi_ui();
void show_my_orders_ui();
void show_my_info_ui();
void show_cancel_order_ui();
void show_payment_ui();
void show_recharge_ui();

// 司机功能界面
void show_toggle_online_ui();
void show_available_orders_ui();
void show_my_current_order_ui();
void show_complete_order_ui();
void show_register_vehicle_ui();

// 通用界面(finish)
void show_header(const char* title);
void show_separator();

#endif