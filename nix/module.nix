self:
{
  config,
  lib,
  pkgs,
  ...
}:
{
  nixpkgs.overlays = [ self.overlays.default ];

  services.xserver.enable = lib.mkDefault true;
  services.xserver.windowManager.dwm = {
    enable = lib.mkDefault true;
    package = lib.mkDefault pkgs.dwm;
  };

  # slock needs its privileged NixOS wrapper; the package's PATH prefers it.
  programs.slock.enable = lib.mkIf config.services.xserver.windowManager.dwm.enable (
    lib.mkDefault true
  );
}
