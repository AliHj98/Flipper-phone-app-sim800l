#include "../uart_terminal_app_i.h"

// For each command, define whether additional arguments are needed
// (enabling text input to fill them out), and whether the console
// text box should focus at the start of the output or the end
typedef enum { NO_ARGS = 0, INPUT_ARGS, TOGGLE_ARGS } InputArgs;

typedef enum { FOCUS_CONSOLE_END = 0, FOCUS_CONSOLE_START, FOCUS_CONSOLE_TOGGLE } FocusConsole;

#define SHOW_STOPSCAN_TIP_1 (true)

#define SHOW_STOPSCAN_TIP (true)
#define NO_TIP (false)

#define MAX_OPTIONS (25)
typedef struct {
    const char* item_string;
    const char* options_menu[MAX_OPTIONS];
    int num_options_menu;
    const char* actual_commands[MAX_OPTIONS];
    InputArgs needs_keyboard;
    FocusConsole focus_console;
    bool show_stopscan_tip;
} UART_TerminalItem;

// NUM_MENU_ITEMS defined in uart_terminal_app_i.h - if you add an entry here, increment it!
const UART_TerminalItem items[NUM_MENU_ITEMS] = {
    {"Console",
     {"115200", "75",     "110",    "150",    "300",    "600",    "1200",  "1800",  "2400",
      "4800",   "7200",   "9600",   "14400",  "19200",  "31250",  "38400", "56000", "57600",
      "76800",  "128000", "230400", "250000", "256000", "460800", "921600"},
     25,
     {"115200", "75",     "110",    "150",    "300",    "600",    "1200",  "1800",  "2400",
      "4800",   "7200",   "9600",   "14400",  "19200",  "31250",  "38400", "56000", "57600",
      "76800",  "128000", "230400", "250000", "256000", "460800", "921600"},
     NO_ARGS,
     FOCUS_CONSOLE_END,
     NO_TIP},
    {"Phone stat", {""}, 1, {"AT+CPAS"}, INPUT_ARGS, FOCUS_CONSOLE_END, NO_TIP},
    {"Signal Quality", {""}, 1, {"AT+CSQ"}, NO_ARGS, FOCUS_CONSOLE_START, NO_TIP},
    {"SIM card Number", {""}, 1, {"AT+CCID"}, NO_ARGS, FOCUS_CONSOLE_START, NO_TIP},

    {"Call number <NUMBER;>", {""}, 1, {"ATD+"}, INPUT_ARGS, FOCUS_CONSOLE_END, SHOW_STOPSCAN_TIP},

    {"Send AT command", {""}, 1, {"AT"}, INPUT_ARGS, FOCUS_CONSOLE_END, NO_TIP},
    
    {"Fast cmd",
     {"help", "uptime", "date", "df -h", "ps", "dmesg", "reboot", "poweroff"},
     8,
     {"help", "uptime", "date", "df -h", "ps", "dmesg", "reboot", "poweroff"},
     INPUT_ARGS,
     FOCUS_CONSOLE_END,
     NO_TIP},
     
    {"Help", {""}, 1, {"help"}, NO_ARGS, FOCUS_CONSOLE_START, SHOW_STOPSCAN_TIP},
};

static void uart_terminal_scene_start_var_list_enter_callback(void* context, uint32_t index) {
    furi_assert(context);
    UART_TerminalApp* app = context;

    furi_assert(index < NUM_MENU_ITEMS);
    const UART_TerminalItem* item = &items[index];

    const int selected_option_index = app->selected_option_index[index];
    furi_assert(selected_option_index < item->num_options_menu);
    app->selected_tx_string = item->actual_commands[selected_option_index];
    app->is_command = (1 <= index);
    app->is_custom_tx_string = false;
    app->selected_menu_index = index;
    app->focus_console_start = (item->focus_console == FOCUS_CONSOLE_TOGGLE) ?
                                   (selected_option_index == 0) :
                                   item->focus_console;
    app->show_stopscan_tip = item->show_stopscan_tip;

    bool needs_keyboard = (item->needs_keyboard == TOGGLE_ARGS) ? (selected_option_index != 0) :
                                                                  item->needs_keyboard;
    if(needs_keyboard) {
        view_dispatcher_send_custom_event(app->view_dispatcher, UART_TerminalEventStartKeyboard);
    } else {
        view_dispatcher_send_custom_event(app->view_dispatcher, UART_TerminalEventStartConsole);
    }
}

static void uart_terminal_scene_start_var_list_change_callback(VariableItem* item) {
    furi_assert(item);

    UART_TerminalApp* app = variable_item_get_context(item);
    furi_assert(app);

    const UART_TerminalItem* menu_item = &items[app->selected_menu_index];
    uint8_t item_index = variable_item_get_current_value_index(item);
    furi_assert(item_index < menu_item->num_options_menu);
    variable_item_set_current_value_text(item, menu_item->options_menu[item_index]);
    app->selected_option_index[app->selected_menu_index] = item_index;
}

void uart_terminal_scene_start_on_enter(void* context) {
    UART_TerminalApp* app = context;
    VariableItemList* var_item_list = app->var_item_list;

    variable_item_list_set_enter_callback(
        var_item_list, uart_terminal_scene_start_var_list_enter_callback, app);

    VariableItem* item;
    for(int i = 0; i < NUM_MENU_ITEMS; ++i) {
        item = variable_item_list_add(
            var_item_list,
            items[i].item_string,
            items[i].num_options_menu,
            uart_terminal_scene_start_var_list_change_callback,
            app);
        variable_item_set_current_value_index(item, app->selected_option_index[i]);
        variable_item_set_current_value_text(
            item, items[i].options_menu[app->selected_option_index[i]]);
    }

    variable_item_list_set_selected_item(
        var_item_list, scene_manager_get_scene_state(app->scene_manager, UART_TerminalSceneStart));

    view_dispatcher_switch_to_view(app->view_dispatcher, UART_TerminalAppViewVarItemList);
}

bool uart_terminal_scene_start_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UART_TerminalApp* app = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == UART_TerminalEventStartKeyboard) {
            scene_manager_set_scene_state(
                app->scene_manager, UART_TerminalSceneStart, app->selected_menu_index);
            scene_manager_next_scene(app->scene_manager, UART_TerminalAppViewTextInput);
        } else if(event.event == UART_TerminalEventStartConsole) {
            scene_manager_set_scene_state(
                app->scene_manager, UART_TerminalSceneStart, app->selected_menu_index);
            scene_manager_next_scene(app->scene_manager, UART_TerminalAppViewConsoleOutput);
        }
        consumed = true;
    } else if(event.type == SceneManagerEventTypeTick) {
        app->selected_menu_index = variable_item_list_get_selected_item_index(app->var_item_list);
        consumed = true;
    }

    return consumed;
}

void uart_terminal_scene_start_on_exit(void* context) {
    UART_TerminalApp* app = context;
    variable_item_list_reset(app->var_item_list);
}
