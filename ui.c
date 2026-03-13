#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include "utils.h"
#include "data.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//通用界面
void show_header(const char* title) {
    system("cls");  // 清屏（Windows）
    printf("========================================\n");
    printf("         滴滴打车系统 - %s\n", title);
    printf("========================================\n");
}

void show_separator() {
    printf("----------------------------------------\n");
}

// 主菜单
void show_main_menu() {
    show_header("主菜单");
    printf("1. 乘客登录\n");
    printf("2. 司机登录\n");
    printf("3. 注册\n");
    printf("4. 退出系统\n");
    show_separator();

    int choice = get_int_input("请选择操作 (1-4): ", 1, 4);
    handle_main_menu_choice(choice);
}

void handle_main_menu_choice(int choice) {
    switch (choice) {
    case 1:
    case 2:
        login_user();
        break;
    case 3:
        show_register_menu();
        break;
    case 4:
        printf("感谢使用滴滴打车系统，再见！\n");
        save_all_data();  // 退出前保存数据
        exit(0);
        break;
    }
}

//乘客菜单
void show_passenger_menu() {
    show_header("乘客功能菜单");
    printf("1. 我要打车\n");
    printf("2. 查看我的订单\n");
    printf("3. 个人信息\n");
    printf("4. 取消订单\n");
    printf("5. 支付订单\n");
    printf("6. 账户充值\n");
    printf("7. 退出登录\n");
    printf("8. 返回主菜单\n");
    show_separator();

    int choice = get_int_input("请选择操作 (1-8): ", 1, 8);
    handle_passenger_choice(choice);
}

void handle_passenger_choice(int choice) {
    switch (choice) {
    case 1:
        show_call_taxi_ui();
        break;
    case 2:
        show_my_orders_ui();
        break;
    case 3:
        show_my_info_ui();
        break;
    case 4:
        show_cancel_order_ui();
        break;
    case 5:
        show_payment_ui();
        break;
    case 6:
        show_recharge_ui();
        break;
    case 7:
        logout_user();
        break;
    case 8:
        show_main_menu();
        break;
    }
}

// 司机菜单
void show_driver_menu() {
    show_header("司机功能菜单");
    printf("1. 上线/下线\n");
    printf("2. 查看可接订单\n");
    printf("3. 我的当前订单\n");
    printf("4. 完成订单\n");
    printf("5. 注册车辆\n");
    printf("6. 个人信息\n");
    printf("7. 退出登录\n");
    printf("8. 返回主菜单\n");
    show_separator();

    int choice = get_int_input("请选择操作 (1-8): ", 1, 8);
    handle_driver_choice(choice);
}

void handle_driver_choice(int choice) {
    switch (choice) {
    case 1:
        show_toggle_online_ui();
        break;
    case 2:
        show_available_orders_ui();
        break;
    case 3:
        show_my_current_order_ui();
        break;
    case 4:
        show_complete_order_ui();
        break;
    case 5:
        show_register_vehicle_ui();
        break;
    case 6:
        show_my_info_ui();
        break;
    case 7:
        logout_user();
        break;
    case 8:
        show_main_menu();
        break;
    }
}

//乘客功能界面
void show_call_taxi_ui() {
    show_header("叫车服务");

    if (current_user.balance < 10.0) {
        printf("警告：您的余额较低 (%.2f元)，建议先充值！\n", current_user.balance);
        show_separator();
    }

    char start[50], end[50];

    get_string_input(start, 50, "请输入起点: ");
    get_string_input(end, 50, "请输入终点: ");

    Order new_order = create_order(current_user.id, start, end);

    printf("\n======= 行程信息 =======\n");
    printf("起点：%s\n", new_order.start_location);
    printf("终点：%s\n", new_order.end_location);
    printf("预估距离：%.1f公里\n", new_order.distance);
    printf("预估价格：%.2f元\n", new_order.price);
    printf("当前余额：%.2f元\n", current_user.balance);
    show_separator();

    int confirm = get_int_input("确认叫车？ (1:确认, 0:取消): ", 0, 1);

    if (confirm) {
        if (add_order(new_order)) {
            printf("\n正在为您寻找附近司机...\n");
            printf("订单已创建，请耐心等待司机接单！\n");
        }
    }
    else {
        printf("已取消叫车。\n");
    }

    pause_program();
    show_passenger_menu();
}

void show_my_orders_ui() {
    show_header("我的订单");
    show_user_orders(current_user.id, current_user.type);
    pause_program();
    show_passenger_menu();
}

void show_my_info_ui() {
    show_header("个人信息");

    printf("用户ID: %d\n", current_user.id);
    printf("用户名: %s\n", current_user.username);
    printf("手机号: %s\n", current_user.phone);
    printf("用户类型: %s\n", get_user_type_name(current_user.type));
    printf("账户余额: %.2f元\n", current_user.balance);
    printf("在线状态: %s\n", current_user.status == STATUS_ONLINE ? "在线" : "离线");

    // 如果是司机，显示车辆信息
    if (current_user.type == USER_DRIVER) {
        Vehicle* vehicle = find_vehicle_by_driver(current_user.id);
        if (vehicle) {
            printf("\n车辆信息：\n");
            printf("车牌号: %s\n", vehicle->plate_number);
            printf("车型: %s\n", vehicle->type);
            printf("座位数: %d\n", vehicle->seats);
        }
        else {
            printf("\n尚未注册车辆！\n");
        }
    }

    show_separator();
    pause_program();

    if (current_user.type == USER_PASSENGER) {
        show_passenger_menu();
    }
    else {
        show_driver_menu();
    }
}

void show_cancel_order_ui() {
    show_header("取消订单");

    // 查找用户的待处理订单
    Order* order = find_order_by_passenger(current_user.id);

    if (order == NULL) {
        printf("您没有待处理的订单！\n");
        pause_program();
        show_passenger_menu();
        return;
    }

    printf("当前订单信息：\n");
    printf("订单号: %d\n", order->id);
    printf("起点: %s\n", order->start_location);
    printf("终点: %s\n", order->end_location);
    printf("状态: %s\n", get_order_status_name(order->status));
    printf("价格: %.2f元\n", order->price);
    show_separator();

    int confirm = get_int_input("确认取消此订单？ (1:确认, 0:取消): ", 0, 1);

    if (confirm) {
        if (cancel_order(order->id, current_user.id)) {
            printf("订单已取消！\n");
        }
    }
    else {
        printf("取消操作已中止。\n");
    }

    pause_program();
    show_passenger_menu();
}

void show_payment_ui() {
    show_header("支付订单");

    Order* order = find_order_by_passenger(current_user.id);

    if (order == NULL) {
        printf("您没有待支付的订单！\n");
        pause_program();
        show_passenger_menu();
        return;
    }

    if (order->status != ORDER_ONGOING) {
        printf("此订单当前无法支付！\n");
        printf("订单状态: %s\n", get_order_status_name(order->status));
        pause_program();
        show_passenger_menu();
        return;
    }

    printf("待支付订单信息：\n");
    printf("订单号: %d\n", order->id);
    printf("起点: %s\n", order->start_location);
    printf("终点: %s\n", order->end_location);
    printf("距离: %.1f公里\n", order->distance);
    printf("支付金额: %.2f元\n", order->price);
    printf("您的余额: %.2f元\n", current_user.balance);
    show_separator();

    int confirm = get_int_input("确认支付？ (1:确认, 0:取消): ", 0, 1);

    if (confirm) {
        if (make_payment(order->id)) {
            printf("支付成功！\n");
            // 更新当前用户信息
            for (int i = 0; i < user_count; i++) {
                if (users[i].id == current_user.id) {
                    current_user = users[i];
                    break;
                }
            }
        }
    }
    else {
        printf("支付已取消。\n");
    }

    pause_program();
    show_passenger_menu();
}

void show_recharge_ui() {
    show_header("账户充值");

    printf("当前余额: %.2f元\n", current_user.balance);
    printf("\n充值金额选项：\n");
    printf("1. 50元\n");
    printf("2. 100元\n");
    printf("3. 200元\n");
    printf("4. 500元\n");
    printf("5. 其他金额\n");
    show_separator();

    int choice = get_int_input("请选择充值金额 (1-5): ", 1, 5);
    float amount = 0;

    switch (choice) {
    case 1: amount = 50.0; break;
    case 2: amount = 100.0; break;
    case 3: amount = 200.0; break;
    case 4: amount = 500.0; break;
    case 5:
        while (1) {
            printf("请输入充值金额: ");
            if (scanf("%f", &amount) != 1) {
                clear_input_buffer();
                printf("输入无效！请输入数字。\n");
                continue;
            }
            clear_input_buffer();
            if (amount <= 0) {
                printf("充值金额必须大于0！\n");
                continue;
            }
            break;
        }
        break;
    }

    int confirm = get_int_input("确认充值？ (1:确认, 0:取消): ", 0, 1);

    if (confirm) {
        if (recharge_balance(current_user.id, amount)) {
            printf("充值成功！\n");
            // 更新当前用户信息
            for (int i = 0; i < user_count; i++) {
                if (users[i].id == current_user.id) {
                    current_user = users[i];
                    break;
                }
            }
        }
    }
    else {
        printf("充值已取消。\n");
    }

    pause_program();
    show_passenger_menu();
}

// 司机功能界面
void show_toggle_online_ui() {
    show_header("上线/下线");

    if (current_user.status == STATUS_ONLINE) {
        printf("当前状态: 在线\n");
        printf("切换为离线状态将不再接收新订单。\n");
        show_separator();

        int confirm = get_int_input("确认下线？ (1:确认, 0:取消): ", 0, 1);

        if (confirm) {
            current_user.status = STATUS_OFFLINE;
            update_user(current_user);
            printf("已下线！\n");
        }
    }
    else {
        printf("当前状态: 离线\n");

        // 检查是否有车辆
        Vehicle* vehicle = find_vehicle_by_driver(current_user.id);
        if (vehicle == NULL) {
            printf("警告：您尚未注册车辆，无法上线接单！\n");
            printf("请先注册车辆。\n");
            pause_program();
            show_driver_menu();
            return;
        }

        printf("切换为在线状态后可以接收订单。\n");
        show_separator();

        int confirm = get_int_input("确认上线？ (1:确认, 0:取消): ", 0, 1);

        if (confirm) {
            current_user.status = STATUS_ONLINE;
            update_user(current_user);
            printf("已上线！可以开始接单了。\n");
        }
    }

    pause_program();
    show_driver_menu();
}

void show_available_orders_ui() {
    show_header("可接订单");

    if (current_user.status != STATUS_ONLINE) {
        printf("您当前处于离线状态，请先上线！\n");
        pause_program();
        show_driver_menu();
        return;
    }

    int count = 0;
    Order* available_orders = find_available_orders(&count);

    if (count == 0) {
        printf("暂无待接订单。\n");
        pause_program();
        show_driver_menu();
        return;
    }

    printf("共有 %d 个待接订单：\n", count);
    show_separator();

    for (int i = 0; i < count; i++) {
        printf("订单号: %d\n", available_orders[i].id);
        printf("起点: %s\n", available_orders[i].start_location);
        printf("终点: %s\n", available_orders[i].end_location);
        printf("距离: %.1f公里\n", available_orders[i].distance);
        printf("价格: %.2f元\n", available_orders[i].price);
        printf("创建时间: %s\n", available_orders[i].create_time);
        show_separator();
    }

    int order_id = get_int_input("请输入要接的订单号 (0:返回): ", 0, 9999);

    if (order_id > 0) {
        if (accept_order(order_id, current_user.id)) {
            printf("接单成功！请前往乘客起点。\n");
        }
    }

    pause_program();
    show_driver_menu();
}

void show_my_current_order_ui() {
    show_header("当前订单");

    Order* order = find_order_by_driver(current_user.id);

    if (order == NULL) {
        printf("您当前没有进行中的订单。\n");
    }
    else {
        printf("当前订单信息：\n");
        printf("订单号: %d\n", order->id);
        printf("起点: %s\n", order->start_location);
        printf("终点: %s\n", order->end_location);
        printf("距离: %.1f公里\n", order->distance);
        printf("价格: %.2f元\n", order->price);
        printf("状态: %s\n", get_order_status_name(order->status));
        printf("创建时间: %s\n", order->create_time);

        if (order->status == ORDER_ACCEPTED) {
            printf("\n提示：请前往起点接乘客，接到后可在'完成订单'中确认。\n");
        }
    }

    pause_program();
    show_driver_menu();
}

void show_complete_order_ui() {
    show_header("完成订单");

    Order* order = find_order_by_driver(current_user.id);

    if (order == NULL) {
        printf("您当前没有进行中的订单。\n");
        pause_program();
        show_driver_menu();
        return;
    }

    if (order->status != ORDER_ACCEPTED && order->status != ORDER_ONGOING) {
        printf("当前订单无法完成！\n");
        printf("订单状态: %s\n", get_order_status_name(order->status));
        pause_program();
        show_driver_menu();
        return;
    }

    printf("订单信息：\n");
    printf("订单号: %d\n", order->id);
    printf("起点: %s\n", order->start_location);
    printf("终点: %s\n", order->end_location);
    printf("距离: %.1f公里\n", order->distance);
    printf("价格: %.2f元\n", order->price);
    show_separator();

    int confirm = get_int_input("确认已完成此订单？ (1:确认, 0:取消): ", 0, 1);

    if (confirm) {
        if (complete_order(order->id, current_user.id)) {
            printf("订单已完成！请等待乘客支付。\n");
        }
    }
    else {
        printf("操作已取消。\n");
    }

    pause_program();
    show_driver_menu();
}

void show_register_vehicle_ui() {
    show_header("注册车辆");

    // 检查是否已注册车辆
    Vehicle* existing = find_vehicle_by_driver(current_user.id);
    if (existing != NULL) {
        printf("您已注册过车辆：\n");
        printf("车牌号: %s\n", existing->plate_number);
        printf("车型: %s\n", existing->type);
        printf("座位数: %d\n", existing->seats);
        printf("\n提示：如需修改车辆信息，请联系管理员。\n");
        pause_program();
        show_driver_menu();
        return;
    }

    Vehicle new_vehicle;
    new_vehicle.driver_id = current_user.id;

    get_string_input(new_vehicle.plate_number, 10, "请输入车牌号: ");

    printf("请选择车型：\n");
    printf("1. 普通车型\n");
    printf("2. 豪华车型\n");
    int type_choice = get_int_input("请选择 (1-2): ", 1, 2);

    if (type_choice == 1) {
        strcpy(new_vehicle.type, "普通车型");
    }
    else {
        strcpy(new_vehicle.type, "豪华车型");
    }

    new_vehicle.seats = get_int_input("请输入座位数 (4-7): ", 4, 7);

    printf("\n车辆信息确认：\n");
    printf("车牌号: %s\n", new_vehicle.plate_number);
    printf("车型: %s\n", new_vehicle.type);
    printf("座位数: %d\n", new_vehicle.seats);
    show_separator();

    int confirm = get_int_input("确认注册此车辆？ (1:确认, 0:取消): ", 0, 1);

    if (confirm) {
        if (add_vehicle(new_vehicle)) {
            printf("车辆注册成功！\n");
            printf("现在您可以上线接单了。\n");
        }
    }
    else {
        printf("车辆注册已取消。\n");
    }

    pause_program();
    show_driver_menu();
}

//登录功能
void login_user() {
    show_header("用户登录");

    char username[20], password[20];

    get_string_input(username, 20, "请输入用户名: ");
    get_string_input(password, 20, "请输入密码: ");

    User* user = find_user_by_username(username);

    if (user != NULL && strcmp(user->password, password) == 0) {
        current_user = *user;
        is_logged_in = 1;
        printf("登录成功！\n");

        if (user->type == USER_PASSENGER) {
            show_passenger_menu();
        }
        else {
            show_driver_menu();
        }
    }
    else {
        printf("登录失败！用户名或密码错误。\n");
        pause_program();
        show_main_menu();
    }
}

void logout_user() {
    is_logged_in = 0;
    pause_program();
    show_main_menu();
}

// 注册菜单
void show_register_menu() {
    show_header("注册菜单");
    User new_user;
    char phone[12];
    char confirm_password[20];

    // 选择用户类型
    printf("请选择注册类型：\n");
    printf("1. 乘客\n");
    printf("2. 司机\n");
    int type_choice = get_int_input("请选择 (1-2): ", 1, 2);
    new_user.type = (type_choice == 1) ? USER_PASSENGER : USER_DRIVER;

    //使用while(1)帮助乘客与司机完成相同信息填写，避免代码重复
    // 输入用户名
    while (1) {
        get_string_input(new_user.username, 20, "请输入用户名 (3-20位): ");
        if (strlen(new_user.username) < 3) {
            printf("用户名至少需要3位！\n");
            continue;
        }
        if (find_user_by_username(new_user.username) != NULL) {
            printf("用户名已存在！\n");
            continue;
        }
        break;
    }

    // 输入密码
    while (1) {
        get_string_input(new_user.password, 20, "请输入密码 (至少6位): ");
        if (!validate_password(new_user.password)) {
            continue;
        }

        get_string_input(confirm_password, 20, "请再次输入密码: ");
        if (strcmp(new_user.password, confirm_password) != 0) {
            printf("两次输入的密码不一致！\n");
            continue;
        }
        break;
    }

    // 输入手机号
    while (1) {
        get_string_input(new_user.phone, 12, "请输入手机号: ");
        if (!validate_phone(new_user.phone)) {
            continue;
        }
        if (find_user_by_phone(new_user.phone) != NULL) {
            printf("手机号已注册！\n");
            continue;
        }
        break;
    }

    // 设置初始值
    new_user.balance = 0.0;
    new_user.status = STATUS_OFFLINE;

    // 添加用户
    if (add_user(new_user)) {
        printf("\n注册成功！\n");
        printf("用户名: %s\n", new_user.username);
        printf("用户类型: %s\n", get_user_type_name(new_user.type));
        printf("请牢记您的登录信息！\n");

        // 如果是司机，提示注册车辆
        if (new_user.type == USER_DRIVER) {
            printf("\n提示：司机用户需要注册车辆后才能接单。\n");
        }
    }
    pause_program();
    show_main_menu();

}