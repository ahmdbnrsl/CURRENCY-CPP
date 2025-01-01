{ pkgs, ... }: {
  channel = "stable-24.05";
  packages = [
    pkgs.doas-sudo-shim
    pkgs.pkg
    pkgs.gcc
    pkgs.conan
    pkgs.curl
  ];

  env = {};
  idx = {
    extensions = [
    ];

    previews = {
      enable = true;
      previews = {
     
      };
    };

    workspace = {
      onCreate = {
      };
      onStart = {
      };
    };
  };
}
