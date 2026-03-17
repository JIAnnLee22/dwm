{
  description = "dwm (suckless) packaged as a Nix flake + overlay";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      systems = [
        "x86_64-linux"
        "aarch64-linux"
      ];
      forAllSystems = f: nixpkgs.lib.genAttrs systems (system: f system);

      mkDwm =
        { pkgs }:
        pkgs.stdenv.mkDerivation {
          pname = "dwm";
          version = "6.8";

          src = self;

          nativeBuildInputs = [ pkgs.pkg-config ];
          buildInputs = [
            pkgs.libx11
            pkgs.libxinerama
            pkgs.libxft
            pkgs.fontconfig
            pkgs.freetype
          ];

          makeFlags = [
            "PREFIX=/"
            "MANPREFIX=/share/man"

            "X11INC=${pkgs.libx11.dev}/include"
            "X11LIB=${pkgs.libx11.out}/lib"

            "FREETYPEINC=${pkgs.freetype.dev}/include/freetype2"
          ];

          installFlags = [ "DESTDIR=$(out)" ];

          meta = {
            description = "Dynamic window manager for X";
            homepage = "https://dwm.suckless.org/";
            license = pkgs.lib.licenses.mit;
            platforms = pkgs.lib.platforms.linux;
            mainProgram = "dwm";
          };
        };
    in
    {
      packages = forAllSystems (system: rec {
        dwm = mkDwm { pkgs = import nixpkgs { inherit system; }; };
        default = dwm;
      });

      overlays.default = final: prev: {
        dwm = mkDwm { pkgs = final; };
      };

      nixosModules.default =
        { config, lib, pkgs, ... }:
        {
          imports = [ ];

          config = {
            nixpkgs.overlays = [ self.overlays.default ];

            services.xserver.enable = lib.mkDefault true;
            services.xserver.windowManager.dwm.enable = lib.mkDefault true;
          };
        };
    };
}

