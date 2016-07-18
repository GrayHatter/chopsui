#include <chopsui.h>

void say_hi_clicked(sui_t *source, sui_event_t *event) {
	sui_alert("Hello world!");
}

void exit_clicked(sui_t *source, sui_event_t *event) {
	sui_exit();
}

void add_thing_clicked(sui_t *source, sui_event_t *event) {
	sui_t *window = sui_find_anscestor(source, "window"); // CSS selector
	sui_t *container = sui_find_descendant(window, "#main-container");
	sui_t *new_text = sui_parse_sui("label text='New Text'");
	sui_add_child(container, new_text);
}

int main(int argc, char **argv) {
	init_sui();
	sui_t *window = sui_load_sui("window.sui");
	sui_css_t *css = sui_load_css("window.css");
	sui_add_handler(window, exit_clicked);
	sui_add_handler(window, say_hi_clicked);
	sui_add_handler(window, add_thing_clicked);
	sui_style(window, css);
	sui_show(window);
	sui_run();
	return 0;
}
