#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p build
cd build
for lib in kernel32 user32 gdi32 shell32; do
  lld-link /dll /noentry /nodefaultlib /machine:x64 /out:${lib}.dll /implib:${lib}.lib /def:../${lib}.def >/dev/null
done
lld-link /dll /noentry /nodefaultlib /machine:x64 /out:kernel32_external.dll /implib:kernel32_external.lib /def:../kernel32_external.def >/dev/null
clang --target=x86_64-pc-windows-msvc -ffreestanding -fno-builtin -fno-stack-protector -mno-stack-arg-probe -O2 -c ../external_menu.c -o external_menu.obj
clang --target=x86_64-pc-windows-msvc -ffreestanding -fno-builtin -fno-stack-protector -O2 -c ../launcher.c -o launcher.obj
lld-link /entry:ExternalMenuEntry /nodefaultlib /machine:x64 /subsystem:windows /dynamicbase /nxcompat /out:LuvvyOdysseyExternalMenu.exe external_menu.obj kernel32_external.lib user32.lib gdi32.lib shell32.lib
lld-link /entry:LauncherEntry /nodefaultlib /machine:x64 /subsystem:windows /dynamicbase /nxcompat /out:"Luvvy Odyssey.exe" launcher.obj kernel32.lib shell32.lib
