{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";

    pre-commit-hooks = {
      url = "github:cachix/pre-commit-hooks.nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };

  outputs = {
    self,
    nixpkgs,
    flake-utils,
    pre-commit-hooks,
  }:
    flake-utils.lib.eachSystem ["x86_64-linux"] (system: let
      pkgs = nixpkgs.legacyPackages.${system};
    in {
      formatter = pkgs.alejandra;

      devShells = {
        default = pkgs.mkShell {
          inherit (self.checks.${system}.pre-commit-check) shellHook;

          inputsFrom = pkgs.lib.attrsets.attrValues self.packages.${system};
          hardeningDisable = ["format" "fortify"];
          packages = with pkgs; [
            tokei
            valgrind
            python3Packages.compiledb
            bear
          ];
        };
      };

      packages = {
        default = self.packages.${system}.my_rpg;

        my_rpg = pkgs.callPackage ./nix/build_rpg.nix {};

        csfml-debug = pkgs.callPackage ./nix/csfml_debug {};

        debug = self.packages.${system}.my_rpg.override {
          name = "debug";
          csfml = self.packages.${system}.csfml-debug;
        };
      };

      checks = {
        pre-commit-check = pre-commit-hooks.lib.${system}.run {
          src = ./.;
          hooks = {
            alejandra.enable = true;
            convco.enable = true;
          };
        };
      };
    });
}
