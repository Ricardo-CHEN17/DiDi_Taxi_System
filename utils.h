#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 清除缓冲区
void clear_input_buffer();

// 获取安全的整数输入
int get_int_input(const char* prompt, int min, int max);

//获取安全的字符串输入（防止溢出）
void get_string_input(char* buffer, int size, const char* prompt);

// 验证手机号格式（简单验证）
int validate_phone(const char* phone);

// 验证密码强度（简单验证：至少6位）
int validate_password(const char* password);

// 暂停程序，按任意键继续
void pause_program();

#endif