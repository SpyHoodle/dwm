{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = [ pkgs.gnumake pkgs.pkg-config pkgs.xorg.libX11 pkgs.xorg.libXft pkgs.xorg.libXinerama ];
}
