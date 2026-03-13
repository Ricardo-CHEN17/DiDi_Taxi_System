#define _CRT_SECURE_NO_WARNINGS
#include "core.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Order create_order(int passenger_id, const char* start, const char* end) {
	Order new_order;

	new_order.passenger_id = passenger_id;
	new_order.driver_id = -1;//初始无司机

	strcpy(new_order.start_location, start);
	strcpy(new_order.end_location, end);

	// 模拟距离计算（实际应该根据坐标计算）
	new_order.distance = 5.0 + (rand() % 15);  // 5-20公里；rand()是<stdlib.h>标准库用于生成伪随机数

	// 计算价格（普通车型）
	new_order.price = calculate_price(new_order.distance, 0);

	new_order.status = ORDER_WAITING;

	// 生成时间(还未接单，部分时间先留空)
	generate_time_string(new_order.create_time);
	strcpy(new_order.accept_time, "");
	strcpy(new_order.complete_time, "");

	return new_order;
}

int cancel_order(int order_id, int passenger_id) {
	Order* order = find_order_by_id(order_id);

	if (order == NULL) {
		printf("订单不存在\n");
		return 0;
	}
	if (order->passenger_id != passenger_id) {
		printf("你无权取消此订单!\n");
		return 0;
	}
	if (order->status != ORDER_WAITING && order->status != ORDER_ACCEPTED) {
		printf("当前状态无法取消!\n");
		return 0;
	}
	
	order->status = ORDER_CANCELLED;
	printf("订单取消成功!");

	return 1;
}

// 计算价格
float calculate_price(float distance, int car_type) {
	float base_fare, per_km;

	if (car_type == 0) {  // 普通车型
		base_fare = 8.0;
		per_km = 2.5;
	}
	else {  // 豪华车型
		base_fare = 15.0;
		per_km = 4.0;
	}

	float price = base_fare + distance * per_km;

	return price;
}

// 接单
int accept_order(int order_id, int driver_id) {
	Order* order = find_order_by_id(order_id);

	if (order == NULL) {
		printf("订单不存在！\n");
		return 0;
	}

	if (order->status != ORDER_WAITING) {
		printf("该订单无法接单！\n");
		return 0;
	}

	// 检查司机是否有车辆
	Vehicle* vehicle = find_vehicle_by_driver(driver_id);
	if (vehicle == NULL) {
		printf("您还没有注册车辆，无法接单！\n");
		return 0;
	}
}
	// 完成订单
int complete_order(int order_id, int driver_id) {
		Order* order = find_order_by_id(order_id);

		if (order == NULL) {
			printf("订单不存在！\n");
			return 0;
		}

		if (order->driver_id != driver_id) {
			printf("无权完成此订单！\n");
			return 0;
		}

		if (order->status != ORDER_ACCEPTED && order->status != ORDER_ONGOING) {
			printf("当前状态无法完成订单！\n");
			return 0;
		}

		order->status = ORDER_ONGOING;
		generate_time_string(order->complete_time);
		printf("订单已完成！请等待乘客支付。\n");

		return 1;
}

	// 支付订单
int make_payment(int order_id) {
		Order* order = find_order_by_id(order_id);

		if (order == NULL) {
			printf("订单不存在！\n");
			return 0;
		}

		if (order->status != ORDER_ONGOING) {
			printf("订单状态错误，无法支付！\n");
			return 0;
		}

		// 查找乘客
		for (int i = 0; i < user_count; i++) {
			if (users[i].id == order->passenger_id) {
				// 检查余额
				if (users[i].balance < order->price) {
					printf("余额不足！当前余额：%.2f元，需要支付：%.2f元\n",
						users[i].balance, order->price);
					return 0;
				}

				// 乘客扣款
				users[i].balance -= order->price;

				// 给司机加钱（平台抽成20%）
				if (order->driver_id != -1) {
					for (int j = 0; j < user_count; j++) {
						if (users[j].id == order->driver_id) {
							users[j].balance += order->price * 0.8;
							printf("司机收入：%.2f元（平台抽成：%.2f元）\n",
								order->price * 0.8, order->price * 0.2);
							break;
						}
					}
				}

				order->status = ORDER_COMPLETED;
				printf("支付成功！支付金额：%.2f元\n", order->price);
				return 1;
			}
		}

		return 0;
}

	// 充值余额
int recharge_balance(int user_id, float amount) {
		if (amount <= 0) {
			printf("充值金额必须大于0！\n");
			return 0;
		}

		for (int i = 0; i < user_count; i++) {
			if (users[i].id == user_id) {
				users[i].balance += amount;
				printf("充值成功！当前余额：%.2f元\n", users[i].balance);
				return 1;
			}
		}

		return 0;
}

void show_user_orders(int user_id, int user_type) {
	printf("\n======= 我的订单 =======\n");

	int found = 0;
	for (int i = 0; i < order_count; i++) {
		if ((user_type == USER_PASSENGER && orders[i].passenger_id == user_id) ||
				(user_type == USER_DRIVER && orders[i].driver_id == user_id)) {

			printf("订单号: %d\n", orders[i].id);
			printf("起点: %s\n", orders[i].start_location);
			printf("终点: %s\n", orders[i].end_location);
			printf("距离: %.1f公里\n", orders[i].distance);
			printf("价格: %.2f元\n", orders[i].price);
			printf("状态: %s\n", get_order_status_name(orders[i].status));
			printf("创建时间: %s\n", orders[i].create_time);

			if (orders[i].driver_id != -1) {
				User* driver = NULL;
				for (int j = 0; j < user_count; j++) {
					if (users[j].id == orders[i].driver_id) {
						driver = &users[j];
						break;
					}
				}
				if (driver) {
					printf("司机: %s (%s)\n", driver->username, driver->phone);
				}
			}

			printf("------------------------\n");
			found++;
		}
	}

	if (found == 0) {
		printf("暂无订单记录。\n");
	}
}

