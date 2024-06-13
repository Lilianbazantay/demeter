{pkgs, ...}: let
  debug-attrs = {
    cmakeBuildType = "Debug";
    dontStrip = true;
    enableDebugging = true;
  };
in
  pkgs.csfml.overrideAttrs (prev:
    {
      buildInputs = let
        sfml-debug = pkgs.sfml.overrideAttrs (_: debug-attrs);
      in [sfml-debug];

      patches = [./notice.patch];

      # In debug mode, lib ends with -d suffix, symlink without it
      postInstall = ''
        ls $out/lib | while read file; do
          ln -s "$out/lib/''${file}" "$out/lib/''${file/-d/}";
        done
      '';
    }
    // debug-attrs)
