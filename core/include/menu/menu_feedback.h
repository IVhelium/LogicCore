#pragma once

constexpr int MENU_FEDBACK_MESSAGE_SIZE = 512;

typedef enum MenuFeadbackStatus {
    NONE,
    SUCCESS,
    INFO,
    ERROR,
    MENU_FEADBACK_STATUS_COUNT
} MenuFeadbackStatus;

typedef struct MenuFeadback {
    MenuFeadbackStatus status;
    char message[MENU_FEDBACK_MESSAGE_SIZE];
} MenuFeadback;

