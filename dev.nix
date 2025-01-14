{ pkgs, ... }: {
  # Which nixpkgs channel to use.
  ####channel = "stable-24.05"; # or "unstable"
  channel = "unstable-24.11";
  # Use https://search.nixos.org/packages to find packages
  packages = [
    pkgs.uv
  ];
  # Sets environment variables in the workspace
  env = {};
  idx = {


    # Search for the extensions you want on https://open-vsx.org/ and use "publisher.id"
    extensions = [ "ms-python.python" "ms-toolsai.jupyter" ];
    workspace = {
      # Runs when a workspace is first created with this `dev.nix` file
      onCreate = {
        install =
          "uv init hello-world && cd hello-world && uv add --dev ipykernel pandas matplotlib && uv run ipython kernel install --user --name=hello-world";
        # Open editors for the following files by default, if they exist:
        default.openFiles = [ "hello.py" ];
      };
    };
  };
}
