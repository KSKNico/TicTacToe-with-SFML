{ stdenv, cmake, sfml }:
stdenv.mkDerivation {
  name = "tic-tac-toe";
  src = ./.;
  nativeBuildInputs = [ cmake ];
  buildInputs = [ sfml ];
}
