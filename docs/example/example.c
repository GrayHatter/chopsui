#include <chopsui.h>

void say_hi_clicked(sui_t *button, sui_event_t *event) {
	sui_alert("Hello world!");
}

void exit_clicked(sui_t *button, sui_event_t *event) {
	sui_exit();
}

int main(int argc, char **argv) {
	init_sui();
	sui_t *window = sui_load("window.sui");
	sui_load_css("window.css");
	sui_add_handler(window, exit_clicked);
	sui_add_handler(window, say_hi_clicked);
	sui_show(window);
	sui_run();
	return 0;
}
