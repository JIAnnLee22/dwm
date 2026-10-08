{
  lib,
  stdenv,
  pkg-config,
  makeWrapper,
  libx11,
  libxinerama,
  libxft,
  fontconfig,
  freetype,
  src,
  conf ? null,
}:

stdenv.mkDerivation {
  pname = "dwm";
  version = "6.8";
  inherit src;

  nativeBuildInputs = [
    pkg-config
    makeWrapper
  ];
  buildInputs = [
    libx11
    libxinerama
    libxft
    fontconfig
    freetype
  ];

  # `pkgs.dwm.override { conf = ./config.h; }` keeps custom configuration declarative.
  postPatch = lib.optionalString (conf != null) ''
    cp ${conf} config.h
  '';

  makeFlags = [
    "PREFIX=/"
    "MANPREFIX=/share/man"
    "X11INC=${libx11.dev}/include"
    "X11LIB=${libx11.out}/lib"
    "FREETYPEINC=${freetype.dev}/include/freetype2"
  ];
  installFlags = [ "DESTDIR=$(out)" ];

  postInstall = ''
    # Resolve setuid launchers before unprivileged store executables.
    # Application dependencies still come from the user's/system's PATH.
    wrapProgram "$out/bin/dwm" --prefix PATH : /run/wrappers/bin

    mkdir -p "$out/share/xsessions"
    cat > "$out/share/xsessions/dwm.desktop" <<EOF
    [Desktop Entry]
    Name=dwm
    Comment=Dynamic window manager for X11
    Exec=$out/bin/dwm
    Type=Application
    DesktopNames=dwm
    EOF
  '';

  meta = {
    description = "Dynamic window manager for X";
    homepage = "https://dwm.suckless.org/";
    license = lib.licenses.mit;
    platforms = lib.platforms.linux;
    mainProgram = "dwm";
  };
}
