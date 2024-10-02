#!/bin/bash
# set -x

# make <my_keyboard>:<my_keymap>
# make <my_keyboard>:<my_keymap>:flash

# qmk compile -kb <my_keyboard> -km <my_keymap>
# qmk flash -kb <my_keyboard> -km <my_keymap>

cd "$(dirname "$0")" || exit 1

keyboard_def=jqqr/minyu
keymap_def=hhkb_ext

# keyboard_def=minyu
# keymap_def=hhkb

help-info() {
	echo -e "Usage:\n\t$0 [OPTION]..."
	echo '
    OPTION:
        -k, --keyboard  <PARM>        default '"$keyboard_def"'
        -m, --keymap    <PARM>        default '"$keymap_def"'
        -f, --flash                   flash
        -v, --via                     enable via
        -c, --custom-macro            open custom macro
        -p, --passwd                  input password for PWD_MACRO
        -h, --help                    show help info
    '
}

temp=$(getopt -o k:m:fvcph --long keyboard:,keymap:,flash,via,custom-macro,passwd,help -n "$0" -- "$@") || {
	echo "Terminating..." >&2
	exit 1
}
eval set -- "$temp"

keyboard=$keyboard_def
keymap=$keymap_def
flash=false
via=false
macro=false
passwd_macros=()

read_passwd() {
	echo -n "Enter Password for $1: "
    read -s -r pwd; echo
	[ -n "$pwd" ] && {
		local def="-D$1=\"${pwd//\"/\\\"}\""; #echo "$def"
		local def_trans; def_trans="$(echo -n "$def" | sed 's/\\/\\\\/g; s/"/\\"/g; s/#/\\#/g')"; #echo "$def_trans"
		passwd_macros+=("$def_trans")
	}
}

while true; do
	case "$1" in
	-h| --help)
		help-info
		exit 0
		;;
	-k | --keyboard)
		if [ -n "$2" ]; then keyboard=$2; fi
		shift 2
		;;
	-m | --keymap)
		if [ -n "$2" ]; then keymap=$2; fi
		shift 2
		;;
	-f | --flash)
		flash=true
		shift
		;;
	-v | --via)
		via=true
		shift
		;;
	-c | --custom)
		macro=true
		shift
		;;
	-p | --passwd)
		read_passwd USER_PASSWD
		read_passwd ROOT_PASSWD
		shift
		;;
	--)
		shift
		break
		;;
	*)
		echo "Internal error!" >&2
		exit 1
		;;
	esac
done

[ "$via" == true ] && {
    [[ "$keymap" =~ "_via" ]] || keymap="${keymap}_via"
}

target="$keyboard:$keymap"
[ "$flash" == true ] && target+=":flash"

[ "$macro" == true ] && extra_flags+="-DCUSTOM_MACRO_OPEN ${passwd_macros[*]}"

make clean
make EXTRAFLAGS="$extra_flags" "$target"
