#define _CRT_SECURE_NO_WARNINGS
#include "utils.h"

void clear_input_buffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

int get_int_input(const char* prompt, int min, int max) {
	int value;
	int valid = 0;
	while (!valid) {
		printf("%s", prompt);
		if (scanf("%d", &value) != 1) {
			clear_input_buffer();
			printf("Invaid! Please input a number!\n");
			continue;
		}
		clear_input_buffer();

		if (value < min || value > max) {
			printf("Input out of range! Please in put a number in range of %d and %d\n", min, max);
		}
		else {
			valid = 1;
		}
	}
	return value;
}

void get_string_input(char* buffer, int size, const char* prompt) {
	// ²ÎÊý¼ì²é
	if (buffer == NULL || size <= 0) {
		return;
	}

	if (prompt != NULL) {
		printf("%s", prompt);
	}

	buffer[0] = '\0';

	if (fgets(buffer, size, stdin) == NULL) {
		buffer[0] = '\0';
		return;
	}

	size_t len = strlen(buffer);
	if (len > 0 && buffer[len - 1] == '\n') {
		buffer[len - 1] = '\0';
	}
	else if (len == size - 1) {
		clear_input_buffer();
	}
}
int validate_phone(const char* phone) {
	if (strlen(phone) != 11) {
		return 0;
	}

	for (int i = 0; i < 11; i++) {
		if (!isdigit(phone[i])) {
			return 0;
		}
	}
	
	return 1;
}

int validate_password(const char* password) {
	return strlen(password) >= 6;
}

void pause_program() {
	printf("\nPress any key to continue");
	getchar();
}