{ pkgs }: {
	deps = [
		pkgs.clang_12
		pkgs.gdb
		pkgs.gnumake
		pkgs.man
		pkgs.ccls
		pkgs.sfml
	];
}
