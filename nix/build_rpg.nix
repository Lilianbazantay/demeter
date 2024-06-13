{
  stdenv,
  csfml,
  name ? "my_rpg",
  ncurses, # colored build logs requires tput
}:
stdenv.mkDerivation (finalAttrs: {
  inherit name;

  src = ./..;

  nativeBuildInputs = [ncurses];
  buildInputs = [csfml];

  preConfigure = "touch .fast";

  prePatch = ''
    substituteInPlace demeter_V2/{de_sound.c,de_texture.c} \
      --replace-fail "./resources/" "$out/assets/"
  '';

  buildPhase = ''
    runHook preBuild

    V=1 make ${finalAttrs.name} SUPPORT_QWERTY=1

    runHook postBuild
  '';

  hardeningDisable = ["format" "fortify"];

  installPhase = ''
    install -D ${finalAttrs.name} $out/bin/${finalAttrs.name} --mode 0755
    cp -r resources $out/assets
  '';

  meta.mainProgram = finalAttrs.name;
})
