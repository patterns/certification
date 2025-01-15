{ pkgs, environment ? "py-notebook",  ... }: {
    packages = [ pkgs.curl ];
  bootstrap = ''
    curl -LsSf https://astral.sh/uv/install.sh | sh
    cp -rf ${./.}/${environment} "$WS_NAME"
    chmod -R +w "$WS_NAME"

    chmod -R +wx "$WS_NAME"

    mv "$WS_NAME" "$out"

  '';
}
