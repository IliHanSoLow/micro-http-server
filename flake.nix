{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem
    (
      system: let
        pkgs = nixpkgs.legacyPackages.${system};
      in
        with pkgs; {
          devShells.default = mkShell {
            buildInputs = [
              ninja
            ];
          };
          c_http = pkgs.stdenv.mkDerivation {
            name = "c_http";
            src = ./src/main.c;
            buildPhase = "make build";
            installPhase = "make setup";
          };
        }
    );
}
