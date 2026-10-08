# NixOS integration
The flake exports `packages.<system>.dwm`, `packages.<system>.default`, `overlays.default`, and `nixosModules.default` for x86_64-linux and aarch64-linux. Its module enables Xorg and dwm and configures the privileged `programs.slock` wrapper; login-manager policy remains with the consuming NixOS configuration.
```nix
inputs.dwm = {
  url = "git+ssh://git@github.com/JIAnnLee22/dwm.git?ref=master";
  inputs.nixpkgs.follows = "nixpkgs";
};
# In nixosSystem's modules:
# inputs.dwm.nixosModules.default
```
To use a custom C configuration declaratively:
```nix
services.xserver.windowManager.dwm.package = pkgs.dwm.override {
  conf = ./config.h;
};
```
## greetd / rootless Xorg
Unlike Wayland compositors, dwm does not start a display server. Use NixOS's generated startx scripts rather than launching `dwm` directly from greetd:
```nix
{ pkgs, lib, ... }:
let
  session = pkgs.writeShellApplication {
    name = "dwm-session";
    runtimeInputs = [ pkgs.xinit ];
    text = ''
      export XDG_SESSION_TYPE=x11
      export XDG_CURRENT_DESKTOP=dwm
      export XDG_SESSION_DESKTOP=dwm
      exec startx /etc/X11/xinit/xinitrc -- /etc/X11/xinit/xserverrc :0 vt1 -keeptty
    '';
  };
in {
  services.xserver.displayManager = {
    lightdm.enable = false;
    startx = {
      enable = true;
      generateScript = true;
      extraCommands = ''
        ${pkgs.dbus}/bin/dbus-update-activation-environment --systemd \
          DISPLAY XAUTHORITY XDG_CURRENT_DESKTOP XDG_SESSION_DESKTOP XDG_SESSION_TYPE
      '';
    };
  };
  services.greetd = {
    enable = true;
    useTextGreeter = true;
    settings.default_session = {
      command = "${lib.getExe pkgs.tuigreet} --cmd ${lib.getExe session}";
      user = "greeter";
    };
  };
}
```
Current NixOS greetd runs on VT1. `vt1 -keeptty` lets unprivileged Xorg use the authenticated logind session's controlling terminal. Explicit xinitrc/xserverrc paths avoid stale per-user startup overrides. NixOS's generated xinitrc starts/stops the graphical user-session target and waits for dwm; exiting dwm returns to the greeter. On a machine with another X server already using display `:0`, choose an unused display number.
Do not run a second login manager in parallel. If autologin is wanted, set greetd's `settings.initial_session` to the same session command and a real login user; `default_session` must remain the unprivileged greeter account.
## Autostart and keyboard commands
Executable `autostart_blocking.sh` and `autostart.sh` are searched independently in this order:
1. `$XDG_CONFIG_HOME/dwm`, defaulting to `$HOME/.config/dwm`.
2. `$XDG_DATA_HOME/dwm`, defaulting to `$HOME/.local/share/dwm` for compatibility.
3. `$HOME/.dwm` for compatibility.
Empty/relative XDG values are ignored. Blocking startup completes first; ordinary startup runs asynchronously. Scripts are executed directly without constructing shell commands, so spaces and shell metacharacters in paths are safe. Scripts must be executable and have a valid shebang; on NixOS use `pkgs.writeShellScript`, not `#!/bin/bash`.
The default lock binding executes `slock` through PATH. The Nix package prepends `/run/wrappers/bin`, ensuring NixOS's privileged wrapper is used instead of the unprivileged store binary. Wallpaper switching defaults to `$HOME/Pictures/wallpaper`; override this using `DWM_WALLPAPER_DIR`. Other keybinding/autostart dependencies (st, rofi, feh, etc.) remain the consumer's responsibility rather than adding a large application closure to dwm itself. The touchpad binding uses synclient and therefore needs a Synaptics-managed device, not libinput.
## Build validation
`nix flake check` builds the package. For local integration before publication:
```sh
nix flake check --override-input nixpkgs path:/path/to/cached/nixpkgs
nix build path:/path/to/nixos-config#nixosConfigurations.HOST.config.system.build.toplevel \
  --override-input dwm path:/path/to/dwm --no-write-lock-file
```
