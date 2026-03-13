#pragma once
#ifndef DATA_H
#define DATA_H

#define MAX_USERS 100
#define MAX_ORDERS 200
#define MAX_VEHICLES 50
#define MAX_NAME_LEN 20
#define MAX_PHONE_LEN 12
#define MAX_LOCATION_LEN 50
#define MAX_PLATE_LEN 10
#define MAX_CAR_TYPE_LEN 20
#define MAX_TIME_LEN 20

typedef enum {
	USER_PASSENGER = 0,
	USER_DRIVER = 1
}UserType;

typedef enum {
	STATUS_OFFLINE = 0,
	STATUS_ONLINE = 1
}UserStatus;

typedef enum {
	ORDER_WAITING = 0,
	ORDER_ACCEPTED = 1,
	ORDER_ONGOING = 2,
	ORDER_COMPLETED = 3,
	ORDER_CANCELLED = 4
}OrderStatus;

typedef struct {
	int id;
	char username[MAX_NAME_LEN];
	char password[MAX_NAME_LEN];
	char phone[MAX_PHONE_LEN];
	UserType type;
	float balance;
	UserStatus status;
} User;

typedef struct {
	int id;
	int driver_id;	// 司机ID（-1表示未分配）
	char plate_number[MAX_PLATE_LEN];
	char type[MAX_CAR_TYPE_LEN];
	int seats;
} Vehicle;

typedef struct {
	int id;//订单id
	int passenger_id;
	int driver_id;
	char start_location[MAX_LOCATION_LEN];
	char end_location[MAX_LOCATION_LEN];
	float distance;//公里
	float price;
	OrderStatus status;
	char create_time[MAX_TIME_LEN];
	char accept_time[MAX_TIME_LEN];
	char complete_time[MAX_TIME_LEN];
} Order;

// 全局数据数组（告诉计算机这几个变量已经存在，无需重新分配内存）
extern User users[MAX_USERS];
extern Vehicle vehicles[MAX_VEHICLES];
extern Order orders[MAX_ORDERS];
extern int user_count;
extern int vehicle_count;
extern int order_count;
extern User current_user;
extern int is_logged_in;

// 当前登录用户信息
extern User current_user;

//文件操作函数
void load_all_data();
void save_all_data();

//用户数据操作
int add_User(User user);
User* find_user_by_username(const char* username);
User* find_user_by_phone(const char* phone);

//车辆数据操作
int add_vehicle(Vehicle vehicle);
Vehicle* find_vehicle_by_driver(int driver_id);

//订单数据操作
int add_order(Order order);
Order* find_order_by_id(int order_id);
Order* find_order_by_driver(int driver_id);
Order* find_order_by_passenger(int passenger_id);
Order* find_available_orders(int* count);  // 查找可接订单
int update_order(Order order);
int update_user(User user);

// 辅助函数
const char* get_user_type_name(UserType type);
const char* get_order_status_name(OrderStatus status);
void generate_time_string(char* buffer);
#endif

