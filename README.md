# chopsui [![](https://travis-ci.org/SirCmpwn/chopsui.svg?branch=master)](https://travis-ci.org/SirCmpwn/chopsui)

This is a **very** WIP library for creating user interfaces. There are no
screenshots because it doesn't support rendering yet.

    make
    make check

There is no `make install` yet. Edit `config.mk` if you want.

## Goals

See docs/example/ for an idea of what an example project could look like.

- CSS for styling and tree traversal (`sui_find_descendant(window, ".list > button")`)
- SUI markup for layout
    ```
    window @main-window title='chopsui example'
      container @main-container orientation=vertical
        label .heading text='Hello World!'
        button clicked=say_hi_clicked
          label text='Say hi'
        button [
          clicked=exit_clicked
          background='#FF0000'
        ]
          label text='Exit'
        button background='#eeeeee' clicked=add_thing_clicked { label text='Add Thing' }
    ```

- SUI at runtime:
    ```c
    sui_node_t *button = sui_parse_sui("button color=black { label text='Click me' }");
    ```
- Highly modular (layout engine, CSS parser, SUI parser, etc should all be
    usable solo)
- Written in C with no magic (GTK has lots of magic and is hard to write API
    wrappers for, Qt is C++ and hard to write API wrappers for)
- Mobile support and responsive UI without compromises on any platform (desktop
    still feels like a desktop UI, mobile still feels like a mobile UI)
- Web support?
- Embeddable in arbitrary GL applications (video games?)

Why doesn't this exist yet?
