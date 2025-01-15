{ pkgs, environment ? "py-notebook",  ... }: {
    packages = [ pkgs.curl ];
  bootstrap = ''
    cp -rf ${./.}/${environment} "$WS_NAME"
    chmod -R +w "$WS_NAME"

    chmod -R +wx "$WS_NAME"

    mv "$WS_NAME" "$out"

  '';
}
