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
          packages.x86_64-linux.c_http = pkgs.stdenv.mkDerivation {
            name = "c_http";
            src = ./src/main.c;
            buildPhase = "make";
            preBuild = "make setup";
            installPhase = ''
              mkdir $out/bin
              cp build/c_http $out/bin/
            '';
          };
          defaultPackage.x86_64-linux = self.packages.x86_64-linux.c_http;
        }
    );
}
