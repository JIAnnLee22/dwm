{
  description = "dwm (suckless) packaged as a Nix flake + overlay";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs =
    { self, nixpkgs }:
    let
      systems = [
        "x86_64-linux"
        "aarch64-linux"
      ];
      forAllSystems = nixpkgs.lib.genAttrs systems;
      pkgsFor =
        system:
        import nixpkgs {
          inherit system;
          overlays = [ self.overlays.default ];
        };
    in
    {
      packages = forAllSystems (system: {
        inherit (pkgsFor system) dwm;
        default = self.packages.${system}.dwm;
      });

      overlays.default = final: _prev: {
        dwm = final.callPackage ./nix/package.nix { src = self; };
      };

      nixosModules.default = import ./nix/module.nix self;
      checks = forAllSystems (system: {
        dwm = self.packages.${system}.dwm;
      });
      formatter = forAllSystems (system: (pkgsFor system).nixfmt);
    };
}
