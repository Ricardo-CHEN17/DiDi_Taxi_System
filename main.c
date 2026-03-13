#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "data.h"
#include <windows.h>

int main() {

    printf("========== 欢迎使用滴滴打车系统 ==========\n");
    printf("            作者: Yijin CHEN\n");
    printf("==========================================\n");
    printf("系统初始化中...\n");

    // 加载数据
    load_all_data();
    printf("数据加载完成！\n");

    // 显示主菜单
    pause_program();
    show_main_menu();

    return 0;
}