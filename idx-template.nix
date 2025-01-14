{ pkgs, ... }: {
#  packages = [
#    pkgs.uv
#  ];
  bootstrap = ''    
    mkdir "$out"
    mkdir -p "$out/.idx/"
    cp -rf ${./dev.nix} "$out/.idx/dev.nix"
    chmod -R +w "$out"
  '';
}
