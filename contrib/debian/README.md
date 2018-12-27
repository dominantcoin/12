
Debian
====================
This directory contains files used to package dmtcd/dmtc-qt
for Debian-based Linux systems. If you compile dmtcd/dmtc-qt yourself, there are some useful files here.

## dmtc: URI support ##


dmtc-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install dmtc-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your dmtcqt binary to `/usr/bin`
and the `../../share/pixmaps/dmtc128.png` to `/usr/share/pixmaps`

dmtc-qt.protocol (KDE)

