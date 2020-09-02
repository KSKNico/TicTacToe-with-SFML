let
  sources = import ./nix/sources.nix;
  niv = import sources.niv { inherit sources; };
  nixpkgs = import sources.nixpkgs { };
in { pkgs ? nixpkgs }:
pkgs.mkShell {
  buildInputs = [
    # Build tooling
    pkgs.cmake
    pkgs.pkgconfig

    # Libraries we depend on
    pkgs.sfml

    # Nix-specific
    niv.niv
  ];
}
