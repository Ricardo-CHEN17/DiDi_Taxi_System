#define _CRT_SECURE_NO_WARNINGS
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

User users[MAX_USERS];
Vehicle vehicles[MAX_VEHICLES];
Order orders[MAX_ORDERS];

int user_count = 0;
int vehicle_count = 0;
int order_count = 0;

User current_user;
int is_logged_in = 0;

//数据文件路径
#define USER_FILE "data/users.txt"
#define VEHICLE_FILE "data/vehicles.txt"
#define ORDER_FILE "data/orders.txt"

// 获取订单状态名称
const char* get_order_status_name(OrderStatus status) {
	switch (status) {
	case ORDER_WAITING: return "等待接单";
	case ORDER_ACCEPTED: return "已接单";
	case ORDER_ONGOING: return "进行中";
	case ORDER_COMPLETED: return "已完成";
	case ORDER_CANCELLED: return "已取消";
	default: return "未知";
	}
}

void load_all_data() {
	FILE* file;

	system("mkdir data 2 > nul");//确保数据存储目录存在
	// 加载用户数据
	file = fopen(USER_FILE, "r");

	if (file) {
		while(scanf(file,"%d %s %s %s %d %f %d",
			&users[user_count].id,
			users[user_count].username,
			users[user_count].password,
			users[user_count].phone,
			(int*)&users[user_count].type,
			&users[user_count].balance,
			(int*)&users[user_count].status) == 7){

			user_count++;
		}
		fclose(file);
	}

	// 加载车辆数据
	file = fopen(VEHICLE_FILE, "r");

	if (file) {
		while (scanf(file, "%d %d %s %s %d",
			&vehicles[vehicle_count].id,
			&vehicles[vehicle_count].driver_id,
			vehicles[vehicle_count].plate_number,
			vehicles[vehicle_count].type,
			&vehicles[vehicle_count].seats) == 5) {

			vehicle_count++;
		}
		fclose(file);
	}
	// 加载订单数据
	file = fopen(ORDER_FILE, "r");
	if (file) {
		while (scanf(file, "%d %d %d %s %s %f %f %d %s",
			&orders[order_count].id,
			&orders[order_count].passenger_id,
			&orders[order_count].driver_id,
			orders[order_count].start_location,
			orders[order_count].end_location,
			&orders[order_count].distance,
			&orders[order_count].price,
			(int*)&orders[order_count].status,
			orders[order_count].create_time,
			orders[order_count].accept_time,
			orders[order_count].complete_time)==11) {

			order_count++;
		}
		fclose(file);
	}

	printf("数据加载完成！用户数：%d\n", user_count);
	printf("数据加载完成！车辆数：%d\n", user_count);
	printf("数据加载完成！订单数：%d\n", user_count);
}

void save_all_data() {
	FILE* file;

	// 保存用户数据
	file = fopen(USER_FILE, "w");
	if (file) {
		for (int i = 0; i < user_count; i++) {
			fprintf(file, "%d %s %s %s %d %.2f %d\n",
				users[i].id,
				users[i].username,
				users[i].password,
				users[i].phone,
				users[i].type,
				users[i].balance,
				users[i].status);
		}
		fclose(file);
	}

	// 保存车辆数据
	file = fopen(VEHICLE_FILE, "w");
	if (file) {
		for (int i = 0; i < vehicle_count; i++) {
			fprintf(file, "%d %d %s %s %d\n",
				vehicles[i].id,
				vehicles[i].driver_id,
				vehicles[i].plate_number,
				vehicles[i].type,
				vehicles[i].seats);
		}
		fclose(file);
	}

	// 保存订单数据
	file = fopen(ORDER_FILE, "w");
	if (file) {
		for (int i = 0; i < order_count; i++) {
			fprintf(file, "%d %d %d %s %s %.2f %.2f %d %s %s %s\n",
				orders[i].id,
				orders[i].passenger_id,
				orders[i].driver_id,
				orders[i].start_location,
				orders[i].end_location,
				orders[i].distance,
				orders[i].price,
				orders[i].status,
				orders[i].create_time,
				orders[i].accept_time,
				orders[i].complete_time);
		}
		fclose(file);
	}

	printf("数据保存完成！\n");
}

int add_user(User user) {
	if (user_count >= MAX_USERS) {
		printf("用户数量已达上限！\n");
		return 0;
	}

	user.id = user_count + 1;
	users[user_count] = user;
	user_count++;

	return 1;
}

User* find_user_by_username(const char* username) {
	for (int i = 0; i < user_count; i++) {
		if (strcmp(users[i].username, username) == 0) {
			return &users[i];
		}
	}
	//strcmp()函数基于ASCII码值进行比较，如果相等则返回0
	return NULL;
}

User* find_user_by_phone(const char* phone) {
	for (int i = 0; i < user_count; i++) {
		if (strcmp(users[i].phone, phone) == 0) {
			return &users[i];
		}
	}
	return NULL;
}


int add_vehicle(Vehicle vehicle) {
	if (vehicle_count >= MAX_VEHICLES) {
		printf("车辆数量已达上限！\n");
		return 0;
	}

	vehicle.id = vehicle_count + 2001;
	vehicles[vehicle_count] = vehicle;
	vehicle_count++;

	printf("车辆添加成功！车辆ID: %d\n", vehicle.id);
	return 1;
}

Vehicle* find_vehicle_by_driver(int driver_id) {
	for (int i = 0; i < vehicle_count; i++) {
		if (vehicles[i].driver_id == driver_id) {
			return &vehicles[i];
		}
	}
	return NULL;
}

int add_order(Order order) {
	if (order_count >= MAX_ORDERS) {
		printf("订单数量已达上限！\n");
		return 0;
	}

	order.id = order_count + 3001;
	orders[order_count] = order;
	order_count++;

	printf("订单创建成功！订单号: %d\n", order.id);
	return 1;
}

Order* find_order_by_id(int order_id) {
	for (int i = 0; i < order_count; i++) {
		if (orders[i].id == order_id) {
			return &orders[i];
		}
	}
	return NULL;
}

// 根据司机ID查找订单
Order* find_order_by_driver(int driver_id) {
	for (int i = 0; i < order_count; i++) {
		if (orders[i].driver_id == driver_id &&
			orders[i].status != ORDER_COMPLETED &&
			orders[i].status != ORDER_CANCELLED) {
			return &orders[i];
		}
	}
	return NULL;
}

// 根据乘客ID查找订单
Order* find_order_by_passenger(int passenger_id) {
	for (int i = 0; i < order_count; i++) {
		if (orders[i].passenger_id == passenger_id &&
			orders[i].status != ORDER_COMPLETED &&
			orders[i].status != ORDER_CANCELLED) {
			return &orders[i];
		}
	}
	return NULL;
}

// 查找可接订单
Order* find_available_orders(int* count) {
	static Order available_orders[MAX_ORDERS];
	int found = 0;

	for (int i = 0; i < order_count; i++) {
		if (orders[i].status == ORDER_WAITING) {
			available_orders[found] = orders[i];
			found++;
		}
	}

	*count = found;
	return available_orders;
}

// 更新订单
int update_order(Order order) {
	for (int i = 0; i < order_count; i++) {
		if (orders[i].id == order.id) {
			orders[i] = order;
			return 1;
		}
	}
	return 0;
}

// 更新用户
int update_user(User user) {
	for (int i = 0; i < user_count; i++) {
		if (users[i].id == user.id) {
			users[i] = user;
			return 1;
		}
	}
	return 0;
}

//获取用户类型
const char* get_user_type_name(UserType type) {
	return type == USER_PASSENGER ? "乘客" : "司机";
}

// 生成时间字符串
void generate_time_string(char* buffer) {
	time_t now = time(NULL);
	struct tm* timeinfo = localtime(&now);
	strftime(buffer, MAX_TIME_LEN, "%Y-%m-%d %H:%M:%S", timeinfo);
}