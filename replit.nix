{ pkgs }: {
	deps = [
		pkgs.clang_12
		pkgs.gdb
		pkgs.gnumake
		pkgs.ccls
		pkgs.sfml
	];
}