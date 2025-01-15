{ pkgs, environment ? "py-notebook",  ... }: {
    packages = [];

  bootstrap = ''

    cp -rf ${./.}/${environment} "$WS_NAME"
    chmod -R +w "$WS_NAME"

    chmod -R +wx "$WS_NAME"

    mv "$WS_NAME" "$out"

  '';
}
