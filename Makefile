CC = gcc
CFLAGs = -g \
				 -pthread \
				 -I/usr/include/gtkmm-3.0 \
				 -I/usr/lib/gtkmm-3.0/include \
				 -I/usr/include/atkmm-1.6 \
				 -I/usr/include/atk-1.0 \
				 -I/usr/include/glib-2.0 \
				 -I/usr/lib/glib-2.0/include \
				 -I/usr/lib/libffi-3.2.1/include \
				 -I/usr/include/glibmm-2.4 \
				 -I/usr/lib/glibmm-2.4/include \
				 -I/usr/include/sigc++-2.0 \
				 -I/usr/lib/sigc++-2.0/include \
				 -I/usr/include/giomm-2.4 \
				 -I/usr/lib/giomm-2.4/include \
				 -I/usr/include/libmount \
				 -I/usr/include/blkid \
				 -I/usr/include/pangomm-1.4 \
				 -I/usr/lib/pangomm-1.4/include \
				 -I/usr/include/cairomm-1.0 \
				 -I/usr/lib/cairomm-1.0/include \
				 -I/usr/include/cairo \
				 -I/usr/include/pixman-1 \
				 -I/usr/include/freetype2 \
				 -I/usr/include/libpng16 \
				 -I/usr/include/harfbuzz \
				 -I/usr/include/uuid \
				 -I/usr/include/pango-1.0 \
				 -I/usr/include/fribidi \
				 -I/usr/include/gtk-3.0 \
				 -I/usr/include/gdk-pixbuf-2.0 \
				 -I/usr/include/gio-unix-2.0 \
				 -I/usr/include/at-spi2-atk/2.0 \
				 -I/usr/include/dbus-1.0 \
				 -I/usr/lib/dbus-1.0/include \
				 -I/usr/include/at-spi-2.0 \
				 -I/usr/include/gtk-3.0/unix-print \
				 -I/usr/include/gdkmm-3.0 \
				 -I/usr/lib/gdkmm-3.0/include \
				 -I./inc \
				 -I./src

TARGET = ./src/*.cc

CLIBS = -lgtkmm-3.0 \
				-latkmm-1.6 \
				-lgdkmm-3.0 \
				-lgiomm-2.4 \
				-lpangomm-1.4 \
				-lglibmm-2.4 \
				-lgtk-3 \
				-lgdk-3 \
				-lz \
				-lpangocairo-1.0 \
				-lpango-1.0 \
				-lharfbuzz \
				-latk-1.0 \
				-lcairo-gobject \
				-lgio-2.0 \
				-lcairomm-1.0 \
				-lcairo \
				-lsigc-2.0 \
				-lgdk_pixbuf-2.0 \
				-lgobject-2.0 \
				-lglib-2.0 \
				-lpthread \
				-lstdc++ \
				-lcurl \
				-lm

OUTPUT = ./out/OSRS-Gear-Calculator

all:
	$(CC) $(CFLAGs) $(TARGET) $(CLIBS) -o $(OUTPUT)