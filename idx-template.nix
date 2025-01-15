{ pkgs, environment ? "py-notebook",  ... }: {
    packages = [
      pkgs.python311
      pkgs.python311Packages.pip
    ];
  bootstrap = ''
    pip install uv

    cp -rf ${./.}/${environment} "$WS_NAME"
    chmod -R +w "$WS_NAME"

    chmod -R +wx "$WS_NAME"

    mv "$WS_NAME" "$out"

  '';
}
